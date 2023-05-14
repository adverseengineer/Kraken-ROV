
#ifndef CONTROL_H
#define CONTROL_H

namespace Control {

  struct Joystick {
    int32_t x;
    int32_t y;
  };

  const int32_t HAT_MIN = -65536;
  const int32_t HAT_MAX = 65535;

  extern bool A;
  extern bool B;
  extern bool X;
  extern bool Y;
  extern bool LB;
  extern bool RB;
  extern bool L3;
  extern bool R3;
  extern bool Up;
  extern bool Down;
  extern bool Left;
  extern bool Right;
  extern bool Xbox;
  extern bool Start;
  extern bool Select;
  extern uint8_t LT;
  extern uint8_t RT;
  extern Joystick JoyL;
  extern Joystick JoyR;

  extern void Init(void) noexcept; 
  extern void Update(void) noexcept;
  extern bool IsAvailable(void) noexcept;
}

#endif
