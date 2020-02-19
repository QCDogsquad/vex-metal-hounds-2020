#if !defined(ROBOT_UTILITIES_H)
#define ROBOT_UTILITIES_H

#include "tyler_utilities.h"

#define DEPLOY_PATH "/usd/"

struct path_point
{
    // NOTE(Tyler): Typically I would use f32 but as WPIlib uses
    // doubles, this is why f64 is being used instead
    f64 Heading; // This is the direction that the robot is facing
    f64 LeftWheelPos;
    f64 LeftWheelVel;
    f64 LeftWheelAcc;
    f64 RightWheelPos;
    f64 RightWheelVel;
    f64 RightWheelAcc;
};

struct path
{
    memory_index PointsSize;
    path_point *Points;
    u32 PointCount;
};

// NOTE(Tyler): This reads CSV files that are formatted: 
// POSITION, VELOCITY, ACCELERATION, HEADING
path ReadPathFromCsv(char *LeftCsvPath, char *RightCsvPath);

#endif
