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
	print("GPIO Initialized!")

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
	#print(f"setting thruster speed to {speed}")

def claw_set_position(pi, claw, position):
	assert(CLAW_CLOSE <= position <= CLAW_OPEN)
	pi.set_servo_pulsewidth(claw, position)
	print(f"setting claw position to {position}")

#rotate the rov about the y axis (yaw)
def rov_turn(pi, event):
	# -1 +1
	# +1 -1
	#the front right and back left thrusters must spin the opposite direction of the other two
	val = map(event.state, AXIS_MIN, AXIS_MAX, THRUSTER_REVERSE, THRUSTER_FORWARD)
	thruster_set_speed(pi, THRUSTER_FR, val)
	thruster_set_speed(pi, THRUSTER_BL, val)
	val = map(event.state, AXIS_MIN, AXIS_MAX, THRUSTER_FORWARD, THRUSTER_REVERSE)
	thruster_set_speed(pi, THRUSTER_FL, val)
	thruster_set_speed(pi, THRUSTER_BR, val)

#move the rov forward or backward
def rov_move(pi, event):
	# +1 +1
	# -1 -1
	#the front thrusters must spin the opposite direction of the other two
	val = map(event.state, AXIS_MAX, AXIS_MIN, THRUSTER_REVERSE, THRUSTER_FORWARD)
	thruster_set_speed(pi, THRUSTER_FL, val)
	thruster_set_speed(pi, THRUSTER_FR, val)
	val = map(event.state, AXIS_MAX, AXIS_MIN, THRUSTER_FORWARD, THRUSTER_REVERSE)
	thruster_set_speed(pi, THRUSTER_BL, val)
	thruster_set_speed(pi, THRUSTER_BR, val)

#move the rov left or right
def rov_strafe(pi, event):
	# +1 -1
	# +1 -1
	#the left side thrusters must spin the opposite direction of the other two 
	val = map(event.state, AXIS_MIN, AXIS_MAX, THRUSTER_REVERSE, THRUSTER_FORWARD)
	thruster_set_speed(pi, THRUSTER_FL, val)
	thruster_set_speed(pi, THRUSTER_BR, val)
	val = map(event.state, AXIS_MIN, AXIS_MAX, THRUSTER_FORWARD, THRUSTER_REVERSE)
	thruster_set_speed(pi, THRUSTER_FR, val)
	thruster_set_speed(pi, THRUSTER_BR, val)

#raise or lower the rov
def rov_updown(pi, event):
	val = map(event.state, AXIS_MAX, AXIS_MIN, THRUSTER_REVERSE, THRUSTER_FORWARD)
	thruster_set_speed(pi, THRUSTER_ML, val)
	thruster_set_speed(pi, THRUSTER_MR, val)
		