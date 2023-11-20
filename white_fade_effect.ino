#include <FastLED.h>

#define DATA_PIN 5  // Digital pin connected to the LED
#define NUM_LEDS 20 // Number of LEDs

CRGB leds[NUM_LEDS];
int led_brightness[NUM_LEDS];
#define FADE_EFFECT_DELAY 200 // Adjust this delay as needed
#define FADE_EFFECT_STEP 10   // Adjust this step as needed

void setup() {
  setBrightnessArray();
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.show(); // Initialize LEDs
}

void loop() {
  int brightness = 0;

  for (int ledIndex = 0; ledIndex < NUM_LEDS; ledIndex++) {
    leds[ledIndex] = CRGB((255 / FADE_EFFECT_STEP), (255 / FADE_EFFECT_STEP),
                          (255 / FADE_EFFECT_STEP));
    increasePreviousLEDsBrightness(ledIndex);
    delay(FADE_EFFECT_DELAY);
    FastLED.show();
  }
  //   for (int ledIndex = NUM_LEDS - 1; ledIndex >= 0; ledIndex--) {
  //     leds[ledIndex] = CRGB(255, 255, 255);
  //     decreasePreviousLEDsBrightness(ledIndex);
  //     delay(FADE_EFFECT_DELAY);
  //     FastLED.show();
  //   }
}

void setBrightnessArray() {
  for (int i = 0; i < NUM_LEDS; i++) {
    led_brightness[i] = 0;
  }
}

void increasePreviousLEDsBrightness(int index) {
  for (int i = FADE_EFFECT_STEP; i > 0; index--, i--) {
    if (index - 1 > 0) {
      led_brightness[index - 1] += 255 / FADE_EFFECT_STEP;
      leds[index - 1] =
          CRGB(led_brightness[index - 1], led_brightness[index - 1],
               led_brightness[index - 1]);
    } else {
      i = 0;
    }
  }
}

void decreasePreviousLEDsBrightness(int index) {
  for (int i = FADE_EFFECT_STEP; i > 0; i--) {
    if (index - 1) {
      led_brightness[index - 1] -= 255 / FADE_EFFECT_STEP;
      leds[index - 1] =
          CRGB(led_brightness[index - 1], led_brightness[index - 1],
               led_brightness[index - 1]);
    } else {
      i = 0;
    }
  }
}