#include <stdio.h>
#include "pico/cyw43_arch.h"
#include "pico/async_context.h"
#include "lwip/altcp.h"
#include "lwipopts.h"
#include "http_client_util.h"
#include "weather.h"

static char buffer_weather[2048];
static int buffer_index = 0;

int fetch_weather()
{
    buffer_index = 0;

    EXAMPLE_HTTP_REQUEST_T req = {0};       // object for http request
    req.hostname = HOST;                    // which server to connect to
    req.url = URL_REQUEST;                  // what page to connect to from the server
    req.headers_fn = NULL;                  // what to do when http headers (meta data) arrive (nothing/ignore bc spam)
    req.recv_fn = my_recv_fn;               // call this function whenever data arrives (lwIP will do this for each chunk of data)

    int result = http_client_request_sync(cyw43_arch_async_context(), &req);        // DNS, then tcp connect to server, send http req (GET) to the URL, then receive data
                                                                                    // async co ntext is allowing code to run, networking runs in background, then callbacks get triggered auto
                                                                                    // runtime environment for networking

    buffer_weather[buffer_index] = '\0';        // insert null terminator right after data received via my_recv_fn

    char *pos = strstr(buffer_weather, "\"temp_F\"");
    if (pos)    // did we find first occurence of " "temp_F" "
    {
        pos = strchr(pos, ':');     // then find first occurence of ':'
        if (pos)                    // did we find first occurence of :
        {
            pos++;
            while (*pos == ' ' || *pos == '\"') pos++;      // skip spaces and quotes 
            int temp = atoi(pos);

            printf("%dF\n", temp);
        }
    }

    buffer_index = 0;

    return result;
}

err_t my_recv_fn(void *arg, struct altcp_pcb *conn, struct pbuf *p, err_t err) // p = packed of received network data (P == NULL: no more data, connection is closing | P != NULL: here is some data)
{
    if (!p) return ERR_OK;      // no packet data, exit here and everything is good

    char *data = (char *)p->payload; // cast char to void* to treat its memory as bytes 

    int len = p->len;  

    if (buffer_index + len >= sizeof(buffer_weather))
        len = sizeof(buffer_weather) - buffer_index - 1;

    memcpy(buffer_weather + buffer_index, data, len); // start copying at buffer_weather[buffer_index]
    buffer_index += len; // just copied len bytes, move forward in the buffer for next copy

    pbuf_free(p);
    return ERR_OK;
}

