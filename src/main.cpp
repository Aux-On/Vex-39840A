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
motor LeftMotor = motor(PORT2);
motor RightMotor = motor(PORT9);

int pos = 0;
int indexstage = 1; //stages of autonomus

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  indexstage = 1;
  InitPointDeg = PotentiometerA.angle(degrees);
  Initarm = ArmGroup.position(degrees);
  ArmGroup.setPosition(0,degrees);

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

void findColor(){
  Brain.Screen.clearScreen();
  Brain.Screen.setOrigin(1,1);
  Brain.Screen.drawRectangle(0,0,316,212);

  Vision5.takeSnapshot(Vision5__SIG_1);

  //while(true){
    if(Vision5.largestObject.exists){
        LeftMotor.stop(brakeType::hold);
        RightMotor.stop(brakeType::hold);
        if(Vision5.largestObject.originX > 316/2){
          LeftMotor.spin(forward, 100, vex::velocityUnits::pct);
          pos += 3;
        }
        else if(Vision5.largestObject.originX < 316/2-2){
          RightMotor.spin(forward, 100, vex::velocityUnits::pct);
          pos -= 3;
        }
        //else{
        //  break;
        //}
        Brain.Screen.drawRectangle(Vision5.largestObject.originX, Vision5.largestObject.originY, 
        Vision5.largestObject.width, Vision5.largestObject.width, color::red);
    }
    else{
      LeftMotor.spin(forward, 75, vex::velocityUnits::pct);
      //pos += 10;
    }
  //}
}

void largestObjXlim(vision colorSensor, int maxXlim){

if (colorSensor.largestObject.width >= maxXlim){
  indexstage++;
}

}

void setArmPos(motor_group arm, double setpos, double errorRange){
  std::cout << "1 POS: " <<  arm.position(degrees) << std::endl; 
  if (arm.position(degrees) > (setpos+errorRange)){
    arm.spin(reverse, 100, vex::velocityUnits::pct);
    std::cout << "1 POS: " <<  arm.position(degrees) << std::endl; 
  }
  if (arm.position(degrees) < (setpos-errorRange)){
    arm.spin(forward, 100, vex::velocityUnits::pct);
    std::cout << "2 POS: " <<  arm.position(degrees) << std::endl; 
  }
  else{
    arm.stop(brakeType::hold);
    indexstage = indexstage+1;
  }

}

void reorientation(double errorRate){
  double netCurrentOrientation = RightMotor.position(degrees) - LeftMotor.position(degrees);
  if(netCurrentOrientation > (0 + errorRate)){
    RightMotor.spin(reverse, 50, vex::velocityUnits::pct);
  }
  else if(netCurrentOrientation < (0 - errorRate)){
    LeftMotor.spin(forward, 50, vex::velocityUnits::pct);
  }else{
    indexstage++;
  }
}




void autonStages(){

while(1){
  
switch (indexstage)
{
case 1:
    setArmPos(ArmGroup, -20, 5);
    break;
case 2:
    findColor();
    largestObjXlim(Vision5, 280);
    break;
case 3:
    setArmPos(ArmGroup, -60, 30);
    break;
case 4:
    reorientation(15);
    break;
case 5:
    RightMotor.spin(reverse, 100, vex::velocityUnits::pct);
    LeftMotor.spin(reverse, 100, vex::velocityUnits::pct);
    break;
default:
  ArmGroup.stop();
    break;
}
std::cout << "Stage: " << indexstage << std::endl;
vex::task::sleep(20);
}

}



void autonomous(void) {

  LeftMotor.spin(forward, 20, vex::velocityUnits::pct);
  RightMotor.spin(forward, 20, vex::velocityUnits::pct);
  wait(2000,msec);
  LeftMotor.stop();
  RightMotor.stop();


  /*
  while(true){

    autonStages();

    wait(20,msec);
  }
  */

  /*
  while(true)
  {
    LeftMotor.spin(forward, 7, vex::velocityUnits::pct);
    RightMotor.spin(forward, 7, vex::velocityUnits::pct);
  }
  wait(10, seconds);
  */
  //autonStages();

  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................


 

/*
while(true){
  std::cout << indexstage << std::endl << ArmGroup.position(degrees) << std::endl;
  
  if (indexstage == 0){

    //setArmPos(ArmGroup, -1340, 30);
    if (ArmGroup.position(degrees) > (Initarm - 130)){
    ArmGroup.spin(reverse, 150, vex::velocityUnits::pct);
    }
    else if (ArmGroup.position(degrees) < (Initarm - 150)){
    ArmGroup.stop(brakeType::hold);
    indexstage = indexstage+1;
    }
  

  }
  if (indexstage == 1){
    findColor();
    largestObjXlim(Vision5, 280);
  }
  if (indexstage == 2){
    setArmPos(ArmGroup, -600, 30);
  }
  if (indexstage == 3){
    reorientation(15);
  }
  if (indexstage == 4){
    RightMotor.spin(reverse, 150, vex::velocityUnits::pct);
    LeftMotor.spin(reverse, 150, vex::velocityUnits::pct);
  }
}
*/
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

   std::cout << "Motor Degrees:" << ArmGroup.position(degrees) << std::endl;
   // std::cout << "Actual Value " << PotentiometerA.angle(degrees) << std::endl;

//////////////////////////////////////////////////

if (Controller1.ButtonB.pressing() == true){
  initmotorpos = (ArmGroup.position(degrees))/2;
}

usedmotorpos = ArmGroup.position(degrees) - initmotorpos;

//////////////////////////////////////////////////////////

    if (Controller1.ButtonL2.pressing() == true /*&& (usedmotorpos > -1343.6 || Controller1.ButtonB.pressing() == true)*/){
        ArmGroup.spin(reverse, 150, vex::velocityUnits::pct);
    }else if (Controller1.ButtonL1.pressing() == true && (usedmotorpos < 0 || Controller1.ButtonB.pressing() == true)){
        //control = std::abs(PotentiometerA.angle(degrees) - InitPointDeg) * 0.1;
        ArmGroup.spin(forward, 150, vex::velocityUnits::pct);
    }else{
      ArmGroup.stop(brakeType::hold);
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
  //autonomous();
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
