#include "Arduino_mock.h"

typedef struct Pin {
    int mode;
    int value;
} pin_t;

static pin_t pins[NUM_PINS];

int digitalRead(int pin){
        return pins[pin].value;
}

void pinMode(int pin, int mode){
        if(mode == INPUT || mode == OUTPUT) {
                pins[pin].mode = mode;
        }
}

void digitalWrite(int pin, int value){
        if (value == HIGH || value == LOW) {
                pins[pin].value = value;
        }
}
