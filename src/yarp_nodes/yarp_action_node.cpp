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

BT::YARPActionNode::YARPActionNode(std::string name, const char *yarp_client_name, const char *yarp_server_name) : BT::ActionNode::ActionNode(name)
{

    port_.open(yarp_client_name);

    std::cout << "Waiting for the module port name "<< yarp_server_name << " to start." << std::endl;

    yarp_.sync(yarp_server_name);//waits for the port
    yarp_.connect(yarp_client_name, yarp_server_name);
    std::cout << "Module port name "<< yarp_server_name << " Started.+++++++++++++++++++++" << std::endl;

}
BT::YARPActionNode::~YARPActionNode() {}



BT::ReturnStatus BT::YARPActionNode::Tick()
{

    printf("YARP ticking the BT Action Module \n");

    Bottle cmd;
    cmd.addString("tick");
    Bottle response;
    port_.write(cmd,response);
    printf("YARP Action Got response: %s\n", response.toString().c_str());

    int status = response.pop().asInt();

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
    printf("YARP halting the BTModule \n");

    Bottle cmd;
    cmd.addString("halt");
    Bottle response;
    port_.write(cmd,response);
   set_status(BT::HALTED);
}
