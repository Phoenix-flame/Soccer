#pragma once
#include <Game/Robot.h>
#include <Core/Base.h>

int main();

namespace Phoenix{
    
    class Vision;
    class Game{
    public:
        Game();
    private:
        static Ref<Robot> ourGK;
        static Ref<Robot> oppGK;
    private:
        friend int ::main();
        friend class Vision;
    };
}