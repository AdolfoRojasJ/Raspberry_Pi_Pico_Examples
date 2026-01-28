#include "pico/stdlib.h"
#define LEDPIN 0

void led_init(void)
{
	gpio_init(LEDPIN);
	gpio_set_dir(LEDPIN, GPIO_OUT);
}

int main()
{
	led_init();
	while(1)
	{
		gpio_put(LEDPIN, 1);
		sleep_ms(500);
		gpio_put(LEDPIN, 0);
		sleep_ms(500);
	}
}
