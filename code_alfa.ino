#include <FastLED.h>

#define DATA_PIN 5            // Digital pin connected to the LED
#define NUM_LEDS 20           // Number of LEDs
#define FADE_EFFECT_DELAY 200 // Adjust this delay as needed
#define FADE_EFFECT_STEP 10   // Adjust this step as needed

CRGB leds[NUM_LEDS];
int led_brightness[NUM_LEDS];

void setup() {
  setBrightnessArray();
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.show(); // Initialize LEDs
}

void loop() {
  for (int ledIndex = 0; ledIndex < NUM_LEDS; ledIndex++) {
    // Set the brightness of the current LED
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

  // Reset brightness array for the next iteration
  setBrightnessArray();
}

void setBrightnessArray() {
  for (int i = 0; i < NUM_LEDS; i++) {
    led_brightness[i] = 0;
  }
}
