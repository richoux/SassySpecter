#pragma once

#include "Common.h"
#include "MicroManager.h"

class SassySpecterBot;

class RangedManager: public MicroManager
{
public:

    RangedManager(SassySpecterBot & bot);
    void    executeMicro(const std::vector<Unit> & targets);
    void    assignTargets(const std::vector<Unit> & targets);
    int     getAttackPriority(const Unit & rangedUnit, const Unit & target);
    Unit    getTarget(const Unit & rangedUnit, const std::vector<Unit> & targets);
};
