/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\VG                                               */
/*    Created:      Fri Sep 24 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Motor2               motor         2               
// Motor9               motor         9               
// Motor10              motor         10              
// Controller1          controller                    
// Motor1               motor         1               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

competition Competition;

motor FrontRightMotor = motor(PORT1);
motor RearLeftMotor = motor(PORT2);
motor RearRightMotor = motor(PORT9);
motor FrontLeftMotor = motor(PORT10);

controller Controller = controller();

void pre_auton(void){

}

void autonomous(void){

}

void usercontrol(void){
  while(1){
    RearRightMotor.spin(directionType::fwd, Controller.Axis3.position(), velocityUnits::pct);
    RearLeftMotor.spin(directionType::fwd, Controller.Axis3.position(), velocityUnits::pct);

    FrontRightMotor.spin(directionType::fwd, Controller.Axis2.position(), velocityUnits::pct);
    FrontLeftMotor.spin(directionType::fwd, Controller.Axis2.position(), velocityUnits::pct);

    task::sleep(20);
  }
}


int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  while(1){
    task::sleep(100);
  }
}
