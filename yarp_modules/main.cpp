#include <iostream>
#include <yarp/os/Network.h>
#include <yarp/os/Time.h>
#include <bt_yarp_module.h>
#include <blackboard.h>
#include <blackboard_server.h>

int main(int argc, char * argv[])
{
        yarp::os::Network yarp;
        BlackBoardServer bb_server;
        yarp::os::Port port;
        bb_server.yarp().attachAsServer(port);
        if (!port.open("/blackboardserver")) { return 1; }
        while (true) {
            printf("Server running happily\n");
            yarp::os::Time::delay(10);
        }
        port.close();
        return 0;
}
