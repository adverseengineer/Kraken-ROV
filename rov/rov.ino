//Nick Sells, 2023
//ETSU Underwater Robotics

#include <Servo.h>

//these are the pulse widths that make our ESCs run the engines
#define ESC_HALT 1500
#define ESC_FULLREVERSE 1100
#define ESC_FORWARD 1900

//it takes roughly this many seconds for our ESCs to initialize after being fed a halt signal
#define ESC_INIT_DELAY 7000

//TODO: edit these as the rov is wired
//these are the pin numbers on the board where our ESCs are controlled from
#define PIN_ESC_FL 0
#define PIN_ESC_FR 0
#define PIN_ESC_BL 0
#define PIN_ESC_BR 0
#define PIN_ESC_VL 0
#define PIN_ESC_VR 0
//TODO: may be able to remove one of the vertical servos, depends on if we can wire two thrusters to the same ESC

//these are the objects that track the state of our ESCs and servos
Servo escFL;
Servo escFR;
Servo escBL;
Servo escBR;
Servo escVL;
Servo escVR;

void initESCs(void) {
  //set the pin mode for each pin used to control an ESC
  pinMode(PIN_ESC_FL, OUTPUT);
  pinMode(PIN_ESC_FR, OUTPUT);
  pinMode(PIN_ESC_BL, OUTPUT);
  pinMode(PIN_ESC_BR, OUTPUT);
  pinMode(PIN_ESC_VL, OUTPUT);
  pinMode(PIN_ESC_VR, OUTPUT);

  //register each of the ESCs to a pin
  escFL.attach(PIN_ESC_FL);
  escFR.attach(PIN_ESC_FR);
  escBL.attach(PIN_ESC_BL);
  escBR.attach(PIN_ESC_BR);
  escVL.attach(PIN_ESC_VL);
  escVR.attach(PIN_ESC_VR);

  //write the halt signal to each of our ESCs
  escFL.writeMicroseconds(ESC_HALT);
  escFR.writeMicroseconds(ESC_HALT);
  escBL.writeMicroseconds(ESC_HALT);
  escBR.writeMicroseconds(ESC_HALT);
  escVL.writeMicroseconds(ESC_HALT);
  escVR.writeMicroseconds(ESC_HALT);

  //wait for them to beep
  delay(ESC_INIT_DELAY);
}

//these are the pulse widths that make our servos open and close
#define CLAW_CLOSE 800
#define CLAW_OPEN 2200

//TODO: edit these as the rov is wired
//these are the pins that our claw servos are controlled from
#define PIN_CLAW_1 0
#define PIN_CLAW_2 0

Servo claw1;
Servo claw2;

//initialize the servos that control our claws
void initServos(void) {
  //set the pin mode for each pin used to control a claw
  pinMode(PIN_CLAW_1, OUTPUT);
  pinMode(PIN_CLAW_2, OUTPUT);

  //register each of them to a pin
  claw1.attach(PIN_CLAW_1);
  claw2.attach(PIN_CLAW_2);
}

void setThrusterSpeed(Servo& esc, const unsigned int speed) {
  esc.writeMicroseconds(speed);
}

void setClawPosition(Servo& claw, const unsigned int position) {
  claw.writeMicroseconds(position);
}

void rovTurn(void) {
  //-1 +1
  //+1 -1
  //TODO: translate the python code for use here
  //the FR and BL thrusters must spin the opposite direction of the other two
	//val = map(event.state, AXIS_MIN, AXIS_MAX, THRUSTER_REVERSE, THRUSTER_FORWARD)
	//thruster_set_speed(pi, THRUSTER_FR, val)
	//thruster_set_speed(pi, THRUSTER_BL, val)
	//val = map(event.state, AXIS_MIN, AXIS_MAX, THRUSTER_FORWARD, THRUSTER_REVERSE)
	//thruster_set_speed(pi, THRUSTER_FL, val)
	//thruster_set_speed(pi, THRUSTER_BR, val)
}

void rovForwardBackward(void) {
  //+1 +1
	//-1 -1
  //TODO: translate the python code for use here
	//the front thrusters must spin the opposite direction of the other two
	//val = map(event.state, AXIS_MAX, AXIS_MIN, THRUSTER_REVERSE, THRUSTER_FORWARD)
	//thruster_set_speed(pi, THRUSTER_FL, val)
	//thruster_set_speed(pi, THRUSTER_FR, val)
	//val = map(event.state, AXIS_MAX, AXIS_MIN, THRUSTER_FORWARD, THRUSTER_REVERSE)
	//thruster_set_speed(pi, THRUSTER_BL, val)
	//thruster_set_speed(pi, THRUSTER_BR, val)
}

void rovStrafe(void) {
  //# +1 -1
	//# +1 -1
	//#the left side thrusters must spin the opposite direction of the other two 
	//val = map(event.state, AXIS_MIN, AXIS_MAX, THRUSTER_REVERSE, THRUSTER_FORWARD)
	//thruster_set_speed(pi, THRUSTER_FL, val)
	//thruster_set_speed(pi, THRUSTER_BR, val)
	//val = map(event.state, AXIS_MIN, AXIS_MAX, THRUSTER_FORWARD, THRUSTER_REVERSE)
	//thruster_set_speed(pi, THRUSTER_FR, val)
	//thruster_set_speed(pi, THRUSTER_BR, val)
}

void rovUpDown(void) {
	//val = map(event.state, AXIS_MAX, AXIS_MIN, THRUSTER_REVERSE, THRUSTER_FORWARD)
	//thruster_set_speed(pi, THRUSTER_ML, val)
	//thruster_set_speed(pi, THRUSTER_MR, val)
}

#define LJOY_X 0
#define LJOY_y 1
int lJoystick[2];

#define RJOY_X 0
#define RJOY_Y 1
int rJoystick[2];

void getInput(void){
  //TODO: this
}

const float forwardSpeedMult = 1.0f;
const float backwardSpeedMult = 1.0f;
const float strafeSpeedBult = 1.0f;

//called by the board before starting loop
void setup(void) {
  pinMode(LED_BUILTIN, OUTPUT);
  initESCs();
  initServos();
}

//called every tick by the board while running
void loop(void) {
  //for now, just blink the onboard LED
  digitalWrite(LED_BUILTIN, HIGH);
  delay(50);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
}
