#ifndef SWITCH_H
#define SWITCH_H

#include <Arduino.h>

class Switch
{
    public:
        enum State { Setting1, Setting2, Setting3, Setting4, OFF };

        enum Update { POWER_ON, CHANGE_STATE, HOLD_STATE };

        Switch() = default;
        ~Switch() = default;

        /// Initialize the class, and assign the correct pins. Each parameter
        /// should be the corresponding pin.
        void begin(int setting1, int setting2, int setting3, int setting4,
                   unsigned long delay = 1000)
        {
                current_state = OFF;
                settingPins[0] = setting1;
                settingPins[1] = setting2;
                settingPins[2] = setting3;
                settingPins[3] = setting4;
                this->delay = delay;
        }

        /// Should be called in the main loop. Returns the current type of update to watch for.
        Update update(unsigned long delta)
        {
                // Copy value of current state into the space allocated for prev_state.
                State prev_state = current_state;
                elapsed += delta;
                if (elapsed >= delay) {
                        readPins();
                        updateState();
                        elapsed = 0;
                        if (prev_state == OFF && current_state != OFF) {
                                return Update::POWER_ON;
                        } else if (prev_state != current_state) {
                                return Update::CHANGE_STATE;
                        } else {
                                return Update::HOLD_STATE;
                        }
                } else {
                        return Update::HOLD_STATE;
                }
        }

        /// Gets the current switch state.
        State getState()
        {
                return current_state;
        }

    private:
        State current_state;
        unsigned long delay;
        unsigned long elapsed;
        /// Holds the pin numbers.
        int settingPins[4];
        /// Holds the value from calling digitalRead on the corresponding pin.
        int pinOutputs[4];

        /// Read all the pins, and assign them to the pinOutputs array.
        void readPins()
        {
                for (size_t i = 0; i < 4; i++) {
                        pinOutputs[i] = digitalRead(settingPins[i]);
                }
        }

        /// Use pinOutputs to update the switch state.
        void updateState()
        {
                for (int i = 0; i < 4; i++) {
                        if (pinOutputs[i] == HIGH) {
                                current_state = (State)i;
                                return;
                        }
                }
                // no pins active, power off
                current_state = OFF;
        }
};

#endif // SWITCH_H