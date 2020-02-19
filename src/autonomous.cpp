#include "common.h"

path PublicAutonomousRobotPath;

internal void 
FollowPath(path *Path)
{
    local_constant f64 ConversionFactor = 0.8 * ((60*12)/(4.5*PI));
    for(u32 Index = 0; 
        Index < Path->PointCount;
        Index++)
    {
        path_point *Point = &Path->Points[Index];
        printf("Here %f,%f!\n", Point->LeftWheelVel, Point->RightWheelVel);
        motor_move_velocity(LEFT_DRIVE_MOTOR, ConversionFactor*Point->LeftWheelVel);
        motor_move_velocity(RIGHT_DRIVE_MOTOR, -ConversionFactor*Point->RightWheelVel);
        pros::Task::delay(10);
    }
    motor_move_velocity(LEFT_DRIVE_MOTOR, 0.0);
    motor_move_velocity(RIGHT_DRIVE_MOTOR, 0.0);
}

void 
autonomous()
{
    printf("Autonomous Start!\n");
    //FollowPath(&PublicAutonomousRobotPath);
    
    motor_move_velocity(LEFT_DRIVE_MOTOR, 200.0);
    motor_move_velocity(RIGHT_DRIVE_MOTOR, -200.0);
    pros::Task::delay(500);
    motor_move_velocity(LEFT_DRIVE_MOTOR, -200.0);
    motor_move_velocity(RIGHT_DRIVE_MOTOR, 200.0);
    pros::Task::delay(200);
    motor_move_velocity(LEFT_DRIVE_MOTOR, 0.0);
    motor_move_velocity(RIGHT_DRIVE_MOTOR, 0.0);
    
    printf("Autonomous End!\n");
}
