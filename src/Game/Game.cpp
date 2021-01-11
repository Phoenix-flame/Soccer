#include <Game/Game.h>
#include <Core/Config.h>

namespace Phoenix{
    Ref<Robot> Game::ourGK;
    Ref<Robot> Game::oppGK;

    Game::Game(){
        ourGK = CreateRef<Robot>(Config::s_GameConfig.ourGK);
        oppGK = CreateRef<Robot>(Config::s_GameConfig.oppGK);
    }
}