
#ifndef ESC_H
#define ESC_H

#include "control.h"

namespace ESC {

  //pulse widths to lerp between to communicate with our ESCs
  const uint16_t HALT = 1500;
  const uint16_t REVERSE = 1100;
  const uint16_t FORWARD = 1900;

  //it takes roughly this many ms for our ESCs to initialize after being fed a halt signal
  const uint16_t INIT_DELAY = 7000;

  Servo escFL;
  Servo escFR;
  Servo escBL;
  Servo escBR;
  Servo escVL;
  Servo escVR;

  float moveScalarFL;
  float moveScalarFR;
  float moveScalarBL;
  float moveScalarBR;

  float spinScalarFL;
  float spinScalarFR;
  float spinScalarBL;
  float spinScalarBR;

  //initialize our ESCs
  //TODO: communicate with the ESC's to know if the initialization fails so we can halt
  void Init(void) {
    Serial.print("Initializing ESCs... ");
    
    pinMode(Defs::Pins::FL, OUTPUT);
    pinMode(Defs::Pins::FR, OUTPUT);
    pinMode(Defs::Pins::BL, OUTPUT);
    pinMode(Defs::Pins::BR, OUTPUT);
    pinMode(Defs::Pins::VL, OUTPUT);
    pinMode(Defs::Pins::VR, OUTPUT);

    escFL.attach(Defs::Pins::FL, REVERSE, FORWARD);
    escFR.attach(Defs::Pins::FR, REVERSE, FORWARD);
    escBL.attach(Defs::Pins::BL, REVERSE, FORWARD);
    escBR.attach(Defs::Pins::BR, REVERSE, FORWARD);
    escVL.attach(Defs::Pins::VL, REVERSE, FORWARD);
    escVR.attach(Defs::Pins::VR, REVERSE, FORWARD);

    escFL.writeMicroseconds(HALT);
    escFR.writeMicroseconds(HALT);
    escBL.writeMicroseconds(HALT);
    escBR.writeMicroseconds(HALT);
    escVL.writeMicroseconds(HALT);
    escVR.writeMicroseconds(HALT);

    //wait for them to initialize
    delay(INIT_DELAY);
    Serial.println("ESCs Initialized!");
  }

  //
  void UpdateMoveScalars() {

    //we use the left stick to indicate which way we want to go and how fast

    //so we start with a resultant vector and we work backwards to find the vectors that will produce it
    //the angles of our thrust vectors are fixed into the structure of our ROV, so we just need to find the magnitudes
    //we will refer to them as move scalars
    //we will refer to the joystick vector as j
    //let each move scalar be equal to cos(m-k) * |j|
    //where m is the mount angle of that thruster and k is the joystick angle, i.e. atan2(j.y, j.x)
    //we can use a trig identity to simplify this: cos(m-k) = cos(m)cos(k) + sin(m)sin(k)
    //if we plug all the mount angles into that, we get scalars in the form: (±cos(k)±sin(k))/sqrt(2)
    //now that our sines and cosines are of just one variable, we can remove the redundant step of calculating k in the first place
    //all we need is j and Soh Cah Toa    
    //for our triangle, the opposite side is j.y and the adjacent side is j.x. the hypotenuse is sqrt(j.x^2 + j.y^2)
    //this makes sin(k) = j.y/|j| and cos(k) = j.x/|j|
    //on a physical joystick, |j| will be constrained to the range [0,1]
    //and because our move scalars are multiplied by |j|, it cancels out and we are left with just sqrt(2) on the bottom
    //so our move scalars are simply of the form (±j.x±j.y)/sqrt(2)

    float invSqrt2 = sqrt(2)/2;
    float c = Control::JoyL.x * invSqrt2;
    float s = Control::JoyL.y * invSqrt2;

    moveScalarFL = c + s;
    moveScalarFR = -c + s;
    moveScalarBL = c - s;
    moveScalarBR = -c - s;
  }

  void UpdateSpinScalars(void) {
    //we use the left-right axis of the right stick to indicate which direction to spin and how fast
    //this is fairly straightforward:
    //to rotate clockwise, each thruster's output vector points counter-clockwise, relative to the center of the ROV
    //to rotate counter-clockwise, each thruster's output vector points clockwise, relative to the center of the ROV
    //the magnitude of these vectors is proportional to the horizontal component of the right joystick's vector

    //TODO:
  }

  void ApplyScalars(void) {

  }
}

#endif
