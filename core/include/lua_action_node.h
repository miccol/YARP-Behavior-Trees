#ifndef LUA_ACTION_NODE_H
#define LUA_ACTION_NODE_H
#include "action_node.h"
extern "C" {
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
private:
    std::string filename_;
    lua_State *lua_state_;
};
}
#endif // LUA_ACTION_NODE_H
