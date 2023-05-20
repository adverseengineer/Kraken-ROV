//Nick Sells, 2023
//ETSU Underwater Robotics

#ifndef CONTROL_H
#define CONTROL_H

#define USE360

#ifdef USE360
#include <XBOXUSB.h>
#else
#include <XBOXONE.h>
#endif

namespace Control {

  //any axis reading less than this amount is ignored to mitigate controller drift
  const int16_t DEADZONE = 6553; //0.2

  //the minimum value that can be reported by an analog axis
  const int16_t HAT_MIN = -32768;
  //the maximum value that can be reported by an analog axis
  const int16_t HAT_MAX = 32767;

  //the minimum value that can be reported by an analog trigger
  const uint8_t TRIG_MIN = 0;
  //the maximum value that can be reported by an analog trigger
  const uint8_t TRIG_MAX = 255;

  extern void Init(void) noexcept; 
  extern void Update(void) noexcept;
  extern bool IsAvailable(void) noexcept;

  extern uint8_t GetButtonHit(ButtonEnum btn) noexcept;
  extern uint8_t GetButtonHeld(ButtonEnum btn) noexcept;
  extern int16_t GetHat(AnalogHatEnum hat) noexcept;
}

#endif
