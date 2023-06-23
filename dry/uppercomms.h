//Nick Sells, 2023
//ETSU Underwater Robotics

#ifndef UPPERCOMMS_H
#define UPPERCOMMS_H

#define NUM_SIGS 10

namespace UpperComms {

  extern uint16_t signals[NUM_SIGS];

  extern void Init(void) noexcept;
  extern void Update(void) noexcept;
}

#endif
