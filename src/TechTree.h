#pragma once

#include "Common.h"
#include "UnitType.h"

class SassySpecterBot;
class MetaType;

struct TypeData
{
    CCRace                  race{};
    int                     mineralCost     = 0;      // mineral cost of the item
    int                     gasCost         = 0;          // gas cost of the item
    int                     supplyCost      = 0;       // supply cost of the item
    int                     buildTime       = 0;        // build time of the item
    bool                    isUnit          = false;
    bool                    isBuilding      = false;
    bool                    isWorker        = false;
    bool                    isRefinery      = false;
    bool                    isSupplyProvider= false;
    bool                    isResourceDepot = false;
    bool                    isAddon         = false;
#ifdef SC2API
    sc2::AbilityID          buildAbility    = 0;     // the ability that creates this item
    sc2::AbilityID          warpAbility     = 0;      // the ability that creates this item via warp-in
#endif
    std::vector<UnitType>   whatBuilds;       // any of these units can build the item
    std::vector<UnitType>   requiredUnits;    // owning ONE of these is required to make
    std::vector<CCUpgrade>  requiredUpgrades; // having ALL of these is required to make
};

class TechTree
{
    SassySpecterBot & m_bot;
    std::map<UnitType, TypeData>  m_unitTypeData;
    std::map<CCUpgrade, TypeData> m_upgradeData;

    void initUnitTypeData();
    void initUpgradeData();

    void outputJSON(const std::string & filename) const;

public:

    TechTree(SassySpecterBot & bot);
    void onStart();

    const TypeData & getData(const UnitType & type) const;
    const TypeData & getData(const CCUpgrade & type) const;
    const TypeData & getData(const MetaType & type) const;

    inline bool is_building( const sc2::UnitTypeData& type ) const { return std::find( type.attributes.begin(), type.attributes.end(), sc2::Attribute::Structure ) != type.attributes.end(); }
    inline bool is_worker(const sc2::UnitTypeData& type) const 
    { 
      return ( type.unit_type_id == sc2::UNIT_TYPEID::TERRAN_SCV 
        || type.unit_type_id == sc2::UNIT_TYPEID::PROTOSS_PROBE 
        || type.unit_type_id == sc2::UNIT_TYPEID::ZERG_DRONE ); 
    }
    
    inline bool is_refinery( const sc2::UnitTypeData& type ) const 
    {
      return ( type.unit_type_id == sc2::UNIT_TYPEID::TERRAN_REFINERY || type.unit_type_id == sc2::UNIT_TYPEID::TERRAN_REFINERYRICH
        || type.unit_type_id == sc2::UNIT_TYPEID::PROTOSS_ASSIMILATOR || type.unit_type_id == sc2::UNIT_TYPEID::PROTOSS_ASSIMILATORRICH
        || type.unit_type_id == sc2::UNIT_TYPEID::ZERG_EXTRACTOR || type.unit_type_id == sc2::UNIT_TYPEID::ZERG_EXTRACTORRICH );
     }

    inline bool is_resource_depot( const sc2::UnitTypeData& type ) const
    {
      return ( type.unit_type_id == sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER || type.unit_type_id == sc2::UNIT_TYPEID::TERRAN_COMMANDCENTERFLYING
        || type.unit_type_id == sc2::UNIT_TYPEID::PROTOSS_NEXUS
        || type.unit_type_id == sc2::UNIT_TYPEID::ZERG_HATCHERY || type.unit_type_id == sc2::UNIT_TYPEID::ZERG_LAIR || type.unit_type_id == sc2::UNIT_TYPEID::ZERG_HIVE );
    }

    inline sc2::AbilityID what_ability_to_be_warped( const sc2::UnitTypeData& type ) const
    {
      switch( type.unit_type_id.ToType )
      {
      case sc2::UNIT_TYPEID::PROTOSS_ZEALOT:
        return sc2::ABILITY_ID::TRAINWARP_ZEALOT;
      case sc2::UNIT_TYPEID::PROTOSS_SENTRY:
        return sc2::ABILITY_ID::TRAINWARP_SENTRY;
      case sc2::UNIT_TYPEID::PROTOSS_STALKER:
        return sc2::ABILITY_ID::TRAINWARP_STALKER;
      case sc2::UNIT_TYPEID::PROTOSS_HIGHTEMPLAR:
        return sc2::ABILITY_ID::TRAINWARP_HIGHTEMPLAR;
      case sc2::UNIT_TYPEID::PROTOSS_DARKTEMPLAR:
        return sc2::ABILITY_ID::TRAINWARP_DARKTEMPLAR;
      case sc2::UNIT_TYPEID::PROTOSS_ADEPT:
        return sc2::ABILITY_ID::TRAINWARP_ADEPT;
      default:
        return 0;
      }
    }
};