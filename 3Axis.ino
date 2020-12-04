/*
  Simple demo, should work with any driver board

  Connect STEP, DIR as indicated

  Copyright (C)2015-2017 Laurentiu Badea

  This file may be redistributed under the terms of the MIT license.
  A copy of this license has been included with this distribution in the file LICENSE.
*/
#include <Arduino.h>
#include "BasicStepperDriver.h"
#include "SyncDriver.h"

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
#define RPM 240

// Since microstepping is set externally, make sure this matches the selected mode
// If it doesn't, the motor will move at a different RPM than chosen
// 1=full step, 2=half step etc.
#define MICROSTEPS 1

// All the wires needed for full functionality
#define YDIR 6
#define YSTEP 3
#define XDIR 5
#define XSTEP 2
#define X2STEP 4
#define X2DIR 7
//Uncomment line to use enable/disable functionality
#define SLEEP 8

// 2-wire basic config, microstepping is hardwired on the driver
//BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP);

//Uncomment line to use enable/disable functionality
BasicStepperDriver stepperY(MOTOR_STEPS, YDIR, YSTEP, SLEEP);
BasicStepperDriver stepperX1(MOTOR_STEPS, XDIR, XSTEP, SLEEP);
BasicStepperDriver stepperX2(MOTOR_STEPS, X2DIR, X2STEP, SLEEP);//z


SyncDriver controller(stepperX1, stepperX2,stepperY);
void setup() {
  stepperX1.begin(RPM, MICROSTEPS);
  stepperX2.begin(RPM, MICROSTEPS);
  stepperY.begin(RPM, MICROSTEPS);
  // if using enable/disable on ENABLE pin (active LOW) instead of SLEEP uncomment next line
  stepperX1.setEnableActiveState(LOW);
  stepperX2.setEnableActiveState(LOW);
  stepperY.setEnableActiveState(LOW);

}

void loop() {

  // energize coils - the motor will hold position
  stepperY.enable();
  stepperX1.enable();
  stepperX2.enable();


  /*
     Moving motor one full revolution using the degree notation
  */
  stepperY.rotate(360);

  
  stepperY.move(-MOTOR_STEPS * MICROSTEPS);
  // pause and allow the motor to be moved by hand
  stepperY.disable();
  stepperX2.enable();
  stepperX1.enable();
  controller.rotate(-360,360);

  controller.rotate(360,-360);
  stepperX2.disable();
  stepperX1.disable();


    delay(5000);
}
