
#ifndef WEATHER_H
#define WEATHER_H

#include "lwip/err.h"
#include "lwip/pbuf.h"
#include "lwip/altcp.h"

#define HOST                                "wttr.in"
#define URL_REQUEST                         "/Camarillo?format=j1"
#define WIFI_RETRY_DELAY_MS                 5000
#define FETCH_INTERVAL_MS                   1800000

int fetch_weather(int *temp_out);
err_t my_recv_fn(void *arg, struct altcp_pcb *conn, struct pbuf *p, err_t err);
#endif