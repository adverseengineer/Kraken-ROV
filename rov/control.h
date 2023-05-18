
#ifndef CONTROL_H
#define CONTROL_H

#define USE360

#ifdef USE360
#include <XBOXUSB.h>
#else
#include <XBOXONE.h>
#endif

namespace Control {

  const int32_t HAT_MIN = -65536;
  const int32_t HAT_MAX = 65535;

  const uint8_t TRIG_MIN = 0;
  const uint8_t TRIG_MAX = 255;

  extern void Init(void) noexcept; 
  extern void Update(void) noexcept;
  extern bool IsAvailable(void) noexcept;

  extern uint8_t GetButtonHit(ButtonEnum btn) noexcept;
  extern uint8_t GetButtonHeld(ButtonEnum btn) noexcept;
  extern int32_t GetHat(AnalogHatEnum hat) noexcept;
}

#endif
