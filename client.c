// Created by Giacomo Cunardi on 28/09/23.
//


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "UDP.h"

#define UDP_PORT 23365

int ONOFF(unsigned char buffer[1024]) // 0 = OK 1 = ERR (La funzione non è completa ma simula il funzionanamnto della lampadina)
{
    sleep(atoi((const char *) buffer[1]));
    return rand()%2;
}

int main(void)
{
    unsigned char buffer[1024];     // Reception buffer
    unsigned long ip_address;       // Variable to store the client's IP address
    unsigned short port_number;     // Variable to store the client's port number
    int n;
    short iSwitch = 0;

    for(n = 0; n < 1024; n++)
    {
        buffer[n] = 0;
    }

    if (UDP_init(UDP_PORT) < 0) // Initialize the socket with UDP port number 54321
    {
        printf("ERR 101: Socket Error\r\n");
        return -1;
    }


    printf("Service Activated\r\n");


    while (iSwitch == 0)
    {
        if ((UDP_receive(&ip_address, &port_number, buffer, sizeof(buffer))) > 0) // Receive a datagram and check the message
        {
            if (ONOFF(buffer) == 1) {
                printf("ERR 102: Object error\n\r");
                buffer[1023] = 1;
                iSwitch = 1;
            }

            UDP_send(ip_address, port_number, (void *) &buffer,sizeof(buffer)); // Send the datagram back to the client
        }

    }
    UDP_close();
    return 0;


}