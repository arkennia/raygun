#ifndef FADE_H
#define FADE_H

#include <stdint.h>

// Fade/Breathe/Pulse allows for different speeds of Brightening and dimming, along with a pause at
// maximumum and minimum light
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

        void update_state()
        {
                switch (current_state) {
                case DIMMING:
                        if (cur_bright <= min_bright) {
                                current_state = HOLDINGDIM;
                                current_step_ms = dim_hold_ms;
                        } else {
                                cur_bright--;
                        }
                        break;
                case HOLDINGDIM:
                        current_state = BRIGHTENING;
                        current_step_ms = bright_step_ms;
                        break;
                case BRIGHTENING:
                        if (cur_bright >= max_bright) {
                                current_state = HOLDINGBRIGHT;
                                current_step_ms = bright_hold_ms;
                        } else {
                                cur_bright++;
                        }
                        break;
                case HOLDINGBRIGHT:
                        current_state = DIMMING;
                        current_step_ms = dim_step_ms;
                        break;
                default:
                        break;
                }
        }

    public:
        Fade() = default;

        uint8_t update(unsigned long elapsed)
        {
                delta_ms += elapsed;

                if (delta_ms >= current_step_ms) {
                        delta_ms = 0;
                        update_state();
                }
                return cur_bright;
        }

        void begin(unsigned long bright_ms = 1500, unsigned long dim_ms = 1500,
                   unsigned long bright_hold_ms = 200, unsigned long dim_hold_ms = 200,
                   uint8_t max_bright = 150, uint8_t min_bright = 20)
        {
                this->bright_ms = bright_ms;
                this->dim_ms = dim_ms;
                this->bright_hold_ms = bright_hold_ms;
                this->dim_hold_ms = dim_hold_ms;
                this->max_bright = max_bright;
                this->min_bright = min_bright;
                this->cur_bright = min_bright;

                uint8_t bright_difference = max_bright - min_bright;

                this->bright_step_ms = bright_ms / bright_difference;
                this->dim_step_ms = dim_ms / bright_difference;
                this->delta_ms = 0;
                this->current_state = BRIGHTENING;
                this->current_step_ms = bright_step_ms;
        }
};

#endif // FADE_H