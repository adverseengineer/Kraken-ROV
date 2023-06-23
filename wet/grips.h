//Nick Sells, 2023
//ETSU Underwater Robotics

#ifndef GRIPS_H
#define GRIPS_H

#define INDEX_GRIPL 6
#define INDEX_GRIPR 7

#include <Servo.h>
#include "lowercomms.h"

namespace Grips {

  static constexpr uint8_t PIN_GRIPL = 8;
  static constexpr uint8_t PIN_GRIPR = 9;

  static Servo gripL;
  static Servo gripR;

  //initialize our grippers
  static inline void Init(void) noexcept {
    pinMode(PIN_GRIPL, OUTPUT);
    pinMode(PIN_GRIPR, OUTPUT);
    gripL.attach(PIN_GRIPL);
    gripR.attach(PIN_GRIPR);
  }

  //update the state of our grippers
  static inline void Update(void) noexcept {
    gripL.writeMicroseconds(LowerComms::signals[INDEX_GRIPL]);
    gripR.writeMicroseconds(LowerComms::signals[INDEX_GRIPR]);
  }
}

#endif
