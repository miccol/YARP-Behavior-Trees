#include "lua_action_node.h"
extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}



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

  //  lua_sethook(lua_state_, &BT::LuaActionNode::LineHookFunc, LUA_MASKLINE, 0);



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
    set_lua_script_done(true);


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

        if(lua_return)
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
    set_status(BT::HALTED);
    while (!lua_script_done());
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

bool BT::LuaActionNode::lua_script_done()
{
    std::lock_guard<std::mutex> LockGuard(lua_script_done_mutex_);

    return lua_script_done_;
}

void BT::LuaActionNode::set_lua_script_done(bool lua_script_done)
{
    std::lock_guard<std::mutex> LockGuard(lua_script_done_mutex_);
    lua_script_done_ = lua_script_done;
}

int BT::LuaActionNode::lua_is_halted(lua_State* L)
{
    lua_pushboolean(L, is_halted());
    return 1; //number of returning values
}



void BT::LuaActionNode::LineHookFunc(lua_State *L, lua_Debug *ar)
{
    if(ar->event == LUA_HOOKLINE)
        if(is_halted() == true)
            luaL_error(L, "HALTED");
}
