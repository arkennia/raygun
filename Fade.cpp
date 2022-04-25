#include "Fade.h"

void Fade::begin(unsigned long bright_ms, unsigned long dim_ms, unsigned long bright_hold_ms,
                 unsigned long dim_hold_ms, uint8_t max_bright, uint8_t min_bright)
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


//determine if it is time to trigger an update_State() function. returns current brightness. 
uint8_t Fade::update(unsigned long elapsed)
{
        delta_ms += elapsed;

        if (delta_ms >= current_step_ms) {
                delta_ms = 0;
                update_state();
        }
        return cur_bright;
}

//swap between the 4 light states
void Fade::update_state()
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