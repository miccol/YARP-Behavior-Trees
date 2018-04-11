#ifndef PYTHON_CONDITION_NODE_H
#define PYTHON_CONDITION_NODE_H
#include "condition_node.h"
#include <mutex>
#include <blackboard.h>
#include <yarp/os/Value.h>
#include <yarp/os/Property.h> // the blackboard is a yarp property



namespace BT
{

class PythonConditionNode : public BT::ConditionNode
{
public:
    PythonConditionNode(std::string name, std::string filename, yarp::os::Property* blackboard = NULL);
    ~PythonConditionNode();
    BT::ReturnStatus Tick();
    void Finalize();
    // bool lua_script_done();
    // void set_lua_script_done(bool lua_script_done);

    // int lua_is_halted(lua_State *L);
    // void LineHookFunc(lua_State *L, lua_Debug *ar);

    // void LuaWriteToBlackboard(lua_State* L, std::string name, std::string type, yarp::os::Value value);

private:
    std::string filename_;
    //PyObject* python_state_;
    // PyObject* python_tick_fn_;
    // BlackBoardCmd* blackboard_cmd_;
};
}
#endif // PYTHON_CONDITION_NODE_H
