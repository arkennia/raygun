#ifndef FADE_H
#define FADE_H

#include <stdint.h>

// Fade/Breathe/Pulse allows for different speeds of Brightening and dimming, along with a pause at maximumum and minimum light
class Fade
{
        enum LightState { DIMMING, HOLDINGDIM, BRIGHTENING, HOLDINGBRIGHT };

    private:
        LightState current_state;

        // Milliseconds to reach max Dimness, this is half of the cycle full times.
        unsigned long dim_ms;
        // Milliseconds to reach max Brightness, typically the same as dimTime.
        unsigned long bright_ms;
        // Milliseconds to hold at brightest value.
        unsigned long bright_hold_ms;
        // Millisconds to hold at dimmest value.
        unsigned long dim_hold_ms;
        // Color Values
        uint8_t max_bright;
        uint8_t min_bright;
        uint8_t cur_bright;

        // Amount of time between each increase.
        unsigned long bright_step_ms;
        // Amount of time between each decrease.
        unsigned long dim_step_ms;

        unsigned long delta_ms;

        unsigned long current_step_ms;

        void update_state();

    public:
        Fade() = default;

        uint8_t update(unsigned long elapsed);

        void begin(unsigned long bright_ms = 1500, unsigned long dim_ms = 1500,
                   unsigned long bright_hold_ms = 200, unsigned long dim_hold_ms = 200,
                   uint8_t max_bright = 150, uint8_t min_bright = 20);
};

#endif // FADE_H