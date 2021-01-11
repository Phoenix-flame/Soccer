#pragma once
#include <lua5.1/lua.hpp>
#include <string>
#include <vector>

#define getString(name) getValue<std::string>(L, name)
#define getInt(name) getValue<int>(L, name)
#define getFloat(name) getValue<float>(L, name)
#define getBool(name) getValue<bool>(L, name)

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
        std::vector<bool> enabled_cam;
    };
    struct GameConfig{
        int numOurRobots;
        int numOppRobots;
        int ourGK;
        int oppGK;
        bool ourColor;
    };


    class Config{
    public:
        Config();
        ~Config() = default;

        static VisionConfig s_VisionConfig;
        static GameConfig s_GameConfig;
    };
}