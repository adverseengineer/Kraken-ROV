
#include <SPI.h>

#include "control.h"

namespace Control {

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
    xb.setLedMode(LEDModeEnum::ROTATING);
    Serial.println("USB Initialized!");
    //while(!xb.Xbox360Connected);
  }

  //update the state of the xbox controller 
  void Update(void) noexcept {
    usb.Task();
  }

  bool IsAvailable(void) noexcept {
    return xb.Xbox360Connected;
  }

  uint8_t GetButtonHit(ButtonEnum btn) noexcept {
    return xb.getButtonClick(btn);
  }

  uint8_t GetButtonHeld(ButtonEnum btn) noexcept {
    return xb.getButtonPress(btn);
  }

  int32_t GetHat(AnalogHatEnum hat) noexcept {
    return xb.getAnalogHat(hat);
  }
}
