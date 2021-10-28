#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LeftDriveSmart = motor(PORT2, ratio18_1, false);
motor RightDriveSmart = motor(PORT9, ratio18_1, true);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 295, 40, mm, 1);
controller Controller1 = controller(primary);
motor ArmGroupMotorA = motor(PORT1, ratio18_1, false);
motor ArmGroupMotorB = motor(PORT10, ratio18_1, true);
motor_group ArmGroup = motor_group(ArmGroupMotorA, ArmGroupMotorB);
pot PotentiometerA = pot(Brain.ThreeWirePort.A);
/*vex-vision-config:begin*/
signature Vision5__SIG_1 = signature (1, 1435, 2077, 1756, -4241, -3705, -3973, 2.4, 0);
vision Vision5 = vision (PORT5, 50, Vision5__SIG_1);
/*vex-vision-config:end*/

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}