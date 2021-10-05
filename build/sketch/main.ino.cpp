#line 1 "c:\\Users\\faane\\Documents\\Arduino\\raygun\\main.ino"
#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

#ifdef __AVR__
#include <avr/power.h>
#endif

///------Define inputs -------\\\

#define PIN 12 // outputpin for Neopixel strip im using
//#define board_PIN 16 // boards installed Neopixel. apearently it is pin 16, NOT 27! not that it
// matters, ive had zero success making it work
#define NUMPIXELS 6

Adafruit_NeoPixel pixel_Strip(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);

///------Define Time -----\\\
//unsigned longs are suggested for time based function
unsigned long boardTime = 0; // total up time of the board
unsigned long frameTime = 10; // how long a frame should last, do i need this here?
unsigned long elapsed_time = 0;
uint8_t r = 0;
uint8_t g = 0;
uint8_t b = 0;
uint8_t w = 0;

#line 27 "c:\\Users\\faane\\Documents\\Arduino\\raygun\\main.ino"
void setup();
#line 36 "c:\\Users\\faane\\Documents\\Arduino\\raygun\\main.ino"
void loop();
#line 27 "c:\\Users\\faane\\Documents\\Arduino\\raygun\\main.ino"
void setup()
{
// Mostly needed for certain kinds of trinkets, no harm in leaving it in
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
        clock_prescale_set(clock_div_1);
#endif
        pixel_Strip.begin(); // REQUIRED Instantiate a neopixel list
}

void loop()
{

        if (elapsed_time >= frameTime) {
                elapsed_time = 0;
                pixel_Strip.fill(Adafruit_NeoPixel::Color(0, Adafruit_NeoPixel::sine8(g++), 0, 0),
                                 0, NUMPIXELS);
                pixel_Strip.show();
                // for (int i = 0; i < NUMPIXELS; i++) {
                //         pixel_Strip.setPixelColor(i, 0, Adafruit_NeoPixel::sine8(g++), 0, 0);
                //         pixel_Strip.show();
                // }
        }
}
