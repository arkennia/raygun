# 1 "c:\\Users\\faane\\Documents\\Arduino\\raygun\\main.ino"
# 2 "c:\\Users\\faane\\Documents\\Arduino\\raygun\\main.ino" 2
# 3 "c:\\Users\\faane\\Documents\\Arduino\\raygun\\main.ino" 2





///------Define inputs -------\\


//#define board_PIN 16 // boards installed Neopixel. apearently it is pin 16, NOT 27! not that it
// matters, ive had zero success making it work


Adafruit_NeoPixel pixel_Strip(6, 12 /* outputpin for Neopixel strip im using*/, ((3<<6) | (1<<4) | (0<<2) | (2)) /*|< Transmit as G,R,B,W*/ + 0x0000 /*|< 800 KHz data transmission*/);

///------Define Time -----\\//unsigned longs are suggested for time based function

unsigned long boardTime = 0; // total up time of the board
unsigned long frameTime = 10; // how long a frame should last, do i need this here?
unsigned long elapsed_time = 0;
uint8_t r = 0;
uint8_t g = 0;
uint8_t b = 0;
uint8_t w = 0;

void setup()
{
// Mostly needed for certain kinds of trinkets, no harm in leaving it in



        pixel_Strip.begin(); // REQUIRED Instantiate a neopixel list
}

void loop()
{

        if (elapsed_time >= frameTime) {
                elapsed_time = 0;
                pixel_Strip.fill(Adafruit_NeoPixel::Color(0, Adafruit_NeoPixel::sine8(g++), 0, 0),
                                 0, 6);
                pixel_Strip.show();
                // for (int i = 0; i < NUMPIXELS; i++) {
                //         pixel_Strip.setPixelColor(i, 0, Adafruit_NeoPixel::sine8(g++), 0, 0);
                //         pixel_Strip.show();
                // }
        }
}
