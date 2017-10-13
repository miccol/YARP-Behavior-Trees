#ifndef LUA_ACTION_NODE_H
#define LUA_ACTION_NODE_H
#include "action_node.h"
#include <mutex>
extern "C"
{
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

namespace BT
{

class LuaActionNode : public BT::ActionNode
{
public:
    LuaActionNode(std::string name, std::string filename, lua_State *lua_state);
    ~LuaActionNode();
    BT::ReturnStatus Tick();
    void Halt();
    bool lua_script_done();
    void set_lua_script_done(bool lua_script_done);

    int lua_is_halted(lua_State *L);
    void LineHookFunc(lua_State *L, lua_Debug *ar);
private:
    std::string filename_;
    lua_State *lua_state_;
    bool lua_script_done_;
    std::mutex lua_script_done_mutex_;
};
}
#endif // LUA_ACTION_NODE_H
