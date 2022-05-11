#!/usr/bin/env python3
#Nick Sells 2022

import pigpio, time

pi = pigpio.pi('nickpi')

pin = 6

pi.set_mode(pin, pigpio.OUTPUT)

pi.set_servo_pulsewidth(pin, 1500)
time.sleep(7)

loops = 0

close_requested = False

while not close_requested:
	try:
		loops += 1;
		pi.set_servo_pulsewidth(pin, 800)
		print(loops)
		time.sleep(0.01)
	except KeyboardInterrupt:
		close_requested = True

pi.set_servo_pulsewidth(pin, 1400)
pi.stop()