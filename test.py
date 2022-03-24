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
			if event.code == "ABS_Y":
				val = map(event.state, -32768, 32767, ESC_US_REVERSE, ESC_US_FORWARD)
				pi.set_servo_pulsewidth(LED_PIN_1, val)
			elif event.code == "ABS_RY":
				val = map(event.state, 32767, -32768, ESC_US_REVERSE, ESC_US_FORWARD)
				pi.set_servo_pulsewidth(LED_PIN_2, val)
			elif event.code == "ABS_Z":
				if event.state == 255:
					pi.set_servo_pulsewidth(LED_PIN_3, SAVOX_US_CLOSE)
				elif event.state == 0:
					pi.set_servo_pulsewidth(LED_PIN_3, SAVOX_US_OPEN)

	except OSError:
		print("OS Error! This usually means you unplugged the controller")
		close_requested = True

	except Exception:
		print("Plain Exception! This is usally an issue with pigpiod")
		print(traceback.format_exc())

pi.stop()
