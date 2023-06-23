# Kraken ROV
This repository contains the code for the ETSU Mate Team ROV. We use two Arduino Mega 2560's, each equipped with an ethernet shield. Kraken uses six BlueRobotics T200 thrusters and BlueESC's, and a 50-foot cat-6 ethernet cable to facilitate communication between the 2560's.

The code for Kraken is split into two parts. We have the dry code, which runs on an Arduino in the control box, and we have the wet code, which runs on an Arduino inside Kraken's watertight enclosure.
	
The dry code is responsible for establishing the client side of a TCP connection, interfacing with a Playstation 2 controller, interpreting controller input to generate PWM signals, and sending those signals along to the server.

The wet code is responsible for establishing the server side of a TCP connection, initializing the ESCs and Servos, receiving PWM signals from the upper Arduino, and writing those signals to the ESCs and Servos.

The Playstation 2 controller interface is made possible by an the PS2X library by Bill Porter.

The ethernet connection is made possible by ethernet shields equipped to each of the Arduino and the Arduino Ethernet3 library. To establish the connection, we assign a unique MAC address and IP address to each of them. We then set the gateway address for each of them to each other's IP address. By assigning the IPs and gateways statically, we bypass DHCP. This gives us two machines with an exceptionally stable bi-directional line of communication.