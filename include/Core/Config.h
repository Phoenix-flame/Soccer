#pragma once
#include <lua5.1/lua.hpp>
#include <string>
#include <vector>
namespace ssl{


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
        std::vector<bool> enabled_cam;
    };
    class Config{
    public:
        Config();
        ~Config() = default;

        static VisionConfig s_VisionConfig;
    };
}