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
    Brain.Screen.print(PotentiometerA.angle(degrees) - InitPointDeg); 
    Brain.Screen.newLine();

    //wheel motors
    motor LeftMotor = motor(PORT2);
    motor RightMotor = motor(PORT9);

    //Value of joystick positions
    double turnVal = -Controller1.Axis1.position(percent);
    double forwardVal = Controller1.Axis3.position(percent);

    //Converts percentage to voltage
    double turnVolts = turnVal * 0.12;
    double forwardVolts = forwardVal * 0.12 * (1 - (std::abs(turnVolts)/12.0) * turnImportance);

    LeftMotor.spin(forward, forwardVolts - turnVolts, voltageUnits::volt);
    RightMotor.spin(forward, forwardVolts + turnVolts, voltageUnits::volt);

    int control;
    if (Controller1.ButtonL2.pressing() == true){
        ArmGroup.spin(forward, 150, vex::velocityUnits::pct);
    }else if (Controller1.ButtonL1.pressing() == true && PotentiometerA.angle(degrees) - InitPointDeg > 0){
        control = std::abs(PotentiometerA.angle(degrees) - InitPointDeg) * 0.1;
        ArmGroup.spin(reverse, 150 * control, vex::velocityUnits::pct);
    }else{
      ArmGroup.stop();
    }
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
