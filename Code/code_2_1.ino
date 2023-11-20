#include <FastLED.h>

#define TOTAL_LEDS 49
#define FADE_EFFECT_DELAY 70 // Adjust this delay as needed

#define DATA_PIN 3            // Digital pin connected to the LED
#define CENTER_BRIGHTNESS 255 // Maximum brightness for center LEDs
#define CORNER_BRIGHTNESS 5   // Maximum brightness for corner LEDs

CRGB leds[TOTAL_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, TOTAL_LEDS);
  FastLED.show(); // Initialize LEDs
}

void loop() {
  // Fade in from the left
  for (int ledIndex = 0; ledIndex < TOTAL_LEDS; ledIndex++) {
    int center = TOTAL_LEDS / 2;
    int distanceToCenter = abs(center - ledIndex);
    int maxBrightness =
        CENTER_BRIGHTNESS -
        (distanceToCenter * (CENTER_BRIGHTNESS - CORNER_BRIGHTNESS) / center);

    leds[ledIndex] = CRGB(maxBrightness, maxBrightness, maxBrightness);

    FastLED.show();
    delay(FADE_EFFECT_DELAY);
  }

  // Fade out to the right
  for (int ledIndex = TOTAL_LEDS - 1; ledIndex >= 0; ledIndex--) {
    int center = TOTAL_LEDS / 2;
    int distanceToCenter = abs(center - ledIndex);
    int maxBrightness =
        CENTER_BRIGHTNESS -
        (distanceToCenter * (CENTER_BRIGHTNESS - CORNER_BRIGHTNESS) / center);

    leds[ledIndex] = CRGB(maxBrightness, maxBrightness, maxBrightness);

    FastLED.show();
    delay(FADE_EFFECT_DELAY);
  }
}
