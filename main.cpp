#include <iostream>
#include <Core/Log.h>
#include <Vision/Vision.h>
#include <Core/Config.h>
int main(){
    Phoenix::Log::Init();
    PHX_CORE_INFO("Let's Rock");
    Phoenix::Config config;
    Phoenix::Vision vision;
    while(true){
        vision.ReceivePacket();
    }

    return 0;
}