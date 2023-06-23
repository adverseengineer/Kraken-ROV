//Nick Sells, 2023
//ETSU Underwater Robotics

#ifndef LOWERCOMMS_H
#define LOWERCOMMS_H

#define NUM_SIGS 10

namespace LowerComms {

  extern uint16_t signals[NUM_SIGS];

  extern void Init(void) noexcept;
  extern void Update(void) noexcept;
}

#endif
