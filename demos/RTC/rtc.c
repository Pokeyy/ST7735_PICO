#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "drivers/ST7735_TFT.h"
#include "drivers/fonts.h"
#include "hardware/regs/powman.h"
#include "hardware/structs/powman.h"


#define POWMAN_TIMER_PASS                   (0x5AFE << 16)
#define POWMAN_TIMER_RUN                    (1u << 1)
#define POWMAN_TIMER_USE_XOSC               (1u << 9)


uint64_t read_ao_time(void) {
    uint32_t upper1, upper2, lower;
    do {                                            
        upper1 = powman_hw->read_time_upper;
        lower = powman_hw->read_time_lower;

        // AON Timer can increment during read, upper2 is to protect against that and check if lower 32 bits rolled over to incr. upper 32 by comparing it to before rollover
        upper2 = powman_hw->read_time_upper;                
    } while(upper1 != upper2);

    return ((uint64_t)upper1 << 32 | lower);    // actual time in ticks 
}

void ao_timer_demo(void) {
    // Every write to TIMER register must have the Password in the upper 16bits, then you send anything to write
    // Bit 2 resets the clock
    powman_hw->timer = POWMAN_TIMER_PASS | (1u << 2);          
    
    // Send Password, Set Bit 1 to start timer, Set Bit 9 to use Crystal Osc. for timer (more accurate)
    powman_hw->timer = POWMAN_TIMER_PASS | POWMAN_TIMER_RUN | POWMAN_TIMER_USE_XOSC;

    while (true) {
        uint64_t ticks = read_ao_time();                                            // Grab 1 tick = 1ms
        uint64_t total_seconds = ticks / 1000;                                      // ms to total seconds
        uint64_t hours   = total_seconds / 3600;                                    // seconds to current hours
        uint64_t minutes = (total_seconds % 3600) / 60;                             // seconds to current minutes
        uint64_t seconds = total_seconds % 60;                                      // current seconds including roll over
        printf("AO Timer = %02llu:%02llu:%02llu\n", hours, minutes, seconds);       // %02 = print at least 2digits, pad 0's if less | llu = long long unsigned
        //fflush(stdout); // force immediate output

        sleep_ms(1000);
    }
}