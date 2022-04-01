#Nick Sells, 2022

#@@-@@@-@@-@@@@-+-+@@
#@@@@-@@@@@@@-@+@@@+-

#all pin values are BCM numbered
THRUSTER_BL = 26, #pin 37, ground 39 
#THRUSTER_ML = 16, #pin 36, ground 34
THRUSTER_FL = 12, #pin 32, ground 30
THRUSTER_FR = 25, #pin 22, ground 20
#THRUSTER_MR = 23, #pin 16, ground 14
THRUSTER_BR = 17, #pin 11, ground 9
#CLAW = 5 #pin 29, ground 25

#NOTE: these are temporary until i can wire up the actual configuration
THRUSTER_ML = 26
THRUSTER_MR = 16
CLAW = 12

#it takes roughly this many seconds for our ESC's to initialize
THRUSTER_INIT_DELAY = 7

THRUSTER_HALT = 1500
THRUSTER_REVERSE = 1100
THRUSTER_FORWARD = 1900

CLAW_CLOSE = 800
CLAW_OPEN = 2200

XB_AXIS = {
	"ABS_X": (-32768, 32767),
	"ABS_Y": (32767, -32768),
	"ABS_Z": (0, 255),
	"ABS_RX": (-32768, 32767),
	"ABS_RY": (32767, -32768),
	"ABS_RZ": (0, 255)
}
