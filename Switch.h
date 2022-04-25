#ifndef SWITCH_H
#define SWITCH_H

class Switch
{
    public:
        enum State { Setting1, Setting2, Setting3, Setting4, OFF };
        enum Update { POWER_ON, CHANGE_STATE, HOLD_STATE };

        Switch() = default;
        ~Switch() = default;

        /// Initialize the class, and assign the correct pins. Each parameter
        /// should be the corresponding pin.
        void begin(int setting1, int setting2, int setting3, int setting4);

        /// Should be called in the main loop. Returns true if the raygun switch
        /// has gone from off to any of the settings.
        Update update();

        /// Gets the current switch state.
        State getState();

    private:
        State current_state;
        /// Holds the pin numbers.
        int settingPins[4];
        /// Holds the value from calling digitalRead on the corresponding pin.
        int pinOutputs[4];

        /// Read all the pins, and assign them to the pinOutputs array.
        void readPins();

        /// Use pinOutputs to update the switch state.
        void updateState();
};

#endif // SWITCH_H