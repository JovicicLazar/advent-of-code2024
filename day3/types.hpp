#pragma once

// part1 enum
enum class States {
    START,
    HAS_M,
    HAS_U,
    HAS_L,
    OPENB,
    NUM1,
    COMMA,
    NUM2
};

// part2 enums

enum class GlobalStates {
    MAKE_DO,
    MAKE_DONT,
    MAKE_MUL,
    UNKNOWN
};

enum class StatesWithChecks {
    // mul(x,y)
    START,
    HAS_M,
    HAS_U,
    HAS_L,
    NUM1,
    COMMA,
    NUM2,

    // do()
    HAS_D,
    HAS_O,

    // don't()
    HAS_N,
    HAS_SQ,
    HAS_T,

    // ( bcs on ) we need to break the "building" process
    OPENBR
};