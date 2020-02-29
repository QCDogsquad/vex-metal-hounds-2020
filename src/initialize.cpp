#include "common.h"

// NOTE(Tyler): Normally I would just use normal pointers, however
// okapi forces one to use "smart" pointers
std::shared_ptr<okapi::ChassisController> PublicDriveChassis;
std::shared_ptr<okapi::AsyncMotionProfileController> PublicMotionProfileController;

void initialize()
{ 
    //~ Setup motors
    motor_set_brake_mode(LEFT_LIFT_MOTOR, E_MOTOR_BRAKE_HOLD);
    motor_set_brake_mode(RIGHT_LIFT_MOTOR, E_MOTOR_BRAKE_HOLD);
    
    motor_set_brake_mode(CLAW_OPEN_MOTOR, E_MOTOR_BRAKE_HOLD);
    motor_set_brake_mode(CLAW_WRIST_MOTOR, E_MOTOR_BRAKE_HOLD);
    
    motor_set_gearing(LEFT_LIFT_MOTOR, E_MOTOR_GEARSET_36);
    motor_set_gearing(RIGHT_LIFT_MOTOR, E_MOTOR_GEARSET_36);
    motor_set_gearing(CLAW_WRIST_MOTOR, E_MOTOR_GEARSET_36);
    
    PublicDriveChassis = 
        (okapi::ChassisControllerBuilder()
         .withMotors(LEFT_DRIVE_MOTOR, -RIGHT_DRIVE_MOTOR)
         .withDimensions(okapi::AbstractMotor::gearset::green, 
                         {{4_in, 13.5_in}, okapi::imev5GreenTPR})
         // TODO(Tyler): Tune these values!!!
         .withGains({0.001, 0, 0.0001},
                    {0.001, 0, 0.0001},
                    {0.001, 0, 0.0001})
         .build());
    
    //~ Setup pathfinder
    // NOTE(Tyler): Setup is done here to avoid a delay during 
    // autonomous mode.
    PublicMotionProfileController = (okapi::AsyncMotionProfileControllerBuilder()
                                     .withLimits({0.25_mps, 0.5_mps, 2.5_mps})
                                     .withOutput(PublicDriveChassis)
                                     .buildMotionProfileController());
    
    PublicMotionProfileController
        ->generatePath({
                           {0_ft, 0_ft, 0_deg},
                           {9_in, 0_in, 0_deg},
                           {2_ft+8_in, 1_ft+3_in, 0_deg},
                       }, PATH_A);
}

void competition_initialize()
{
}

void disabled()
{
}