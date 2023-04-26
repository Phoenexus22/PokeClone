#include<iostream>
#include "pokeEngine.h"
#include "specieslist.h"
using namespace std;
int main()
{
    srand(time(0));
    species alakazam;
    alakazam.name = "Alakazam";
    alakazam.speciesID = 0x0003;
    alakazam.type1 = Types::PSYCHIC;
    alakazam.type2 = Types::NONE;
    alakazam.baseStats[Stat::HP] = 55;
    alakazam.baseStats[Stat::ATTACK] = 50;
    alakazam.baseStats[Stat::DEFENCE] = 45;
    alakazam.baseStats[Stat::SPATTACK] = 135;
    alakazam.baseStats[Stat::SPDEFENCE] = 95;
    alakazam.baseStats[Stat::SPEED] = 120;
    //alakazam.abilities;
    alakazam.expGroup = ExpGroup::MEDSLOW;
    alakazam.baseFriendship = 50;
    alakazam.catchRate = 50;
    alakazam.genderSplit = 191;

    pokemon neddy = {0x0003, &alakazam};
    neddy.level = 100;
    updateMinExp(&neddy);
    genGender(&neddy);
    genIVs(&neddy);
    genNature(&neddy);
    basicUpdateStats(&neddy);
    cout << stringifyPokemon(&neddy);
}