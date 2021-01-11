#include <iostream>
#include <Core/Log.h>
#include <Vision/Vision.h>
#include <Core/Config.h>
#include <Game/Game.h>
int main(){
    Phoenix::Log::Init();
    PHX_CORE_INFO("Let's Rock");
    Phoenix::Config config;
    Phoenix::Vision vision;
    Phoenix::Game game;
    while(true){
        vision.ReceivePacket();
        Phoenix::Game::ourGK->Debug();
    }

    return 0;
}