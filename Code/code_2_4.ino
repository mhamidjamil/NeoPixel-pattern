#include <FastLED.h>

#define TOTAL_LEDS 144
#define CENTER_BRIGHTNESS 255 // Maximum brightness for center LEDs
#define CORNER_BRIGHTNESS 5   // Maximum brightness for corner LEDs

int fadeEffectDelay = 70; // Default delay
int fadeEffectSpeed = 10; // Default speed

#define DATA_PIN 5 // Digital pin connected to the LED

CRGB leds[TOTAL_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, TOTAL_LEDS);
  FastLED.show(); // Initialize LEDs
}

void loop() {
  unsigned long startTime = millis();

  // Fade in from the left
  for (int ledIndex = 0; ledIndex < TOTAL_LEDS; ledIndex++) {
    int center = TOTAL_LEDS / 2;
    int distanceToCenter = abs(center - ledIndex);
    int targetBrightness =
        CENTER_BRIGHTNESS -
        (distanceToCenter * (CENTER_BRIGHTNESS - CORNER_BRIGHTNESS) / center);

    fadeEffect(ledIndex, targetBrightness);

    FastLED.show();
    delay(fadeEffectSpeed);
  }

  // Fade out from the right
  for (int ledIndex = TOTAL_LEDS - 1; ledIndex >= 0; ledIndex--) {
    int center = TOTAL_LEDS / 2;
    int distanceToCenter = abs(center - ledIndex);
    int targetBrightness =
        CENTER_BRIGHTNESS -
        (distanceToCenter * (CENTER_BRIGHTNESS - CORNER_BRIGHTNESS) / center);

    fadeOut(ledIndex, targetBrightness);

    FastLED.show();
    delay(fadeEffectSpeed);
  }

  unsigned long elapsedTime = millis() - startTime;

  // Ensure a constant delay between LED activations
  if (elapsedTime < fadeEffectDelay) {
    delay(fadeEffectDelay - elapsedTime);
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

// Function to smoothly fade LED brightness in
void fadeEffect(int ledIndex, int targetBrightness) {
  int currentBrightness = 0;

  while (currentBrightness <= targetBrightness) {
    leds[ledIndex] =
        CRGB(currentBrightness, currentBrightness, currentBrightness);
    FastLED.show();
    currentBrightness++;
  }
}

// Function to smoothly fade LED brightness out
void fadeOut(int ledIndex, int targetBrightness) {
  int currentBrightness = targetBrightness;

  while (currentBrightness >= 0) {
    leds[ledIndex] =
        CRGB(currentBrightness, currentBrightness, currentBrightness);
    FastLED.show();
    currentBrightness--;
  }
}
