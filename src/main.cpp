// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    1, 10           
// MotorGroup2          motor_group   2, 9            
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    1, 10           
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Motor1               motor         1               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Motor10              motor         10              
// Controller1          controller                    
// Motor1               motor         1               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Motor9               motor         9               
// Motor10              motor         10              
// Controller1          controller                    
// Motor1               motor         1               
// ---- END VEXCODE CONFIGURED DEVICES ----
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

motor_group Movement = motor_group(RearLeftMotor, RearRightMotor);
motor_group ArmMotors = motor_group(FrontLeftMotor, FrontRightMotor);

controller Controller = controller();

const float WHEEL_DIAMETER = 4; // inches
const float WHEEL_CIRCUMFERENCE = WHEEL_DIAMETER * 3.1416;
const float GEAR_RATIO = 0.5; // 0.5 turn of motor = 1 turn of wheel
const int  AUTON_DRIVE_PCT = 50; // motors at 50% power during auton
const float TURNING_DIAMETER = 19.0;

void driveForward( float inches ) {
    float inchesPerDegree = WHEEL_CIRCUMFERENCE / 360;
    float degrees = inches / inchesPerDegree;
    // startRotate doesn't wait for completion
    // this way, the other wheel can turn at same time
    RearLeftMotor.startRotateFor(
        degrees * GEAR_RATIO, rotationUnits::deg, 
        AUTON_DRIVE_PCT, velocityUnits::pct
    );
    RearRightMotor.rotateFor(
        degrees * GEAR_RATIO, rotationUnits::deg,
        AUTON_DRIVE_PCT, velocityUnits::pct
    );
}

void turn( float degrees ) {
    // Note: +90 degrees is a right turn
    float turningRatio = TURNING_DIAMETER / WHEEL_DIAMETER;
    float wheelDegrees = turningRatio * degrees;    
    // Divide by two because each wheel provides half the rotation
    RearLeftMotor.startRotateFor(
        wheelDegrees * GEAR_RATIO / 2, rotationUnits::deg, 
        AUTON_DRIVE_PCT, velocityUnits::pct
    );
    RearRightMotor.rotateFor(
        wheelDegrees * GEAR_RATIO / 2, rotationUnits::deg,
        AUTON_DRIVE_PCT, velocityUnits::pct
    );
}

void pre_auton(void){

}

void autonomous(void){

  //comment to delete

}

void usercontrol(void){
  while(1){
    // motor movement: use axis 3 to move the wheels, axis 2 to move the arms
    Movement.spin(directionType::fwd, Controller.Axis3.position(), velocityUnits::pct);
    ArmMotors.spin(directionType::fwd, Controller.Axis2.position(), velocityUnits::pct);


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
