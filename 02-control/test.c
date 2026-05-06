#include "stdio-task/stdio-task.h"
#include "stdio.h"
#include "stdlib.h"
#include "pico/stdlib.h"
#include "protocol-task/protocol-task.h"
#define DEVICE_NAME "my-pico-device"
#define DEVICE_VRSN "v0.0.1"

char* stdio_task_handle()
{
	int symbol = getchar_timeout_us(0);
	if (symbol == PICO_ERROR_TIMEOUT)
	{
		return NULL;
	}

	putchar(symbol);

	if (symbol == '\r' || symbol == '\n')
	{
		command[command_buf_idx] = '\0';
		command_buf_idx = 0;
		
		printf("received string: '%s'\n", command);

	return command;
	}

	if (command_buf_idx >= COMMAND_BUF_LEN - 1)
	{
		command_buf_idx = 0;
		return NULL;
	}

	command[command_buf_idx] = symbol;
	command_buf_idx++;
	return NULL;
}

void version_callback(const char* args){
	printf("device name: '%s', firmware version: %s\n", DEVICE_NAME, DEVICE_VRSN);
}

const uint LED_PIN = 25;
api_t device_api[] =
{
	{"version", version_callback, "get device name and firmware version"},
	{NULL, NULL, NULL},
};
void protocol_task_init(api_t* device_api){}
protocol_task_init(device_api);
protocol_task_handle(stdio_task_handle());

int main() {
    stdio_init_all();

    stdio_task_init();
    while (true) {
        stdio_task_handle();
    }
}