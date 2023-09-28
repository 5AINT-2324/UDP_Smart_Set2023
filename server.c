// Created by Gabriele on 28/09/23

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h> // Include the standard library header for strtol function
#include "UDP.h" // Assuming you have a UDP library/header

#define TIMEOUT (1 * CLOCKS_PER_SEC) // Enclose the macro replacement list in parentheses
#define UDP_PORT 23365

int main(int argc, char* argv[]) {
    if (argc < 4) {
        printf("Usage: %s <IP address> <on/off> <time>\n", argv[0]);
        return -1;
    }

    unsigned char buffer[1024];
    unsigned long ip_address;
    unsigned short port_number = UDP_PORT;

    if (UDP_init(0) < 0) {
        printf("Error initializing socket!\n");
        return -1;
    }

    ip_address = IP_to_bin(argv[1]);

    // Use strtol for better error handling during string-to-integer conversion
    char *endptr;
    long int value = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0' && *endptr != '\n') {
        // Handle conversion error, e.g., print an error message
        printf("Conversion error: %s is not a valid integer\n", argv[2]);
        UDP_close();
        return -1;
    }

    if (value < 0 || value > 255) {
        // Handle out-of-range values for buffer[0] (unsigned char)
        printf("Value out of range: %ld is not within the valid range of unsigned char (0 to 255)\n", value);
        UDP_close();
        return -1;
    }

    buffer[0] = (unsigned char)value;
    buffer[1] = '\0'; // Null-terminate the string
    UDP_send(ip_address, port_number, (const char*)buffer, strlen((const char*)buffer));

    clock_t start = clock();
    clock_t now;

    while (1) {
        now = clock();
        if ((now - start) >= TIMEOUT) {
            printf("No response received\n");
            UDP_close();
            return -1;
        }

        if (UDP_receive(&ip_address, &port_number, (char*)buffer, sizeof(buffer)) > 0) {
            if (atoi((const char*)buffer) == 1) {
                printf("ERR\n");
                UDP_close();
                return 0;
            } else {
                printf("OK\n");
                UDP_close();
                return 1;
            }
        }
    }
}
