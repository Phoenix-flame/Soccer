#include <Network/Debugger.h>
#include <Core/Log.h>

namespace Phoenix{
    Ref<UDPSocket> Debugger::s_Sock;
    AI_Debug Debugger::s_Packet;
    char Debugger::s_OutgoingArray[1000];

    void Debugger::AddFloat(std::string name, float value){
        VariableData *data = s_Packet.add_variables();
        data->set_name(name);
        data->set_value(value);
    }

    void Debugger::Flush(){
        s_Packet.set_frame_id(100);
        std::string content;
        s_Packet.SerializeToArray(s_OutgoingArray, s_Packet.ByteSize());
        try{
            s_Sock->sendTo(s_OutgoingArray, s_Packet.ByteSize(), "224.5.23.16", 10007);
        }catch(std::exception const& e){
            PHX_CORE_CRITICAL(e.what());
        }
        s_Packet.Clear();
    }
}