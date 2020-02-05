#include "SassySpecterBot.h"
#include "Util.h"

SassySpecterBot::SassySpecterBot()
    : m_map(*this)
    , m_bases(*this)
    , m_unitInfo(*this)
    , m_workers(*this)
    , m_gameCommander(*this)
    , m_strategy(*this)
    , m_techTree(*this)
{
    
}

void SassySpecterBot::OnGameStart() 
{
    m_config.readConfigFile();

    // add all the possible start locations on the map
#ifdef SC2API
    for (auto & loc : Observation()->GetGameInfo().enemy_start_locations)
    {
        m_baseLocations.push_back(loc);
    }
    m_baseLocations.push_back(Observation()->GetStartLocation());
#else
    for (auto & loc : BWAPI::Broodwar->getStartLocations())
    {
        m_baseLocations.push_back(BWAPI::Position(loc));
    }

    for( int = 0; i < (int)m_baseLocations.size() ; ++i )
      if (m_baseLocations[i] == GetStartLocation())
      {
        mainBaseIndex = i;
        break;
      }

    // set the BWAPI game flags
    BWAPI::Broodwar->setLocalSpeed(m_config.SetLocalSpeed);
    BWAPI::Broodwar->setFrameSkip(m_config.SetFrameSkip);
    
    if (m_config.CompleteMapInformation)
    {
        BWAPI::Broodwar->enableFlag(BWAPI::Flag::CompleteMapInformation);
    }

    if (m_config.UserInput)
    {
        BWAPI::Broodwar->enableFlag(BWAPI::Flag::UserInput);
    }
#endif
    
    setUnits();
    m_techTree.onStart();
    m_strategy.onStart();
    m_map.onStart();
    m_unitInfo.onStart();
    m_bases.onStart();
    m_workers.onStart();

    m_gameCommander.onStart();
}

void SassySpecterBot::OnStep()
{
    setUnits();
    m_map.onFrame();
    m_unitInfo.onFrame();
    m_bases.onFrame();
    m_workers.onFrame();
    m_strategy.onFrame();

    m_gameCommander.onFrame();

#ifdef SC2API
    Debug()->SendDebug();
#endif
}

void SassySpecterBot::setUnits()
{
    m_allUnits.clear();
#ifdef SC2API
    Control()->GetObservation();
    for (auto & unit : Observation()->GetUnits())
    {
        m_allUnits.push_back(Unit(unit, *this));    
    }
#else
    for (auto & unit : BWAPI::Broodwar->getAllUnits())
    {
        m_allUnits.push_back(Unit(unit, *this));
    }
#endif
}

CCRace SassySpecterBot::GetPlayerRace(int player) const
{
#ifdef SC2API
    auto playerID = Observation()->GetPlayerID();
    for (auto & playerInfo : Observation()->GetGameInfo().player_info)
    {
        if (playerInfo.player_id == playerID)
        {
            return playerInfo.race_actual;
        }
    }

    BOT_ASSERT(false, "Didn't find player to get their race");
    return sc2::Race::Random;
#else
    if (player == Players::Self)
    {
        return BWAPI::Broodwar->self()->getRace();
    }
    else
    {
        return BWAPI::Broodwar->enemy()->getRace();
    }
#endif
}

BotConfig & SassySpecterBot::Config()
{
     return m_config;
}

const MapTools & SassySpecterBot::Map() const
{
    return m_map;
}

const StrategyManager & SassySpecterBot::Strategy() const
{
    return m_strategy;
}

const BaseLocationManager & SassySpecterBot::Bases() const
{
    return m_bases;
}

const UnitInfoManager & SassySpecterBot::UnitInfo() const
{
    return m_unitInfo;
}

int SassySpecterBot::GetCurrentFrame() const
{
#ifdef SC2API
    return (int)Observation()->GetGameLoop();
#else
    return BWAPI::Broodwar->getFrameCount();
#endif
}

const TypeData & SassySpecterBot::Data(const UnitType & type) const
{
    return m_techTree.getData(type);
}

const TypeData & SassySpecterBot::Data(const Unit & unit) const
{
    return m_techTree.getData(unit.getType());
}

const TypeData & SassySpecterBot::Data(const CCUpgrade & type) const
{
    return m_techTree.getData(type);
}

const TypeData & SassySpecterBot::Data(const MetaType & type) const
{
    return m_techTree.getData(type);
}

WorkerManager & SassySpecterBot::Workers()
{
    return m_workers;
}

int SassySpecterBot::GetCurrentSupply() const
{
#ifdef SC2API
    return Observation()->GetFoodUsed();
#else
    return BWAPI::Broodwar->self()->supplyUsed();
#endif
}

int SassySpecterBot::GetMaxSupply() const
{
#ifdef SC2API
    return Observation()->GetFoodCap();
#else
    return BWAPI::Broodwar->self()->supplyTotal();
#endif
}

int SassySpecterBot::GetMinerals() const
{
#ifdef SC2API
    return Observation()->GetMinerals();
#else
    return BWAPI::Broodwar->self()->minerals();
#endif
}

int SassySpecterBot::GetGas() const
{
#ifdef SC2API
    return Observation()->GetVespene();
#else
    return BWAPI::Broodwar->self()->gas();
#endif
}

Unit SassySpecterBot::GetUnit(const CCUnitID & tag) const
{
#ifdef SC2API
    return Unit(Observation()->GetUnit(tag), *(SassySpecterBot *)this);
#else
    return Unit(BWAPI::Broodwar->getUnit(tag), *(SassySpecterBot *)this);
#endif
}

const std::vector<Unit> & SassySpecterBot::GetUnits() const
{
    return m_allUnits;
}

CCPosition SassySpecterBot::GetStartLocation() const
{
#ifdef SC2API
    return Observation()->GetStartLocation();
#else
    return BWAPI::Position(BWAPI::Broodwar->self()->getStartLocation());
#endif
}

CCPosition SassySpecterBot::GetMainBaseLocation() const
{
  return m_baseLocations[ mainBaseIndex ]; 
}

const std::vector<CCPosition> & SassySpecterBot::GetStartLocations() const
{
    return m_baseLocations;
}

#ifdef SC2API
void SassySpecterBot::OnError(const std::vector<sc2::ClientError> & client_errors, const std::vector<std::string> & protocol_errors)
{
    
}
#endif