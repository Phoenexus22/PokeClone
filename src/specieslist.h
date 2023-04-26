#include "pokeEngine.h"
void genSpecArray(species** specarray)
{
    species MissingNo;
    //Fire Bug
    //Grass Dark
    species Kalip;
    Kalip.name = "Kalip";
    Kalip.speciesID = 0x0007;
    Kalip.type1 = Types::WATER;
    Kalip.type2 = Types::NONE;
    Kalip.baseStats[Stat::HP] = 55;
    Kalip.baseStats[Stat::ATTACK] = 40;
    Kalip.baseStats[Stat::DEFENCE] = 50;
    Kalip.baseStats[Stat::SPATTACK] = 50;
    Kalip.baseStats[Stat::SPDEFENCE] = 60;
    Kalip.baseStats[Stat::SPEED] = 50;
    Kalip.expGroup = ExpGroup::MEDSLOW;
    //Kalip.abilities = {}
    Kalip.baseFriendship = 50;
    Kalip.catchRate = 45;
    Kalip.genderSplit = 223;
    Kalip.evoLevel = 17;
    Kalip.expYield = 60;
    Kalip.EVYieldType = Stat::SPDEFENCE;
    Kalip.EVYield = 1;

    species Kaliputt;
    Kaliputt.name = "Kaliputt";
    Kaliputt.speciesID = 0x0008;
    Kaliputt.type1 = Types::WATER;
    Kaliputt.type2 = Types::FAIRY;
    Kaliputt.baseStats[Stat::HP] = 75;
    Kaliputt.baseStats[Stat::ATTACK] = 54;
    Kaliputt.baseStats[Stat::DEFENCE] = 68;
    Kaliputt.baseStats[Stat::SPATTACK] = 68;
    Kaliputt.baseStats[Stat::SPDEFENCE] = 81;
    Kaliputt.baseStats[Stat::SPEED] = 68;
    Kaliputt.expGroup = ExpGroup::MEDSLOW;
    //Kaliputt.abilities = {}
    Kaliputt.baseFriendship = 50;
    Kaliputt.catchRate = 45;
    Kaliputt.genderSplit = 223;
    Kaliputt.evoLevel = 36;
    Kaliputt.expYield = 145;
    Kaliputt.EVYieldType = Stat::SPDEFENCE;
    Kaliputt.EVYield = 2;
//
    Kalip.evoPtr  = &Kaliputt;
//


    species Kaliproud;
    Kaliproud.name = "Kaliproud";
    Kaliproud.speciesID = 0x0009;
    Kaliproud.type1 = Types::WATER;
    Kaliproud.type2 = Types::FAIRY;
    Kaliproud.baseStats[Stat::HP] = 96;
    Kaliproud.baseStats[Stat::ATTACK] = 69;
    Kaliproud.baseStats[Stat::DEFENCE] = 87;
    Kaliproud.baseStats[Stat::SPATTACK] = 87;
    Kaliproud.baseStats[Stat::SPDEFENCE] = 104;
    Kaliproud.baseStats[Stat::SPEED] = 87;
    Kaliproud.expGroup = ExpGroup::MEDSLOW;
    //Kaliproud.abilities = {}
    Kaliproud.baseFriendship = 50;
    Kaliproud.catchRate = 45;
    Kaliproud.genderSplit = 223;
    Kaliproud.evoLevel = 0;
    Kaliproud.expYield = 238;
    Kaliproud.EVYieldType = Stat::SPDEFENCE;
    Kaliproud.EVYield = 3;
    //
    Kaliputt.evoPtr = &Kaliproud;
    //


    //species* specarray[256];
    specarray[0x0000] = &MissingNo;
    specarray[0x0007] = &Kalip;
    specarray[0x0008] = &Kaliputt;
    specarray[0x0009] = &Kaliproud;
} 