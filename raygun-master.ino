#include "Fade.h"
// ###### NEW ######
#include "Switch.h"
#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <DFRobotDFPlayerMini.h>
#include <HardwareSerial.h>

void get_delta();

// Control Systems input pins
//  3.3 volt pin to the selector switch to switch lighting and sound settings (INPUT HIGH), advise a
//  pulldown resistor in this section Pins 13, 6 and 5 do not work for this section for some unknown
//  reason, and where removed from planning during the testing phase0
#define SWITCHPIN1 12
#define SWITCHPIN2 11
#define SWITCHPIN3 10
#define SWITCHPIN4 9
#define TRIGGERPIN 24

/// Light Definitions///
#define LIGHTSTRIPPIN 25
#define FADEPIXELS 10
#define VENTPIXELS 2
#define SUMPIXELS 12 // fix when possible to be an addition of vent and fade pixels

// one LED strip, animations need to be split, teh Pixels are all a single set
Adafruit_NeoPixel stripPixels(SUMPIXELS, LIGHTSTRIPPIN, NEO_GRBW + NEO_KHZ800);

Fade g_fade; // Green channel color set
Fade r_fade; // Red Channel Vent color set
DFRobotDFPlayerMini myDFPlayer;
// ###### NEW ######
Switch settingSwitch;
string prevSwitchState = 0;

/// Standard timekeeping code, uses get_Delta() function to determine time passed between loops
unsigned long prev_time = 0;
unsigned long cur_time = 0;
unsigned long delta = 0; // pass to functions that require an input of passed time

unsigned long triggerDuration = 0; // how many MS the gun needs to be locked up to finish
// HandletriggerState, different depending on gun setting
unsigned long triggerTimeElapsed = 0;
enum TriggerState { Active, Inactive, Finished };
TriggerState triggerState;

// SOUND SYSTEM
String currentSoundLoop = ""; // active ambient raygun sound
String currentTriggerSound = ""; // acctive trigger sound when fired , combine with ambient in
                                 // sound mix software, cannot play two tracks at once

void setup()
{
        pinMode(SWITCHPIN1, INPUT);
        pinMode(SWITCHPIN2, INPUT);
        pinMode(SWITCHPIN3, INPUT);
        pinMode(SWITCHPIN4, INPUT);
        pinMode(TRIGGERPIN, INPUT);
        ///////#----PREPARE THE SOUND SYSTEM---#///////
        // already defined by default
        // Serial1.setRX(3); // this is the RX GP01 pin on the feather RP2040
        // Serial1.setTX(2); // this is the TX GP00 pin on the feather RP2040

        // myHardwareSerial.begin(9600);// this doesnt work, but seems to be defaulted to
        // Serial1.begin(9600); // if use youse the RX, TX ports this should work****
        delay(3000); // buffer delay

        Serial.begin(9600); // USB debug communication
        delay(3000); // buffer delay
        // myDFPlayer.begin(Serial1);***

        //// this code unfortunately doesnt work, i am uncertain to why the true/false statement
        /// fails, though if i had to guess its due to using pre assigned serials////
        // if (!myDFPlayer.begin(Serial1))
        // { //Using hardware Serial1 to communicate with mp3.
        //     Serial.println(F("Unable to begin:"));
        //     Serial.println(F("1.Please recheck the connection!"));
        //     Serial.println(F("2.Please insert the SD card!"));
        //     while (true)
        //     {
        //         delay(0); // Code to compatible with ESP8266 watch dog.
        //     }
        // }
        // Serial.println(F("DFPlayer Mini online."));

        ///////#----PREPARE LIGHT SYSTEM---#///////
        stripPixels.begin();
        g_fade.begin();
        r_fade.begin();

        // ###### NEW ######
        settingSwitch.begin(SWITCHPIN1, SWITCHPIN2, SWITCHPIN3, SWITCHPIN4);

        // myDFPlayer.volume(25); // Set volume value. From 0 to 30
        //  myDFPlayer.play(1); // Play the first mp3
}

