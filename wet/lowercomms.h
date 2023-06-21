//Nick Sells, 2023
//ETSU Underwater Robotics

#ifndef LOWERCOMMS_H
#define LOWERCOMMS_H

#include <PS2X_lib.h>

namespace LowerComms {

  extern void Init(void) noexcept;
  extern void Update(void) noexcept;
  extern void GiveSignals(uint16_t*) noexcept;
  
  void PrintSignals(void) noexcept;
}


#endif
