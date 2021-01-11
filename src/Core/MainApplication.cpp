#include <Core/MainApplication.h>


namespace ssl{
    void MyClient::RunSSL(){
        while(true){
            m_Vision->ReceivePacket();
        }
    }
}