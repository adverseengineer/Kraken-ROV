#Nick Sells, 2022

import pigpio, time, config

def map(t, in_min, in_max, out_min, out_max):
	return out_min + (t - in_min) * (out_max - out_min) / (in_max - in_min)

def init_pins(pi):
	pi.set_mode(config.THRUSTER_BL, pigpio.OUTPUT)
	pi.set_mode(config.THRUSTER_ML, pigpio.OUTPUT)
	pi.set_mode(config.THRUSTER_FR, pigpio.OUTPUT)
	pi.set_mode(config.THRUSTER_FR, pigpio.OUTPUT)
	pi.set_mode(config.THRUSTER_MR, pigpio.OUTPUT)
	pi.set_mode(config.THRUSTER_BR, pigpio.OUTPUT)
	pi.set_mode(config.CLAW, pigpio.OUTPUT)

def init_thrusters(pi):
	pi.set_servo_pulsewidth(config.THRUSTER_BL, config.THRUSTER_HALT)
	pi.set_servo_pulsewidth(config.THRUSTER_ML, config.THRUSTER_HALT)
	pi.set_servo_pulsewidth(config.THRUSTER_FL, config.THRUSTER_HALT)
	pi.set_servo_pulsewidth(config.THRUSTER_FR, config.THRUSTER_HALT)
	pi.set_servo_pulsewidth(config.THRUSTER_MR, config.THRUSTER_HALT)
	pi.set_servo_pulsewidth(config.THRUSTER_BR, config.THRUSTER_HALT)
	time.sleep(config.THRUSTER_INIT_DELAY)

def thruster_set_speed(pi, thruster, speed):
	assert(config.THRUSTER_REVERSE <= speed <= config.THRUSTER_FORWARD)
	pi.set_servo_pulsewidth(thruster, speed)

def claw_set_position(pi, position):
	assert(config.CLAW_CLOSE <= position <= config.CLAW_OPEN)
	pi.set_servo_pulsewidth(config.CLAW, position)
