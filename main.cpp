#include <iostream>
#include <Core/Log.h>
#include <Vision/Vision.h>
#include <Core/Config.h>
#include <Game/Game.h>
#include <Network/Debugger.h>
#include <Network/GrSim.h>
int main(){
    Phoenix::Log::Init();
    PHX_CORE_INFO("Let's Rock");
    Phoenix::Config config;
    Phoenix::Debugger debug;
    Phoenix::GrSim grsim;
    Phoenix::Vision vision;
    Phoenix::Game game;

    grsim.InitPosition();
    while(true){
        vision.ReceivePacket();
        Phoenix::Game::ourGK->Debug();
        Phoenix::Debugger::Flush();
    }

    return 0;
}