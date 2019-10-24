/*
  Sensor Calibration test. Upon successful calibration, serial monitor should show "Calibration Complete" and "Sensor Active"
  Once calibrated, sensor should be able to show output 1 for motion detected and 0 for no motion.

  Written by ELEC5552 Team 25.
  Last revision 24.10.2019
  
 */

#include <SPI.h>

int calibrationTime = 30;
long unsigned int lowIn;
long unsigned int pause = 5000;
boolean lockLow = true;
boolean takeLowTime;
int pirpin = 3;
int val = 0;

 // initialise Arduino Serial Monitor
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect.
  }
  calibrateSensor();
  Serial.println("Begin sensor detection");
  delay(2000);
}

// calibrate the Adafruit PIR sensor
void calibrateSensor()
{
  pinMode(pirpin, INPUT);
  digitalWrite(pirpin, LOW);
  Serial.println("[INFO]Calibrating Sensor");
  for (int i = 0; i < calibrationTime; i++)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("[INFO]Calibration Complete");
  Serial.println("[INFO]Sensor Active");
  delay(2000);
}

// check sensor output
void loop() {
  
 // output the value of each analog input pin
 val = digitalRead(pirpin);  // read input value
 
 if (val == HIGH) {            // check if the input is HIGH
    Serial.println("Output: 1");
 }
 else {
    // input is LOW
    Serial.println("Output: 0");
 }       
    delay(1000);
}
