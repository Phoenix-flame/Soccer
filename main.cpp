#include <iostream>
#include <Core/Log.h>
#include <Vision/Vision.h>

int main(){
    Phoenix::Log::Init();
    PHX_CORE_INFO("Let's Rock");
    Phoenix::Vision vision;
    while(true){
        vision.ReceivePacket();
    }

    return 0;
}