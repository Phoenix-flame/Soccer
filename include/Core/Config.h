#pragma once
#include <lua5.1/lua.hpp>
#include <Core/Log.h>
#include <string>
namespace Phoenix{


    template<typename T>
    T getValue(lua_State *L, std::string name){
        lua_getglobal(L, name.c_str());
        if  constexpr (std::is_same<T, std::string>::value){
            T val = lua_tostring(L, -1);
            lua_pop(L, 1);
            return val;
        }
        else if constexpr (std::is_same<T, bool>::value){
            T val = lua_toboolean(L, -1);
            lua_pop(L, 1);
            return val;
        }
        else{
            T val = lua_tonumber(L, -1);
            lua_pop(L, 1);
            return val;
        }

       
    }

    struct VisionConfig{
        std::string ip;
        int port; 
    };
    class Config{
    public:
        Config();
        ~Config() = default;

        static VisionConfig s_VisionConfig;
    };
}