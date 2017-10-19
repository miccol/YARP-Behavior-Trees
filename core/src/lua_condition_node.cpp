#include "lua_condition_node.h"

extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}



void looptable(lua_State *L1, lua_State* L2)

{
    //lua_createtable(L2, 0, 4);
    lua_newtable (L2);
    lua_pushglobaltable(L1);       // Get global table
    lua_pushnil(L1);               // put a nil key on stack
    while (lua_next(L1,-2) != 0) { // key(-1) is replaced by the next key(-1) in table(-2)
       // std::cout << lua_tostring(L1,-2) << std::endl;  // Get key(-2) name
        if (lua_isnumber(L1, -1))
        {
            std::cout << "is number" << std::endl;
            std::cout << lua_tostring(L1, -2) << " : " << lua_tonumber(L1, -1) << std::endl;
            lua_pushnumber(L2, lua_tonumber(L1, -1));
            lua_setglobal(L2, lua_tostring(L1, -2));
        }
        else if (lua_istable(L1, -1))
        {
//            std::cout << "is table" << std::endl;
//            std::cout << lua_tostring(L1, -2) << std::endl;
//            lua_pushstring(L2, lua_tostring(L1, -2));
//            lua_newtable(L2);
//            looptable(L1, L2);
//            lua_settable(L2, -3);
        }
        else if (lua_isboolean(L1, -1))
        {
            std::cout <<  lua_tostring(L1, -2)<< " is boolean. Value: "<<  lua_toboolean(L1, -1) << std::endl;
            std::cout << "Variable name set" << std::endl;
            lua_pushboolean(L2, lua_toboolean(L1, -1));
            lua_setglobal(L2, lua_tostring(L1, -2));
            std::cout << "Variable value set" << std::endl;
        }
        lua_pop(L1,1);               // remove value(-1), now key on top at(-1)
    }
    lua_pop(L1,1);
}





BT::LuaConditionNode::LuaConditionNode(std::string name, std::string filename, lua_State *lua_state) : BT::ConditionNode::ConditionNode(name)
{
    filename_ = filename;
    lua_state_ = lua_state;
}

BT::ReturnStatus BT::LuaConditionNode::Tick()
{

    // create new Lua state
    lua_State *lua_state ;



//    lua_state = lua_newthread(lua_state_);
    lua_state = luaL_newstate();
    luaL_openlibs(lua_state);

//    xcopy(lua_state_, lua_state,2);
    // load Lua libraries


    static const luaL_Reg lualibs[] =
    {
        { "base", luaopen_base },
        { NULL, NULL}
    };

    const luaL_Reg *lib = lualibs;
    for(; lib->func != NULL; lib++)
    {
        lib->func(lua_state);
        lua_settop(lua_state, 0);
    }


// lua_newtable(lua_state);
//    lua_pushnumber(lua_state, 10);
//   lua_setglobal(lua_state, "c");
//    lua_settable(lua_state, -3);
    //looptable(lua_state_, lua_state);

 looptable(lua_state_, lua_state);



    //    lua_settable(lua_state_, -3);
    //lua_setglobal(lua_state_, "arg");

    // run the Lua script
    luaL_dofile(lua_state, filename_.c_str());

    // close the Lua state
    bool lua_return = lua_toboolean(lua_state, lua_gettop(lua_state));
    // if the return is not a boolean, the Lua script returned somethig else, either nil (error in the return value)
    //or a generic error message
    if(!lua_isboolean(lua_state,lua_gettop(lua_state)))
    {
        if(lua_isnil(lua_state,lua_gettop(lua_state)))
        {
            std::cout << "ERROR: The script " << get_name()  << " returned NIL "<< std::endl;
        }
        else
        {
            std::cout  << lua_tostring(lua_state, lua_gettop(lua_state)) << std::endl;
        }
        std::cout << "Something went wrong in" << get_name() << std::endl;
        lua_close(lua_state);
        return BT::FAILURE;
    }


    lua_close(lua_state);

    if(lua_return)
    {
        return BT::SUCCESS;
    }
    else
    {
        return BT::FAILURE;
    }

}



