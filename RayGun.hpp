#ifndef RAYGUN_HPP
#define RAYGUN_HPP

#include "Fade.hpp"
#include "Switch.hpp"
#include "Util.h"

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <DFRobotDFPlayerMini.h>
#include <HardwareSerial.h>

#define TRIGGER_DISABLED
#define SOUND_DISABLED

#define SWITCHPIN1 12
#define SWITCHPIN2 11
#define SWITCHPIN3 10
#define SWITCHPIN4 9
#define TRIGGERPIN 24

#define LIGHTSTRIPPIN 25
#define FADEPIXELS 10
#define VENTPIXELS 2
#define SUMPIXELS 12 // fix when possible to be an addition of vent and fade pixels

class RayGun
{
    public:
        enum TriggerStates { ACTIVE, FINISHED, INACTIVE };
        enum Sounds {BLAST=1, BIGGER_BLAST, EVEN_BIGGER_BLAST};
        /// Creates all necessary objects for the class to function.
        RayGun(unsigned int triggerDuration = 0)
        {
                this->_triggerState = INACTIVE;
                _stripPixels = Adafruit_NeoPixel(SUMPIXELS, LIGHTSTRIPPIN, NEO_GRBW + NEO_KHZ800);
                _stripPixels.begin();
                _gFade.begin();
                _rFade.begin();
                _settingSwitch.begin(SWITCHPIN1, SWITCHPIN2, SWITCHPIN3, SWITCHPIN4);
                this->_triggerTimeElapsed = 0;
                this->_triggerDuration = triggerDuration;
#ifndef SOUND_DISABLED
                _initSound();
#endif
        }

        /// The main portion of the Raygun. Will update things as needed.
        void update()
        {
                this->_delta = get_delta();
                _processSignals();
#ifndef SOUND_DISABLED
                _processSound();
#endif
        }

    private:
        Adafruit_NeoPixel _stripPixels;
        Fade _gFade; // Green channel color set
        Fade _rFade; // Red Channel Vent color set
        Fade _tGFade;
        Fade _tRFade;
        DFRobotDFPlayerMini _myDFPlayer;
        Switch _settingSwitch;
        unsigned long _delta;

        TriggerStates _triggerState;

        unsigned long _triggerDuration; // how many MS the gun needs to be locked up to finish

        unsigned long _triggerTimeElapsed;

        /// Manage the switch in the gun.
        void _handleSwitchState(Switch::State state, Switch::Update update_type)
        {
                if (update_type == Switch::Update::CHANGE_STATE
                    || update_type == Switch::Update::POWER_ON) {
                        switch (state) {
                        case Switch::State::Setting1:
                                // pass G-Fade color rules, setting 1 is standard generic
                                // Set Sound effect Loop
                                _gFade.begin(3000, 3000, 3000, 3000, 200, 2);
                                _rFade.begin(3000, 3000, 3000, 3000, 200, 2);
                                // Assign trigger behavior sounds and colors
                                _triggerDuration = 1000; // time to lock up raygun for fire sequence
                                break;

                        case Switch::State::Setting2:
                                // High intensity pulsation effect
                                // High intensity pulsation sound effect
                                _gFade.begin(1000, 1000, 100, 100, 200, 20);
                                _rFade.begin(1000, 1000, 100, 100, 200, 20);
                                break;

                        case Switch::State::Setting3:
                                _gFade.begin(3000, 3000, 3000, 3000, 200, 2);
                                _rFade.begin(3000, 3000, 3000, 3000, 200, 2);
                                break;

                        case Switch::State::Setting4:
                                _gFade.begin(2000, 500, 100, 100, 200, 20);
                                _rFade.begin(2000, 500, 100, 100, 200, 20);
                                break;

                        case Switch::State::OFF:
                                _gFade.begin(0, 0, 0, 0, 0, 0);
                                _rFade.begin(0, 0, 0, 0, 0, 0);
                                break;
                        }
                }
        }

        /// Do trigger things.
        TriggerStates _handleTriggerState()
        {
                if (digitalRead(TRIGGERPIN) == HIGH) {
                        _triggerTimeElapsed = 0;
                        // PLAY SOUND HERE ///
                        return ACTIVE;
                } else if (_triggerState == ACTIVE && _triggerTimeElapsed <= _triggerDuration) {
                        // already doing stuff
                        _triggerTimeElapsed += _delta;
                        return ACTIVE;
                } else if (_triggerState == ACTIVE && _triggerTimeElapsed >= _triggerDuration) {
                        _triggerTimeElapsed = 0;
                        return FINISHED;
                } else {
                        return INACTIVE;
                }
        }

        void _updateLights(Fade &gfade, Fade &rfade)
        {
                auto updateLights = [&](Fade &fade) {
                        return _stripPixels.Color(0, fade.update(_delta), 0, 0);
                };

                for (int i = 0; i < FADEPIXELS; i++) {
                        _stripPixels.setPixelColor(i, updateLights(gfade));
                }
                for (int i = FADEPIXELS; i < SUMPIXELS; i++) {
                        _stripPixels.setPixelColor(i, updateLights(rfade));
                }
                _stripPixels.show();
        }

        void _processSignals()
        {
#ifndef TRIGGER_DISABLED
                if (_triggerState == ACTIVE) {
                        _triggerState = _handleTriggerState();
                        _update_lights(_tGFade, _tRFade);
                } else if (_triggerState == FINISHED) {
                        // Force the a light settings update to change them from the ones
                        // used for the trigger.
                        _handleSwitchState(_settingSwitch.getState(), Switch::Update::CHANGE_STATE);
                        _updateLights(_gFade, _rFade);
                } else {
                        // step 1: what state is the control dial at on the physical Raygun?
                        // step 2: is the raygun state the same as it was the previous check?
                        _handleSwitchState(_settingSwitch.getState(),
                                           _settingSwitch.update(_delta));
                        // need to update switch state so the lights are properly set or change
                        // based on Behaviors for active trigger
                        _triggerState = _handleTriggerState();
                        _updateLights(_gFade, _rFade);
                }
#else
                _handleSwitchState(_settingSwitch.getState(), _settingSwitch.update(_delta));
#endif
        }

#ifndef SOUND_DISABLED

        void _initSound()
        {
                Serial1.setRX(3); // this is the RX GP01 pin on the feather RP2040
                Serial1.setTX(2); // this is the TX GP00 pin on the feather RP2040

                Serial1.begin(9600); // if use youse the RX, TX ports this should work****
                delay(500); // buffer delay

                myDFPlayer.begin(Serial1);
        }
        void _process_sound()
        {
        }
#endif
};

#endif /* RAYGUN_HPP */
