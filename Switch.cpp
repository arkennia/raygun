#include "Switch.h"

#include <Arduino.h>

void Switch::begin(int setting1, int setting2, int setting3, int setting4)
{
        current_state = OFF;
        settingPins[0] = setting1;
        settingPins[1] = setting2;
        settingPins[2] = setting3;
        settingPins[3] = setting4;
}

Switch::Update Switch::update()
{
        State prev_state = current_state;
        readPins();
        updateState();

        if (prev_state == OFF && current_state != OFF) {
                return Update::POWER_ON;
        } else if (prev_state != current_state) {
                return Update::CHANGE_STATE;
        } else {
                return Update::HOLD_STATE;
        }
}

void Switch::readPins()
{
        for (size_t i = 0; i < 4; i++) {
                pinOutputs[i] = digitalRead(settingPins[i]);
        }
}

Switch::State Switch::getState()
{
        return current_state;
}

void Switch::updateState()
{
        for (int i = 0; i < 4; i++) {
                if (pinOutputs[i] == HIGH) {
                        current_state = (State)i;
                        return;
                }
        }
        current_state = OFF;
}
