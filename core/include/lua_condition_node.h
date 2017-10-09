
#ifndef LUA_CONDITION_NODE_H
#define LUA_CONDITION_NODE_H
#include <condition_node.h>

extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}


namespace BT
{

class LuaConditionNode : public BT::ConditionNode
{
public:
    LuaConditionNode(std::string name, std::string filename, lua_State *lua_state);
    ~LuaConditionNode();
    BT::ReturnStatus Tick();
private:
    std::string filename_;
    lua_State *lua_state_;

};
}
#endif // LUA_CONDITION_NODE_H
