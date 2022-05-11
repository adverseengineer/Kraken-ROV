#!/usr/bin/env python3
#Nick Sells 2022

import inputs, pigpio
from config import *
from util import *
from sys import exc_info

try:
	assert len(inputs.devices.gamepads) == 1, "please connect exactly one controller"

	pi = pigpio.pi()
	init_pins(pi)
	init_thrusters(pi)

	close_requested = False
	while not close_requested:
		events = inputs.get_gamepad()
		for event in events:

			#ignore sync events, they are literally useless
			if event.ev_type == "Sync":
				continue

			elif event.code == "ABS_X":
				rov_turn(pi, event)
			elif event.code == "ABS_Y":
				rov_move(pi, event)
			elif event.code == "ABS_RX":
				rov_strafe(pi, event)
			elif event.code == "ABS_RY":
				rov_updown(pi, event)

			elif event.code == "BTN_TL": #left claw open
				claw_set_position(pi, CLAW_L, CLAW_OPEN)
			elif event.code == "ABS_Z": #left claw close
				val = map(event.state, TRIGGER_MIN, TRIGGER_MAX, CLAW_OPEN, CLAW_CLOSE)
				claw_set_position(pi, CLAW_L, val)
			elif event.code == "BTN_TR": #right claw open
				claw_set_position(pi, CLAW_R, CLAW_OPEN)
			elif event.code == "ABS_RZ": #right claw close
				val = map(event.state, TRIGGER_MIN, TRIGGER_MAX, CLAW_OPEN, CLAW_CLOSE)
				claw_set_position(pi, CLAW_R, val)

			else:
				print(f"unmapped input: {event.code}")

except OSError:
	print(exc_info())
	close_requested = True
except KeyboardInterrupt:
	print("Ctrl+C Caught! Goodbye!")
	close_requested = True

pi.stop()
