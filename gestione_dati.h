
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct dati{
    int on_of;
    int time;
}data;

int gestOF(struct dati data){
    if(data.on_of == 0){
        return 0; //in caso di off
    }
    if(data.on_of == 1){
        return 1; //in caso di on
    }
}