void loop()
{

        // gets how much time has past since last loop and stores the delta for all update code
        get_delta();

        if (triggerState == Active) {
                triggerState = handleTriggerState();
                Serial.println(F("PEW PEW"));
        } else if (triggerState == Finished) {
                handleSwitchState(settingSwitch.getState(), Switch::Update::CHANGE_STATE);
        } else {
                // step 1: what state is the control dial at on the physical Raygun?
                // step 2: is the raygun state the same as it was the previous check?
                Switch::Update update = settingSwitch.update();
                handleSwitchState(settingSwitch.getState(), update);
                // need to update switch state so the lights are properly set or change based on
                // provided informationvvv
                prevSwitchState = handleRayGunState(settingSwitch.getState());
                // Behaviors for active trigger
                triggerState = handleTriggerState(); // need this to
        }

        // update string of pixel colors based on information provided from switchstate
        for (int i = 0; i < FADEPIXELS; i++) {
                stripPixels.setPixelColor(i, stripPixels.Color(0, g_fade.update(delta), 0, 0));
        }
        for (int i = FADEPIXELS; i < SUMPIXELS; i++) {
                stripPixels.setPixelColor(i, stripPixels.Color(r_fade.update(delta), 0, 0, 0));
        }
        stripPixels.show();

        // make the fun noise
        // myDFPlayer.play(currentSoundLoop);
        // add loop trim integer value, so music plays seamlessly, compare against Delta
        // Value DF player has a loop function check and see if DFPlayer can get a video
        // length, which will simplify this task
}

// what state of lights and sounds are we set to currently for the raygun? swaps it to the
// appropriate settings
void handleSwitchState(Switch::State state, Switch::Update update_type)
{
        if (update_type == Switch::Update::CHANGE_STATE) {
                switch (state) {
                case Switch::State::Setting1:
                        // pass G-Fade color rules, setting 1 is standard generic
                        // Set Sound effect Loop
                        Serial.println("Switch State is 1");
                        g_fade.begin(3000, 3000, 3000, 3000, 200, 2);
                        r_fade.begin(3000, 3000, 3000, 3000, 200, 2);
                        currentSoundLoop = "001"; /// cannot read in strings! must be integers, SWAP
                                                  /// TO ENUM SYSTEM
                        currentTriggerSound = "002";
                        // Assign trigger behavior sounds and colors
                        triggerDuration = 1000; // time to lock up raygun for fire sequence

                        break;

                case Switch::State::Setting2:
                        // High intensity pulsation effect
                        // High intensity pulsation sound effect
                        Serial.println("Switch State 2");
                        g_fade.begin(1000, 1000, 100, 100, 200, 20);
                        r_fade.begin(1000, 1000, 100, 100, 200, 20);
                        currentSoundLoop = "003";
                        currentTriggerSound = "004";
                        break;

                case Switch::State::Setting3:
                        Serial.println("Switch State 3");
                        g_fade.begin(0, 0, 0, 0, 0, 0);
                        r_fade.begin(0, 0, 0, 0, 0, 0);
                        break;

                case Switch::State::Setting4:
                        Serial.println("Switch State 4 ");

                        g_fade.begin(0, 0, 0, 0, 0, 0);
                        r_fade.begin(0, 0, 0, 0, 0, 0);
                        break;

                case Switch::State::OFF:
                        Serial.println("Switch State OFF");
                        g_fade.begin(0, 0, 0, 0, 0, 0);
                        r_fade.begin(0, 0, 0, 0, 0, 0);
                        if (prevState != state)

                                break;

                default:
                        Serial.println(F("Switch default"));
                        if (prevState != state) {
                                g_fade.begin(0, 0, 0, 0, 0, 0);
                                r_fade.begin(0, 0, 0, 0, 0, 0);
                        }
                        break;
                }
        }
}

// Interupts previous Handled Raygun state to handle firing sound and light settings
TriggerState handleTriggerState()
{

        if (digitalRead(TRIGGERPIN) == HIGH) {
                triggerTimeElapsed = 0;
                // PLAY SOUND HERE ///
                return Active;
        } else if (triggerState == Active && triggerTimeElapsed <= triggerDuration) {
                // already doing stuff
                triggerTimeElapsed += delta;
                return Active;
        } else if (triggerState == Active && triggerTimeElapsed >= triggerDuration) {
                triggerTimeElapsed = 0;
                return Finished;
        } else {
                return Inactive;
        }
}

///// standard time tracking code
///// detects how much time passes between loops and updates current delta (uptime)
void get_delta()
{
        cur_time = millis();
        delta = cur_time - prev_time;
        prev_time = cur_time;
}
