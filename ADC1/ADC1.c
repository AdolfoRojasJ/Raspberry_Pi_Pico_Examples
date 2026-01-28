#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"


float read_voltage() {
    
    /* 12-bit conversion, assume max value == ADC_VREF == 3.3 V */
    const float conversionFactor = 3.3f / (1 << 12);
    float adc = (float)adc_read() * conversionFactor;	
    printf("Voltage = %.02f %c\n", adc, "v");
    sleep_ms(500);
}

int main() {
    stdio_init_all();
    adc_init();
    adc_gpio_init(27);
    adc_select_input(1);

    while (true) {
        read_voltage();
    }
}
