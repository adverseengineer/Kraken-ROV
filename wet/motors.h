//Nick Sells, 2023
//ETSU Underwater Robotics

#ifndef MOTORS_H
#define MOTORS_H

namespace Motors {

  extern void Init(void) noexcept;
  extern void Update(void) noexcept;
  extern void GetSignals(uint16_t*) noexcept;
}

#endif