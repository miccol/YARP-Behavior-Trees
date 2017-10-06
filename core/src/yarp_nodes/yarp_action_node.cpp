/* Copyright (C) 2015-2017 Michele Colledanchise - All Rights Reserved
*
*   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
*   to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
*   and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
*   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
*   WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <yarp_nodes/yarp_action_node.h>
#include <string>
using namespace yarp::os;

BT::YARPActionNode::YARPActionNode(std::string name, std::string server_name) : BT::ActionNode::ActionNode(name)
{
    std::string client_name_ = "/" + name;
    port_.open(client_name_);

    std::cout << "Waiting for the module port name "<< server_name << " to start." << std::endl;

    yarp_.sync("/" + server_name + "/cmd");//waits for the port
    if(!yarp_.connect(client_name_, "/" + server_name + "/cmd"))
    {
       std::cout << "Error! Could not connect to module " << server_name << std::endl;
       return;
    }

    BTCmd action_server;

    action_server_ = action_server;
    std::cout << "Module "<< server_name << " has started." << std::endl;

    action_server_.yarp().attachAsClient(port_);


    std::cout << "Module "<< server_name << " attached." << std::endl;


}
BT::YARPActionNode::~YARPActionNode() {}



BT::ReturnStatus BT::YARPActionNode::Tick()
{


    int status = action_server_.request_tick();

    switch(status)
    {
    case 0:
        return BT::SUCCESS;
        break;
    case 1:
        return BT::FAILURE;
        break;
    default:
        return BT::RUNNING;
    }
}

void BT::YARPActionNode::Halt()
{
    action_server_.request_halt();
}
