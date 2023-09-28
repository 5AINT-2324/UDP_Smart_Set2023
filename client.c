#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "UDP.h"

#define UDP_PORT 23365
#define BUFFER_SIZE 1024

int ONOFF(unsigned char buffer[BUFFER_SIZE]) {
    char *endptr;
    long sleepTime = strtol((const char *) &buffer[1], &endptr, 10);

    // Check for conversion errors
    if (*endptr != '\0' || errno == ERANGE) {
        fprintf(stderr, "ERR 103: Conversion error\n");
        return 1; // Error code
    }

    sleep(sleepTime);
    return rand()%2;
}

void cleanup() {
    // Close the socket here
    UDP_close();
}

int main(void) {
    unsigned char buffer[BUFFER_SIZE];
    unsigned long ip_address;
    unsigned short port_number;

    memset(buffer, 0, sizeof(buffer));

    if (UDP_init(UDP_PORT) < 0) {
        fprintf(stderr, "ERR 101: Socket Error\n");
        return -1;
    }

    printf("Service Activated\n");

    // Register cleanup function to be called when the program exits
    atexit(cleanup);

    while (1) {
        if ((UDP_receive(&ip_address, &port_number, buffer, sizeof(buffer))) > 0) {
            if (ONOFF(buffer) == 1) {
                fprintf(stderr, "ERR 102: Object error\n");
                buffer[BUFFER_SIZE - 1] = 1;
                break;
            }

            UDP_send(ip_address, port_number, (void *) &buffer, sizeof(buffer));
        }
    }

    // The cleanup function registered with atexit will be called upon program exit


}
