#define FASTLED_ALLOW_INTERRUPTS 0
#include "FastLED.h"


// How many leds in your strip?
#define NUM_LEDS 30

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
//#define CLOCK_PIN 13
#define DATA_PIN 4
#define SWITCH_PIN 3

int rearLights[15] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
int frontLights[15] = {15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29};
const int EFFECT_BLINK = 0;
const int EFFECT_SPIN = 1;
const int EFFECT_KITT = 2;
int currentEffect = EFFECT_KITT;
unsigned long lastInterrupt;
 
// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() { 
    Serial.begin(9600);
    pinMode(SWITCH_PIN,  INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(SWITCH_PIN), toggle, FALLING);
      
      // Uncomment/edit one of the following lines for your leds arrangement.
      // FastLED.addLeds<TM1803, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<TM1804, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<TM1809, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
       FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  	  // FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
      // FastLED.addLeds<APA104, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<UCS1903, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<UCS1903B, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<GW6205, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<GW6205_400, DATA_PIN, RGB>(leds, NUM_LEDS);
      
      // FastLED.addLeds<WS2801, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<SM16716, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<LPD8806, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<P9813, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<APA102, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<DOTSTAR, RGB>(leds, NUM_LEDS);

      // FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<SM16716, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<LPD8806, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<DOTSTAR, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
}

void loop() { 
  switch(currentEffect) {
    case EFFECT_BLINK:
      Serial.println("BLINK");
      doBlink();
      break;
    case EFFECT_SPIN:
      Serial.println("SPIN");
      doSpin();
      break;
    case EFFECT_KITT:
      Serial.println("KITT");
      doKitt();
      break;
    default:
      Serial.println("DEFAULT");
      break;      
  }
}


void toggle() {
  if ((millis - lastInterrupt) > 300) {
    switch(currentEffect) {
      case EFFECT_BLINK:
        currentEffect = EFFECT_SPIN;
        break;
      case EFFECT_SPIN:
        currentEffect = EFFECT_KITT;
        break;
      case EFFECT_KITT:
        currentEffect = EFFECT_BLINK;
        break;
      default:
        break;
    }
    Serial.println(".");
  }
  Serial.print("|");
  lastInterrupt = millis();
  attachInterrupt(digitalPinToInterrupt(SWITCH_PIN), toggle, FALLING);
}

void doBlink() {
  while(currentEffect == EFFECT_BLINK) {
    // Turn the LED on, then pause
    for(int i = 0; i < 15; i++) {
      leds[rearLights[i]] = CRGB::Red;
    }
    for(int i = 0; i < 15; i++) {
      leds[frontLights[i]] = CRGB::White;
    }
    FastLED.show();
    //Serial.print(".");
    delay(100);
    Serial.print("B ");
  
    // Now turn the LED off, then pause
  for(int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Black;
    }
    FastLED.show();
    delay(400);
    attachInterrupt(digitalPinToInterrupt(SWITCH_PIN), toggle, FALLING);
  }
}

void doSpin() {
  int i = 0;
  while(currentEffect == EFFECT_SPIN) {
    for(int j = 0; j < NUM_LEDS; j++) {
      leds[j] = CRGB::Black;
    }
    //Serial.print(" ");
    //Serial.print(i);
    if(i < 14) {
      leds[i] = CRGB::Red;
      leds[i + 15] = CRGB::White;
      leds[++i] = CRGB::Red;
      leds[i + 15] = CRGB::White;
    } else if (i == 14) {
      leds[0] = CRGB::Red;
      leds[14] = CRGB::Red;
      leds[15] = CRGB::White;
      leds[29] = CRGB::White;
      i = 0;
    }
    FastLED.show();
    delay(20);
    attachInterrupt(digitalPinToInterrupt(SWITCH_PIN), toggle, FALLING);
  }
}

void doKitt() {
  int i = 0;
  int increment = 1;
  while(currentEffect == EFFECT_KITT) {
    for(int j = 0; j < NUM_LEDS; j++) {
      leds[j] = CRGB::Black;
    }
    //Serial.print(" ");
    //Serial.print(i);
    //Serial.println(i);
    leds[i] = CRGB::Red;
    leds[i + 15] = CRGB::White;
    leds[i + 1] = CRGB::Red;
    leds[i + 16] = CRGB::White;
    i += increment;
    if (i == 13) {
      increment = -1;
    } 
    if (i == 0) {
      increment = 1;
    }
    FastLED.show();
    delay(50);
    attachInterrupt(digitalPinToInterrupt(SWITCH_PIN), toggle, FALLING);
  }
}
