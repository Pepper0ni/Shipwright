#include "soh/Enhancements/randomizer/location_access.h"
#include "soh/Enhancements/randomizer/entrance.h"
#include "soh/Enhancements/randomizer/dungeon.h"

using namespace Rando;

void RegionTable_Init_WaterTemple() {
    // clang-format off
    // Vanilla/MQ Decider
    areaTable[RR_WATER_TEMPLE_ENTRYWAY] = Region("Water Temple Entryway", SCENE_WATER_TEMPLE, {}, {}, {
        //Exits
        Entrance(RR_WATER_TEMPLE_ENTRANCE_LEDGE,    []{return logic->HasItem(RG_BRONZE_SCALE) && ctx->GetDungeon(WATER_TEMPLE)->IsVanilla();}),
        Entrance(RR_WATER_TEMPLE_MQ_WATER_ENTRANCE, []{return logic->HasItem(RG_BRONZE_SCALE) && ctx->GetDungeon(WATER_TEMPLE)->IsMQ();}),
        Entrance(RR_LH_FROM_WATER_TEMPLE,           []{return true;}),
    });

#pragma region Vanilla

    //Water Temple logic currently assumes that the locked door leading to the upper water raising location is unlocked from the start
    areaTable[RR_WATER_TEMPLE_ENTRANCE_LEDGE] = Region("Water Temple Entrance Ledge", SCENE_WATER_TEMPLE, {}, {}, {
        //Exits
        Entrance(RR_WATER_TEMPLE_ENTRYWAY,      []{return logic->HasItem(RG_BRONZE_SCALE) || logic->CanUse(RG_IRON_BOOTS);}),
        Entrance(RR_WATER_TEMPLE_MAIN,          []{return true;}),
        Entrance(RR_WATER_TEMPLE_3F_CENTRAL_A,  []{return (logic->WaterLevel(WL_HIGH) && logic->CanUse(RG_HOOKSHOT)) || logic->CanUse(RG_HOVER_BOOTS);}),
        Entrance(RR_WATER_TEMPLE_3F_CENTRAL_H,  []{return logic->WaterLevel(WL_HIGH) && (logic->CanUse(RG_HOOKSHOT) || logic->CanUse(RG_HOVER_BOOTS));}),
        Entrance(RR_WATER_TEMPLE_3F_CENTRAL_LM, []{return logic->CanUse(RG_HOVER_BOOTS) && logic->WaterLevel(WL_LOW_OR_MID);}),
        Entrance(RR_WATER_TEMPLE_2F_CENTRAL_LM, []{return logic->WaterLevel(WL_LOW_OR_MID);}),
    });

    //This region covers simply existing in the area around the central pillar without being on a specific platform, either swimming or walking on the lakebed
    //Entry should only include being in the correct area, taking any possible fall damage, and floating up to the surface of WL_HIGH if coming from below
    //This area then leads to others based on level and worst-case water timers for follow-up exits from the water's surface
    //remember that any solution that works for any level doesn't need to be given a level, even if that solution is overkill for a lower level
    //Water Temple logic currently assumes that the locked door leading to the upper water raising location is unlocked from the start
    areaTable[RR_WATER_TEMPLE_MAIN] = Region("Water Temple Main", SCENE_WATER_TEMPLE, {
        //Events
        EventAccess(LOGIC_WATER_PUSHED_1F_BLOCK, []{return logic->WaterLevel(WL_LOW) && logic->HasItem(RG_GORONS_BRACELET);}),
        EventAccess(LOGIC_WATER_COULD_MIDDLE,    []{return (logic->CanUse(RG_LONGSHOT) && (logic->HasFireSourceWithTorch() || logic->CanUse(RG_FAIRY_BOW))) ||
                                                           logic->SmallKeys(SCENE_WATER_TEMPLE, 5);}),
    }, {}, {
        //Exits
        Entrance(RR_WATER_TEMPLE_ENTRANCE_LEDGE, []{return logic->HasItem(RG_BRONZE_SCALE) && logic->WaterLevel(WL_HIGH);}),
        Entrance(RR_WATER_TEMPLE_SIDE_TOWER_1F,  []{return (logic->WaterTimer() >= 24 && logic->CanUse(RG_IRON_BOOTS)) || 
                                                           (logic->WaterLevel(WL_MID) && logic->HasItem(RG_GOLDEN_SCALE) && logic->WaterTimer() >= 16) || 
                                                           logic->WaterLevel(WL_LOW) ||
                                                           (logic->CanUse(RG_LONGSHOT) && ctx->GetTrickOption(RT_WATER_LONGSHOT_TORCH) && logic->HasItem(RG_BRONZE_SCALE) && logic->WaterTimer() >= 8);}),
        Entrance(RR_WATER_TEMPLE_3F_CENTRAL_A,   []{return logic->WaterLevel(WL_HIGH) && logic->HasItem(RG_BRONZE_SCALE);}),
        Entrance(RR_WATER_TEMPLE_3F_CENTRAL_H,   []{return logic->WaterLevel(WL_HIGH) && logic->HasItem(RG_BRONZE_SCALE);}),
        Entrance(RR_WATER_TEMPLE_2F_CENTRAL_H,   []{return logic->WaterLevel(WL_HIGH) && logic->CanUse(RG_IRON_BOOTS) && ((logic->WaterTimer() >= 8 && logic->HasItem(RG_BRONZE_SCALE)) || (logic->WaterTimer() >= 40) && logic->CanUse(RG_LONGSHOT));}),
        Entrance(RR_WATER_TEMPLE_2F_CENTRAL_LM,  []{return logic->WaterLevel(WL_LOW_OR_MID) && ((logic->WaterLevel(WL_MID) && logic->HasItem(RG_BRONZE_SCALE)) ||
                                                           ((logic->WaterLevel(WL_LOW) || (logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 40)) && logic->CanUse(RG_LONGSHOT)));}),
        Entrance(RR_WATER_TEMPLE_PILLAR_1F,      []{return logic->WaterLevel(WL_LOW) && logic->SmallKeys(SCENE_WATER_TEMPLE, 5);}),
        Entrance(RR_WATER_TEMPLE_SPIKE_MOAT,      []{return ((logic->WaterLevel(WL_LOW) && logic->HasItem(RG_BRONZE_SCALE)) || (logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 16 && (logic->CanUse(RG_HOOKSHOT) || logic->HasItem(RG_BRONZE_SCALE))));}),
        Entrance(RR_WATER_TEMPLE_BLOCK_U_BEND,   []{return logic->Get(LOGIC_WATER_PUSHED_1F_BLOCK) && 
                                                          ((logic->CanUse(RG_IRON_BOOTS) && logic->HasItem(RG_BRONZE_SCALE) && logic->WaterTimer() >= 16) ||
                                                            (logic->WaterLevel(WL_LOW) && logic->HasItem(RG_SILVER_SCALE)));}),
        Entrance(RR_WATER_TEMPLE_NEAR_CAGE,      []{return Here(RR_WATER_TEMPLE_MAIN, []{return logic->WaterLevel(WL_LOW) && logic->HasExplosives();}) &&
                                                           (logic->WaterLevel(WL_LOW) && logic->HasItem(RG_SILVER_SCALE) ||
                                                            (logic->CanUse(RG_IRON_BOOTS) && logic->HasItem(RG_BRONZE_SCALE) && logic->WaterTimer() >= 16));}),
    });

    areaTable[RR_WATER_TEMPLE_3F_CENTRAL_A] = Region("Water Temple 3F Central Any Water", SCENE_WATER_TEMPLE, {}, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_MAIN_LEVEL_2_POT_1, logic->CanUse(RG_BOOMERANG)),
        LOCATION(RC_WATER_TEMPLE_MAIN_LEVEL_2_POT_2, logic->CanUse(RG_BOOMERANG)),
    }, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MAIN,                []{return true;}),
        Entrance(RR_WATER_TEMPLE_ENTRANCE_LEDGE,      []{return logic->CanUse(RG_LONGSHOT) || logic->CanUse(RG_HOVER_BOOTS);}),
        Entrance(RR_WATER_TEMPLE_HIGH_EMBLEM,         []{return logic->Water3FCentralToHighEmblem();}),
    });

    //assumes checking for WL_HIGH on entry
    areaTable[RR_WATER_TEMPLE_3F_CENTRAL_H] = Region("Water Temple 3F Central High Water", SCENE_WATER_TEMPLE, {}, {}, {
        //Exits
        Entrance(RR_WATER_TEMPLE_2F_CENTRAL_H,        []{return logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 8 && logic->HasItem(RG_BRONZE_SCALE);}),
        Entrance(RR_WATER_TEMPLE_WATERFALL,           []{return logic->SmallKeys(SCENE_WATER_TEMPLE, 4) &&
                                                                (logic->CanUse(RG_HOOKSHOT) || logic->CanUse(RG_HOVER_BOOTS) || logic->CanUse(RG_BRONZE_SCALE));}),
        Entrance(RR_WATER_TEMPLE_BLOCK_LOOP_3F_H,     []{return logic->CanUse(RG_HOVER_BOOTS) || logic->CanUse(RG_BRONZE_SCALE);}),
       Entrance(RR_WATER_TEMPLE_RISING_TARGET_LEDGE, []{return logic->CanUse(RG_LONGSHOT) || (ctx->GetTrickOption(RT_HOVER_BOOST_SIMPLE) && ctx->GetTrickOption(RT_DAMAGE_BOOST_SIMPLE) && logic->HasExplosives() && logic->CanUse(RG_HOVER_BOOTS));}),
    });

    //assumes checking for WL_LOW_OR_MID on entry
    areaTable[RR_WATER_TEMPLE_3F_CENTRAL_LM] = Region("Water Temple 3F Central Low Or Mid Water", SCENE_WATER_TEMPLE, {}, {
    }, {
        //Exits
        Entrance(RR_WATER_TEMPLE_2F_CENTRAL_LM,       []{return true;}),
        Entrance(RR_WATER_TEMPLE_BLOCK_LOOP,          []{return ctx->GetTrickOption(RT_WATER_CENTRAL_BOW) && logic->CanHitEyeTargets();}),
        Entrance(RR_WATER_TEMPLE_BLOCK_LOOP_3F_LM,    []{return logic->CanUse(RG_HOVER_BOOTS);}),
        //assumes RR_WATER_TEMPLE_HIGH_EMBLEM and RR_WATER_TEMPLE_3F_CENTRAL_LM access
        Entrance(RR_WATER_TEMPLE_PILLAR_H,            []{return ctx->GetTrickOption(RT_WATER_IRONS_CENTRAL_GS) && logic->CanUse(RG_DINS_FIRE) && logic->Water3FCentralToHighEmblem();}),
        Entrance(RR_WATER_TEMPLE_RISING_TARGET_LEDGE, []{return (ctx->GetTrickOption(RT_HOVER_BOOST_SIMPLE) && ctx->GetTrickOption(RT_DAMAGE_BOOST_SIMPLE) && logic->HasExplosives() && logic->CanUse(RG_HOVER_BOOTS));}),
    });

    //Assumes checking for Iron boots and WL_HIGH on entry
    areaTable[RR_WATER_TEMPLE_2F_CENTRAL_H] = Region("Water Temple 2F Central High Water", SCENE_WATER_TEMPLE, {}, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_MAIN_LEVEL_2_POT_1, logic->CanUse(RG_HOOKSHOT)),
        LOCATION(RC_WATER_TEMPLE_MAIN_LEVEL_2_POT_2, logic->CanUse(RG_HOOKSHOT)),
    }, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MAIN,           []{return true;}),
        //Implies CanAvoid(RE_STINGERS)
        Entrance(RR_WATER_TEMPLE_JET_CHEST_ROOM, []{return logic->CanUse(RG_HOOKSHOT) && logic->WaterTimer() >= 48;}),
        //TODO tunic timer
        Entrance(RR_WATER_TEMPLE_3F_CENTRAL_A,   []{return logic->CanUse(RG_LONGSHOT) && logic->WaterTimer() >= 40;;}),
        Entrance(RR_WATER_TEMPLE_3F_CENTRAL_H,   []{return logic->CanUse(RG_LONGSHOT) && logic->WaterTimer() >= 40;;}),
    });
    
    //assumes checking for WL_LOW_OR_MID on entry
    areaTable[RR_WATER_TEMPLE_2F_CENTRAL_LM] = Region("Water Temple 2F Central Low Or Mid Water", SCENE_WATER_TEMPLE, {
        //Events
        //Assumes RR_WATER_TEMPLE_JET_LIFT and RR_WATER_TEMPLE_HIGH_EMBLEM access
        EventAccess(LOGIC_WATER_COULD_HIGH, []{return logic->WaterLevel(WL_MID) && 
                                                      (logic->CanUse(RG_HOOKSHOT) || logic->CanUse(RG_HOVER_BOOTS) || logic->CanUse(RG_BRONZE_SCALE)) &&
                                                      logic->CanHitSwitch(ED_BOMB_THROW);})
    }, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_MAIN_LEVEL_2_POT_1, logic->CanBreakPots()),
        LOCATION(RC_WATER_TEMPLE_MAIN_LEVEL_2_POT_2, logic->CanBreakPots()),
    }, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MAIN,           []{return true;}),
        //Implies CanAvoid(RE_STINGERS)
        Entrance(RR_WATER_TEMPLE_JET_CHEST_ROOM, []{return logic->CanUse(RG_HOOKSHOT);}),
        Entrance(RR_WATER_TEMPLE_JET_LIFT_2F,    []{return logic->WaterLevel(WL_MID) && 
                                                           (logic->CanUse(RG_HOOKSHOT) || logic->CanUse(RG_HOVER_BOOTS) || logic->CanUse(RG_BRONZE_SCALE));}),
        //Child can jumpslash with the lit stick to light the torch
        Entrance(RR_WATER_TEMPLE_PILLAR_2F,      []{return logic->HasFireSourceWithTorch() || logic->CanUse(RG_FAIRY_BOW);}),
        //assumes RR_WATER_TEMPLE_3F_CENTRAL_LM and RR_WATER_TEMPLE_HIGH_EMBLEM access
        Entrance(RR_WATER_TEMPLE_PILLAR_H,       []{return ctx->GetTrickOption(RT_WATER_IRONS_CENTRAL_GS) && 
                                                           (logic->HasFireSourceWithTorch() || logic->CanUse(RG_FAIRY_BOW)) && 
                                                           logic->CanUse(RG_LONGSHOT) && 
                                                           logic->Water3FCentralToHighEmblem();}),
        //hookshot + jumpslash can make it up through the platform slit as adult, is easier with WL_MID but still possible on WL_LOW, but it's a trick
        Entrance(RR_WATER_TEMPLE_3F_CENTRAL_A,   []{return logic->CanUse(RG_LONGSHOT);}),
        Entrance(RR_WATER_TEMPLE_3F_CENTRAL_LM,  []{return logic->CanUse(RG_LONGSHOT);}),
        Entrance(RR_WATER_TEMPLE_BLOCK_LOOP,     []{return logic->CanHitEyeTargets() && (logic->CanUse(RG_LONGSHOT) || logic->CanUse(RG_HOVER_BOOTS));}),
    });

    areaTable[RR_WATER_TEMPLE_SIDE_TOWER_1F] = Region("Water Temple Side Tower", SCENE_WATER_TEMPLE, {
        //Events
        EventAccess(LOGIC_WATER_COULD_LOW, []{return logic->CanUse(RG_BRONZE_SCALE);}),
    }, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_TORCH_POT_1, (logic->WaterLevel(WL_LOW) && logic->CanBreakPots()) || (logic->CanUse(RG_HOOKSHOT) && logic->CanUse(RG_IRON_BOOTS))),
        LOCATION(RC_WATER_TEMPLE_TORCH_POT_2, (logic->WaterLevel(WL_LOW) && logic->CanBreakPots()) || (logic->CanUse(RG_HOOKSHOT) && logic->CanUse(RG_IRON_BOOTS))),
    }, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MAIN,          []{return logic->WaterLevel(WL_LOW) || (logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 8);}),
        Entrance(RR_WATER_TEMPLE_LOW_EMBLEM,    []{return logic->WaterLevel(WL_HIGH) && logic->HasItem(RG_BRONZE_SCALE) && logic->WaterTimer() >= 8;}),
        Entrance(RR_WATER_TEMPLE_SIDE_TOWER_2F, []{return logic->WaterLevel(WL_MID) && logic->HasItem(RG_BRONZE_SCALE) && logic->WaterTimer() >= 8;}),
        Entrance(RR_WATER_TEMPLE_TORCH_ROOM,    []{return logic->WaterLevel(WL_LOW) && (logic->HasFireSourceWithTorch() || logic->CanUse(RG_FAIRY_BOW));}),
    });
    
    areaTable[RR_WATER_TEMPLE_SIDE_TOWER_2F] = Region("Water Temple Side Tower", SCENE_WATER_TEMPLE, {}, {}, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MAIN,         []{return (logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 8) || logic->WaterLevel(WL_LOW);}),
        Entrance(RR_WATER_TEMPLE_CRACKED_WALL, []{return logic->WaterLevel(WL_LOW_OR_MID) && logic->HasExplosives();}),
        });

    areaTable[RR_WATER_TEMPLE_LOW_EMBLEM] = Region("Water Temple Side Tower", SCENE_WATER_TEMPLE, {
        //Events
        EventAccess(LOGIC_WATER_LOW,       []{return logic->CanUse(RG_ZELDAS_LULLABY);}),
        EventAccess(LOGIC_WATER_COULD_LOW, []{return true;}),
    }, {}, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MAIN,          []{return logic->WaterLevel(WL_LOW) || logic->WaterTimer() >= 24 && logic->CanUse(RG_IRON_BOOTS);}),
        Entrance(RR_WATER_TEMPLE_CRACKED_WALL,  []{return logic->WaterLevel(WL_LOW_OR_MID) && ((logic->CanUse(RG_HOVER_BOOTS) && ctx->GetTrickOption(RT_WATER_CRACKED_WALL_HOVERS)) || ctx->GetTrickOption(RT_WATER_CRACKED_WALL)) ||
                                                          logic->WaterLevel(WL_MID) && logic->HasItem(RG_BRONZE_SCALE);}),
        Entrance(RR_WATER_TEMPLE_4_SPIKES_ROOM, []{return true;}),
    });

    areaTable[RR_WATER_TEMPLE_4_SPIKES_ROOM] = Region("Water Temple 4 Spikes Room", SCENE_WATER_TEMPLE, {}, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_MAP_CHEST, Here(RR_WATER_TEMPLE_4_SPIKES_ROOM, []{return logic->CanKillEnemy(RE_SPIKE, ED_CLOSE, true, 4);})),
    }, {
        //Exits
        Entrance(RR_WATER_TEMPLE_SIDE_TOWER_1F, []{return Here(RR_WATER_TEMPLE_4_SPIKES_ROOM, []{return logic->CanKillEnemy(RE_SPIKE, ED_CLOSE, true, 4);});}),
    });

    areaTable[RR_WATER_TEMPLE_CRACKED_WALL] = Region("Water Temple Cracked Wall", SCENE_WATER_TEMPLE, {}, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_CRACKED_WALL_CHEST, logic->WaterLevel(WL_MID)),
    }, {
        //Exits
        Entrance(RR_WATER_TEMPLE_SIDE_TOWER_2F, []{return true;}),
    });

    areaTable[RR_WATER_TEMPLE_TORCH_ROOM] = Region("Water Temple Torch Room", SCENE_WATER_TEMPLE, {}, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_TORCHES_CHEST, Here(RR_WATER_TEMPLE_TORCH_ROOM, []{return (logic->WaterLevel(WL_LOW) && logic->CanKillEnemy(RE_SHELL_BLADE, ED_CLOSE, true, 3)) ||
                                                                                           logic->CanUse(RG_HOOKSHOT);})),
    }, {
        //Exits
        Entrance(RR_WATER_TEMPLE_SIDE_TOWER_1F, []{return ((logic->WaterLevel(WL_LOW) || logic->CanUse(RG_IRON_BOOTS)) && 
                                                          Here(RR_WATER_TEMPLE_TORCH_ROOM, []{return (logic->WaterLevel(WL_LOW) && logic->CanKillEnemy(RE_SHELL_BLADE, ED_CLOSE, true, 3)) ||
                                                                                                     logic->CanUse(RG_HOOKSHOT);}));}),
    });

    areaTable[RR_WATER_TEMPLE_SPIKE_MOAT] = Region("Water Temple Spike Moat", SCENE_WATER_TEMPLE, {}, {}, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MAIN,              []{return logic->HasItem(RG_BRONZE_SCALE);}),
        Entrance(RR_WATER_TEMPLE_BEHIND_SPIKE_MOAT, []{return (logic->CanUse(RG_LONGSHOT) || (ctx->GetTrickOption(RT_WATER_BK_REGION) && logic->CanUse(RG_HOVER_BOOTS)));}),
    });

    areaTable[RR_WATER_TEMPLE_BEHIND_SPIKE_MOAT] = Region("Water Temple Behind Spike Moat", SCENE_WATER_TEMPLE, {}, {}, {
        //Exits
        //You can backflip over the spikes and into the water. You can equip irons to get over while skipping swim, but it leaves you stuck in the pond
        Entrance(RR_WATER_TEMPLE_SPIKE_MOAT,     []{return logic->HasItem(RG_BRONZE_SCALE) || logic->CanUse(RG_LONGSHOT) || (logic->CanUse(RG_HOOKSHOT) &&  logic->CanUse(RG_IRON_BOOTS));}),
        Entrance(RR_WATER_TEMPLE_BOULDERS_SOUTH, []{return logic->SmallKeys(SCENE_WATER_TEMPLE, 4);}),
    });

    areaTable[RR_WATER_TEMPLE_BOULDERS_SOUTH] = Region("Water Temple Boulders South", SCENE_WATER_TEMPLE, {}, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_GS_NEAR_BOSS_KEY_CHEST, logic->CanUse(RG_LONGSHOT)),
    }, {
        //Exits
        Entrance(RR_WATER_TEMPLE_SPIKE_MOAT,     []{return logic->SmallKeys(SCENE_WATER_TEMPLE, 4);}),
        Entrance(RR_WATER_TEMPLE_BOULDERS_NORTH, []{return logic->HasItem(RG_BRONZE_SCALE) || (ctx->GetTrickOption(RT_WATER_MQ_LOCKED_GS) && (logic->CanUse(RG_IRON_BOOTS) && logic->CanUse(RG_HOOKSHOT)));}),
        Entrance(RR_WATER_TEMPLE_BOULDERS_UPPER, []{return (logic->IsAdult && (logic->CanUse(RG_HOVER_BOOTS) || ctx->GetTrickOption(RT_WATER_NORTH_BASEMENT_LEDGE_JUMP))) || (logic->CanUse(RG_HOVER_BOOTS) && logic->CanUse(RG_IRON_BOOTS));}),
    });

    areaTable[RR_WATER_TEMPLE_BOULDERS_NORTH] = Region("Water Temple Boulders North", SCENE_WATER_TEMPLE, {}, {}, {
        //Exits
        Entrance(RR_WATER_TEMPLE_BOULDERS_SOUTH,         []{return logic->HasItem(RG_BRONZE_SCALE);}),
        Entrance(RR_WATER_TEMPLE_BLOCK_ROOM_TO_BOULDERS, []{return true;}),
    });

    areaTable[RR_WATER_TEMPLE_BLOCK_ROOM_TO_BOULDERS] = Region("Water Temple Block Room to Boulders", SCENE_WATER_TEMPLE, {}, {}, {
        //Exits
        Entrance(RR_WATER_TEMPLE_BLOCK_ROOM,         []{return true;}),
        Entrance(RR_WATER_TEMPLE_BLOCK_ROOM_TO_JETS, []{return logic->CanUse(RG_HOVER_BOOTS);}),
    });

    areaTable[RR_WATER_TEMPLE_BLOCK_ROOM] = Region("Water Temple Block Room", SCENE_WATER_TEMPLE, {}, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_BASEMENT_BLOCK_PUZZLE_POT_1, logic->CanBreakPots()),
        LOCATION(RC_WATER_TEMPLE_BASEMENT_BLOCK_PUZZLE_POT_2, logic->CanBreakPots()),
    }, {
        //Exits
        Entrance(RR_WATER_TEMPLE_BLOCK_ROOM_TO_BOULDERS, []{return logic->HasItem(RG_GORONS_BRACELET) && logic->HasExplosives() && logic->HasItem(RG_BRONZE_SCALE);}),
        Entrance(RR_WATER_TEMPLE_BLOCK_ROOM_TO_JETS,     []{return logic->HasItem(RG_GORONS_BRACELET) && logic->HasExplosives() && logic->HasItem(RG_BRONZE_SCALE);}),
    });

    areaTable[RR_WATER_TEMPLE_BLOCK_ROOM_TO_JETS] = Region("Water Temple Block Room to Boulders", SCENE_WATER_TEMPLE, {}, {}, {
        //Exits
        Entrance(RR_WATER_TEMPLE_BLOCK_ROOM,             []{return true;}),
        Entrance(RR_WATER_TEMPLE_BLOCK_ROOM_TO_BOULDERS, []{return logic->CanUse(RG_HOOKSHOT) || logic->CanUse(RG_HOVER_BOOTS);}),
    });

    areaTable[RR_WATER_TEMPLE_JETS_ROOM] = Region("Water Temple Jets Room", SCENE_WATER_TEMPLE, {}, {}, {
        //Exits
        Entrance(RR_WATER_TEMPLE_BLOCK_ROOM_TO_JETS,    []{return logic->CanUse(RG_HOOKSHOT);}),
        Entrance(RR_WATER_TEMPLE_BOULDERS_UPPER_ALCOVE, []{return true;}),
    });

    areaTable[RR_WATER_TEMPLE_BOULDERS_UPPER] = Region("Water Temple Boulders Upper", SCENE_WATER_TEMPLE, {}, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_GS_NEAR_BOSS_KEY_CHEST, (logic->IsAdult && logic->HookshotOrBoomerang()) || (logic->CanUse(RG_IRON_BOOTS) && logic->CanUse(RG_HOOKSHOT))), // can also get token with hover backflip
    }, {
        //Exits
        Entrance(RR_WATER_TEMPLE_BOULDERS_SOUTH,   []{return logic->HasItem(RG_BRONZE_SCALE) || (logic->IsAdult && (logic->CanJumpslash() || logic->CanUse(RG_HOVER_BOOTS)));}),
        Entrance(RR_WATER_TEMPLE_BOULDERS_UPPER_ALCOVE,  []{return logic->IsAdult;}),
        Entrance(RR_WATER_TEMPLE_OUTSIDE_BOSS_KEY_ROOM,  []{return (logic->CanUse(RG_IRON_BOOTS) || (logic->IsAdult && ctx->GetTrickOption(RT_WATER_BK_JUMP_DIVE))) && logic->HasItem(RG_BRONZE_SCALE);}),
    });

    areaTable[RR_WATER_TEMPLE_BOULDERS_UPPER_ALCOVE] = Region("Water Temple Boulders Upper Alcove", SCENE_WATER_TEMPLE, {}, {}, {
        //Exits
        Entrance(RR_WATER_TEMPLE_JETS_ROOM, []{return true;}),
    });

    areaTable[RR_WATER_TEMPLE_OUTSIDE_BOSS_KEY_ROOM] = Region("Water Temple Outside Boss Key Room", SCENE_WATER_TEMPLE, {}, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_GS_NEAR_BOSS_KEY_CHEST, logic->CanUse(RG_IRON_BOOTS) && logic->CanUse(RG_HOOKSHOT)),
    }, {
        //Exits
        Entrance(RR_WATER_TEMPLE_BOULDERS_UPPER, []{return logic->HasItem(RG_BRONZE_SCALE);}),
        Entrance(RR_WATER_TEMPLE_BOSS_KEY_ROOM,  []{return logic->SmallKeys(SCENE_WATER_TEMPLE, 5);}),
    });

    areaTable[RR_WATER_TEMPLE_BOSS_KEY_ROOM] = Region("Water Temple Boss Key Room", SCENE_WATER_TEMPLE, {
        //Events
        EventAccess(LOGIC_FAIRY_POT, []{return true;}),
    }, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_BOSS_KEY_CHEST, true),
        LOCATION(RC_WATER_TEMPLE_BOSS_KEY_POT_1, logic->CanBreakPots()),
        LOCATION(RC_WATER_TEMPLE_BOSS_KEY_POT_2, logic->CanBreakPots()),
    }, {
        //Exits
        Entrance(RR_WATER_TEMPLE_OUTSIDE_BOSS_KEY_ROOM, []{return logic->SmallKeys(SCENE_WATER_TEMPLE, 5);}),
    });

    areaTable[RR_WATER_TEMPLE_NEAR_CAGE] = Region("Water Temple South Lower", SCENE_WATER_TEMPLE, {}, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_GS_BEHIND_GATE,    logic->CanJumpslash() && (logic->CanUse(RG_HOOKSHOT) || (logic->IsAdult && logic->CanUse(RG_HOVER_BOOTS)))),
        LOCATION(RC_WATER_TEMPLE_BEHIND_GATE_POT_1, logic->CanJumpslash() && (logic->CanUse(RG_HOOKSHOT) || (logic->IsAdult && logic->CanUse(RG_HOVER_BOOTS)))),
        LOCATION(RC_WATER_TEMPLE_BEHIND_GATE_POT_2, logic->CanJumpslash() && (logic->CanUse(RG_HOOKSHOT) || (logic->IsAdult && logic->CanUse(RG_HOVER_BOOTS)))),
        LOCATION(RC_WATER_TEMPLE_BEHIND_GATE_POT_3, logic->CanJumpslash() && (logic->CanUse(RG_HOOKSHOT) || (logic->IsAdult && logic->CanUse(RG_HOVER_BOOTS)))),
        LOCATION(RC_WATER_TEMPLE_BEHIND_GATE_POT_4, logic->CanJumpslash() && (logic->CanUse(RG_HOOKSHOT) || (logic->IsAdult && logic->CanUse(RG_HOVER_BOOTS)))),
    }, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MAIN, []{return logic->CanUse(RG_IRON_BOOTS);}),
    });

    areaTable[RR_WATER_TEMPLE_WEST_LOWER] = Region("Water Temple West Lower", SCENE_WATER_TEMPLE, {}, {}, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MAIN,               []{return logic->CanUse(RG_HOOKSHOT) && logic->CanUse(RG_IRON_BOOTS) && logic->HasItem(RG_GORONS_BRACELET);}),
        Entrance(RR_WATER_TEMPLE_OUTSIDE_DRAGON_ROOM, []{return logic->CanHitSwitch();}),
    });

    areaTable[RR_WATER_TEMPLE_OUTSIDE_DRAGON_ROOM] = Region("Water Temple Outside Dragon Room", SCENE_WATER_TEMPLE, {}, {}, {
        //Exits
        Entrance(RR_WATER_TEMPLE_WEST_LOWER,  []{return logic->CanHitSwitch(ED_BOOMERANG);}),
        Entrance(RR_WATER_TEMPLE_DRAGON_ROOM, []{return true;}),
    });

    areaTable[RR_WATER_TEMPLE_DRAGON_ROOM] = Region("Water Temple Dragon Room", SCENE_WATER_TEMPLE, {}, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_DRAGON_CHEST, (logic->CanUse(RG_HOOKSHOT) && logic->CanUse(RG_IRON_BOOTS)) || (((logic->IsAdult && ctx->GetTrickOption(RT_WATER_ADULT_DRAGON) && (logic->CanUse(RG_HOOKSHOT) || logic->CanUse(RG_FAIRY_BOW) || logic->CanUse(RG_BOMBCHU_5))) || (logic->IsChild && ctx->GetTrickOption(RT_WATER_CHILD_DRAGON) && (logic->CanUse(RG_FAIRY_SLINGSHOT) || logic->CanUse(RG_BOOMERANG) || logic->CanUse(RG_BOMBCHU_5)))) && (logic->HasItem(RG_SILVER_SCALE) || logic->CanUse(RG_IRON_BOOTS)))),
    }, {
        //Exits
        Entrance(RR_WATER_TEMPLE_OUTSIDE_DRAGON_ROOM, []{return true;}),
    });

    areaTable[RR_WATER_TEMPLE_PILLAR_1F] = Region("Water Temple Central Pillar 1F", SCENE_WATER_TEMPLE, {}, {}, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MAIN,      []{return logic->SmallKeys(SCENE_WATER_TEMPLE, 5) && logic->WaterLevel(WL_LOW);}),
        Entrance(RR_WATER_TEMPLE_PILLAR_2F, []{return logic->CanUse(RG_HOOKSHOT);}),
        Entrance(RR_WATER_TEMPLE_PILLAR_B1, []{return logic->WaterLevel(WL_MID) && logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 40;}),
        Entrance(RR_WATER_TEMPLE_PILLAR_H,  []{return ctx->GetTrickOption(RT_WATER_FW_CENTRAL_GS) && logic->CanUse(RG_FARORES_WIND) && (logic->CanUse(RG_IRON_BOOTS) || logic->HasItem(RG_BRONZE_SCALE));}),
    });

    areaTable[RR_WATER_TEMPLE_PILLAR_2F] = Region("Water Temple Central Pillar 2F", SCENE_WATER_TEMPLE, {
        //Events
        EventAccess(LOGIC_WATER_MIDDLE,       []{return logic->CanUse(RG_ZELDAS_LULLABY);}),
        EventAccess(LOGIC_WATER_COULD_MIDDLE, []{return true;}),
    }, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_GS_CENTRAL_PILLAR, logic->CanUse(RG_LONGSHOT);),
    }, {
        //Exits
        Entrance(RR_WATER_TEMPLE_2F_CENTRAL_LM, []{return true;}),
        Entrance(RR_WATER_TEMPLE_PILLAR_1F,     []{return logic->WaterLevel(WL_LOW) || logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 8;}),
        Entrance(RR_WATER_TEMPLE_PILLAR_H,      []{return ctx->GetTrickOption(RT_WATER_FW_CENTRAL_GS) && logic->CanUse(RG_FARORES_WIND) && (logic->CanUse(RG_IRON_BOOTS) || logic->HasItem(RG_BRONZE_SCALE));}),
    });

    areaTable[RR_WATER_TEMPLE_PILLAR_H] = Region("Water Temple Central Pillar High Water", SCENE_WATER_TEMPLE, {
    }, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_GS_CENTRAL_PILLAR, logic->HasItem(RG_BRONZE_SCALE) && logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA, ED_BOOMERANG)),
    }, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MAIN,          []{return logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 8;}),
        Entrance(RR_WATER_TEMPLE_2F_CENTRAL_LM, []{return logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 8;}),
        Entrance(RR_WATER_TEMPLE_PILLAR_B1,     []{return logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 40;}),
    });

    areaTable[RR_WATER_TEMPLE_PILLAR_B1] = Region("Water Temple Central Pillar Basement", SCENE_WATER_TEMPLE, {}, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_CENTRAL_PILLAR_CHEST, logic->CanUse(RG_HOOKSHOT) && logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 40),
    }, {
        //Exits
        Entrance(RR_WATER_TEMPLE_PILLAR_1F, []{return logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 16;}),
    });

    areaTable[RR_WATER_TEMPLE_JET_CHEST_ROOM] = Region("Water Temple East Middle", SCENE_WATER_TEMPLE, {}, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_COMPASS_CHEST,      logic->CanUseProjectile()),
        LOCATION(RC_WATER_TEMPLE_NEAR_COMPASS_POT_1, logic->CanBreakPots()),
        LOCATION(RC_WATER_TEMPLE_NEAR_COMPASS_POT_2, logic->CanBreakPots()),
        LOCATION(RC_WATER_TEMPLE_NEAR_COMPASS_POT_3, logic->CanBreakPots()),
    }, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MAIN, []{return logic->CanUse(RG_IRON_BOOTS);}),
    });

    areaTable[RR_WATER_TEMPLE_JET_LIFT_2F] = Region("Water Temple Jet Lift 2F", SCENE_WATER_TEMPLE, {}, {}, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MAIN,        []{return true;}),
        Entrance(RR_WATER_TEMPLE_JET_LIFT_3F, []{return logic->CanHitSwitch(ED_BOMB_THROW);}),
    });

    areaTable[RR_WATER_TEMPLE_JET_LIFT_3F] = Region("Water Temple Jet Lift 3F", SCENE_WATER_TEMPLE, {}, {}, {
        //Exits
        Entrance(RR_WATER_TEMPLE_JET_LIFT_2F, []{return true;}),
        Entrance(RR_WATER_TEMPLE_HIGH_EMBLEM, []{return true;}),
    });

    areaTable[RR_WATER_TEMPLE_HIGH_EMBLEM] = Region("Water Temple High Emblem", SCENE_WATER_TEMPLE, {
        //Events
        EventAccess(LOGIC_WATER_HIGH,      []{return logic->CanUse(RG_ZELDAS_LULLABY);}),
        EventAccess(LOGIC_WATER_SCARECROW, []{return logic->ScarecrowsSong();}),
    }, {}, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MAIN,         []{return true;}),
        Entrance(RR_WATER_TEMPLE_3F_CENTRAL_A, []{return true;}),
        Entrance(RR_WATER_TEMPLE_3F_CENTRAL_H, []{return logic->WaterLevel(WL_HIGH);}),
    });

    //This region represents being able to be in "front" of the block while it's in it's half-pushed state
    //Currently Assumes WL_LOW_OR_MID as there's no way to reach it on WL_HIGH in logic, this will need splitting if one is added
    areaTable[RR_WATER_TEMPLE_BLOCK_LOOP] = Region("Water Temple Block Loop", SCENE_WATER_TEMPLE, {}, {}, {
        //Exits
        Entrance(RR_WATER_TEMPLE_BLOCK_LOOP_BACK,  []{return logic->HasItem(RG_GORONS_BRACELET) && logic->WaterLevel(WL_LOW_OR_MID);}),
        Entrance(RR_WATER_TEMPLE_BLOCK_LOOP_3F_LM, []{return (logic->CanUse(RG_HOOKSHOT) && (logic->CanUse(RG_IRON_BOOTS) || logic->HasItem(RG_BRONZE_SCALE)));}),
    });

    //Currently Assumes WL_LOW_OR_MID as there's no way to reach it on WL_HIGH in logic, this will need splitting if one is added
    areaTable[RR_WATER_TEMPLE_BLOCK_LOOP_BACK] = Region("Water Temple Block Loop Back", SCENE_WATER_TEMPLE, {}, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_CENTRAL_BOW_TARGET_CHEST, true),
        LOCATION(RC_WATER_TEMPLE_CENTRAL_BOW_POT_1,        logic->CanBreakPots()),
        LOCATION(RC_WATER_TEMPLE_CENTRAL_BOW_POT_2,        logic->CanBreakPots()),
    }, {});

    //This region is not able to finish pushing the block out of the way to reach the chest
    //assumes checking WL_HIGH on entry
    areaTable[RR_WATER_TEMPLE_BLOCK_LOOP_3F_H] = Region("Water Temple Block Loop 3F High Water", SCENE_WATER_TEMPLE, {}, {}, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MAIN,         []{return true;}),
        Entrance(RR_WATER_TEMPLE_3F_CENTRAL_A, []{return logic->CanUse(RG_HOOKSHOT) || logic->CanUse(RG_HOVER_BOOTS);}),
        Entrance(RR_WATER_TEMPLE_3F_CENTRAL_H, []{return logic->CanUse(RG_HOOKSHOT) || logic->CanUse(RG_HOVER_BOOTS);}),
    });

    //This region is not able to finish pushing the block out of the way to reach the chest
    //Assumes checking WL_LOW_OR_MID on entry
    areaTable[RR_WATER_TEMPLE_BLOCK_LOOP_3F_LM] = Region("Water Temple Block Loop 3F Low or Mid Water", SCENE_WATER_TEMPLE, {}, {}, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MAIN,          []{return true;}),
        Entrance(RR_WATER_TEMPLE_3F_CENTRAL_A,  []{return logic->CanUse(RG_HOOKSHOT) || logic->CanUse(RG_HOVER_BOOTS);}),
        Entrance(RR_WATER_TEMPLE_3F_CENTRAL_LM, []{return logic->CanUse(RG_HOOKSHOT) || logic->CanUse(RG_HOVER_BOOTS);}),
    });

    areaTable[RR_WATER_TEMPLE_WATERFALL] = Region("Water Temple Falling Platform Room", SCENE_WATER_TEMPLE, {}, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_GS_FALLING_PLATFORM_ROOM, logic->CanUse(RG_LONGSHOT) || (ctx->GetTrickOption(RT_WATER_RANG_FALLING_PLATFORM_GS) && logic->IsChild && logic->CanUse(RG_BOOMERANG)) || (ctx->GetTrickOption(RT_WATER_HOOKSHOT_FALLING_PLATFORM_GS) && logic->IsAdult && logic->CanUse(RG_HOOKSHOT))),
    }, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MAIN,                     []{return logic->SmallKeys(SCENE_WATER_TEMPLE, 4);}),
        Entrance(RR_WATER_TEMPLE_FALLING_PLATFORM_ROOM_END, []{return logic->CanUse(RG_HOOKSHOT);}),
    });

    areaTable[RR_WATER_TEMPLE_FALLING_PLATFORM_ROOM_END] = Region("Water Temple Falling Platform Room End", SCENE_WATER_TEMPLE, {}, {}, {
        Entrance(RR_WATER_TEMPLE_WATERFALL, []{return logic->CanUse(RG_HOOKSHOT);}),
        Entrance(RR_WATER_TEMPLE_DRAGON_PILLARS_ROOM,   []{return logic->SmallKeys(SCENE_WATER_TEMPLE, 5);}),
    });

    areaTable[RR_WATER_TEMPLE_DRAGON_PILLARS_ROOM] = Region("Water Temple Dragon Pillars Room", SCENE_WATER_TEMPLE, {}, {}, {
        //Exits
        Entrance(RR_WATER_TEMPLE_WATERFALL,     []{return logic->SmallKeys(SCENE_WATER_TEMPLE, 5);}),
        Entrance(RR_WATER_TEMPLE_DRAGON_PILLARS_ROOM_UPPER, []{return logic->CanUse(RG_HOOKSHOT);}),
    });

    //specifically the area past the spikes
    areaTable[RR_WATER_TEMPLE_DRAGON_PILLARS_ROOM_UPPER] = Region("Water Temple Dragon Pillars Room Upper", SCENE_WATER_TEMPLE, {}, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_LIKE_LIKE_POT_1, logic->CanBreakPots()),
        LOCATION(RC_WATER_TEMPLE_LIKE_LIKE_POT_2, logic->CanBreakPots()),
    }, {
        Entrance(RR_WATER_TEMPLE_DRAGON_PILLARS_ROOM, []{return (logic->IsAdult || logic->TakeDamage() || logic->CanUse(RG_GORON_TUNIC)) && (logic->HasItem(RG_BRONZE_SCALE) || logic->CanUse(RG_HOVER_BOOTS));}),
        Entrance(RR_WATER_TEMPLE_DARK_LINK_ROOM,      []{return true;}),
    });

    areaTable[RR_WATER_TEMPLE_DARK_LINK_ROOM] = Region("Water Temple Dark Link Room", SCENE_WATER_TEMPLE, {}, {}, {
        //Exits
        Entrance(RR_WATER_TEMPLE_DRAGON_PILLARS_ROOM_UPPER, []{return logic->CanKillEnemy(RE_DARK_LINK);}),
        Entrance(RR_WATER_TEMPLE_LONGSHOT_ROOM,             []{return logic->CanKillEnemy(RE_DARK_LINK);}),
    });

    areaTable[RR_WATER_TEMPLE_LONGSHOT_ROOM] = Region("Water Temple Longshot Room", SCENE_WATER_TEMPLE, {}, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_LONGSHOT_CHEST, true),
    }, {
        //Exits
        Entrance(RR_WATER_TEMPLE_DARK_LINK_ROOM, []{return true;}),
        Entrance(RR_WATER_TEMPLE_RIVER,          []{return logic->IsChild || logic->CanUse(RG_SONG_OF_TIME);}),
    });

    areaTable[RR_WATER_TEMPLE_RIVER] = Region("Water Temple River", SCENE_WATER_TEMPLE, {}, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_RIVER_CHEST,   (logic->CanUse(RG_FAIRY_SLINGSHOT) || logic->CanUse(RG_FAIRY_BOW)) && (logic->IsAdult || logic->CanUse(RG_HOVER_BOOTS) || logic->CanUse(RG_HOOKSHOT))),
        LOCATION(RC_WATER_TEMPLE_GS_RIVER,      (logic->CanUse(RG_IRON_BOOTS) && logic->CanUse(RG_HOOKSHOT)) || (ctx->GetTrickOption(RT_WATER_RIVER_GS) && logic->CanUse(RG_LONGSHOT))),
        LOCATION(RC_WATER_TEMPLE_RIVER_POT_1,   logic->CanBreakPots()),
        LOCATION(RC_WATER_TEMPLE_RIVER_POT_2,   logic->CanBreakPots()),
        LOCATION(RC_WATER_TEMPLE_RIVER_HEART_1, (logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 16) || logic->HasItem(RG_BRONZE_SCALE)),
        LOCATION(RC_WATER_TEMPLE_RIVER_HEART_2, (logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 16) || logic->HasItem(RG_BRONZE_SCALE)),
        LOCATION(RC_WATER_TEMPLE_RIVER_HEART_3, (logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 16) || logic->HasItem(RG_BRONZE_SCALE)),
        LOCATION(RC_WATER_TEMPLE_RIVER_HEART_4, (logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 24) || logic->HasItem(RG_BRONZE_SCALE)),
        LOCATION(RC_WATER_TEMPLE_DRAGON_CHEST,  logic->IsAdult && logic->CanUse(RG_FAIRY_BOW) && ((ctx->GetTrickOption(RT_WATER_ADULT_DRAGON) && (logic->HasItem(RG_SILVER_SCALE) || logic->CanUse(RG_IRON_BOOTS))) || ctx->GetTrickOption(RT_WATER_DRAGON_JUMP_DIVE))),
    }, {
        //Exits
        Entrance(RR_WATER_TEMPLE_DRAGON_ROOM, []{return logic->CanHitEyeTargets() && (logic->CanUse(RG_FAIRY_SLINGSHOT) || logic->CanUse(RG_FAIRY_BOW)) && (logic->IsAdult || logic->CanUse(RG_HOVER_BOOTS) || logic->CanUse(RG_HOOKSHOT));}),
    });

    areaTable[RR_WATER_TEMPLE_RISING_TARGET_LEDGE] = Region("Water Temple Pre Boss Room", SCENE_WATER_TEMPLE, {
        //Events
        EventAccess(LOGIC_FAIRY_POT, []{return true;}),
    }, {
        // Locations
        LOCATION(RC_WATER_TEMPLE_MAIN_LEVEL_1_POT_1, logic->CanBreakPots()),
        LOCATION(RC_WATER_TEMPLE_MAIN_LEVEL_1_POT_2, logic->CanBreakPots()),
    }, {
        //Exits
        //As you cannot change the water level from here, we must be able to make the drop on any water level
        //Bronze scale does this alone thanks to the nearby pond cancelling fall damage
        //otherwise we need irons for high level and taking damage for low
        Entrance(RR_WATER_TEMPLE_MAIN,               []{return logic->HasItem(RG_BRONZE_SCALE) || (logic->CanUse(RG_IRON_BOOTS) && logic->TakeDamage());}),
        Entrance(RR_WATER_TEMPLE_3F_CENTRAL_A,       []{return logic->HasItem(RG_LONGSHOT);}),
        Entrance(RR_WATER_TEMPLE_3F_CENTRAL_H,       []{return logic->HasItem(RG_LONGSHOT) && logic->WaterLevel(WL_HIGH);}),
        Entrance(RR_WATER_TEMPLE_3F_CENTRAL_LM,      []{return logic->HasItem(RG_LONGSHOT) && logic->WaterLevel(WL_LOW_OR_MID);}),
        //You can perform RT_WATER_IRONS_CENTRAL_GS from here without hookshot using fire arrows, but it requires a trick to cross
        Entrance(RR_WATER_TEMPLE_PRE_BOSS_ROOM_RAMP, []{return true;}),
    });

    areaTable[RR_WATER_TEMPLE_PRE_BOSS_ROOM_RAMP] = Region("Water Temple Pre Boss Room Ramp", SCENE_WATER_TEMPLE, {}, {}, {
        Entrance(RR_WATER_TEMPLE_RISING_TARGET_LEDGE, []{return true;}),
        Entrance(RR_WATER_TEMPLE_BOSS_ENTRYWAY,       []{return true;}),
    });

