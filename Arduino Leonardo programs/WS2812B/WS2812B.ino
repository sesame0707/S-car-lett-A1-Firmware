#include <FastLED.h>

#define LED_PIN     7
#define NUM_LEDS    60

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(31, 31, 31);
  }
  FastLED.show();
}

void loop() {

}