#ifndef PYTHON_ACTION_NODE_H
#define PYTHON_ACTION_NODE_H
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
    // bool lua_script_done();
    // void set_lua_script_done(bool lua_script_done);

    // int lua_is_halted(lua_State *L);
    // void LineHookFunc(lua_State *L, lua_Debug *ar);

    // void LuaWriteToBlackboard(lua_State* L, std::string name, std::string type, yarp::os::Value value);

private:
    std::string filename_;
    //lua_State *lua_state_;
    bool lua_script_done_;
    std::mutex lua_script_done_mutex_;
    BlackBoardCmd* blackboard_cmd_;
};
}
#endif // LUA_ACTION_NODE_H
