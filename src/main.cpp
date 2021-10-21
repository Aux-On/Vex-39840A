/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    2, 9            
// Controller1          controller                    
// ArmGroup             motor_group   1, 10           
// PotentiometerA       pot           A               
// Vision5              vision        5               
// ---- END VEXCODE CONFIGURED DEVICES ----
#include <iostream>
#include "vex.h"
#include <cmath> //std::abs
// A global instance of competition
competition Competition;

//Constants
int32_t InitPointDeg;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/
motor LeftMotor = motor(PORT2);
motor RightMotor = motor(PORT9);
void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  InitPointDeg = PotentiometerA.angle(degrees);

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
void autonomous(void) {
  double error;

  double target[3];
  double targetangle;
  double turnamount;
  double angleerror;
  double turnpower;
  // in inches
  target[0] = 73;
  target[1] = 48;
  target[2] = 48;
  targetangle = (atan(1/6) * 180) / M_PI;


  // diameter of wheel is 4 inches
  // circumfrence is about 12.56


  for (int i = 0; i < sizeof(target); i++){
    long motorposition = (LeftMotor.position(degrees) + RightMotor.position(degrees))/2; // average of two motors
    long motordistance = (motorposition/360) * 12.56;

    error = target[i] - motordistance;
    turnamount = LeftMotor.position(degrees) - RightMotor.position(degrees);
    angleerror = targetangle - turnamount;
    turnpower = angleerror * 0.5;
    while(error > 0.01 && angleerror > 0.01){
      LeftMotor.spin(forward, 100 * error / target[i] + turnpower, vex::velocityUnits::pct);
      RightMotor.spin(forward, 100 * error / target[i] - turnpower, vex::velocityUnits::pct);

      motorposition = (LeftMotor.position(degrees) + RightMotor.position(degrees))/2; // average of two motors
      motordistance = (motorposition/360) * 12.56;

      error = target[i] - motordistance;
      turnamount = LeftMotor.position(degrees) - RightMotor.position(degrees);
      angleerror = targetangle - turnamount;
      turnpower = angleerror * 0.5;
    }
  }
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  //Settings
  double turnImportance = 1;

  while (1) {
    // Brain.Screen.print(PotentiometerA.angle(degrees) - InitPointDeg); 
    // Brain.Screen.newLine();

    //wheel motors


    //Value of joystick positions
    double turnVal = -Controller1.Axis1.position(percent);
    double forwardVal = Controller1.Axis3.position(percent);

    //Converts percentage to voltage
    double turnVolts = turnVal * 0.12;
    double forwardVolts = forwardVal * 0.12 * (1 - (std::abs(turnVolts)/12.0) * turnImportance);

    LeftMotor.spin(forward, forwardVolts - turnVolts, voltageUnits::volt);
    RightMotor.spin(forward, forwardVolts + turnVolts, voltageUnits::volt);

    int control;
    if (Controller1.ButtonL2.pressing() == true && PotentiometerA.angle(degrees) - InitPointDeg < 250){
        ArmGroup.spin(forward, 150, vex::velocityUnits::pct);
    }else if (Controller1.ButtonL1.pressing() == true && PotentiometerA.angle(degrees) - InitPointDeg > 0){
        control = std::abs(PotentiometerA.angle(degrees) - InitPointDeg) * 0.1;
        ArmGroup.spin(reverse, 150, vex::velocityUnits::pct);
    }else{
      ArmGroup.stop();
    }

    Brain.Screen.clearScreen();
    Brain.Screen.setOrigin(1,1);
    Brain.Screen.drawRectangle(0,0,316,212);

    Vision5.takeSnapshot(Vision5__SIG_1);

    if(Vision5.largestObject.exists){
        Brain.Screen.drawRectangle(Vision5.largestObject.originX, Vision5.largestObject.originY, 
        Vision5.largestObject.width, Vision5.largestObject.width, color::red);
    }

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
    // Run the pre-autonomous function.
  pre_auton();
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
