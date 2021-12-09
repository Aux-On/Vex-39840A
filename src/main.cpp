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
// LeftMotor            motor         2               
// RightMotor           motor         9               
// ClampMotor           motor         10              
// ArmMotor             motor         1               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include <iostream>
#include "vex.h"
#include <cmath>

// A global instance of competition
competition Competition;

controller Controller1 = controller();

motor LeftMotor = motor(PORT2);
motor RightMotor = motor(PORT9);
motor ClampMotor = motor(PORT10);
motor ArmMotor = motor(PORT1);

double InitPointDeg;
long usedmotorpos;
long initmotorpos;
double Initarm;

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

  LeftMotor.spin(forward, 20, vex::velocityUnits::pct);
  RightMotor.spin(forward, 20, vex::velocityUnits::pct);
  wait(2000,msec);
  LeftMotor.stop();
  RightMotor.stop();
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
    //wheel motors
    // motor LeftMotor = motor(PORT2);
    // motor RightMotor = motor(PORT9);

    //Value of joystick positions
    double turnVal = Controller1.Axis3.position(percent);
    double forwardVal = Controller1.Axis1.position(percent);

    //Converts percentage to voltage
    double turnVolts = turnVal * 0.12 * 2;
    double forwardVolts = forwardVal * 0.12 * 2 * (1 - (std::abs(turnVolts)/12.0) * turnImportance);

    LeftMotor.spin(forward, forwardVolts - turnVolts, voltageUnits::volt);
    RightMotor.spin(forward, forwardVolts + turnVolts, voltageUnits::volt);

  //  std::cout << "Motor Degrees:" << ArmGroup.position(degrees) << std::endl;
   // std::cout << "Actual Value " << PotentiometerA.angle(degrees) << std::endl;

//////////////////////////////////////////////////

// if (Controller1.ButtonB.pressing() == true){
//   initmotorpos = (ArmGroup.position(degrees))/2;
// }

// usedmotorpos = ArmGroup.position(degrees) - initmotorpos;

//////////////////////////////////////////////////////////
    ClampMotor.spin(reverse, 50 * Controller1.ButtonL2.pressing(), vex::velocityUnits::pct);
    ClampMotor.spin(forward, 50 * Controller1.ButtonL2.pressing(), vex::velocityUnits::pct);
    ArmMotor.spin(reverse, 50 * Controller1.ButtonR2.pressing(), vex::velocityUnits::pct);
    ArmMotor.spin(forward, 50 * Controller1.ButtonR2.pressing(), vex::velocityUnits::pct);
    
    // if (Controller1.ButtonL2.pressing()){
    //     ClampMotor.spin(reverse, 50, vex::velocityUnits::pct);
    // }
    // if (Controller1.ButtonL1.pressing() /*&& (usedmotorpos > -1343.6 || Controller1.ButtonB.pressing() == true)*/){
    //     ClampMotor.spin(forward, 50, vex::velocityUnits::pct);
    // }
    // if (Controller1.ButtonR2.pressing() /*&& (usedmotorpos > -1343.6 || Controller1.ButtonB.pressing() == true)*/){
    //     ArmMotor.spin(reverse, 50, vex::velocityUnits::pct);
    // }
    // if (Controller1.ButtonR1.pressing() /*&& (usedmotorpos > -1343.6 || Controller1.ButtonB.pressing() == true)*/){
    //     ArmMotor.spin(forward, 50, vex::velocityUnits::pct);
    // }
    // else{
    //     ClampMotor.stop(brakeType::hold);
    //     ArmMotor.stop(brakeType::hold);
    // }
    // }else if (Controller1.ButtonL1.pressing() == true && (usedmotorpos < 0 || Controller1.ButtonB.pressing() == true)){
    //     //control = std::abs(PotentiometerA.angle(degrees) - InitPointDeg) * 0.1;
    //     ArmGroup.spin(forward, 150, vex::velocityUnits::pct);
    // }else{
    //   ArmGroup.stop(brakeType::hold);
    // }
  
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
