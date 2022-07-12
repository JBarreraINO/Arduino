// DualMotorShield.pde
// -*- mode: C++ -*-
//
// Shows how to run 2 simultaneous steppers
// using the Itead Studio Arduino Dual Stepper Motor Driver Shield
// model IM120417015
// This shield is capable of driving 2 steppers at 
// currents of up to 750mA
// and voltages up to 30V
// Runs both steppers forwards and backwards, accelerating and decelerating
// at the limits.
//
// Copyright (C) 2014 Mike McCauley
// $Id:  $

#include <AccelStepper.h>

// The X Stepper pins
#define STEPPER1_DIR_PIN 50
#define STEPPER1_STEP_PIN 2
// The Y stepper pins
#define STEPPER2_DIR_PIN 7
#define STEPPER2_STEP_PIN 4

// Define some steppers and the pins the will use
AccelStepper stepper1(AccelStepper::DRIVER, STEPPER1_STEP_PIN, STEPPER1_DIR_PIN);
AccelStepper stepper2(AccelStepper::DRIVER, STEPPER2_STEP_PIN, STEPPER2_DIR_PIN);

void setup()
{  pinMode(8,OUTPUT);
digitalWrite(8,LOW);
    stepper1.setMaxSpeed(1000.0);
    stepper1.setAcceleration(50.0);
    stepper1.moveTo(1000);
    
    stepper2.setMaxSpeed(1000.0);
    stepper2.setAcceleration(10.0);
    stepper2.moveTo(1000);
}

void loop()
{
digitalWrite(8,LOW);
    // Change direction at the limits
    if (stepper1.distanceToGo() == 0)
	stepper1.moveTo(800);
 
    stepper1.run();
    stepper2.run();
}
