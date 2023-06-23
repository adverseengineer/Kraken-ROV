//Nick Sells, 2023
//ETSU Underwater Robotics

#ifndef GRIPS_H
#define GRIPS_H

#define INDEX_GRIPL 6
#define INDEX_GRIPR 7

#include "uppercomms.h"

namespace Grips {

  //positions for the grip servos
  const static uint16_t GRIP_OPEN = 1900;
  const static uint16_t GRIP_CLOSED = 1200;

  //amounts to increment the grip servo positions by
  static constexpr uint16_t GRIP_OPEN_SPEED = 14;
  static constexpr uint16_t GRIP_CLOSE_SPEED = 14;

  static inline void Update(void) noexcept {
    //if the left trigger is held, but the grip is not yet fully closed
    if(Controls::ButtonHeld(PSB_L2) > 0) {
      if(UpperComms::signals[INDEX_GRIPL] > GRIP_CLOSED)
        UpperComms::signals[INDEX_GRIPL] -= GRIP_CLOSE_SPEED;
    }
    //if the left bumper is held, but the grip is not yet fully open
    else if(Controls::ButtonHeld(PSB_L1)) {
      if(UpperComms::signals[INDEX_GRIPL] < GRIP_OPEN)
        UpperComms::signals[INDEX_GRIPL] += GRIP_OPEN_SPEED;
    }

    //do all the same again but for right
    if(Controls::ButtonHeld(PSB_R2) > 0) {
      if(UpperComms::signals[INDEX_GRIPR] > GRIP_CLOSED)
        UpperComms::signals[INDEX_GRIPR] -= GRIP_CLOSE_SPEED;
    }
    else if(Controls::ButtonHeld(PSB_R1)) {
      if(UpperComms::signals[INDEX_GRIPR] < GRIP_OPEN)
        UpperComms::signals[INDEX_GRIPR] += GRIP_OPEN_SPEED;
    }
  }

}

#endif