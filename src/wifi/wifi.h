#ifndef WIFI_H 
#define WIFI_H
#include "pico/cyw43_arch.h"
#include "event_groups.h"

EventGroupHandle_t wifi_group;

void wifi_task(void *pvParameters);

#endif