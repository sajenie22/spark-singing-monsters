#include "leds.h"
#include <FastLED.h>

// Need info from controller

static Track tracks[NUM_TRACKS];
static CRGB leds[NUM_LEDS];

void leds_init() {
  FastLED.addLeds<WS2812B, PIN_LED_TRACK, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(LED_BRIGHTNESS);
  FastLED.clear();
  FastLED.show();
}

void leds_loop() {
  FastLED.clear();

  // Assume we magically get the track state from controller for now
  // Read new track states and progress from mailbox?
  // tracks = _;

  // TODO: Change colour/turn off cursor for different states (need to restructure this)
  for (int i = 0; i < NUM_TRACKS; i++) {
    CRGB colour;
    switch (tracks[i].state) {
      case TRACK_EMPTY: colour = CRGB::Black; break;
      case TRACK_RECORDING: colour = CRGB::Blue; break;
      case TRACK_PLAYING: colour = CRGB::Green; break;
      case TRACK_MUTED: colour = CRGB::Red; break;
      default: colour = CRGB::Magenta; // error state
    }
    leds[i * LEDS_PER_TRACK] = colour;

    uint32_t cursor = tracks[i].cursor % SAMPLES_PER_TRACK; // Should never be needed, prevents silent memory corruption
    uint8_t pos = (cursor * (LEDS_PER_TRACK - 1)) / SAMPLES_PER_TRACK; // Scale to number of cursor leds
    leds[i * LEDS_PER_TRACK + (pos + 1)] = CRGB::White; // Offset by 1 to skip button LED
  }

  FastLED.show();
}
