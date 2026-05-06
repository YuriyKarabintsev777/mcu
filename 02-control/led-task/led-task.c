#include "led-task.h"
#include "stdint.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"

const uint LED_PIN = 25;
uint LED_BLINK_PERIOD_US = 500000;

uint64_t led_ts;
led_state_t led_state;
bool last = true;

void led_task_state_set(led_state_t ls) {
    led_state = ls;
}

void led_task_init(){
    led_state = LED_STATE_OFF;
    led_ts = 0;
    led_task_state_set(led_state);
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
}

void led_task_handle() {
    switch (led_state) {
        case LED_STATE_OFF:
	        // ваш код
            gpio_put(LED_PIN, 0);
	        break;
        case LED_STATE_ON:
	        // ваш код
            gpio_put(LED_PIN, 1);
            break;
        case LED_STATE_BLINK:
	        // ваш код
            //boolean blink;
            if (time_us_64() > led_ts) {
	            led_ts = time_us_64() + (LED_BLINK_PERIOD_US / 2);
	            // ваш код
                /*if (last == true) {
                    printf("blink on\n");
                    gpio_put(LED_PIN, 1);
                    last = false;
                } else {
                    printf("blink off\n");
                    gpio_put(LED_PIN, 0);
                    last = true;
                }*/

                gpio_put(LED_PIN, last);
                last = !last;
            }
	        break;
        default:
	        break;
    }
}

void led_task_set_blink_period_ms(uint32_t period) {
    LED_BLINK_PERIOD_US = period * 1000;
}