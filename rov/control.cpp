
#ifndef CONTROL_H
#define CONTROL_H

#include <SPI.h>
#include <XBOXUSB.h>

namespace Control {

  struct Joystick {
    int32_t x;
    int32_t y;
  };

  // static const int32_t HAT_MIN = -65536;
  // static const int32_t HAT_MAX = 65535;

  bool A;
  bool B;
  bool X;
  bool Y;
  bool LB;
  bool RB;
  bool L3;
  bool R3;
  bool Up;
  bool Down;
  bool Left;
  bool Right;
  bool Xbox;
  bool Start;
  bool Select;
  uint8_t LT;
  uint8_t RT;
  Joystick JoyL;
  Joystick JoyR;

  USB usb;
  XBOXUSB xb(&usb);

  //initialize our USB library
  //NOTE: if it fails to start, we halt by entering into an infinite loop
  void Init(void) noexcept {
    Serial.print("Initializing USB... ");
    if(usb.Init() == -1) {
      Serial.println("Failed to initialize USB. Halt.");
      while(true);
    }
    Serial.println("USB Initialized!");
  }

  //update the state of the xbox controller
  void Update(void) noexcept {
    usb.Task();
    A = xb.getButtonClick(ButtonEnum::A);
    B = xb.getButtonClick(ButtonEnum::B);
    X = xb.getButtonClick(ButtonEnum::X);
    Y = xb.getButtonClick(ButtonEnum::Y);
    LB = xb.getButtonClick(ButtonEnum::LB);
    RB = xb.getButtonClick(ButtonEnum::RB);
    L3 = xb.getButtonClick(ButtonEnum::L3);
    R3 = xb.getButtonClick(ButtonEnum::R3);
    Up = xb.getButtonClick(ButtonEnum::UP);
    Down = xb.getButtonClick(ButtonEnum::DOWN);
    Left = xb.getButtonClick(ButtonEnum::LEFT);
    Right = xb.getButtonClick(ButtonEnum::RIGHT);
    Xbox = xb.getButtonClick(ButtonEnum::XBOX);
    Start = xb.getButtonClick(ButtonEnum::START);
    Select = xb.getButtonClick(ButtonEnum::SELECT);
    LT = xb.getButtonPress(ButtonEnum::LT);
    RT = xb.getButtonPress(ButtonEnum::RT);
    JoyL.x = xb.getAnalogHat(AnalogHatEnum::LeftHatX);
    JoyL.y = xb.getAnalogHat(AnalogHatEnum::LeftHatY);
    JoyR.x = xb.getAnalogHat(AnalogHatEnum::RightHatX);
    JoyR.y = xb.getAnalogHat(AnalogHatEnum::RightHatY);
  }

  bool IsAvailable(void) noexcept {
    return xb.Xbox360Connected;
  }
}

#endif
