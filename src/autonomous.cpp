#include "common.h"

using namespace okapi::literals;

#if 0
void 
autonomous()
{
    printf("Autonomous Start!\n");
    
    MotionProfileController->setTarget(PATH_A);
    MotionProfileController->waitUntilSettled();
    
    printf("Autonomous End!\n");
}

#else

void
autonomous()
{
    printf("Autonomous Start!\n");
    
    PublicDriveChassis->moveDistance(-1_ft);
    PublicDriveChassis->moveDistance(1_ft);
    
    printf("Autonomous End!\n");
}

#endif
