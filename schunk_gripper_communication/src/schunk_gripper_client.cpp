#include "ros/ros.h"
#include "schunk_gripper_communication/schunk_gripper.h"
#include <cstdlib>
#include <stdlib.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "schunk_gripper_client");
    
        if (argc != 2){
            ROS_INFO("usage: schunk_gripper_client  *motor value*");
            return 1;
        }
    
    //setenv("PYTHONPATH",".",1);
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<schunk_gripper_communication::schunk_gripper>("set_gripper");

    schunk_gripper_communication::schunk_gripper srv;
    srv.request.motorvalue = atof(argv[1]);
    
    //ROS_INFO("input: %s %s %f",srv.request.pythonfile, srv.request.pythonfunction,(double)srv.request.motorvalue);

    if (client.call(srv)){
        ROS_INFO("Motor value set to: %f",(double)srv.response.motorvalue);
    }else{
        ROS_ERROR("Failed to set motor value");
        return 1;
    }

    return 0;

}
