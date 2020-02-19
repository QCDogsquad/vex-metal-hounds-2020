#if 1
#include <memory>

#include "common.h"

using namespace okapi::literals;

void
opcontrol()
{
    okapi::ChassisControllerBuilder ChassisBuilder = okapi::ChassisControllerBuilder();
    ChassisBuilder.withMotors(LEFT_DRIVE_MOTOR, -RIGHT_DRIVE_MOTOR);
    ChassisBuilder.withDimensions(okapi::AbstractMotor::gearset::green, 
                                  {{4_in, 11_in}, okapi::imev5GreenTPR});
    
    auto DriveChassis = ChassisBuilder.build();
    
    //~ Setup motors
    motor_set_brake_mode(LEFT_LIFT_MOTOR, E_MOTOR_BRAKE_HOLD);
    motor_set_brake_mode(RIGHT_LIFT_MOTOR, E_MOTOR_BRAKE_HOLD);
    
    motor_set_brake_mode(CLAW_OPEN_MOTOR, E_MOTOR_BRAKE_HOLD);
    motor_set_brake_mode(CLAW_WRIST_MOTOR, E_MOTOR_BRAKE_HOLD);
    
    while(true)
    {
        // TODO(Tyler): Should the inputs maybe be squared?
        f64 Forward = controller_get_analog(E_CONTROLLER_MASTER, ANALOG_LEFT_Y);
        f64 Yaw = controller_get_analog(E_CONTROLLER_MASTER, ANALOG_LEFT_X);
        DriveChassis->getModel()->arcade(Forward/127, Yaw/127);
        
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
            motor_move_velocity(CLAW_WRIST_MOTOR, 25);
        }
        else if(controller_get_digital(CONTROLLER_MASTER, 
                                       DIGITAL_L2))
        {
            motor_move_velocity(CLAW_WRIST_MOTOR, -25);
        }
        else 
        {
            motor_move_velocity(CLAW_WRIST_MOTOR, 0);
        }
        
        f64 LiftMotion = controller_get_analog(CONTROLLER_MASTER, ANALOG_RIGHT_Y);
        motor_move_velocity(LEFT_LIFT_MOTOR, -LiftMotion);
        motor_move_velocity(RIGHT_LIFT_MOTOR, LiftMotion);
        
        motor_move(1, Forward+Yaw);
        motor_move(2, -Forward+Yaw);
        f64 LeftMotorVelocity = motor_get_actual_velocity(1);
        f64 RightMotorVelocity = -motor_get_actual_velocity(2);
        controller_print(CONTROLLER_MASTER, 0, 0, "%f %f", LeftMotorVelocity, RightMotorVelocity);
        pros::Task::delay(100);
    }
    
}

#else   

#include "common.h"


using namespace pros;
using namespace pros::c;
using namespace pros::literals;

// NOTE(Tyler): Under no circumstance is okapi to be included!!!
using namespace okapi::literals;

internal inline u8
TruncateF64ToU8(f64 Value)
{
    u8 Result = (u8)Value;
    return(Result);
}

internal inline u8
F64ToFixedPoint4(f64 Value)
{
    u8 Result = TruncateF64ToU8(Value*pow(2, 4));
    return(Result);
}

internal inline void
MotorSetPidConstants(u8 Port, 
                     f64 PConstant, f64 IConstant, f64 DConstant)
{
    motor_set_pos_pid(Port, {
                          .kf = 0,
                          .kp = F64ToFixedPoint4(PConstant), 
                          .ki = F64ToFixedPoint4(IConstant), 
                          .kd = F64ToFixedPoint4(DConstant)});
}

void 
opcontrol()
{
    local_constant u32 TEST_MOTOR = 1;
    
    f64 Step = 0.01;
    f64 PConstant = 0.0;
    f64 IConstant = 0.0;
    f64 DConstant = 0.0;
    while(true)
    {
        motor_pid_full_s_t MotorPid = motor_get_pos_pid(TEST_MOTOR);
        
        if(controller_get_digital(CONTROLLER_MASTER,
                                  DIGITAL_X))
        {
            PConstant += Step;
        }
        else if(controller_get_digital(CONTROLLER_MASTER, DIGITAL_Y))
        {
            PConstant -= Step;
        }
        
        if(controller_get_digital(CONTROLLER_MASTER, 
                                  DIGITAL_UP))
        {
            IConstant += Step;
        }
        else if(controller_get_digital(CONTROLLER_MASTER, 
                                       DIGITAL_DOWN))
        {
            IConstant -= Step;
        }
        
        if(controller_get_digital(CONTROLLER_MASTER, 
                                  DIGITAL_L1))
        {
            DConstant += Step;
        }
        else if(controller_get_digital(CONTROLLER_MASTER, 
                                       DIGITAL_L2))
        {
            DConstant -= Step;
        }
        
        if(controller_get_digital(CONTROLLER_MASTER,
                                  DIGITAL_R1))
        {
            motor_move_absolute(TEST_MOTOR, 2000, 200);
        }
        else if(controller_get_digital(CONTROLLER_MASTER,
                                       DIGITAL_R2))
        {
            motor_move_absolute(TEST_MOTOR, 25, 200);
        }
        
        if(controller_get_digital(CONTROLLER_MASTER,
                                  DIGITAL_RIGHT))
        {
            Step = 1.0;
        }
        else
        {
            Step = 0.01;
        }
        
        printf("P=%f, I=%f, D=%f\n", PConstant, IConstant, DConstant);
        MotorSetPidConstants(TEST_MOTOR, 
                             PConstant, IConstant, DConstant);
        
        pros::Task::delay(100);
    }
    
}

#endif
