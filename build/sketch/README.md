#line 1 "c:\\Users\\faane\\Documents\\Arduino\\raygun\\README.md"
# RayGun

Project for the creation of a ray gun for a cosplay.

## Equipment

1. Feather RP2040
   * Board Manager JSON [located here](https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json).

2. Adafruit Neopixel SK6812
    * Adafruit_Neopixel library is in the Arduino libraries.


## Environment Setup

1. Get the VSCode Arduino extension and set the Arduino path.
2. For proper IntelliSense, add the following to your `c_cpp_properties.json` file:
    * `...Arduino\\hardware\\arduino\\avr\\**`
    * `...Arduino\\hardware\\tools\\avr\\avr\\include\\**`
      * This is located in your Arduino install folder.
    * `...Arduino\\libraries\\**`
      * Typical default location is Documents.
3. Add `"C_Cpp.intelliSenseEngine": "Tag Parser",` to your `settings.json`.