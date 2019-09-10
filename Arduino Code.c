/**
 * BrainScannerDriver.ino
 */
#include <Arduino.h> //Arduino Library
//#include <BrainDriver.h> //Brain Scanner Driver/Library
#include <Stepper.h> //Stepper Motor Library
/**
 * Main Driver for the brain scanner headset
 * 
 * Author: Hunter Eller
 * Version: Snapshot-0.0.1
 */
 
#define recieve 0 //RX pin on arduino
int stepsPerRev = 150; //Number of steps per revolution
Stepper motor0(stepsPerRev, 8, 9, 10, 11); //Thumb
Stepper motor1(stepsPerRev, 8, 9, 10, 11); //Index Finger
Stepper motor2(stepsPerRev, 8, 9, 10, 11); //Middle Finger
Stepper motor3(stepsPerRev, 8, 9, 10, 11); //Ring Finger
Stepper motor4(stepsPerRev, 8, 9, 10, 11); //Pinkie Finger


double interval = 500; //Interval between readings
double Millis = 0; //Previous count in milliseconds
int focusVal; //Level of focus

void setup() {
  init(); //Initializes headset and stepper motors.
  Serial.begin(9600); //Sets data rate in bits per second.
}

void loop() {
  logic(); //Runs the logic and data handling for the prosthetic and headset.
  delay(500); //Delay between updates.
}

void init() {
  pinMode(recieve, INPUT); //Sets the input pin.
  Stepper.setSpeed(60); //60 Revolutions per minute.
    
}

void logic() {
  //This method handles the logic with information received from the headset.
  focusVal = getBeta(); //Reads the recieve pin data.
  if (focusVal >= 0) {
    printf("Currently Focused");
    grip();
  }
  else {
    printf("Currently UnFocused");
    gripReset(); //Resets the values of the motors.
  }
  }
// Logic will be refined once the EEG driver is finished and input from headset is more accurate.
// Input from the headset will provide the conditions for the logic, 
// the prosthetic hand will be moved from an off(release) to on(grip)
// depending on the input received. 

void grip() {
  //Spins the motors to make the prostethic grip.
  while (motor0.getStep() == 0) {
    setMotor(stepsPerRev);
  }
  
}

void gripReset() {
  //Resets the motors to an open position
  while (motor0.getStep() > 0) {
    setMotor(-stepsPerRevolution);
  }
}

int setMotor(int steps) {
  //Uses a parameter for steps to change the values for the motors.
  motor0.step(steps);
  motor1.step(steps);
  motor2.step(steps);
  motor3.step(steps);
  motor4.step(steps);
}