namespace Gender
{
    enum Gender 
    {
        MALE = 0,
        FEMALE = 1,
        UNKNOWN = -1
    };
}

namespace Stat
{
    enum Stat
    {
        HP,
        ATTACK,
        DEFENCE,
        SPATTACK,
        SPDEFENCE,
        SPEED,

        FIRST = HP,
        LAST = SPEED
    };
}

namespace Nature
{
    enum Nature
    {
        //+ATTACK
        HARDY,//-ATTACK
        LONELY,//-DEFENCE
        ADAMANT,//-SPATTACK
        NAUGHTY,//-SPDEFENCE
        BRAVE,//-SPEED

        //+DEFENCE
        BOLD,//-ATTACK
        DOCILE,//-DEFENCE
        IMPISH,//-SPATTACK
        LAX,//-SPDEFENCE
        RELAXED,//-SPEED

        //+SPATTACK
        MODEST,//-ATTACK
        MILD,//-DEFENCE
        BASHFUL,//-SPATTACK
        RASH,//-SPDEFENCE
        QUIET,//-SPEED

        //+SPDEFENCE
        CALM,//-ATTACK
        GENTLE,//-DEFENCE
        CAREFUL,//-SPATTACK
        QUIRKY,//-SPDEFENCE
        SASSY,//-SPEED

        //+SPEED
        TIMID,//-ATTACK
        HASTY,//-DEFENCE
        JOLLY,//-SPATTACK
        NAIVE,//-SPDEFENCE
        SERIOUS,//-SPEED

        FIRST = HARDY,
        LAST = SERIOUS
    };
}

namespace Status{
    enum Status
    {
        NONE,
        SLP1,
        SLP2,
        SLP3,
        PSN,
        BRN,
        FRZ,
        PAR,
        BADPSN
    };
}

namespace Types{
    enum Types
    {
        NONE,
        NORMAL,
        FIRE,
        WATER,
        GRASS,
        ELECTRIC,
        ICE,
        FIGHTING,
        POISON,
        GROUND,
        FLYING,
        PSYCHIC,
        BUG,
        ROCK,
        GHOST,
        DRAGON,
        DARK,
        STEEL,
        FAIRY
    };
}

namespace MoveType
{
    enum MoveType
    {
        PHYSICAL,
        SPECIAL,
        STATUS
    };
}

namespace ExpGroup
{
    enum ExpGroup
    {
        FAST,
        MEDFAST,
        MEDSLOW,
        SLOW
    };
}