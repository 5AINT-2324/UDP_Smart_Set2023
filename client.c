//
// Created by Gabriele on 28/09/23
//

#include <stdio.h>
#include <time.h>
#include <string.h>
#include "UDP.h"
#define TIMEOUT 1*CLOCKS_PER_SEC // 1 secondo
#define UDP_PORT 23365

int main(int argc, char* argv[]){
    unsigned char buffer[1024];
    unsigned long ip_address;
    unsigned short port_number;
    unsigned long start, now;
    
    if (argc < 4) // 1 argument required ip address, 2 arguments required on/off and 3 arguments required time
    {
        printf("Deve essere fornito l'indirizzo IP del server!\r\n");
        return -1;
    }
    // inizializzazione socket con numero di porta UDP arbitrario
    if (UDP_init(0) < 0)
    {
        printf("Errore inizializzazione socket!\r\n");
        return -1;
    }
    ip_address = IP_to_bin(argv[1]);
    buffer[0] = (unsigned char) argv[1];
    buffer[1] = (unsigned char) argv[2];
    port_number = UDP_PORT;

    UDP_send(ip_address, port_number, buffer, sizeof(buffer));
    start = clock();
    now = clock();
    while((now - start) < TIMEOUT) {
        UDP_receive((unsigned long *) ip_address, (unsigned short *) port_number, buffer, sizeof(buffer));
        if(atoi(buffer[1023]) == 1){
            printf("ERR\r\n");
            UDP_close();
            return 0;
        }else{
            printf("OK\r\n");
            UDP_close();
            return 1;
        }
        now = clock();
    }
    printf("Nessuna risposta ricevuta\r\n");
    UDP_close();
    return -1;
}