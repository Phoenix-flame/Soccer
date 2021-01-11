#include <iostream>
#include <Phoenix/core/log.h>
#include <Core/MainApplication.h>

int main(int argc, char** argv){
    Phoenix::Log::Init();
    PHX_INFO("Phoenix flame");
    ssl::MyClient app;
    app.Run();

    return 0;
}