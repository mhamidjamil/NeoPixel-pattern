#include <FastLED.h>

#define TOTAL_LEDS 20
#define FADE_EFFECT_DELAY 200 // Adjust this delay as needed

#define NUM_LEDS TOTAL_LEDS + 5 // Number of LEDs
#define DATA_PIN 5              // Digital pin connected to the LED
#define FADE_EFFECT_STEP 10     // Adjust this step as needed

CRGB leds[NUM_LEDS];
int led_brightness[NUM_LEDS];

void setup() {
  // setBrightnessArray();
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.show(); // Initialize LEDs
}

void loop() {
  // Fade in
  for (int ledIndex = 0; ledIndex < NUM_LEDS; ledIndex++) {
    // Increment the brightness of the current LED
    led_brightness[ledIndex] += 255 / FADE_EFFECT_STEP;
    leds[ledIndex] = CRGB(led_brightness[ledIndex], led_brightness[ledIndex],
                          led_brightness[ledIndex]);

    // Increment the brightness of the previous LEDs
    for (int prevIndex = ledIndex - 1;
         prevIndex >= 0 && prevIndex > ledIndex - FADE_EFFECT_STEP;
         prevIndex--) {
      led_brightness[prevIndex] += 255 / FADE_EFFECT_STEP;
      leds[prevIndex] =
          CRGB(led_brightness[prevIndex], led_brightness[prevIndex],
               led_brightness[prevIndex]);
    }

    FastLED.show();
    delay(FADE_EFFECT_DELAY);
  }

  // Fade out
  for (int ledIndex = NUM_LEDS - 1; ledIndex >= 0; ledIndex--) {
    // Decrement the brightness of the current LED
    led_brightness[ledIndex] -= 255 / FADE_EFFECT_STEP;
    leds[ledIndex] = CRGB(led_brightness[ledIndex], led_brightness[ledIndex],
                          led_brightness[ledIndex]);

    // Decrement the brightness of the previous LEDs
    for (int prevIndex = ledIndex - 1;
         prevIndex >= 0 && prevIndex > ledIndex - FADE_EFFECT_STEP;
         prevIndex--) {
      led_brightness[prevIndex] -= 255 / FADE_EFFECT_STEP;
      leds[prevIndex] =
          CRGB(led_brightness[prevIndex], led_brightness[prevIndex],
               led_brightness[prevIndex]);
    }

    FastLED.show();
    delay(FADE_EFFECT_DELAY);
  }
}
