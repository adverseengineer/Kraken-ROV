//Nick Sells, 2023
//ETSU Underwater Robotics

#include <Arduino.h>

#include "lights.h"
#include "control.h"
#include "util.h"

//TODO: edit these when the lights are added
const static uint8_t PINS[2] = {0, 0};

static bool lit;

void Lights::Init(void) noexcept {
  Serial.print("Initializing Lights... ");

  lit = true;

  for(auto i = 0; i < 2; i++) {
    pinMode(PINS[i], OUTPUT);
    digitalWrite(PINS[i], lit);
  }

  Serial.println("Lights Initialized!");
}

void Lights::On(void) noexcept {
  lit = true;
  for(auto i = 0; i < 2; i++)
    digitalWrite(PINS[i], lit);
}

void Lights::Off(void) noexcept {
  lit = false;
  for(auto i = 0; i < 2; i++)
    digitalWrite(PINS[i], lit);
}

void Lights::Update(void) noexcept {
  if(unlikely(Control::GetButtonHit(A))) {
    if(!lit) On();
    else Off();
  }
}
