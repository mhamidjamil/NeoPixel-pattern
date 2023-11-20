#include <FastLED.h>

#define TOTAL_LEDS 49
#define CENTER_BRIGHTNESS 255 // Maximum brightness for center LEDs
#define CORNER_BRIGHTNESS 5   // Maximum brightness for corner LEDs

int fadeEffectDelay = 70;  // Default delay
int fadeEffectSpeed = 100; // Default speed

#define DATA_PIN 3 // Digital pin connected to the LED

CRGB leds[TOTAL_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, TOTAL_LEDS);
  FastLED.show(); // Initialize LEDs
}

void loop() {
  // User-adjustable delay
  delay(fadeEffectDelay);

  // Fade in from the left
  for (int ledIndex = 0; ledIndex < TOTAL_LEDS; ledIndex++) {
    int center = TOTAL_LEDS / 2;
    int distanceToCenter = abs(center - ledIndex);
    int maxBrightness =
        CENTER_BRIGHTNESS -
        (distanceToCenter * (CENTER_BRIGHTNESS - CORNER_BRIGHTNESS) / center);

    fadeEffect(ledIndex, maxBrightness);

    FastLED.show();
    delay(fadeEffectSpeed);
  }

  // User-adjustable delay
  delay(fadeEffectDelay);

  // Fade out to the right
  for (int ledIndex = TOTAL_LEDS - 1; ledIndex >= 0; ledIndex--) {
    int center = TOTAL_LEDS / 2;
    int distanceToCenter = abs(center - ledIndex);
    int maxBrightness =
        CENTER_BRIGHTNESS -
        (distanceToCenter * (CENTER_BRIGHTNESS - CORNER_BRIGHTNESS) / center);

    fadeEffect(ledIndex, maxBrightness);

    FastLED.show();
    delay(fadeEffectSpeed);
  }
}

// Function to handle serial input for adjusting parameters
void handleSerialInput() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    switch (command) {
    case 'd': // Adjust delay
      fadeEffectDelay = Serial.parseInt();
      break;
    case 's': // Adjust speed
      fadeEffectSpeed = Serial.parseInt();
      break;
    }
  }
}

// Function to smoothly fade LED brightness
void fadeEffect(int ledIndex, int maxBrightness) {
  for (int brightness = 0; brightness <= maxBrightness; brightness++) {
    leds[ledIndex] = CRGB(brightness, brightness, brightness);
  }
}
