#include "vex.h"

using namespace vex;
competition Competition;

#pragma region
/*---------------------------------------------------------------------------*/
/*                             VEXcode Config                                */
/*                                                                           */
/*  Before you do anything else, start by configuring your motors and        */
/*  sensors. In VEXcode Pro V5, you can do this using the graphical          */
/*  configurer port icon at the top right. In the VSCode extension, you'll   */
/*  need to go to robot-config.cpp and robot-config.h and create the         */
/*  motors yourself by following the style shown. All motors must be         */
/*  properly reversed, meaning the drive should drive forward when all       */
/*  motors spin forward.                                                     */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                             JAR-Template Config                           */
/*                                                                           */
/*  Where all the magic happens. Follow the instructions below to input      */
/*  all the physical constants and values for your robot. You should         */
/*  already have configured your motors.                                     */
/*---------------------------------------------------------------------------*/

Drive chassis(

//Pick your drive setup from the list below:
//ZERO_TRACKER_NO_ODOM
//ZERO_TRACKER_ODOM
//TANK_ONE_FORWARD_ENCODER
//TANK_ONE_FORWARD_ROTATION
//TANK_ONE_SIDEWAYS_ENCODER
//TANK_ONE_SIDEWAYS_ROTATION
//TANK_TWO_ENCODER
//TANK_TWO_ROTATION
//HOLONOMIC_TWO_ENCODER
//HOLONOMIC_TWO_ROTATION
//
//Write it here:
ZERO_TRACKER_NO_ODOM,

//Add the names of your Drive motors into the motor groups below, separated by commas, i.e. motor_group(Motor1,Motor2,Motor3).
//You will input whatever motor names you chose when you configured your robot using the sidebar configurer, they don't have to be "Motor1" and "Motor2".

//Left Motors:
motor_group(lf, lm, lb),

//Right Motors:
motor_group(rf, rm, rb),

//Specify the PORT NUMBER of your inertial sensor, in PORT format (i.e. "PORT1", not simply "1"):
PORT18,

//Input your wheel diameter. (4" omnis are actually closer to 4.125"):
WHEEL_DIAMETER,

//External ratio, must be in decimal, in the format of input teeth/output teeth.
//If your motor has an 84-tooth gear and your wheel has a 60-tooth gear, this value will be 1.4.
//If the motor drives the wheel directly, this value is 1:
GEAR_RATIO,

//Gyro scale, this is what your gyro reads when you spin the robot 360 degrees.
//For most cases 360 will do fine here, but this scale factor can be very helpful when precision is necessary.
IMU_SCALE,

/*---------------------------------------------------------------------------*/
/*                                  PAUSE!                                   */
/*                                                                           */
/*  The rest of the drive constructor is for robots using POSITION TRACKING. */
/*  If you are not using position tracking, leave the rest of the values as  */
/*  they are.                                                                */
/*---------------------------------------------------------------------------*/

//If you are using ZERO_TRACKER_ODOM, you ONLY need to adjust the FORWARD TRACKER CENTER DISTANCE.

//FOR HOLONOMIC DRIVES ONLY: Input your drive motors by position. This is only necessary for holonomic drives, otherwise this section can be left alone.
//LF:      //RF:    
PORT1,     -PORT2,

//LB:      //RB: 
PORT3,     -PORT4,

//If you are using position tracking, this is the Forward Tracker port (the tracker which runs parallel to the direction of the chassis).
//If this is a rotation sensor, enter it in "PORT1" format, inputting the port below.
//If this is an encoder, enter the port as an integer. Triport A will be a "1", Triport B will be a "2", etc.
3,

//Input the Forward Tracker diameter (reverse it to make the direction switch):
2.75,

//Input Forward Tracker center distance (a positive distance corresponds to a tracker on the right side of the robot, negative is left.)
//For a zero tracker tank drive with odom, put the positive distance from the center of the robot to the right side of the drive.
//This distance is in inches:
-2,

//Input the Sideways Tracker Port, following the same steps as the Forward Tracker Port:
1,

//Sideways tracker diameter (reverse to make the direction switch):
-2.75,

//Sideways tracker center distance (positive distance is behind the center of the robot, negative is in front):
5.5

);
#pragma endregion

/**
 * Function before autonomous. It prints the current auton number on the screen
 * and tapping the screen cycles the selected auton by 1. Add anything else you
 * may need, like resetting pneumatic components. You can rename these autons to
 * be more descriptive, if you like.
 */

int auton = 0;

