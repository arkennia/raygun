#ifndef ARDUINO_MOCK_H
#define ARDUINO_MOCK_H

#define HIGH 1
#define LOW 0

#define INPUT 0
#define OUTPUT 1

#define NUM_PINS 32

int digitalRead(int);
void pinMode(int, int);
void digitalWrite(int, int);

#endif // ARDUINO_MOCK_H
