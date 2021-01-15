#include <iostream>
#include <Core/Log.h>
#include <Vision/Vision.h>
#include <Core/Config.h>
#include <Game/Game.h>
#include <Network/Debugger.h>
#include <Network/GrSim.h>
#include <Tools/Timer.h>

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
        PHX_SCOPE_TIMER("MainLoop")
        {
            PHX_SCOPE_TIMER("Vision Receive Packet")
            vision.ReceivePacket();
        }

        {
            PHX_SCOPE_TIMER("GrSim Command")
            grsim.SendCommand({3, 0.0, 0.0, 0.0, 0.0, 0.0});
        }

        {
            PHX_SCOPE_TIMER("Flush")
            Phoenix::Debugger::Flush();
            grsim.FlushCommands();
        }
    }

    return 0;
}