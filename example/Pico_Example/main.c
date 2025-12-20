#include <stdio.h>
#include "pico/stdlib.h"
#include "epd_api.h"

int main() {
    stdio_init_all();
    
    printf("EPD Pico Example Starting...\n");
    
    // Initialize EPD here
    // EPD_Init(...);

    while (true) {
        printf("Hello from Pico!\n");
        sleep_ms(1000);
    }
    return 0;
}
