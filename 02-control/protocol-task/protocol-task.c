#include "protocol-task.h"
#include "stdio.h"
#include "string.h"

static api_t* api = {0};
static int commands_count = 0;

void protocol_task_init(api_t* device_api) {
    api = device_api;
    int counter = 0;
    while (device_api[counter].command_name) {
        counter++;
    } 
    commands_count = counter;
}

void protocol_task_handle(char* command_string) {

    if (!command_string) {
        return;
    }

// логика обработки полученной строки. Делим ее на команду и аргументы:
    const char* command_name = command_string;
    const char* command_args = NULL;
    char* space_symbol = strchr(command_string, ' ');
    if (space_symbol) {
        *space_symbol = '\0';
        command_args = space_symbol + 1;
    } else {
        command_args = "";
    }

  
// Добавляем вывод найденных имени команды и ее аргументов;
    printf("command name: %s %s", command_name, "\n");
    printf("command args: '%s'", command_args, "\n");

  
// в цикле проходим по массиву команд `api` и ищем совпадение имени команды;
    for (int i = 0; i < commands_count; i++) {
        if (strcmp(command_name, api[i].command_name)) {
            continue;
        }
        api[i].command_callback(command_args);
        return;
    }
    printf("ERROR: COMMAND NOT FOUND\n");
    return;
}