#include "pokeEngine.h"
namespace Species
{
    enum Species
    {
        MISSINGNO = 0x0000,
        KALIP = 0x0007,
        KALIPUTT = 0x0008,
        KALIPROUD = 0x0009
    };
}
void genSpecArray(species specarray[256])
{
    species MissingNo;
    specarray[Species::MISSINGNO] = MissingNo;
    //Fire Bug
    //Grass Fighting
    //species Kalip;
    specarray[Species::KALIP].name = "Kalip";
    specarray[Species::KALIP].speciesID = 0x0007;
    specarray[Species::KALIP].type1 = Types::WATER;
    specarray[Species::KALIP].type2 = Types::NONE;
    specarray[Species::KALIP].baseStats[Stat::HP] = 55;
    specarray[Species::KALIP].baseStats[Stat::ATTACK] = 40;
    specarray[Species::KALIP].baseStats[Stat::DEFENCE] = 50;
    specarray[Species::KALIP].baseStats[Stat::SPATTACK] = 50;
    specarray[Species::KALIP].baseStats[Stat::SPDEFENCE] = 60;
    specarray[Species::KALIP].baseStats[Stat::SPEED] = 50;
    specarray[Species::KALIP].expGroup = ExpGroup::MEDSLOW;
    //specarray[Species::KALIP].abilities = {}
    specarray[Species::KALIP].baseFriendship = 50;
    specarray[Species::KALIP].catchRate = 45;
    specarray[Species::KALIP].genderSplit = 223;
    specarray[Species::KALIP].evoLevel = 17;
    specarray[Species::KALIP].expYield = 60;
    specarray[Species::KALIP].EVYieldType = Stat::SPDEFENCE;
    specarray[Species::KALIP].EVYield = 1;

    specarray[Species::KALIPUTT].name = "Kaliputt";
    specarray[Species::KALIPUTT].speciesID = 0x0008;
    specarray[Species::KALIPUTT].type1 = Types::WATER;
    specarray[Species::KALIPUTT].type2 = Types::ROCK;
    specarray[Species::KALIPUTT].baseStats[Stat::HP] = 75;
    specarray[Species::KALIPUTT].baseStats[Stat::ATTACK] = 54;
    specarray[Species::KALIPUTT].baseStats[Stat::DEFENCE] = 68;
    specarray[Species::KALIPUTT].baseStats[Stat::SPATTACK] = 68;
    specarray[Species::KALIPUTT].baseStats[Stat::SPDEFENCE] = 81;
    specarray[Species::KALIPUTT].baseStats[Stat::SPEED] = 68;
    specarray[Species::KALIPUTT].expGroup = ExpGroup::MEDSLOW;
    //specarray[Species::KALIPUTT].abilities = {}
    specarray[Species::KALIPUTT].baseFriendship = 50;
    specarray[Species::KALIPUTT].catchRate = 45;
    specarray[Species::KALIPUTT].genderSplit = 223;
    specarray[Species::KALIPUTT].evoLevel = 36;
    specarray[Species::KALIPUTT].expYield = 145;
    specarray[Species::KALIPUTT].EVYieldType = Stat::SPDEFENCE;
    specarray[Species::KALIPUTT].EVYield = 2;
//
    specarray[Species::KALIP].evoPtr  = &specarray[Species::KALIPUTT];
//


    species Kaliproud;
    specarray[Species::KALIPROUD].name = "Kaliproud";
    specarray[Species::KALIPROUD].speciesID = 0x0009;
    specarray[Species::KALIPROUD].type1 = Types::WATER;
    specarray[Species::KALIPROUD].type2 = Types::ROCK;
    specarray[Species::KALIPROUD].baseStats[Stat::HP] = 96;
    specarray[Species::KALIPROUD].baseStats[Stat::ATTACK] = 69;
    specarray[Species::KALIPROUD].baseStats[Stat::DEFENCE] = 87;
    specarray[Species::KALIPROUD].baseStats[Stat::SPATTACK] = 87;
    specarray[Species::KALIPROUD].baseStats[Stat::SPDEFENCE] = 104;
    specarray[Species::KALIPROUD].baseStats[Stat::SPEED] = 87;
    specarray[Species::KALIPROUD].expGroup = ExpGroup::MEDSLOW;
    //specarray[Species::KALIPROUD].abilities = {}
    specarray[Species::KALIPROUD].baseFriendship = 50;
    specarray[Species::KALIPROUD].catchRate = 45;
    specarray[Species::KALIPROUD].genderSplit = 223;
    specarray[Species::KALIPROUD].evoLevel = 0;
    specarray[Species::KALIPROUD].expYield = 238;
    specarray[Species::KALIPROUD].EVYieldType = Stat::SPDEFENCE;
    specarray[Species::KALIPROUD].EVYield = 3;

    //
    specarray[Species::KALIPUTT].evoPtr = &specarray[Species::KALIPROUD];
    //
} 