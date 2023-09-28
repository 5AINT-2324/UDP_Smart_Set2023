#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>

enum State { OFF, ON };

struct dati {
    enum State on_off;
    int time;
} data;

#define OFF_STR "off"
#define ON_STR "on"

// Function to convert enum State to string representation
const char* stateToString(enum State state) {
    return (state == OFF) ? OFF_STR : ON_STR;
}

int gestOF(struct dati data) {
    const char* stateStr = stateToString(data.on_off);

    if (strcasecmp(stateStr, OFF_STR) == 0) {
        return -1; // in caso di off
    }
    if (strcasecmp(stateStr, ON_STR) == 0) {
        return 0; // in caso di on
    }
    // Handle other cases or return an error code here.
    return -2; // Unknown state
}
