#include <FastLED.h>

#define TOTAL_LEDS 50
#define FADE_EFFECT_DELAY 70 // Adjust this delay as needed

#define NUM_LEDS TOTAL_LEDS   // Number of LEDs
#define DATA_PIN 3            // Digital pin connected to the LED
#define CENTER_BRIGHTNESS 255 // Maximum brightness for center LEDs
#define CORNER_BRIGHTNESS 10  // Maximum brightness for corner LEDs

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.show(); // Initialize LEDs
}

void loop() {
  // Fade in
  for (int ledIndex = 0; ledIndex < TOTAL_LEDS / 2; ledIndex++) {
    int center = TOTAL_LEDS / 2;
    int distanceToCenter = abs(center - ledIndex);
    int maxBrightness =
        CENTER_BRIGHTNESS -
        (distanceToCenter * (CENTER_BRIGHTNESS - CORNER_BRIGHTNESS) / center);

    leds[center + distanceToCenter] =
        CRGB(maxBrightness, maxBrightness, maxBrightness);
    leds[center - distanceToCenter] =
        CRGB(maxBrightness, maxBrightness, maxBrightness);

    FastLED.show();
    delay(FADE_EFFECT_DELAY);
  }

  // Fade out
  for (int ledIndex = TOTAL_LEDS / 2; ledIndex < TOTAL_LEDS; ledIndex++) {
    int center = TOTAL_LEDS / 2;
    int distanceToCenter = abs(center - ledIndex);
    int maxBrightness =
        CENTER_BRIGHTNESS -
        (distanceToCenter * (CENTER_BRIGHTNESS - CORNER_BRIGHTNESS) / center);

    leds[center + distanceToCenter] =
        CRGB(maxBrightness, maxBrightness, maxBrightness);
    leds[center - distanceToCenter] =
        CRGB(maxBrightness, maxBrightness, maxBrightness);

    FastLED.show();
    delay(FADE_EFFECT_DELAY);
  }
}
