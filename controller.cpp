#include "controller.h"
#include "events.h"

// ----- Controller owned state -----

static Track tracks[NUM_TRACKS];
static Mode current_mode;
static uint32_t last_tick_ms; // Used for sleeping

// ----- Controlller functions -----

void volume_encoder(Mode mode, Event current_event, Track tracks[]) {



}

Mode mode_recording(Mode mode, Event current_event, Track tracks[]) {
  if (current_event.type == EVT_BUTTON_PRESSED) {
    mode = TRACK_RECORDING;
    Serial.printf("Mode: Recording\n");
  }

  else if (current_event.type == EVT_MODE_CHANGED) {
    mode = TRACK_PLAYING;
    Serial.printf("Mode: Switching to Playing due to Button Press\n");

  }
  else if (current_event.type == EVT_MIC_TIMEOUT) {
    mode = TRACK_PLAYING;
    Serial.printf("Mode: Switching to Playing due to MIC TIMEOUT\n");

  }

  return mode;

} 

Mode mode_playing(Mode current, Event current_event, Track tracks[]) {
  if (current_event.type == EVT_BUTTON_PRESSED) {
    mode = TRACK_PLAYING;
    Serial.printf("Mode: Playing\n");
  }

  else if (current_event.type == EVT_MODE_CHANGED) {
    mode = TRACK_RECORDING;
    Serial.printf("Mode: Switching to Recording\n");
  }

  return mode;
}

Mode mode_sd_occupied(Mode current, Event current_event, Track tracks[]) {
  Serial.printf("Mode: SD Occupied\n");
  if (current_event.type == EVT_SD_READ) {
    // pass Track Array
  }
  if (current_event.type == EVT_SD_DONE) {
    // will just return when done
  }
  return mode;
}

void controller_debug() {
  Event e;
  while (event_queue_pop(&e)) {
    Serial.printf("Event: type %d, id %u, value %d\n", e.type, e.id, e.value);
    // begin
    if (e.type == EVT_ENCODER) {
      volume_encoder(current_mode, &e, tracks);
      Serial.printf("Volume_Encoder\n");
    } 
    else if (current_mode == TRACK_RECORDING) {
      current_mode = mode_recording(current_mode, &e, tracks);
      Serial.printf("Mode: Recording\n");
    }

    else if (current_mode == TRACK_PLAYING)  {
      current_mode = mode_playing(current_mode, &e, tracks);
    }

    if (current_mode == SD_OCCUPIED) {
      current_mode = mode_sd_occupied(current_mode, &e, tracks);
    }
  // end
  }
}

void controller_init() {
  // Various init calls from drivers, other subteams

  for (int i = 0; i < NUM_TRACKS; i++) {
    tracks[i].id = i;
    tracks[i].instrument = (InstrumentType)i;
    tracks[i].state = TRACK_EMPTY;
    // Clear leds
  }

  // Call driver to set current_mode

  last_tick_ms = millis();
}

void controller_loop() {
  // DEBUG:
  controller_debug();

  // Poll inputs manager

  // Dequeue events and handle them

  // Update timeouts
}
