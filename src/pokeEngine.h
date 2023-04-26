#include <string>
#include "typedef.h"
#include "pokenums.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
f32 naturePerStat(i16 nature, i16 stat)
{
    f32 retval = 1.0f;
    if (nature%5==stat-1)retval+=0.1f; 
    if ((nature>4)+(nature>9)+(nature>14)+(nature>19)==stat-1)retval-=0.1f;   
    return retval;  
}

struct species
{
    string name = "MissingNo.";
    u16 speciesID = 0x0000;
    u8 type1 = Types::NONE;
    u8 type2 = Types::NONE;
    u16 baseStats[6] = {50, 50, 50, 50, 50, 50};
    u16 abilites[2] = {0x0000, 0x0000};
    u8 expGroup = ExpGroup::MEDFAST;
    u8 baseFriendship = 90;
    u8 catchRate = 190;
    u16 expYield = 60;
    u8 EVYieldType = Stat::HP;
    u8 EVYield = 0;
    u8 genderSplit = 255;//if gendersplit is 255, all pokemon are unknown, if randnum above  then male if below female
    u8 evoLevel = 0;// if set to 0, pokemon never evolves by leveling
    species* evoPtr;// ptr to the pokemon species evolved into. is reservation for null mon
};

struct pokemon
{
    u16 speciesID;
    species* speciesPtr;
    string name = (*speciesPtr).name;
    string OT = "None"; // may remove, None if uncaught
    i8 gender = -1;
    u16 abilityID = 0x0000;
    u8 level = 1;
    u8 levelCaught = 0; // 0 if uncaught
    u8 friendship = (*speciesPtr).baseFriendship;
    u32 exp = 0;
    bool (*ability)(bool);
    //parameter bool is set high for relevence test and return is relevance
    u16 currentHP;
    u8 status;
    u16 stats[6];
    u8 EVs[6] = {0, 0, 0, 0, 0, 0};
    u8 IVs[6] = {0, 0, 0, 0, 0, 0};// 0-31
    u8 nature = Nature::SERIOUS;
    bool isEgg;
    bool isShiny;
    void (*updateStats)(pokemon*);//should technically belong to species.
};

string stringifyPokemon(pokemon* pokeref)
{
    pokemon& poke = *pokeref;
    return "Species: " + (*(poke.speciesPtr)).name + "\n"
    + "Name: " + poke.name + "\nOT: " + poke.OT + "\n"
    + "Gender: " + ((poke.gender)?((poke.gender == -1)?"N/A":"\u2642"):"\u2640")+"\n"
    + "Level: " + to_string(poke.level) + "\nEXP: " + to_string(poke.exp) + "\n"
    + "Stats:\n\tHP: " + to_string(poke.stats[Stat::HP]) +"\n\tAttack: " + to_string(poke.stats[Stat::ATTACK])
    + "\n\tDefence: " + to_string(poke.stats[Stat::DEFENCE]) + "\n\tSp. Attack: " + to_string(poke.stats[Stat::SPATTACK])
    + "\n\tSp. Defence: " + to_string(poke.stats[Stat::SPDEFENCE]) + "\n\tSpeed: " + to_string(poke.stats[Stat::SPEED]) + "\n"
    + "IVs:\n\tHP: " + to_string(poke.IVs[Stat::HP]) +"\n\tAttack: " + to_string(poke.IVs[Stat::ATTACK])
    + "\n\tDefence: " + to_string(poke.IVs[Stat::DEFENCE]) + "\n\tSp. Attack: " + to_string(poke.IVs[Stat::SPATTACK])
    + "\n\tSp. Defence: " + to_string(poke.IVs[Stat::SPDEFENCE]) + "\n\tSpeed: " + to_string(poke.IVs[Stat::SPEED]) + "\n\n";

}

void genGender(pokemon* pokeref)
{
    pokemon& poke = (*pokeref);
    if ((*poke.speciesPtr).genderSplit == 255)
    {
        poke.gender = Gender::UNKNOWN;
        return;
    }
    u8 ranbyte = rand() % 255;
    poke.gender = ranbyte <= (*poke.speciesPtr).genderSplit;

}

void genIVs(pokemon* pokeref)
{
    pokemon& poke = (*pokeref);
    if(rand()%8192==4096)
    {
        poke.isShiny = true;
        poke.IVs[Stat::HP] = 31;
        poke.IVs[Stat::ATTACK] = 31;
        poke.IVs[Stat::DEFENCE] = 31;
        poke.IVs[Stat::SPATTACK] = 31;
        poke.IVs[Stat::SPDEFENCE] = 31;
        poke.IVs[Stat::SPEED] = 31;
    }
    else{
        poke.IVs[Stat::HP] = rand() % 32;
        poke.IVs[Stat::ATTACK] = rand() % 32;
        poke.IVs[Stat::DEFENCE] = rand() % 32;
        poke.IVs[Stat::SPATTACK] = rand() % 32;
        poke.IVs[Stat::SPDEFENCE] = rand() % 32;
        poke.IVs[Stat::SPEED] = rand() % 32;
    }
}
void genNature(pokemon* pokeref)
{
    (*pokeref).nature = rand() %(Nature::LAST+1);
}

