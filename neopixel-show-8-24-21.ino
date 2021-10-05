// A basic everyday NeoPixel strip test program.

// NEOPIXEL BEST PRACTICES for most reliable operation:
// - Add 1000 uF CAPACITOR between NeoPixel strip's + and - connections.
// - MINIMIZE WIRING LENGTH between microcontroller board and first pixel.
// - NeoPixel strip's DATA-IN should pass through a 300-500 OHM RESISTOR.
// - AVOID connecting NeoPixels on a LIVE CIRCUIT. If you must, ALWAYS
//   connect GROUND (-) first, then +, then data.
// - When using a 3.3V microcontroller with a 5V-powered NeoPixel strip,
//   a LOGIC-LEVEL CONVERTER on the data line is STRONGLY RECOMMENDED.
// (Skipping these may work OK on your workbench but can fail in the field)

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    6

// How many NeoPixel strands?
#define STRANDS 2
// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 30 * STRANDS

#define BLACK = strip.Color(0,0,0);
#define BLUE = strip.Color(0,0,225);
#define BROWN = strip.Color(175,130,100);
#define CYAN = strip.Color(0,255,255);
#define GREEN = strip.Color(30, 220,60);
#define GOLD = strip.Color(255,160,0);
#define LIGHTBLUE = strip.Color(135,206,250);
#define LIGHTGREEN = strip.Color(0,225,50);
#define LIGHTPURPLE = strip.Color(230,100,250);
#define MAGENTA = strip.Color(255,0,255);
#define ORANGE = strip.Color(255,130,0);
#define PINK = strip.Color(255,50,150);
#define PURPLE = strip.Color(160,0,255);
#define RED = strip.Color(255,0,0);
#define SILVER = strip.Color(225,225,230);
#define WHITE = strip.Color(255,255,255);
#define YELLOW = strip.Color(255,255,0);


// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)


// setup() function -- runs once at startup --------------------------------

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
}


// loop() function -- runs repeatedly as long as board is on ---------------

void loop() {
  // Fill along the length of the strip in various colors...
  colorWipe(RED, 5);
  revColorWipe(ORANGE, 5);
  colorWipe(YELLOW, 5);
  revColorWipe(GREEN, 5);
  colorWipe(BLUE, 5);
  revColorWipe(PURPLE, 5);
  colorWipe(PINK, 5);
  revColorWipe(BROWN, 5);
  colorWipe(GOLD, 5);
  revColorWipe(CYAN, 5);
  colorWipe(MAGENTA, 5);
  revColorWipe(SILVER, 5);
  colorWipe(LIGHTGREEN, 5);
  revColorWipe(LIGHTBLUE, 5);
  colorWipe(LIGHTPURPLE, 5);
  revColorWipe(BLACK, 5);

  // Do a theater marquee effect in various colors...
  //theaterChase(strip.Color(127, 127, 127), 50); // White, half brightness
  //theaterChase(strip.Color(127,   0,   0), 50); // Red, half brightness
  theaterChase(strip.Color(  0,   0, 127), 50); // Blue, half brightness

  rainbow(10);             // Flowing rainbow cycle along the whole strip
  //theaterChaseRainbow(50); // Rainbow-enhanced theaterChase variant
}


// Some functions of our own for creating animated effects -----------------

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

void revColorWipe(uint32_t color, int wait) {
  for(int i=strip.numPixels()-1; i>=0; i--) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this outer loop:
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}

void flashBetween(uint32_t color1, uint32_t color2, int wait) {
  for(int i = 0; i<10; i++){
    for(int z = 0; z<strip.numPixels(); z++){
      strip.setPixelColor(z,color1);
    }
    strip.show();
    delay(wait);
    for(int j = 0; j<strip.numPixels(); j++){
      strip.setPixelColor(j,color2);
    }
    strip.show();
    delay(wait);
  }
}

void onePixel(uint32_t color1, int wait){
  for(int i = 0; i<strip.numPixels(); i++){
    strip.clear();
    strip.setPixelColor(i,color1);
    strip.show();
    delay(wait);
  }
  for (int i = strip.numPixels(); i > 0; i--) {
    strip.clear();
    strip.setPixelColor(i,color1);
    strip.show();
    delay(wait);
  }
}

void twoPixels(uint32_t color1, uint32_t color2, int wait){
  for(int i = 0; i<strip.numPixels(); i++){
    strip.clear();
    strip.setPixelColor(i,color1);
    strip.setPixelColor((strip.numPixels()-1)-i, color2);
    strip.show();
    delay(wait);
  }
}

//flashing siren light
void policeChase(uint32_t color1, uint32_t color2, int wait) {
  for (int i = 1; i < strip.numPixels(); i++) {
    if (i%2 == 0) {
      strip.clear();
      strip.setPixelColor(i - 1, color1);
    }
    else {
      strip.clear();
      strip.setPixelColor(i + 1, color2);
    }
    strip.show();
    delay(wait);
  }
}

void reversePoliceChase(uint32_t color1, uint32_t color2, int wait) {
  for (int i = strip.numPixels(); i > 0; i--) {
    if (i%2 == 0) {
      strip.clear();
      strip.setPixelColor(i + 1, color1);
      strip.show();
      delay(wait);
    }
    else {
      strip.clear();
      strip.setPixelColor(i - 1, color2);
      strip.show();
      delay(wait);
    }
  }
}
