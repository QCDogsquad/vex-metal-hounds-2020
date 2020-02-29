//~
#define LEFT_DRIVE_MOTOR 19
#define RIGHT_DRIVE_MOTOR 18
#define CLAW_OPEN_MOTOR 7
#define CLAW_WRIST_MOTOR 6 
#define LEFT_LIFT_MOTOR 20
#define RIGHT_LIFT_MOTOR 13

#define PATH_A "A"

using namespace pros;
using namespace pros::c;
using namespace pros::literals;
using namespace okapi::literals;

extern std::shared_ptr<okapi::ChassisController> PublicDriveChassis;
extern std::shared_ptr<okapi::AsyncMotionProfileController> PublicMotionProfileController;