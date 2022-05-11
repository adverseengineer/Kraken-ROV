#Nick Sells, 2022

import pigpio, time
from config import *

def map(t, in_min, in_max, out_min, out_max):
	return out_min + (t - in_min) * (out_max - out_min) / (in_max - in_min)

def init_pins(pi):
	pi.set_mode(THRUSTER_BL, pigpio.OUTPUT)
	pi.set_mode(THRUSTER_ML, pigpio.OUTPUT)
	pi.set_mode(THRUSTER_FR, pigpio.OUTPUT)
	pi.set_mode(THRUSTER_FR, pigpio.OUTPUT)
	pi.set_mode(THRUSTER_MR, pigpio.OUTPUT)
	pi.set_mode(THRUSTER_BR, pigpio.OUTPUT)
	pi.set_mode(CLAW_L, pigpio.OUTPUT)
	pi.set_mode(CLAW_R, pigpio.OUTPUT)

def init_thrusters(pi):
	pi.set_servo_pulsewidth(THRUSTER_BL, THRUSTER_HALT)
	pi.set_servo_pulsewidth(THRUSTER_ML, THRUSTER_HALT)
	pi.set_servo_pulsewidth(THRUSTER_FL, THRUSTER_HALT)
	pi.set_servo_pulsewidth(THRUSTER_FR, THRUSTER_HALT)
	pi.set_servo_pulsewidth(THRUSTER_MR, THRUSTER_HALT)
	pi.set_servo_pulsewidth(THRUSTER_BR, THRUSTER_HALT)
	time.sleep(THRUSTER_INIT_DELAY)
	print("Thrusters Initialized!")

def thruster_set_speed(pi, thruster, speed):
	assert(THRUSTER_REVERSE <= speed <= THRUSTER_FORWARD)
	pi.set_servo_pulsewidth(thruster, speed)

def claw_set_position(pi, claw, position):
	assert(CLAW_CLOSE <= position <= CLAW_OPEN)
	pi.set_servo_pulsewidth(claw, position)
	print("setting claw position")

#takes an absolute event and updates the proper motors
def update_thrusters(pi, event):

	if event.ev_type != "Absolute":
		return

	if event.code == "ABS_X": #rotate cw/ccw
		val = map(event.state, AXIS_MIN, AXIS_MAX, THRUSTER_REVERSE, THRUSTER_FORWARD)
		thruster_set_speed(pi, THRUSTER_FL, val)
		thruster_set_speed(pi, THRUSTER_FR, val)
		thruster_set_speed(pi, THRUSTER_BL, val)
		thruster_set_speed(pi, THRUSTER_BR, val)
	elif event.code == "ABS_Y": #move forward/backward
		val = map(event.state, AXIS_MAX, AXIS_MIN, THRUSTER_REVERSE, THRUSTER_FORWARD)
		thruster_set_speed(pi, THRUSTER_FL, val)
		thruster_set_speed(pi, THRUSTER_FR, val)
		thruster_set_speed(pi, THRUSTER_BL, val)
		thruster_set_speed(pi, THRUSTER_BR, val)
	elif event.code == "ABS_RX": #strafe left/right
		val = map(event.state, AXIS_MIN, AXIS_MAX, THRUSTER_REVERSE, THRUSTER_FORWARD)
		thruster_set_speed(pi, THRUSTER_FL, val)
		thruster_set_speed(pi, THRUSTER_FR, val)
		thruster_set_speed(pi, THRUSTER_BL, val)
		thruster_set_speed(pi, THRUSTER_BR, val)
	elif event.code == "ABS_RY": #surface/dive
		val = map(event.state, AXIS_MAX, AXIS_MIN, THRUSTER_REVERSE, THRUSTER_FORWARD)
		thruster_set_speed(pi, THRUSTER_ML, val)
		thruster_set_speed(pi, THRUSTER_MR, val)
	else:
		print(f"Unbound Keypress!: {event.code}")

#takes an event and uses it to update the claw servos
def update_claws(pi, event):

	if event.ev_type != "Key" and event.ev_type != "Absolute":
		return

	if event.code == "BTN_TL": #left claw open
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
		print(f"Unbound Keypress!: {event.code}")
		