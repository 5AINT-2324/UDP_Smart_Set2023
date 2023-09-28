
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct dati{
    char on_of[3];
    int time;
}data;

int gestOF(dati data){
    if(strcmp(data.on_of, "off")==0){
        return -1; //in caso di off
    }
    if(strcmp(data.on_of, "OFF")==0){
        return -1; //in caso di off
    }
    if(strcmp(data.on_of, "ON")==0){
        return 0; //in caso di on
    }
    if(strcmp(data.on_of, "on")==0){
        return 0; //in caso di on
    }
}