#pragma endregion

#pragma region MQ

    areaTable[RR_WATER_TEMPLE_MQ_WATER_ENTRANCE] = Region("Water Temple MQ Water Entrance", SCENE_WATER_TEMPLE, {}, {}, {
        //Exits
        Entrance(RR_WATER_TEMPLE_ENTRYWAY,      []{return logic->HasItem(RG_BRONZE_SCALE) || logic->CanUse(RG_IRON_BOOTS);}),
        Entrance(RR_WATER_TEMPLE_MQ_MAIN,       []{return true;}),
        //If we are not on WL_HIGH, we reach RR_WATER_TEMPLE_MQ_3F_MAIN with hookshot via 2F, otherwise we can reach the platform
        Entrance(RR_WATER_TEMPLE_MQ_3F_CENTRAL, []{return logic->CanUse(RG_HOOKSHOT) || logic->CanUse(RG_HOVER_BOOTS);}),
        Entrance(RR_WATER_TEMPLE_MQ_2F_CENTRAL, []{return logic->MQWaterLevel(WL_LOW_OR_MID);}),
    });

    //This region covers simply existing in the area around the central pillar without being on a specific platform, either swimming or walking on the lakebed
    //Entry should only include being in the correct area, taking any possible fall damage, and floating up to the surface of WL_HIGH if coming from below
    //This area then leads to others based on level and worst-case water timers for follow-up exits from the water's surface
    //remember that any solution that works for any level doesn't need to be given a level, even if that solution is overkill for a lower level
    areaTable[RR_WATER_TEMPLE_MQ_MAIN] = Region("Water Temple MQ Main", SCENE_WATER_TEMPLE, {}, {}, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MQ_WATER_ENTRANCE,         []{return logic->HasItem(RG_BRONZE_SCALE) && logic->MQWaterLevel(WL_HIGH);}),
        Entrance(RR_WATER_TEMPLE_MQ_SIDE_TOWER,             []{return (logic->WaterTimer() >= 24 && logic->CanUse(RG_IRON_BOOTS)) || (logic->MQWaterLevel(WL_MID) && logic->HasItem(RG_GOLDEN_SCALE) && logic->WaterTimer() >= 16) || logic->MQWaterLevel(WL_LOW);}),
        Entrance(RR_WATER_TEMPLE_MQ_3F_CENTRAL,             []{return logic->MQWaterLevel(WL_HIGH) && logic->HasItem(RG_BRONZE_SCALE);}),
        //First water timer uses the hook to go from the top of center to storage room/central pillar as coming from the bottom
        //Second water timer is simply diving down and entering the door as fast as possible from the surface
        Entrance(RR_WATER_TEMPLE_MQ_2F_CENTRAL,             []{return ((logic->MQWaterLevel(WL_LOW) || (logic->CanUse(RG_IRON_BOOTS) && (logic->MQWaterLevel(WL_MID) || logic->WaterTimer() >= 16))) && logic->CanUse(RG_LONGSHOT)) || 
                                                                      ((logic->MQWaterLevel(WL_MID) || (logic->MQWaterLevel(WL_HIGH_OR_MID) && logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 8)) && logic->HasItem(RG_BRONZE_SCALE));}),
        Entrance(RR_WATER_TEMPLE_MQ_PILLAR_1F,              []{return logic->MQWaterLevel(WL_LOW);}),
        //A special entry as we can't set it to high after entering at a lower height
        Entrance(RR_WATER_TEMPLE_MQ_PILLAR_HIGH,            []{return logic->MQWaterLevel(WL_HIGH) && logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 16 && (logic->HasItem(RG_BRONZE_SCALE) || logic->CanUse(RG_LONGSHOT));}),
        Entrance(RR_WATER_TEMPLE_MQ_LIZALFOS_HALLWAY,       []{return (logic->MQWaterLevel(WL_MID) || (logic->MQWaterLevel(WL_HIGH_OR_MID) && logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 16)) && logic->HasItem(RG_BRONZE_SCALE);}),
        Entrance(RR_WATER_TEMPLE_MQ_B1_GATE_SWITCH,         []{return logic->Get(LOGIC_WATER_MQ_B1_SWITCH) && (logic->MQWaterLevel(WL_LOW) || ((logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 24) && logic->HasItem(RG_BRONZE_SCALE)));}),
        Entrance(RR_WATER_TEMPLE_MQ_TRIANGLE_TORCH_ROOM,    []{return logic->Get(LOGIC_WATER_MQ_B1_SWITCH) && ((logic->MQWaterLevel(WL_LOW) && logic->HasItem(RG_SILVER_SCALE)) || (logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 16 &&  (logic->HasItem(RG_BRONZE_SCALE) || logic->CanUse(RG_LONGSHOT))));}),
        //Adult needs to jump in instead of dive for swim access, but you just hold forward. RT_WATER_BK_REGION Isn't relevant unless the Dark Link loop can be done without longshot with other tricks
        Entrance(RR_WATER_TEMPLE_MQ_CRATES_WHIRLPOOLS_ROOM, []{return logic->Get(LOGIC_WATER_MQ_B1_SWITCH) && ((logic->MQWaterLevel(WL_LOW) && logic->HasItem(RG_BRONZE_SCALE)) || (logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 16 && logic->CanUse(RG_HOOKSHOT) || logic->HasItem(RG_BRONZE_SCALE))) && (logic->CanUse(RG_LONGSHOT) || (ctx->GetTrickOption(RT_WATER_BK_REGION) && logic->CanUse(RG_HOVER_BOOTS)));}),
    });

    //This region specifically covers the topmost platform around central pillar
    areaTable[RR_WATER_TEMPLE_MQ_3F_CENTRAL] = Region("Water Temple MQ 3F Central", SCENE_WATER_TEMPLE, {}, {}, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MQ_MAIN,                []{return true;}),
        Entrance(RR_WATER_TEMPLE_MQ_WATER_ENTRANCE,      []{return logic->CanUse(RG_LONGSHOT) || logic->CanUse(RG_HOVER_BOOTS);}),
        Entrance(RR_WATER_TEMPLE_MQ_2F_CENTRAL,          []{return (logic->MQWaterLevel(WL_LOW_OR_MID) || (logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 16)) && logic->CanUse(RG_HOOKSHOT);}),
        Entrance(RR_WATER_TEMPLE_MQ_PILLAR_HIGH,         []{return logic->MQWaterLevel(WL_HIGH) && logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 16 && logic->CanUse(RG_HOOKSHOT);}),
        Entrance(RR_WATER_TEMPLE_MQ_3F_NORTH_LEDGE,      []{return (logic->MQWaterLevel(WL_HIGH) && logic->CanUse(RG_LONGSHOT)) || (ctx->GetTrickOption(RT_HOVER_BOOST_SIMPLE) && ctx->GetTrickOption(RT_DAMAGE_BOOST_SIMPLE) && logic->HasExplosives() && logic->CanUse(RG_HOVER_BOOTS));}),
        //Jumping across is possible but a trick due to the janky ledge
        Entrance(RR_WATER_TEMPLE_MQ_HIGH_EMBLEM,         []{return logic->CanUse(RG_HOOKSHOT) || (logic->IsAdult && logic->CanUse(RG_HOVER_BOOTS));}),
        //room access is (logic->IsAdult || (logic->HasItem(RG_BRONZE_SCALE) || logic->CanUse(RG_HOVER_BOOTS) || logic->CanUse(RG_HOOKSHOT)))
        Entrance(RR_WATER_TEMPLE_MQ_WATERFALL,           []{return logic->SmallKeys(SCENE_WATER_TEMPLE, 1) && logic->MQWaterLevel(WL_HIGH) && logic->CanUse(RG_LONGSHOT);}),
        //this swimless jump with irons may be a trick as you have to put irons on quite late.
        Entrance(RR_WATER_TEMPLE_MQ_LIZALFOS_HALLWAY,    []{return (logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 16) || logic->MQWaterLevel(WL_LOW_OR_MID);}),
    });

    //This region specifically covers walking on the lower platform around central pillar. This is underwater when WL_HIGH
    //RR_WATER_TEMPLE_MQ_PILLAR_HIGH should be accessed directly to use the central pillar door while at WL_HIGH
    areaTable[RR_WATER_TEMPLE_MQ_2F_CENTRAL] = Region("Water Temple MQ 2F Central", SCENE_WATER_TEMPLE, {}, {}, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MQ_MAIN,                  []{return true;}),
        Entrance(RR_WATER_TEMPLE_MQ_3F_CENTRAL,            []{return logic->CanUse(RG_HOOKSHOT);}),
        Entrance(RR_WATER_TEMPLE_MQ_CENTRAL_PILLAR_2F,     []{return logic->MQWaterLevel(WL_LOW_OR_MID);}),
        Entrance(RR_WATER_TEMPLE_MQ_STORAGE_ROOM,          []{return logic->CanUse(RG_HOOKSHOT);}),
        Entrance(RR_WATER_TEMPLE_MQ_BEHIND_BLUE_SWITCH_2F, []{return logic->MQWaterLevel(WL_LOW_OR_MID) && (logic->IsAdult || logic->CanUse(RG_HOVER_BOOTS)) && logic->CanUse(RG_HOOKSHOT);}),
        Entrance(RR_WATER_TEMPLE_MQ_LIZALFOS_HALLWAY,      []{return logic->MQWaterLevel(WL_LOW_OR_MID) && logic->CanUse(RG_HOVER_BOOTS);}),
    });

    areaTable[RR_WATER_TEMPLE_MQ_HIGH_EMBLEM] = Region("Water Temple MQ High Emblem", SCENE_WATER_TEMPLE, {
        //Events
        EventAccess(LOGIC_WATER_SCARECROW, []{return true;}),
        EventAccess(LOGIC_WATER_HIGH,                []{return logic->CanUse(RG_ZELDAS_LULLABY);}),
    }, {}, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MQ_3F_CENTRAL, []{return true;}),
        Entrance(RR_WATER_TEMPLE_MQ_MAIN,       []{return true;}),
    });

    areaTable[RR_WATER_TEMPLE_MQ_3F_NORTH_LEDGE] = Region("Water Temple MQ 3F North Ledge", SCENE_WATER_TEMPLE, {}, {}, {
        //Exits
        //what we need if WL_LOW, we can't guarantee repeated access otherwise.
        Entrance(RR_WATER_TEMPLE_MQ_MAIN,           []{return logic->HasItem(RG_BRONZE_SCALE) || logic->TakeDamage();}),
        Entrance(RR_WATER_TEMPLE_MQ_3F_CENTRAL,     []{return logic->CanUse(RG_LONGSHOT);}),
        Entrance(RR_WATER_TEMPLE_MQ_BOSS_DOOR_RAMP, []{return true;}),
    });

    areaTable[RR_WATER_TEMPLE_MQ_BOSS_DOOR_RAMP] = Region("Water Temple MQ Boss Door Ramp", SCENE_WATER_TEMPLE, {}, {}, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MQ_3F_NORTH_LEDGE, []{return true;}),
        Entrance(RR_WATER_TEMPLE_MQ_BOSS_DOOR,      []{return logic->CanUse(RG_LONGSHOT) || logic->CanUse(RG_ICE_ARROWS) || logic->CanUse(RG_NAYRUS_LOVE);}),
    });

    areaTable[RR_WATER_TEMPLE_MQ_BOSS_DOOR] = Region("Water Temple MQ Boss Door", SCENE_WATER_TEMPLE, {}, {}, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MQ_BOSS_DOOR_RAMP, []{return logic->CanUse(RG_ICE_ARROWS) || logic->TakeDamage();}),
        Entrance(RR_WATER_TEMPLE_BOSS_ENTRYWAY,     []{return true;}),
    });

    areaTable[RR_WATER_TEMPLE_MQ_SIDE_TOWER] = Region("Water Temple MQ East Tower", SCENE_WATER_TEMPLE, {
        //Events
        //if we can't reach these, we can't move the water at all, so no need to specify level or account for WL_LOW access here
        //review is some way to play ocarina underwater exists
        EventAccess(LOGIC_WATER_COULD_LOW,     []{return true;}),
        EventAccess(LOGIC_WATER_LOW, []{return logic->CanUse(RG_ZELDAS_LULLABY);}),
        //Reserved for glitches/tricks that could do this
        //EventAccess(LOGIC_WATER_LOW_FROM_MIDDLE,  []{return false;}),
    }, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_MQ_MAP_CHEST,           logic->MQWaterLevel(WL_HIGH) && logic->HasFireSource() && logic->CanUse(RG_HOOKSHOT)),
        LOCATION(RC_WATER_TEMPLE_MQ_LONGSHOT_CHEST,      (logic->MQWaterLevel(WL_MID) && logic->CanUse(RG_HOOKSHOT)) || (logic->MQWaterLevel(WL_HIGH_OR_MID) && logic->CanOpenUnderwaterChest())),
        LOCATION(RC_WATER_TEMPLE_MQ_LOWER_TORCHES_POT_1, (logic->MQWaterLevel(WL_LOW) && logic->CanBreakPots()) || (logic->CanUse(RG_IRON_BOOTS) && logic->CanUse(RG_HOOKSHOT) && logic->WaterTimer() >= 16)),
        LOCATION(RC_WATER_TEMPLE_MQ_LOWER_TORCHES_POT_2, (logic->MQWaterLevel(WL_LOW) && logic->CanBreakPots()) || (logic->CanUse(RG_IRON_BOOTS) && logic->CanUse(RG_HOOKSHOT) && logic->WaterTimer() >= 16)),
    }, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MQ_EAST_TOWER_3F_ROOM, []{return logic->MQWaterLevel(WL_HIGH) && logic->HasFireSource();}),
        Entrance(RR_WATER_TEMPLE_MQ_EAST_TOWER_1F_ROOM, []{return logic->MQWaterLevel(WL_LOW) && (logic->CanUse(RG_FAIRY_BOW) || logic->CanUse(RG_DINS_FIRE) || logic->CanUse(RG_STICKS));}),
    });

    areaTable[RR_WATER_TEMPLE_MQ_EAST_TOWER_3F_ROOM] = Region("Water Temple MQ East Tower 3F Room", SCENE_WATER_TEMPLE, {}, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_MQ_MAP_CHEST, logic->CanUse(RG_HOOKSHOT)),
    }, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MQ_SIDE_TOWER, []{return logic->CanKillEnemy(RE_STALFOS, ED_CLOSE, true, 4);}),
    });

    //Raising the targets by clearing this room achieves nothing logically because it requires WL_LOW to do and hookshot to use, which implies access to WL_MID and WL_HIGH already
    areaTable[RR_WATER_TEMPLE_MQ_EAST_TOWER_1F_ROOM] = Region("Water Temple MQ East Tower 1F Room", SCENE_WATER_TEMPLE, {}, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_MQ_COMPASS_CHEST, logic->CanKillEnemy(RE_LIZALFOS) && logic->CanKillEnemy(RE_SPIKE)),
    }, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MQ_SIDE_TOWER, []{return true;}),
    });

    //This area assumes we entered through the lower door, so water is low and cannot be changed without leaving.
    areaTable[RR_WATER_TEMPLE_MQ_PILLAR_1F] = Region("Water Temple MQ Central Pillar 1F", SCENE_WATER_TEMPLE, {
        //Events
        //This is harder than the other possibilities as you have to move between shots on top of the extra range, but there's basically no universe this should matter.
        EventAccess(LOGIC_WATER_MQ_B1_SWITCH, []{return ctx->GetTrickOption(RT_WATER_MQ_CENTRAL_PILLAR) && logic->CanUse(RG_FIRE_ARROWS);}),
    }, {}, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MQ_MAIN,                []{return logic->MQWaterLevel(WL_LOW);}),
        Entrance(RR_WATER_TEMPLE_MQ_PILLAR_HIGH, []{return logic->MQWaterLevel(WL_HIGH) && ctx->GetTrickOption(RT_WATER_FW_CENTRAL_GS) && logic->CanUse(RG_FARORES_WIND) && logic->HasItem(RG_BRONZE_SCALE);}),
        //I don't know if this FW trick can ever matter but maybe it's needed to get child to CENTRAL_2F or something
        Entrance(RR_WATER_TEMPLE_MQ_CENTRAL_PILLAR_2F,   []{return logic->CanUse(RG_HOOKSHOT) || (logic->MQWaterLevel(WL_MID) && ctx->GetTrickOption(RT_WATER_FW_CENTRAL_GS) && logic->CanUse(RG_FARORES_WIND) && logic->HasItem(RG_BRONZE_SCALE));}),
        //if the gate is open, you sink straight in, so you can't climb up this way in logic without swimming
        Entrance(RR_WATER_TEMPLE_MQ_CENTRAL_PILLAR_B1,   []{return logic->Get(LOGIC_WATER_MQ_B1_OPENED_PILLAR) && logic->MQWaterLevel(WL_HIGH_OR_MID) && ctx->GetTrickOption(RT_WATER_FW_CENTRAL_GS) && logic->CanUse(RG_FARORES_WIND) && logic->CanUse(RG_IRON_BOOTS) && logic->CanUse(RG_ZORA_TUNIC);}),
    });

    //If we enter here in WL_HIGH, go to RR_WATER_TEMPLE_MQ_PILLAR_HIGH instead, Assumes WL_MID_OR_LOW
    areaTable[RR_WATER_TEMPLE_MQ_CENTRAL_PILLAR_2F] = Region("Water Temple MQ Central Pillar 2F", SCENE_WATER_TEMPLE, {
        //Events
        EventAccess(LOGIC_WATER_COULD_MIDDLE,         []{return true;}),
        EventAccess(LOGIC_WATER_MIDDLE,               []{return logic->CanUse(RG_ZELDAS_LULLABY);}),
        //It's possible to do this even on low water, but more awkward. I'm not sure if it's even possible for it to be relevant though.
        EventAccess(LOGIC_WATER_MQ_B1_OPENED_PILLAR,  []{return ctx->GetTrickOption(RT_WATER_MQ_CENTRAL_PILLAR) && logic->CanUse(RG_FIRE_ARROWS);}),
        //this could theoretically matter once OI and equip swap is in logic, as one age may be able to get here dry and not wet, and the other may not be able to OI, but as you can OI with hookshot it probably never happens
        //EventAccess(LOGIC_WATER_MQ_PILLAR_SOT_BLOCK,  []{return logic->CanUse(RG_HOOKSHOT) && logic->CanUse(RG_SONG_OF_TIME);}),
    }, {}, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MQ_2F_CENTRAL,          []{return true;}),
        Entrance(RR_WATER_TEMPLE_MQ_PILLAR_HIGH, []{return logic->MQWaterLevel(WL_HIGH) && logic->CanUse(RG_FARORES_WIND) && (logic->HasItem(RG_BRONZE_SCALE) || logic->CanUse(RG_IRON_BOOTS));}),
        Entrance(RR_WATER_TEMPLE_MQ_CENTRAL_PILLAR_B1,   []{return logic->Get(LOGIC_WATER_MQ_B1_OPENED_PILLAR) && logic->MQWaterLevel(WL_MID) && logic->CanUse(RG_IRON_BOOTS) && logic->CanUse(RG_ZORA_TUNIC);}),
    });

    areaTable[RR_WATER_TEMPLE_MQ_PILLAR_HIGH] = Region("Water Temple MQ Central Pillar High", SCENE_WATER_TEMPLE, {
        //Events
        EventAccess(LOGIC_WATER_MQ_B1_OPENED_PILLAR, []{return ((logic->CanUse(RG_SONG_OF_TIME) && logic->CanUse(RG_DINS_FIRE)) || (ctx->GetTrickOption(RT_WATER_MQ_CENTRAL_PILLAR) && logic->CanUse(RG_FIRE_ARROWS))) && (logic->HasItem(RG_BRONZE_SCALE) || (logic->CanUse(RG_IRON_BOOTS) && logic->CanUse(RG_LONGSHOT) && logic->CanJumpslash()));}),
    }, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_MQ_CENTRAL_PILLAR_UPPER_CRATE_1, logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_CENTRAL_PILLAR_UPPER_CRATE_2, logic->CanBreakCrates()),
    }, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MQ_CENTRAL_PILLAR_B1, []{return logic->Get(LOGIC_WATER_MQ_B1_SWITCH) && logic->CanUse(RG_IRON_BOOTS) && logic->CanUse(RG_ZORA_TUNIC);}),
    });

    //Assuming tunic and irons was checked on entry
    areaTable[RR_WATER_TEMPLE_MQ_CENTRAL_PILLAR_B1] = Region("Water Temple MQ Central Pillar B1", SCENE_WATER_TEMPLE, {}, {}, {
        //Exits
        //Can't know water level, so we'll just assume any possibility and skip to MAIN
        Entrance(RR_WATER_TEMPLE_MQ_MAIN,                    []{return logic->Get(LOGIC_WATER_MQ_B1_OPENED_PILLAR) && logic->CanUse(RG_IRON_BOOTS) && logic->HasItem(RG_BRONZE_SCALE);}),
        //Child needs to release irons for height to push down the larger "peg", however they can push the lower one down by climbing and then hit the switch through the larger peg, but it's a trick
        Entrance(RR_WATER_TEMPLE_MQ_CENTRAL_PILLAR_B1_FINAL, []{return ((logic->IsAdult && logic->CanUse(RG_LONGSHOT)) || (logic->CanUse(RG_HOOKSHOT) && logic->HasItem(RG_BRONZE_SCALE)));}),
    });

    areaTable[RR_WATER_TEMPLE_MQ_CENTRAL_PILLAR_B1_FINAL] = Region("Water Temple MQ Central Pillar B1 Final", SCENE_WATER_TEMPLE, {}, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_MQ_CENTRAL_PILLAR_CHEST,          logic->CanUse(RG_HOOKSHOT)),
        LOCATION(RC_WATER_TEMPLE_MQ_CENTRAL_PILLAR_LOWER_CRATE_1,  logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_CENTRAL_PILLAR_LOWER_CRATE_2,  logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_CENTRAL_PILLAR_LOWER_CRATE_3,  logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_CENTRAL_PILLAR_LOWER_CRATE_4,  logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_CENTRAL_PILLAR_LOWER_CRATE_5,  logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_CENTRAL_PILLAR_LOWER_CRATE_6,  logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_CENTRAL_PILLAR_LOWER_CRATE_7,  logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_CENTRAL_PILLAR_LOWER_CRATE_8,  logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_CENTRAL_PILLAR_LOWER_CRATE_9,  logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_CENTRAL_PILLAR_LOWER_CRATE_10, logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_CENTRAL_PILLAR_LOWER_CRATE_11, logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_CENTRAL_PILLAR_LOWER_CRATE_12, logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_CENTRAL_PILLAR_LOWER_CRATE_13, logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_CENTRAL_PILLAR_LOWER_CRATE_14, logic->CanBreakCrates()),
    }, {});

    //Region exists to add crate/pot/box locations
    areaTable[RR_WATER_TEMPLE_MQ_STORAGE_ROOM] = Region("Water Temple MQ Storage Room", SCENE_WATER_TEMPLE, {}, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_A_POT_1,           logic->CanBreakPots()),
        LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_A_POT_2,           logic->CanBreakPots()),
        LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_A_POT_3,           logic->CanBreakPots()),
        LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_A_CRATE_1,         logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_A_CRATE_2,         logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_A_CRATE_3,         logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_A_CRATE_4,         logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_A_CRATE_5,         logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_A_CRATE_6,         logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_A_CRATE_7,         logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_A_SMALL_CRATE_1,   logic->CanBreakSmallCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_A_SMALL_CRATE_2,   logic->CanBreakSmallCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_A_SMALL_CRATE_3,   logic->CanBreakSmallCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_A_SMALL_CRATE_4,   logic->CanBreakSmallCrates()),
    }, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MQ_MAIN, []{return logic->MQWaterLevel(WL_LOW_OR_MID) || (logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 8);}),
    });

    areaTable[RR_WATER_TEMPLE_MQ_BEHIND_BLUE_SWITCH_2F] = Region("Water Temple MQ Behind Blue Switch 2F", SCENE_WATER_TEMPLE, {}, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_MQ_GS_STORAGE_ROOM_POT_1,              logic->CanBreakPots()),
        LOCATION(RC_WATER_TEMPLE_MQ_GS_STORAGE_ROOM_POT_2,              logic->CanBreakPots()),
        LOCATION(RC_WATER_TEMPLE_MQ_GS_STORAGE_ROOM_POT_3,              logic->CanBreakPots()),
        LOCATION(RC_WATER_TEMPLE_MQ_GS_STORAGE_ROOM_LOWER_CRATE_1,      logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_GS_STORAGE_ROOM_LOWER_CRATE_2,      logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_GS_STORAGE_ROOM_LOWER_CRATE_3,      logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_GS_STORAGE_ROOM_LOWER_CRATE_4,      logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_GS_STORAGE_ROOM_LOWER_CRATE_5,      logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_GS_STORAGE_ROOM_LOWER_CRATE_6,      logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_GS_STORAGE_ROOM_LOWER_SMALL_CRATE,  logic->CanBreakSmallCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_GS_STORAGE_ROOM_UPPER_CRATE_1,      logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_GS_STORAGE_ROOM_UPPER_CRATE_2,      logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_GS_STORAGE_ROOM_UPPER_SMALL_CRATE,  logic->CanBreakSmallCrates()),
    }, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MQ_MAIN,                  []{return true;}),
        Entrance(RR_WATER_TEMPLE_MQ_BEHIND_BLUE_SWITCH_3F, []{return logic->CanUse(RG_LONGSHOT);}),
    });

    areaTable[RR_WATER_TEMPLE_MQ_BEHIND_BLUE_SWITCH_3F] = Region("Water Temple MQ Behind Blue Switch 2F", SCENE_WATER_TEMPLE, {}, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_MQ_GS_BEFORE_UPPER_WATER_SWITCH, logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA)),
    }, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MQ_BEHIND_BLUE_SWITCH_2F, []{return true;}),
        Entrance(RR_WATER_TEMPLE_MQ_HIGH_EMBLEM,           []{return true;}),
    });

    areaTable[RR_WATER_TEMPLE_MQ_LIZALFOS_HALLWAY] = Region("Water Temple MQ Lizalfos Hallway", SCENE_WATER_TEMPLE, {}, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_MQ_LIZALFOS_HALLWAY_WEST_POT,     logic->CanBreakPots()),
        LOCATION(RC_WATER_TEMPLE_MQ_LIZALFOS_HALLWAY_SOUTH_POT,    logic->CanBreakPots()),
        LOCATION(RC_WATER_TEMPLE_MQ_LIZALFOS_HALLWAY_SE_POT,       logic->CanBreakPots()),
        LOCATION(RC_WATER_TEMPLE_MQ_LIZALFOS_HALLWAY_CRATE_1,      logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_LIZALFOS_HALLWAY_CRATE_2,      logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_LIZALFOS_HALLWAY_CRATE_3,      logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_LIZALFOS_HALLWAY_ROOM_CRATE_1, logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_LIZALFOS_HALLWAY_ROOM_CRATE_2, logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_LIZALFOS_HALLWAY_ROOM_CRATE_3, logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_LIZALFOS_HALLWAY_ROOM_CRATE_4, logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_LIZALFOS_HALLWAY_ROOM_CRATE_5, logic->CanBreakCrates()),
    }, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MQ_LIZALFOS_CAGE, []{return logic->MQWaterLevel(WL_LOW_OR_MID) && logic->CanUse(RG_DINS_FIRE);}),
        //this technically exists, but only complicates things, uncomment if some edge case/glitch can use RR_WATER_TEMPLE_MQ_LIZALFOS_HALLWAY to reach RR_WATER_TEMPLE_MQ_3F_CENTRAL, or if a void warp goes here
        /*Entrance(RR_WATER_TEMPLE_MQ_3F_EAST_LEDGE, []{return (logic->CanUse(RG_HOOKSHOT) && (logic->HasItem(RG_BRONZE_SCALE) || logic->CanUse(RG_IRON_BOOTS))) || (logic->MQWaterLevel(WL_LOW_OR_MID) && logic->CanUse(RG_HOOKSHOT)) || logic->MQWaterLevel(WL_HIGH) && (logic->HasItem(RG_BRONZE_SCALE));}),
    });

    areaTable[RR_WATER_TEMPLE_MQ_3F_EAST_LEDGE] = Region("Water Temple MQ 3F East Ledge", SCENE_WATER_TEMPLE, {}, {}, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MQ_MAIN,       []{return true;}),
        Entrance(RR_WATER_TEMPLE_MQ_3F_CENTRAL, []{return logic->CanUse(RG_HOOKSHOT) || logic->CanUse(RG_HOVER_BOOTS);}),*/
    });

    areaTable[RR_WATER_TEMPLE_MQ_LIZALFOS_CAGE] = Region("Water Temple MQ Lizalfos Cage", SCENE_WATER_TEMPLE, {}, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_MQ_GS_LIZALFOS_HALLWAY,           logic->CanKillEnemy(RE_GOLD_SKULLTULA)),
        LOCATION(RC_WATER_TEMPLE_MQ_LIZALFOS_CAGE_SOUTH_POT,       logic->CanBreakPots()),
        LOCATION(RC_WATER_TEMPLE_MQ_LIZALFOS_CAGE_NORTH_POT,       logic->CanBreakPots()),
        LOCATION(RC_WATER_TEMPLE_MQ_LIZALFOS_HALLWAY_GATE_CRATE_1, logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_LIZALFOS_HALLWAY_GATE_CRATE_2, logic->CanBreakCrates()),
    }, {});

    //This room exists to hold the wonderitems that drop from the emblems here. Specifically this assumes you are standing on the final ledge
    areaTable[RR_WATER_TEMPLE_MQ_WATERFALL] = Region("Water Temple Waterfall", SCENE_WATER_TEMPLE, {}, {}, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MQ_3F_CENTRAL,        []{return logic->SmallKeys(SCENE_WATER_TEMPLE, 1) && logic->CanUse(RG_LONGSHOT);}),
        Entrance(RR_WATER_TEMPLE_MQ_STALFOS_PIT,       []{return true;}),
    });

    areaTable[RR_WATER_TEMPLE_MQ_STALFOS_PIT] = Region("Water Temple MQ Stalfos Pit", SCENE_WATER_TEMPLE, {}, {}, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MQ_WATERFALL,         []{return logic->Get(LOGIC_WATER_MQ_STALFOS_PIT);}),
        Entrance(RR_WATER_TEMPLE_MQ_STALFOS_PIT_LOWER, []{return true;}),
        Entrance(RR_WATER_TEMPLE_MQ_STALFOS_PIT_POTS,  []{return (logic->Get(LOGIC_WATER_MQ_STALFOS_PIT) && logic->IsAdult && logic->CanUse(RG_HOOKSHOT)) || logic->CanUse(RG_HOVER_BOOTS);}),
        Entrance(RR_WATER_TEMPLE_MQ_STALFOS_PIT_UPPER, []{return logic->Get(LOGIC_WATER_MQ_STALFOS_PIT) && logic->CanUse(RG_LONGSHOT);}),
    });

    areaTable[RR_WATER_TEMPLE_MQ_STALFOS_PIT_LOWER] = Region("Water Temple MQ Stalfos Pit Lower", SCENE_WATER_TEMPLE, {
        //Events
        EventAccess(LOGIC_WATER_MQ_STALFOS_PIT, []{return ((logic->IsAdult && logic->CanKillEnemy(RE_STALFOS, ED_CLOSE, true, 3, false, true)) || (logic->CanUse(RG_IRON_BOOTS) && logic->CanUse(RG_HOOKSHOT) && logic->CanKillEnemy(RE_STALFOS, ED_BOMB_THROW, true, 3, false, true)));}),
    }, {}, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MQ_STALFOS_PIT,       []{return logic->CanUse(RG_HOOKSHOT) && (logic->IsAdult || (logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 8));}),
        Entrance(RR_WATER_TEMPLE_MQ_STALFOS_PIT_POTS,  []{return (logic->IsAdult && logic->CanUse(RG_HOOKSHOT)) || (logic->CanUse(RG_HOOKSHOT) && (logic->IsAdult || logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 8) && (logic->CanUse(RG_HOVER_BOOTS) || logic->Get(LOGIC_WATER_MQ_STALFOS_PIT)));}),
        Entrance(RR_WATER_TEMPLE_MQ_STALFOS_PIT_UPPER, []{return logic->Get(LOGIC_WATER_MQ_STALFOS_PIT) && (logic->IsAdult || logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 8) && logic->CanUse(RG_HOOKSHOT);}),
    });

    //also includes the suns fairy in the middle
    areaTable[RR_WATER_TEMPLE_MQ_STALFOS_PIT_POTS] = Region("Water Temple MQ Stalfos Pit Pots", SCENE_WATER_TEMPLE, {
        //Events
        EventAccess(LOGIC_FAIRY_POT, []{return true;}),
        EventAccess(LOGIC_NUT_POT,   []{return true;}),
    }, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_MQ_STALFOS_PIT_SOUTH_POT,     logic->CanBreakPots()),
        LOCATION(RC_WATER_TEMPLE_MQ_STALFOS_PIT_MIDDLE_POT,    logic->CanBreakPots()),
        LOCATION(RC_WATER_TEMPLE_MQ_STALFOS_PIT_NORTH_POT,     logic->CanBreakPots()),
        LOCATION(RC_WATER_TEMPLE_MQ_DARK_LINK_PILAR_SUN_FAIRY, logic->CanUse(RG_SUNS_SONG)),
    }, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MQ_STALFOS_PIT,       []{return logic->Get(LOGIC_WATER_MQ_STALFOS_PIT) && (logic->CanUse(RG_HOVER_BOOTS) || logic->CanUse(RG_LONGSHOT));}),
        Entrance(RR_WATER_TEMPLE_MQ_STALFOS_PIT_LOWER, []{return true;}),
        Entrance(RR_WATER_TEMPLE_MQ_STALFOS_PIT_UPPER, []{return logic->Get(LOGIC_WATER_MQ_STALFOS_PIT) && logic->CanUse(RG_HOOKSHOT);}),
    });

    //specifically the area past the spikes
    areaTable[RR_WATER_TEMPLE_MQ_STALFOS_PIT_UPPER] = Region("Water Temple MQ Stalfos Pit Upper", SCENE_WATER_TEMPLE, {}, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_MQ_BEFORE_DARK_LINK_POT_1,     logic->CanBreakPots()),
        LOCATION(RC_WATER_TEMPLE_MQ_BEFORE_DARK_LINK_POT_2,     logic->CanBreakPots()),
        LOCATION(RC_WATER_TEMPLE_MQ_DARK_LINK_LEFT_STORM_FAIRY, logic->CanUse(RG_SONG_OF_STORMS)),
        LOCATION(RC_WATER_TEMPLE_MQ_DARK_LINK_RIGHT_SUN_FAIRY,  logic->CanUse(RG_SUNS_SONG)),
    }, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MQ_STALFOS_PIT_LOWER, []{return logic->IsAdult || logic->TakeDamage() || logic->CanUse(RG_GORON_TUNIC);}),
        Entrance(RR_WATER_TEMPLE_MQ_STALFOS_PIT_POTS,  []{return logic->IsAdult || logic->TakeDamage() || logic->CanUse(RG_GORON_TUNIC);}),
    });

    areaTable[RR_WATER_TEMPLE_MQ_DARK_LINK_ROOM] = Region("Water Temple MQ Dark Link Room", SCENE_WATER_TEMPLE, {}, {}, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MQ_STALFOS_PIT_UPPER, []{return Here(RR_WATER_TEMPLE_MQ_DARK_LINK_ROOM, []{return logic->CanKillEnemy(RE_DARK_LINK);});}),
        Entrance(RR_WATER_TEMPLE_MQ_AFTER_DARK_LINK,   []{return Here(RR_WATER_TEMPLE_MQ_DARK_LINK_ROOM, []{return logic->CanKillEnemy(RE_DARK_LINK);});}),
    });

    areaTable[RR_WATER_TEMPLE_MQ_AFTER_DARK_LINK] = Region("Water Temple MQ After Dark Link", SCENE_WATER_TEMPLE, {
        //Events
        EventAccess(LOGIC_FAIRY_POT, []{return true;}),
    }, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_MQ_AFTER_DARK_LINK_POT_1, logic->CanBreakPots()),
        LOCATION(RC_WATER_TEMPLE_MQ_AFTER_DARK_LINK_POT_2, logic->CanBreakPots()),
    }, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MQ_DARK_LINK_ROOM,  []{return true;}),
        Entrance(RR_WATER_TEMPLE_MQ_RIVER_SKULL,     []{return logic->CanUse(RG_HOOKSHOT) && (logic->HasItem(RG_BRONZE_SCALE) || (logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 8) || logic->CanUse(RG_LONGSHOT));}),
    });

    //if we can use hookshot, we are standing on the targets, otherwise assume we're in the water
    areaTable[RR_WATER_TEMPLE_MQ_RIVER_SKULL] = Region("Water Temple MQ River Skull", SCENE_WATER_TEMPLE, {}, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_MQ_GS_RIVER, logic->CanUse(RG_LONGSHOT) || (logic->CanUse(RG_IRON_BOOTS) && logic->CanUse(RG_HOOKSHOT))),
    }, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MQ_RIVER_POTS, []{return logic->HasItem(RG_BRONZE_SCALE) || logic->CanUse(RG_LONGSHOT);}),
    });

    areaTable[RR_WATER_TEMPLE_MQ_RIVER_POTS] = Region("Water Temple MQ River Pots", SCENE_WATER_TEMPLE, {
        //Events
        EventAccess(LOGIC_FAIRY_POT, []{return true;}),
    }, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_MQ_RIVER_POT_1, logic->CanBreakPots()),
        LOCATION(RC_WATER_TEMPLE_MQ_RIVER_POT_2, logic->CanBreakPots()),
    }, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MQ_RIVER_SKULL,        []{return logic->CanUse(RG_LONGSHOT) || (logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 8 && logic->CanUse(RG_HOOKSHOT));}),
        //You don't need to swim for this if you put irons on in midair and hold forward while aiming for the tunnel with a tight angle, but if you miss you have to void unless you have a hook. It's only relevant with glitches anyway
        Entrance(RR_WATER_TEMPLE_MQ_DRAGON_ROOM_TUNNEL, []{return logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 16;}),
        Entrance(RR_WATER_TEMPLE_MQ_DRAGON_ROOM_ALCOVE, []{return logic->HasItem(RG_SILVER_SCALE) || (logic->IsAdult && logic->HasItem(RG_BRONZE_SCALE) && ctx->GetTrickOption(RT_WATER_DRAGON_JUMP_DIVE));}),
        Entrance(RR_WATER_TEMPLE_MQ_DRAGON_ROOM_DOOR,   []{return logic->HasItem(RG_BRONZE_SCALE) || logic->CanUse(RG_LONGSHOT) || (logic->CanUse(RG_HOVER_BOOTS) && logic->CanJumpslash());}),
    });

    //This region assumes Iron boots to access
    areaTable[RR_WATER_TEMPLE_MQ_DRAGON_ROOM_TUNNEL] = Region("Water Temple MQ Dragon Room Tunnel", SCENE_WATER_TEMPLE, {}, 
    {
        //Locations
        LOCATION(RC_WATER_TEMPLE_MQ_DRAGON_ROOM_SUBMERGED_CRATE_1, logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_DRAGON_ROOM_SUBMERGED_CRATE_2, logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_DRAGON_ROOM_SUBMERGED_CRATE_3, logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_DRAGON_ROOM_SUBMERGED_CRATE_4, logic->CanBreakCrates()),
    },
    {
        //Exits
        Entrance(RR_WATER_TEMPLE_MQ_RIVER_POTS,         []{return logic->CanUse(RG_LONGSHOT);}),
        Entrance(RR_WATER_TEMPLE_MQ_DRAGON_ROOM_ALCOVE, []{return logic->HasItem(RG_BRONZE_SCALE) || logic->CanUse(RG_HOOKSHOT);}),
        Entrance(RR_WATER_TEMPLE_MQ_DRAGON_ROOM_DOOR,   []{return logic->HasItem(RG_BRONZE_SCALE) || logic->CanUse(RG_LONGSHOT);}),
    });

    areaTable[RR_WATER_TEMPLE_MQ_DRAGON_ROOM_ALCOVE] = Region("Water Temple MQ Dragon Room Alcove", SCENE_WATER_TEMPLE, {
        //Events
        EventAccess(LOGIC_WATER_MQ_DRAGON_TORCHES, []{return logic->HasFireSource();}),
    }, 
    {
        //Locations
        LOCATION(RC_WATER_TEMPLE_MQ_DRAGON_ROOM_TORCHES_CRATE_1,        logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_DRAGON_ROOM_TORCHES_CRATE_2,        logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_DRAGON_ROOM_TORCHES_SMALL_CRATE_1,  logic->CanBreakSmallCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_DRAGON_ROOM_TORCHES_SMALL_CRATE_2,  logic->CanBreakSmallCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_DRAGON_ROOM_TORCHES_SMALL_CRATE_3,  logic->CanBreakSmallCrates()),
    }, 
    {
        //Exits
        Entrance(RR_WATER_TEMPLE_MQ_DRAGON_ROOM_TUNNEL, []{return logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 16;}),
        Entrance(RR_WATER_TEMPLE_MQ_DRAGON_ROOM_DOOR,   []{return logic->HasItem(RG_SILVER_SCALE);}),
    });

    areaTable[RR_WATER_TEMPLE_MQ_DRAGON_ROOM_DOOR] = Region("Water Temple MQ Dragon Room Door", SCENE_WATER_TEMPLE, {}, 
    {
        //Locations
        LOCATION(RC_WATER_TEMPLE_MQ_DRAGON_ROOM_DOOR_CRATE_1, logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_DRAGON_ROOM_DOOR_CRATE_2, logic->CanBreakCrates()),
    }, 
    {
        //Exits
        Entrance(RR_WATER_TEMPLE_MQ_RIVER_POTS,            []{return logic->CanUse(RG_LONGSHOT);}),
        Entrance(RR_WATER_TEMPLE_MQ_DRAGON_ROOM_TUNNEL,    []{return logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 16 && logic->CanUse(RG_HOOKSHOT);}),
        Entrance(RR_WATER_TEMPLE_MQ_DRAGON_ROOM_ALCOVE,    []{return logic->HasItem(RG_SILVER_SCALE);}),
        Entrance(RR_WATER_TEMPLE_MQ_BOSS_KEY_ROOM_SWITCH,  []{return logic->Get(LOGIC_WATER_MQ_DRAGON_TORCHES);}),
    });

    areaTable[RR_WATER_TEMPLE_MQ_BOSS_KEY_ROOM_SWITCH] = Region("Water Temple MQ Boss Key Room Switch", SCENE_WATER_TEMPLE, {}, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_MQ_BOSS_KEY_POT,           logic->CanBreakPots()),
        LOCATION(RC_WATER_TEMPLE_MQ_BK_ROOM_UPPER_CRATE,    logic->CanBreakCrates()),
    }, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MQ_DRAGON_ROOM_DOOR,    []{return true;}),
        Entrance(RR_WATER_TEMPLE_MQ_BOSS_KEY_ROOM_PIT,   []{return true;}),
        Entrance(RR_WATER_TEMPLE_MQ_BOSS_KEY_ROOM_CHEST, []{return logic->CanHitSwitch() && Here(RR_WATER_TEMPLE_MQ_BOSS_KEY_ROOM_SWITCH, []{return logic->CanUse(RG_DINS_FIRE);});}),
    });

    //this exists for the crates in preparation for clips through the grate
    areaTable[RR_WATER_TEMPLE_MQ_BOSS_KEY_ROOM_PIT] = Region("Water Temple MQ Boss Key Room Pit", SCENE_WATER_TEMPLE, {}, 
    {
        //Locations
        LOCATION(RC_WATER_TEMPLE_MQ_BK_ROOM_LOWER_CRATE_1, logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_BK_ROOM_LOWER_CRATE_2, logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_BK_ROOM_LOWER_CRATE_3, logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_BK_ROOM_LOWER_CRATE_4, logic->CanBreakCrates()),
    }, 
    {
        //Exits
        Entrance(RR_WATER_TEMPLE_MQ_BOSS_KEY_ROOM_SWITCH, []{return logic->CanHitSwitch(ED_BOOMERANG);}),
    });

    areaTable[RR_WATER_TEMPLE_MQ_BOSS_KEY_ROOM_CHEST] = Region("Water Temple MQ Boss Key Room Chest", SCENE_WATER_TEMPLE, {}, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_MQ_BOSS_KEY_CHEST, true),
    }, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MQ_BOSS_KEY_ROOM_SWITCH, []{return logic->CanHitSwitch(ED_BOMB_THROW) || logic->CanUse(RG_HOVER_BOOTS);}),
        Entrance(RR_WATER_TEMPLE_MQ_BOSS_KEY_ROOM_PIT,    []{return true;}),
        Entrance(RR_WATER_TEMPLE_MQ_B1_GATE_SWITCH,       []{return logic->HasItem(RG_SILVER_SCALE) || (logic->CanUse(RG_IRON_BOOTS) && (logic->HasItem(RG_BRONZE_SCALE) || (logic->WaterTimer() >= 24 && logic->CanUse(RG_LONGSHOT))));}),
    });

    areaTable[RR_WATER_TEMPLE_MQ_B1_GATE_SWITCH] = Region("Water Temple MQ B1 Gate Switch", SCENE_WATER_TEMPLE, {
        //Events
        //If the water is low, the switch is underwater and needs irons to press, otherwise, the water is too low to climb up and you need irons to hookshot a target
        //If a glitch clips through the gate on low, have it logically press the switch and let entrance logic enter
        EventAccess(LOGIC_WATER_MQ_B1_SWITCH, []{return logic->CanUse(RG_IRON_BOOTS);}),
    }, {}, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MQ_MAIN,                []{return logic->Get(LOGIC_WATER_MQ_B1_SWITCH) && (logic->MQWaterLevel(WL_LOW) || (logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 16));}),
        Entrance(RR_WATER_TEMPLE_MQ_BOSS_KEY_ROOM_CHEST, []{return logic->CanUse(RG_IRON_BOOTS) && logic->HasItem(RG_BRONZE_SCALE) && (logic->MQWaterLevel(WL_LOW) || logic->WaterTimer() >= 24);})
    });

    areaTable[RR_WATER_TEMPLE_MQ_TRIANGLE_TORCH_ROOM] = Region("Water Temple MQ Triangle Torch Room", SCENE_WATER_TEMPLE, {}, 
    {
        //Locations
        LOCATION(RC_WATER_TEMPLE_MQ_TRIPLE_TORCH_ROOM_SUBMERGED_CRATE_1, logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 16 && logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_TRIPLE_TORCH_ROOM_SUBMERGED_CRATE_2, logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 16 && logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_TRIPLE_TORCH_ROOM_SUBMERGED_CRATE_3, logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 16 && logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_TRIPLE_TORCH_ROOM_SUBMERGED_CRATE_4, logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 16 && logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_TRIPLE_TORCH_ROOM_SUBMERGED_CRATE_5, logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 16 && logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_TRIPLE_TORCH_ROOM_SUBMERGED_CRATE_6, logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 16 && logic->CanBreakCrates()),
    }, 
    {
        //Exits
        Entrance(RR_WATER_TEMPLE_MQ_MAIN,                []{return logic->Get(LOGIC_WATER_MQ_B1_SWITCH) && ((logic->MQWaterLevel(WL_LOW) && logic->HasItem(RG_GOLDEN_SCALE)) || (logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 40 && (logic->HasItem(RG_BRONZE_SCALE) || logic->CanUse(RG_LONGSHOT))));}),
        Entrance(RR_WATER_TEMPLE_MQ_TRIANGLE_TORCH_CAGE, []{return logic->CanUse(RG_FIRE_ARROWS) && ((logic->IsAdult && logic->CanUse(RG_HOVER_BOOTS)) || (logic->CanUse(RG_LONGSHOT) && Here(RR_WATER_TEMPLE_MQ_TRIANGLE_TORCH_ROOM, []{return logic->ScarecrowsSong();})));})
    });

    areaTable[RR_WATER_TEMPLE_MQ_TRIANGLE_TORCH_CAGE] = Region("Water Temple MQ Triangle Torch Cage", SCENE_WATER_TEMPLE, {}, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_MQ_GS_TRIPLE_WALL_TORCH,           logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA, ED_BOOMERANG)),
        LOCATION(RC_WATER_TEMPLE_MQ_LOWEST_GS_POT_1,                logic->CanBreakPots()),
        LOCATION(RC_WATER_TEMPLE_MQ_LOWEST_GS_POT_2,                logic->CanBreakPots()),
        LOCATION(RC_WATER_TEMPLE_MQ_LOWEST_GS_POT_3,                logic->CanBreakPots()),
        LOCATION(RC_WATER_TEMPLE_MQ_LOWEST_GS_POT_4,                logic->CanBreakPots()),
        LOCATION(RC_WATER_TEMPLE_MQ_TRIPLE_TORCH_ROOM_GATE_CRATE_3, logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_TRIPLE_TORCH_ROOM_GATE_CRATE_1, logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_TRIPLE_TORCH_ROOM_GATE_CRATE_2, logic->CanBreakCrates()),
    }, {});

    areaTable[RR_WATER_TEMPLE_MQ_CRATES_WHIRLPOOLS_ROOM] = Region("Water Temple MQ Crates Whirlpools Room", SCENE_WATER_TEMPLE, {}, 
    {
        //Locations
        LOCATION(RC_WATER_TEMPLE_MQ_WHIRLPOOL_FRONT_CRATE_1,     logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_WHIRLPOOL_FRONT_CRATE_2,     logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_WHIRLPOOL_SUBMERGED_CRATE_1, logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 16 && logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_WHIRLPOOL_SUBMERGED_CRATE_2, logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 16 && logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_WHIRLPOOL_SUBMERGED_CRATE_3, logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 16 && logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_WHIRLPOOL_SUBMERGED_CRATE_4, logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 16 && logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_WHIRLPOOL_SUBMERGED_CRATE_5, logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 16 && logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_WHIRLPOOL_SUBMERGED_CRATE_6, logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 16 && logic->CanBreakCrates()),
    }, 
    {
        //Exits
        //we can backflip over the spikes, but land in water.
        Entrance(RR_WATER_TEMPLE_MQ_MAIN,                   []{return logic->Get(LOGIC_WATER_MQ_B1_SWITCH) && logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 24 && (logic->CanUse(RG_LONGSHOT) || logic->HasItem(RG_BRONZE_SCALE));}),
        //Child can use the crate to get the height to make it with hovers, but it's annoyingly tight so would be a trick
        Entrance(RR_WATER_TEMPLE_MQ_SINGLE_STALFOS_ROOM,    []{return logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 8 &&
                                                                                                                                //We're putting the requirement to get out of the water here as the scarecrow method in includes hook which satisfies it
                                                                                                                                ((logic->IsAdult && (logic->CanUse(RG_HOVER_BOOTS) || ctx->GetTrickOption(RT_WATER_NORTH_BASEMENT_LEDGE_JUMP)) && (logic->CanUse(RG_HOOKSHOT) || logic->HasItem(RG_BRONZE_SCALE))) ||
                                                                                                                                 (Here(RR_WATER_TEMPLE_MQ_CRATES_WHIRLPOOLS_ROOM, []{return logic->ScarecrowsSong();}) && logic->CanUse(RG_HOOKSHOT)));}),
        Entrance(RR_WATER_TEMPLE_MQ_4_TORCH_ROOM,           []{return logic->IsAdult && (logic->CanUse(RG_HOVER_BOOTS) || ctx->GetTrickOption(RT_WATER_NORTH_BASEMENT_LEDGE_JUMP) || (Here(RR_WATER_TEMPLE_MQ_CRATES_WHIRLPOOLS_ROOM, []{return logic->ScarecrowsSong();}) && logic->CanUse(RG_HOOKSHOT)));}),
        Entrance(RR_WATER_TEMPLE_MQ_CRATES_WHIRLPOOLS_CAGE, []{return ctx->GetTrickOption(RT_WATER_MQ_LOCKED_GS) && (logic->CanUse(RG_IRON_BOOTS) && logic->CanUse(RG_HOOKSHOT));}),
    });

    areaTable[RR_WATER_TEMPLE_MQ_SINGLE_STALFOS_ROOM] = Region("Water Temple MQ Single Stalfos Room", SCENE_WATER_TEMPLE, {}, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_MQ_FREESTANDING_KEY,       logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_B_POT_1,   logic->CanBreakPots()),
        LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_B_POT_2,   logic->CanBreakPots()),
        LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_B_CRATE_1, logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_B_CRATE_2, logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_B_CRATE_3, logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_B_CRATE_4, logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_B_CRATE_5, logic->CanBreakCrates()),

    }, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MQ_CRATES_WHIRLPOOLS_ROOM, []{return logic->HasItem(RG_SILVER_SCALE) || (logic->IsChild && logic->HasItem(RG_BRONZE_SCALE)) || (logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 8 && (logic->HasItem(RG_BRONZE_SCALE) || logic->CanUse(RG_HOOKSHOT)));})
    });

    areaTable[RR_WATER_TEMPLE_MQ_4_TORCH_ROOM] = Region("Water Temple MQ 4 Torch Room", SCENE_WATER_TEMPLE, {}, {}, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MQ_CRATES_WHIRLPOOLS_ROOM, []{return (logic->IsAdult && (logic->CanUse(RG_HOVER_BOOTS) || logic->CanJumpslash())) || (logic->HasItem(RG_BRONZE_SCALE) || (logic->CanUse(RG_IRON_BOOTS) && logic->WaterTimer() >= 8 && logic->CanUse(RG_HOOKSHOT) ));}),
        Entrance(RR_WATER_TEMPLE_MQ_DODONGO_ROOM,           []{return logic->CanHitSwitch() && logic->HasFireSource();})
    });

    areaTable[RR_WATER_TEMPLE_MQ_DODONGO_ROOM] = Region("Water Temple MQ Dodongo Room", SCENE_WATER_TEMPLE, {}, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_MQ_MINI_DODONGO_POT_1,         logic->CanBreakPots()),
        LOCATION(RC_WATER_TEMPLE_MQ_MINI_DODONGO_POT_2,         logic->CanBreakPots()),
        LOCATION(RC_WATER_TEMPLE_MQ_DODONGO_ROOM_UPPER_CRATE,   logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_DODONGO_ROOM_HALL_CRATE,    logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_DODONGO_ROOM_LOWER_CRATE_1, logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_DODONGO_ROOM_LOWER_CRATE_2, logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_DODONGO_ROOM_LOWER_CRATE_3, logic->CanBreakCrates()),
    }, {
        //Exits
        Entrance(RR_WATER_TEMPLE_MQ_4_TORCH_ROOM,           []{return (logic->CanUse(RG_HOOKSHOT) || logic->CanUse(RG_HOVER_BOOTS)) && Here(RR_WATER_TEMPLE_MQ_DODONGO_ROOM, []{return logic->CanKillEnemy(RE_DODONGO, ED_CLOSE, true, 5);});}),
        Entrance(RR_WATER_TEMPLE_MQ_CRATES_WHIRLPOOLS_CAGE, []{return (logic->CanUse(RG_HOOKSHOT) || logic->CanUse(RG_HOVER_BOOTS)) && Here(RR_WATER_TEMPLE_MQ_DODONGO_ROOM, []{return logic->CanKillEnemy(RE_DODONGO, ED_CLOSE, true, 5);});})
    });

    areaTable[RR_WATER_TEMPLE_MQ_CRATES_WHIRLPOOLS_CAGE] = Region("Water Temple MQ Basement Gated Areas", SCENE_WATER_TEMPLE, {}, {
        //Locations
        LOCATION(RC_WATER_TEMPLE_MQ_GS_FREESTANDING_KEY_AREA,       logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA) && logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_WHIRLPOOL_BEHIND_GATE_CRATE_1,  logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_WHIRLPOOL_BEHIND_GATE_CRATE_2,  logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_WHIRLPOOL_BEHIND_GATE_CRATE_3,  logic->CanBreakCrates()),
        LOCATION(RC_WATER_TEMPLE_MQ_WHIRLPOOL_BEHIND_GATE_CRATE_4,  logic->CanBreakCrates()),
    }, {
        Entrance(RR_WATER_TEMPLE_MQ_DODONGO_ROOM, []{return true;})
    });

