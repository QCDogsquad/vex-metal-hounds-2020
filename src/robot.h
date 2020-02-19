
//~
#include "robot_utilities.h"

enum alliance {
    Alliance_Blue,
    Alliance_Skills,
    Alliance_Red,
};

struct robot_config_state {
    alliance Alliance;
};

extern path PublicAutonomousRobotPath;

#define LEFT_DRIVE_MOTOR 19
#define RIGHT_DRIVE_MOTOR 18
#define CLAW_OPEN_MOTOR 13
#define CLAW_WRIST_MOTOR 6 
#define LEFT_LIFT_MOTOR 20
#define RIGHT_LIFT_MOTOR 13

using namespace pros;
using namespace pros::c;
using namespace pros::literals;