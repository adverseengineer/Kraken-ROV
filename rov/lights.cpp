//Nick Sells, 2023
//ETSU Underwater Robotics

#include <Arduino.h>

#include "lights.h"
#include "control.h"

namespace Lights {

  //TODO: edit these when the lights are added
  const uint8_t PINS[2] = {0, 0};

  bool lit;

  void Init(void) noexcept {
    Serial.print("Initializing Lights... ");

    lit = true;

    for(auto i = 0; i < 2; i++) {
      pinMode(PINS[i], OUTPUT);
      digitalWrite(PINS[i], lit);
    }

    Serial.println("Lights Initialized!");
  }

  void On(void) noexcept {
    lit = true;
    for(auto i = 0; i < 2; i++)
      digitalWrite(PINS[i], lit);
  }

  void Off(void) noexcept {
    lit = false;
    for(auto i = 0; i < 2; i++)
      digitalWrite(PINS[i], lit);
  }

  void Update(void) noexcept {
    if(Control::GetButtonHit(A)) {
      if(!lit) On();
      else Off();
    }
  }
}
