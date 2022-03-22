#!/usr/bin/env python3
#Nick Sells 2022

import inputs, pigpio, time, sys, traceback
from config import *

if len(inputs.devices.gamepads) != 1:
	print("please connect exactly one controller")
	sys.exit(-1)

LED_PIN_1 = 26 #white
LED_PIN_2 = 16 #gray
LED_PIN_3 = 12 #blue

close_requested = False

pi = pigpio.pi('raspberrypi')

pi.set_mode(LED_PIN_1, pigpio.OUTPUT)
pi.set_mode(LED_PIN_2, pigpio.OUTPUT)
pi.set_mode(LED_PIN_3, pigpio.OUTPUT)

def map(t, in_min, in_max, out_min, out_max):
	return out_min + (t - in_min) * (out_max - out_min) / (in_max - in_min)

while not close_requested:

	try:
		events = inputs.get_gamepad()
		for event in events:
			val = map(event.state, XB_AXIS_MIN[event.code], XB_AXIS_MAX[event.code], 0, 255)
			match event.code:
				case "ABS_X":
					pi.set_PWM_dutycycle(LED_PIN_1, val)
				case "ABS_Y":
					pi.set_PWM_dutycycle(LED_PIN_2, val)
				case "ABS_Z":
					pi.set_PWM_dutycycle(LED_PIN_3, val)

	except OSError:
		print("OS Error! This usually means you unplugged the controller")
		close_requested = True

	except Exception:
		print("Plain Exception! This is usally an issue with pigpiod")

pi.stop()
