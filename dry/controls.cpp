//Nick Sells, 2023
//ETSU Underwater Robotics

#include "controls.h"

//the pins our controller is connected to
static const uint8_t PIN_DAT = 9; //brown
static const uint8_t PIN_CMD = 8; //orange
static const uint8_t PIN_ATT = 7; //yellow
static const uint8_t PIN_CLK = 6; //blue

//the amount of ms needed to let a wireless dualshock initialize
static const uint16_t WIRELESS_INIT_DELAY = 300;

//whether or not to read buttons as analog
static const bool analogModeOn = false;
//whether or not to enable rumble
static const bool rumbleModeOn = true;
//our controller object that holds the state of the buttons
static PS2X controller;
static uint8_t status = 0;
static uint8_t type = 0;

uint8_t Controls::rumbleStrength = 0;

//initialize the controller
void Controls::Init(void) noexcept {
    //initialize the controller
  status = controller.config_gamepad(PIN_CLK, PIN_CMD, PIN_ATT, PIN_DAT, analogModeOn, rumbleModeOn);
  delay(WIRELESS_INIT_DELAY);

  switch(status) {
    case ControllerStatus::OK:
      Serial.println(F("Controller found, successfully configured"));
      break;
    case ControllerStatus::NOTFOUND:
      Serial.println(F("No controller found, check wiring"));
      break;
    case ControllerStatus::UNRESPONSIVE:
      Serial.println(F("Controller found, but not accepting commands"));
      break;
    case ControllerStatus::NOANALOG:
      Serial.println(F("Controller found, but refusing to enter Analog mode. May not support it"));
      break;
  }
    
  type = controller.readType(); 
  switch(type) {
    case ControllerType::UNKNOWN:
      Serial.println(F("Unknown Controller type found"));
      break;
    case ControllerType::DUALSHOCK:
      Serial.println(F("Dualshock Controller found"));
      break;
    case ControllerType::GUITARHERO:
      Serial.println(F("Guitar Hero Controller found"));
      break;
	  case ControllerType::WIRELESSDUALSHOCK:
      Serial.println(F("Wireless Sony DualShock Controller found"));
      break;
  }
}

//update the virtual state of our controller
void Controls::Update(void) noexcept {
  //do nothing if there is no controller
  if(status == ControllerStatus::NOTFOUND)
    return;
  //do nothing unless the controller is a dualshock
  else if((type != ControllerType::DUALSHOCK) && (type != ControllerType::WIRELESSDUALSHOCK))
    return;

  //reads the gamepad state and sets the left motor to spin at 'rumbleStrength' speed
  controller.read_gamepad(false, rumbleStrength);
}

bool Controls::ButtonHeld(unsigned int button) noexcept {
  return controller.Button(button);
}
bool Controls::ButtonPressed(unsigned int button) noexcept {
  return controller.ButtonPressed(button);
}
bool Controls::ButtonReleased(unsigned int button) noexcept {
  return controller.ButtonReleased(button);
}
int8_t Controls::Analog(unsigned int axis) noexcept {
  int8_t val = (uint8_t) controller.Analog(axis) - 128;
  if(val < 0) val++;
  return val;
}