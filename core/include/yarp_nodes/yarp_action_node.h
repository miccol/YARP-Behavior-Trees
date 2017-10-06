#ifndef YARPACTIONNODE_H
#define YARPACTIONNODE_H

#include <action_node.h>
#include <yarp/os/all.h>
#include <stdio.h>
#include <btyarpmodule.h>

using namespace yarp::os;


namespace BT
{
class YARPActionNode : public BT::ActionNode
{
public:
    YARPActionNode(std::string name, std::string server_name);
    ~YARPActionNode();
    BT::ReturnStatus Tick();
    void Halt();

private:
    Network yarp_;
    yarp::os::Port port_;
    const char* client_name_;
    const char* server_name_;
    BTCmd action_server_;


};
}

#endif
