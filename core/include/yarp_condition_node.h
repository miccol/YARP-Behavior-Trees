#ifndef YARPCONDITIONNODE_H
#define YARPCONDITIONNODE_H

#include <condition_node.h>
#include <yarp/os/Network.h>
#include <yarp/os/Port.h>
#include <stdio.h>
#include <BTCmd.h>

namespace BT
{
class YARPConditionNode : public BT::ConditionNode
{
public:
    YARPConditionNode(std::string name, std::string server_name);
    ~YARPConditionNode();
    BT::ReturnStatus Tick();
    void Finalize();

private:
    yarp::os::Network yarp_;
    yarp::os::Port port_;
    const char* client_name_;
    const char* server_name_;
   BTCmd condition_server_;

};
}

#endif