void basicUpdateStats(pokemon* pokeref)
{
    pokemon& poke = *pokeref;
    poke.stats[Stat::HP] = floor(((2*(*poke.speciesPtr).baseStats[Stat::HP] + poke.IVs[Stat::HP]+(poke.EVs[Stat::HP]/4))*poke.level)/100)+poke.level+10;
    for(int i = 1; i <= Stat::LAST; i++)
    {
        poke.stats[i] = floor(((((2*(*poke.speciesPtr).baseStats[i] + poke.IVs[i]+floor(poke.EVs[i]/4))*poke.level)/100)+5)*naturePerStat(poke.nature,i));
    }
}

u32 queryMinExp(pokemon* pokeref)
{
    pokemon& poke = *pokeref;
    switch ((*poke.speciesPtr).expGroup)
    {
        case ExpGroup::FAST:
            return 4/5*pow(poke.level, 3);
            break;
        case ExpGroup::MEDFAST:
            return pow(poke.level, 3);
            break;
        case ExpGroup::MEDSLOW:
            return ((6/5.0)*pow(poke.level, 3))-15*pow(poke.level, 2)+(100*poke.level)-140;
            break;
        case ExpGroup::SLOW:
            return 5/4*pow(poke.level, 3);
            break;
        default:
            return pow(poke.level, 3);
            break;
    }
}
void updateMinExp(pokemon* pokeref)
{
    (*pokeref).exp = queryMinExp(pokeref);
}

u8 queryLevel(pokemon* pokeref)
{
    pokemon& poke = *pokeref;
    switch ((*poke.speciesPtr).expGroup)
    {
        case ExpGroup::FAST:
            return floor(cbrt(poke.exp*5/4));
            break;
        case ExpGroup::MEDFAST:
            return floor(cbrt(poke.exp));
            break;
        case ExpGroup::MEDSLOW:
            for(u8 i = 100;;i--){if(poke.exp >= (6/5.0)*pow(i, 3)-15*pow(i, 2)+100*i-140)return i;}
            break;
        case ExpGroup::SLOW:
            return floor(cbrt(poke.exp*4/5));
            break;
        default:
            return floor(cbrt(poke.exp));
            break;
    }
}

void updateLevel(pokemon* pokeref)
{
    (*pokeref).level = queryLevel(pokeref);
}
void forceLevelUp(pokemon* pokeref)
{
    pokemon& poke = *pokeref;
    poke.level++;
    updateMinExp(&poke);
    basicUpdateStats(&poke);
}

void populatePtrs(pokemon* pokeref, species** specarray)
{
    (*pokeref).speciesPtr = specarray[(*pokeref).speciesID];
}

f32 typeEfficacy(u8 movtype1, u8 movtype2, u8 tartype1, u8 tartype2 )
{
    u8 movtypes[] = {movtype1, movtype2};
    u8 tartypes[] = {tartype1, tartype2};
    f32 retval = 1.0f;
    for (u8 i = 0; i < 2; i++)
    {
        for (u8 n = 0; n < 2; n++)
        {
            switch (movtypes[i])
            {
                case Types::NORMAL:
                    switch (tartypes[n])
                    {
                        case Types::ROCK: case Types::STEEL:
                            retval*=0.5f;
                            break;
                        case Types::GHOST:
                            retval*=0.0f;
                            break;
                    }
                    break;

                case Types::FIRE:
                    switch (tartypes[n])
                    {
                        case Types::GRASS:case Types::ICE:case Types::BUG:case Types::STEEL:
                            retval*=2.0f;
                            break;
                        case Types::FIRE:case Types::WATER:case Types::ROCK:case Types::DRAGON:
                            retval*=0.5f;
                            break;
                    }
                    break;

                case Types::WATER:
                    switch(tartypes[n])
                    {
                        case Types::FIRE:case Types::GROUND:case Types::ROCK:
                            retval*=2.0f;
                            break;
                        case Types::WATER:case Types::GRASS:case Types::DRAGON:
                            retval*=0.5f;
                            break;
                    }
                    break;

                case Types::GRASS:
                    switch(tartypes[n])
                    {
                        case Types::WATER:case Types::GROUND:case Types::ROCK:
                            retval*=2.0f;
                            break;
                        case Types::FIRE:case Types::GRASS:case Types::POISON:case Types::FLYING:case Types::BUG:case Types::DRAGON:case Types::STEEL:
                            retval*=0.5f;
                            break;
                    }
                    break;

                case Types::ELECTRIC:
                    switch(tartypes[n])
                    {
                        case Types::WATER:case Types::FLYING:
                            retval*=2.0f;
                            break;
                        case Types::GRASS:case Types::ELECTRIC:case Types::DRAGON:
                            retval*=0.5f;
                            break;
                        case Types::GROUND:
                            retval*=0.0f;
                            break;
                    }
                    break;

                case Types::ICE:
                    switch(tartypes[n])
                    {
                        case Types::GRASS:case Types::GROUND:case Types::FLYING:case Types::DRAGON:
                            retval*=2.0f;
                            break;
                        case Types::FIRE:case Types::WATER:case Types::ICE:case Types::STEEL:
                            retval*=0.5f;
                            break;
                    }
                    break;
            }
        }
    }
    return retval;
}
