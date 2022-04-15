#!/usr/bin/env python3
#Nick Sells 2022

import inputs, pigpio
from config import *
from util import *
from gamepad_state import gamepad_state;
from sys import exc_info

assert len(inputs.devices.gamepads) == 1, "please connect exactly one controller"
# gamepad = inputs.devices.gamepads[0]

pi = pigpio.pi()

init_pins()
init_thrusters()

close_requested = False

while not close_requested:

	try:
		events = inputs.get_gamepad()
		for event in events:
			update_thrusters(pi, event)
			update_claws(pi, event)

	except OSError:
		print(exc_info())
		close_requested = True

pi.stop()
