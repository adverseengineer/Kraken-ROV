
#include <Arduino.h>
#include <Servo.h>

#include "grips.h"
#include "defs.h"

namespace Grips {

  const uint16_t OPEN = 1900;
  const uint16_t CLOSED = 1100;

  Servo gripL;
  Servo gripR;

  //initialize the grippers
  void Init(void) noexcept {
    Serial.print("Initializing Grippers... ");
    
    pinMode(Defs::Pins::GRIPL, OUTPUT);
    pinMode(Defs::Pins::GRIPR, OUTPUT);
    gripL.attach(Defs::Pins::GRIPL, CLOSED, OPEN);
    gripR.attach(Defs::Pins::GRIPR, CLOSED, OPEN);

    Serial.println("Grippers Initialized!");
  }
}