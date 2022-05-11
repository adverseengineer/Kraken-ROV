#!/usr/bin/env python3
#Nick Sells 2022

import inputs, pigpio
from config import *
from util import *
from sys import exc_info

try:
	assert len(inputs.devices.gamepads) == 1, "please connect exactly one controller"
	# gamepad = inputs.devices.gamepads[0]

	pi = pigpio.pi()

	init_pins(pi)
	init_thrusters(pi)

	close_requested = False

	while not close_requested:
		events = inputs.get_gamepad()
		for event in events:
			if event.ev_type == "Sync":
				continue
			
			update_claws(pi, event)
			if event.ev_type == "Absolute":
				update_thrusters(pi, event)

except OSError:
	print(exc_info())
	close_requested = True
except KeyboardInterrupt:
	print("Ctrl+C Caught! Goodbye!")
	close_requested = True

pi.stop()
