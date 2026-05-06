#include "stdio-task/stdio-task.h"
#include "stdio.h"
#include "pico/stdlib.h"
#include "stdio-task/stdio-task.h"
#include "protocol-task/protocol-task.h"
#include "led-task/led-task.h"
#include "led-task/led-task.c"

#define DEVICE_NAME "my-pico-device"
#define DEVICE_VRSN "v0.0.1"
#define COMMAND_BUF_LEN 128
//const uint LED_PIN = 25;
led_state_t led_state;

void version_callback(const char* args) {
	printf("device name: '%s', firmware version: %s\n", DEVICE_NAME, DEVICE_VRSN);
}

void led_on_callback() {
	led_task_state_set(LED_STATE_ON);
	printf("led is working: ON\n");
} 

void led_off_callback() {
	led_task_state_set(LED_STATE_OFF);
	printf("led is working: OFF\n");
}

void led_blink_callback() {
	led_task_state_set(LED_STATE_BLINK);
	printf("led is working: BLINKING\n");
}

void led_blink_set_period_ms_callback(const char* args) {
	uint period_ms = 0;
	sscanf(args, "%u", &period_ms);
	led_task_set_blink_period_ms(period_ms);
	if (period_ms == 0) {
		printf("ERROR: period can not be 0\n");
	} else {
		printf("new period of blinking set\n");
	}
}

void help();
void help_prototype() {
	help();
}

api_t device_api[] =
{
	{"version", version_callback, "get device name and firmware version"},
	{"on", led_on_callback, "get information about led working"},
	{"off", led_off_callback, "get information about led not working"},
	{"blink", led_blink_callback, "get information about led blinking"},
	{"set_period", led_blink_set_period_ms_callback, "set new period of blinking"},
	{"help", help_prototype, "information about all possible commands"},
	{NULL, NULL, NULL},
};

void help() {
	int counter = 0;
	while (device_api[counter].command_name) {
		printf("Команда '%s', описание команды '%s' \n", device_api[counter].command_name, device_api[counter].command_help);
		counter++;
	}
	printf("закончен вывод команд\n");
}

int main() {
    protocol_task_init(device_api);
	led_task_init();
    stdio_init_all();

	//led_task_set_blink_period_ms(2000);
    //stdio_task_init();

    while (true) {
		protocol_task_handle(stdio_task_handle());
        led_task_handle();
    }
}