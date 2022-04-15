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
	pi.set_mode(CLAW, pigpio.OUTPUT)

def init_thrusters(pi):
	pi.set_servo_pulsewidth(THRUSTER_BL, THRUSTER_HALT)
	pi.set_servo_pulsewidth(THRUSTER_ML, THRUSTER_HALT)
	pi.set_servo_pulsewidth(THRUSTER_FL, THRUSTER_HALT)
	pi.set_servo_pulsewidth(THRUSTER_FR, THRUSTER_HALT)
	pi.set_servo_pulsewidth(THRUSTER_MR, THRUSTER_HALT)
	pi.set_servo_pulsewidth(THRUSTER_BR, THRUSTER_HALT)
	time.sleep(THRUSTER_INIT_DELAY)

def thruster_set_speed(pi, thruster, speed):
	assert(THRUSTER_REVERSE <= speed <= THRUSTER_FORWARD)
	pi.set_servo_pulsewidth(thruster, speed)

def claw_set_position(pi, claw, position):
	assert(CLAW_CLOSE <= position <= CLAW_OPEN)
	pi.set_servo_pulsewidth(claw, position)

def update_thrusters(pi, event):
	val = map(event.state, XB_AXIS[event.code][0], XB_AXIS[event.code][1], THRUSTER_REVERSE, THRUSTER_FORWARD)
	match(event.code):
		case "ABS_Y": #move forward/backward
			thruster_set_speed(pi, THRUSTER_FL, val)
			thruster_set_speed(pi, THRUSTER_FR, val)
			thruster_set_speed(pi, THRUSTER_BL, val)
			thruster_set_speed(pi, THRUSTER_BR, val)
		case "ABS_X": #rotate cw/ccw
			thruster_set_speed(pi, THRUSTER_FL, val)
			thruster_set_speed(pi, THRUSTER_FR, val)
			thruster_set_speed(pi, THRUSTER_BL, val)
			thruster_set_speed(pi, THRUSTER_BR, val)
		case "ABS_RX": #strafe left/right
			thruster_set_speed(pi, THRUSTER_FL, val)
			thruster_set_speed(pi, THRUSTER_FR, val)
			thruster_set_speed(pi, THRUSTER_BL, val)
			thruster_set_speed(pi, THRUSTER_BR, val)
		case "ABS_RY": #surface/dive
			thruster_set_speed(pi, THRUSTER_ML, val)
			thruster_set_speed(pi, THRUSTER_MR, val)

def update_claws(pi, event):
	val = map(event.state, XB_AXIS[event.code][0], XB_AXIS[event.code][1], CLAW_CLOSE, CLAW_OPEN)
	match(event.code):
		case "BTN_TL": #left claw open
			claw_set_position(pi, CLAW_L, CLAW_OPEN)
		case "ABS_Z": #left claw close
			claw_set_position(pi, CLAW_L, val)
		case "BTN_TR": #right claw open
			claw_set_position(pi, CLAW_R, CLAW_OPEN)
		case "ABS_RZ": #right claw close
			claw_set_position(pi, CLAW_R, val)