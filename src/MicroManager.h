#pragma once

#include "Common.h"
#include "SquadOrder.h"
#include "Unit.h"

class SassySpecterBot;

class MicroManager
{
    std::vector<Unit> m_units;

protected:

    SassySpecterBot & m_bot;
    SquadOrder order;

    virtual void executeMicro(const std::vector<Unit> & targets) = 0;
    void trainSubUnits(const Unit & unit) const;

public:

    MicroManager(SassySpecterBot & bot);

    const std::vector<Unit> & getUnits() const;

    void setUnits(const std::vector<Unit> & u);
    void execute(const SquadOrder & order);
    void regroup(const CCPosition & regroupPosition) const;

};