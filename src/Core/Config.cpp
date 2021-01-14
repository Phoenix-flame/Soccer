#include <Core/Config.h>
#include <Core/Log.h>
namespace Phoenix{
    VisionConfig Config::s_VisionConfig;
    GameConfig Config::s_GameConfig;
    DebuggerConfig Config::s_DebuggerConfig;

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

        s_VisionConfig.ip = getString("vision_ip");
        s_VisionConfig.port = getInt("vision_port");
        for(unsigned int i = 0 ; i < getInt("vision_num_cam"); i++){
            s_VisionConfig.enabled_cam.push_back(getBool("vision_camera" + std::to_string(i + 1)));
        }

        s_DebuggerConfig.ip = getString("debugger_ip");
        s_DebuggerConfig.port = getInt("debugger_port");

        s_GameConfig.numOurRobots = getInt("game_numOurRobots");
        s_GameConfig.numOppRobots = getInt("game_numOppRobots");
        s_GameConfig.ourGK = getInt("game_ourGK");
        s_GameConfig.oppGK = getInt("game_oppGK");
        s_GameConfig.ourColor = getBool("game_ourcolor");
        
        lua_close(L);

    }
}