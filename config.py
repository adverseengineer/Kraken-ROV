#Nick Sells, 2022

#all pin values are BCM numbered
THRUSTER_BL = 12 #pin 12, ground 30
THRUSTER_ML = 16 #pin 16, ground 34
THRUSTER_FL = 23 #pin 23, ground 14
THRUSTER_FR = 26 #pin 26, ground 39
THRUSTER_MR = 17 #pin 17, ground 9
THRUSTER_BR = 25 #pin 25, ground 20
CLAW_L = 13 #pin 13, no ground
CLAW_R = 6 #pin 6, no ground

#it takes roughly this many seconds for our ESC's to initialize
THRUSTER_INIT_DELAY = 7

THRUSTER_HALT = 1500
THRUSTER_REVERSE = 1100
THRUSTER_FORWARD = 1900

CLAW_CLOSE = 800
CLAW_OPEN = 2200

AXIS_MIN = -32768
AXIS_MAX = 32767

TRIGGER_MIN = 0
TRIGGER_MAX = 255
