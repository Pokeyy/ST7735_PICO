#ifndef WIFI_H 
#define WIFI_H
#include "pico/cyw43_arch.h"
#include "event_groups.h"

EventGroupHandle_t wifi_group;

int wifi_task();

#endif