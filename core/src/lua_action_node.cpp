#include "lua_action_node.h"

BT::LuaActionNode::LuaActionNode(std::string name, std::string filename, lua_State *lua_state) : BT::ActionNode::ActionNode(name)
{
    filename_ = filename;
    lua_state_ = lua_state;

}

BT::ReturnStatus BT::LuaActionNode::Tick()
{

    // create new Lua state
    //lua_State *lua_state;
    //lua_state = luaL_newstate();

    // load Lua libraries

    static const luaL_Reg lualibs[] =
    {
        { "base", luaopen_base },
        { NULL, NULL}
    };

    const luaL_Reg *lib = lualibs;
    for(; lib->func != NULL; lib++)
    {
        lib->func(lua_state_);
        lua_settop(lua_state_, 0);
    }


    lua_createtable(lua_state_, 1, 0);

    // run the Lua script
    luaL_dofile(lua_state_, filename_.c_str());
    bool lua_return = lua_toboolean(lua_state_, lua_gettop(lua_state_));

    // if the return is not a boolean, the Lua script returned somethig else, either nil (error in the return value)
    //or a generic error message
    if(!lua_isboolean(lua_state_,lua_gettop(lua_state_)))
    {
        if(lua_isnil(lua_state_,lua_gettop(lua_state_)))
        {
            std::cout << "invalid return value" << std::endl;
        }
        else
        {
            std::cout  << lua_tostring(lua_state_, lua_gettop(lua_state_)) << std::endl;
        }
        std::cout << "Something went wrong in" << get_name() << std::endl;

        return BT::FAILURE;
    }
    else
    {

        if(true)//lua_return)
        {
            return BT::SUCCESS;
        }
        else
        {
            return BT::FAILURE;
        }
    }

}

void BT::LuaActionNode::Halt()
{

}
