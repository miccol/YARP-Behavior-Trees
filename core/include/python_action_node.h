#ifndef PYTHON_ACTION_NODE_H
#define PYTHON_ACTION_NODE_H
//#include <Python.h>

#include "action_node.h"

#include <mutex>
#include <BlackBoardCmd.h>
#include <yarp/os/Value.h>



namespace BT
{

class PythonActionNode : public BT::ActionNode
{
public:
    PythonActionNode(std::string name, std::string filename, BlackBoardCmd* blackboard_cmd = NULL);
    ~PythonActionNode();
    BT::ReturnStatus Tick();
    void Finalize();

    void Halt();





private:
    std::string filename_;
    //lua_State *lua_state_;
    //PyObject* python_state_;
    // PyObject* python_tick_fn_;
    bool lua_script_done_;
    std::mutex lua_script_done_mutex_;
    BlackBoardCmd* blackboard_cmd_;
};
}
#endif // PYTHON_ACTION_NODE_H
