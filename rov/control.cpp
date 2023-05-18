
#include <SPI.h>

#include "control.h"

namespace Control {

  USB usb;
  
  #ifdef USE360
  XBOXUSB xb(&usb);
  #else
  XBOXONE xb(&usb);
  #endif

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
  }

  bool IsAvailable(void) noexcept {
    #ifdef USE360
    return xb.Xbox360Connected;
    #else
    return xb.XboxOneConnected;
    #endif
  }

  uint8_t GetButtonHit(ButtonEnum btn) noexcept {
    return xb.getButtonClick(btn);
  }

  uint8_t GetButtonHeld(ButtonEnum btn) noexcept {
    return xb.getButtonPress(btn);
  }

  int16_t GetHat(AnalogHatEnum hat) noexcept {
    auto val = xb.getAnalogHat(hat);
    if((DEADZONE < val) || (val < -DEADZONE))
      return val;
    else
      return 0;
  }
}
