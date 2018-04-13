#ifndef PYTHON_ACTION_NODE_H
#define PYTHON_ACTION_NODE_H

#include "action_node.h"

#include <mutex>
#include <blackboard.h>
#include <yarp/os/Value.h>
#include <yarp/os/Property.h> // the blackboard is a yarp property



namespace BT
{

class PythonActionNode : public BT::ActionNode
{
public:
    PythonActionNode(std::string name, std::string filename, yarp::os::Property* blackboard_ptr = NULL);
    ~PythonActionNode();
    BT::ReturnStatus Tick();
    void Finalize();
    void SomeFunction();
    void Halt();




private:
    std::string filename_;
    //lua_State *lua_state_;
    //PyObject* python_state_;
    // PyObject* python_tick_fn_;
    void WriteOnBlackboard(std::string key, yarp::os::Value value);
    yarp::os::Value ReadFromBlackboard(std::string key);
    yarp::os::Property* blackboard_ptr_;
    bool lua_script_done_;
    std::mutex lua_script_done_mutex_;
    // BlackBoardCmd* blackboard_cmd_;
};
}
#endif // PYTHON_ACTION_NODE_H
