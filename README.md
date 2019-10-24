# ROSA Software
 Contains the main software, supporting libraries and testing software for ROSA.
 
 ROSA_main.ino:
 
	Performs all functionalities of ROSA.
	
	Instructions:
		1. Flash program to Arduino Uno with Ethernet Shield. Connect Ethernet Shield to local machine. Ensure a Adafruit PIR sensor is connected to the right pins.
		2. Open browser and enter IP Address: 192.168.1.177. Change IPv4 address to current network in Line 19 of code if necessary.
		3. Wait for sensor calibration. Once complete, occupancy sensor should be fully functioning.
		

		- libraries folder contains all relevant libraries
		
		- Testing ROSA: test folder contains all function tests for ROSA:
		
		httpTest.ino: 			Tests ROSA's HTTP connection to local server
		mazemapTest.ino: 		Test MazeMap overlay for eZone
		sensorCalibrate.ino:	Calibrate PIR sensor and perform motion detection