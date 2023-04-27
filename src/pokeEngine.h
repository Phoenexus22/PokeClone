#include "typedef.h"
#include "pokenums.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
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


typedef struct pokemon pokemon;
typedef struct battleMove battleMove;



struct battleMove
{
    string name = "MissingNo.";
    string description = "";
    u16 moveID = 0x0000;
    u8 type1 = Types::NONE;
    u8 type2 = Types::NONE;
    u8 power = 50;
    u8 PP = 20;
    u8 accuracy = 100;// 0 means always hits and ignores acc/evasion
    u8 moveType = MoveType::PHYSICAL;
    u8 statusEffect = Status::NONE;
    bool statusTargetOppo = true;
    u8 statChanged = Stat::SPEED;
    bool statTargetOppo = false;
    u8 effectChance = 0;//as percentage of 100
    u8 statusChance = 0;//as percentage of 100
    i8 priority = 0;// 0 is standard
    void (*use) (battleMove*, pokemon*, pokemon*);// this, user, target
    void (*use2) (battleMove*, pokemon*, pokemon*);// usually nothing - used for moves like giga drain
    bool makesContact = true;
};

struct pokemon// in battle pokemon have a
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
    battleMove* moves[4];
    u16 moveIDs[4] = {0x0000, 0x0000, 0x0000, 0x0000};
    u8 currentPP[4] = {0, 0, 0, 0};
    bool isEgg = false;
    bool isShiny = false;
    void (*updateStats)(pokemon);//should technically belong to species.
};

struct battlemon// must be destroyed after every battle
{
    pokemon* pokePtr;
    u8 confusionLevel = 0;//0 is not confused, anything abobe is number of turns
    i8 statStages[6] = {0, 0, 0, 0, 0, 0};//HP is not used, but this means the enums work
    i8& evasion = statStages[0];

};



