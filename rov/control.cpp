//Nick Sells, 2023
//ETSU Underwater Robotics

#include "control.h"
#include "util.h"

static USB usb;

#ifdef USE360
static XBOXUSB gamepad(&usb);
#else
static XBOXONE gamepad(&usb);
#endif

//initialize our input system
void Control::Init(void) noexcept {

  Serial.print(F("\nInitializing USB... "));
  Util::Assert(usb.Init() == -1, F("Failed to initialize USB"));
  Serial.println(F("USB Initialized!"));
}

//update the state of our input system 
void Control::Update(void) noexcept {
  usb.Task();
}

//returns true if a controller is connected and responsive
bool Control::IsAvailable(void) noexcept {
  #ifdef USE360
  return gamepad.Xbox360Connected;
  #else
  return gamepad.XboxOneConnected;
  #endif
}

//tells whether or not the given button has been pressed since last tick
uint8_t Control::GetButtonHit(ButtonEnum btn) noexcept {
  return gamepad.getButtonClick(btn);
}

//tells whether or not the given button is pressed right now
//in the case of triggers, it returns the strength of the pull
uint8_t Control::GetButtonHeld(ButtonEnum btn) noexcept {
  return gamepad.getButtonPress(btn);
}

//returns the value reported by the given analog axis
int16_t Control::GetHat(AnalogHatEnum hat) noexcept {
  auto val = gamepad.getAnalogHat(hat);
  if((DEADZONE < val) || (DEADZONE < -val))
    return val;
  else
    return 0;
}
