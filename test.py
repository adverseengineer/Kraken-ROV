#!/usr/bin/python3
#Nick Sells 2022

from config import *
from inputs import devices, get_gamepad
import pigpio
import time

if len(devices.gamepads) < 1:
	raise RuntimeError("unable to detect gamepad")

LED_PIN = 23
close_requested = False

pi = pigpio.pi()
pi.set_mode(LED_PIN, pigpio.OUTPUT)

def map(t, in_min, in_max, out_min, out_max):
	return out_min + (t - in_min) * (out_max - out_min) / (in_max - in_min)

def init_esc():
	for _, pin in enumerate(ESC_PIN):
		pi.set_servo_pulsewidth(pin, ESC_US_HALT)
	
	time.sleep(ESC_INIT_DELAY)

#TODO: try using set_servo_pulsewidth to control an esc
#it seems to be a similar case to the arduino servo stuff working perfectly to control an esc

while not close_requested:

	try:
		events = get_gamepad()
		for event in events:
			if event.code == "ABS_Z":
				val = map(
					event.state,
					XB_AXIS_MIN[event.code],
					XB_AXIS_MAX[event.code],
					0,
					255)
				pi.set_PWM_dutycycle(LED_PIN, val)
				
	except KeyboardInterrupt:
		close_requested = True
		print("Ctrl+C caught! Goodbye!")

	except OSError:
		close_requested = True
		print("controller has been disconnected") 

pi.stop()