#pragma once
#include <Network/PracticalSocket.h>
#include <Core/Base.h>



namespace Phoenix{
    class GrSim{
    public:
        GrSim();
        void InitPosition();



    private:
        Ref<UDPSocket> m_Sock; 
        char s_OutgoingArray[1000];
    };
}