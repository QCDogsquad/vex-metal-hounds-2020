#if 1
#include <memory>

#include "common.h"

using namespace okapi::literals;

void
opcontrol()
{
    while(true)
    {
        // TODO(Tyler): Should the inputs maybe be squared?
        f64 Forward = controller_get_analog(E_CONTROLLER_MASTER, ANALOG_LEFT_Y);
        f64 Yaw = controller_get_analog(E_CONTROLLER_MASTER, ANALOG_LEFT_X);
        PublicDriveChassis->getModel()->arcade(Forward/127, Yaw/127);
        
        if(controller_get_digital(CONTROLLER_MASTER, 
                                  DIGITAL_R1))
        {
            motor_move_velocity(CLAW_OPEN_MOTOR, 200);
        }
        else if(controller_get_digital(CONTROLLER_MASTER, DIGITAL_R2))
        {
            motor_move_velocity(CLAW_OPEN_MOTOR, -200);
        }
        else
        {
            motor_move_velocity(CLAW_OPEN_MOTOR, 0);
        }
        
        if(controller_get_digital(CONTROLLER_MASTER,
                                  DIGITAL_L1))
        {
            motor_move_velocity(CLAW_WRIST_MOTOR, 50);
        }
        else if(controller_get_digital(CONTROLLER_MASTER, 
                                       DIGITAL_L2))
        {
            motor_move_velocity(CLAW_WRIST_MOTOR, -50);
        }
        else 
        {
            motor_move_velocity(CLAW_WRIST_MOTOR, 0);
        }
        
        f64 LiftMotion = ((f64)controller_get_analog(CONTROLLER_MASTER, ANALOG_RIGHT_Y))/127.0f;
        motor_move_velocity(LEFT_LIFT_MOTOR, -LiftMotion*100);
        motor_move_velocity(RIGHT_LIFT_MOTOR, LiftMotion*100);
        
        motor_move(1, Forward+Yaw);
        motor_move(2, -Forward+Yaw);
        f64 LeftMotorVelocity = motor_get_actual_velocity(1);
        f64 RightMotorVelocity = -motor_get_actual_velocity(2);
        controller_print(CONTROLLER_MASTER, 0, 0, "%f %f", LeftMotorVelocity, RightMotorVelocity);
        
        pros::Task::delay(10);
    }
}

#else   

#include "common.h"

void
opcontrol() 
{
    auto PidTuner = okapi::PidTunerFactory::create();
}

#endif
