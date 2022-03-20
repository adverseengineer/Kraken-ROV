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
	"BL": 4,
	"ML": 17,
	"FL": 27,
	"FR": 22,
	"MR": 5,
	"BR": 6
}

ESC_US_REVERSE = 1100
ESC_US_HALT = 1500
ESC_US_FORWARD = 1900

#it takes roughly seven seconds for our ESC's to initialize
ESC_INIT_DELAY = 7