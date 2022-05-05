#include "RayGun.hpp"
#include "Util.h"

#include <Arduino.h>

RayGun raygun(500);

void setup()
{
        pinMode(SWITCHPIN1, INPUT);
        pinMode(SWITCHPIN2, INPUT);
        pinMode(SWITCHPIN3, INPUT);
        pinMode(SWITCHPIN4, INPUT);
        pinMode(TRIGGERPIN, INPUT);
        Serial.begin(9600); // USB debug communication
}

void loop()
{
        raygun.update();
}
