#ifndef YARPACTIONNODE_H
#define YARPACTIONNODE_H

#include <action_node.h>
#include <yarp/os/all.h>
#include <stdio.h>

using namespace yarp::os;


namespace BT
{
class YARPActionNode : public BT::ActionNode
{
public:
    YARPActionNode(std::string name, const char *yarp_client_name, const char *yarp_server_name);
    ~YARPActionNode();
    BT::ReturnStatus Tick();
    void Halt();

private:
    Network yarp_;
    RpcClient port_;
    const char* client_name_;
    const char* server_name_;


};
}

#endif
