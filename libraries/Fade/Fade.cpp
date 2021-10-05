#include "Fade.h"

bool Fade::checktime(int timeToCheck)
{
        if (delta >= timeTocheck) {
                Delta = 0;
                lastTimeCheck = 0;
                return true;
        } else {
                delta += lastTimeCheck;
                return false;
        }
}

void Fade::fadeState()
{

        // // 0 raise brightness
        // if (brightState = 0) {
        //         brightStep++; // light isn't at max yet
        //         for (int i = 0; i < NUMPIXELS; i++) { // ADJUST TO INTAKE ANY PIXEL STRIPS
        //                 pixel_Strip.setPixelColor(
        //                         i, pixel_Strip.Color(0, brightStep, 0,
        //                                              0)); // Set light brighness to brightStep.
        //                                                   // ADJUST TO INTAKE ANY PIXEL STRIPS
        //         }
        // }
        // // 1 hold crecendo
        // if (brightState = 1) {
        // }
        // // 3 decrecendo
        // if (brightState = 2) {
        // }
        // // 4 hold Decrecendo
        // if (brightState = 3) {
        // }
        // update brightState information for next pass
        switch (brightState) {
        case DIMMING:
                break;
        case HOLDINGDIM:
                break;
        case BRIGHTENING:
                raiseBrightness(brightStep++);
                break;
        case HOLDINGBRIGHT:
                break;
        }
}

void Fade::raiseBrightness(iunt val)
{
        brightStep++; // light isn't at max yet
        for (int i = 0; i < NUMPIXELS; i++) { // ADJUST TO INTAKE ANY PIXEL STRIPS
                pixel_Strip.setPixelColor(
                        i, pixel_Strip.Color(0, brightStep, 0,
                                             0)); // Set light brighness to brightStep.
                                                  // ADJUST TO INTAKE ANY PIXEL STRIPS
        }
}