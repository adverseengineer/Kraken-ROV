//Nick Sells, 2023
//ETSU Underwater Robotics

#ifndef UPPERCOMMS_H
#define UPPERCOMMS_H

namespace UpperComms {

  extern void Init(void) noexcept;
  extern void Update(void) noexcept;
  extern void GetSignals(uint16_t*) noexcept;

  extern void PrintSignals(void) noexcept;
}

#endif
