#ifndef YARPACTIONNODE_H
#define YARPACTIONNODE_H

#include <action_node.h>
#include <yarp/os/Network.h>
#include <yarp/os/Port.h>
#include <BTCmd.h>


namespace BT
{
class YARPActionNode : public BT::ActionNode
{
public:
    YARPActionNode(std::string name, std::string server_name);
    ~YARPActionNode();
    BT::ReturnStatus Tick();
    void Halt();
    void Finalize();

private:
    yarp::os::Network yarp_;
    yarp::os::Port port_tick_;
    yarp::os::Port port_halt_;
    const char* client_name_;
    const char* server_name_;

    BTCmd action_tick_server_;
    BTCmd action_halt_server_;


};
}

#endif
