
#include <Arduino.h>
#include <Servo.h>

#include "grips.h"
#include "control.h"
#include "defs.h"

namespace Grips {

  const uint16_t OPEN = 1900;
  const uint16_t CLOSED = 1200;

  const uint16_t OPEN_SPEED = 12;
  const uint16_t CLOSE_SPEED = 12;

  Servo gripL;
  Servo gripR;

  uint16_t gripPosL = OPEN;
  uint16_t gripPosR = OPEN;

  //initialize the grippers
  void Init(void) noexcept {
    Serial.print("Initializing Grippers... ");
    
    pinMode(Defs::Pins::GRIPL, OUTPUT);
    pinMode(Defs::Pins::GRIPR, OUTPUT);
    gripL.attach(Defs::Pins::GRIPL, CLOSED, OPEN);
    gripR.attach(Defs::Pins::GRIPR, CLOSED, OPEN);
    gripL.writeMicroseconds(gripPosL);
    gripR.writeMicroseconds(gripPosR);

    Serial.println("Grippers Initialized!");
  }

  void Update(void) noexcept {

    //if the left trigger is held, but the grip is not yet fully closed
    if(Control::GetButtonHeld(LT) > 0) {
      if(gripPosL > CLOSED) {
        gripPosL -= CLOSE_SPEED;
        gripL.writeMicroseconds(gripPosL);
      }
    }
    //if the left bumper is held, but the grip is not yet fully open
    else if(Control::GetButtonHeld(LB)) {
      if(gripPosL < OPEN) {
        gripPosL += OPEN_SPEED;
        gripL.writeMicroseconds(gripPosL);
      }
    }

    //do all the same again but for right
    if(Control::GetButtonHeld(RT) > 0) {
      if(gripPosR > CLOSED) {
        gripPosR -= CLOSE_SPEED;
        gripR.writeMicroseconds(gripPosR);
      }
    }
    else if(Control::GetButtonHeld(RB)) {
      if(gripPosR < OPEN) {
        gripPosR += OPEN_SPEED;
        gripR.writeMicroseconds(gripPosR);
      }
    }

  }
}
