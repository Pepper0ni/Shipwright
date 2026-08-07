#include "soh/Enhancements/AdultMasks.h"
#include "soh/Enhancements/game-interactor/GameInteractor.h"
#include "soh/Enhancements/randomizer/SeedContext.h"
#include "soh/cvar_prefixes.h"

extern "C" {
#include "z64.h"
#include "variables.h"
}

// rando's Masks as Adult setting forces the enhancement on, as logic may require it
bool Ship_MasksEquippableAsAdult() {
    if (IS_RANDO && RAND_GET_OPTION(RSK_MASKS_AS_ADULT)) {
        return true;
    }
    return CVarGetInteger(CVAR_ENHANCEMENT("AdultMasks"), 0) || CVarGetInteger(CVAR_CHEAT("TimelessEquipment"), 0);
}
