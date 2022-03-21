#!/usr/bin/env python3
#Nick Sells 2022

import inputs, pigpio, time, sys, traceback
from config import *

if len(inputs.devices.gamepads) != 1:
	print("please connect exactly one controller")
	sys.exit(-1)

LED_PIN = 26
close_requested = False

pi = pigpio.pi('raspberrypi')

pi.set_mode(LED_PIN, pigpio.OUTPUT)

def map(t, in_min, in_max, out_min, out_max):
	return out_min + (t - in_min) * (out_max - out_min) / (in_max - in_min)

while not close_requested:

	try:
		events = inputs.get_gamepad()
		for event in events:
			if event.code == "ABS_Z":
				val = round(map(
					event.state,
					XB_AXIS_MIN[event.code],
					XB_AXIS_MAX[event.code],
					0,
					255
				))

				pi.set_PWM_dutycycle(LED_PIN, val)
				print(val)

	except OSError:
		print("OS Error! This usually means you unplugged the controller")
		#close_requested = True

	except Exception:
		print("Plain Exception! This is usally an issue with pigpiod")

pi.stop()