#pragma endregion

    // Boss Room
    areaTable[RR_WATER_TEMPLE_BOSS_ENTRYWAY] = Region("Water Temple Boss Entryway", SCENE_WATER_TEMPLE, {}, {}, {
        // Exits
        Entrance(RR_WATER_TEMPLE_RISING_TARGET_LEDGE, []{return ctx->GetDungeon(WATER_TEMPLE)->IsVanilla() && false;}),
        Entrance(RR_WATER_TEMPLE_MQ_BOSS_DOOR,  []{return ctx->GetDungeon(WATER_TEMPLE)->IsMQ() && false;}),
        Entrance(RR_WATER_TEMPLE_BOSS_ROOM,     []{return logic->HasItem(RG_WATER_TEMPLE_BOSS_KEY);}),
    });

    areaTable[RR_WATER_TEMPLE_BOSS_ROOM] = Region("Water Temple Boss Room", SCENE_WATER_TEMPLE_BOSS, {
        // Events
        EventAccess(LOGIC_WATER_TEMPLE_CLEAR, []{return logic->CanKillEnemy(RE_MORPHA);}),
    }, {
        // Locations
        LOCATION(RC_WATER_TEMPLE_MORPHA_HEART, logic->Get(LOGIC_WATER_TEMPLE_CLEAR)),
        LOCATION(RC_MORPHA,                    logic->Get(LOGIC_WATER_TEMPLE_CLEAR)),
    }, {
        // Exits
        Entrance(RR_WATER_TEMPLE_BOSS_ENTRYWAY, []{return false;}),
        Entrance(RR_LAKE_HYLIA,                 []{return logic->Get(LOGIC_WATER_TEMPLE_CLEAR);}, false),
    });

    // clang-format on
}
