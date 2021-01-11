#include <Core/Config.h>
#include <Core/Log.h>
namespace Phoenix{
    VisionConfig Config::s_VisionConfig;
    GameConfig Config::s_GameConfig;
    Config::Config(){
        lua_State *L;
        L = luaL_newstate();
        luaL_openlibs(L);
        if (luaL_loadfile(L, "scripts/config.lua")) {
            PHX_CORE_CRITICAL("Something went wrong loading the chunk (syntax error?)");
            PHX_CORE_CRITICAL("{0}", lua_tostring(L, -1));
            lua_pop(L,1);
            lua_close(L);
            exit(-1);
        }

        if (lua_pcall(L,0, LUA_MULTRET, 0)) {
            PHX_CORE_CRITICAL("Something went wrong during execution");
            PHX_CORE_CRITICAL("{0}", lua_tostring(L, -1));
            lua_pop(L,1);
        }


        s_VisionConfig.ip = getValue<std::string>(L, "vision_ip");
        s_VisionConfig.port = getValue<int>(L, "vision_port");
        for(unsigned int i = 0 ; i < getValue<int>(L, "vision_num_cam"); i++){
            s_VisionConfig.enabled_cam.push_back(getValue<bool>(L, "vision_camera" + std::to_string(i + 1)));
        }

        s_GameConfig.numOurRobots = getValue<int>(L, "game_numOurRobots");
        s_GameConfig.numOppRobots = getValue<int>(L, "game_numOppRobots");
        s_GameConfig.ourGK = getValue<int>(L, "game_ourGK");
        s_GameConfig.oppGK = getValue<int>(L, "game_oppGK");
        s_GameConfig.ourColor = getValue<bool>(L, "game_ourcolor");
        
        lua_close(L);

    }
}