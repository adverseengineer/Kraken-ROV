#!/usr/bin/env python3
#Nick Sells 2022

import inputs, pigpio
from config import *
from util import *
from sys import exit

assert len(inputs.devices.gamepads) == 1, "please connect exactly one controller"
gamepad = inputs.devices.gamepads[0]
pi = pigpio.pi()

close_requested = False

while not close_requested:

	try:
		events = inputs.get_gamepad()
		for event in events:
			if event.code == "ABS_Y":
				val = map(event.state, -32768, 32767, THRUSTER_REVERSE, THRUSTER_FORWARD)
				thruster_set_speed(pi, THRUSTER_ML, val)
			elif event.code == "ABS_RY":
				val = map(event.state, 32767, -32768, THRUSTER_REVERSE, THRUSTER_FORWARD)
				thruster_set_speed(pi, THRUSTER_MR, val)
			elif event.code == "ABS_Z":
				val = map(event.state, XB_AXIS[event.code][0], XB_AXIS[event.code][1], CLAW_OPEN, CLAW_CLOSE)
				claw_set_position(pi, val)

	except OSError:
		print("OS Error! This usually means you unplugged the controller")
		close_requested = True

pi.stop()
