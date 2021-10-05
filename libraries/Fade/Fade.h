#ifndef FADE_H
#define FADE_H

// Fade/Breathe/Pulse allows for different speeds of Brightening and dimming, along with a pause at
// Crecendo and decrecendo. very versatile!
class Fade // also known as breathe, Pulse
{
        enum LightState {
                DIMMING, // 0
                HOLDINGDIM, // 1
                BRIGHTENING, // 2
                HOLDINGBRIGHT, // 3

        };

    private:
        LightState brightState;

        // default Time values
        // milliseconds to reach max Dimness, this is half of the cycle full times
        int dimTime = 1500;
        // milliseconds to reach max Brightness, typically the same as dimTime
        int brightTime = 1500;
        int brightHoldTime = 200; // milliseconds to hold at maximum brightness
        int dimHoldTime = 200; // millisconds to hold at minimum brightness

        // Color Values
        int peakBright = 150;
        int minimumBright = 20;
        // int brightState // removing, replaced with LightState

        int brightGap = peakBright - minimumBright; // total brightness transition Gap
        int brightStep = brightTime / brightGap; // how many lower and raise light steps do we need
                                                 // per time interpolation? intiation value
        int dimStep = dimTime / brightGap;

        // self reseting timers + function
        int delta = 0; // millisonds to the next state, zero'd out at the end of each LightState.
                       // delta is assigned by the above time values
        int lastTimeCheck = 0; // this is used to store the last amount of time that passed,
                               // compared against delta and zeroed after passing delta.

        // Functions //
        bool checktime(int timeToCheck);

        // which fade state are we in?
        void fadeState();

        void raiseBrightness(int val);

    public:
}

#endif // FADE_H