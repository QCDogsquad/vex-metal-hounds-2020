#include "common.h"
#include "tyler_utilities.h"
#include "robot_utilities.h"

global robot_config_state GlobalRobotConfig;

using namespace pros;
using namespace pros::literals;

const char *const autonomous_selector_button_map[] = {"Auto 1", "Auto 2", ""};
const char *alliance_selector_button_map[6] = {"Blue", "\n", "Skills", "\n", "Red", ""};

lv_res_t alliance_selector_action(lv_obj_t *object, const char *ButtonName)
{
    if (strcmp(ButtonName, "Blue") == 0)
    {
        GlobalRobotConfig.Alliance = Alliance_Blue;
    }
    else if (strcmp(ButtonName, "Skills") == 0)
    {
        GlobalRobotConfig.Alliance = Alliance_Skills;
    }
    else if (strcmp(ButtonName, "Red") == 0)
    {
        GlobalRobotConfig.Alliance = Alliance_Red;
    }
    else 
    {
        // TODO(Tyler): Determine the proper return value
        return -1;
    }
    
    return LV_RES_OK;
}

void initialize()
{ 
    GlobalRobotConfig.Alliance = Alliance_Red;
    
#if 0    
    char *LeftPath = (char*)DEPLOY_PATH "path_left.csv";
    char *RightPath = (char*)DEPLOY_PATH "path_right.csv";
    PublicAutonomousRobotPath = ReadPathFromCsv(LeftPath, RightPath);
#endif
}

void competition_initialize()
{
}

void disabled()
{
}