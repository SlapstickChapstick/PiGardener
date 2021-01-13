#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int microsecond = 1000000;
int humidity_reading = 85;
int temperature_reading = 2;
char* loop_running = "false";

void StartMainLoop() {
    loop_running = "true";
    while (loop_running == "true")
    {
        printf("Humidity : %d | Temperature : %d\n", humidity_reading, temperature_reading);
        usleep(3 * microsecond);
    }
}