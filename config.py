#Nick Sells, 2022

DEADZONE = 0.5

XB_AXIS_MIN = {
	"ABS_X": -32768,
	"ABS_Y": 32767,
	"ABS_Z": 0,
	"ABS_RX": -32768,
	"ABS_RY": 32767,
	"ABS_RZ": 0
}

XB_AXIS_MAX = {
	"ABS_X": 32767,
	"ABS_Y": -32768,
	"ABS_Z": 255,
	"ABS_RX": 32767,
	"ABS_RY": -32768,
	"ABS_RZ": 255
}

ESC_PIN = {
	"BL": 26, #pin 37, ground 39 
	"ML": 16, #pin 36, ground 34
	"FL": 12, #pin 32, ground 30
	"FR": 25, #pin 22, ground 20
	"MR": 23, #pin 16, ground 14
	"BR": 17 #pin 11, ground 9
}

THRUSTER_HALT = 1500
THRUSTER_REVERSE = 1100
THRUSTER_FORWARD = 1900

#SAVOX_US_MID = 1500
SAVOX_US_CLOSE = 800
SAVOX_US_OPEN = 2200

#it takes roughly seven seconds for our ESC's to initialize
ESC_INIT_DELAY = 7
