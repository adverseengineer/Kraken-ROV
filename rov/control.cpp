//Nick Sells, 2023
//ETSU Underwater Robotics

#include "control.h"
#include "util.h"

namespace Control {

  USB usb;

  #ifdef USE360
  XBOXUSB gamepad(&usb);
  #else
  XBOXONE gamepad(&usb);
  #endif

  //initialize our input system
  void Init(void) noexcept {

    Serial.print(F("\nInitializing USB... "));
    Util::Assert(usb.Init() == -1, F("Failed to initialize USB"));
    Serial.println(F("USB Initialized!"));
  }

  //update the state of our input system 
  void Update(void) noexcept {
    usb.Task();
  }

  //returns true if a controller is connected and responsive
  bool IsAvailable(void) noexcept {
    #ifdef USE360
    return gamepad.Xbox360Connected;
    #else
    return gamepad.XboxOneConnected;
    #endif
  }

  //tells whether or not the given button has been pressed since last tick
  uint8_t GetButtonHit(ButtonEnum btn) noexcept {
    return gamepad.getButtonClick(btn);
  }

  //tells whether or not the given button is pressed right now
  //in the case of triggers, it returns the strength of the pull
  uint8_t GetButtonHeld(ButtonEnum btn) noexcept {
    return gamepad.getButtonPress(btn);
  }

  //returns the value reported by the given analog axis
  int16_t GetHat(AnalogHatEnum hat) noexcept {
    auto val = gamepad.getAnalogHat(hat);
    if((DEADZONE < val) || (DEADZONE < -val))
      return val;
    else
      return 0;
  }
}