string stringifyPokemon(pokemon& poke)
{
    return "Species: " + (*poke.speciesPtr).name + "\n"
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

void genGender(pokemon& poke)
{
    if ((*poke.speciesPtr).genderSplit == 255)
    {
        poke.gender = Gender::UNKNOWN;
        return;
    }
    u8 ranbyte = rand() % 255;
    poke.gender = ranbyte <= (*poke.speciesPtr).genderSplit;

}

void genIVs(pokemon& poke)
{
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
void genNature(pokemon& pokeref)
{
    pokeref.nature = rand() %(Nature::LAST+1);
}

void basicUpdateStats(pokemon& poke)
{
    poke.stats[Stat::HP] = floor(((2*(*poke.speciesPtr).baseStats[Stat::HP] + poke.IVs[Stat::HP]+(poke.EVs[Stat::HP]/4))*poke.level)/100)+poke.level+10;
    for(int i = 1; i <= Stat::LAST; i++)
    {
        poke.stats[i] = floor(((((2*(*poke.speciesPtr).baseStats[i] + poke.IVs[i]+floor(poke.EVs[i]/4))*poke.level)/100)+5)*naturePerStat(poke.nature,i));
    }
}

u32 queryMinExp(pokemon& poke)
{
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
void updateMinExp(pokemon& pokeref)
{
    pokeref.exp = queryMinExp(pokeref);
}

u8 queryLevel(pokemon& poke)
{
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

void updateLevel(pokemon& pokeref)
{
    pokeref.level = queryLevel(pokeref);
}
void forceLevelUp(pokemon& poke)
{
    poke.level++;
    updateMinExp(poke);
    basicUpdateStats(poke);
}

void populatePtrs(pokemon& pokeref, species specarray[])
{
    pokeref.speciesPtr = &specarray[pokeref.speciesID];
}

void evolve(pokemon& pokeref)
{
    species& evolution = *(*pokeref.speciesPtr).evoPtr;
    pokemon evolved = {evolution.speciesID, &evolution};
    evolved = pokeref;

    if (pokeref.name == (*pokeref.speciesPtr).name)
    {
        evolved.name = evolution.name;
    }
    evolved.speciesID = evolution.speciesID;
    evolved.speciesPtr = &evolution;
    pokeref = evolved;
    basicUpdateStats(pokeref);
    /*
    evolved.IVs[Stat::HP] = pokeref.IVs[Stat::HP];
    evolved.IVs[Stat::ATTACK] = pokeref.IVs[Stat::ATTACK];
    evolved.IVs[Stat::DEFENCE] = pokeref.IVs[Stat::DEFENCE];
    evolved.IVs[Stat::SPATTACK] = pokeref.IVs[Stat::SPATTACK];
    evolved.IVs[Stat::SPDEFENCE] = pokeref.IVs[Stat::SPDEFENCE];
    evolved.IVs[Stat::SPEED] = pokeref.IVs[Stat::SPEED];

    evolved.EVs[Stat::HP] = pokeref.EVs[Stat::HP];
    evolved.EVs[Stat::ATTACK] = pokeref.EVs[Stat::ATTACK];
    evolved.EVs[Stat::DEFENCE] = pokeref.EVs[Stat::DEFENCE];
    evolved.EVs[Stat::SPATTACK] = pokeref.EVs[Stat::SPATTACK];
    evolved.EVs[Stat::SPDEFENCE] = pokeref.EVs[Stat::SPDEFENCE];
    evolved.EVs[Stat::SPEED] = pokeref.EVs[Stat::SPEED];
    evolved.level = pokeref.level;
    evolved.levelCaught = pokeref.levelCaught;
    evolved.nature = pokeref.nature;*/
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
                        case Types::GRASS: case Types::ICE: case Types::BUG: case Types::STEEL:
                            retval*=2.0f;
                            break;
                        case Types::FIRE: case Types::WATER: case Types::ROCK: case Types::DRAGON:
                            retval*=0.5f;
                            break;
                    }
                    break;

                case Types::WATER:
                    switch(tartypes[n])
                    {
                        case Types::FIRE: case Types::GROUND: case Types::ROCK:
                            retval*=2.0f;
                            break;
                        case Types::WATER: case Types::GRASS: case Types::DRAGON:
                            retval*=0.5f;
                            break;
                    }
                    break;

                case Types::GRASS:
                    switch(tartypes[n])
                    {
                        case Types::WATER: case Types::GROUND: case Types::ROCK:
                            retval*=2.0f;
                            break;
                        case Types::FIRE: case Types::GRASS: case Types::POISON: case Types::FLYING: case Types::BUG: case Types::DRAGON: case Types::STEEL:
                            retval*=0.5f;
                            break;
                    }
                    break;

                case Types::ELECTRIC:
                    switch(tartypes[n])
                    {
                        case Types::WATER: case Types::FLYING:
                            retval*=2.0f;
                            break;
                        case Types::GRASS: case Types::ELECTRIC: case Types::DRAGON:
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
                        case Types::GRASS: case Types::GROUND: case Types::FLYING: case Types::DRAGON:
                            retval*=2.0f;
                            break;
                        case Types::FIRE: case Types::WATER: case Types::ICE: case Types::STEEL:
                            retval*=0.5f;
                            break;
                    }
                    break;

                case Types::FIGHTING:
                    switch(tartypes[n])
                    {
                        case Types::NORMAL: case Types::ICE: case Types::ROCK: case Types::DARK: case Types::STEEL:
                            retval*=2.0f;
                            break;
                        case Types::POISON: case Types::FLYING: case Types::PSYCHIC: case Types::BUG: case Types::FAIRY:
                            retval*=0.5f;
                            break;
                        case Types::GHOST:
                            retval*=0.0f;
                            break;
                    }
                    break;

                case Types::POISON:
                    switch (tartypes[n])
                    {
                        case Types::GRASS: case Types::FAIRY:
                            retval*=2.0f;
                            break;
                        case Types::POISON: case Types::GROUND: case Types::ROCK: case Types::GHOST:
                            retval*=0.5f;
                            break;
                        case Types::STEEL:
                            retval*=0.0f;
                            break;
                    }
                    break;

                case Types::GROUND:
                    switch(tartypes[n])
                    {
                        case Types::FIRE: case Types::ELECTRIC: case Types::POISON: case Types::ROCK: case Types::STEEL:
                            retval*=2.0f;
                            break;
                        case Types::GRASS: case Types::BUG:
                            retval*=0.5f;
                            break;
                        case Types::FLYING:
                            retval*=0.0f;
                            break;
                    }
                    break;
                
                case Types::FLYING:
                    switch(tartypes[n])
                    {
                        case Types::GRASS: case Types::FIGHTING: case Types::BUG:
                            retval*=2.0f;
                            break;
                        case Types::ELECTRIC: case Types::ROCK: case Types::STEEL:
                            retval*=0.5f;
                            break;
                    }
                    break;

                case Types::PSYCHIC:
                    switch(tartypes[n])
                    {
                        case Types::FIGHTING: case Types::POISON:
                            retval*=2.0f;
                            break;
                        case Types::PSYCHIC: case Types::STEEL:
                            retval*=0.5;
                            break;
                        case Types::DARK:
                            retval*=0.0f;
                            break;
                    }
                    break;
                
                case Types::BUG:
                    switch(tartypes[n])
                    {
                        case Types::GRASS: case Types::PSYCHIC: case Types::DARK:
                            retval*=2.0f;
                            break;
                        case Types::FIRE: case Types::FIGHTING: case Types::POISON: case Types::FLYING: case Types::GHOST: case Types::STEEL: case Types::FAIRY:
                            retval*=0.5f;
                            break;
                    }
                    break;

                case Types::ROCK:
                    switch(tartypes[n])
                    {
                        case Types::FIRE: case Types::ICE: case Types::FLYING: case Types::BUG: 
                            retval*=2.0f;
                            break;
                        case Types::FIGHTING: case Types::GROUND: case Types::STEEL:
                            retval*=0.5f;
                            break;
                    }
                    break;

                case Types::GHOST:
                    switch(tartypes[n])
                    {
                        case Types::PSYCHIC: case Types::GHOST: 
                            retval*=2.0f;
                            break;
                        case Types::DARK:
                            retval*=0.5f;
                            break;
                        case Types::NORMAL:
                            retval*=0.0f;
                            break;
                    }

                case Types::DRAGON:
                    switch (tartypes[n])
                    {
                        case Types::DRAGON:
                            retval*=2.0f;
                            break;
                        case Types::STEEL:
                            retval*=0.5f;
                            break;
                        case Types::FAIRY:
                            retval*=0.0f;
                            break;
                    }

                    break;
                case Types::DARK:
                    switch (tartypes[n])
                    {
                        case Types::PSYCHIC: case Types::GHOST:
                            retval*=2.0f;
                            break;
                        case Types::FIGHTING: case Types::DARK: case Types::FAIRY:
                            retval*=0.5f;
                            break;
                    }
                    break;

                case Types::STEEL:
                    switch (tartypes[n])
                    {
                        case Types::ICE: case Types::ROCK: case Types::FAIRY:
                            retval*=2.0f;
                            break;
                        case Types::FIRE: case Types::WATER: case Types::ELECTRIC: case Types::STEEL:
                            retval*=0.5f;
                            break;
                    }
                    break;
                
                case Types::FAIRY:
                    switch (tartypes[n])
                    {
                        case Types::FIGHTING: case Types::DRAGON: case Types::DARK:
                            retval*=2.0f;
                            break;
                        case Types::FIRE: case Types::POISON: case Types::STEEL:
                            retval*=0.5f;
                            break;
                    }
                    break;
            }
        }
    }
    return retval;
}
