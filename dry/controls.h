//Nick Sells, 2023
//ETSU Underwater Robotics

#ifndef CONTROLS_H
#define CONTROLS_H

#include <stdint.h>
#include <PS2X_lib.h>

namespace Controls {

  static const int8_t ANALOG_MIN = -127;
  static const int8_t ANALOG_MAX = 127;

  extern void Init(void) noexcept;
  extern void Update(void) noexcept;

  extern bool ButtonHeld(unsigned int button) noexcept;
  extern bool ButtonPressed(unsigned int button) noexcept;
  extern bool ButtonReleased(unsigned int button) noexcept;
  extern int8_t Analog(unsigned int axis) noexcept;
}

enum ControllerStatus : uint8_t {
  OK = 0,
  NOTFOUND = 1,
  UNRESPONSIVE = 2,
  NOANALOG = 3
};

enum ControllerType : uint8_t {
  UNKNOWN = 0,
  DUALSHOCK = 1,
  GUITARHERO = 2,
  WIRELESSDUALSHOCK = 3
};

#endif