void telemetry() {
  while (1) {
    float pos = (chassis.get_right_position_in() + chassis.get_left_position_in()) / 2;
    std::cout << "position:         " << pos << std::endl;
    std::cout << "heading:          " << chassis.get_absolute_heading() << std::endl;
    std::cout << "drive:            " << l.temperature(celsius) << std::endl;
    std::cout << "intake:           " << intake.temperature(celsius) << std::endl << std::endl;
    //std::cout << "velocity:         " << (l.voltage() + r.voltage()) / 2 << std::endl << std::endl;

    // std::cout << "output:           " << chassis.
    //std::cout << "drive temp:       " << l.temperature() << std::endl;
    //std::cout << "intake temp:      " << intake.temperature(celsius) << std::endl;
    //std::cout << "intake vel:       " << intake.voltage() << std::endl;
    //std::cout << "lift position:    " << lift.position(deg) << std::endl;
    
    // if (mogo.value()) {
    //   std::cout << "mogo:             " << "extended" << std::endl;
    // } else {
    //   std::cout << "mogo:             " << "retracted" << std::endl;
    // }

    // if (doinker.value()) {
    //   std::cout << "doinker:          " << "extended" << std::endl;
    // } else {
    //   std::cout << "doinker:          " << "retracted" << std::endl << std::endl;
    // }
    
    wait(500, msec);
  }
}

void pre_auton() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  default_constants();

  telemetry();

  imu.calibrate(3000);
  wait(3000, msec);

  optic.setLight(ledState::on);
  optic.setLightPower(100);
}

/**
 * Auton function, which runs the selected auton. Case 0 is the default,
 * and will run in the brain screen goes untouched during preauton. Replace
 * drive_test(), for example, with your own auton function you created in
 * autons.cpp and declared in autons.h.
 */

void autonomous(void) {
  l.resetPosition();
  r.resetPosition();
  lift.resetPosition();
  imu.resetHeading();
  imu.resetRotation();
  //telemetry();

  int auton = 0;

  if (auton == 0) {
    redLeft();
  } else if (auton == 1) {
    red_right();
  } else if (auton == 2) {
    blue_left(); 
  } else if (auton == 3) {
    blueRight();
  } else if (auton == 4) {
    autoSkills();
  } else if (auton == 5)
    test();
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
  Brain.Screen.clearScreen();
  Brain.Screen.setFont(mono60);
  Brain.Screen.setCursor(2.5, 1);
  Brain.Screen.print("393W");   

  bool newL1 = false;
  bool newL2 = false;
  bool newR1 = false;
  bool newR2 = false;

  while (1) {
    
    // chassis
    int forward = controller1.Axis3.position();
    int turn = controller1.Axis1.position();
    l.spin(fwd, to_volt(forward + turn), volt);
    r.spin(fwd, to_volt(forward - turn), volt);

    // intake

    if (controller1.ButtonL1.pressing()) {
      newL1 = true;
    } else {
      newL1 = false;
    }

    if (controller1.ButtonL2.pressing()) {
      newL2 = true;
    } else {
      newL2 = false;
    }
    
    // lift
    if (((controller1.ButtonL1.pressing() && newL2 || (newL1 && controller1.ButtonL2.pressing())) || ((newL1 && newL2) || (controller1.ButtonL1.pressing()) && (controller1.ButtonL2.pressing())))) {
      lift.spin(fwd, 6, volt);
      move_intake(0);
    // } else if (((controller1.ButtonR1.pressing() && newR2 || (newR1 && controller1.ButtonR2.pressing())) || ((newR1 && newR2) || (controller1.ButtonR1.pressing()) && (controller1.ButtonR2.pressing())))) {
    //   lift.spin(fwd, -6, volt);
    //   move_intake(0);
    //   doinker.set(false);
    } else if (controller1.ButtonL1.pressing()) {
      move_intake(12);
    } else if (controller1.ButtonL2.pressing()) {
      move_intake(-12);
    } else {
      move_intake(0);
      lift.stop(hold);
    } 

    if (controller1.ButtonA.pressing()) {
      move_lift(0, 100);
    } else if (controller1.ButtonX.pressing()) {
      move_lift(115, 100);
    } else if (controller1.ButtonY.pressing()) {
      move_lift(635, 100);
    }

    wait(20, msec);
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  controller1.ButtonR1.pressed(mogo_control);
  controller1.ButtonR2.pressed(doinker_control);

  // controller1.ButtonA.pressed(lift_reset);
  // controller1.ButtonX.pressed(lift_grab);
  // controller1.ButtonY.pressed(lift_score);

  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}