#include <stdio.h>
#include "pico/cyw43_arch.h"
#include "pico/async_context.h"
#include "lwip/altcp.h"
#include "lwipopts.h"
#include "http_client_util.h"
#include "weather.h"

static char buffer_weather[2048];
static int buffer_index = 0;

int fetch_weather(int *temp_out)
{
    buffer_index = 0;

    EXAMPLE_HTTP_REQUEST_T req = {0};
    req.hostname   = HOST;
    req.url        = URL_REQUEST;
    req.headers_fn = NULL;
    req.recv_fn    = my_recv_fn;

    int result = http_client_request_sync(cyw43_arch_async_context(), &req);

    buffer_weather[buffer_index] = '\0';

    printf("\n===== RAW BUFFER =====\n%s\n======================\n", buffer_weather);
    printf("BUFFER SIZE: %d\n", buffer_index);
    printf("HTTP RESULT: %d\n", result);

    // 🔥 ONLY FAIL IF NO DATA
    if (buffer_index == 0)
    {
        printf("ERROR: no data\n");
        return -1;
    }

    char *pos = strstr(buffer_weather, "\"weather\"");
    if (!pos)
    {
        printf("ERROR: weather array not found\n");
        return -1;
    }

    pos = strchr(pos, '[');  // enter weather array
    if (!pos)
    {
        printf("ERROR: bad JSON structure\n");
        return -1;
    }

    int day = 0;

    while (day < 3)
    {
        char *found = strstr(pos, "\"avgtempF\"");
        if (!found)
        {
            printf("DEBUG: missing avgtempF at day %d\n", day);
            break;
        }

        char *colon = strchr(found, ':');
        if (!colon)
            break;

        colon++;

        while (*colon == ' ' || *colon == '\"')
            colon++;

        temp_out[day] = atoi(colon);

        printf("Day %d AVG Temp = %dF\n", day, temp_out[day]);

        day++;

        // 🔥 CRITICAL FIX: move forward properly
        pos = found + strlen("\"avgtempF\"");
    }

    buffer_index = 0;
    return 0;
}

err_t my_recv_fn(void *arg, struct altcp_pcb *conn, struct pbuf *p, err_t err)
{
    if (!p) return ERR_OK;

    int len = p->tot_len;

    if (buffer_index + len >= sizeof(buffer_weather))
        len = sizeof(buffer_weather) - buffer_index - 1;

    pbuf_copy_partial(p,
                       buffer_weather + buffer_index,
                       len,
                       0);

    buffer_index += len;

    printf("RX chunk: %d bytes (total buffer: %d)\n",
           len, buffer_index);

    pbuf_free(p);
    return ERR_OK;
}

// err_t my_recv_fn(void *arg, struct altcp_pcb *conn, struct pbuf *p, err_t err) // p = packed of received network data (P == NULL: no more data, connection is closing | P != NULL: here is some data)
// {
//     if (!p) return ERR_OK;      // no packet data, exit here and everything is good

//     char *data = (char *)p->payload; // cast char to void* to treat its memory as bytes 

//     int len = p->len;  

//     if (buffer_index + len >= sizeof(buffer_weather))
//         len = sizeof(buffer_weather) - buffer_index - 1;

//     memcpy(buffer_weather + buffer_index, data, len); // start copying at buffer_weather[buffer_index]
//     buffer_index += len; // just copied len bytes, move forward in the buffer for next copy

//     pbuf_free(p);
//     return ERR_OK;
// }

// int fetch_weather_old(int *temp_out)
// {
//     buffer_index = 0;

//     EXAMPLE_HTTP_REQUEST_T req = {0};       // object for http request
//     req.hostname = HOST;                    // which server to connect to
//     req.url = URL_REQUEST;                  // what page to connect to from the server
//     req.headers_fn = NULL;                  // what to do when http headers (meta data) arrive (nothing/ignore bc spam)
//     req.recv_fn = my_recv_fn;               // call this function whenever data arrives (lwIP will do this for each chunk of data)

//     int result = http_client_request_sync(cyw43_arch_async_context(), &req);        // DNS, then tcp connect to server, send http req (GET) to the URL, then receive data
//                                                                                     // async co ntext is allowing code to run, networking runs in background, then callbacks get triggered auto
//                                                                                     // runtime environment for networking

//     buffer_weather[buffer_index] = '\0';        // insert null terminator right after data received via my_recv_fn

//     char *pos = strstr(buffer_weather, "\"temp_F\"");
//     if (pos)    // did we find first occurence of " "temp_F" "
//     {
//         pos = strchr(pos, ':');     // then find first occurence of ':'
//         if (pos)                    // did we find first occurence of :
//         {
//             pos++;
//             while (*pos == ' ' || *pos == '\"') pos++;      // skip spaces and quotes 
//             *temp_out = atoi(pos);

//             printf("%dF\n", *temp_out);
//         }
//     }

//     buffer_index = 0;

//     return result;
// }