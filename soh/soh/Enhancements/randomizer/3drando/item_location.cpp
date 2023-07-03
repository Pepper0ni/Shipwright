#include "item_location.hpp"

#include "dungeon.hpp"
#include "settings.hpp"
#include "spoiler_log.hpp"
#include "shops.hpp"
#include "keys.hpp"
#include <spdlog/spdlog.h>
#include "../randomizerTypes.h"

//Location definitions
static std::array<ItemLocation, KEY_ENUM_MAX> locationTable;
static std::unordered_map<RandomizerCheck, Key> locationLookupTable;

void LocationTable_Init() {
    locationTable[NONE]                                  = ItemLocation::Base       (RC_UNKNOWN_CHECK,                              0xFF,       "Invalid Location",                     NONE,                                  NONE,                      {},                                                   SpoilerCollectionCheck::None());
    //Kokiri Forest                                                                                                                 scene flag  name                                    hint key (hint_list.cpp)               vanilla item               categories                                            collection check (if needed)                     collection check group
    locationTable[KF_KOKIRI_SWORD_CHEST]                 = ItemLocation::Chest      (RC_KF_KOKIRI_SWORD_CHEST,                      0x55, 0x00, "KF Kokiri Sword Chest",                KF_KOKIRI_SWORD_CHEST,                 KOKIRI_SWORD,              {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_KOKIRI_FOREST);
    locationTable[KF_MIDOS_TOP_LEFT_CHEST]               = ItemLocation::Chest      (RC_KF_MIDOS_TOP_LEFT_CHEST,                    0x28, 0x00, "KF Mido Top Left Chest",               KF_MIDOS_TOP_LEFT_CHEST,               BLUE_RUPEE,                {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_KOKIRI_FOREST);
    locationTable[KF_MIDOS_TOP_RIGHT_CHEST]              = ItemLocation::Chest      (RC_KF_MIDOS_TOP_RIGHT_CHEST,                   0x28, 0x01, "KF Mido Top Right Chest",              KF_MIDOS_TOP_RIGHT_CHEST,              BLUE_RUPEE,                {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_KOKIRI_FOREST);
    locationTable[KF_MIDOS_BOTTOM_LEFT_CHEST]            = ItemLocation::Chest      (RC_KF_MIDOS_BOTTOM_LEFT_CHEST,                 0x28, 0x02, "KF Mido Bottom Left Chest",            KF_MIDOS_BOTTOM_LEFT_CHEST,            GREG_RUPEE,                {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_KOKIRI_FOREST);
    locationTable[KF_MIDOS_BOTTOM_RIGHT_CHEST]           = ItemLocation::Chest      (RC_KF_MIDOS_BOTTOM_RIGHT_CHEST,                0x28, 0x03, "KF Mido Bottom Right Chest",           KF_MIDOS_BOTTOM_RIGHT_CHEST,           RECOVERY_HEART,            {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_KOKIRI_FOREST);
    locationTable[KF_STORMS_GROTTO_CHEST]                = ItemLocation::Chest      (RC_KF_STORMS_GROTTO_CHEST,                     0x3E, 0x0C, "KF Storms Grotto Chest",               KF_STORMS_GROTTO_CHEST,                RED_RUPEE,                 {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_KOKIRI_FOREST);

    //Lost Woods
    locationTable[LW_NEAR_SHORTCUTS_GROTTO_CHEST]        = ItemLocation::Chest      (RC_LW_NEAR_SHORTCUTS_GROTTO_CHEST,             0x3E, 0x14, "LW Near Shortcuts Grotto Chest",       LW_NEAR_SHORTCUTS_GROTTO_CHEST,        BLUE_RUPEE,                {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_LOST_WOODS);
    locationTable[LW_SKULL_KID]                          = ItemLocation::Base       (RC_LW_SKULL_KID,                               0x5B,       "LW Skull Kid",                         LW_SKULL_KID,                          PIECE_OF_HEART,            {},                                                   SpoilerCollectionCheck::ItemGetInf(30),          SpoilerCollectionCheckGroup::GROUP_LOST_WOODS);
    locationTable[LW_TRADE_COJIRO]                       = ItemLocation::Base       (RC_LW_TRADE_COJIRO,                            0x5B,       "LW Trade Cojiro",                      LW_TRADE_COJIRO,                       ODD_MUSHROOM,              {Category::cAdultTrade},                              SpoilerCollectionCheck::RandomizerInf(),         SpoilerCollectionCheckGroup::GROUP_LOST_WOODS);
    locationTable[LW_TRADE_ODD_POTION]                   = ItemLocation::Base       (RC_LW_TRADE_ODD_POTION,                        0x5B,       "LW Trade Odd Potion",                  LW_TRADE_ODD_POTION,                   ODD_POTION,                {Category::cAdultTrade},                              SpoilerCollectionCheck::ItemGetInf(57),          SpoilerCollectionCheckGroup::GROUP_LOST_WOODS);
    locationTable[LW_OCARINA_MEMORY_GAME]                = ItemLocation::Base       (RC_LW_OCARINA_MEMORY_GAME,                     0x5B,       "LW Ocarina Memory Game",               LW_OCARINA_MEMORY_GAME,                PIECE_OF_HEART,            {},                                                   SpoilerCollectionCheck::ItemGetInf(31),          SpoilerCollectionCheckGroup::GROUP_LOST_WOODS);
    locationTable[LW_TARGET_IN_WOODS]                    = ItemLocation::Base       (RC_LW_TARGET_IN_WOODS,                         0x5B,       "LW Target in Woods",                   LW_TARGET_IN_WOODS,                    PROGRESSIVE_SLINGSHOT,     {},                                                   SpoilerCollectionCheck::ItemGetInf(21),          SpoilerCollectionCheckGroup::GROUP_LOST_WOODS);
    locationTable[LW_DEKU_SCRUB_NEAR_DEKU_THEATER_RIGHT] = ItemLocation::Base       (RC_LW_DEKU_SCRUB_NEAR_DEKU_THEATER_RIGHT,      0x5B,       "LW Deku Scrub Near Deku Theater Right",LW_DEKU_SCRUB_NEAR_DEKU_THEATER_RIGHT, BUY_DEKU_NUT_5,            {Category::cDekuScrub},                               SpoilerCollectionCheck::Scrub(),                 SpoilerCollectionCheckGroup::GROUP_LOST_WOODS);
    locationTable[LW_DEKU_SCRUB_NEAR_DEKU_THEATER_LEFT]  = ItemLocation::Base       (RC_LW_DEKU_SCRUB_NEAR_DEKU_THEATER_LEFT,       0x5B,       "LW Deku Scrub Near Deku Theater Left", LW_DEKU_SCRUB_NEAR_DEKU_THEATER_LEFT,  BUY_DEKU_STICK_1,          {Category::cDekuScrub},                               SpoilerCollectionCheck::Scrub(),                 SpoilerCollectionCheckGroup::GROUP_LOST_WOODS);
    locationTable[LW_DEKU_SCRUB_NEAR_BRIDGE]             = ItemLocation::Base       (RC_LW_DEKU_SCRUB_NEAR_BRIDGE,                  0x5B,       "LW Deku Scrub Near Bridge",            LW_DEKU_SCRUB_NEAR_BRIDGE,             PROGRESSIVE_STICK_UPGRADE, {Category::cDekuScrub, Category::cDekuScrubUpgrades}, SpoilerCollectionCheck::Scrub(),                 SpoilerCollectionCheckGroup::GROUP_LOST_WOODS);
    locationTable[LW_DEKU_SCRUB_GROTTO_REAR]             = ItemLocation::GrottoScrub(RC_LW_DEKU_SCRUB_GROTTO_REAR,                  0xF5,       "LW Deku Scrub Grotto Rear",            LW_DEKU_SCRUB_GROTTO_REAR,             BUY_DEKU_SEEDS_30,         {Category::cDekuScrub},                               SpoilerCollectionCheck::Scrub(),                 SpoilerCollectionCheckGroup::GROUP_LOST_WOODS);
    locationTable[LW_DEKU_SCRUB_GROTTO_FRONT]            = ItemLocation::GrottoScrub(RC_LW_DEKU_SCRUB_GROTTO_FRONT,                 0xF5,       "LW Deku Scrub Grotto Front",           LW_DEKU_SCRUB_GROTTO_FRONT,            PROGRESSIVE_NUT_UPGRADE,   {Category::cDekuScrub, Category::cDekuScrubUpgrades}, SpoilerCollectionCheck::Scrub(),                 SpoilerCollectionCheckGroup::GROUP_LOST_WOODS);
    locationTable[DEKU_THEATER_SKULL_MASK]               = ItemLocation::Base       (RC_DEKU_THEATER_SKULL_MASK,                    0x3E,       "Deku Theater Skull Mask",              DEKU_THEATER_SKULL_MASK,               PROGRESSIVE_STICK_UPGRADE, {},                                                   SpoilerCollectionCheck::Chest(0x3E, 0x1F),       SpoilerCollectionCheckGroup::GROUP_LOST_WOODS);
    locationTable[DEKU_THEATER_MASK_OF_TRUTH]            = ItemLocation::Base       (RC_DEKU_THEATER_MASK_OF_TRUTH,                 0x3E,       "Deku Theater Mask of Truth",           DEKU_THEATER_MASK_OF_TRUTH,            PROGRESSIVE_NUT_UPGRADE,   {},                                                   SpoilerCollectionCheck::Chest(0x3E, 0x1E),       SpoilerCollectionCheckGroup::GROUP_LOST_WOODS);

    //Sacred Forest Meadow
    locationTable[SFM_WOLFOS_GROTTO_CHEST]               = ItemLocation::Chest      (RC_SFM_WOLFOS_GROTTO_CHEST,                    0x3E, 0x11, "SFM Wolfos Grotto Chest",              SFM_WOLFOS_GROTTO_CHEST,               PURPLE_RUPEE,              {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_LOST_WOODS);
    locationTable[SFM_DEKU_SCRUB_GROTTO_REAR]            = ItemLocation::GrottoScrub(RC_SFM_DEKU_SCRUB_GROTTO_REAR,                 0xEE,       "SFM Deku Scrub Grotto Rear",           SFM_DEKU_SCRUB_GROTTO_REAR,            BUY_RED_POTION_30,         {Category::cDekuScrub},                               SpoilerCollectionCheck::Scrub(),                 SpoilerCollectionCheckGroup::GROUP_LOST_WOODS);
    locationTable[SFM_DEKU_SCRUB_GROTTO_FRONT]           = ItemLocation::GrottoScrub(RC_SFM_DEKU_SCRUB_GROTTO_FRONT,                0xEE,       "SFM Deku Scrub Grotto Front",          SFM_DEKU_SCRUB_GROTTO_FRONT,           BUY_GREEN_POTION,          {Category::cDekuScrub},                               SpoilerCollectionCheck::Scrub(),                 SpoilerCollectionCheckGroup::GROUP_LOST_WOODS);

    //Hyrule Field
    locationTable[HF_SOUTHEAST_GROTTO_CHEST]             = ItemLocation::Chest      (RC_HF_SOUTHEAST_GROTTO_CHEST,                  0x3E, 0x02, "HF Southeast Grotto Chest",            HF_SOUTHEAST_GROTTO_CHEST,             RED_RUPEE,                 {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_HYRULE_FIELD);
    locationTable[HF_OPEN_GROTTO_CHEST]                  = ItemLocation::Chest      (RC_HF_OPEN_GROTTO_CHEST,                       0x3E, 0x03, "HF Open Grotto Chest",                 HF_OPEN_GROTTO_CHEST,                  BLUE_RUPEE,                {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_HYRULE_FIELD);
    locationTable[HF_NEAR_MARKET_GROTTO_CHEST]           = ItemLocation::Chest      (RC_HF_NEAR_MARKET_GROTTO_CHEST,                0x3E, 0x00, "HF Near Market Grotto Chest",          HF_NEAR_MARKET_GROTTO_CHEST,           BLUE_RUPEE,                {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_HYRULE_FIELD);
    locationTable[HF_OCARINA_OF_TIME_ITEM]               = ItemLocation::Base       (RC_HF_OCARINA_OF_TIME_ITEM,                    0x51,       "HF Ocarina of Time Item",              HF_OCARINA_OF_TIME_ITEM,               PROGRESSIVE_OCARINA,       {},                                                   SpoilerCollectionCheck::EventChkInf(0x43),       SpoilerCollectionCheckGroup::GROUP_HYRULE_FIELD);
    locationTable[HF_TEKTITE_GROTTO_FREESTANDING_POH]    = ItemLocation::Collectable(RC_HF_TEKTITE_GROTTO_FREESTANDING_POH,         0x3E, 0x01, "HF Tektite Grotto Freestanding PoH",   HF_TEKTITE_GROTTO_FREESTANDING_POH,    PIECE_OF_HEART,            {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_HYRULE_FIELD);
    locationTable[HF_DEKU_SCRUB_GROTTO]                  = ItemLocation::GrottoScrub(RC_HF_DEKU_SCRUB_GROTTO,                       0xE6,       "HF Deku Scrub Grotto",                 HF_DEKU_SCRUB_GROTTO,                  PIECE_OF_HEART,            {Category::cDekuScrub, Category::cDekuScrubUpgrades}, SpoilerCollectionCheck::Scrub(),                 SpoilerCollectionCheckGroup::GROUP_HYRULE_FIELD);

    //Lake Hylia
    locationTable[LH_CHILD_FISHING]                      = ItemLocation::Base       (RC_LH_CHILD_FISHING,                           0x49,       "LH Child Fishing",                     LH_CHILD_FISHING,                      PIECE_OF_HEART,            {},                                                   SpoilerCollectionCheck::RandomizerInf(),         SpoilerCollectionCheckGroup::GROUP_LAKE_HYLIA);
    locationTable[LH_ADULT_FISHING]                      = ItemLocation::Base       (RC_LH_ADULT_FISHING,                           0x49,       "LH Adult Fishing",                     LH_ADULT_FISHING,                      PROGRESSIVE_SCALE,         {},                                                   SpoilerCollectionCheck::RandomizerInf(),         SpoilerCollectionCheckGroup::GROUP_LAKE_HYLIA);
    locationTable[LH_LAB_DIVE]                           = ItemLocation::Base       (RC_LH_LAB_DIVE,                                0x38,       "LH Lab Dive",                          LH_LAB_DIVE,                           PIECE_OF_HEART,            {},                                                   SpoilerCollectionCheck::ItemGetInf(24),          SpoilerCollectionCheckGroup::GROUP_LAKE_HYLIA);
    locationTable[LH_TRADE_FROG]                         = ItemLocation::Base       (RC_LH_TRADE_FROG,                              0x38,       "LH Lab Trade Eyeball Frog",            LH_TRADE_FROG,                         EYEDROPS,                  {Category::cAdultTrade},                              SpoilerCollectionCheck::RandomizerInf(),         SpoilerCollectionCheckGroup::GROUP_LAKE_HYLIA);
    locationTable[LH_UNDERWATER_ITEM]                    = ItemLocation::Base       (RC_LH_UNDERWATER_ITEM,                         0x57,       "LH Underwater Item",                   LH_UNDERWATER_ITEM,                    RUTOS_LETTER,              {},                                                   SpoilerCollectionCheck::EventChkInf(0x31),       SpoilerCollectionCheckGroup::GROUP_LAKE_HYLIA);
    locationTable[LH_SUN]                                = ItemLocation::Base       (RC_LH_SUN,                                     0x57,       "LH Sun",                               LH_SUN,                                FIRE_ARROWS,               {},                                                   SpoilerCollectionCheck::Chest(0x57, 0x1F),       SpoilerCollectionCheckGroup::GROUP_LAKE_HYLIA);
    locationTable[LH_FREESTANDING_POH]                   = ItemLocation::Collectable(RC_LH_FREESTANDING_POH,                        0x57, 0x1E, "LH Freestanding PoH",                  LH_FREESTANDING_POH,                   PIECE_OF_HEART,            {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_LAKE_HYLIA);
    locationTable[LH_DEKU_SCRUB_GROTTO_LEFT]             = ItemLocation::GrottoScrub(RC_LH_DEKU_SCRUB_GROTTO_LEFT,                  0xEF,       "LH Deku Scrub Grotto Left",            LH_DEKU_SCRUB_GROTTO_LEFT,             BUY_DEKU_NUT_5,            {Category::cDekuScrub},                               SpoilerCollectionCheck::Scrub(),                 SpoilerCollectionCheckGroup::GROUP_LAKE_HYLIA);
    locationTable[LH_DEKU_SCRUB_GROTTO_RIGHT]            = ItemLocation::GrottoScrub(RC_LH_DEKU_SCRUB_GROTTO_RIGHT,                 0xEF,       "LH Deku Scrub Grotto Right",           LH_DEKU_SCRUB_GROTTO_RIGHT,            BUY_BOMBS_535,             {Category::cDekuScrub},                               SpoilerCollectionCheck::Scrub(),                 SpoilerCollectionCheckGroup::GROUP_LAKE_HYLIA);
    locationTable[LH_DEKU_SCRUB_GROTTO_CENTER]           = ItemLocation::GrottoScrub(RC_LH_DEKU_SCRUB_GROTTO_CENTER,                0xEF,       "LH Deku Scrub Grotto Center",          LH_DEKU_SCRUB_GROTTO_CENTER,           BUY_DEKU_SEEDS_30,         {Category::cDekuScrub},                               SpoilerCollectionCheck::Scrub(),                 SpoilerCollectionCheckGroup::GROUP_LAKE_HYLIA);

    //Gerudo Valley
    locationTable[GV_CHEST]                              = ItemLocation::Chest      (RC_GV_CHEST,                                   0x5A, 0x00, "GV Chest",                             GV_CHEST,                              PURPLE_RUPEE,              {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_GERUDO_VALLEY);
    locationTable[GV_TRADE_SAW]                          = ItemLocation::Base       (RC_GV_TRADE_SAW,                               0x5A,       "GV Trade Saw",                         GV_TRADE_SAW,                          BROKEN_SWORD,              {Category::cAdultTrade},                              SpoilerCollectionCheck::RandomizerInf(),         SpoilerCollectionCheckGroup::GROUP_GERUDO_VALLEY);
    locationTable[GV_WATERFALL_FREESTANDING_POH]         = ItemLocation::Collectable(RC_GV_WATERFALL_FREESTANDING_POH,              0x5A, 0x01, "GV Waterfall Freestanding PoH",        GV_WATERFALL_FREESTANDING_POH,         PIECE_OF_HEART,            {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_GERUDO_VALLEY);
    locationTable[GV_CRATE_FREESTANDING_POH]             = ItemLocation::Collectable(RC_GV_CRATE_FREESTANDING_POH,                  0x5A, 0x02, "GV Crate Freestanding PoH",            GV_CRATE_FREESTANDING_POH,             PIECE_OF_HEART,            {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_GERUDO_VALLEY);
    locationTable[GV_DEKU_SCRUB_GROTTO_REAR]             = ItemLocation::GrottoScrub(RC_GV_DEKU_SCRUB_GROTTO_REAR,                  0xF0,       "GV Deku Scrub Grotto Rear",            GV_DEKU_SCRUB_GROTTO_REAR,             BUY_RED_POTION_30,         {Category::cDekuScrub},                               SpoilerCollectionCheck::Scrub(),                 SpoilerCollectionCheckGroup::GROUP_GERUDO_VALLEY);
    locationTable[GV_DEKU_SCRUB_GROTTO_FRONT]            = ItemLocation::GrottoScrub(RC_GV_DEKU_SCRUB_GROTTO_FRONT,                 0xF0,       "GV Deku Scrub Grotto Front",           GV_DEKU_SCRUB_GROTTO_FRONT,            BUY_GREEN_POTION,          {Category::cDekuScrub},                               SpoilerCollectionCheck::Scrub(),                 SpoilerCollectionCheckGroup::GROUP_GERUDO_VALLEY);

    //Gerudo Fortress
    locationTable[GF_CHEST]                              = ItemLocation::Chest      (RC_GF_CHEST,                                   0x5D, 0x00, "GF Chest",                             GF_CHEST,                              PIECE_OF_HEART,            {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_GERUDO_VALLEY);
    locationTable[GF_HBA_1000_POINTS]                    = ItemLocation::Base       (RC_GF_HBA_1000_POINTS,                         0x5D,       "GF HBA 1000 Points",                   GF_HBA_1000_POINTS,                    PIECE_OF_HEART,            {},                                                   SpoilerCollectionCheck::InfTable(0x19, 0x08),    SpoilerCollectionCheckGroup::GROUP_GERUDO_VALLEY);
    locationTable[GF_HBA_1500_POINTS]                    = ItemLocation::Base       (RC_GF_HBA_1500_POINTS,                         0x5D,       "GF HBA 1500 Points",                   GF_HBA_1500_POINTS,                    PROGRESSIVE_BOW,           {},                                                   SpoilerCollectionCheck::ItemGetInf(7),           SpoilerCollectionCheckGroup::GROUP_GERUDO_VALLEY);
    locationTable[GF_GERUDO_MEMBERSHIP_CARD]             = ItemLocation::Base       (RC_GF_GERUDO_MEMBERSHIP_CARD,                  0x0C,       "GF Gerudo Membership Card",            GF_GERUDO_MEMBERSHIP_CARD,             GERUDO_MEMBERSHIP_CARD,    {},                                                   SpoilerCollectionCheck::GerudoToken(),           SpoilerCollectionCheckGroup::GROUP_GERUDO_VALLEY);
    locationTable[GF_NORTH_F1_CARPENTER]                 = ItemLocation::Collectable(RC_GF_NORTH_F1_CARPENTER,                      0x0C, 0x0C, "GF North F1 Carpenter",                GF_NORTH_F1_CARPENTER,                 GERUDO_FORTRESS_SMALL_KEY, {Category::cVanillaGFSmallKey},                                                                        SpoilerCollectionCheckGroup::GROUP_GERUDO_VALLEY);
    locationTable[GF_NORTH_F2_CARPENTER]                 = ItemLocation::Collectable(RC_GF_NORTH_F2_CARPENTER,                      0x0C, 0x0A, "GF North F2 Carpenter",                GF_NORTH_F2_CARPENTER,                 GERUDO_FORTRESS_SMALL_KEY, {Category::cVanillaGFSmallKey},                                                                        SpoilerCollectionCheckGroup::GROUP_GERUDO_VALLEY);
    locationTable[GF_SOUTH_F1_CARPENTER]                 = ItemLocation::Collectable(RC_GF_SOUTH_F1_CARPENTER,                      0x0C, 0x0E, "GF South F1 Carpenter",                GF_SOUTH_F1_CARPENTER,                 GERUDO_FORTRESS_SMALL_KEY, {Category::cVanillaGFSmallKey},                                                                        SpoilerCollectionCheckGroup::GROUP_GERUDO_VALLEY);
    locationTable[GF_SOUTH_F2_CARPENTER]                 = ItemLocation::Collectable(RC_GF_SOUTH_F2_CARPENTER,                      0x0C, 0x0F, "GF South F2 Carpenter",                GF_SOUTH_F2_CARPENTER,                 GERUDO_FORTRESS_SMALL_KEY, {Category::cVanillaGFSmallKey},                                                                        SpoilerCollectionCheckGroup::GROUP_GERUDO_VALLEY);

    //Haunted Wasteland
    locationTable[WASTELAND_CHEST]                       = ItemLocation::Chest      (RC_WASTELAND_CHEST,                            0x5E, 0x00, "Wasteland Chest",                      WASTELAND_CHEST,                       PURPLE_RUPEE,              {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_GERUDO_VALLEY);
    locationTable[WASTELAND_BOMBCHU_SALESMAN]            = ItemLocation::Base       (RC_WASTELAND_BOMBCHU_SALESMAN,                 0x5E,       "Wasteland Carpet Salesman",            WASTELAND_BOMBCHU_SALESMAN,            BOMBCHU_10,                {Category::cMerchant},                                SpoilerCollectionCheck::Merchant(),              SpoilerCollectionCheckGroup::GROUP_GERUDO_VALLEY);

    //Desert Colossus
    locationTable[COLOSSUS_FREESTANDING_POH]             = ItemLocation::Collectable(RC_COLOSSUS_FREESTANDING_POH,                  0x5C, 0x0D, "Colossus Freestanding PoH",            COLOSSUS_FREESTANDING_POH,             PIECE_OF_HEART,            {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_GERUDO_VALLEY);
    locationTable[COLOSSUS_DEKU_SCRUB_GROTTO_REAR]       = ItemLocation::GrottoScrub(RC_COLOSSUS_DEKU_SCRUB_GROTTO_REAR,            0xFD,       "Colossus Deku Scrub Grotto Rear",      COLOSSUS_DEKU_SCRUB_GROTTO_REAR,       BUY_RED_POTION_30,         {Category::cDekuScrub},                               SpoilerCollectionCheck::Scrub(),                 SpoilerCollectionCheckGroup::GROUP_GERUDO_VALLEY);
    locationTable[COLOSSUS_DEKU_SCRUB_GROTTO_FRONT]      = ItemLocation::GrottoScrub(RC_COLOSSUS_DEKU_SCRUB_GROTTO_FRONT,           0xFD,       "Colossus Deku Scrub Grotto Front",     COLOSSUS_DEKU_SCRUB_GROTTO_FRONT,      BUY_GREEN_POTION,          {Category::cDekuScrub},                               SpoilerCollectionCheck::Scrub(),                 SpoilerCollectionCheckGroup::GROUP_GERUDO_VALLEY);

    //Market
    locationTable[MARKET_TREASURE_CHEST_GAME_REWARD]     = ItemLocation::Chest      (RC_MARKET_TREASURE_CHEST_GAME_REWARD,          0x10,       "MK Treasure Chest Game Reward",        MARKET_TREASURE_CHEST_GAME_REWARD,     TREASURE_GAME_HEART,       {},                                                   SpoilerCollectionCheck::ItemGetInf(19),          SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);
    locationTable[MARKET_BOMBCHU_BOWLING_FIRST_PRIZE]    = ItemLocation::Base       (RC_MARKET_BOMBCHU_BOWLING_FIRST_PRIZE,         0x4B,       "MK Bombchu Bowling First Prize",       MARKET_BOMBCHU_BOWLING_FIRST_PRIZE,    PROGRESSIVE_BOMB_BAG,      {},                                                   SpoilerCollectionCheck::ItemGetInf(25),          SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);
    locationTable[MARKET_BOMBCHU_BOWLING_SECOND_PRIZE]   = ItemLocation::Base       (RC_MARKET_BOMBCHU_BOWLING_SECOND_PRIZE,        0x4B,       "MK Bombchu Bowling Second Prize",      MARKET_BOMBCHU_BOWLING_SECOND_PRIZE,   PIECE_OF_HEART,            {},                                                   SpoilerCollectionCheck::ItemGetInf(26),          SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);
    locationTable[MARKET_BOMBCHU_BOWLING_BOMBCHUS]       = ItemLocation::Base       (RC_MARKET_BOMBCHU_BOWLING_BOMBCHUS,            0x4B,       "MK Bombchu Bowling Bombchus",          NONE,                                  BOMBCHU_DROP,              {},                                                   SpoilerCollectionCheck::None(),                  SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);
    locationTable[MARKET_LOST_DOG]                       = ItemLocation::Base       (RC_MARKET_LOST_DOG,                            0x35,       "MK Lost Dog",                          MARKET_LOST_DOG,                       PIECE_OF_HEART,            {},                                                   SpoilerCollectionCheck::InfTable(0x19, 0x09),    SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);
    locationTable[MARKET_SHOOTING_GALLERY_REWARD]        = ItemLocation::Base       (RC_MARKET_SHOOTING_GALLERY_REWARD,             0x42,       "MK Shooting Gallery",                  MARKET_SHOOTING_GALLERY_REWARD,        PROGRESSIVE_SLINGSHOT,     {},                                                   SpoilerCollectionCheck::ItemGetInf(5),           SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);
    locationTable[MARKET_10_BIG_POES]                    = ItemLocation::Base       (RC_MARKET_10_BIG_POES,                         0x4D,       "MK 10 Big Poes",                       MARKET_10_BIG_POES,                    EMPTY_BOTTLE,              {},                                                   SpoilerCollectionCheck::RandomizerInf(),         SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);
    locationTable[MARKET_TREASURE_CHEST_GAME_ITEM_1]     = ItemLocation::Chest      (RC_MARKET_TREASURE_CHEST_GAME_ITEM_1,          0x10, 0x01, "MK Chest Game First Room Chest",       MARKET_TREASURE_CHEST_GAME_ITEM_1,     TREASURE_GAME_SMALL_KEY,   {Category::cChestMinigame},                                                                            SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);
    locationTable[MARKET_TREASURE_CHEST_GAME_ITEM_2]     = ItemLocation::Chest      (RC_MARKET_TREASURE_CHEST_GAME_ITEM_2,          0x10, 0x03, "MK Chest Game Second Room Chest",      MARKET_TREASURE_CHEST_GAME_ITEM_2,     TREASURE_GAME_SMALL_KEY,   {Category::cChestMinigame},                                                                            SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);
    locationTable[MARKET_TREASURE_CHEST_GAME_ITEM_3]     = ItemLocation::Chest      (RC_MARKET_TREASURE_CHEST_GAME_ITEM_3,          0x10, 0x05, "MK Chest Game Third Room Chest",       MARKET_TREASURE_CHEST_GAME_ITEM_3,     TREASURE_GAME_SMALL_KEY,   {Category::cChestMinigame},                                                                            SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);
    locationTable[MARKET_TREASURE_CHEST_GAME_ITEM_4]     = ItemLocation::Chest      (RC_MARKET_TREASURE_CHEST_GAME_ITEM_4,          0x10, 0x07, "MK Chest Game Fourth Room Chest",      MARKET_TREASURE_CHEST_GAME_ITEM_4,     TREASURE_GAME_SMALL_KEY,   {Category::cChestMinigame},                                                                            SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);
    locationTable[MARKET_TREASURE_CHEST_GAME_ITEM_5]     = ItemLocation::Chest      (RC_MARKET_TREASURE_CHEST_GAME_ITEM_5,          0x10, 0x09, "MK Chest Game Fifth Room Chest",       MARKET_TREASURE_CHEST_GAME_ITEM_5,     TREASURE_GAME_SMALL_KEY,   {Category::cChestMinigame},                                                                            SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);

    //Hyrule Castle
    locationTable[HC_MALON_EGG]                          = ItemLocation::Base       (RC_HC_MALON_EGG,                               0x5F,       "HC Malon Egg",                         HC_MALON_EGG,                          WEIRD_EGG,                 {},                                                   SpoilerCollectionCheck::EventChkInf(0x12),       SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);
    locationTable[HC_ZELDAS_LETTER]                      = ItemLocation::Base       (RC_HC_ZELDAS_LETTER,                           0x4A,       "HC Zeldas Letter",                     HC_ZELDAS_LETTER,                      ZELDAS_LETTER,             {},                                                   SpoilerCollectionCheck::EventChkInf(0x40),       SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);

    //Kakariko
    locationTable[KAK_REDEAD_GROTTO_CHEST]               = ItemLocation::Chest      (RC_KAK_REDEAD_GROTTO_CHEST,                    0x3E, 0x0A, "Kak Redead Grotto Chest",              KAK_REDEAD_GROTTO_CHEST,               HUGE_RUPEE,                {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[KAK_OPEN_GROTTO_CHEST]                 = ItemLocation::Chest      (RC_KAK_OPEN_GROTTO_CHEST,                      0x3E, 0x08, "Kak Open Grotto Chest",                KAK_OPEN_GROTTO_CHEST,                 RED_RUPEE,                 {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[KAK_10_GOLD_SKULLTULA_REWARD]          = ItemLocation::Base       (RC_KAK_10_GOLD_SKULLTULA_REWARD,               0x50,       "Kak 10 Gold Skulltula Reward",         KAK_10_GOLD_SKULLTULA_REWARD,          PROGRESSIVE_WALLET,        {},                                                   SpoilerCollectionCheck::EventChkInf(0xDA),       SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[KAK_20_GOLD_SKULLTULA_REWARD]          = ItemLocation::Base       (RC_KAK_20_GOLD_SKULLTULA_REWARD,               0x50,       "Kak 20 Gold Skulltula Reward",         KAK_20_GOLD_SKULLTULA_REWARD,          STONE_OF_AGONY,            {},                                                   SpoilerCollectionCheck::EventChkInf(0xDB),       SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[KAK_30_GOLD_SKULLTULA_REWARD]          = ItemLocation::Base       (RC_KAK_30_GOLD_SKULLTULA_REWARD,               0x50,       "Kak 30 Gold Skulltula Reward",         KAK_30_GOLD_SKULLTULA_REWARD,          PROGRESSIVE_WALLET,        {},                                                   SpoilerCollectionCheck::EventChkInf(0xDC),       SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[KAK_40_GOLD_SKULLTULA_REWARD]          = ItemLocation::Base       (RC_KAK_40_GOLD_SKULLTULA_REWARD,               0x50,       "Kak 40 Gold Skulltula Reward",         KAK_40_GOLD_SKULLTULA_REWARD,          BOMBCHU_10,                {},                                                   SpoilerCollectionCheck::EventChkInf(0xDD),       SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[KAK_50_GOLD_SKULLTULA_REWARD]          = ItemLocation::Base       (RC_KAK_50_GOLD_SKULLTULA_REWARD,               0x50,       "Kak 50 Gold Skulltula Reward",         KAK_50_GOLD_SKULLTULA_REWARD,          PIECE_OF_HEART,            {},                                                   SpoilerCollectionCheck::EventChkInf(0xDE),       SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[KAK_100_GOLD_SKULLTULA_REWARD]         = ItemLocation::Base       (RC_KAK_100_GOLD_SKULLTULA_REWARD,              0x50,       "Kak 100 Gold Skulltula Reward",        KAK_100_GOLD_SKULLTULA_REWARD,         HUGE_RUPEE,                {},                                                   SpoilerCollectionCheck::EventChkInf(0xDF),       SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[KAK_MAN_ON_ROOF]                       = ItemLocation::Base       (RC_KAK_MAN_ON_ROOF,                            0x52,       "Kak Man on Roof",                      KAK_MAN_ON_ROOF,                       PIECE_OF_HEART,            {},                                                   SpoilerCollectionCheck::ItemGetInf(29),          SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[KAK_SHOOTING_GALLERY_REWARD]           = ItemLocation::Base       (RC_KAK_SHOOTING_GALLERY_REWARD,                0x42,       "Kak Shooting Gallery Reward",          KAK_SHOOTING_GALLERY_REWARD,           PROGRESSIVE_BOW,           {},                                                   SpoilerCollectionCheck::Chest(0x42, 0x1F),       SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[KAK_TRADE_ODD_MUSHROOM]                = ItemLocation::Base       (RC_KAK_TRADE_ODD_MUSHROOM,                     0x4E,       "Kak Trade Odd Mushroom",               KAK_TRADE_ODD_MUSHROOM,                ODD_POTION,                {Category::cAdultTrade},                              SpoilerCollectionCheck::ItemGetInf(56),          SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[KAK_GRANNYS_SHOP]                      = ItemLocation::Base       (RC_KAK_GRANNYS_SHOP,                           0x4E,       "Kak Granny's Shop",                    KAK_GRANNYS_SHOP,                      BLUE_POTION_REFILL,        {Category::cMerchant},                                SpoilerCollectionCheck::RandomizerInf(),         SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[KAK_ANJU_AS_ADULT]                     = ItemLocation::Base       (RC_KAK_ANJU_AS_ADULT,                          0x52,       "Kak Anju as Adult",                    KAK_ANJU_AS_ADULT,                     CLAIM_CHECK,               {},                                                   SpoilerCollectionCheck::ItemGetInf(36),          SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[KAK_ANJU_AS_CHILD]                     = ItemLocation::Base       (RC_KAK_ANJU_AS_CHILD,                          0x52,       "Kak Anju as Child",                    KAK_ANJU_AS_CHILD,                     EMPTY_BOTTLE,              {},                                                   SpoilerCollectionCheck::ItemGetInf(4),           SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[KAK_TRADE_POCKET_CUCCO]                = ItemLocation::Base       (RC_KAK_TRADE_POCKET_CUCCO,                     0x52,       "Kak Trade Pocket Cucco",               KAK_TRADE_POCKET_CUCCO,                COJIRO,                    {Category::cAdultTrade},                              SpoilerCollectionCheck::ItemGetInf(38),          SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[KAK_IMPAS_HOUSE_FREESTANDING_POH]      = ItemLocation::Collectable(RC_KAK_IMPAS_HOUSE_FREESTANDING_POH,           0x37, 0x01, "Kak Impas House Freestanding PoH",     KAK_IMPAS_HOUSE_FREESTANDING_POH,      PIECE_OF_HEART,            {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[KAK_WINDMILL_FREESTANDING_POH]         = ItemLocation::Collectable(RC_KAK_WINDMILL_FREESTANDING_POH,              0x48, 0x01, "Kak Windmill Freestanding PoH",        KAK_WINDMILL_FREESTANDING_POH,         PIECE_OF_HEART,            {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_KAKARIKO);

    //Graveyard
    locationTable[GRAVEYARD_SHIELD_GRAVE_CHEST]          = ItemLocation::Chest      (RC_GRAVEYARD_SHIELD_GRAVE_CHEST,               0x40, 0x00, "GY Shield Grave Chest",                GRAVEYARD_SHIELD_GRAVE_CHEST,          HYLIAN_SHIELD,             {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[GRAVEYARD_HEART_PIECE_GRAVE_CHEST]     = ItemLocation::Chest      (RC_GRAVEYARD_HEART_PIECE_GRAVE_CHEST,          0x3F, 0x00, "GY Heart Piece Grave Chest",           GRAVEYARD_HEART_PIECE_GRAVE_CHEST,     PIECE_OF_HEART,            {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[GRAVEYARD_COMPOSERS_GRAVE_CHEST]       = ItemLocation::Chest      (RC_GRAVEYARD_ROYAL_FAMILYS_TOMB_CHEST,         0x41, 0x00, "GY Composers Grave Chest",             GRAVEYARD_COMPOSERS_GRAVE_CHEST,       BOMBS_5,                   {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[GRAVEYARD_HOOKSHOT_CHEST]              = ItemLocation::Chest      (RC_GRAVEYARD_HOOKSHOT_CHEST,                   0x48, 0x00, "GY Hookshot Chest",                    GRAVEYARD_HOOKSHOT_CHEST,              PROGRESSIVE_HOOKSHOT,      {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[GRAVEYARD_DAMPE_RACE_FREESTANDING_POH] = ItemLocation::Collectable(RC_GRAVEYARD_DAMPE_RACE_FREESTANDING_POH,      0x48, 0x07, "GY Dampe Race Freestanding PoH",       GRAVEYARD_DAMPE_RACE_FREESTANDING_POH, PIECE_OF_HEART,            {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[GRAVEYARD_FREESTANDING_POH]            = ItemLocation::Collectable(RC_GRAVEYARD_FREESTANDING_POH,                 0x53, 0x04, "GY Freestanding PoH",                  GRAVEYARD_FREESTANDING_POH,            PIECE_OF_HEART,            {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[GRAVEYARD_DAMPE_GRAVEDIGGING_TOUR]     = ItemLocation::Collectable(RC_GRAVEYARD_DAMPE_GRAVEDIGGING_TOUR,          0x53,       "GY Dampe Gravedigging Tour",           GRAVEYARD_DAMPE_GRAVEDIGGING_TOUR,     PIECE_OF_HEART,            {},                                                   SpoilerCollectionCheck::Gravedigger(0x53, 0x1F), SpoilerCollectionCheckGroup::GROUP_KAKARIKO);

    //Death Mountain
    locationTable[DMT_CHEST]                             = ItemLocation::Chest      (RC_DMT_CHEST,                                  0x60, 0x01, "DMT Chest",                            DMT_CHEST,                             PURPLE_RUPEE,              {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_DEATH_MOUNTAIN);
    locationTable[DMT_STORMS_GROTTO_CHEST]               = ItemLocation::Chest      (RC_DMT_STORMS_GROTTO_CHEST,                    0x3E, 0x17, "DMT Storms Grotto Chest",              DMT_STORMS_GROTTO_CHEST,               HUGE_RUPEE,                {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_DEATH_MOUNTAIN);
    locationTable[DMT_TRADE_BROKEN_SWORD]                = ItemLocation::Base       (RC_DMT_TRADE_BROKEN_SWORD,                     0x60,       "DMT Trade Broken Sword",               DMT_TRADE_BROKEN_SWORD,                PRESCRIPTION,              {Category::cAdultTrade},                              SpoilerCollectionCheck::RandomizerInf(),         SpoilerCollectionCheckGroup::GROUP_DEATH_MOUNTAIN);
    locationTable[DMT_TRADE_EYEDROPS]                    = ItemLocation::Base       (RC_DMT_TRADE_EYEDROPS,                         0x60,       "DMT Trade Eyedrops",                   DMT_TRADE_EYEDROPS,                    CLAIM_CHECK,               {Category::cAdultTrade},                              SpoilerCollectionCheck::RandomizerInf(),         SpoilerCollectionCheckGroup::GROUP_DEATH_MOUNTAIN);
    locationTable[DMT_TRADE_CLAIM_CHECK]                 = ItemLocation::Base       (RC_DMT_TRADE_CLAIM_CHECK,                      0x60,       "DMT Trade Claim Check",                DMT_TRADE_CLAIM_CHECK,                 BIGGORON_SWORD,            {},                                                   SpoilerCollectionCheck::Chest(0x60, 0x1F),       SpoilerCollectionCheckGroup::GROUP_DEATH_MOUNTAIN);
    locationTable[DMT_FREESTANDING_POH]                  = ItemLocation::Collectable(RC_DMT_FREESTANDING_POH,                       0x60, 0x1E, "DMT Freestanding PoH",                 DMT_FREESTANDING_POH,                  PIECE_OF_HEART,            {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_DEATH_MOUNTAIN);

    //Goron City
    locationTable[GC_MAZE_LEFT_CHEST]                    = ItemLocation::Chest      (RC_GC_MAZE_LEFT_CHEST,                         0x62, 0x00, "GC Maze Left Chest",                   GC_MAZE_LEFT_CHEST,                    HUGE_RUPEE,                {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_GORON_CITY);
    locationTable[GC_MAZE_RIGHT_CHEST]                   = ItemLocation::Chest      (RC_GC_MAZE_RIGHT_CHEST,                        0x62, 0x01, "GC Maze Right Chest",                  GC_MAZE_RIGHT_CHEST,                   PURPLE_RUPEE,              {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_GORON_CITY);
    locationTable[GC_MAZE_CENTER_CHEST]                  = ItemLocation::Chest      (RC_GC_MAZE_CENTER_CHEST,                       0x62, 0x02, "GC Maze Center Chest",                 GC_MAZE_CENTER_CHEST,                  PURPLE_RUPEE,              {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_GORON_CITY);
    locationTable[GC_ROLLING_GORON_AS_CHILD]             = ItemLocation::Base       (RC_GC_ROLLING_GORON_AS_CHILD,                  0x62,       "GC Rolling Goron as Child",            GC_ROLLING_GORON_AS_CHILD,             PROGRESSIVE_BOMB_BAG,      {},                                                   SpoilerCollectionCheck::InfTable(0x11, 0x06),    SpoilerCollectionCheckGroup::GROUP_GORON_CITY);
    locationTable[GC_ROLLING_GORON_AS_ADULT]             = ItemLocation::Base       (RC_GC_ROLLING_GORON_AS_ADULT,                  0x62,       "GC Rolling Goron as Adult",            GC_ROLLING_GORON_AS_ADULT,             GORON_TUNIC,               {},                                                   SpoilerCollectionCheck::InfTable(0x10, 0x01),    SpoilerCollectionCheckGroup::GROUP_GORON_CITY);
    locationTable[GC_DARUNIAS_JOY]                       = ItemLocation::Base       (RC_GC_DARUNIAS_JOY,                            0x62,       "GC Darunias Joy",                      GC_DARUNIAS_JOY,                       PROGRESSIVE_STRENGTH,      {},                                                   SpoilerCollectionCheck::Chest(0x62, 0x1E),       SpoilerCollectionCheckGroup::GROUP_GORON_CITY);
    locationTable[GC_POT_FREESTANDING_POH]               = ItemLocation::Collectable(RC_GC_POT_FREESTANDING_POH,                    0x62, 0x1F, "GC Pot Freestanding PoH",              GC_POT_FREESTANDING_POH,               PIECE_OF_HEART,            {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_GORON_CITY);
    locationTable[GC_DEKU_SCRUB_GROTTO_LEFT]             = ItemLocation::GrottoScrub(RC_GC_DEKU_SCRUB_GROTTO_LEFT,                  0xFB,       "GC Deku Scrub Grotto Left",            GC_DEKU_SCRUB_GROTTO_LEFT,             BUY_DEKU_NUT_5,            {Category::cDekuScrub},                               SpoilerCollectionCheck::Scrub(),                 SpoilerCollectionCheckGroup::GROUP_GORON_CITY);
    locationTable[GC_DEKU_SCRUB_GROTTO_RIGHT]            = ItemLocation::GrottoScrub(RC_GC_DEKU_SCRUB_GROTTO_RIGHT,                 0xFB,       "GC Deku Scrub Grotto Right",           GC_DEKU_SCRUB_GROTTO_RIGHT,            BUY_BOMBS_535,             {Category::cDekuScrub},                               SpoilerCollectionCheck::Scrub(),                 SpoilerCollectionCheckGroup::GROUP_GORON_CITY);
    locationTable[GC_DEKU_SCRUB_GROTTO_CENTER]           = ItemLocation::GrottoScrub(RC_GC_DEKU_SCRUB_GROTTO_CENTER,                0xFB,       "GC Deku Scrub Grotto Center",          GC_DEKU_SCRUB_GROTTO_CENTER,           BUY_ARROWS_30,             {Category::cDekuScrub},                               SpoilerCollectionCheck::Scrub(),                 SpoilerCollectionCheckGroup::GROUP_GORON_CITY);
    locationTable[GC_MEDIGORON]                          = ItemLocation::Base       (RC_GC_MEDIGORON,                               0x62,       "GC Medigoron",                         GC_MEDIGORON,                          GIANTS_KNIFE,              {Category::cMerchant},                                SpoilerCollectionCheck::Merchant(),              SpoilerCollectionCheckGroup::GROUP_GORON_CITY);

    //Death Mountain Crater
    locationTable[DMC_UPPER_GROTTO_CHEST]                = ItemLocation::Chest      (RC_DMC_UPPER_GROTTO_CHEST,                     0x3E, 0x1A, "DMC Upper Grotto Chest",               DMC_UPPER_GROTTO_CHEST,                BOMBS_20,                  {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_DEATH_MOUNTAIN);
    locationTable[DMC_WALL_FREESTANDING_POH]             = ItemLocation::Collectable(RC_DMC_WALL_FREESTANDING_POH,                  0x61, 0x02, "DMC Wall Freestanding PoH",            DMC_WALL_FREESTANDING_POH,             PIECE_OF_HEART,            {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_DEATH_MOUNTAIN);
    locationTable[DMC_VOLCANO_FREESTANDING_POH]          = ItemLocation::Collectable(RC_DMC_VOLCANO_FREESTANDING_POH,               0x61, 0x08, "DMC Volcano Freestanding PoH",         DMC_VOLCANO_FREESTANDING_POH,          PIECE_OF_HEART,            {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_DEATH_MOUNTAIN);
    locationTable[DMC_DEKU_SCRUB]                        = ItemLocation::Base       (RC_DMC_DEKU_SCRUB,                             0x61,       "DMC Deku Scrub",                       DMC_DEKU_SCRUB,                        BUY_BOMBS_535,             {Category::cDekuScrub},                               SpoilerCollectionCheck::Scrub(),                 SpoilerCollectionCheckGroup::GROUP_DEATH_MOUNTAIN);
    locationTable[DMC_DEKU_SCRUB_GROTTO_LEFT]            = ItemLocation::GrottoScrub(RC_DMC_DEKU_SCRUB_GROTTO_LEFT,                 0xF9,       "DMC Deku Scrub Grotto Left",           DMC_DEKU_SCRUB_GROTTO_LEFT,            BUY_DEKU_NUT_5,            {Category::cDekuScrub},                               SpoilerCollectionCheck::Scrub(),                 SpoilerCollectionCheckGroup::GROUP_DEATH_MOUNTAIN);
    locationTable[DMC_DEKU_SCRUB_GROTTO_RIGHT]           = ItemLocation::GrottoScrub(RC_DMC_DEKU_SCRUB_GROTTO_RIGHT,                0xF9,       "DMC Deku Scrub Grotto Right",          DMC_DEKU_SCRUB_GROTTO_RIGHT,           BUY_BOMBS_535,             {Category::cDekuScrub},                               SpoilerCollectionCheck::Scrub(),                 SpoilerCollectionCheckGroup::GROUP_DEATH_MOUNTAIN);
    locationTable[DMC_DEKU_SCRUB_GROTTO_CENTER]          = ItemLocation::GrottoScrub(RC_DMC_DEKU_SCRUB_GROTTO_CENTER,               0xF9,       "DMC Deku Scrub Grotto Center",         DMC_DEKU_SCRUB_GROTTO_CENTER,          BUY_ARROWS_30,             {Category::cDekuScrub},                               SpoilerCollectionCheck::Scrub(),                 SpoilerCollectionCheckGroup::GROUP_DEATH_MOUNTAIN);

    //Zoras River
    locationTable[ZR_OPEN_GROTTO_CHEST]                  = ItemLocation::Chest      (RC_ZR_OPEN_GROTTO_CHEST,                       0x3E, 0x09, "ZR Open Grotto Chest",                 ZR_OPEN_GROTTO_CHEST,                  RED_RUPEE,                 {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_ZORAS_RIVER);
    locationTable[ZR_MAGIC_BEAN_SALESMAN]                = ItemLocation::Base       (RC_ZR_MAGIC_BEAN_SALESMAN,                     0x54,       "ZR Magic Bean Salesman",               ZR_MAGIC_BEAN_SALESMAN,                MAGIC_BEAN,                {},                                                   SpoilerCollectionCheck::MagicBeans(),            SpoilerCollectionCheckGroup::GROUP_ZORAS_RIVER);
    locationTable[ZR_FROGS_ZELDAS_LULLABY]               = ItemLocation::Base       (RC_ZR_FROGS_ZELDAS_LULLABY,                    0x54,       "ZR Frogs Zelda's Lullaby",             ZR_FROGS_ZELDAS_LULLABY,               PURPLE_RUPEE,              {},                                                   SpoilerCollectionCheck::EventChkInf(0xD1),       SpoilerCollectionCheckGroup::GROUP_ZORAS_RIVER);
    locationTable[ZR_FROGS_EPONAS_SONG]                  = ItemLocation::Base       (RC_ZR_FROGS_EPONAS_SONG,                       0x54,       "ZR Frogs Epona's Song",                ZR_FROGS_EPONAS_SONG,                  PURPLE_RUPEE,              {},                                                   SpoilerCollectionCheck::EventChkInf(0xD2),       SpoilerCollectionCheckGroup::GROUP_ZORAS_RIVER);
    locationTable[ZR_FROGS_SARIAS_SONG]                  = ItemLocation::Base       (RC_ZR_FROGS_SARIAS_SONG,                       0x54,       "ZR Frogs Saria's Song",                ZR_FROGS_SARIAS_SONG,                  PURPLE_RUPEE,              {},                                                   SpoilerCollectionCheck::EventChkInf(0xD4),       SpoilerCollectionCheckGroup::GROUP_ZORAS_RIVER);
    locationTable[ZR_FROGS_SUNS_SONG]                    = ItemLocation::Base       (RC_ZR_FROGS_SUNS_SONG,                         0x54,       "ZR Frogs Sun's Song",                  ZR_FROGS_SUNS_SONG,                    PURPLE_RUPEE,              {},                                                   SpoilerCollectionCheck::EventChkInf(0xD3),       SpoilerCollectionCheckGroup::GROUP_ZORAS_RIVER);
    locationTable[ZR_FROGS_SONG_OF_TIME]                 = ItemLocation::Base       (RC_ZR_FROGS_SONG_OF_TIME,                      0x54,       "ZR Frogs Song of Time",                ZR_FROGS_SONG_OF_TIME,                 PURPLE_RUPEE,              {},                                                   SpoilerCollectionCheck::EventChkInf(0xD5),       SpoilerCollectionCheckGroup::GROUP_ZORAS_RIVER);
    locationTable[ZR_FROGS_IN_THE_RAIN]                  = ItemLocation::Base       (RC_ZR_FROGS_IN_THE_RAIN,                       0x54,       "ZR Frogs in the Rain",                 ZR_FROGS_IN_THE_RAIN,                  PIECE_OF_HEART,            {},                                                   SpoilerCollectionCheck::EventChkInf(0xD6),       SpoilerCollectionCheckGroup::GROUP_ZORAS_RIVER);
    locationTable[ZR_FROGS_OCARINA_GAME]                 = ItemLocation::Base       (RC_ZR_FROGS_OCARINA_GAME,                      0x54,       "ZR Frogs Ocarina Game",                ZR_FROGS_OCARINA_GAME,                 PIECE_OF_HEART,            {},                                                   SpoilerCollectionCheck::EventChkInf(0xD0),       SpoilerCollectionCheckGroup::GROUP_ZORAS_RIVER);
    locationTable[ZR_NEAR_OPEN_GROTTO_FREESTANDING_POH]  = ItemLocation::Collectable(RC_ZR_NEAR_OPEN_GROTTO_FREESTANDING_POH,       0x54, 0x04, "ZR Near Open Grotto Freestanding PoH", ZR_NEAR_OPEN_GROTTO_FREESTANDING_POH,  PIECE_OF_HEART,            {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_ZORAS_RIVER);
    locationTable[ZR_NEAR_DOMAIN_FREESTANDING_POH]       = ItemLocation::Collectable(RC_ZR_NEAR_DOMAIN_FREESTANDING_POH,            0x54, 0x0B, "ZR Near Domain Freestanding PoH",      ZR_NEAR_DOMAIN_FREESTANDING_POH,       PIECE_OF_HEART,            {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_ZORAS_RIVER);
    locationTable[ZR_DEKU_SCRUB_GROTTO_REAR]             = ItemLocation::GrottoScrub(RC_ZR_DEKU_SCRUB_GROTTO_REAR,                  0xEB,       "ZR Deku Scrub Grotto Rear",            ZR_DEKU_SCRUB_GROTTO_REAR,             BUY_RED_POTION_30,         {Category::cDekuScrub},                               SpoilerCollectionCheck::Scrub(),                 SpoilerCollectionCheckGroup::GROUP_ZORAS_RIVER);
    locationTable[ZR_DEKU_SCRUB_GROTTO_FRONT]            = ItemLocation::GrottoScrub(RC_ZR_DEKU_SCRUB_GROTTO_FRONT,                 0xEB,       "ZR Deku Scrub Grotto Front",           ZR_DEKU_SCRUB_GROTTO_FRONT,            BUY_GREEN_POTION,          {Category::cDekuScrub},                               SpoilerCollectionCheck::Scrub(),                 SpoilerCollectionCheckGroup::GROUP_ZORAS_RIVER);

    //Zoras Domain
    locationTable[ZD_CHEST]                              = ItemLocation::Chest      (RC_ZD_CHEST,                                   0x58, 0x00, "ZD Chest",                             ZD_CHEST,                              PIECE_OF_HEART,            {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_ZORAS_DOMAIN);
    locationTable[ZD_DIVING_MINIGAME]                    = ItemLocation::Base       (RC_ZD_DIVING_MINIGAME,                         0x58,       "ZD Diving Minigame",                   ZD_DIVING_MINIGAME,                    PROGRESSIVE_SCALE,         {},                                                   SpoilerCollectionCheck::EventChkInf(0x38),       SpoilerCollectionCheckGroup::GROUP_ZORAS_DOMAIN);
    locationTable[ZD_KING_ZORA_THAWED]                   = ItemLocation::Base       (RC_ZD_KING_ZORA_THAWED,                        0x58,       "ZD King Zora Thawed",                  ZD_KING_ZORA_THAWED,                   ZORA_TUNIC,                {},                                                   SpoilerCollectionCheck::InfTable(0x13, 0x01),    SpoilerCollectionCheckGroup::GROUP_ZORAS_DOMAIN);
    locationTable[ZD_TRADE_PRESCRIPTION]                 = ItemLocation::Base       (RC_ZD_TRADE_PRESCRIPTION,                      0x58,       "ZD Trade Prescription",                ZD_TRADE_PRESCRIPTION,                 EYEBALL_FROG,              {Category::cAdultTrade},                              SpoilerCollectionCheck::Chest(0x58, 0x1F),       SpoilerCollectionCheckGroup::GROUP_ZORAS_DOMAIN);

    //Zoras Fountain
    locationTable[ZF_ICEBERG_FREESTANDING_POH]           = ItemLocation::Collectable(RC_ZF_ICEBERC_FREESTANDING_POH,                0x59, 0x01, "ZF Iceberg Freestanding PoH",          ZF_ICEBERG_FREESTANDING_POH,           PIECE_OF_HEART,            {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_ZORAS_DOMAIN);
    locationTable[ZF_BOTTOM_FREESTANDING_POH]            = ItemLocation::Collectable(RC_ZF_BOTTOM_FREESTANDING_POH,                 0x59, 0x14, "ZF Bottom Freestanding PoH",           ZF_BOTTOM_FREESTANDING_POH,            PIECE_OF_HEART,            {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_ZORAS_DOMAIN);

    //Lon Lon Ranch
    locationTable[LLR_TALONS_CHICKENS]                   = ItemLocation::Base       (RC_LLR_TALONS_CHICKENS,                        0x4C,       "LLR Talons Chickens",                  LLR_TALONS_CHICKENS,                   BOTTLE_WITH_MILK,          {},                                                   SpoilerCollectionCheck::ItemGetInf(10),          SpoilerCollectionCheckGroup::GROUP_LON_LON_RANCH);
    locationTable[LLR_FREESTANDING_POH]                  = ItemLocation::Collectable(RC_LLR_FREESTANDING_POH,                       0x4C, 0x01, "LLR Freestanding PoH",                 LLR_FREESTANDING_POH,                  PIECE_OF_HEART,            {},                                                                                                    SpoilerCollectionCheckGroup::GROUP_LON_LON_RANCH);
    locationTable[LLR_DEKU_SCRUB_GROTTO_LEFT]            = ItemLocation::GrottoScrub(RC_LLR_DEKU_SCRUB_GROTTO_LEFT,                 0xFC,       "LLR Deku Scrub Grotto Left",           LLR_DEKU_SCRUB_GROTTO_LEFT,            BUY_DEKU_NUT_5,            {Category::cDekuScrub},                               SpoilerCollectionCheck::Scrub(),                 SpoilerCollectionCheckGroup::GROUP_LON_LON_RANCH);
    locationTable[LLR_DEKU_SCRUB_GROTTO_RIGHT]           = ItemLocation::GrottoScrub(RC_LLR_DEKU_SCRUB_GROTTO_RIGHT,                0xFC,       "LLR Deku Scrub Grotto Right",          LLR_DEKU_SCRUB_GROTTO_RIGHT,           BUY_BOMBS_535,             {Category::cDekuScrub},                               SpoilerCollectionCheck::Scrub(),                 SpoilerCollectionCheckGroup::GROUP_LON_LON_RANCH);
    locationTable[LLR_DEKU_SCRUB_GROTTO_CENTER]          = ItemLocation::GrottoScrub(RC_LLR_DEKU_SCRUB_GROTTO_CENTER,               0xFC,       "LLR Deku Scrub Grotto Center",         LLR_DEKU_SCRUB_GROTTO_CENTER,          BUY_DEKU_SEEDS_30,         {Category::cDekuScrub},                               SpoilerCollectionCheck::Scrub(),                 SpoilerCollectionCheckGroup::GROUP_LON_LON_RANCH);

    /*-------------------
       --- DUNGEONS ---
      -------------------*/

    //Deku Tree Vanilla
    locationTable[DEKU_TREE_MAP_CHEST]                                         = ItemLocation::Chest      (RC_DEKU_TREE_MAP_CHEST,                                          0x00, 0x03, "Deku Tree Map Chest",                                DEKU_TREE_MAP_CHEST,                 DEKU_TREE_MAP,            {Category::cVanillaMap},                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_DEKU_TREE);
    locationTable[DEKU_TREE_COMPASS_CHEST]                                     = ItemLocation::Chest      (RC_DEKU_TREE_COMPASS_CHEST,                                      0x00, 0x02, "Deku Tree Compass Chest",                            DEKU_TREE_COMPASS_CHEST,             DEKU_TREE_COMPASS,        {Category::cVanillaCompass},                                                              SpoilerCollectionCheckGroup::GROUP_DUNGEON_DEKU_TREE);
    locationTable[DEKU_TREE_COMPASS_ROOM_SIDE_CHEST]                           = ItemLocation::Chest      (RC_DEKU_TREE_COMPASS_ROOM_SIDE_CHEST,                            0x00, 0x06, "Deku Tree Compass Room Side Chest",                  DEKU_TREE_COMPASS_ROOM_SIDE_CHEST,   RECOVERY_HEART,           {},                                                                                       SpoilerCollectionCheckGroup::GROUP_DUNGEON_DEKU_TREE);
    locationTable[DEKU_TREE_BASEMENT_CHEST]                                    = ItemLocation::Chest      (RC_DEKU_TREE_BASEMENT_CHEST,                                     0x00, 0x04, "Deku Tree Basement Chest",                           DEKU_TREE_BASEMENT_CHEST,            RECOVERY_HEART,           {},                                                                                       SpoilerCollectionCheckGroup::GROUP_DUNGEON_DEKU_TREE);
    locationTable[DEKU_TREE_SLINGSHOT_CHEST]                                   = ItemLocation::Chest      (RC_DEKU_TREE_SLINGSHOT_CHEST,                                    0x00, 0x01, "Deku Tree Slingshot Chest",                          DEKU_TREE_SLINGSHOT_CHEST,           PROGRESSIVE_SLINGSHOT,    {},                                                                                       SpoilerCollectionCheckGroup::GROUP_DUNGEON_DEKU_TREE);
    locationTable[DEKU_TREE_SLINGSHOT_ROOM_SIDE_CHEST]                         = ItemLocation::Chest      (RC_DEKU_TREE_SLINGSHOT_ROOM_SIDE_CHEST,                          0x00, 0x05, "Deku Tree Slingshot Room Side Chest",                DEKU_TREE_SLINGSHOT_ROOM_SIDE_CHEST, RECOVERY_HEART,           {},                                                                                       SpoilerCollectionCheckGroup::GROUP_DUNGEON_DEKU_TREE);
    //Deku Tree MQ
    locationTable[DEKU_TREE_MQ_MAP_CHEST]                                      = ItemLocation::Chest      (RC_DEKU_TREE_MQ_MAP_CHEST,                                       0x00, 0x03, "Deku Tree MQ Map Chest",                             DEKU_TREE_MQ_MAP_CHEST,                 DEKU_TREE_MAP,         {Category::cVanillaMap},                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_DEKU_TREE);
    locationTable[DEKU_TREE_MQ_COMPASS_CHEST]                                  = ItemLocation::Chest      (RC_DEKU_TREE_MQ_COMPASS_CHEST,                                   0x00, 0x01, "Deku Tree MQ Compass Chest",                         DEKU_TREE_MQ_COMPASS_CHEST,             DEKU_TREE_COMPASS,     {Category::cVanillaCompass},                                                              SpoilerCollectionCheckGroup::GROUP_DUNGEON_DEKU_TREE);
    locationTable[DEKU_TREE_MQ_SLINGSHOT_CHEST]                                = ItemLocation::Chest      (RC_DEKU_TREE_MQ_SLINGSHOT_CHEST,                                 0x00, 0x06, "Deku Tree MQ Slingshot Chest",                       DEKU_TREE_MQ_SLINGSHOT_CHEST,           PROGRESSIVE_SLINGSHOT, {},                                                                                       SpoilerCollectionCheckGroup::GROUP_DUNGEON_DEKU_TREE);
    locationTable[DEKU_TREE_MQ_SLINGSHOT_ROOM_BACK_CHEST]                      = ItemLocation::Chest      (RC_DEKU_TREE_MQ_SLINGSHOT_ROOM_BACK_CHEST,                       0x00, 0x02, "Deku Tree MQ Slingshot Room Back Chest",             DEKU_TREE_MQ_SLINGSHOT_ROOM_BACK_CHEST, DEKU_SHIELD,           {},                                                                                       SpoilerCollectionCheckGroup::GROUP_DUNGEON_DEKU_TREE);
    locationTable[DEKU_TREE_MQ_BASEMENT_CHEST]                                 = ItemLocation::Chest      (RC_DEKU_TREE_MQ_BASEMENT_CHEST,                                  0x00, 0x04, "Deku Tree MQ Basement Chest",                        DEKU_TREE_MQ_BASEMENT_CHEST,            DEKU_SHIELD,           {},                                                                                       SpoilerCollectionCheckGroup::GROUP_DUNGEON_DEKU_TREE);
    locationTable[DEKU_TREE_MQ_BEFORE_SPINNING_LOG_CHEST]                      = ItemLocation::Chest      (RC_DEKU_TREE_MQ_BEFORE_SPINNING_LOG_CHEST,                       0x00, 0x05, "Deku Tree MQ Before Spinning Log Chest",             DEKU_TREE_MQ_BEFORE_SPINNING_LOG_CHEST, RECOVERY_HEART,        {},                                                                                       SpoilerCollectionCheckGroup::GROUP_DUNGEON_DEKU_TREE);
    locationTable[DEKU_TREE_MQ_AFTER_SPINNING_LOG_CHEST]                       = ItemLocation::Chest      (RC_DEKU_TREE_MQ_AFTER_SPINNING_LOG_CHEST,                        0x00, 0x00, "Deku Tree MQ After Spinning Log Chest",              DEKU_TREE_MQ_AFTER_SPINNING_LOG_CHEST,  PURPLE_RUPEE,          {},                                                                                       SpoilerCollectionCheckGroup::GROUP_DUNGEON_DEKU_TREE);
    locationTable[DEKU_TREE_MQ_DEKU_SCRUB]                                     = ItemLocation::Base       (RC_DEKU_TREE_MQ_DEKU_SCRUB,                                      0x00,       "Deku Tree MQ Deku Scrub",                            DEKU_TREE_MQ_DEKU_SCRUB,                BUY_DEKU_SHIELD,       {Category::cDekuScrub},                                  SpoilerCollectionCheck::Scrub(), SpoilerCollectionCheckGroup::GROUP_DUNGEON_DEKU_TREE);

    //Dodongos Cavern Shared
    locationTable[DODONGOS_CAVERN_BOSS_ROOM_CHEST]                             = ItemLocation::Chest      (RC_DODONGOS_CAVERN_BOSS_ROOM_CHEST,                              0x12, 0x00, "Dodongos Cavern Boss Room Chest",                    DODONGOS_CAVERN_BOSS_ROOM_CHEST,                                  BOMBS_5,                 {},                                                           SpoilerCollectionCheckGroup::GROUP_DUNGEON_DODONGOS_CAVERN);
    //Dodongos Cavern Vanilla
    locationTable[DODONGOS_CAVERN_MAP_CHEST]                                   = ItemLocation::Chest      (RC_DODONGOS_CAVERN_MAP_CHEST,                                    0x01, 0x08, "Dodongos Cavern Map Chest",                          DODONGOS_CAVERN_MAP_CHEST,                                        DODONGOS_CAVERN_MAP,     {Category::cVanillaMap},                                      SpoilerCollectionCheckGroup::GROUP_DUNGEON_DODONGOS_CAVERN);
    locationTable[DODONGOS_CAVERN_COMPASS_CHEST]                               = ItemLocation::Chest      (RC_DODONGOS_CAVERN_COMPASS_CHEST,                                0x01, 0x05, "Dodongos Cavern Compass Chest",                      DODONGOS_CAVERN_COMPASS_CHEST,                                    DODONGOS_CAVERN_COMPASS, {Category::cVanillaCompass},                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_DODONGOS_CAVERN);
    locationTable[DODONGOS_CAVERN_BOMB_FLOWER_PLATFORM_CHEST]                  = ItemLocation::Chest      (RC_DODONGOS_CAVERN_BOMB_FLOWER_PLATFORM_CHEST,                   0x01, 0x06, "Dodongos Cavern Bomb Flower Platform Chest",         DODONGOS_CAVERN_BOMB_FLOWER_PLATFORM_CHEST,                       RED_RUPEE,               {},                                                           SpoilerCollectionCheckGroup::GROUP_DUNGEON_DODONGOS_CAVERN);
    locationTable[DODONGOS_CAVERN_BOMB_BAG_CHEST]                              = ItemLocation::Chest      (RC_DODONGOS_CAVERN_BOMB_BAG_CHEST,                               0x01, 0x04, "Dodongos Cavern Bomb Bag Chest",                     DODONGOS_CAVERN_BOMB_BAG_CHEST,                                   PROGRESSIVE_BOMB_BAG,    {},                                                           SpoilerCollectionCheckGroup::GROUP_DUNGEON_DODONGOS_CAVERN);
    locationTable[DODONGOS_CAVERN_END_OF_BRIDGE_CHEST]                         = ItemLocation::Chest      (RC_DODONGOS_CAVERN_END_OF_BRIDGE_CHEST,                          0x01, 0x0A, "Dodongos Cavern End Of Bridge Chest",                DODONGOS_CAVERN_END_OF_BRIDGE_CHEST,                              DEKU_SHIELD,             {},                                                           SpoilerCollectionCheckGroup::GROUP_DUNGEON_DODONGOS_CAVERN);
    locationTable[DODONGOS_CAVERN_DEKU_SCRUB_NEAR_BOMB_BAG_LEFT]               = ItemLocation::Base       (RC_DODONGOS_CAVERN_DEKU_SCRUB_NEAR_BOMB_BAG_LEFT,                0x01,       "Dodongos Cavern Deku Scrub Near Bomb Bag Left",      DODONGOS_CAVERN_DEKU_SCRUB_NEAR_BOMB_BAG_LEFT,                    BUY_DEKU_NUT_5,          {Category::cDekuScrub},      SpoilerCollectionCheck::Scrub(), SpoilerCollectionCheckGroup::GROUP_DUNGEON_DODONGOS_CAVERN);
    locationTable[DODONGOS_CAVERN_DEKU_SCRUB_SIDE_ROOM_NEAR_DODONGOS]          = ItemLocation::Base       (RC_DODONGOS_CAVERN_DEKU_SCRUB_SIDE_ROOM_NEAR_DODONGOS,           0x01,       "Dodongos Cavern Deku Scrub Side Room Near Dodongos", DODONGOS_CAVERN_DEKU_SCRUB_SIDE_ROOM_NEAR_DODONGOS,               BUY_DEKU_STICK_1,        {Category::cDekuScrub},      SpoilerCollectionCheck::Scrub(), SpoilerCollectionCheckGroup::GROUP_DUNGEON_DODONGOS_CAVERN);
    locationTable[DODONGOS_CAVERN_DEKU_SCRUB_NEAR_BOMB_BAG_RIGHT]              = ItemLocation::Base       (RC_DODONGOS_CAVERN_DEKU_SCRUB_NEAR_BOMB_BAG_RIGHT,               0x01,       "Dodongos Cavern Deku Scrub Near Bomb Bag Right",     DODONGOS_CAVERN_DEKU_SCRUB_NEAR_BOMB_BAG_RIGHT,                   BUY_DEKU_SEEDS_30,       {Category::cDekuScrub},      SpoilerCollectionCheck::Scrub(), SpoilerCollectionCheckGroup::GROUP_DUNGEON_DODONGOS_CAVERN);
    locationTable[DODONGOS_CAVERN_DEKU_SCRUB_LOBBY]                            = ItemLocation::Base       (RC_DODONGOS_CAVERN_DEKU_SCRUB_LOBBY,                             0x01,       "Dodongos Cavern Deku Scrub Lobby",                   DODONGOS_CAVERN_DEKU_SCRUB_LOBBY,                                 BUY_DEKU_SHIELD,         {Category::cDekuScrub},      SpoilerCollectionCheck::Scrub(), SpoilerCollectionCheckGroup::GROUP_DUNGEON_DODONGOS_CAVERN);
    //Dodongos Cavern MQ
    locationTable[DODONGOS_CAVERN_MQ_MAP_CHEST]                                = ItemLocation::Chest      (RC_DODONGOS_CAVERN_MQ_MAP_CHEST,                                 0x01, 0x00, "Dodongos Cavern MQ Map Chest",                       DODONGOS_CAVERN_MQ_MAP_CHEST,                                     DODONGOS_CAVERN_MAP,     {Category::cVanillaMap},                                      SpoilerCollectionCheckGroup::GROUP_DUNGEON_DODONGOS_CAVERN);
    locationTable[DODONGOS_CAVERN_MQ_BOMB_BAG_CHEST]                           = ItemLocation::Chest      (RC_DODONGOS_CAVERN_MQ_BOMB_BAG_CHEST,                            0x01, 0x04, "Dodongos Cavern MQ Bomb Bag Chest",                  DODONGOS_CAVERN_MQ_BOMB_BAG_CHEST,                                PROGRESSIVE_BOMB_BAG,    {},                                                           SpoilerCollectionCheckGroup::GROUP_DUNGEON_DODONGOS_CAVERN);
    locationTable[DODONGOS_CAVERN_MQ_COMPASS_CHEST]                            = ItemLocation::Chest      (RC_DODONGOS_CAVERN_MQ_COMPASS_CHEST,                             0x01, 0x05, "Dodongos Cavern MQ Compass Chest",                   DODONGOS_CAVERN_MQ_COMPASS_CHEST,                                 DODONGOS_CAVERN_COMPASS, {Category::cVanillaCompass},                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_DODONGOS_CAVERN);
    locationTable[DODONGOS_CAVERN_MQ_LARVAE_ROOM_CHEST]                        = ItemLocation::Chest      (RC_DODONGOS_CAVERN_MQ_LARVAE_ROOM_CHEST,                         0x01, 0x02, "Dodongos Cavern MQ Larvae Room Chest",               DODONGOS_CAVERN_MQ_LARVAE_ROOM_CHEST,                             DEKU_SHIELD,             {},                                                           SpoilerCollectionCheckGroup::GROUP_DUNGEON_DODONGOS_CAVERN);
    locationTable[DODONGOS_CAVERN_MQ_TORCH_PUZZLE_ROOM_CHEST]                  = ItemLocation::Chest      (RC_DODONGOS_CAVERN_MQ_TORCH_PUZZLE_ROOM_CHEST,                   0x01, 0x03, "Dodongos Cavern MQ Torch Puzzle Room Chest",         DODONGOS_CAVERN_MQ_TORCH_PUZZLE_ROOM_CHEST,                       BLUE_RUPEE,              {},                                                           SpoilerCollectionCheckGroup::GROUP_DUNGEON_DODONGOS_CAVERN);
    locationTable[DODONGOS_CAVERN_MQ_UNDER_GRAVE_CHEST]                        = ItemLocation::Chest      (RC_DODONGOS_CAVERN_MQ_UNDER_GRAVE_CHEST,                         0x01, 0x01, "Dodongos Cavern MQ Under Grave Chest",               DODONGOS_CAVERN_MQ_UNDER_GRAVE_CHEST,                             HYLIAN_SHIELD,           {},                                                           SpoilerCollectionCheckGroup::GROUP_DUNGEON_DODONGOS_CAVERN);
    locationTable[DODONGOS_CAVERN_MQ_DEKU_SCRUB_LOBBY_REAR]                    = ItemLocation::Base       (RC_DODONGOS_CAVERN_MQ_DEKU_SCRUB_LOBBY_REAR,                     0x01,       "Dodongos Cavern Deku Scrub Lobby Rear",              DODONGOS_CAVERN_MQ_DEKU_SCRUB_LOBBY_REAR,                         BUY_DEKU_STICK_1,        {Category::cDekuScrub},      SpoilerCollectionCheck::Scrub(), SpoilerCollectionCheckGroup::GROUP_DUNGEON_DODONGOS_CAVERN);
    locationTable[DODONGOS_CAVERN_MQ_DEKU_SCRUB_LOBBY_FRONT]                   = ItemLocation::Base       (RC_DODONGOS_CAVERN_MQ_DEKU_SCRUB_LOBBY_FRONT,                    0x01,       "Dodongos Cavern Deku Scrub Lobby Front",             DODONGOS_CAVERN_MQ_DEKU_SCRUB_LOBBY_FRONT,                        BUY_DEKU_SEEDS_30,       {Category::cDekuScrub},      SpoilerCollectionCheck::Scrub(), SpoilerCollectionCheckGroup::GROUP_DUNGEON_DODONGOS_CAVERN);
    locationTable[DODONGOS_CAVERN_MQ_DEKU_SCRUB_STAIRCASE]                     = ItemLocation::Base       (RC_DODONGOS_CAVERN_MQ_DEKU_SCRUB_STAIRCASE,                      0x01,       "Dodongos Cavern Deku Scrub Staircase",               DODONGOS_CAVERN_MQ_DEKU_SCRUB_STAIRCASE,                          BUY_DEKU_SHIELD,         {Category::cDekuScrub},      SpoilerCollectionCheck::Scrub(), SpoilerCollectionCheckGroup::GROUP_DUNGEON_DODONGOS_CAVERN);
    locationTable[DODONGOS_CAVERN_MQ_DEKU_SCRUB_SIDE_ROOM_NEAR_LOWER_LIZALFOS] = ItemLocation::Base       (RC_DODONGOS_CAVERN_MQ_DEKU_SCRUB_SIDE_ROOM_NEAR_LOWER_LIZALFOS,  0x01,       "Dodongos Cavern Deku Scrub Side Room Near Lower Lizalfos",DODONGOS_CAVERN_MQ_DEKU_SCRUB_SIDE_ROOM_NEAR_LOWER_LIZALFOS, BUY_RED_POTION_30,       {Category::cDekuScrub},      SpoilerCollectionCheck::Scrub(), SpoilerCollectionCheckGroup::GROUP_DUNGEON_DODONGOS_CAVERN);

    //Jabu Jabus Belly Vanilla
    locationTable[JABU_JABUS_BELLY_MAP_CHEST]                                  = ItemLocation::Chest      (RC_JABU_JABUS_BELLY_MAP_CHEST,                                   0x02, 0x02, "Jabu Jabus Belly Map Chest",                         JABU_JABUS_BELLY_MAP_CHEST,                       JABU_JABUS_BELLY_MAP,     {Category::cVanillaMap},                                                     SpoilerCollectionCheckGroup::GROUP_DUNGEON_JABUJABUS_BELLY);
    locationTable[JABU_JABUS_BELLY_COMPASS_CHEST]                              = ItemLocation::Chest      (RC_JABU_JABUS_BELLY_COMPASS_CHEST,                               0x02, 0x04, "Jabu Jabus Belly Compass Chest",                     JABU_JABUS_BELLY_COMPASS_CHEST,                   JABU_JABUS_BELLY_COMPASS, {Category::cVanillaCompass},                                                 SpoilerCollectionCheckGroup::GROUP_DUNGEON_JABUJABUS_BELLY);
    locationTable[JABU_JABUS_BELLY_BOOMERANG_CHEST]                            = ItemLocation::Chest      (RC_JABU_JABUS_BELLY_BOOMERANG_CHEST,                             0x02, 0x01, "Jabu Jabus Belly Boomerang Chest",                   JABU_JABUS_BELLY_BOOMERANG_CHEST,                 BOOMERANG,                {},                                                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_JABUJABUS_BELLY);
    locationTable[JABU_JABUS_BELLY_DEKU_SCRUB]                                 = ItemLocation::Base       (RC_JABU_JABUS_BELLY_DEKU_SCRUB,                                  0x02,       "Jabu Jabus Belly Deku Scrub",                        JABU_JABUS_BELLY_DEKU_SCRUB,                      BUY_DEKU_NUT_5,           {Category::cDekuScrub},                     SpoilerCollectionCheck::Scrub(), SpoilerCollectionCheckGroup::GROUP_DUNGEON_JABUJABUS_BELLY);
    //Jabu Jabus Belly MQ
    locationTable[JABU_JABUS_BELLY_MQ_FIRST_ROOM_SIDE_CHEST]                   = ItemLocation::Chest      (RC_JABU_JABUS_BELLY_MQ_FIRST_ROOM_SIDE_CHEST,                    0x02, 0x05, "Jabu Jabus Belly MQ First Room Side Chest",          JABU_JABUS_BELLY_MQ_FIRST_ROOM_SIDE_CHEST,        DEKU_NUTS_5,              {},                                                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_JABUJABUS_BELLY);
    locationTable[JABU_JABUS_BELLY_MQ_MAP_CHEST]                               = ItemLocation::Chest      (RC_JABU_JABUS_BELLY_MQ_MAP_CHEST,                                0x02, 0x03, "Jabu Jabus Belly MQ Map Chest",                      JABU_JABUS_BELLY_MQ_MAP_CHEST,                    JABU_JABUS_BELLY_MAP,     {Category::cVanillaMap},                                                     SpoilerCollectionCheckGroup::GROUP_DUNGEON_JABUJABUS_BELLY);
    locationTable[JABU_JABUS_BELLY_MQ_SECOND_ROOM_LOWER_CHEST]                 = ItemLocation::Chest      (RC_JABU_JABUS_BELLY_MQ_SECOND_ROOM_LOWER_CHEST,                  0x02, 0x02, "Jabu Jabus Belly MQ Second Room Lower Chest",        JABU_JABUS_BELLY_MQ_SECOND_ROOM_LOWER_CHEST,      DEKU_NUTS_5,              {},                                                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_JABUJABUS_BELLY);
    locationTable[JABU_JABUS_BELLY_MQ_COMPASS_CHEST]                           = ItemLocation::Chest      (RC_JABU_JABUS_BELLY_MQ_COMPASS_CHEST,                            0x02, 0x00, "Jabu Jabus Belly MQ Compass Chest",                  JABU_JABUS_BELLY_MQ_COMPASS_CHEST,                JABU_JABUS_BELLY_COMPASS, {Category::cVanillaCompass},                                                 SpoilerCollectionCheckGroup::GROUP_DUNGEON_JABUJABUS_BELLY);
    locationTable[JABU_JABUS_BELLY_MQ_SECOND_ROOM_UPPER_CHEST]                 = ItemLocation::Chest      (RC_JABU_JABUS_BELLY_MQ_SECOND_ROOM_UPPER_CHEST,                  0x02, 0x07, "Jabu Jabus Belly MQ Second Room Upper Chest",        JABU_JABUS_BELLY_MQ_SECOND_ROOM_UPPER_CHEST,      RECOVERY_HEART,           {},                                                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_JABUJABUS_BELLY);
    locationTable[JABU_JABUS_BELLY_MQ_BASEMENT_NEAR_SWITCHES_CHEST]            = ItemLocation::Chest      (RC_JABU_JABUS_BELLY_MQ_BASEMENT_NEAR_SWITCHES_CHEST,             0x02, 0x08, "Jabu Jabus Belly MQ Basement Near Switches Chest",   JABU_JABUS_BELLY_MQ_BASEMENT_NEAR_SWITCHES_CHEST, DEKU_NUTS_5,              {},                                                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_JABUJABUS_BELLY);
    locationTable[JABU_JABUS_BELLY_MQ_BASEMENT_NEAR_VINES_CHEST]               = ItemLocation::Chest      (RC_JABU_JABUS_BELLY_MQ_BASEMENT_NEAR_VINES_CHEST,                0x02, 0x04, "Jabu Jabus Belly MQ Basement Near Vines Chest",      JABU_JABUS_BELLY_MQ_BASEMENT_NEAR_VINES_CHEST,    BOMBCHU_10,               {},                                                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_JABUJABUS_BELLY);
    locationTable[JABU_JABUS_BELLY_MQ_NEAR_BOSS_CHEST]                         = ItemLocation::Chest      (RC_JABU_JABUS_BELLY_MQ_NEAR_BOSS_CHEST,                          0x02, 0x0A, "Jabu Jabus Belly MQ Near Boss Chest",                JABU_JABUS_BELLY_MQ_NEAR_BOSS_CHEST,              DEKU_SHIELD,              {},                                                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_JABUJABUS_BELLY);
    locationTable[JABU_JABUS_BELLY_MQ_FALLING_LIKE_LIKE_ROOM_CHEST]            = ItemLocation::Chest      (RC_JABU_JABUS_BELLY_MQ_FALLING_LIKE_LIKE_ROOM_CHEST,             0x02, 0x09, "Jabu Jabus Belly MQ Falling Like Like Room Chest",   JABU_JABUS_BELLY_MQ_FALLING_LIKE_LIKE_ROOM_CHEST, DEKU_STICK_1,             {},                                                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_JABUJABUS_BELLY);
    locationTable[JABU_JABUS_BELLY_MQ_BOOMERANG_ROOM_SMALL_CHEST]              = ItemLocation::Chest      (RC_JABU_JABUS_BELLY_MQ_BOOMERANG_ROOM_SMALL_CHEST,               0x02, 0x01, "Jabu Jabus Belly MQ Boomerang Room Small Chest",     JABU_JABUS_BELLY_MQ_BOOMERANG_ROOM_SMALL_CHEST,   DEKU_NUTS_5,              {},                                                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_JABUJABUS_BELLY);
    locationTable[JABU_JABUS_BELLY_MQ_BOOMERANG_CHEST]                         = ItemLocation::Chest      (RC_JABU_JABUS_BELLY_MQ_BOOMERANG_CHEST,                          0x02, 0x06, "Jabu Jabus Belly MQ Boomerang Chest",                JABU_JABUS_BELLY_MQ_BOOMERANG_CHEST,              BOOMERANG,                {},                                                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_JABUJABUS_BELLY);
    //COW

    //Forest Temple Vanilla
    locationTable[FOREST_TEMPLE_FIRST_ROOM_CHEST]                              = ItemLocation::Chest      (RC_FOREST_TEMPLE_FIRST_ROOM_CHEST,                               0x03, 0x03, "Forest Temple First Room Chest",                       FOREST_TEMPLE_FIRST_ROOM_CHEST,                        FOREST_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_FOREST_TEMPLE);
    locationTable[FOREST_TEMPLE_FIRST_STALFOS_CHEST]                           = ItemLocation::Chest      (RC_FOREST_TEMPLE_FIRST_STALFOS_CHEST,                            0x03, 0x00, "Forest Temple First Stalfos Chest",                    FOREST_TEMPLE_FIRST_STALFOS_CHEST,                     FOREST_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_FOREST_TEMPLE);
    locationTable[FOREST_TEMPLE_RAISED_ISLAND_COURTYARD_CHEST]                 = ItemLocation::Chest      (RC_FOREST_TEMPLE_RAISED_ISLAND_COURTYARD_CHEST,                  0x03, 0x05, "Forest Temple Raised Island Courtyard Chest",          FOREST_TEMPLE_RAISED_ISLAND_COURTYARD_CHEST,           RECOVERY_HEART,          {},                                                                    SpoilerCollectionCheckGroup::GROUP_DUNGEON_FOREST_TEMPLE);
    locationTable[FOREST_TEMPLE_MAP_CHEST]                                     = ItemLocation::Chest      (RC_FOREST_TEMPLE_MAP_CHEST,                                      0x03, 0x01, "Forest Temple Map Chest",                              FOREST_TEMPLE_MAP_CHEST,                               FOREST_TEMPLE_MAP,       {Category::cVanillaMap},                                               SpoilerCollectionCheckGroup::GROUP_DUNGEON_FOREST_TEMPLE);
    locationTable[FOREST_TEMPLE_WELL_CHEST]                                    = ItemLocation::Chest      (RC_FOREST_TEMPLE_WELL_CHEST,                                     0x03, 0x09, "Forest Temple Well Chest",                             FOREST_TEMPLE_WELL_CHEST,                              FOREST_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_FOREST_TEMPLE);
    locationTable[FOREST_TEMPLE_FALLING_CEILING_ROOM_CHEST]                    = ItemLocation::Chest      (RC_FOREST_TEMPLE_FALLING_CEILING_ROOM_CHEST,                     0x03, 0x07, "Forest Temple Falling Ceiling Room Chest",             FOREST_TEMPLE_FALLING_CEILING_ROOM_CHEST,              ARROWS_10,               {},                                                                    SpoilerCollectionCheckGroup::GROUP_DUNGEON_FOREST_TEMPLE);
    locationTable[FOREST_TEMPLE_EYE_SWITCH_CHEST]                              = ItemLocation::Chest      (RC_FOREST_TEMPLE_EYE_SWITCH_CHEST,                               0x03, 0x04, "Forest Temple Eye Switch Chest",                       FOREST_TEMPLE_EYE_SWITCH_CHEST,                        ARROWS_30,               {},                                                                    SpoilerCollectionCheckGroup::GROUP_DUNGEON_FOREST_TEMPLE);
    locationTable[FOREST_TEMPLE_BOSS_KEY_CHEST]                                = ItemLocation::Chest      (RC_FOREST_TEMPLE_BOSS_KEY_CHEST,                                 0x03, 0x0E, "Forest Temple Boss Key Chest",                         FOREST_TEMPLE_BOSS_KEY_CHEST,                          FOREST_TEMPLE_BOSS_KEY,  {Category::cVanillaBossKey},                                           SpoilerCollectionCheckGroup::GROUP_DUNGEON_FOREST_TEMPLE);
    locationTable[FOREST_TEMPLE_FLOORMASTER_CHEST]                             = ItemLocation::Chest      (RC_FOREST_TEMPLE_FLOORMASTER_CHEST,                              0x03, 0x02, "Forest Temple Floormaster Chest",                      FOREST_TEMPLE_FLOORMASTER_CHEST,                       FOREST_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_FOREST_TEMPLE);
    locationTable[FOREST_TEMPLE_BOW_CHEST]                                     = ItemLocation::Chest      (RC_FOREST_TEMPLE_BOW_CHEST,                                      0x03, 0x0C, "Forest Temple Bow Chest",                              FOREST_TEMPLE_BOW_CHEST,                               PROGRESSIVE_BOW,         {},                                                                    SpoilerCollectionCheckGroup::GROUP_DUNGEON_FOREST_TEMPLE);
    locationTable[FOREST_TEMPLE_RED_POE_CHEST]                                 = ItemLocation::Chest      (RC_FOREST_TEMPLE_RED_POE_CHEST,                                  0x03, 0x0D, "Forest Temple Red Poe Chest",                          FOREST_TEMPLE_RED_POE_CHEST,                           FOREST_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_FOREST_TEMPLE);
    locationTable[FOREST_TEMPLE_BLUE_POE_CHEST]                                = ItemLocation::Chest      (RC_FOREST_TEMPLE_BLUE_POE_CHEST,                                 0x03, 0x0F, "Forest Temple Blue Poe Chest",                         FOREST_TEMPLE_BLUE_POE_CHEST,                          FOREST_TEMPLE_COMPASS,   {Category::cVanillaCompass},                                           SpoilerCollectionCheckGroup::GROUP_DUNGEON_FOREST_TEMPLE);
    locationTable[FOREST_TEMPLE_BASEMENT_CHEST]                                = ItemLocation::Chest      (RC_FOREST_TEMPLE_BASEMENT_CHEST,                                 0x03, 0x0B, "Forest Temple Basement Chest",                         FOREST_TEMPLE_BASEMENT_CHEST,                          ARROWS_5,                {},                                                                    SpoilerCollectionCheckGroup::GROUP_DUNGEON_FOREST_TEMPLE);
    //Forest Temple MQ
    locationTable[FOREST_TEMPLE_MQ_FIRST_ROOM_CHEST]                           = ItemLocation::Chest      (RC_FOREST_TEMPLE_MQ_FIRST_ROOM_CHEST,                            0x03, 0x03, "Forest Temple MQ First Room Chest",                    FOREST_TEMPLE_MQ_FIRST_ROOM_CHEST,                     FOREST_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_FOREST_TEMPLE);
    locationTable[FOREST_TEMPLE_MQ_WOLFOS_CHEST]                               = ItemLocation::Chest      (RC_FOREST_TEMPLE_MQ_WOLFOS_CHEST,                                0x03, 0x00, "Forest Temple MQ Wolfos Chest",                        FOREST_TEMPLE_MQ_WOLFOS_CHEST,                         FOREST_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_FOREST_TEMPLE);
    locationTable[FOREST_TEMPLE_MQ_BOW_CHEST]                                  = ItemLocation::Chest      (RC_FOREST_TEMPLE_MQ_BOW_CHEST,                                   0x03, 0x0C, "Forest Temple MQ Bow Chest",                           FOREST_TEMPLE_MQ_BOW_CHEST,                            PROGRESSIVE_BOW,         {},                                                                    SpoilerCollectionCheckGroup::GROUP_DUNGEON_FOREST_TEMPLE);
    locationTable[FOREST_TEMPLE_MQ_RAISED_ISLAND_COURTYARD_LOWER_CHEST]        = ItemLocation::Chest      (RC_FOREST_TEMPLE_MQ_RAISED_ISLAND_COURTYARD_LOWER_CHEST,         0x03, 0x01, "Forest Temple MQ Raised Island Courtyard Lower Chest", FOREST_TEMPLE_MQ_RAISED_ISLAND_COURTYARD_LOWER_CHEST,  FOREST_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_FOREST_TEMPLE);
    locationTable[FOREST_TEMPLE_MQ_RAISED_ISLAND_COURTYARD_UPPER_CHEST]        = ItemLocation::Chest      (RC_FOREST_TEMPLE_MQ_RAISED_ISLAND_COURTYARD_UPPER_CHEST,         0x03, 0x05, "Forest Temple MQ Raised Island Courtyard Upper Chest", FOREST_TEMPLE_MQ_RAISED_ISLAND_COURTYARD_UPPER_CHEST,  FOREST_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_FOREST_TEMPLE);
    locationTable[FOREST_TEMPLE_MQ_WELL_CHEST]                                 = ItemLocation::Chest      (RC_FOREST_TEMPLE_MQ_WELL_CHEST,                                  0x03, 0x09, "Forest Temple MQ Well Chest",                          FOREST_TEMPLE_MQ_WELL_CHEST,                           FOREST_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_FOREST_TEMPLE);
    locationTable[FOREST_TEMPLE_MQ_MAP_CHEST]                                  = ItemLocation::Chest      (RC_FOREST_TEMPLE_MQ_MAP_CHEST,                                   0x03, 0x0D, "Forest Temple MQ Map Chest",                           FOREST_TEMPLE_MQ_MAP_CHEST,                            FOREST_TEMPLE_MAP,       {Category::cVanillaMap},                                               SpoilerCollectionCheckGroup::GROUP_DUNGEON_FOREST_TEMPLE);
    locationTable[FOREST_TEMPLE_MQ_COMPASS_CHEST]                              = ItemLocation::Chest      (RC_FOREST_TEMPLE_MQ_COMPASS_CHEST,                               0x03, 0x0F, "Forest Temple MQ Compass Chest",                       FOREST_TEMPLE_MQ_COMPASS_CHEST,                        FOREST_TEMPLE_COMPASS,   {Category::cVanillaCompass},                                           SpoilerCollectionCheckGroup::GROUP_DUNGEON_FOREST_TEMPLE);
    locationTable[FOREST_TEMPLE_MQ_FALLING_CEILING_ROOM_CHEST]                 = ItemLocation::Chest      (RC_FOREST_TEMPLE_MQ_FALLING_CEILING_ROOM_CHEST,                  0x03, 0x06, "Forest Temple MQ Falling Ceiling Room Chest",          FOREST_TEMPLE_MQ_FALLING_CEILING_ROOM_CHEST,           ARROWS_5,                {},                                                                    SpoilerCollectionCheckGroup::GROUP_DUNGEON_FOREST_TEMPLE);
    locationTable[FOREST_TEMPLE_MQ_BASEMENT_CHEST]                             = ItemLocation::Chest      (RC_FOREST_TEMPLE_MQ_BASEMENT_CHEST,                              0x03, 0x0B, "Forest Temple MQ Basement Chest",                      FOREST_TEMPLE_MQ_BASEMENT_CHEST,                       ARROWS_5,                {},                                                                    SpoilerCollectionCheckGroup::GROUP_DUNGEON_FOREST_TEMPLE);
    locationTable[FOREST_TEMPLE_MQ_REDEAD_CHEST]                               = ItemLocation::Chest      (RC_FOREST_TEMPLE_MQ_REDEAD_CHEST,                                0x03, 0x02, "Forest Temple MQ Redead Chest",                        FOREST_TEMPLE_MQ_REDEAD_CHEST,                         FOREST_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_FOREST_TEMPLE);
    locationTable[FOREST_TEMPLE_MQ_BOSS_KEY_CHEST]                             = ItemLocation::Chest      (RC_FOREST_TEMPLE_MQ_BOSS_KEY_CHEST,                              0x03, 0x0E, "Forest Temple MQ Boss Key Chest",                      FOREST_TEMPLE_MQ_BOSS_KEY_CHEST,                       FOREST_TEMPLE_BOSS_KEY,  {Category::cVanillaBossKey},                                           SpoilerCollectionCheckGroup::GROUP_DUNGEON_FOREST_TEMPLE);

    //Fire Temple Vanilla
    locationTable[FIRE_TEMPLE_NEAR_BOSS_CHEST]                                 = ItemLocation::Chest      (RC_FIRE_TEMPLE_NEAR_BOSS_CHEST,                                  0x04, 0x01, "Fire Temple Near Boss Chest",                        FIRE_TEMPLE_NEAR_BOSS_CHEST,                     FIRE_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                    SpoilerCollectionCheckGroup::GROUP_DUNGEON_FIRE_TEMPLE);
    locationTable[FIRE_TEMPLE_FLARE_DANCER_CHEST]                              = ItemLocation::Chest      (RC_FIRE_TEMPLE_FLARE_DANCER_CHEST,                               0x04, 0x00, "Fire Temple Flare Dancer Chest",                     FIRE_TEMPLE_FLARE_DANCER_CHEST,                  BOMBS_10,              {},                                                                              SpoilerCollectionCheckGroup::GROUP_DUNGEON_FIRE_TEMPLE);
    locationTable[FIRE_TEMPLE_BOSS_KEY_CHEST]                                  = ItemLocation::Chest      (RC_FIRE_TEMPLE_BOSS_KEY_CHEST,                                   0x04, 0x0C, "Fire Temple Boss Key Chest",                         FIRE_TEMPLE_BOSS_KEY_CHEST,                      FIRE_TEMPLE_BOSS_KEY,  {Category::cVanillaBossKey},                                                     SpoilerCollectionCheckGroup::GROUP_DUNGEON_FIRE_TEMPLE);
    locationTable[FIRE_TEMPLE_BIG_LAVA_ROOM_BLOCKED_DOOR_CHEST]                = ItemLocation::Chest      (RC_FIRE_TEMPLE_BIG_LAVA_ROOM_BLOCKED_DOOR_CHEST,                 0x04, 0x02, "Fire Temple Big Lava Room Blocked Door Chest",       FIRE_TEMPLE_BIG_LAVA_ROOM_BLOCKED_DOOR_CHEST,    FIRE_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                    SpoilerCollectionCheckGroup::GROUP_DUNGEON_FIRE_TEMPLE);
    locationTable[FIRE_TEMPLE_BIG_LAVA_ROOM_LOWER_OPEN_DOOR_CHEST]             = ItemLocation::Chest      (RC_FIRE_TEMPLE_BIG_LAVA_ROOM_LOWER_OPEN_DOOR_CHEST,              0x04, 0x04, "Fire Temple Big Lava Room Lower Open Door Chest",    FIRE_TEMPLE_BIG_LAVA_ROOM_LOWER_OPEN_DOOR_CHEST, FIRE_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                    SpoilerCollectionCheckGroup::GROUP_DUNGEON_FIRE_TEMPLE);
    locationTable[FIRE_TEMPLE_BOULDER_MAZE_LOWER_CHEST]                        = ItemLocation::Chest      (RC_FIRE_TEMPLE_BOULDER_MAZE_LOWER_CHEST,                         0x04, 0x03, "Fire Temple Boulder Maze Lower Chest",               FIRE_TEMPLE_BOULDER_MAZE_LOWER_CHEST,            FIRE_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                    SpoilerCollectionCheckGroup::GROUP_DUNGEON_FIRE_TEMPLE);
    locationTable[FIRE_TEMPLE_BOULDER_MAZE_UPPER_CHEST]                        = ItemLocation::Chest      (RC_FIRE_TEMPLE_BOULDER_MAZE_UPPER_CHEST,                         0x04, 0x06, "Fire Temple Boulder Maze Upper Chest",               FIRE_TEMPLE_BOULDER_MAZE_UPPER_CHEST,            FIRE_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                    SpoilerCollectionCheckGroup::GROUP_DUNGEON_FIRE_TEMPLE);
    locationTable[FIRE_TEMPLE_BOULDER_MAZE_SIDE_ROOM_CHEST]                    = ItemLocation::Chest      (RC_FIRE_TEMPLE_BOULDER_MAZE_SIDE_ROOM_CHEST,                     0x04, 0x08, "Fire Temple Boulder Maze Side Room Chest",           FIRE_TEMPLE_BOULDER_MAZE_SIDE_ROOM_CHEST,        FIRE_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                    SpoilerCollectionCheckGroup::GROUP_DUNGEON_FIRE_TEMPLE);
    locationTable[FIRE_TEMPLE_BOULDER_MAZE_SHORTCUT_CHEST]                     = ItemLocation::Chest      (RC_FIRE_TEMPLE_BOULDER_MAZE_SHORTCUT_CHEST,                      0x04, 0x0B, "Fire Temple Boulder Maze Shortcut Chest",            FIRE_TEMPLE_BOULDER_MAZE_SHORTCUT_CHEST,         FIRE_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                    SpoilerCollectionCheckGroup::GROUP_DUNGEON_FIRE_TEMPLE);
    locationTable[FIRE_TEMPLE_SCARECROW_CHEST]                                 = ItemLocation::Chest      (RC_FIRE_TEMPLE_SCARECROW_CHEST,                                  0x04, 0x0D, "Fire Temple Scarecrow Chest",                        FIRE_TEMPLE_SCARECROW_CHEST,                     HUGE_RUPEE,            {},                                                                              SpoilerCollectionCheckGroup::GROUP_DUNGEON_FIRE_TEMPLE);
    locationTable[FIRE_TEMPLE_MAP_CHEST]                                       = ItemLocation::Chest      (RC_FIRE_TEMPLE_MAP_CHEST,                                        0x04, 0x0A, "Fire Temple Map Chest",                              FIRE_TEMPLE_MAP_CHEST,                           FIRE_TEMPLE_MAP,       {Category::cVanillaMap},                                                         SpoilerCollectionCheckGroup::GROUP_DUNGEON_FIRE_TEMPLE);
    locationTable[FIRE_TEMPLE_COMPASS_CHEST]                                   = ItemLocation::Chest      (RC_FIRE_TEMPLE_COMPASS_CHEST,                                    0x04, 0x07, "Fire Temple Compass Chest",                          FIRE_TEMPLE_COMPASS_CHEST,                       FIRE_TEMPLE_COMPASS,   {Category::cVanillaCompass},                                                     SpoilerCollectionCheckGroup::GROUP_DUNGEON_FIRE_TEMPLE);
    locationTable[FIRE_TEMPLE_HIGHEST_GORON_CHEST]                             = ItemLocation::Chest      (RC_FIRE_TEMPLE_HIGHEST_GORON_CHEST,                              0x04, 0x09, "Fire Temple Highest Goron Chest",                    FIRE_TEMPLE_HIGHEST_GORON_CHEST,                 FIRE_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                    SpoilerCollectionCheckGroup::GROUP_DUNGEON_FIRE_TEMPLE);
    locationTable[FIRE_TEMPLE_MEGATON_HAMMER_CHEST]                            = ItemLocation::Chest      (RC_FIRE_TEMPLE_MEGATON_HAMMER_CHEST,                             0x04, 0x05, "Fire Temple Megaton Hammer Chest",                   FIRE_TEMPLE_MEGATON_HAMMER_CHEST,                MEGATON_HAMMER,        {},                                                                              SpoilerCollectionCheckGroup::GROUP_DUNGEON_FIRE_TEMPLE);
    //Fire Temple MQ
    locationTable[FIRE_TEMPLE_MQ_NEAR_BOSS_CHEST]                              = ItemLocation::Chest      (RC_FIRE_TEMPLE_MQ_NEAR_BOSS_CHEST,                               0x04, 0x07, "Fire Temple MQ Near Boss Chest",                     FIRE_TEMPLE_MQ_NEAR_BOSS_CHEST,                  FIRE_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                    SpoilerCollectionCheckGroup::GROUP_DUNGEON_FIRE_TEMPLE);
    locationTable[FIRE_TEMPLE_MQ_MEGATON_HAMMER_CHEST]                         = ItemLocation::Chest      (RC_FIRE_TEMPLE_MQ_MEGATON_HAMMER_CHEST,                          0x04, 0x00, "Fire Temple MQ Megaton Hammer Chest",                FIRE_TEMPLE_MQ_MEGATON_HAMMER_CHEST,             MEGATON_HAMMER,        {},                                                                              SpoilerCollectionCheckGroup::GROUP_DUNGEON_FIRE_TEMPLE);
    locationTable[FIRE_TEMPLE_MQ_COMPASS_CHEST]                                = ItemLocation::Chest      (RC_FIRE_TEMPLE_MQ_COMPASS_CHEST,                                 0x04, 0x0B, "Fire Temple MQ Compass Chest",                       FIRE_TEMPLE_MQ_COMPASS_CHEST,                    FIRE_TEMPLE_COMPASS,   {Category::cVanillaCompass},                                                     SpoilerCollectionCheckGroup::GROUP_DUNGEON_FIRE_TEMPLE);
    locationTable[FIRE_TEMPLE_MQ_LIZALFOS_MAZE_LOWER_CHEST]                    = ItemLocation::Chest      (RC_FIRE_TEMPLE_MQ_LIZALFOS_MAZE_LOWER_CHEST,                     0x04, 0x03, "Fire Temple MQ Lizalfos Maze Lower Chest",           FIRE_TEMPLE_MQ_LIZALFOS_MAZE_LOWER_CHEST,        BOMBS_10,              {},                                                                              SpoilerCollectionCheckGroup::GROUP_DUNGEON_FIRE_TEMPLE);
    locationTable[FIRE_TEMPLE_MQ_LIZALFOS_MAZE_UPPER_CHEST]                    = ItemLocation::Chest      (RC_FIRE_TEMPLE_MQ_LIZALFOS_MAZE_UPPER_CHEST,                     0x04, 0x06, "Fire Temple MQ Lizalfos Maze Upper Chest",           FIRE_TEMPLE_MQ_LIZALFOS_MAZE_UPPER_CHEST,        BOMBS_10,              {},                                                                              SpoilerCollectionCheckGroup::GROUP_DUNGEON_FIRE_TEMPLE);
    locationTable[FIRE_TEMPLE_MQ_CHEST_ON_FIRE]                                = ItemLocation::Chest      (RC_FIRE_TEMPLE_MQ_CHEST_ON_FIRE,                                 0x04, 0x05, "Fire Temple MQ Chest on Fire",                       FIRE_TEMPLE_MQ_CHEST_ON_FIRE,                    FIRE_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                    SpoilerCollectionCheckGroup::GROUP_DUNGEON_FIRE_TEMPLE);
    locationTable[FIRE_TEMPLE_MQ_MAP_ROOM_SIDE_CHEST]                          = ItemLocation::Chest      (RC_FIRE_TEMPLE_MQ_MAP_ROOM_SIDE_CHEST,                           0x04, 0x02, "Fire Temple MQ Map Room Side Chest",                 FIRE_TEMPLE_MQ_MAP_ROOM_SIDE_CHEST,              HYLIAN_SHIELD,         {},                                                                              SpoilerCollectionCheckGroup::GROUP_DUNGEON_FIRE_TEMPLE);
    locationTable[FIRE_TEMPLE_MQ_MAP_CHEST]                                    = ItemLocation::Chest      (RC_FIRE_TEMPLE_MQ_MAP_CHEST,                                     0x04, 0x0C, "Fire Temple MQ Map Chest",                           FIRE_TEMPLE_MQ_MAP_CHEST,                        FIRE_TEMPLE_MAP,       {Category::cVanillaMap},                                                         SpoilerCollectionCheckGroup::GROUP_DUNGEON_FIRE_TEMPLE);
    locationTable[FIRE_TEMPLE_MQ_BOSS_KEY_CHEST]                               = ItemLocation::Chest      (RC_FIRE_TEMPLE_MQ_BOSS_KEY_CHEST,                                0x04, 0x04, "Fire Temple MQ Boss Key Chest",                      FIRE_TEMPLE_MQ_BOSS_KEY_CHEST,                   FIRE_TEMPLE_BOSS_KEY,  {Category::cVanillaBossKey},                                                     SpoilerCollectionCheckGroup::GROUP_DUNGEON_FIRE_TEMPLE);
    locationTable[FIRE_TEMPLE_MQ_BIG_LAVA_ROOM_BLOCKED_DOOR_CHEST]             = ItemLocation::Chest      (RC_FIRE_TEMPLE_MQ_BIG_LAVA_ROOM_BLOCKED_DOOR_CHEST,              0x04, 0x01, "Fire Temple MQ Big Lava Room Blocked Door Chest",    FIRE_TEMPLE_MQ_BIG_LAVA_ROOM_BLOCKED_DOOR_CHEST, FIRE_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                    SpoilerCollectionCheckGroup::GROUP_DUNGEON_FIRE_TEMPLE);
    locationTable[FIRE_TEMPLE_MQ_LIZALFOS_MAZE_SIDE_ROOM_CHEST]                = ItemLocation::Chest      (RC_FIRE_TEMPLE_MQ_LIZALFOS_MAZE_SIDE_ROOM_CHEST,                 0x04, 0x08, "Fire Temple MQ Lizalfos Maze Side Room Chest",       FIRE_TEMPLE_MQ_LIZALFOS_MAZE_SIDE_ROOM_CHEST,    FIRE_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                    SpoilerCollectionCheckGroup::GROUP_DUNGEON_FIRE_TEMPLE);
    locationTable[FIRE_TEMPLE_MQ_FREESTANDING_KEY]                             = ItemLocation::Collectable(RC_FIRE_TEMPLE_MQ_FREESTANDING_KEY,                              0x04, 0x1C, "Fire Temple MQ Freestanding Key",                    FIRE_TEMPLE_MQ_FREESTANDING_KEY,                 FIRE_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                    SpoilerCollectionCheckGroup::GROUP_DUNGEON_FIRE_TEMPLE);

    //Water Temple Vanilla
    locationTable[WATER_TEMPLE_MAP_CHEST]                                      = ItemLocation::Chest      (RC_WATER_TEMPLE_MAP_CHEST,                                       0x05, 0x02, "Water Temple Map Chest",                             WATER_TEMPLE_MAP_CHEST,                          WATER_TEMPLE_MAP,       {Category::cVanillaMap},                                                        SpoilerCollectionCheckGroup::GROUP_DUNGEON_WATER_TEMPLE);
    locationTable[WATER_TEMPLE_COMPASS_CHEST]                                  = ItemLocation::Chest      (RC_WATER_TEMPLE_COMPASS_CHEST,                                   0x05, 0x09, "Water Temple Compass Chest",                         WATER_TEMPLE_COMPASS_CHEST,                      WATER_TEMPLE_COMPASS,   {Category::cVanillaCompass},                                                    SpoilerCollectionCheckGroup::GROUP_DUNGEON_WATER_TEMPLE);
    locationTable[WATER_TEMPLE_TORCHES_CHEST]                                  = ItemLocation::Chest      (RC_WATER_TEMPLE_TORCHES_CHEST,                                   0x05, 0x01, "Water Temple Torches Chest",                         WATER_TEMPLE_TORCHES_CHEST,                      WATER_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_WATER_TEMPLE);
    locationTable[WATER_TEMPLE_DRAGON_CHEST]                                   = ItemLocation::Chest      (RC_WATER_TEMPLE_DRAGON_CHEST,                                    0x05, 0x0A, "Water Temple Dragon Chest",                          WATER_TEMPLE_DRAGON_CHEST,                       WATER_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_WATER_TEMPLE);
    locationTable[WATER_TEMPLE_CENTRAL_BOW_TARGET_CHEST]                       = ItemLocation::Chest      (RC_WATER_TEMPLE_CENTRAL_BOW_TARGET_CHEST,                        0x05, 0x08, "Water Temple Central Bow Target Chest",              WATER_TEMPLE_CENTRAL_BOW_TARGET_CHEST,           WATER_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_WATER_TEMPLE);
    locationTable[WATER_TEMPLE_CENTRAL_PILLAR_CHEST]                           = ItemLocation::Chest      (RC_WATER_TEMPLE_CENTRAL_PILLAR_CHEST,                            0x05, 0x06, "Water Temple Central Pillar Chest",                  WATER_TEMPLE_CENTRAL_PILLAR_CHEST,               WATER_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_WATER_TEMPLE);
    locationTable[WATER_TEMPLE_CRACKED_WALL_CHEST]                             = ItemLocation::Chest      (RC_WATER_TEMPLE_CRACKED_WALL_CHEST,                              0x05, 0x00, "Water Temple Cracked Wall Chest",                    WATER_TEMPLE_CRACKED_WALL_CHEST,                 WATER_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_WATER_TEMPLE);
    locationTable[WATER_TEMPLE_BOSS_KEY_CHEST]                                 = ItemLocation::Chest      (RC_WATER_TEMPLE_BOSS_KEY_CHEST,                                  0x05, 0x05, "Water Temple Boss Key Chest",                        WATER_TEMPLE_BOSS_KEY_CHEST,                     WATER_TEMPLE_BOSS_KEY,  {Category::cVanillaBossKey},                                                    SpoilerCollectionCheckGroup::GROUP_DUNGEON_WATER_TEMPLE);
    locationTable[WATER_TEMPLE_LONGSHOT_CHEST]                                 = ItemLocation::Chest      (RC_WATER_TEMPLE_LONGSHOT_CHEST,                                  0x05, 0x07, "Water Temple Longshot Chest",                        WATER_TEMPLE_LONGSHOT_CHEST,                     PROGRESSIVE_HOOKSHOT,   {},                                                                             SpoilerCollectionCheckGroup::GROUP_DUNGEON_WATER_TEMPLE);
    locationTable[WATER_TEMPLE_RIVER_CHEST]                                    = ItemLocation::Chest      (RC_WATER_TEMPLE_RIVER_CHEST,                                     0x05, 0x03, "Water Temple River Chest",                           WATER_TEMPLE_RIVER_CHEST,                        WATER_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_WATER_TEMPLE);
    //Water Temple MQ
    locationTable[WATER_TEMPLE_MQ_CENTRAL_PILLAR_CHEST]                        = ItemLocation::Chest      (RC_WATER_TEMPLE_MQ_CENTRAL_PILLAR_CHEST,                         0x05, 0x06, "Water Temple MQ Central Pillar Chest",               WATER_TEMPLE_MQ_CENTRAL_PILLAR_CHEST,            WATER_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_WATER_TEMPLE);
    locationTable[WATER_TEMPLE_MQ_BOSS_KEY_CHEST]                              = ItemLocation::Chest      (RC_WATER_TEMPLE_MQ_BOSS_KEY_CHEST,                               0x05, 0x05, "Water Temple MQ Boss Key Chest",                     WATER_TEMPLE_MQ_BOSS_KEY_CHEST,                  WATER_TEMPLE_BOSS_KEY,  {Category::cVanillaBossKey},                                                    SpoilerCollectionCheckGroup::GROUP_DUNGEON_WATER_TEMPLE);
    locationTable[WATER_TEMPLE_MQ_LONGSHOT_CHEST]                              = ItemLocation::Chest      (RC_WATER_TEMPLE_MQ_LONGSHOT_CHEST,                               0x05, 0x00, "Water Temple MQ Longshot Chest",                     WATER_TEMPLE_MQ_LONGSHOT_CHEST,                  PROGRESSIVE_HOOKSHOT,   {},                                                                             SpoilerCollectionCheckGroup::GROUP_DUNGEON_WATER_TEMPLE);
    locationTable[WATER_TEMPLE_MQ_COMPASS_CHEST]                               = ItemLocation::Chest      (RC_WATER_TEMPLE_MQ_COMPASS_CHEST,                                0x05, 0x01, "Water Temple MQ Compass Chest",                      WATER_TEMPLE_MQ_COMPASS_CHEST,                   WATER_TEMPLE_COMPASS,   {Category::cVanillaCompass},                                                    SpoilerCollectionCheckGroup::GROUP_DUNGEON_WATER_TEMPLE);
    locationTable[WATER_TEMPLE_MQ_MAP_CHEST]                                   = ItemLocation::Chest      (RC_WATER_TEMPLE_MQ_MAP_CHEST,                                    0x05, 0x02, "Water Temple MQ Map Chest",                          WATER_TEMPLE_MQ_MAP_CHEST,                       WATER_TEMPLE_MAP,       {Category::cVanillaMap},                                                        SpoilerCollectionCheckGroup::GROUP_DUNGEON_WATER_TEMPLE);
    locationTable[WATER_TEMPLE_MQ_FREESTANDING_KEY]                            = ItemLocation::Collectable(RC_WATER_TEMPLE_MQ_FREESTANDING_KEY,                             0x05, 0x01, "Water Temple MQ Freestanding Key",                   WATER_TEMPLE_MQ_FREESTANDING_KEY,                WATER_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_WATER_TEMPLE);

    //Spirit Temple Shared
    locationTable[SPIRIT_TEMPLE_SILVER_GAUNTLETS_CHEST]                        = ItemLocation::Chest      (RC_SPIRIT_TEMPLE_SILVER_GAUNTLETS_CHEST,                         0x5C, 0x0B, "Spirit Temple Silver Gauntlets Chest",               SPIRIT_TEMPLE_SILVER_GAUNTLETS_CHEST,           PROGRESSIVE_STRENGTH,    {},                                                                             SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_MIRROR_SHIELD_CHEST]                           = ItemLocation::Chest      (RC_SPIRIT_TEMPLE_MIRROR_SHIELD_CHEST,                            0x5C, 0x09, "Spirit Temple Mirror Shield Chest",                  SPIRIT_TEMPLE_MIRROR_SHIELD_CHEST,              MIRROR_SHIELD,           {},                                                                             SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    //Spirit Temple Vanilla
    locationTable[SPIRIT_TEMPLE_CHILD_BRIDGE_CHEST]                            = ItemLocation::Chest      (RC_SPIRIT_TEMPLE_CHILD_BRIDGE_CHEST,                             0x06, 0x08, "Spirit Temple Child Bridge Chest",                   SPIRIT_TEMPLE_CHILD_BRIDGE_CHEST,               DEKU_SHIELD,             {},                                                                             SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_CHILD_EARLY_TORCHES_CHEST]                     = ItemLocation::Chest      (RC_SPIRIT_TEMPLE_CHILD_EARLY_TORCHES_CHEST,                      0x06, 0x00, "Spirit Temple Child Early Torches Chest",            SPIRIT_TEMPLE_CHILD_EARLY_TORCHES_CHEST,        SPIRIT_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_COMPASS_CHEST]                                 = ItemLocation::Chest      (RC_SPIRIT_TEMPLE_COMPASS_CHEST,                                  0x06, 0x04, "Spirit Temple Compass Chest",                        SPIRIT_TEMPLE_COMPASS_CHEST,                    SPIRIT_TEMPLE_COMPASS,   {Category::cVanillaCompass},                                                    SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_EARLY_ADULT_RIGHT_CHEST]                       = ItemLocation::Chest      (RC_SPIRIT_TEMPLE_EARLY_ADULT_RIGHT_CHEST,                        0x06, 0x07, "Spirit Temple Early Adult Right Chest",              SPIRIT_TEMPLE_EARLY_ADULT_RIGHT_CHEST,          SPIRIT_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_FIRST_MIRROR_LEFT_CHEST]                       = ItemLocation::Chest      (RC_SPIRIT_TEMPLE_FIRST_MIRROR_LEFT_CHEST,                        0x06, 0x0D, "Spirit Temple First Mirror Left Chest",              SPIRIT_TEMPLE_FIRST_MIRROR_LEFT_CHEST,          ICE_TRAP,                {},                                                                             SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_FIRST_MIRROR_RIGHT_CHEST]                      = ItemLocation::Chest      (RC_SPIRIT_TEMPLE_FIRST_MIRROR_RIGHT_CHEST,                       0x06, 0x0E, "Spirit Temple First Mirror Right Chest",             SPIRIT_TEMPLE_FIRST_MIRROR_RIGHT_CHEST,         RECOVERY_HEART,          {},                                                                             SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_MAP_CHEST]                                     = ItemLocation::Chest      (RC_SPIRIT_TEMPLE_MAP_CHEST,                                      0x06, 0x03, "Spirit Temple Map Chest",                            SPIRIT_TEMPLE_MAP_CHEST,                        SPIRIT_TEMPLE_MAP,       {Category::cVanillaMap},                                                        SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_CHILD_CLIMB_NORTH_CHEST]                       = ItemLocation::Chest      (RC_SPIRIT_TEMPLE_CHILD_CLIMB_NORTH_CHEST,                        0x06, 0x06, "Spirit Temple Child Climb North Chest",              SPIRIT_TEMPLE_CHILD_CLIMB_NORTH_CHEST,          BOMBCHU_10,              {},                                                                             SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_CHILD_CLIMB_EAST_CHEST]                        = ItemLocation::Chest      (RC_SPIRIT_TEMPLE_CHILD_CLIMB_EAST_CHEST,                         0x06, 0x0C, "Spirit Temple Child Climb East Chest",               SPIRIT_TEMPLE_CHILD_CLIMB_EAST_CHEST,           DEKU_SHIELD,             {},                                                                             SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_SUN_BLOCK_ROOM_CHEST]                          = ItemLocation::Chest      (RC_SPIRIT_TEMPLE_SUN_BLOCK_ROOM_CHEST,                           0x06, 0x01, "Spirit Temple Sun Block Room Chest",                 SPIRIT_TEMPLE_SUN_BLOCK_ROOM_CHEST,             SPIRIT_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_STATUE_ROOM_HAND_CHEST]                        = ItemLocation::Chest      (RC_SPIRIT_TEMPLE_STATUE_ROOM_HAND_CHEST,                         0x06, 0x02, "Spirit Temple Statue Room Hand Chest",               SPIRIT_TEMPLE_STATUE_ROOM_HAND_CHEST,           SPIRIT_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_STATUE_ROOM_NORTHEAST_CHEST]                   = ItemLocation::Chest      (RC_SPIRIT_TEMPLE_STATUE_ROOM_NORTHEAST_CHEST,                    0x06, 0x0F, "Spirit Temple Statue Room Northeast Chest",          SPIRIT_TEMPLE_STATUE_ROOM_NORTHEAST_CHEST,      BLUE_RUPEE,              {},                                                                             SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_NEAR_FOUR_ARMOS_CHEST]                         = ItemLocation::Chest      (RC_SPIRIT_TEMPLE_NEAR_FOUR_ARMOS_CHEST,                          0x06, 0x05, "Spirit Temple Near Four Armos Chest",                SPIRIT_TEMPLE_NEAR_FOUR_ARMOS_CHEST,            SPIRIT_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_HALLWAY_RIGHT_INVISIBLE_CHEST]                 = ItemLocation::Chest      (RC_SPIRIT_TEMPLE_HALLWAY_RIGHT_INVISIBLE_CHEST,                  0x06, 0x14, "Spirit Temple Hallway Right Invisible Chest",        SPIRIT_TEMPLE_HALLWAY_RIGHT_INVISIBLE_CHEST,    RECOVERY_HEART,          {},                                                                             SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_HALLWAY_LEFT_INVISIBLE_CHEST]                  = ItemLocation::Chest      (RC_SPIRIT_TEMPLE_HALLWAY_LEFT_INVISIBLE_CHEST,                   0x06, 0x15, "Spirit Temple Hallway Left Invisible Chest",         SPIRIT_TEMPLE_HALLWAY_LEFT_INVISIBLE_CHEST,     RECOVERY_HEART,          {},                                                                             SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_BOSS_KEY_CHEST]                                = ItemLocation::Chest      (RC_SPIRIT_TEMPLE_BOSS_KEY_CHEST,                                 0x06, 0x0A, "Spirit Temple Boss Key Chest",                       SPIRIT_TEMPLE_BOSS_KEY_CHEST,                   SPIRIT_TEMPLE_BOSS_KEY,  {Category::cVanillaBossKey},                                                    SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_TOPMOST_CHEST]                                 = ItemLocation::Chest      (RC_SPIRIT_TEMPLE_TOPMOST_CHEST,                                  0x06, 0x12, "Spirit Temple Topmost Chest",                        SPIRIT_TEMPLE_TOPMOST_CHEST,                    BOMBS_20,                {},                                                                             SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    //Spirit Temple MQ
    locationTable[SPIRIT_TEMPLE_MQ_ENTRANCE_FRONT_LEFT_CHEST]                  = ItemLocation::Chest      (RC_SPIRIT_TEMPLE_MQ_ENTRANCE_FRONT_LEFT_CHEST,                   0x06, 0x1A, "Spirit Temple MQ Entrance Front Left Chest",         SPIRIT_TEMPLE_MQ_ENTRANCE_FRONT_LEFT_CHEST,     BOMBCHU_10,              {},                                                                             SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_MQ_ENTRANCE_BACK_RIGHT_CHEST]                  = ItemLocation::Chest      (RC_SPIRIT_TEMPLE_MQ_ENTRANCE_BACK_RIGHT_CHEST,                   0x06, 0x1F, "Spirit Temple MQ Entrance Back Right Chest",         SPIRIT_TEMPLE_MQ_ENTRANCE_BACK_RIGHT_CHEST,     BOMBCHU_10,              {},                                                                             SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_MQ_ENTRANCE_FRONT_RIGHT_CHEST]                 = ItemLocation::Chest      (RC_SPIRIT_TEMPLE_MQ_ENTRANCE_FRONT_RIGHT_CHEST,                  0x06, 0x1B, "Spirit Temple MQ Entrance Front Right Chest",        SPIRIT_TEMPLE_MQ_ENTRANCE_FRONT_RIGHT_CHEST,    SPIRIT_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_MQ_ENTRANCE_BACK_LEFT_CHEST]                   = ItemLocation::Chest      (RC_SPIRIT_TEMPLE_MQ_ENTRANCE_BACK_LEFT_CHEST,                    0x06, 0x1E, "Spirit Temple MQ Entrance Back Left Chest",          SPIRIT_TEMPLE_MQ_ENTRANCE_BACK_LEFT_CHEST,      SPIRIT_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_MQ_CHILD_HAMMER_SWITCH_CHEST]                  = ItemLocation::Chest      (RC_SPIRIT_TEMPLE_MQ_CHILD_HAMMER_SWITCH_CHEST,                   0x06, 0x1D, "Spirit Temple MQ Child Hammer Switch Chest",         SPIRIT_TEMPLE_MQ_CHILD_HAMMER_SWITCH_CHEST,     SPIRIT_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_MQ_MAP_CHEST]                                  = ItemLocation::Chest      (RC_SPIRIT_TEMPLE_MQ_MAP_CHEST,                                   0x06, 0x00, "Spirit Temple MQ Map Chest",                         SPIRIT_TEMPLE_MQ_MAP_CHEST,                     SPIRIT_TEMPLE_MAP,       {Category::cVanillaMap},                                                        SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_MQ_MAP_ROOM_ENEMY_CHEST]                       = ItemLocation::Chest      (RC_SPIRIT_TEMPLE_MQ_MAP_ROOM_ENEMY_CHEST,                        0x06, 0x08, "Spirit Temple MQ Map Room Enemy Chest",              SPIRIT_TEMPLE_MQ_MAP_ROOM_ENEMY_CHEST,          SPIRIT_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_MQ_CHILD_CLIMB_NORTH_CHEST]                    = ItemLocation::Chest      (RC_SPIRIT_TEMPLE_MQ_CHILD_CLIMB_NORTH_CHEST,                     0x06, 0x06, "Spirit Temple MQ Child Climb North Chest",           SPIRIT_TEMPLE_MQ_CHILD_CLIMB_NORTH_CHEST,       BOMBCHU_10,              {},                                                                             SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_MQ_CHILD_CLIMB_SOUTH_CHEST]                    = ItemLocation::Chest      (RC_SPIRIT_TEMPLE_MQ_CHILD_CLIMB_SOUTH_CHEST,                     0x06, 0x0C, "Spirit Temple MQ Child Climb South Chest",           SPIRIT_TEMPLE_MQ_CHILD_CLIMB_SOUTH_CHEST,       SPIRIT_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_MQ_COMPASS_CHEST]                              = ItemLocation::Chest      (RC_SPIRIT_TEMPLE_MQ_COMPASS_CHEST,                               0x06, 0x03, "Spirit Temple MQ Compass Chest",                     SPIRIT_TEMPLE_MQ_COMPASS_CHEST,                 SPIRIT_TEMPLE_COMPASS,   {Category::cVanillaCompass},                                                    SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_MQ_STATUE_ROOM_LULLABY_CHEST]                  = ItemLocation::Chest      (RC_SPIRIT_TEMPLE_MQ_STATUE_ROOM_LULLABY_CHEST,                   0x06, 0x0F, "Spirit Temple MQ Statue Room Lullaby Chest",         SPIRIT_TEMPLE_MQ_STATUE_ROOM_LULLABY_CHEST,     BLUE_RUPEE,              {},                                                                             SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_MQ_STATUE_ROOM_INVISIBLE_CHEST]                = ItemLocation::Chest      (RC_SPIRIT_TEMPLE_MQ_STATUE_ROOM_INVISIBLE_CHEST,                 0x06, 0x02, "Spirit Temple MQ Statue Room Invisible Chest",       SPIRIT_TEMPLE_MQ_STATUE_ROOM_INVISIBLE_CHEST,   RECOVERY_HEART,          {},                                                                             SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_MQ_SILVER_BLOCK_HALLWAY_CHEST]                 = ItemLocation::Chest      (RC_SPIRIT_TEMPLE_MQ_SILVER_BLOCK_HALLWAY_CHEST,                  0x06, 0x1C, "Spirit Temple MQ Silver Block Hallway Chest",        SPIRIT_TEMPLE_MQ_SILVER_BLOCK_HALLWAY_CHEST,    SPIRIT_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_MQ_SUN_BLOCK_ROOM_CHEST]                       = ItemLocation::Chest      (RC_SPIRIT_TEMPLE_MQ_SUN_BLOCK_ROOM_CHEST,                        0x06, 0x01, "Spirit Temple MQ Sun Block Room Chest",              SPIRIT_TEMPLE_MQ_SUN_BLOCK_ROOM_CHEST,          RECOVERY_HEART,          {},                                                                             SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_MQ_SYMPHONY_ROOM_CHEST]                        = ItemLocation::Chest      (RC_SPIRIT_TEMPLE_MQ_SYMPHONY_ROOM_CHEST,                         0x06, 0x07, "Spirit Temple MQ Symphony Room Chest",               SPIRIT_TEMPLE_MQ_SYMPHONY_ROOM_CHEST,           PURPLE_RUPEE,            {},                                                                             SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_MQ_LEEVER_ROOM_CHEST]                          = ItemLocation::Chest      (RC_SPIRIT_TEMPLE_MQ_LEEVER_ROOM_CHEST,                           0x06, 0x04, "Spirit Temple MQ Leever Room Chest",                 SPIRIT_TEMPLE_MQ_LEEVER_ROOM_CHEST,             PURPLE_RUPEE,            {},                                                                             SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_MQ_BEAMOS_ROOM_CHEST]                          = ItemLocation::Chest      (RC_SPIRIT_TEMPLE_MQ_BEAMOS_ROOM_CHEST,                           0x06, 0x19, "Spirit Temple MQ Beamos Room Chest",                 SPIRIT_TEMPLE_MQ_BEAMOS_ROOM_CHEST,             RECOVERY_HEART,          {},                                                                             SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_MQ_CHEST_SWITCH_CHEST]                         = ItemLocation::Chest      (RC_SPIRIT_TEMPLE_MQ_CHEST_SWITCH_CHEST,                          0x06, 0x18, "Spirit Temple MQ Chest Switch Chest",                SPIRIT_TEMPLE_MQ_CHEST_SWITCH_CHEST,            ICE_TRAP,                {},                                                                             SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_MQ_BOSS_KEY_CHEST]                             = ItemLocation::Chest      (RC_SPIRIT_TEMPLE_MQ_BOSS_KEY_CHEST,                              0x06, 0x05, "Spirit Temple MQ Boss Key Chest",                    SPIRIT_TEMPLE_MQ_BOSS_KEY_CHEST,                SPIRIT_TEMPLE_BOSS_KEY,  {Category::cVanillaBossKey},                                                    SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_MQ_MIRROR_PUZZLE_INVISIBLE_CHEST]              = ItemLocation::Chest      (RC_SPIRIT_TEMPLE_MQ_MIRROR_PUZZLE_INVISIBLE_CHEST,               0x06, 0x12, "Spirit Temple MQ Mirror Puzzle Invisible Chest",     SPIRIT_TEMPLE_MQ_MIRROR_PUZZLE_INVISIBLE_CHEST, SPIRIT_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);

    //Shadow Temple Vanilla
    locationTable[SHADOW_TEMPLE_MAP_CHEST]                                     = ItemLocation::Chest      (RC_SHADOW_TEMPLE_MAP_CHEST,                                      0x07, 0x01, "Shadow Temple Map Chest",                            SHADOW_TEMPLE_MAP_CHEST,                           SHADOW_TEMPLE_MAP,       {Category::cVanillaMap},                                                     SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_HOVER_BOOTS_CHEST]                             = ItemLocation::Chest      (RC_SHADOW_TEMPLE_HOVER_BOOTS_CHEST,                              0x07, 0x07, "Shadow Temple Hover Boots Chest",                    SHADOW_TEMPLE_HOVER_BOOTS_CHEST,                   HOVER_BOOTS,             {},                                                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_COMPASS_CHEST]                                 = ItemLocation::Chest      (RC_SHADOW_TEMPLE_COMPASS_CHEST,                                  0x07, 0x03, "Shadow Temple Compass Chest",                        SHADOW_TEMPLE_COMPASS_CHEST,                       SHADOW_TEMPLE_COMPASS,   {Category::cVanillaCompass},                                                 SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_EARLY_SILVER_RUPEE_CHEST]                      = ItemLocation::Chest      (RC_SHADOW_TEMPLE_EARLY_SILVER_RUPEE_CHEST,                       0x07, 0x02, "Shadow Temple Early Silver Rupee Chest",             SHADOW_TEMPLE_EARLY_SILVER_RUPEE_CHEST,            SHADOW_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_INVISIBLE_BLADES_VISIBLE_CHEST]                = ItemLocation::Chest      (RC_SHADOW_TEMPLE_INVISIBLE_BLADES_VISIBLE_CHEST,                 0x07, 0x0C, "Shadow Temple Invisible Blades Visible Chest",       SHADOW_TEMPLE_INVISIBLE_BLADES_VISIBLE_CHEST,      BLUE_RUPEE,              {},                                                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_INVISIBLE_BLADES_INVISIBLE_CHEST]              = ItemLocation::Chest      (RC_SHADOW_TEMPLE_INVISIBLE_BLADES_INVISIBLE_CHEST,               0x07, 0x16, "Shadow Temple Invisible Blades Invisible Chest",     SHADOW_TEMPLE_INVISIBLE_BLADES_INVISIBLE_CHEST,    ARROWS_30,               {},                                                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_FALLING_SPIKES_LOWER_CHEST]                    = ItemLocation::Chest      (RC_SHADOW_TEMPLE_FALLING_SPIKES_LOWER_CHEST,                     0x07, 0x05, "Shadow Temple Falling Spikes Lower Chest",           SHADOW_TEMPLE_FALLING_SPIKES_LOWER_CHEST,          ARROWS_10,               {},                                                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_FALLING_SPIKES_UPPER_CHEST]                    = ItemLocation::Chest      (RC_SHADOW_TEMPLE_FALLING_SPIKES_UPPER_CHEST,                     0x07, 0x06, "Shadow Temple Falling Spikes Upper Chest",           SHADOW_TEMPLE_FALLING_SPIKES_UPPER_CHEST,          BLUE_RUPEE,              {},                                                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_FALLING_SPIKES_SWITCH_CHEST]                   = ItemLocation::Chest      (RC_SHADOW_TEMPLE_FALLING_SPIKES_SWITCH_CHEST,                    0x07, 0x04, "Shadow Temple Falling Spikes Switch Chest",          SHADOW_TEMPLE_FALLING_SPIKES_SWITCH_CHEST,         SHADOW_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_INVISIBLE_SPIKES_CHEST]                        = ItemLocation::Chest      (RC_SHADOW_TEMPLE_INVISIBLE_SPIKES_CHEST,                         0x07, 0x09, "Shadow Temple Invisible Spikes Chest",               SHADOW_TEMPLE_INVISIBLE_SPIKES_CHEST,              BLUE_RUPEE,              {},                                                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_WIND_HINT_CHEST]                               = ItemLocation::Chest      (RC_SHADOW_TEMPLE_WIND_HINT_CHEST,                                0x07, 0x15, "Shadow Temple Wind Hint Chest",                      SHADOW_TEMPLE_WIND_HINT_CHEST,                     ARROWS_10,               {},                                                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_AFTER_WIND_ENEMY_CHEST]                        = ItemLocation::Chest      (RC_SHADOW_TEMPLE_AFTER_WIND_ENEMY_CHEST,                         0x07, 0x08, "Shadow Temple After Wind Enemy Chest",               SHADOW_TEMPLE_AFTER_WIND_ENEMY_CHEST,              BLUE_RUPEE,              {},                                                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_AFTER_WIND_HIDDEN_CHEST]                       = ItemLocation::Chest      (RC_SHADOW_TEMPLE_AFTER_WIND_HIDDEN_CHEST,                        0x07, 0x14, "Shadow Temple After Wind Hidden Chest",              SHADOW_TEMPLE_AFTER_WIND_HIDDEN_CHEST,             SHADOW_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_SPIKE_WALLS_LEFT_CHEST]                        = ItemLocation::Chest      (RC_SHADOW_TEMPLE_SPIKE_WALLS_LEFT_CHEST,                         0x07, 0x0A, "Shadow Temple Spike Walls Left Chest",               SHADOW_TEMPLE_SPIKE_WALLS_LEFT_CHEST,              BLUE_RUPEE,              {},                                                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_BOSS_KEY_CHEST]                                = ItemLocation::Chest      (RC_SHADOW_TEMPLE_BOSS_KEY_CHEST,                                 0x07, 0x0B, "Shadow Temple Boss Key Chest",                       SHADOW_TEMPLE_BOSS_KEY_CHEST,                      SHADOW_TEMPLE_BOSS_KEY,  {Category::cVanillaBossKey},                                                 SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_INVISIBLE_FLOORMASTER_CHEST]                   = ItemLocation::Chest      (RC_SHADOW_TEMPLE_INVISIBLE_FLOORMASTER_CHEST,                    0x07, 0x0D, "Shadow Temple Invisible Floormaster Chest",          SHADOW_TEMPLE_INVISIBLE_FLOORMASTER_CHEST,         SHADOW_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_FREESTANDING_KEY]                              = ItemLocation::Collectable(RC_SHADOW_TEMPLE_FREESTANDING_KEY,                               0x07, 0x01, "Shadow Temple Freestanding Key",                     SHADOW_TEMPLE_FREESTANDING_KEY,                    SHADOW_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    //Shadow Temple MQ
    locationTable[SHADOW_TEMPLE_MQ_COMPASS_CHEST]                              = ItemLocation::Chest      (RC_SHADOW_TEMPLE_MQ_COMPASS_CHEST,                               0x07, 0x01, "Shadow Temple MQ Compass Chest",                     SHADOW_TEMPLE_MQ_COMPASS_CHEST,                    SHADOW_TEMPLE_COMPASS,   {Category::cVanillaCompass},                                                 SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_MQ_HOVER_BOOTS_CHEST]                          = ItemLocation::Chest      (RC_SHADOW_TEMPLE_MQ_HOVER_BOOTS_CHEST,                           0x07, 0x07, "Shadow Temple MQ Hover Boots Chest",                 SHADOW_TEMPLE_MQ_HOVER_BOOTS_CHEST,                HOVER_BOOTS,             {},                                                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_MQ_EARLY_GIBDOS_CHEST]                         = ItemLocation::Chest      (RC_SHADOW_TEMPLE_MQ_EARLY_GIBDOS_CHEST,                          0x07, 0x03, "Shadow Temple MQ Early Gibdos Chest",                SHADOW_TEMPLE_MQ_EARLY_GIBDOS_CHEST,               SHADOW_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_MQ_MAP_CHEST]                                  = ItemLocation::Chest      (RC_SHADOW_TEMPLE_MQ_MAP_CHEST,                                   0x07, 0x02, "Shadow Temple MQ Map Chest",                         SHADOW_TEMPLE_MQ_MAP_CHEST,                        SHADOW_TEMPLE_MAP,       {Category::cVanillaMap},                                                     SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_MQ_BEAMOS_SILVER_RUPEES_CHEST]                 = ItemLocation::Chest      (RC_SHADOW_TEMPLE_MQ_BEAMOS_SILVER_RUPEES_CHEST,                  0x07, 0x0F, "Shadow Temple MQ Beamos Silver Rupees Chest",        SHADOW_TEMPLE_MQ_BEAMOS_SILVER_RUPEES_CHEST,       ARROWS_5,                {},                                                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_MQ_FALLING_SPIKES_SWITCH_CHEST]                = ItemLocation::Chest      (RC_SHADOW_TEMPLE_MQ_FALLING_SPIKES_SWITCH_CHEST,                 0x07, 0x04, "Shadow Temple MQ Falling Spikes Switch Chest",       SHADOW_TEMPLE_MQ_FALLING_SPIKES_SWITCH_CHEST,      SHADOW_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_MQ_FALLING_SPIKES_LOWER_CHEST]                 = ItemLocation::Chest      (RC_SHADOW_TEMPLE_MQ_FALLING_SPIKES_LOWER_CHEST,                  0x07, 0x05, "Shadow Temple MQ Falling Spikes Lower Chest",        SHADOW_TEMPLE_MQ_FALLING_SPIKES_LOWER_CHEST,       ARROWS_10,               {},                                                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_MQ_FALLING_SPIKES_UPPER_CHEST]                 = ItemLocation::Chest      (RC_SHADOW_TEMPLE_MQ_FALLING_SPIKES_UPPER_CHEST,                  0x07, 0x06, "Shadow Temple MQ Falling Spikes Upper Chest",        SHADOW_TEMPLE_MQ_FALLING_SPIKES_UPPER_CHEST,       ARROWS_5,                {},                                                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_MQ_INVISIBLE_SPIKES_CHEST]                     = ItemLocation::Chest      (RC_SHADOW_TEMPLE_MQ_INVISIBLE_SPIKES_CHEST,                      0x07, 0x09, "Shadow Temple MQ Invisible Spikes Chest",            SHADOW_TEMPLE_MQ_INVISIBLE_SPIKES_CHEST,           BLUE_RUPEE,              {},                                                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_MQ_BOSS_KEY_CHEST]                             = ItemLocation::Chest      (RC_SHADOW_TEMPLE_MQ_BOSS_KEY_CHEST,                              0x07, 0x0B, "Shadow Temple MQ Boss Key Chest",                    SHADOW_TEMPLE_MQ_BOSS_KEY_CHEST,                   SHADOW_TEMPLE_BOSS_KEY,  {Category::cVanillaBossKey},                                                 SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_MQ_SPIKE_WALLS_LEFT_CHEST]                     = ItemLocation::Chest      (RC_SHADOW_TEMPLE_MQ_SPIKE_WALLS_LEFT_CHEST,                      0x07, 0x0A, "Shadow Temple MQ Spike Walls Left Chest",            SHADOW_TEMPLE_MQ_SPIKE_WALLS_LEFT_CHEST,           BLUE_RUPEE,              {},                                                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_MQ_STALFOS_ROOM_CHEST]                         = ItemLocation::Chest      (RC_SHADOW_TEMPLE_MQ_STALFOS_ROOM_CHEST,                          0x07, 0x10, "Shadow Temple MQ Stalfos Room Chest",                SHADOW_TEMPLE_MQ_STALFOS_ROOM_CHEST,               RED_RUPEE,               {},                                                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_MQ_INVISIBLE_BLADES_INVISIBLE_CHEST]           = ItemLocation::Chest      (RC_SHADOW_TEMPLE_MQ_INVISIBLE_BLADES_INVISIBLE_CHEST,            0x07, 0x16, "Shadow Temple MQ Invisible Blades Invisible Chest",  SHADOW_TEMPLE_MQ_INVISIBLE_BLADES_INVISIBLE_CHEST, SHADOW_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_MQ_INVISIBLE_BLADES_VISIBLE_CHEST]             = ItemLocation::Chest      (RC_SHADOW_TEMPLE_MQ_INVISIBLE_BLADES_VISIBLE_CHEST,              0x07, 0x0C, "Shadow Temple MQ Invisible Blades Visible Chest",    SHADOW_TEMPLE_MQ_INVISIBLE_BLADES_VISIBLE_CHEST,   BLUE_RUPEE,              {},                                                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_MQ_BOMB_FLOWER_CHEST]                          = ItemLocation::Chest      (RC_SHADOW_TEMPLE_MQ_BOMB_FLOWER_CHEST,                           0x07, 0x0D, "Shadow Temple MQ Bomb Flower Chest",                 SHADOW_TEMPLE_MQ_BOMB_FLOWER_CHEST,                ARROWS_10,               {},                                                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_MQ_WIND_HINT_CHEST]                            = ItemLocation::Chest      (RC_SHADOW_TEMPLE_MQ_WIND_HINT_CHEST,                             0x07, 0x15, "Shadow Temple MQ Wind Hint Chest",                   SHADOW_TEMPLE_MQ_WIND_HINT_CHEST,                  SHADOW_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_MQ_AFTER_WIND_HIDDEN_CHEST]                    = ItemLocation::Chest      (RC_SHADOW_TEMPLE_MQ_AFTER_WIND_HIDDEN_CHEST,                     0x07, 0x14, "Shadow Temple MQ After Wind Hidden Chest",           SHADOW_TEMPLE_MQ_AFTER_WIND_HIDDEN_CHEST,          ARROWS_5,                {},                                                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_MQ_AFTER_WIND_ENEMY_CHEST]                     = ItemLocation::Chest      (RC_SHADOW_TEMPLE_MQ_AFTER_WIND_ENEMY_CHEST,                      0x07, 0x08, "Shadow Temple MQ After Wind Enemy Chest",            SHADOW_TEMPLE_MQ_AFTER_WIND_ENEMY_CHEST,           BLUE_RUPEE,              {},                                                                          SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_MQ_NEAR_SHIP_INVISIBLE_CHEST]                  = ItemLocation::Chest      (RC_SHADOW_TEMPLE_MQ_NEAR_SHIP_INVISIBLE_CHEST,                   0x07, 0x0E, "Shadow Temple MQ Near Ship Invisible Chest",         SHADOW_TEMPLE_MQ_NEAR_SHIP_INVISIBLE_CHEST,        SHADOW_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_MQ_FREESTANDING_KEY]                           = ItemLocation::Collectable(RC_SHADOW_TEMPLE_MQ_FREESTANDING_KEY,                            0x07, 0x06, "Shadow Temple MQ Freestanding Key",                  SHADOW_TEMPLE_MQ_FREESTANDING_KEY,                 SHADOW_TEMPLE_SMALL_KEY, {Category::cVanillaSmallKey},                                                SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);

    //Bottom of the Well Vanilla
    locationTable[BOTTOM_OF_THE_WELL_FRONT_LEFT_FAKE_WALL_CHEST]               = ItemLocation::Chest      (RC_BOTTOM_OF_THE_WELL_FRONT_LEFT_FAKE_WALL_CHEST,                0x08, 0x08, "Bottom of the Well Front Left Fake Wall Chest",         BOTTOM_OF_THE_WELL_FRONT_LEFT_FAKE_WALL_CHEST,          BOTTOM_OF_THE_WELL_SMALL_KEY, {Category::cVanillaSmallKey},                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_BOTTOM_OF_THE_WELL);
    locationTable[BOTTOM_OF_THE_WELL_FRONT_CENTER_BOMBABLE_CHEST]              = ItemLocation::Chest      (RC_BOTTOM_OF_THE_WELL_FRONT_CENTER_BOMBABLE_CHEST,               0x08, 0x02, "Bottom of the Well Front Center Bombable Chest",        BOTTOM_OF_THE_WELL_FRONT_CENTER_BOMBABLE_CHEST,         BOMBCHU_10,                   {},                                                             SpoilerCollectionCheckGroup::GROUP_DUNGEON_BOTTOM_OF_THE_WELL);
    locationTable[BOTTOM_OF_THE_WELL_RIGHT_BOTTOM_FAKE_WALL_CHEST]             = ItemLocation::Chest      (RC_BOTTOM_OF_THE_WELL_RIGHT_BOTTOM_FAKE_WALL_CHEST,              0x08, 0x05, "Bottom of the Well Right Bottom Fake Wall Chest",       BOTTOM_OF_THE_WELL_RIGHT_BOTTOM_FAKE_WALL_CHEST,        BOTTOM_OF_THE_WELL_SMALL_KEY, {Category::cVanillaSmallKey},                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_BOTTOM_OF_THE_WELL);
    locationTable[BOTTOM_OF_THE_WELL_COMPASS_CHEST]                            = ItemLocation::Chest      (RC_BOTTOM_OF_THE_WELL_COMPASS_CHEST,                             0x08, 0x01, "Bottom of the Well Compass Chest",                      BOTTOM_OF_THE_WELL_COMPASS_CHEST,                       BOTTOM_OF_THE_WELL_COMPASS,   {Category::cVanillaCompass},                                    SpoilerCollectionCheckGroup::GROUP_DUNGEON_BOTTOM_OF_THE_WELL);
    locationTable[BOTTOM_OF_THE_WELL_CENTER_SKULLTULA_CHEST]                   = ItemLocation::Chest      (RC_BOTTOM_OF_THE_WELL_CENTER_SKULLTULA_CHEST,                    0x08, 0x0E, "Bottom of the Well Center Skulltula Chest",             BOTTOM_OF_THE_WELL_CENTER_SKULLTULA_CHEST,              DEKU_NUTS_5,                  {},                                                             SpoilerCollectionCheckGroup::GROUP_DUNGEON_BOTTOM_OF_THE_WELL);
    locationTable[BOTTOM_OF_THE_WELL_BACK_LEFT_BOMBABLE_CHEST]                 = ItemLocation::Chest      (RC_BOTTOM_OF_THE_WELL_BACK_LEFT_BOMBABLE_CHEST,                  0x08, 0x04, "Bottom of the Well Back Left Bombable Chest",           BOTTOM_OF_THE_WELL_BACK_LEFT_BOMBABLE_CHEST,            DEKU_NUTS_10,                 {},                                                             SpoilerCollectionCheckGroup::GROUP_DUNGEON_BOTTOM_OF_THE_WELL);
    locationTable[BOTTOM_OF_THE_WELL_LENS_OF_TRUTH_CHEST]                      = ItemLocation::Chest      (RC_BOTTOM_OF_THE_WELL_LENS_OF_TRUTH_CHEST,                       0x08, 0x03, "Bottom of the Well Lens of Truth Chest",                BOTTOM_OF_THE_WELL_LENS_OF_TRUTH_CHEST,                 LENS_OF_TRUTH,                {Category::cSongDungeonReward},                                 SpoilerCollectionCheckGroup::GROUP_DUNGEON_BOTTOM_OF_THE_WELL);
    locationTable[BOTTOM_OF_THE_WELL_INVISIBLE_CHEST]                          = ItemLocation::Chest      (RC_BOTTOM_OF_THE_WELL_INVISIBLE_CHEST,                           0x08, 0x14, "Bottom of the Well Invisible Chest",                    BOTTOM_OF_THE_WELL_INVISIBLE_CHEST,                     HUGE_RUPEE,                   {},                                                             SpoilerCollectionCheckGroup::GROUP_DUNGEON_BOTTOM_OF_THE_WELL);
    locationTable[BOTTOM_OF_THE_WELL_UNDERWATER_FRONT_CHEST]                   = ItemLocation::Chest      (RC_BOTTOM_OF_THE_WELL_UNDERWATER_FRONT_CHEST,                    0x08, 0x10, "Bottom of the Well Underwater Front Chest",             BOTTOM_OF_THE_WELL_UNDERWATER_FRONT_CHEST,              BOMBS_10,                     {},                                                             SpoilerCollectionCheckGroup::GROUP_DUNGEON_BOTTOM_OF_THE_WELL);
    locationTable[BOTTOM_OF_THE_WELL_UNDERWATER_LEFT_CHEST]                    = ItemLocation::Chest      (RC_BOTTOM_OF_THE_WELL_UNDERWATER_LEFT_CHEST,                     0x08, 0x09, "Bottom of the Well Underwater Left Chest",              BOTTOM_OF_THE_WELL_UNDERWATER_LEFT_CHEST,               RECOVERY_HEART,               {},                                                             SpoilerCollectionCheckGroup::GROUP_DUNGEON_BOTTOM_OF_THE_WELL);
    locationTable[BOTTOM_OF_THE_WELL_MAP_CHEST]                                = ItemLocation::Chest      (RC_BOTTOM_OF_THE_WELL_MAP_CHEST,                                 0x08, 0x07, "Bottom of the Well Map Chest",                          BOTTOM_OF_THE_WELL_MAP_CHEST,                           BOTTOM_OF_THE_WELL_MAP,       {Category::cVanillaMap},                                        SpoilerCollectionCheckGroup::GROUP_DUNGEON_BOTTOM_OF_THE_WELL);
    locationTable[BOTTOM_OF_THE_WELL_FIRE_KEESE_CHEST]                         = ItemLocation::Chest      (RC_BOTTOM_OF_THE_WELL_FIRE_KEESE_CHEST,                          0x08, 0x0A, "Bottom of the Well Fire Keese Chest",                   BOTTOM_OF_THE_WELL_FIRE_KEESE_CHEST,                    DEKU_SHIELD,                  {},                                                             SpoilerCollectionCheckGroup::GROUP_DUNGEON_BOTTOM_OF_THE_WELL);
    locationTable[BOTTOM_OF_THE_WELL_LIKE_LIKE_CHEST]                          = ItemLocation::Chest      (RC_BOTTOM_OF_THE_WELL_LIKE_LIKE_CHEST,                           0x08, 0x0C, "Bottom of the Well Like Like Chest",                    BOTTOM_OF_THE_WELL_LIKE_LIKE_CHEST,                     HYLIAN_SHIELD,                {},                                                             SpoilerCollectionCheckGroup::GROUP_DUNGEON_BOTTOM_OF_THE_WELL);
    locationTable[BOTTOM_OF_THE_WELL_FREESTANDING_KEY]                         = ItemLocation::Collectable(RC_BOTTOM_OF_THE_WELL_FREESTANDING_KEY,                          0x08, 0x01, "Bottom of the Well Freestanding Key",                   BOTTOM_OF_THE_WELL_FREESTANDING_KEY,                    BOTTOM_OF_THE_WELL_SMALL_KEY, {Category::cVanillaSmallKey},                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_BOTTOM_OF_THE_WELL);
    //Bottom of the Well MQBottomOfTheWell]
    locationTable[BOTTOM_OF_THE_WELL_MQ_MAP_CHEST]                             = ItemLocation::Chest      (RC_BOTTOM_OF_THE_WELL_MQ_MAP_CHEST,                              0x08, 0x03, "Bottom of the Well MQ Map Chest",                       BOTTOM_OF_THE_WELL_MQ_MAP_CHEST,                        BOTTOM_OF_THE_WELL_MAP,       {Category::cVanillaMap},                                        SpoilerCollectionCheckGroup::GROUP_DUNGEON_BOTTOM_OF_THE_WELL);
    locationTable[BOTTOM_OF_THE_WELL_MQ_LENS_OF_TRUTH_CHEST]                   = ItemLocation::Chest      (RC_BOTTOM_OF_THE_WELL_MQ_LENS_OF_TRUTH_CHEST,                    0x08, 0x01, "Bottom of the Well MQ Lens of Truth Chest",             BOTTOM_OF_THE_WELL_MQ_LENS_OF_TRUTH_CHEST,              LENS_OF_TRUTH,                {Category::cSongDungeonReward},                                 SpoilerCollectionCheckGroup::GROUP_DUNGEON_BOTTOM_OF_THE_WELL);
    locationTable[BOTTOM_OF_THE_WELL_MQ_COMPASS_CHEST]                         = ItemLocation::Chest      (RC_BOTTOM_OF_THE_WELL_MQ_COMPASS_CHEST,                          0x08, 0x02, "Bottom of the Well MQ Compass Chest",                   BOTTOM_OF_THE_WELL_MQ_COMPASS_CHEST,                    BOTTOM_OF_THE_WELL_COMPASS,   {Category::cVanillaCompass},                                    SpoilerCollectionCheckGroup::GROUP_DUNGEON_BOTTOM_OF_THE_WELL);
    locationTable[BOTTOM_OF_THE_WELL_MQ_DEAD_HAND_FREESTANDING_KEY]            = ItemLocation::Collectable(RC_BOTTOM_OF_THE_WELL_MQ_DEAD_HAND_FREESTANDING_KEY,             0x08, 0x02, "Bottom of the Well MQ Dead Hand Freestanding Key",      BOTTOM_OF_THE_WELL_MQ_DEAD_HAND_FREESTANDING_KEY,       BOTTOM_OF_THE_WELL_SMALL_KEY, {Category::cVanillaSmallKey},                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_BOTTOM_OF_THE_WELL);
    locationTable[BOTTOM_OF_THE_WELL_MQ_EAST_INNER_ROOM_FREESTANDING_KEY]      = ItemLocation::Collectable(RC_BOTTOM_OF_THE_WELL_MQ_EAST_INNER_ROOM_FREESTANDING_KEY,       0x08, 0x01, "Bottom of the Well MQ East Inner Room Freestanding Key",BOTTOM_OF_THE_WELL_MQ_EAST_INNER_ROOM_FREESTANDING_KEY, BOTTOM_OF_THE_WELL_SMALL_KEY, {Category::cVanillaSmallKey},                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_BOTTOM_OF_THE_WELL);

    //Ice Cavern Vanilla
    locationTable[ICE_CAVERN_MAP_CHEST]                                        = ItemLocation::Chest      (RC_ICE_CAVERN_MAP_CHEST,                                         0x09, 0x00, "Ice Cavern Map Chest",                                  ICE_CAVERN_MAP_CHEST,            ICE_CAVERN_MAP,     {Category::cVanillaMap},                                                                         SpoilerCollectionCheckGroup::GROUP_DUNGEON_ICE_CAVERN);
    locationTable[ICE_CAVERN_COMPASS_CHEST]                                    = ItemLocation::Chest      (RC_ICE_CAVERN_COMPASS_CHEST,                                     0x09, 0x01, "Ice Cavern Compass Chest",                              ICE_CAVERN_COMPASS_CHEST,        ICE_CAVERN_COMPASS, {Category::cVanillaCompass},                                                                     SpoilerCollectionCheckGroup::GROUP_DUNGEON_ICE_CAVERN);
    locationTable[ICE_CAVERN_IRON_BOOTS_CHEST]                                 = ItemLocation::Chest      (RC_ICE_CAVERN_IRON_BOOTS_CHEST,                                  0x09, 0x02, "Ice Cavern Iron Boots Chest",                           ICE_CAVERN_IRON_BOOTS_CHEST,     IRON_BOOTS,         {},                                                                                              SpoilerCollectionCheckGroup::GROUP_DUNGEON_ICE_CAVERN);
    locationTable[ICE_CAVERN_FREESTANDING_POH]                                 = ItemLocation::Collectable(RC_ICE_CAVERN_FREESTANDING_POH,                                  0x09, 0x01, "Ice Cavern Freestanding PoH",                           ICE_CAVERN_FREESTANDING_POH,     PIECE_OF_HEART,     {},                                                                                              SpoilerCollectionCheckGroup::GROUP_DUNGEON_ICE_CAVERN);
    //Ice Cavern MQIceCavern]
    locationTable[ICE_CAVERN_MQ_IRON_BOOTS_CHEST]                              = ItemLocation::Chest      (RC_ICE_CAVERN_MQ_IRON_BOOTS_CHEST,                               0x09, 0x02, "Ice Cavern MQ Iron Boots Chest",                        ICE_CAVERN_MQ_IRON_BOOTS_CHEST,  IRON_BOOTS,         {},                                                                                              SpoilerCollectionCheckGroup::GROUP_DUNGEON_ICE_CAVERN);
    locationTable[ICE_CAVERN_MQ_COMPASS_CHEST]                                 = ItemLocation::Chest      (RC_ICE_CAVERN_MQ_COMPASS_CHEST,                                  0x09, 0x00, "Ice Cavern MQ Compass Chest",                           ICE_CAVERN_MQ_COMPASS_CHEST,     ICE_CAVERN_COMPASS, {Category::cVanillaCompass},                                                                     SpoilerCollectionCheckGroup::GROUP_DUNGEON_ICE_CAVERN);
    locationTable[ICE_CAVERN_MQ_MAP_CHEST]                                     = ItemLocation::Chest      (RC_ICE_CAVERN_MQ_MAP_CHEST,                                      0x09, 0x01, "Ice Cavern MQ Map Chest",                               ICE_CAVERN_MQ_MAP_CHEST,         ICE_CAVERN_MAP,     {Category::cVanillaMap},                                                                         SpoilerCollectionCheckGroup::GROUP_DUNGEON_ICE_CAVERN);
    locationTable[ICE_CAVERN_MQ_FREESTANDING_POH]                              = ItemLocation::Collectable(RC_ICE_CAVERN_MQ_FREESTANDING_POH,                               0x09, 0x01, "Ice Cavern MQ Freestanding PoH",                        ICE_CAVERN_MQ_FREESTANDING_POH,  PIECE_OF_HEART,     {},                                                                                              SpoilerCollectionCheckGroup::GROUP_DUNGEON_ICE_CAVERN);

    //Gerudo Training Ground Vanilla
    locationTable[GERUDO_TRAINING_GROUNDS_LOBBY_LEFT_CHEST]                    = ItemLocation::Chest      (RC_GERUDO_TRAINING_GROUND_LOBBY_LEFT_CHEST,                      0x0B, 0x13, "Gerudo Training Grounds Lobby Left Chest",              GERUDO_TRAINING_GROUNDS_LOBBY_LEFT_CHEST,                   BLUE_RUPEE,                        {},                                                    SpoilerCollectionCheckGroup::GROUP_GERUDO_TRAINING_GROUND);
    locationTable[GERUDO_TRAINING_GROUNDS_LOBBY_RIGHT_CHEST]                   = ItemLocation::Chest      (RC_GERUDO_TRAINING_GROUND_LOBBY_RIGHT_CHEST,                     0x0B, 0x07, "Gerudo Training Grounds Lobby Right Chest",             GERUDO_TRAINING_GROUNDS_LOBBY_RIGHT_CHEST,                  ARROWS_10,                         {},                                                    SpoilerCollectionCheckGroup::GROUP_GERUDO_TRAINING_GROUND);
    locationTable[GERUDO_TRAINING_GROUNDS_STALFOS_CHEST]                       = ItemLocation::Chest      (RC_GERUDO_TRAINING_GROUND_STALFOS_CHEST,                         0x0B, 0x00, "Gerudo Training Grounds Stalfos Chest",                 GERUDO_TRAINING_GROUNDS_STALFOS_CHEST,                      GERUDO_TRAINING_GROUNDS_SMALL_KEY, {Category::cVanillaSmallKey},                          SpoilerCollectionCheckGroup::GROUP_GERUDO_TRAINING_GROUND);
    locationTable[GERUDO_TRAINING_GROUNDS_BEAMOS_CHEST]                        = ItemLocation::Chest      (RC_GERUDO_TRAINING_GROUND_BEAMOS_CHEST,                          0x0B, 0x01, "Gerudo Training Grounds Beamos Chest",                  GERUDO_TRAINING_GROUNDS_BEAMOS_CHEST,                       GERUDO_TRAINING_GROUNDS_SMALL_KEY, {Category::cVanillaSmallKey},                          SpoilerCollectionCheckGroup::GROUP_GERUDO_TRAINING_GROUND);
    locationTable[GERUDO_TRAINING_GROUNDS_HIDDEN_CEILING_CHEST]                = ItemLocation::Chest      (RC_GERUDO_TRAINING_GROUND_HIDDEN_CEILING_CHEST,                  0x0B, 0x0B, "Gerudo Training Grounds Hidden Ceiling Chest",          GERUDO_TRAINING_GROUNDS_HIDDEN_CEILING_CHEST,               GERUDO_TRAINING_GROUNDS_SMALL_KEY, {Category::cVanillaSmallKey},                          SpoilerCollectionCheckGroup::GROUP_GERUDO_TRAINING_GROUND);
    locationTable[GERUDO_TRAINING_GROUNDS_MAZE_PATH_FIRST_CHEST]               = ItemLocation::Chest      (RC_GERUDO_TRAINING_GROUND_MAZE_PATH_FIRST_CHEST,                 0x0B, 0x06, "Gerudo Training Grounds Maze Path First Chest",         GERUDO_TRAINING_GROUNDS_MAZE_PATH_FIRST_CHEST,              PURPLE_RUPEE,                      {},                                                    SpoilerCollectionCheckGroup::GROUP_GERUDO_TRAINING_GROUND);
    locationTable[GERUDO_TRAINING_GROUNDS_MAZE_PATH_SECOND_CHEST]              = ItemLocation::Chest      (RC_GERUDO_TRAINING_GROUND_MAZE_PATH_SECOND_CHEST,                0x0B, 0x0A, "Gerudo Training Grounds Maze Path Second Chest",        GERUDO_TRAINING_GROUNDS_MAZE_PATH_SECOND_CHEST,             RED_RUPEE,                         {},                                                    SpoilerCollectionCheckGroup::GROUP_GERUDO_TRAINING_GROUND);
    locationTable[GERUDO_TRAINING_GROUNDS_MAZE_PATH_THIRD_CHEST]               = ItemLocation::Chest      (RC_GERUDO_TRAINING_GROUND_MAZE_PATH_THIRD_CHEST,                 0x0B, 0x09, "Gerudo Training Grounds Maze Path Third Chest",         GERUDO_TRAINING_GROUNDS_MAZE_PATH_THIRD_CHEST,              ARROWS_30,                         {},                                                    SpoilerCollectionCheckGroup::GROUP_GERUDO_TRAINING_GROUND);
    locationTable[GERUDO_TRAINING_GROUNDS_MAZE_PATH_FINAL_CHEST]               = ItemLocation::Chest      (RC_GERUDO_TRAINING_GROUND_MAZE_PATH_FINAL_CHEST,                 0x0B, 0x0C, "Gerudo Training Grounds Maze Path Final Chest",         GERUDO_TRAINING_GROUNDS_MAZE_PATH_FINAL_CHEST,              ICE_ARROWS,                        {Category::cSongDungeonReward},                        SpoilerCollectionCheckGroup::GROUP_GERUDO_TRAINING_GROUND);
    locationTable[GERUDO_TRAINING_GROUNDS_MAZE_RIGHT_CENTRAL_CHEST]            = ItemLocation::Chest      (RC_GERUDO_TRAINING_GROUND_MAZE_RIGHT_CENTRAL_CHEST,              0x0B, 0x05, "Gerudo Training Grounds Maze Right Central Chest",      GERUDO_TRAINING_GROUNDS_MAZE_RIGHT_CENTRAL_CHEST,           BOMBCHU_5,                         {},                                                    SpoilerCollectionCheckGroup::GROUP_GERUDO_TRAINING_GROUND);
    locationTable[GERUDO_TRAINING_GROUNDS_MAZE_RIGHT_SIDE_CHEST]               = ItemLocation::Chest      (RC_GERUDO_TRAINING_GROUND_MAZE_RIGHT_SIDE_CHEST,                 0x0B, 0x08, "Gerudo Training Grounds Maze Right Side Chest",         GERUDO_TRAINING_GROUNDS_MAZE_RIGHT_SIDE_CHEST,              ARROWS_30,                         {},                                                    SpoilerCollectionCheckGroup::GROUP_GERUDO_TRAINING_GROUND);
    locationTable[GERUDO_TRAINING_GROUNDS_UNDERWATER_SILVER_RUPEE_CHEST]       = ItemLocation::Chest      (RC_GERUDO_TRAINING_GROUND_UNDERWATER_SILVER_RUPEE_CHEST,         0x0B, 0x0D, "Gerudo Training Grounds Underwater Silver Rupee Chest", GERUDO_TRAINING_GROUNDS_UNDERWATER_SILVER_RUPEE_CHEST,      GERUDO_TRAINING_GROUNDS_SMALL_KEY, {Category::cVanillaSmallKey},                          SpoilerCollectionCheckGroup::GROUP_GERUDO_TRAINING_GROUND);
    locationTable[GERUDO_TRAINING_GROUNDS_HAMMER_ROOM_CLEAR_CHEST]             = ItemLocation::Chest      (RC_GERUDO_TRAINING_GROUND_HAMMER_ROOM_CLEAR_CHEST,               0x0B, 0x12, "Gerudo Training Grounds Hammer Room Clear Chest",       GERUDO_TRAINING_GROUNDS_HAMMER_ROOM_CLEAR_CHEST,            ARROWS_10,                         {},                                                    SpoilerCollectionCheckGroup::GROUP_GERUDO_TRAINING_GROUND);
    locationTable[GERUDO_TRAINING_GROUNDS_HAMMER_ROOM_SWITCH_CHEST]            = ItemLocation::Chest      (RC_GERUDO_TRAINING_GROUND_HAMMER_ROOM_SWITCH_CHEST,              0x0B, 0x10, "Gerudo Training Grounds Hammer Room Switch Chest",      GERUDO_TRAINING_GROUNDS_HAMMER_ROOM_SWITCH_CHEST,           GERUDO_TRAINING_GROUNDS_SMALL_KEY, {Category::cVanillaSmallKey},                          SpoilerCollectionCheckGroup::GROUP_GERUDO_TRAINING_GROUND);
    locationTable[GERUDO_TRAINING_GROUNDS_EYE_STATUE_CHEST]                    = ItemLocation::Chest      (RC_GERUDO_TRAINING_GROUND_EYE_STATUE_CHEST,                      0x0B, 0x03, "Gerudo Training Grounds Eye Statue Chest",              GERUDO_TRAINING_GROUNDS_EYE_STATUE_CHEST,                   GERUDO_TRAINING_GROUNDS_SMALL_KEY, {Category::cVanillaSmallKey},                          SpoilerCollectionCheckGroup::GROUP_GERUDO_TRAINING_GROUND);
    locationTable[GERUDO_TRAINING_GROUNDS_NEAR_SCARECROW_CHEST]                = ItemLocation::Chest      (RC_GERUDO_TRAINING_GROUND_NEAR_SCARECROW_CHEST,                  0x0B, 0x04, "Gerudo Training Grounds Near Scarecrow Chest",          GERUDO_TRAINING_GROUNDS_NEAR_SCARECROW_CHEST,               GERUDO_TRAINING_GROUNDS_SMALL_KEY, {Category::cVanillaSmallKey},                          SpoilerCollectionCheckGroup::GROUP_GERUDO_TRAINING_GROUND);
    locationTable[GERUDO_TRAINING_GROUNDS_BEFORE_HEAVY_BLOCK_CHEST]            = ItemLocation::Chest      (RC_GERUDO_TRAINING_GROUND_BEFORE_HEAVY_BLOCK_CHEST,              0x0B, 0x11, "Gerudo Training Grounds Before Heavy Block Chest",      GERUDO_TRAINING_GROUNDS_BEFORE_HEAVY_BLOCK_CHEST,           ARROWS_30,                         {},                                                    SpoilerCollectionCheckGroup::GROUP_GERUDO_TRAINING_GROUND);
    locationTable[GERUDO_TRAINING_GROUNDS_HEAVY_BLOCK_FIRST_CHEST]             = ItemLocation::Chest      (RC_GERUDO_TRAINING_GROUND_HEAVY_BLOCK_FIRST_CHEST,               0x0B, 0x0F, "Gerudo Training Grounds Heavy Block First Chest",       GERUDO_TRAINING_GROUNDS_HEAVY_BLOCK_FIRST_CHEST,            HUGE_RUPEE,                        {},                                                    SpoilerCollectionCheckGroup::GROUP_GERUDO_TRAINING_GROUND);
    locationTable[GERUDO_TRAINING_GROUNDS_HEAVY_BLOCK_SECOND_CHEST]            = ItemLocation::Chest      (RC_GERUDO_TRAINING_GROUND_HEAVY_BLOCK_SECOND_CHEST,              0x0B, 0x0E, "Gerudo Training Grounds Heavy Block Second Chest",      GERUDO_TRAINING_GROUNDS_HEAVY_BLOCK_SECOND_CHEST,           BLUE_RUPEE,                        {},                                                    SpoilerCollectionCheckGroup::GROUP_GERUDO_TRAINING_GROUND);
    locationTable[GERUDO_TRAINING_GROUNDS_HEAVY_BLOCK_THIRD_CHEST]             = ItemLocation::Chest      (RC_GERUDO_TRAINING_GROUND_HEAVY_BLOCK_THIRD_CHEST,               0x0B, 0x14, "Gerudo Training Grounds Heavy Block Third Chest",       GERUDO_TRAINING_GROUNDS_HEAVY_BLOCK_THIRD_CHEST,            GERUDO_TRAINING_GROUNDS_SMALL_KEY, {Category::cVanillaSmallKey},                          SpoilerCollectionCheckGroup::GROUP_GERUDO_TRAINING_GROUND);
    locationTable[GERUDO_TRAINING_GROUNDS_HEAVY_BLOCK_FOURTH_CHEST]            = ItemLocation::Chest      (RC_GERUDO_TRAINING_GROUND_HEAVY_BLOCK_FOURTH_CHEST,              0x0B, 0x02, "Gerudo Training Grounds Heavy Block Fourth Chest",      GERUDO_TRAINING_GROUNDS_HEAVY_BLOCK_FOURTH_CHEST,           ICE_TRAP,                          {},                                                    SpoilerCollectionCheckGroup::GROUP_GERUDO_TRAINING_GROUND);
    locationTable[GERUDO_TRAINING_GROUNDS_FREESTANDING_KEY]                    = ItemLocation::Collectable(RC_GERUDO_TRAINING_GROUND_FREESTANDING_KEY,                      0x0B, 0x01, "Gerudo Training Grounds Freestanding Key",              GERUDO_TRAINING_GROUNDS_FREESTANDING_KEY,                   GERUDO_TRAINING_GROUNDS_SMALL_KEY, {Category::cVanillaSmallKey},                          SpoilerCollectionCheckGroup::GROUP_GERUDO_TRAINING_GROUND);
    //Gerudo Training Grounds MQ
    locationTable[GERUDO_TRAINING_GROUNDS_MQ_LOBBY_RIGHT_CHEST]                = ItemLocation::Chest      (RC_GERUDO_TRAINING_GROUND_MQ_LOBBY_RIGHT_CHEST,                  0x0B, 0x07, "Gerudo Training Grounds MQ Lobby Right Chest",          GERUDO_TRAINING_GROUNDS_MQ_LOBBY_RIGHT_CHEST,               BOMBCHU_5,                         {},                                                    SpoilerCollectionCheckGroup::GROUP_GERUDO_TRAINING_GROUND);
    locationTable[GERUDO_TRAINING_GROUNDS_MQ_LOBBY_LEFT_CHEST]                 = ItemLocation::Chest      (RC_GERUDO_TRAINING_GROUND_MQ_LOBBY_LEFT_CHEST,                   0x0B, 0x13, "Gerudo Training Grounds MQ Lobby Left Chest",           GERUDO_TRAINING_GROUNDS_MQ_LOBBY_LEFT_CHEST,                ARROWS_10,                         {},                                                    SpoilerCollectionCheckGroup::GROUP_GERUDO_TRAINING_GROUND);
    locationTable[GERUDO_TRAINING_GROUNDS_MQ_FIRST_IRON_KNUCKLE_CHEST]         = ItemLocation::Chest      (RC_GERUDO_TRAINING_GROUND_MQ_FIRST_IRON_KNUCKLE_CHEST,           0x0B, 0x00, "Gerudo Training Grounds MQ First Iron Knuckle Chest",   GERUDO_TRAINING_GROUNDS_MQ_FIRST_IRON_KNUCKLE_CHEST,        BLUE_RUPEE,                        {},                                                    SpoilerCollectionCheckGroup::GROUP_GERUDO_TRAINING_GROUND);
    locationTable[GERUDO_TRAINING_GROUNDS_MQ_BEFORE_HEAVY_BLOCK_CHEST]         = ItemLocation::Chest      (RC_GERUDO_TRAINING_GROUND_MQ_BEFORE_HEAVY_BLOCK_CHEST,           0x0B, 0x11, "Gerudo Training Grounds MQ Before Heavy Block Chest",   GERUDO_TRAINING_GROUNDS_MQ_BEFORE_HEAVY_BLOCK_CHEST,        ARROWS_10,                         {},                                                    SpoilerCollectionCheckGroup::GROUP_GERUDO_TRAINING_GROUND);
    locationTable[GERUDO_TRAINING_GROUNDS_MQ_EYE_STATUE_CHEST]                 = ItemLocation::Chest      (RC_GERUDO_TRAINING_GROUND_MQ_EYE_STATUE_CHEST,                   0x0B, 0x03, "Gerudo Training Grounds MQ Eye Statue Chest",           GERUDO_TRAINING_GROUNDS_MQ_EYE_STATUE_CHEST,                BOMBCHU_10,                        {},                                                    SpoilerCollectionCheckGroup::GROUP_GERUDO_TRAINING_GROUND);
    locationTable[GERUDO_TRAINING_GROUNDS_MQ_FLAME_CIRCLE_CHEST]               = ItemLocation::Chest      (RC_GERUDO_TRAINING_GROUND_MQ_FLAME_CIRCLE_CHEST,                 0x0B, 0x0E, "Gerudo Training Grounds MQ Flame Circle Chest",         GERUDO_TRAINING_GROUNDS_MQ_FLAME_CIRCLE_CHEST,              GERUDO_TRAINING_GROUNDS_SMALL_KEY, {Category::cVanillaSmallKey},                          SpoilerCollectionCheckGroup::GROUP_GERUDO_TRAINING_GROUND);
    locationTable[GERUDO_TRAINING_GROUNDS_MQ_SECOND_IRON_KNUCKLE_CHEST]        = ItemLocation::Chest      (RC_GERUDO_TRAINING_GROUND_MQ_SECOND_IRON_KNUCKLE_CHEST,          0x0B, 0x12, "Gerudo Training Grounds MQ Second Iron Knuckle Chest",  GERUDO_TRAINING_GROUNDS_MQ_SECOND_IRON_KNUCKLE_CHEST,       ARROWS_10,                         {},                                                    SpoilerCollectionCheckGroup::GROUP_GERUDO_TRAINING_GROUND);
    locationTable[GERUDO_TRAINING_GROUNDS_MQ_DINOLFOS_CHEST]                   = ItemLocation::Chest      (RC_GERUDO_TRAINING_GROUND_MQ_DINOLFOS_CHEST,                     0x0B, 0x01, "Gerudo Training Grounds MQ Dinolfos Chest",             GERUDO_TRAINING_GROUNDS_MQ_DINOLFOS_CHEST,                  GERUDO_TRAINING_GROUNDS_SMALL_KEY, {Category::cVanillaSmallKey},                          SpoilerCollectionCheckGroup::GROUP_GERUDO_TRAINING_GROUND);
    locationTable[GERUDO_TRAINING_GROUNDS_MQ_ICE_ARROWS_CHEST]                 = ItemLocation::Chest      (RC_GERUDO_TRAINING_GROUND_MQ_ICE_ARROWS_CHEST,                   0x0B, 0x04, "Gerudo Training Grounds MQ Ice Arrows Chest",           GERUDO_TRAINING_GROUNDS_MQ_ICE_ARROWS_CHEST,                ICE_ARROWS,                        {Category::cSongDungeonReward},                        SpoilerCollectionCheckGroup::GROUP_GERUDO_TRAINING_GROUND);
    locationTable[GERUDO_TRAINING_GROUNDS_MQ_MAZE_RIGHT_CENTRAL_CHEST]         = ItemLocation::Chest      (RC_GERUDO_TRAINING_GROUND_MQ_MAZE_RIGHT_CENTRAL_CHEST,           0x0B, 0x05, "Gerudo Training Grounds MQ Maze Right Central Chest",   GERUDO_TRAINING_GROUNDS_MQ_MAZE_RIGHT_CENTRAL_CHEST,        BLUE_RUPEE,                        {},                                                    SpoilerCollectionCheckGroup::GROUP_GERUDO_TRAINING_GROUND);
    locationTable[GERUDO_TRAINING_GROUNDS_MQ_MAZE_PATH_FIRST_CHEST]            = ItemLocation::Chest      (RC_GERUDO_TRAINING_GROUND_MQ_MAZE_PATH_FIRST_CHEST,              0x0B, 0x06, "Gerudo Training Grounds MQ Maze Path First Chest",      GERUDO_TRAINING_GROUNDS_MQ_MAZE_PATH_FIRST_CHEST,           GREEN_RUPEE,                       {},                                                    SpoilerCollectionCheckGroup::GROUP_GERUDO_TRAINING_GROUND);
    locationTable[GERUDO_TRAINING_GROUNDS_MQ_MAZE_RIGHT_SIDE_CHEST]            = ItemLocation::Chest      (RC_GERUDO_TRAINING_GROUND_MQ_MAZE_RIGHT_SIDE_CHEST,              0x0B, 0x08, "Gerudo Training Grounds MQ Maze Right Side Chest",      GERUDO_TRAINING_GROUNDS_MQ_MAZE_RIGHT_SIDE_CHEST,           TREASURE_GAME_GREEN_RUPEE,         {},                                                    SpoilerCollectionCheckGroup::GROUP_GERUDO_TRAINING_GROUND);
    locationTable[GERUDO_TRAINING_GROUNDS_MQ_MAZE_PATH_THIRD_CHEST]            = ItemLocation::Chest      (RC_GERUDO_TRAINING_GROUND_MQ_MAZE_PATH_THIRD_CHEST,              0x0B, 0x09, "Gerudo Training Grounds MQ Maze Path Third Chest",      GERUDO_TRAINING_GROUNDS_MQ_MAZE_PATH_THIRD_CHEST,           TREASURE_GAME_GREEN_RUPEE,         {},                                                    SpoilerCollectionCheckGroup::GROUP_GERUDO_TRAINING_GROUND);
    locationTable[GERUDO_TRAINING_GROUNDS_MQ_MAZE_PATH_SECOND_CHEST]           = ItemLocation::Chest      (RC_GERUDO_TRAINING_GROUND_MQ_MAZE_PATH_SECOND_CHEST,             0x0B, 0x0A, "Gerudo Training Grounds MQ Maze Path Second Chest",     GERUDO_TRAINING_GROUNDS_MQ_MAZE_PATH_SECOND_CHEST,          RED_RUPEE,                         {},                                                    SpoilerCollectionCheckGroup::GROUP_GERUDO_TRAINING_GROUND);
    locationTable[GERUDO_TRAINING_GROUNDS_MQ_HIDDEN_CEILING_CHEST]             = ItemLocation::Chest      (RC_GERUDO_TRAINING_GROUND_MQ_HIDDEN_CEILING_CHEST,               0x0B, 0x0B, "Gerudo Training Grounds MQ Hidden Ceiling Chest",       GERUDO_TRAINING_GROUNDS_MQ_HIDDEN_CEILING_CHEST,            PURPLE_RUPEE,                      {},                                                    SpoilerCollectionCheckGroup::GROUP_GERUDO_TRAINING_GROUND);
    locationTable[GERUDO_TRAINING_GROUNDS_MQ_UNDERWATER_SILVER_RUPEE_CHEST]    = ItemLocation::Chest      (RC_GERUDO_TRAINING_GROUND_MQ_UNDERWATER_SILVER_RUPEE_CHEST,      0x0B, 0x0D, "Gerudo Training Grounds MQ Underwater Silver Rupee Chest",GERUDO_TRAINING_GROUNDS_MQ_UNDERWATER_SILVER_RUPEE_CHEST, TREASURE_GAME_GREEN_RUPEE,         {Category::cVanillaSmallKey},                          SpoilerCollectionCheckGroup::GROUP_GERUDO_TRAINING_GROUND);
    locationTable[GERUDO_TRAINING_GROUNDS_MQ_HEAVY_BLOCK_CHEST]                = ItemLocation::Chest      (RC_GERUDO_TRAINING_GROUND_MQ_HEAVY_BLOCK_CHEST,                  0x0B, 0x02, "Gerudo Training Grounds MQ Heavy Block Chest",          GERUDO_TRAINING_GROUNDS_MQ_HEAVY_BLOCK_CHEST,               PURPLE_RUPEE,                      {},                                                    SpoilerCollectionCheckGroup::GROUP_GERUDO_TRAINING_GROUND);

    //Ganons Castle Shared
    locationTable[GANONS_TOWER_BOSS_KEY_CHEST]                                 = ItemLocation::Chest      (RC_GANONS_TOWER_BOSS_KEY_CHEST,                                  0x0A, 0x0B, "Ganon's Tower Boss Key Chest",                          GANONS_TOWER_BOSS_KEY_CHEST,                           GANONS_CASTLE_BOSS_KEY,  {},                                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);
    //Ganons Castle Vanilla
    locationTable[GANONS_CASTLE_FOREST_TRIAL_CHEST]                            = ItemLocation::Chest      (RC_GANONS_CASTLE_FOREST_TRIAL_CHEST,                             0x0D, 0x09, "Ganon's Castle Forest Trial Chest",                     GANONS_CASTLE_FOREST_TRIAL_CHEST,                      BLUE_RUPEE,              {},                                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);
    locationTable[GANONS_CASTLE_WATER_TRIAL_LEFT_CHEST]                        = ItemLocation::Chest      (RC_GANONS_CASTLE_WATER_TRIAL_LEFT_CHEST,                         0x0D, 0x07, "Ganon's Castle Water Trial Left Chest",                 GANONS_CASTLE_WATER_TRIAL_LEFT_CHEST,                  ICE_TRAP,                {},                                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);
    locationTable[GANONS_CASTLE_WATER_TRIAL_RIGHT_CHEST]                       = ItemLocation::Chest      (RC_GANONS_CASTLE_WATER_TRIAL_RIGHT_CHEST,                        0x0D, 0x06, "Ganon's Castle Water Trial Right Chest",                GANONS_CASTLE_WATER_TRIAL_RIGHT_CHEST,                 RECOVERY_HEART,          {},                                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);
    locationTable[GANONS_CASTLE_SHADOW_TRIAL_FRONT_CHEST]                      = ItemLocation::Chest      (RC_GANONS_CASTLE_SHADOW_TRIAL_FRONT_CHEST,                       0x0D, 0x08, "Ganon's Castle Shadow Trial Front Chest",               GANONS_CASTLE_SHADOW_TRIAL_FRONT_CHEST,                BLUE_RUPEE,              {},                                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);
    locationTable[GANONS_CASTLE_SHADOW_TRIAL_GOLDEN_GAUNTLETS_CHEST]           = ItemLocation::Chest      (RC_GANONS_CASTLE_SHADOW_TRIAL_GOLDEN_GAUNTLETS_CHEST,            0x0D, 0x05, "Ganon's Castle Shadow Trial Golden Gauntlets Chest",    GANONS_CASTLE_SHADOW_TRIAL_GOLDEN_GAUNTLETS_CHEST,     PROGRESSIVE_STRENGTH,    {},                                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);
    locationTable[GANONS_CASTLE_SPIRIT_TRIAL_CRYSTAL_SWITCH_CHEST]             = ItemLocation::Chest      (RC_GANONS_CASTLE_SPIRIT_TRIAL_CRYSTAL_SWITCH_CHEST,              0x0D, 0x12, "Ganon's Castle Spirit Trial Crystal Switch Chest",      GANONS_CASTLE_SPIRIT_TRIAL_CRYSTAL_SWITCH_CHEST,       BOMBCHU_20,              {},                                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);
    locationTable[GANONS_CASTLE_SPIRIT_TRIAL_INVISIBLE_CHEST]                  = ItemLocation::Chest      (RC_GANONS_CASTLE_SPIRIT_TRIAL_INVISIBLE_CHEST,                   0x0D, 0x14, "Ganon's Castle Spirit Trial Invisible Chest",           GANONS_CASTLE_SPIRIT_TRIAL_INVISIBLE_CHEST,            ARROWS_10,               {},                                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);
    locationTable[GANONS_CASTLE_LIGHT_TRIAL_FIRST_LEFT_CHEST]                  = ItemLocation::Chest      (RC_GANONS_CASTLE_LIGHT_TRIAL_FIRST_LEFT_CHEST,                   0x0D, 0x0C, "Ganon's Castle Light Trial First Left Chest",           GANONS_CASTLE_LIGHT_TRIAL_FIRST_LEFT_CHEST,            BLUE_RUPEE,              {},                                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);
    locationTable[GANONS_CASTLE_LIGHT_TRIAL_SECOND_LEFT_CHEST]                 = ItemLocation::Chest      (RC_GANONS_CASTLE_LIGHT_TRIAL_SECOND_LEFT_CHEST,                  0x0D, 0x0B, "Ganon's Castle Light Trial Second Left Chest",          GANONS_CASTLE_LIGHT_TRIAL_SECOND_LEFT_CHEST,           ICE_TRAP,                {},                                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);
    locationTable[GANONS_CASTLE_LIGHT_TRIAL_THIRD_LEFT_CHEST]                  = ItemLocation::Chest      (RC_GANONS_CASTLE_LIGHT_TRIAL_THIRD_LEFT_CHEST,                   0x0D, 0x0D, "Ganon's Castle Light Trial Third Left Chest",           GANONS_CASTLE_LIGHT_TRIAL_THIRD_LEFT_CHEST,            RECOVERY_HEART,          {},                                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);
    locationTable[GANONS_CASTLE_LIGHT_TRIAL_FIRST_RIGHT_CHEST]                 = ItemLocation::Chest      (RC_GANONS_CASTLE_LIGHT_TRIAL_FIRST_RIGHT_CHEST,                  0x0D, 0x0E, "Ganon's Castle Light Trial First Right Chest",          GANONS_CASTLE_LIGHT_TRIAL_FIRST_RIGHT_CHEST,           ICE_TRAP,                {},                                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);
    locationTable[GANONS_CASTLE_LIGHT_TRIAL_SECOND_RIGHT_CHEST]                = ItemLocation::Chest      (RC_GANONS_CASTLE_LIGHT_TRIAL_SECOND_RIGHT_CHEST,                 0x0D, 0x0A, "Ganon's Castle Light Trial Second Right Chest",         GANONS_CASTLE_LIGHT_TRIAL_SECOND_RIGHT_CHEST,          ARROWS_30,               {},                                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);
    locationTable[GANONS_CASTLE_LIGHT_TRIAL_THIRD_RIGHT_CHEST]                 = ItemLocation::Chest      (RC_GANONS_CASTLE_LIGHT_TRIAL_THIRD_RIGHT_CHEST,                  0x0D, 0x0F, "Ganon's Castle Light Trial Third Right Chest",          GANONS_CASTLE_LIGHT_TRIAL_THIRD_RIGHT_CHEST,           ICE_TRAP,                {},                                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);
    locationTable[GANONS_CASTLE_LIGHT_TRIAL_INVISIBLE_ENEMIES_CHEST]           = ItemLocation::Chest      (RC_GANONS_CASTLE_LIGHT_TRIAL_INVISIBLE_ENEMIES_CHEST,            0x0D, 0x10, "Ganon's Castle Light Trial Invisible Enemies Chest",    GANONS_CASTLE_LIGHT_TRIAL_INVISIBLE_ENEMIES_CHEST,     GANONS_CASTLE_SMALL_KEY, {Category::cVanillaSmallKey},                                         SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);
    locationTable[GANONS_CASTLE_LIGHT_TRIAL_LULLABY_CHEST]                     = ItemLocation::Chest      (RC_GANONS_CASTLE_LIGHT_TRIAL_LULLABY_CHEST,                      0x0D, 0x11, "Ganon's Castle Light Trial Lullaby Chest",              GANONS_CASTLE_LIGHT_TRIAL_LULLABY_CHEST,               GANONS_CASTLE_SMALL_KEY, {Category::cVanillaSmallKey},                                         SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);
    locationTable[GANONS_CASTLE_DEKU_SCRUB_CENTER_LEFT]                        = ItemLocation::Base       (RC_GANONS_CASTLE_DEKU_SCRUB_CENTER_LEFT,                         0x0D,       "Ganon's Castle Deku Scrub Center-Left",                 GANONS_CASTLE_DEKU_SCRUB_CENTER_LEFT,                  BUY_BOMBS_535,           {Category::cDekuScrub},              SpoilerCollectionCheck::Scrub(), SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);
    locationTable[GANONS_CASTLE_DEKU_SCRUB_CENTER_RIGHT]                       = ItemLocation::Base       (RC_GANONS_CASTLE_DEKU_SCRUB_CENTER_RIGHT,                        0x0D,       "Ganon's Castle Deku Scrub Center-Right",                GANONS_CASTLE_DEKU_SCRUB_CENTER_RIGHT,                 BUY_ARROWS_30,           {Category::cDekuScrub},              SpoilerCollectionCheck::Scrub(), SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);
    locationTable[GANONS_CASTLE_DEKU_SCRUB_RIGHT]                              = ItemLocation::Base       (RC_GANONS_CASTLE_DEKU_SCRUB_RIGHT,                               0x0D,       "Ganon's Castle Deku Scrub Right",                       GANONS_CASTLE_DEKU_SCRUB_RIGHT,                        BUY_RED_POTION_30,       {Category::cDekuScrub},              SpoilerCollectionCheck::Scrub(), SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);
    locationTable[GANONS_CASTLE_DEKU_SCRUB_LEFT]                               = ItemLocation::Base       (RC_GANONS_CASTLE_DEKU_SCRUB_LEFT,                                0x0D,       "Ganon's Castle Deku Scrub Left",                        GANONS_CASTLE_DEKU_SCRUB_LEFT,                         BUY_GREEN_POTION,        {Category::cDekuScrub},              SpoilerCollectionCheck::Scrub(), SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);
    //Ganons Castle MQ
    locationTable[GANONS_CASTLE_MQ_WATER_TRIAL_CHEST]                          = ItemLocation::Chest      (RC_GANONS_CASTLE_MQ_WATER_TRIAL_CHEST,                           0x0D, 0x01, "Ganon's Castle MQ Water Trial Chest",                   GANONS_CASTLE_MQ_WATER_TRIAL_CHEST,                    RED_RUPEE,               {},                                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);
    locationTable[GANONS_CASTLE_MQ_FOREST_TRIAL_EYE_SWITCH_CHEST]              = ItemLocation::Chest      (RC_GANONS_CASTLE_MQ_FOREST_TRIAL_EYE_SWITCH_CHEST,               0x0D, 0x02, "Ganon's Castle MQ Forest Trial Eye Switch Chest",       GANONS_CASTLE_MQ_FOREST_TRIAL_EYE_SWITCH_CHEST,        ARROWS_10,               {},                                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);
    locationTable[GANONS_CASTLE_MQ_FOREST_TRIAL_FROZEN_EYE_SWITCH_CHEST]       = ItemLocation::Chest      (RC_GANONS_CASTLE_MQ_FOREST_TRIAL_FROZEN_EYE_SWITCH_CHEST,        0x0D, 0x03, "Ganon's Castle MQ Forest Trial Frozen Eye Switch Chest",GANONS_CASTLE_MQ_FOREST_TRIAL_FROZEN_EYE_SWITCH_CHEST, BOMBS_5,                 {},                                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);
    locationTable[GANONS_CASTLE_MQ_LIGHT_TRIAL_LULLABY_CHEST]                  = ItemLocation::Chest      (RC_GANONS_CASTLE_MQ_LIGHT_TRIAL_LULLABY_CHEST,                   0x0D, 0x04, "Ganon's Castle MQ Light Trial Lullaby Chest",           GANONS_CASTLE_MQ_LIGHT_TRIAL_LULLABY_CHEST,            RECOVERY_HEART,          {},                                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);
    locationTable[GANONS_CASTLE_MQ_SHADOW_TRIAL_BOMB_FLOWER_CHEST]             = ItemLocation::Chest      (RC_GANONS_CASTLE_MQ_SHADOW_TRIAL_BOMB_FLOWER_CHEST,              0x0D, 0x00, "Ganon's Castle MQ Shadow Trial Bomb Flower Chest",      GANONS_CASTLE_MQ_SHADOW_TRIAL_BOMB_FLOWER_CHEST,       ARROWS_10,               {},                                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);
    locationTable[GANONS_CASTLE_MQ_SHADOW_TRIAL_EYE_SWITCH_CHEST]              = ItemLocation::Chest      (RC_GANONS_CASTLE_MQ_SHADOW_TRIAL_EYE_SWITCH_CHEST,               0x0D, 0x05, "Ganon's Castle MQ Shadow Trial Eye Switch Chest",       GANONS_CASTLE_MQ_SHADOW_TRIAL_EYE_SWITCH_CHEST,        GANONS_CASTLE_SMALL_KEY, {Category::cVanillaSmallKey},                                         SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);
    locationTable[GANONS_CASTLE_MQ_SPIRIT_TRIAL_GOLDEN_GAUNTLETS_CHEST]        = ItemLocation::Chest      (RC_GANONS_CASTLE_MQ_SPIRIT_TRIAL_GOLDEN_GAUNTLETS_CHEST,         0x0D, 0x06, "Ganon's Castle MQ Spirit Trial Golden Gauntlets Chest", GANONS_CASTLE_MQ_SPIRIT_TRIAL_GOLDEN_GAUNTLETS_CHEST,  PROGRESSIVE_STRENGTH,    {},                                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);
    locationTable[GANONS_CASTLE_MQ_SPIRIT_TRIAL_SUN_BACK_RIGHT_CHEST]          = ItemLocation::Chest      (RC_GANONS_CASTLE_MQ_SPIRIT_TRIAL_SUN_BACK_RIGHT_CHEST,           0x0D, 0x07, "Ganon's Castle MQ Spirit Trial Sun Back Right Chest",   GANONS_CASTLE_MQ_SPIRIT_TRIAL_SUN_BACK_RIGHT_CHEST,    RECOVERY_HEART,          {},                                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);
    locationTable[GANONS_CASTLE_MQ_SPIRIT_TRIAL_SUN_BACK_LEFT_CHEST]           = ItemLocation::Chest      (RC_GANONS_CASTLE_MQ_SPIRIT_TRIAL_SUN_BACK_LEFT_CHEST,            0x0D, 0x08, "Ganon's Castle MQ Spirit Trial Sun Back Left Chest",    GANONS_CASTLE_MQ_SPIRIT_TRIAL_SUN_BACK_LEFT_CHEST,     GANONS_CASTLE_SMALL_KEY, {Category::cVanillaSmallKey},                                         SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);
    locationTable[GANONS_CASTLE_MQ_SPIRIT_TRIAL_SUN_FRONT_LEFT_CHEST]          = ItemLocation::Chest      (RC_GANONS_CASTLE_MQ_SPIRIT_TRIAL_SUN_FRONT_LEFT_CHEST,           0x0D, 0x09, "Ganon's Castle MQ Spirit Trial Sun Front Left Chest",   GANONS_CASTLE_MQ_SPIRIT_TRIAL_SUN_FRONT_LEFT_CHEST,    RECOVERY_HEART,          {},                                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);
    locationTable[GANONS_CASTLE_MQ_SPIRIT_TRIAL_FIRST_CHEST]                   = ItemLocation::Chest      (RC_GANONS_CASTLE_MQ_SPIRIT_TRIAL_FIRST_CHEST,                    0x0D, 0x0A, "Ganon's Castle MQ Spirit Trial First Chest",            GANONS_CASTLE_MQ_SPIRIT_TRIAL_FIRST_CHEST,             BOMBCHU_10,              {},                                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);
    locationTable[GANONS_CASTLE_MQ_SPIRIT_TRIAL_INVISIBLE_CHEST]               = ItemLocation::Chest      (RC_GANONS_CASTLE_MQ_SPIRIT_TRIAL_INVISIBLE_CHEST,                0x0D, 0x14, "Ganon's Castle MQ Spirit Trial Invisible Chest",        GANONS_CASTLE_MQ_SPIRIT_TRIAL_INVISIBLE_CHEST,         ARROWS_10,               {},                                                                   SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);
    locationTable[GANONS_CASTLE_MQ_FOREST_TRIAL_FREESTANDING_KEY]              = ItemLocation::Collectable(RC_GANONS_CASTLE_MQ_FOREST_TRIAL_FREESTANDING_KEY,               0x0D, 0x01, "Ganon's Castle MQ Forest Trial Freestanding Key",       GANONS_CASTLE_MQ_FOREST_TRIAL_FREESTANDING_KEY,        GANONS_CASTLE_SMALL_KEY, {Category::cVanillaSmallKey},                                         SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);
    locationTable[GANONS_CASTLE_MQ_DEKU_SCRUB_RIGHT]                           = ItemLocation::Base       (RC_GANONS_CASTLE_MQ_DEKU_SCRUB_RIGHT,                            0x0D,       "Ganon's Castle MQ Deku Scrub Right",                    GANONS_CASTLE_MQ_DEKU_SCRUB_RIGHT,                     BUY_DEKU_NUT_5,          {Category::cDekuScrub},              SpoilerCollectionCheck::Scrub(), SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);
    locationTable[GANONS_CASTLE_MQ_DEKU_SCRUB_CENTER_LEFT]                     = ItemLocation::Base       (RC_GANONS_CASTLE_MQ_DEKU_SCRUB_CENTER_LEFT,                      0x0D,       "Ganon's Castle MQ Deku Scrub Center-Left",              GANONS_CASTLE_MQ_DEKU_SCRUB_CENTER_LEFT,               BUY_BOMBS_535,           {Category::cDekuScrub},              SpoilerCollectionCheck::Scrub(), SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);
    locationTable[GANONS_CASTLE_MQ_DEKU_SCRUB_CENTER]                          = ItemLocation::Base       (RC_GANONS_CASTLE_MQ_DEKU_SCRUB_CENTER,                           0x0D,       "Ganon's Castle MQ Deku Scrub Center",                   GANONS_CASTLE_MQ_DEKU_SCRUB_CENTER,                    BUY_ARROWS_30,           {Category::cDekuScrub},              SpoilerCollectionCheck::Scrub(), SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);
    locationTable[GANONS_CASTLE_MQ_DEKU_SCRUB_CENTER_RIGHT]                    = ItemLocation::Base       (RC_GANONS_CASTLE_MQ_DEKU_SCRUB_CENTER_RIGHT,                     0x0D,       "Ganon's Castle MQ Deku Scrub Center-Right",             GANONS_CASTLE_MQ_DEKU_SCRUB_CENTER_RIGHT,              BUY_RED_POTION_30,       {Category::cDekuScrub},              SpoilerCollectionCheck::Scrub(), SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);
    locationTable[GANONS_CASTLE_MQ_DEKU_SCRUB_LEFT]                            = ItemLocation::Base       (RC_GANONS_CASTLE_MQ_DEKU_SCRUB_LEFT,                             0x0D,       "Ganon's Castle MQ Deku Scrub Left",                     GANONS_CASTLE_MQ_DEKU_SCRUB_LEFT,                      BUY_GREEN_POTION,        {Category::cDekuScrub},              SpoilerCollectionCheck::Scrub(), SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);

    /*-------------------------------
       --- GOLD SKULLTULA TOKENS ---
      -------------------------------*/

    //Dungeons
    locationTable[DEKU_TREE_GS_BASEMENT_BACK_ROOM]                   = ItemLocation::GSToken(RC_DEKU_TREE_GS_BASEMENT_BACK_ROOM,                                            0x00, 0x01, "Deku Tree GS Basement Back Room",                  DEKU_TREE_GS_BASEMENT_BACK_ROOM,                  {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_DEKU_TREE);
    locationTable[DEKU_TREE_GS_BASEMENT_GATE]                        = ItemLocation::GSToken(RC_DEKU_TREE_GS_BASEMENT_GATE,                                                 0x00, 0x02, "Deku Tree GS Basement Gate",                       DEKU_TREE_GS_BASEMENT_GATE,                       {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_DEKU_TREE);
    locationTable[DEKU_TREE_GS_BASEMENT_VINES]                       = ItemLocation::GSToken(RC_DEKU_TREE_GS_BASEMENT_VINES,                                                0x00, 0x04, "Deku Tree GS Basement Vines",                      DEKU_TREE_GS_BASEMENT_VINES,                      {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_DEKU_TREE);
    locationTable[DEKU_TREE_GS_COMPASS_ROOM]                         = ItemLocation::GSToken(RC_DEKU_TREE_GS_COMPASS_ROOM,                                                  0x00, 0x08, "Deku Tree GS Compass Room",                        DEKU_TREE_GS_COMPASS_ROOM,                        {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_DEKU_TREE);
                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    locationTable[DEKU_TREE_MQ_GS_LOBBY]                             = ItemLocation::GSToken(RC_DEKU_TREE_MQ_GS_LOBBY,                                                      0x00, 0x02, "Deku Tree MQ GS Lobby",                            DEKU_TREE_MQ_GS_LOBBY,                            {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_DEKU_TREE);
    locationTable[DEKU_TREE_MQ_GS_COMPASS_ROOM]                      = ItemLocation::GSToken(RC_DEKU_TREE_MQ_GS_COMPASS_ROOM,                                               0x00, 0x08, "Deku Tree MQ GS Compass Room",                     DEKU_TREE_MQ_GS_COMPASS_ROOM,                     {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_DEKU_TREE);
    locationTable[DEKU_TREE_MQ_GS_BASEMENT_GRAVES_ROOM]              = ItemLocation::GSToken(RC_DEKU_TREE_MQ_GS_BASEMENT_GRAVES_ROOM,                                       0x00, 0x04, "Deku Tree MQ GS Basement Graves Room",             DEKU_TREE_MQ_GS_BASEMENT_GRAVES_ROOM,             {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_DEKU_TREE);
    locationTable[DEKU_TREE_MQ_GS_BASEMENT_BACK_ROOM]                = ItemLocation::GSToken(RC_DEKU_TREE_MQ_GS_BASEMENT_BACK_ROOM,                                         0x00, 0x01, "Deku Tree MQ GS Basement Back Room",               DEKU_TREE_MQ_GS_BASEMENT_BACK_ROOM,               {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_DEKU_TREE);
                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    locationTable[DODONGOS_CAVERN_GS_VINES_ABOVE_STAIRS]             = ItemLocation::GSToken(RC_DODONGOS_CAVERN_GS_VINES_ABOVE_STAIRS,                                      0x01, 0x01, "Dodongos Cavern GS Vines Above Stairs",            DODONGOS_CAVERN_GS_VINES_ABOVE_STAIRS,            {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_DODONGOS_CAVERN);
    locationTable[DODONGOS_CAVERN_GS_SCARECROW]                      = ItemLocation::GSToken(RC_DODONGOS_CAVERN_GS_SCARECROW,                                               0x01, 0x02, "Dodongos Cavern GS Scarecrow",                     DODONGOS_CAVERN_GS_SCARECROW,                     {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_DODONGOS_CAVERN);
    locationTable[DODONGOS_CAVERN_GS_ALCOVE_ABOVE_STAIRS]            = ItemLocation::GSToken(RC_DODONGOS_CAVERN_GS_ALCOVE_ABOVE_STAIRS,                                     0x01, 0x04, "Dodongos Cavern GS Alcove Above Stairs",           DODONGOS_CAVERN_GS_ALCOVE_ABOVE_STAIRS,           {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_DODONGOS_CAVERN);
    locationTable[DODONGOS_CAVERN_GS_BACK_ROOM]                      = ItemLocation::GSToken(RC_DODONGOS_CAVERN_GS_BACK_ROOM,                                               0x01, 0x08, "Dodongos Cavern GS Back Room",                     DODONGOS_CAVERN_GS_BACK_ROOM,                     {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_DODONGOS_CAVERN);
    locationTable[DODONGOS_CAVERN_GS_SIDE_ROOM_NEAR_LOWER_LIZALFOS]  = ItemLocation::GSToken(RC_DODONGOS_CAVERN_GS_SIDE_ROOM_NEAR_LOWER_LIZALFOS,                           0x01, 0x10, "Dodongos Cavern GS Side Room Near Lower Lizalfos", DODONGOS_CAVERN_GS_SIDE_ROOM_NEAR_LOWER_LIZALFOS, {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_DODONGOS_CAVERN);
                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    locationTable[DODONGOS_CAVERN_MQ_GS_SCRUB_ROOM]                  = ItemLocation::GSToken(RC_DODONGOS_CAVERN_MQ_GS_SCRUB_ROOM,                                           0x01, 0x02, "Dodongos Cavern MQ GS Scrub Room",                 DODONGOS_CAVERN_MQ_GS_SCRUB_ROOM,                 {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_DODONGOS_CAVERN);
    locationTable[DODONGOS_CAVERN_MQ_GS_SONG_OF_TIME_BLOCK_ROOM]     = ItemLocation::GSToken(RC_DODONGOS_CAVERN_MQ_GS_SONG_OF_TIME_BLOCK_ROOM,                              0x01, 0x08, "Dodongos Cavern MQ GS Song of Time Block Room",    DODONGOS_CAVERN_MQ_GS_SONG_OF_TIME_BLOCK_ROOM,    {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_DODONGOS_CAVERN);
    locationTable[DODONGOS_CAVERN_MQ_GS_LIZALFOS_ROOM]               = ItemLocation::GSToken(RC_DODONGOS_CAVERN_MQ_GS_LIZALFOS_ROOM,                                        0x01, 0x04, "Dodongos Cavern MQ GS Lizalfos Room",              DODONGOS_CAVERN_MQ_GS_LIZALFOS_ROOM,              {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_DODONGOS_CAVERN);
    locationTable[DODONGOS_CAVERN_MQ_GS_LARVAE_ROOM]                 = ItemLocation::GSToken(RC_DODONGOS_CAVERN_MQ_GS_LARVAE_ROOM,                                          0x01, 0x10, "Dodongos Cavern MQ GS Larvae Room",                DODONGOS_CAVERN_MQ_GS_LARVAE_ROOM,                {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_DODONGOS_CAVERN);
    locationTable[DODONGOS_CAVERN_MQ_GS_BACK_AREA]                   = ItemLocation::GSToken(RC_DODONGOS_CAVERN_MQ_GS_BACK_AREA,                                            0x01, 0x01, "Dodongos Cavern MQ GS Back Room",                  DODONGOS_CAVERN_MQ_GS_BACK_AREA,                  {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_DODONGOS_CAVERN);
                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    locationTable[JABU_JABUS_BELLY_GS_LOBBY_BASEMENT_LOWER]          = ItemLocation::GSToken(RC_JABU_JABUS_BELLY_GS_LOBBY_BASEMENT_LOWER,                                   0x02, 0x01, "Jabu Jabus Belly GS Lobby Basement Lower",         JABU_JABUS_BELLY_GS_LOBBY_BASEMENT_LOWER,         {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_JABUJABUS_BELLY);
    locationTable[JABU_JABUS_BELLY_GS_LOBBY_BASEMENT_UPPER]          = ItemLocation::GSToken(RC_JABU_JABUS_BELLY_GS_LOBBY_BASEMENT_UPPER,                                   0x02, 0x02, "Jabu Jabus Belly GS Lobby Basement Upper",         JABU_JABUS_BELLY_GS_LOBBY_BASEMENT_UPPER,         {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_JABUJABUS_BELLY);
    locationTable[JABU_JABUS_BELLY_GS_NEAR_BOSS]                     = ItemLocation::GSToken(RC_JABU_JABUS_BELLY_GS_NEAR_BOSS,                                              0x02, 0x04, "Jabu Jabus Belly GS Near Boss",                    JABU_JABUS_BELLY_GS_NEAR_BOSS,                    {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_JABUJABUS_BELLY);
    locationTable[JABU_JABUS_BELLY_GS_WATER_SWITCH_ROOM]             = ItemLocation::GSToken(RC_JABU_JABUS_BELLY_GS_WATER_SWITCH_ROOM,                                      0x02, 0x08, "Jabu Jabus Belly GS Water Switch Room",            JABU_JABUS_BELLY_GS_WATER_SWITCH_ROOM,            {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_JABUJABUS_BELLY);
                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    locationTable[JABU_JABUS_BELLY_MQ_GS_TAILPASARAN_ROOM]           = ItemLocation::GSToken(RC_JABU_JABUS_BELLY_MQ_GS_TAILPASARAN_ROOM,                                    0x02, 0x04, "Jabu Jabus Belly MQ GS Tail Parasan Room",         JABU_JABUS_BELLY_MQ_GS_TAILPASARAN_ROOM,          {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_JABUJABUS_BELLY);
    locationTable[JABU_JABUS_BELLY_MQ_GS_INVISIBLE_ENEMIES_ROOM]     = ItemLocation::GSToken(RC_JABU_JABUS_BELLY_MQ_GS_INVISIBLE_ENEMIES_ROOM,                              0x02, 0x08, "Jabu Jabus Belly MQ GS Invisible Enemies Room",    JABU_JABUS_BELLY_MQ_GS_INVISIBLE_ENEMIES_ROOM,    {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_JABUJABUS_BELLY);
    locationTable[JABU_JABUS_BELLY_MQ_GS_BOOMERANG_CHEST_ROOM]       = ItemLocation::GSToken(RC_JABU_JABUS_BELLY_MQ_GS_BOOMERANG_CHEST_ROOM,                                0x02, 0x01, "Jabu Jabus Belly MQ GS Boomerang Chest Room",      JABU_JABUS_BELLY_MQ_GS_BOOMERANG_CHEST_ROOM,      {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_JABUJABUS_BELLY);
    locationTable[JABU_JABUS_BELLY_MQ_GS_NEAR_BOSS]                  = ItemLocation::GSToken(RC_JABU_JABUS_BELLY_MQ_GS_NEAR_BOSS,                                           0x02, 0x02, "Jabu Jabus Belly MQ GS Near Boss",                 JABU_JABUS_BELLY_MQ_GS_NEAR_BOSS,                 {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_JABUJABUS_BELLY);
                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    locationTable[FOREST_TEMPLE_GS_RAISED_ISLAND_COURTYARD]          = ItemLocation::GSToken(RC_FOREST_TEMPLE_GS_RAISED_ISLAND_COURTYARD,                                   0x03, 0x01, "Forest Temple GS Raised Island Courtyard",         FOREST_TEMPLE_GS_RAISED_ISLAND_COURTYARD,         {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_FOREST_TEMPLE);
    locationTable[FOREST_TEMPLE_GS_FIRST_ROOM]                       = ItemLocation::GSToken(RC_FOREST_TEMPLE_GS_FIRST_ROOM,                                                0x03, 0x02, "Forest Temple GS First Room",                      FOREST_TEMPLE_GS_FIRST_ROOM,                      {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_FOREST_TEMPLE);
    locationTable[FOREST_TEMPLE_GS_LEVEL_ISLAND_COURTYARD]           = ItemLocation::GSToken(RC_FOREST_TEMPLE_GS_LEVEL_ISLAND_COURTYARD,                                    0x03, 0x04, "Forest Temple GS Level Island Courtyard",          FOREST_TEMPLE_GS_LEVEL_ISLAND_COURTYARD,          {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_FOREST_TEMPLE);
    locationTable[FOREST_TEMPLE_GS_LOBBY]                            = ItemLocation::GSToken(RC_FOREST_TEMPLE_GS_LOBBY,                                                     0x03, 0x08, "Forest Temple GS Lobby",                           FOREST_TEMPLE_GS_LOBBY,                           {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_FOREST_TEMPLE);
    locationTable[FOREST_TEMPLE_GS_BASEMENT]                         = ItemLocation::GSToken(RC_FOREST_TEMPLE_GS_BASEMENT,                                                  0x03, 0x10, "Forest Temple GS Basement",                        FOREST_TEMPLE_GS_BASEMENT,                        {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_FOREST_TEMPLE);
                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    locationTable[FOREST_TEMPLE_MQ_GS_FIRST_HALLWAY]                 = ItemLocation::GSToken(RC_FOREST_TEMPLE_MQ_GS_FIRST_HALLWAY,                                          0x03, 0x02, "Forest Temple MQ GS First Hallway",                FOREST_TEMPLE_MQ_GS_FIRST_HALLWAY,                {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_FOREST_TEMPLE);
    locationTable[FOREST_TEMPLE_MQ_GS_BLOCK_PUSH_ROOM]               = ItemLocation::GSToken(RC_FOREST_TEMPLE_MQ_GS_BLOCK_PUSH_ROOM,                                        0x03, 0x10, "Forest Temple MQ GS Block Push Room",              FOREST_TEMPLE_MQ_GS_BLOCK_PUSH_ROOM,              {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_FOREST_TEMPLE);
    locationTable[FOREST_TEMPLE_MQ_GS_RAISED_ISLAND_COURTYARD]       = ItemLocation::GSToken(RC_FOREST_TEMPLE_MQ_GS_RAISED_ISLAND_COURTYARD,                                0x03, 0x01, "Forest Temple MQ GS Raised Island Courtyard",      FOREST_TEMPLE_MQ_GS_RAISED_ISLAND_COURTYARD,      {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_FOREST_TEMPLE);
    locationTable[FOREST_TEMPLE_MQ_GS_LEVEL_ISLAND_COURTYARD]        = ItemLocation::GSToken(RC_FOREST_TEMPLE_MQ_GS_LEVEL_ISLAND_COURTYARD,                                 0x03, 0x04, "Forest Temple MQ GS Level Island Courtyard",       FOREST_TEMPLE_MQ_GS_LEVEL_ISLAND_COURTYARD,       {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_FOREST_TEMPLE);
    locationTable[FOREST_TEMPLE_MQ_GS_WELL]                          = ItemLocation::GSToken(RC_FOREST_TEMPLE_MQ_GS_WELL,                                                   0x03, 0x08, "Forest Temple MQ GS Well",                         FOREST_TEMPLE_MQ_GS_WELL,                         {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_FOREST_TEMPLE);
                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    locationTable[FIRE_TEMPLE_GS_SONG_OF_TIME_ROOM]                  = ItemLocation::GSToken(RC_FIRE_TEMPLE_GS_SONG_OF_TIME_ROOM,                                           0x04, 0x01, "Fire Temple GS Song of Time Room",                 FIRE_TEMPLE_GS_SONG_OF_TIME_ROOM,                 {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_FIRE_TEMPLE);
    locationTable[FIRE_TEMPLE_GS_BOSS_KEY_LOOP]                      = ItemLocation::GSToken(RC_FIRE_TEMPLE_GS_BOSS_KEY_LOOP,                                               0x04, 0x02, "Fire Temple GS Boss Key Loop",                     FIRE_TEMPLE_GS_BOSS_KEY_LOOP,                     {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_FIRE_TEMPLE);
    locationTable[FIRE_TEMPLE_GS_BOULDER_MAZE]                       = ItemLocation::GSToken(RC_FIRE_TEMPLE_GS_BOULDER_MAZE,                                                0x04, 0x04, "Fire Temple GS Boulder Maze",                      FIRE_TEMPLE_GS_BOULDER_MAZE,                      {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_FIRE_TEMPLE);
    locationTable[FIRE_TEMPLE_GS_SCARECROW_TOP]                      = ItemLocation::GSToken(RC_FIRE_TEMPLE_GS_SCARECROW_TOP,                                               0x04, 0x08, "Fire Temple GS Scarecrow Top",                     FIRE_TEMPLE_GS_SCARECROW_TOP,                     {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_FIRE_TEMPLE);
    locationTable[FIRE_TEMPLE_GS_SCARECROW_CLIMB]                    = ItemLocation::GSToken(RC_FIRE_TEMPLE_GS_SCARECROW_CLIMB,                                             0x04, 0x10, "Fire Temple GS Scarecrow Climb",                   FIRE_TEMPLE_GS_SCARECROW_CLIMB,                   {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_FIRE_TEMPLE);
                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    locationTable[FIRE_TEMPLE_MQ_GS_ABOVE_FIRE_WALL_MAZE]            = ItemLocation::GSToken(RC_FIRE_TEMPLE_MQ_GS_ABOVE_FIRE_WALL_MAZE,                                     0x04, 0x02, "Fire Temple MQ GS Above Fire Wall Maze",           FIRE_TEMPLE_MQ_GS_ABOVE_FIRE_WALL_MAZE,           {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_FIRE_TEMPLE);
    locationTable[FIRE_TEMPLE_MQ_GS_FIRE_WALL_MAZE_CENTER]           = ItemLocation::GSToken(RC_FIRE_TEMPLE_MQ_GS_FIRE_WALL_MAZE_CENTER,                                    0x04, 0x08, "Fire Temple MQ GS Fire Wall Maze Center",          FIRE_TEMPLE_MQ_GS_FIRE_WALL_MAZE_CENTER,          {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_FIRE_TEMPLE);
    locationTable[FIRE_TEMPLE_MQ_GS_BIG_LAVA_ROOM_OPEN_DOOR]         = ItemLocation::GSToken(RC_FIRE_TEMPLE_MQ_GS_BIG_LAVA_ROOM_OPEN_DOOR,                                  0x04, 0x01, "Fire Temple MQ GS Big Lava Room Open Door",        FIRE_TEMPLE_MQ_GS_BIG_LAVA_ROOM_OPEN_DOOR,        {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_FIRE_TEMPLE);
    locationTable[FIRE_TEMPLE_MQ_GS_FIRE_WALL_MAZE_SIDE_ROOM]        = ItemLocation::GSToken(RC_FIRE_TEMPLE_MQ_GS_FIRE_WALL_MAZE_SIDE_ROOM,                                 0x04, 0x10, "Fire Temple MQ GS Fire Wall Maze Side Room",       FIRE_TEMPLE_MQ_GS_FIRE_WALL_MAZE_SIDE_ROOM,       {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_FIRE_TEMPLE);
    locationTable[FIRE_TEMPLE_MQ_GS_SKULL_ON_FIRE]                   = ItemLocation::GSToken(RC_FIRE_TEMPLE_MQ_GS_SKULL_ON_FIRE,                                            0x04, 0x04, "Fire Temple MQ GS Skull on Fire",                  FIRE_TEMPLE_MQ_GS_SKULL_ON_FIRE,                  {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_FIRE_TEMPLE);
                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    locationTable[WATER_TEMPLE_GS_BEHIND_GATE]                       = ItemLocation::GSToken(RC_WATER_TEMPLE_GS_BEHIND_GATE,                                                0x05, 0x01, "Water Temple GS Behind Gate",                      WATER_TEMPLE_GS_BEHIND_GATE,                      {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_WATER_TEMPLE);
    locationTable[WATER_TEMPLE_GS_FALLING_PLATFORM_ROOM]             = ItemLocation::GSToken(RC_WATER_TEMPLE_GS_FALLING_PLATFORM_ROOM,                                      0x05, 0x02, "Water Temple GS Falling Platform Room",            WATER_TEMPLE_GS_FALLING_PLATFORM_ROOM,            {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_WATER_TEMPLE);
    locationTable[WATER_TEMPLE_GS_CENTRAL_PILLAR]                    = ItemLocation::GSToken(RC_WATER_TEMPLE_GS_CENTRAL_PILLAR,                                             0x05, 0x04, "Water Temple GS Central Pillar",                   WATER_TEMPLE_GS_CENTRAL_PILLAR,                   {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_WATER_TEMPLE);
    locationTable[WATER_TEMPLE_GS_NEAR_BOSS_KEY_CHEST]               = ItemLocation::GSToken(RC_WATER_TEMPLE_GS_NEAR_BOSS_KEY_CHEST,                                        0x05, 0x08, "Water Temple GS Near Boss Key Chest",              WATER_TEMPLE_GS_NEAR_BOSS_KEY_CHEST,              {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_WATER_TEMPLE);
    locationTable[WATER_TEMPLE_GS_RIVER]                             = ItemLocation::GSToken(RC_WATER_TEMPLE_GS_RIVER,                                                      0x05, 0x10, "Water Temple GS River",                            WATER_TEMPLE_GS_RIVER,                            {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_WATER_TEMPLE);
                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    locationTable[WATER_TEMPLE_MQ_GS_BEFORE_UPPER_WATER_SWITCH]      = ItemLocation::GSToken(RC_WATER_TEMPLE_MQ_GS_BEFORE_UPPER_WATER_SWITCH,                               0x05, 0x04, "Water Temple MQ GS Before Upper Water Switch",     WATER_TEMPLE_MQ_GS_BEFORE_UPPER_WATER_SWITCH,     {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_WATER_TEMPLE);
    locationTable[WATER_TEMPLE_MQ_GS_FREESTANDING_KEY_AREA]          = ItemLocation::GSToken(RC_WATER_TEMPLE_MQ_GS_FREESTANDING_KEY_AREA,                                   0x05, 0x08, "Water Temple MQ GS Freestanding Key Area",         WATER_TEMPLE_MQ_GS_FREESTANDING_KEY_AREA,         {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_WATER_TEMPLE);
    locationTable[WATER_TEMPLE_MQ_GS_LIZALFOS_HALLWAY]               = ItemLocation::GSToken(RC_WATER_TEMPLE_MQ_GS_LIZALFOS_HALLWAY,                                        0x05, 0x01, "Water Temple MQ GS Lizalfos Hallway",              WATER_TEMPLE_MQ_GS_LIZALFOS_HALLWAY,              {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_WATER_TEMPLE);
    locationTable[WATER_TEMPLE_MQ_GS_RIVER]                          = ItemLocation::GSToken(RC_WATER_TEMPLE_MQ_GS_RIVER,                                                   0x05, 0x02, "Water Temple MQ GS River",                         WATER_TEMPLE_MQ_GS_RIVER,                         {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_WATER_TEMPLE);
    locationTable[WATER_TEMPLE_MQ_GS_TRIPLE_WALL_TORCH]              = ItemLocation::GSToken(RC_WATER_TEMPLE_MQ_GS_TRIPLE_WALL_TORCH,                                       0x05, 0x10, "Water Temple MQ GS Triple Wall Torch",             WATER_TEMPLE_MQ_GS_TRIPLE_WALL_TORCH,             {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_WATER_TEMPLE);
                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    locationTable[SPIRIT_TEMPLE_GS_HALL_AFTER_SUN_BLOCK_ROOM]        = ItemLocation::GSToken(RC_SPIRIT_TEMPLE_GS_HALL_AFTER_SUN_BLOCK_ROOM,                                 0x06, 0x01, "Spirit Temple GS Hall After Sun Block Room",       SPIRIT_TEMPLE_GS_HALL_AFTER_SUN_BLOCK_ROOM,       {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_GS_BOULDER_ROOM]                     = ItemLocation::GSToken(RC_SPIRIT_TEMPLE_GS_BOULDER_ROOM,                                              0x06, 0x02, "Spirit Temple GS Boulder Room",                    SPIRIT_TEMPLE_GS_BOULDER_ROOM,                    {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_GS_LOBBY]                            = ItemLocation::GSToken(RC_SPIRIT_TEMPLE_GS_LOBBY,                                                     0x06, 0x04, "Spirit Temple GS Lobby",                           SPIRIT_TEMPLE_GS_LOBBY,                           {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_GS_SUN_ON_FLOOR_ROOM]                = ItemLocation::GSToken(RC_SPIRIT_TEMPLE_GS_SUN_ON_FLOOR_ROOM,                                         0x06, 0x08, "Spirit Temple GS Sun on Floor Room",               SPIRIT_TEMPLE_GS_SUN_ON_FLOOR_ROOM,               {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_GS_METAL_FENCE]                      = ItemLocation::GSToken(RC_SPIRIT_TEMPLE_GS_METAL_FENCE,                                               0x06, 0x10, "Spirit Temple GS Metal Fence",                     SPIRIT_TEMPLE_GS_METAL_FENCE,                     {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    locationTable[SPIRIT_TEMPLE_MQ_GS_SYMPHONY_ROOM]                 = ItemLocation::GSToken(RC_SPIRIT_TEMPLE_MQ_GS_SYMPHONY_ROOM,                                          0x06, 0x08, "Spirit Temple MQ GS Symphony Room",                SPIRIT_TEMPLE_MQ_GS_SYMPHONY_ROOM,                {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_MQ_GS_LEEVER_ROOM]                   = ItemLocation::GSToken(RC_SPIRIT_TEMPLE_MQ_GS_LEEVER_ROOM,                                            0x06, 0x02, "Spirit Temple MQ GS Leever Room",                  SPIRIT_TEMPLE_MQ_GS_LEEVER_ROOM,                  {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_MQ_GS_NINE_THRONES_ROOM_WEST]        = ItemLocation::GSToken(RC_SPIRIT_TEMPLE_MQ_GS_NINE_THRONES_ROOM_WEST,                                 0x06, 0x04, "Spirit Temple MQ GS Nine Thrones Room West",       SPIRIT_TEMPLE_MQ_GS_NINE_THRONES_ROOM_WEST,       {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_MQ_GS_NINE_THRONES_ROOM_NORTH]       = ItemLocation::GSToken(RC_SPIRIT_TEMPLE_MQ_GS_NINE_THRONES_ROOM_NORTH,                                0x06, 0x10, "Spirit Temple MQ GS Nine Thrones Room North",      SPIRIT_TEMPLE_MQ_GS_NINE_THRONES_ROOM_NORTH,      {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SPIRIT_TEMPLE_MQ_GS_SUN_BLOCK_ROOM]                = ItemLocation::GSToken(RC_SPIRIT_TEMPLE_MQ_GS_SUN_BLOCK_ROOM,                                         0x06, 0x01, "Spirit Temple MQ GS Sun Block Room",               SPIRIT_TEMPLE_MQ_GS_SUN_BLOCK_ROOM,               {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    locationTable[SHADOW_TEMPLE_GS_SINGLE_GIANT_POT]                 = ItemLocation::GSToken(RC_SHADOW_TEMPLE_GS_SINGLE_GIANT_POT,                                          0x07, 0x01, "Shadow Temple GS Single Giant Pot",                SHADOW_TEMPLE_GS_SINGLE_GIANT_POT,                {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_GS_FALLING_SPIKES_ROOM]              = ItemLocation::GSToken(RC_SHADOW_TEMPLE_GS_FALLING_SPIKES_ROOM,                                       0x07, 0x02, "Shadow Temple GS Falling Spikes Room",             SHADOW_TEMPLE_GS_FALLING_SPIKES_ROOM,             {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_GS_TRIPLE_GIANT_POT]                 = ItemLocation::GSToken(RC_SHADOW_TEMPLE_GS_TRIPLE_GIANT_POT,                                          0x07, 0x04, "Shadow Temple GS Triple Giant Pot",                SHADOW_TEMPLE_GS_TRIPLE_GIANT_POT,                {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_GS_LIKE_LIKE_ROOM]                   = ItemLocation::GSToken(RC_SHADOW_TEMPLE_GS_LIKE_LIKE_ROOM,                                            0x07, 0x08, "Shadow Temple GS Like Like Room",                  SHADOW_TEMPLE_GS_LIKE_LIKE_ROOM,                  {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_GS_NEAR_SHIP]                        = ItemLocation::GSToken(RC_SHADOW_TEMPLE_GS_NEAR_SHIP,                                                 0x07, 0x10, "Shadow Temple GS Near Ship",                       SHADOW_TEMPLE_GS_NEAR_SHIP,                       {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    locationTable[SHADOW_TEMPLE_MQ_GS_FALLING_SPIKES_ROOM]           = ItemLocation::GSToken(RC_SHADOW_TEMPLE_MQ_GS_FALLING_SPIKES_ROOM,                                    0x07, 0x02, "Shadow Temple MQ GS Falling Spikes Room",          SHADOW_TEMPLE_MQ_GS_FALLING_SPIKES_ROOM,          {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_MQ_GS_WIND_HINT_ROOM]                = ItemLocation::GSToken(RC_SHADOW_TEMPLE_MQ_GS_WIND_HINT_ROOM,                                         0x07, 0x01, "Shadow Temple MQ GS Wind Hint Room",               SHADOW_TEMPLE_MQ_GS_WIND_HINT_ROOM,               {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_MQ_GS_AFTER_WIND]                    = ItemLocation::GSToken(RC_SHADOW_TEMPLE_MQ_GS_AFTER_WIND,                                             0x07, 0x08, "Shadow Temple MQ GS After Wind",                   SHADOW_TEMPLE_MQ_GS_AFTER_WIND,                   {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_MQ_GS_AFTER_SHIP]                    = ItemLocation::GSToken(RC_SHADOW_TEMPLE_MQ_GS_AFTER_SHIP,                                             0x07, 0x10, "Shadow Temple MQ GS After Ship",                   SHADOW_TEMPLE_MQ_GS_AFTER_SHIP,                   {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[SHADOW_TEMPLE_MQ_GS_NEAR_BOSS]                     = ItemLocation::GSToken(RC_SHADOW_TEMPLE_MQ_GS_NEAR_BOSS,                                              0x07, 0x04, "Shadow Temple MQ GS Near Boss",                    SHADOW_TEMPLE_MQ_GS_NEAR_BOSS,                    {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    locationTable[BOTTOM_OF_THE_WELL_GS_LIKE_LIKE_CAGE]              = ItemLocation::GSToken(RC_BOTTOM_OF_THE_WELL_GS_LIKE_LIKE_CAGE,                                       0x08, 0x01, "Bottom of the Well GS Like Like Cage",             BOTTOM_OF_THE_WELL_GS_LIKE_LIKE_CAGE,             {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_BOTTOM_OF_THE_WELL);
    locationTable[BOTTOM_OF_THE_WELL_GS_EAST_INNER_ROOM]             = ItemLocation::GSToken(RC_BOTTOM_OF_THE_WELL_GS_EAST_INNER_ROOM,                                      0x08, 0x02, "Bottom of the Well GS East Inner Room",            BOTTOM_OF_THE_WELL_GS_EAST_INNER_ROOM,            {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_BOTTOM_OF_THE_WELL);
    locationTable[BOTTOM_OF_THE_WELL_GS_WEST_INNER_ROOM]             = ItemLocation::GSToken(RC_BOTTOM_OF_THE_WELL_GS_WEST_INNER_ROOM,                                      0x08, 0x04, "Bottom of the Well GS West Inner Room",            BOTTOM_OF_THE_WELL_GS_WEST_INNER_ROOM,            {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_BOTTOM_OF_THE_WELL);
                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    locationTable[BOTTOM_OF_THE_WELL_MQ_GS_BASEMENT]                 = ItemLocation::GSToken(RC_BOTTOM_OF_THE_WELL_MQ_GS_BASEMENT,                                          0x08, 0x01, "Bottom of the Well MQ GS Basement",                BOTTOM_OF_THE_WELL_MQ_GS_BASEMENT,                {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_BOTTOM_OF_THE_WELL);
    locationTable[BOTTOM_OF_THE_WELL_MQ_GS_COFFIN_ROOM]              = ItemLocation::GSToken(RC_BOTTOM_OF_THE_WELL_MQ_GS_COFFIN_ROOM,                                       0x08, 0x04, "Bottom of the Well MQ GS Coffin Room",             BOTTOM_OF_THE_WELL_MQ_GS_COFFIN_ROOM,             {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_BOTTOM_OF_THE_WELL);
    locationTable[BOTTOM_OF_THE_WELL_MQ_GS_WEST_INNER_ROOM]          = ItemLocation::GSToken(RC_BOTTOM_OF_THE_WELL_MQ_GS_WEST_INNER_ROOM,                                   0x08, 0x02, "Bottom of the Well MQ GS West Inner Room",         BOTTOM_OF_THE_WELL_MQ_GS_WEST_INNER_ROOM,         {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_BOTTOM_OF_THE_WELL);
                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    locationTable[ICE_CAVERN_GS_PUSH_BLOCK_ROOM]                     = ItemLocation::GSToken(RC_ICE_CAVERN_GS_PUSH_BLOCK_ROOM,                                              0x09, 0x01, "Ice Cavern GS Push Block Room",                    ICE_CAVERN_GS_PUSH_BLOCK_ROOM,                    {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_ICE_CAVERN);
    locationTable[ICE_CAVERN_GS_SPINNING_SCYTHE_ROOM]                = ItemLocation::GSToken(RC_ICE_CAVERN_GS_SPINNING_SCYTHE_ROOM,                                         0x09, 0x02, "Ice Cavern GS Spinning Scythe Room",               ICE_CAVERN_GS_SPINNING_SCYTHE_ROOM,               {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_ICE_CAVERN);
    locationTable[ICE_CAVERN_GS_HEART_PIECE_ROOM]                    = ItemLocation::GSToken(RC_ICE_CAVERN_GS_HEART_PIECE_ROOM,                                             0x09, 0x04, "Ice Cavern GS Heart Piece Room",                   ICE_CAVERN_GS_HEART_PIECE_ROOM,                   {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_ICE_CAVERN);
                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    locationTable[ICE_CAVERN_MQ_GS_SCARECROW]                        = ItemLocation::GSToken(RC_ICE_CAVERN_MQ_GS_SCARECROW,                                                 0x09, 0x01, "Ice Cavern MQ GS Scarecrow",                       ICE_CAVERN_MQ_GS_SCARECROW,                       {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_ICE_CAVERN);
    locationTable[ICE_CAVERN_MQ_GS_ICE_BLOCK]                        = ItemLocation::GSToken(RC_ICE_CAVERN_MQ_GS_ICE_BLOCK,                                                 0x09, 0x04, "Ice Cavern MQ GS Ice Block",                       ICE_CAVERN_MQ_GS_ICE_BLOCK,                       {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_ICE_CAVERN);
    locationTable[ICE_CAVERN_MQ_GS_RED_ICE]                          = ItemLocation::GSToken(RC_ICE_CAVERN_MQ_GS_RED_ICE,                                                   0x09, 0x02, "Ice Cavern MQ GS Red Ice",                         ICE_CAVERN_MQ_GS_RED_ICE,                         {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_ICE_CAVERN);
                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    //Overworld
    locationTable[KF_GS_BEAN_PATCH]                                  = ItemLocation::GSToken(RC_KF_GS_BEAN_PATCH,                                                           0x0C, 0x01, "KF GS Bean Patch",                                 KF_GS_BEAN_PATCH,                                 {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_KOKIRI_FOREST);
    locationTable[KF_GS_KNOW_IT_ALL_HOUSE]                           = ItemLocation::GSToken(RC_KF_GS_KNOW_IT_ALL_HOUSE,                                                    0x0C, 0x02, "KF GS Know It All House",                          KF_GS_KNOW_IT_ALL_HOUSE,                          {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_KOKIRI_FOREST);
    locationTable[KF_GS_HOUSE_OF_TWINS]                              = ItemLocation::GSToken(RC_KF_GS_HOUSE_OF_TWINS,                                                       0x0C, 0x04, "KF GS House of Twins",                             KF_GS_HOUSE_OF_TWINS,                             {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_KOKIRI_FOREST);
                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    locationTable[LW_GS_BEAN_PATCH_NEAR_BRIDGE]                      = ItemLocation::GSToken(RC_LW_GS_BEAN_PATCH_NEAR_BRIDGE,                                               0x0D, 0x01, "LW GS Bean Patch Near Bridge",                     LW_GS_BEAN_PATCH_NEAR_BRIDGE,                     {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_LOST_WOODS);
    locationTable[LW_GS_BEAN_PATCH_NEAR_THEATER]                     = ItemLocation::GSToken(RC_LW_GS_BEAN_PATCH_NEAR_THEATER,                                              0x0D, 0x02, "LW GS Bean Patch Near Theater",                    LW_GS_BEAN_PATCH_NEAR_THEATER,                    {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_LOST_WOODS);
    locationTable[LW_GS_ABOVE_THEATER]                               = ItemLocation::GSToken(RC_LW_GS_ABOVE_THEATER,                                                        0x0D, 0x04, "LW GS Above Theater",                              LW_GS_ABOVE_THEATER,                              {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_LOST_WOODS);
    locationTable[SFM_GS]                                            = ItemLocation::GSToken(RC_SFM_GS,                                                                     0x0D, 0x08, "SFM GS",                                           SFM_GS,                                           {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_LOST_WOODS);
                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    locationTable[HF_GS_COW_GROTTO]                                  = ItemLocation::GSToken(RC_HF_GS_COW_GROTTO,                                                           0x0A, 0x01, "HF GS Cow Grotto",                                 HF_GS_COW_GROTTO,                                 {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_HYRULE_FIELD);
    locationTable[HF_GS_NEAR_KAK_GROTTO]                             = ItemLocation::GSToken(RC_HF_GS_NEAR_KAK_GROTTO,                                                      0x0A, 0x02, "HF GS Near Kak Grotto",                            HF_GS_NEAR_KAK_GROTTO,                            {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_HYRULE_FIELD);
                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    locationTable[LH_GS_BEAN_PATCH]                                  = ItemLocation::GSToken(RC_LH_GS_BEAN_PATCH,                                                           0x12, 0x01, "LH GS Bean Patch",                                 LH_GS_BEAN_PATCH,                                 {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_LAKE_HYLIA);
    locationTable[LH_GS_SMALL_ISLAND]                                = ItemLocation::GSToken(RC_LH_GS_SMALL_ISLAND,                                                         0x12, 0x02, "LH GS Small Island",                               LH_GS_SMALL_ISLAND,                               {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_LAKE_HYLIA);
    locationTable[LH_GS_LAB_WALL]                                    = ItemLocation::GSToken(RC_LH_GS_LAB_WALL,                                                             0x12, 0x04, "LH GS Lab Wall",                                   LH_GS_LAB_WALL,                                   {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_LAKE_HYLIA);
    locationTable[LH_GS_LAB_CRATE]                                   = ItemLocation::GSToken(RC_LH_GS_LAB_CRATE,                                                            0x12, 0x08, "LH GS Lab Crate",                                  LH_GS_LAB_CRATE,                                  {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_LAKE_HYLIA);
    locationTable[LH_GS_TREE]                                        = ItemLocation::GSToken(RC_LH_GS_TREE,                                                                 0x12, 0x10, "LH GS Tree",                                       LH_GS_TREE,                                       {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_LAKE_HYLIA);
                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    locationTable[GV_GS_BEAN_PATCH]                                  = ItemLocation::GSToken(RC_GV_GS_BEAN_PATCH,                                                           0x13, 0x01, "GV GS Bean Patch",                                 GV_GS_BEAN_PATCH,                                 {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_GERUDO_VALLEY);
    locationTable[GV_GS_SMALL_BRIDGE]                                = ItemLocation::GSToken(RC_GV_GS_SMALL_BRIDGE,                                                         0x13, 0x02, "GV GS Small Bridge",                               GV_GS_SMALL_BRIDGE,                               {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_GERUDO_VALLEY);
    locationTable[GV_GS_PILLAR]                                      = ItemLocation::GSToken(RC_GV_GS_PILLAR,                                                               0x13, 0x04, "GV GS Pillar",                                     GV_GS_PILLAR,                                     {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_GERUDO_VALLEY);
    locationTable[GV_GS_BEHIND_TENT]                                 = ItemLocation::GSToken(RC_GV_GS_BEHIND_TENT,                                                          0x13, 0x08, "GV GS Behind Tent",                                GV_GS_BEHIND_TENT,                                {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_GERUDO_VALLEY);
                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    locationTable[GF_GS_ARCHERY_RANGE]                               = ItemLocation::GSToken(RC_GF_GS_ARCHERY_RANGE,                                                        0x14, 0x01, "GF GS Archery Range",                              GF_GS_ARCHERY_RANGE,                              {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_GERUDO_VALLEY);
    locationTable[GF_GS_TOP_FLOOR]                                   = ItemLocation::GSToken(RC_GF_GS_TOP_FLOOR,                                                            0x14, 0x02, "GF GS Top Floor",                                  GF_GS_TOP_FLOOR,                                  {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_GERUDO_VALLEY);
                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    locationTable[WASTELAND_GS]                                      = ItemLocation::GSToken(RC_WASTELAND_GS,                                                               0x15, 0x02, "Wasteland GS",                                     WASTELAND_GS,                                     {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_GERUDO_VALLEY);
    locationTable[COLOSSUS_GS_BEAN_PATCH]                            = ItemLocation::GSToken(RC_COLOSSUS_GS_BEAN_PATCH,                                                     0x15, 0x01, "Colossus GS Bean Patch",                           COLOSSUS_GS_BEAN_PATCH,                           {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_GERUDO_VALLEY);
    locationTable[COLOSSUS_GS_HILL]                                  = ItemLocation::GSToken(RC_COLOSSUS_GS_HILL,                                                           0x15, 0x04, "Colossus GS Hill",                                 COLOSSUS_GS_HILL,                                 {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_GERUDO_VALLEY);
    locationTable[COLOSSUS_GS_TREE]                                  = ItemLocation::GSToken(RC_COLOSSUS_GS_TREE,                                                           0x15, 0x08, "Colossus GS Tree",                                 COLOSSUS_GS_TREE,                                 {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_GERUDO_VALLEY);
                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    locationTable[OGC_GS]                                            = ItemLocation::GSToken(RC_OGC_GS,                                                                     0x0E, 0x01, "OGC GS",                                           OGC_GS,                                           {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);
    locationTable[HC_GS_STORMS_GROTTO]                               = ItemLocation::GSToken(RC_HC_GS_STORMS_GROTTO,                                                        0x0E, 0x02, "HC GS Storms Grotto",                              HC_GS_STORMS_GROTTO,                              {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);
    locationTable[HC_GS_TREE]                                        = ItemLocation::GSToken(RC_HC_GS_TREE,                                                                 0x0E, 0x04, "HC GS Tree",                                       HC_GS_TREE,                                       {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);
    locationTable[MARKET_GS_GUARD_HOUSE]                             = ItemLocation::GSToken(RC_MARKET_GS_GUARD_HOUSE,                                                      0x0E, 0x08, "Market GS Guard House",                            MARKET_GS_GUARD_HOUSE,                            {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);
                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    locationTable[KAK_GS_HOUSE_UNDER_CONSTRUCTION]                   = ItemLocation::GSToken(RC_KAK_GS_HOUSE_UNDER_CONSTRUCTION,                                            0x10, 0x08, "Kak GS House Under Construction",                  KAK_GS_HOUSE_UNDER_CONSTRUCTION,                  {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[KAK_GS_SKULLTULA_HOUSE]                            = ItemLocation::GSToken(RC_KAK_GS_SKULLTULA_HOUSE,                                                     0x10, 0x10, "Kak GS Skulltula House",                           KAK_GS_SKULLTULA_HOUSE,                           {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[KAK_GS_GUARDS_HOUSE]                               = ItemLocation::GSToken(RC_KAK_GS_GUARDS_HOUSE,                                                        0x10, 0x02, "Kak GS Guards House",                              KAK_GS_GUARDS_HOUSE,                              {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[KAK_GS_TREE]                                       = ItemLocation::GSToken(RC_KAK_GS_TREE,                                                                0x10, 0x20, "Kak GS Tree",                                      KAK_GS_TREE,                                      {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[KAK_GS_WATCHTOWER]                                 = ItemLocation::GSToken(RC_KAK_GS_WATCHTOWER,                                                          0x10, 0x04, "Kak GS Watchtower",                                KAK_GS_WATCHTOWER,                                {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[KAK_GS_ABOVE_IMPAS_HOUSE]                          = ItemLocation::GSToken(RC_KAK_GS_ABOVE_IMPAS_HOUSE,                                                   0x10, 0x40, "Kak GS Above Impas House",                         KAK_GS_ABOVE_IMPAS_HOUSE,                         {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    locationTable[GRAVEYARD_GS_WALL]                                 = ItemLocation::GSToken(RC_GRAVEYARD_GS_WALL,                                                          0x10, 0x80, "Graveyard GS Wall",                                GRAVEYARD_GS_WALL,                                {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[GRAVEYARD_GS_BEAN_PATCH]                           = ItemLocation::GSToken(RC_GRAVEYARD_GS_BEAN_PATCH,                                                    0x10, 0x01, "Graveyard GS Bean Patch",                          GRAVEYARD_GS_BEAN_PATCH,                          {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    locationTable[DMC_GS_BEAN_PATCH]                                 = ItemLocation::GSToken(RC_DMC_GS_BEAN_PATCH,                                                          0x0F, 0x01, "DMC GS Bean Patch",                                DMC_GS_BEAN_PATCH,                                {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DEATH_MOUNTAIN);
    locationTable[DMC_GS_CRATE]                                      = ItemLocation::GSToken(RC_DMC_GS_CRATE,                                                               0x0F, 0x80, "DMC GS Crate",                                     DMC_GS_CRATE,                                     {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DEATH_MOUNTAIN);
                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    locationTable[DMT_GS_BEAN_PATCH]                                 = ItemLocation::GSToken(RC_DMT_GS_BEAN_PATCH,                                                          0x0F, 0x02, "DMT GS Bean Patch",                                DMT_GS_BEAN_PATCH,                                {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DEATH_MOUNTAIN);
    locationTable[DMT_GS_NEAR_KAK]                                   = ItemLocation::GSToken(RC_DMT_GS_NEAR_KAK,                                                            0x0F, 0x04, "DMT GS Near Kak",                                  DMT_GS_NEAR_KAK,                                  {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DEATH_MOUNTAIN);
    locationTable[DMT_GS_ABOVE_DODONGOS_CAVERN]                      = ItemLocation::GSToken(RC_DMT_GS_ABOVE_DODONGOS_CAVERN,                                               0x0F, 0x08, "DMT GS Above Dodongos Cavern",                     DMT_GS_ABOVE_DODONGOS_CAVERN,                     {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DEATH_MOUNTAIN);
    locationTable[DMT_GS_FALLING_ROCKS_PATH]                         = ItemLocation::GSToken(RC_DMT_GS_FALLING_ROCKS_PATH,                                                  0x0F, 0x10, "DMT GS Falling Rocks Path",                        DMT_GS_FALLING_ROCKS_PATH,                        {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_DEATH_MOUNTAIN);
                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    locationTable[GC_GS_CENTER_PLATFORM]                             = ItemLocation::GSToken(RC_GC_GS_CENTER_PLATFORM,                                                      0x0F, 0x20, "GC GS Center Platform",                            GC_GS_CENTER_PLATFORM,                            {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_GORON_CITY);
    locationTable[GC_GS_BOULDER_MAZE]                                = ItemLocation::GSToken(RC_GC_GS_BOULDER_MAZE,                                                         0x0F, 0x40, "GC GS Boulder Maze",                               GC_GS_BOULDER_MAZE,                               {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_GORON_CITY);
                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    locationTable[ZR_GS_LADDER]                                      = ItemLocation::GSToken(RC_ZR_GS_LADDER,                                                               0x11, 0x01, "ZR GS Ladder",                                     ZR_GS_LADDER,                                     {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_ZORAS_RIVER);
    locationTable[ZR_GS_TREE]                                        = ItemLocation::GSToken(RC_ZR_GS_TREE,                                                                 0x11, 0x02, "ZR GS Tree",                                       ZR_GS_TREE,                                       {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_ZORAS_RIVER);
    locationTable[ZR_GS_ABOVE_BRIDGE]                                = ItemLocation::GSToken(RC_ZR_GS_ABOVE_BRIDGE,                                                         0x11, 0x08, "ZR GS Above Bridge",                               ZR_GS_ABOVE_BRIDGE,                               {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_ZORAS_RIVER);
    locationTable[ZR_GS_NEAR_RAISED_GROTTOS]                         = ItemLocation::GSToken(RC_ZR_GS_NEAR_RAISED_GROTTOS,                                                  0x11, 0x10, "ZR GS Near Raised Grottos",                        ZR_GS_NEAR_RAISED_GROTTOS,                        {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_ZORAS_RIVER);
                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    locationTable[ZD_GS_FROZEN_WATERFALL]                            = ItemLocation::GSToken(RC_ZD_GS_FROZEN_WATERFALL,                                                     0x11, 0x40, "ZD GS Frozen Waterfall",                           ZD_GS_FROZEN_WATERFALL,                           {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_ZORAS_DOMAIN);
    locationTable[ZF_GS_ABOVE_THE_LOG]                               = ItemLocation::GSToken(RC_ZF_GS_ABOVE_THE_LOG,                                                        0x11, 0x04, "ZF GS Above The Log",                              ZF_GS_ABOVE_THE_LOG,                              {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_ZORAS_DOMAIN);
    locationTable[ZF_GS_HIDDEN_CAVE]                                 = ItemLocation::GSToken(RC_ZF_GS_HIDDEN_CAVE,                                                          0x11, 0x20, "ZF GS Hidden Cave",                                ZF_GS_HIDDEN_CAVE,                                {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_ZORAS_DOMAIN);
    locationTable[ZF_GS_TREE]                                        = ItemLocation::GSToken(RC_ZF_GS_TREE,                                                                 0x11, 0x80, "ZF GS Tree",                                       ZF_GS_TREE,                                       {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_ZORAS_DOMAIN);
                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    locationTable[LLR_GS_BACK_WALL]                                  = ItemLocation::GSToken(RC_LLR_GS_BACK_WALL,                                                           0x0B, 0x01, "LLR GS Back Wall",                                 LLR_GS_BACK_WALL,                                 {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_LON_LON_RANCH);
    locationTable[LLR_GS_RAIN_SHED]                                  = ItemLocation::GSToken(RC_LLR_GS_RAIN_SHED,                                                           0x0B, 0x02, "LLR GS Rain Shed",                                 LLR_GS_RAIN_SHED,                                 {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_LON_LON_RANCH);
    locationTable[LLR_GS_HOUSE_WINDOW]                               = ItemLocation::GSToken(RC_LLR_GS_HOUSE_WINDOW,                                                        0x0B, 0x04, "LLR GS House Window",                              LLR_GS_HOUSE_WINDOW,                              {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_LON_LON_RANCH);
    locationTable[LLR_GS_TREE]                                       = ItemLocation::GSToken(RC_LLR_GS_TREE,                                                                0x0B, 0x08, "LLR GS Tree",                                      LLR_GS_TREE,                                      {Category::cSkulltula},                                                                                  SpoilerCollectionCheckGroup::GROUP_LON_LON_RANCH);

    /*-------------------------------
              --- BOSSES ---
      -------------------------------*/

    locationTable[LINKS_POCKET]                                  = ItemLocation::Reward (RC_LINKS_POCKET,   0xFF, "Link's Pocket", LINKS_POCKET,  LIGHT_MEDALLION,   {}, SpoilerCollectionCheck::AlwaysCollected(), SpoilerCollectionCheckGroup::GROUP_KOKIRI_FOREST);
    locationTable[QUEEN_GOHMA]                                   = ItemLocation::Reward (RC_QUEEN_GOHMA,    0xFF, "Queen Gohma",   QUEEN_GOHMA,   KOKIRI_EMERALD,    {}, SpoilerCollectionCheck::Chest(0x11, 0x1F), SpoilerCollectionCheckGroup::GROUP_DUNGEON_DEKU_TREE);
    locationTable[KING_DODONGO]                                  = ItemLocation::Reward (RC_KING_DODONGO,   0xFF, "King Dodongo",  KING_DODONGO,  GORON_RUBY,        {}, SpoilerCollectionCheck::Chest(0x12, 0x1F), SpoilerCollectionCheckGroup::GROUP_DUNGEON_DODONGOS_CAVERN);
    locationTable[BARINADE]                                      = ItemLocation::Reward (RC_BARINADE,       0xFF, "Barinade",      BARINADE,      ZORA_SAPPHIRE,     {}, SpoilerCollectionCheck::Chest(0x13, 0x1F), SpoilerCollectionCheckGroup::GROUP_DUNGEON_JABUJABUS_BELLY);
    locationTable[PHANTOM_GANON]                                 = ItemLocation::Reward (RC_PHANTOM_GANON,  0xFF, "Phantom Ganon", PHANTOM_GANON, FOREST_MEDALLION,  {}, SpoilerCollectionCheck::Chest(0x14, 0x1F), SpoilerCollectionCheckGroup::GROUP_DUNGEON_FOREST_TEMPLE);
    locationTable[VOLVAGIA]                                      = ItemLocation::Reward (RC_VOLVAGIA,       0xFF, "Volvagia",      VOLVAGIA,      FIRE_MEDALLION,    {}, SpoilerCollectionCheck::Chest(0x15, 0x1F), SpoilerCollectionCheckGroup::GROUP_DUNGEON_FIRE_TEMPLE);
    locationTable[MORPHA]                                        = ItemLocation::Reward (RC_MORPHA,         0xFF, "Morpha",        MORPHA,        WATER_MEDALLION,   {}, SpoilerCollectionCheck::Chest(0x16, 0x1F), SpoilerCollectionCheckGroup::GROUP_DUNGEON_WATER_TEMPLE);
    locationTable[TWINROVA]                                      = ItemLocation::Reward (RC_TWINROVA,       0xFF, "Twinrova",      TWINROVA,      SPIRIT_MEDALLION,  {}, SpoilerCollectionCheck::Chest(0x17, 0x1F), SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[BONGO_BONGO]                                   = ItemLocation::Reward (RC_BONGO_BONGO,    0xFF, "Bongo Bongo",   BONGO_BONGO,   SHADOW_MEDALLION,  {}, SpoilerCollectionCheck::Chest(0x18, 0x1F), SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);
    locationTable[GANON]                                         = ItemLocation::Reward (RC_GANON,          0xFF, "Ganon",         NONE,          TRIFORCE,          {}, SpoilerCollectionCheck::None(),            SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);

    /*-------------------------------
          ---HEART CONTAINERS ---
      -------------------------------*/

    locationTable[DEKU_TREE_QUEEN_GOHMA_HEART]                   = ItemLocation::Base   (RC_DEKU_TREE_QUEEN_GOHMA_HEART,        0x11, "Deku Tree Queen Gohma Heart Container",          DEKU_TREE_QUEEN_GOHMA_HEART,        HEART_CONTAINER,    {Category::cSongDungeonReward}, SpoilerCollectionCheck::Collectable(0x11, 0x1F), SpoilerCollectionCheckGroup::GROUP_DUNGEON_DEKU_TREE);
    locationTable[DODONGOS_CAVERN_KING_DODONGO_HEART]            = ItemLocation::Base   (RC_DODONGOS_CAVERN_KING_DODONGO_HEART, 0x12, "Dodongos Cavern King Dodongo Heart Container",   DODONGOS_CAVERN_KING_DODONGO_HEART, HEART_CONTAINER,    {Category::cSongDungeonReward}, SpoilerCollectionCheck::Collectable(0x12, 0x1F), SpoilerCollectionCheckGroup::GROUP_DUNGEON_DODONGOS_CAVERN);
    locationTable[JABU_JABUS_BELLY_BARINADE_HEART]               = ItemLocation::Base   (RC_JABU_JABUS_BELLY_BARINADE_HEART,    0x13, "Jabu Jabus Belly Barinade Heart Container",      JABU_JABUS_BELLY_BARINADE_HEART,    HEART_CONTAINER,    {Category::cSongDungeonReward}, SpoilerCollectionCheck::Collectable(0x13, 0x1F), SpoilerCollectionCheckGroup::GROUP_DUNGEON_JABUJABUS_BELLY);
    locationTable[FOREST_TEMPLE_PHANTOM_GANON_HEART]             = ItemLocation::Base   (RC_FOREST_TEMPLE_PHANTOM_GANON_HEART,  0x14, "Forest Temple Phantom Ganon Heart Container",    FOREST_TEMPLE_PHANTOM_GANON_HEART,  HEART_CONTAINER,    {Category::cSongDungeonReward}, SpoilerCollectionCheck::Collectable(0x14, 0x1F), SpoilerCollectionCheckGroup::GROUP_DUNGEON_FOREST_TEMPLE);
    locationTable[FIRE_TEMPLE_VOLVAGIA_HEART]                    = ItemLocation::Base   (RC_FIRE_TEMPLE_VOLVAGIA_HEART,         0x15, "Fire Temple Volvagia Heart Container",           FIRE_TEMPLE_VOLVAGIA_HEART,         HEART_CONTAINER,    {Category::cSongDungeonReward}, SpoilerCollectionCheck::Collectable(0x15, 0x1F), SpoilerCollectionCheckGroup::GROUP_DUNGEON_FIRE_TEMPLE);
    locationTable[WATER_TEMPLE_MORPHA_HEART]                     = ItemLocation::Base   (RC_WATER_TEMPLE_MORPHA_HEART,          0x16, "Water Temple Morpha Heart Container",            WATER_TEMPLE_MORPHA_HEART,          HEART_CONTAINER,    {Category::cSongDungeonReward}, SpoilerCollectionCheck::Collectable(0x16, 0x1F), SpoilerCollectionCheckGroup::GROUP_DUNGEON_WATER_TEMPLE);
    locationTable[SPIRIT_TEMPLE_TWINROVA_HEART]                  = ItemLocation::Base   (RC_SPIRIT_TEMPLE_TWINROVA_HEART,       0x17, "Spirit Temple Twinrova Heart Container",         SPIRIT_TEMPLE_TWINROVA_HEART,       HEART_CONTAINER,    {Category::cSongDungeonReward}, SpoilerCollectionCheck::Collectable(0x17, 0x1F), SpoilerCollectionCheckGroup::GROUP_DUNGEON_SPIRIT_TEMPLE);
    locationTable[SHADOW_TEMPLE_BONGO_BONGO_HEART]               = ItemLocation::Base   (RC_SHADOW_TEMPLE_BONGO_BONGO_HEART,    0x18, "Shadow Temple Bongo Bongo Heart Container",      SHADOW_TEMPLE_BONGO_BONGO_HEART,    HEART_CONTAINER,    {Category::cSongDungeonReward}, SpoilerCollectionCheck::Collectable(0x18, 0x1F), SpoilerCollectionCheckGroup::GROUP_DUNGEON_SHADOW_TEMPLE);

    /*-------------------------------
            --- CUTSCENES ---
      -------------------------------*/

    locationTable[TOT_LIGHT_ARROWS_CUTSCENE]                     = ItemLocation::Delayed(RC_TOT_LIGHT_ARROWS_CUTSCENE,          0xFF, "ToT Light Arrow Cutscene",                       TOT_LIGHT_ARROWS_CUTSCENE,   LIGHT_ARROWS,              {}, SpoilerCollectionCheck::Chest(0x43, 0x1E), SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);
    locationTable[LW_GIFT_FROM_SARIA]                            = ItemLocation::Delayed(RC_LW_GIFT_FROM_SARIA,                 0xFF, "LW Gift From Saria",                             LW_GIFT_FROM_SARIA,          PROGRESSIVE_OCARINA,       {}, SpoilerCollectionCheck::EventChkInf(0xC1), SpoilerCollectionCheckGroup::GROUP_LOST_WOODS);
    locationTable[ZF_GREAT_FAIRY_REWARD]                         = ItemLocation::Delayed(RC_ZF_GREAT_FAIRY_REWARD,              0xFF, "ZF Great Fairy Reward",                          ZF_GREAT_FAIRY_REWARD,       FARORES_WIND,              {}, SpoilerCollectionCheck::Chest(0x3D, 0x01), SpoilerCollectionCheckGroup::GROUP_ZORAS_DOMAIN);
    locationTable[HC_GREAT_FAIRY_REWARD]                         = ItemLocation::Delayed(RC_HC_GREAT_FAIRY_REWARD,              0xFF, "HC Great Fairy Reward",                          HC_GREAT_FAIRY_REWARD,       DINS_FIRE,                 {}, SpoilerCollectionCheck::Chest(0x3D, 0x02), SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);
    locationTable[COLOSSUS_GREAT_FAIRY_REWARD]                   = ItemLocation::Delayed(RC_COLOSSUS_GREAT_FAIRY_REWARD,        0xFF, "Colossus Great Fairy Reward",                    COLOSSUS_GREAT_FAIRY_REWARD, NAYRUS_LOVE,               {}, SpoilerCollectionCheck::Chest(0x3D, 0x03), SpoilerCollectionCheckGroup::GROUP_GERUDO_VALLEY);
    locationTable[DMT_GREAT_FAIRY_REWARD]                        = ItemLocation::Delayed(RC_DMT_GREAT_FAIRY_REWARD,             0xFF, "DMT Great Fairy Reward",                         DMT_GREAT_FAIRY_REWARD,      PROGRESSIVE_MAGIC_METER,   {}, SpoilerCollectionCheck::Chest(0x3B, 0x01), SpoilerCollectionCheckGroup::GROUP_DEATH_MOUNTAIN);
    locationTable[DMC_GREAT_FAIRY_REWARD]                        = ItemLocation::Delayed(RC_DMC_GREAT_FAIRY_REWARD,             0xFF, "DMC Great Fairy Reward",                         DMC_GREAT_FAIRY_REWARD,      PROGRESSIVE_MAGIC_METER,   {}, SpoilerCollectionCheck::Chest(0x3B, 0x02), SpoilerCollectionCheckGroup::GROUP_DEATH_MOUNTAIN);
    locationTable[OGC_GREAT_FAIRY_REWARD]                        = ItemLocation::Delayed(RC_OGC_GREAT_FAIRY_REWARD,             0xFF, "OGC Great Fairy Reward",                         OGC_GREAT_FAIRY_REWARD,      DOUBLE_DEFENSE,            {}, SpoilerCollectionCheck::Chest(0x3B, 0x03), SpoilerCollectionCheckGroup::GROUP_DUNGEON_GANONS_CASTLE);

    locationTable[SHEIK_IN_FOREST]                               = ItemLocation::Delayed(RC_SHEIK_IN_FOREST,                    0xFF, "Sheik in Forest",                                SHEIK_IN_FOREST,             MINUET_OF_FOREST,          {Category::cSong},                               SpoilerCollectionCheck::EventChkInf(0x50), SpoilerCollectionCheckGroup::GROUP_LOST_WOODS);
    locationTable[SHEIK_IN_CRATER]                               = ItemLocation::Delayed(RC_SHEIK_IN_CRATER,                    0xFF, "Sheik in Crater",                                SHEIK_IN_CRATER,             BOLERO_OF_FIRE,            {Category::cSong},                               SpoilerCollectionCheck::EventChkInf(0x51), SpoilerCollectionCheckGroup::GROUP_DEATH_MOUNTAIN);
    locationTable[SHEIK_IN_ICE_CAVERN]                           = ItemLocation::Delayed(RC_SHEIK_IN_ICE_CAVERN,                0xFF, "Sheik in Ice Cavern",                            SHEIK_IN_ICE_CAVERN,         SERENADE_OF_WATER,         {Category::cSong, Category::cSongDungeonReward}, SpoilerCollectionCheck::EventChkInf(0x52), SpoilerCollectionCheckGroup::GROUP_DUNGEON_ICE_CAVERN);
    locationTable[SHEIK_AT_COLOSSUS]                             = ItemLocation::Delayed(RC_SHEIK_AT_COLOSSUS,                  0xFF, "Sheik at Colossus",                              SHEIK_AT_COLOSSUS,           REQUIEM_OF_SPIRIT,         {Category::cSong},                               SpoilerCollectionCheck::EventChkInf(0xAC), SpoilerCollectionCheckGroup::GROUP_GERUDO_VALLEY);
    locationTable[SHEIK_IN_KAKARIKO]                             = ItemLocation::Delayed(RC_SHEIK_IN_KAKARIKO,                  0xFF, "Sheik in Kakariko",                              SHEIK_IN_KAKARIKO,           NOCTURNE_OF_SHADOW,        {Category::cSong},                               SpoilerCollectionCheck::EventChkInf(0xAA), SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[SHEIK_AT_TEMPLE]                               = ItemLocation::Delayed(RC_SHEIK_AT_TEMPLE,                    0xFF, "Sheik at Temple",                                SHEIK_AT_TEMPLE,             PRELUDE_OF_LIGHT,          {Category::cSong},                               SpoilerCollectionCheck::Chest(0x43, 0x1F), SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);
    locationTable[SONG_FROM_IMPA]                                = ItemLocation::Delayed(RC_SONG_FROM_IMPA,                     0xFF, "Song from Impa",                                 SONG_FROM_IMPA,              ZELDAS_LULLABY,            {Category::cSong, Category::cSongDungeonReward}, SpoilerCollectionCheck::EventChkInf(0x59), SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);
    locationTable[SONG_FROM_MALON]                               = ItemLocation::Delayed(RC_SONG_FROM_MALON,                    0xFF, "Song from Malon",                                SONG_FROM_MALON,             EPONAS_SONG,               {Category::cSong},                               SpoilerCollectionCheck::Chest(0x63, 0x1F), SpoilerCollectionCheckGroup::GROUP_LON_LON_RANCH);
    locationTable[SONG_FROM_SARIA]                               = ItemLocation::Delayed(RC_SONG_FROM_SARIA,                    0xFF, "Song from Saria",                                SONG_FROM_SARIA,             SARIAS_SONG,               {Category::cSong},                               SpoilerCollectionCheck::Chest(0x56, 0x1F), SpoilerCollectionCheckGroup::GROUP_LOST_WOODS);
    locationTable[SONG_FROM_COMPOSERS_GRAVE]                     = ItemLocation::Delayed(RC_SONG_FROM_ROYAL_FAMILYS_TOMB,       0xFF, "Song from Composers Grave",                      SONG_FROM_COMPOSERS_GRAVE,   SUNS_SONG,                 {Category::cSong},                               SpoilerCollectionCheck::Chest(0x41, 0x1F), SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[SONG_FROM_OCARINA_OF_TIME]                     = ItemLocation::Delayed(RC_SONG_FROM_OCARINA_OF_TIME,          0xFF, "Song from Ocarina of Time",                      SONG_FROM_OCARINA_OF_TIME,   SONG_OF_TIME,              {Category::cSong},                               SpoilerCollectionCheck::Chest(0x51, 0x1F), SpoilerCollectionCheckGroup::GROUP_HYRULE_FIELD);
    locationTable[SONG_FROM_WINDMILL]                            = ItemLocation::Delayed(RC_SONG_FROM_WINDMILL,                 0xFF, "Song from Windmill",                             SONG_FROM_WINDMILL,          SONG_OF_STORMS,            {Category::cSong},                               SpoilerCollectionCheck::EventChkInf(0x5B), SpoilerCollectionCheckGroup::GROUP_KAKARIKO);

    /*-------------------------------
               --- COWS ---
      -------------------------------*/

    locationTable[KF_LINKS_HOUSE_COW]                            = ItemLocation::Base   (RC_KF_LINKS_HOUSE_COW,                 0x34, "KF Links House Cow",                             KF_LINKS_HOUSE_COW,          MILK,                      {Category::cCow}, SpoilerCollectionCheck::Cow(), SpoilerCollectionCheckGroup::GROUP_KOKIRI_FOREST);
    locationTable[HF_COW_GROTTO_COW]                             = ItemLocation::Base   (RC_HF_COW_GROTTO_COW,                  0x3E, "HF Cow Grotto Cow",                              HF_COW_GROTTO_COW,           MILK,                      {Category::cCow}, SpoilerCollectionCheck::Cow(), SpoilerCollectionCheckGroup::GROUP_HYRULE_FIELD);
    locationTable[LLR_STABLES_LEFT_COW]                          = ItemLocation::Base   (RC_LLR_STABLES_LEFT_COW,               0x36, "LLR Stables Left Cow",                           LLR_STABLES_LEFT_COW,        MILK,                      {Category::cCow}, SpoilerCollectionCheck::Cow(), SpoilerCollectionCheckGroup::GROUP_LON_LON_RANCH);
    locationTable[LLR_STABLES_RIGHT_COW]                         = ItemLocation::Base   (RC_LLR_STABLES_RIGHT_COW,              0x36, "LLR Stables Right Cow",                          LLR_STABLES_RIGHT_COW,       MILK,                      {Category::cCow}, SpoilerCollectionCheck::Cow(), SpoilerCollectionCheckGroup::GROUP_LON_LON_RANCH);
    locationTable[LLR_TOWER_LEFT_COW]                            = ItemLocation::Base   (RC_LLR_TOWER_LEFT_COW,                 0x4C, "LLR Tower Left Cow",                             LLR_TOWER_LEFT_COW,          MILK,                      {Category::cCow}, SpoilerCollectionCheck::Cow(), SpoilerCollectionCheckGroup::GROUP_LON_LON_RANCH);
    locationTable[LLR_TOWER_RIGHT_COW]                           = ItemLocation::Base   (RC_LLR_TOWER_RIGHT_COW,                0x4C, "LLR Tower Right Cow",                            LLR_TOWER_RIGHT_COW,         MILK,                      {Category::cCow}, SpoilerCollectionCheck::Cow(), SpoilerCollectionCheckGroup::GROUP_LON_LON_RANCH);
    locationTable[KAK_IMPAS_HOUSE_COW]                           = ItemLocation::Base   (RC_KAK_IMPAS_HOUSE_COW,                0x37, "Kak Impas House Cow",                            KAK_IMPAS_HOUSE_COW,         MILK,                      {Category::cCow}, SpoilerCollectionCheck::Cow(), SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[DMT_COW_GROTTO_COW]                            = ItemLocation::Base   (RC_DMT_COW_GROTTO_COW,                 0x3E, "DMT Cow Grotto Cow",                             DMT_COW_GROTTO_COW,          MILK,                      {Category::cCow}, SpoilerCollectionCheck::Cow(), SpoilerCollectionCheckGroup::GROUP_DEATH_MOUNTAIN);
    locationTable[GV_COW]                                        = ItemLocation::Base   (RC_GV_COW,                             0x5A, "GV Cow",                                         GV_COW,                      MILK,                      {Category::cCow}, SpoilerCollectionCheck::Cow(), SpoilerCollectionCheckGroup::GROUP_GERUDO_VALLEY);
    locationTable[JABU_JABUS_BELLY_MQ_COW]                       = ItemLocation::Base   (RC_JABU_JABUS_BELLY_MQ_COW,            0x02, "Jabu Jabus Belly MQ Cow",                        JABU_JABUS_BELLY_MQ_COW,     MILK,                      {Category::cCow}, SpoilerCollectionCheck::Cow(), SpoilerCollectionCheckGroup::GROUP_DUNGEON_JABUJABUS_BELLY);

    /*-------------------------------
              --- SHOPS ---
      8     6               2     4

      7     5               1     3
      -------------------------------*/

    locationTable[KF_SHOP_ITEM_1]             = ItemLocation::Base(RC_KF_SHOP_ITEM_1,             0x2D, "KF Shop Item 1",         KF_SHOP_ITEM_1,             BUY_DEKU_SHIELD,   {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_KOKIRI_FOREST);
    locationTable[KF_SHOP_ITEM_2]             = ItemLocation::Base(RC_KF_SHOP_ITEM_2,             0x2D, "KF Shop Item 2",         KF_SHOP_ITEM_2,             BUY_DEKU_NUT_5,    {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_KOKIRI_FOREST);
    locationTable[KF_SHOP_ITEM_3]             = ItemLocation::Base(RC_KF_SHOP_ITEM_3,             0x2D, "KF Shop Item 3",         KF_SHOP_ITEM_3,             BUY_DEKU_NUT_10,   {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_KOKIRI_FOREST);
    locationTable[KF_SHOP_ITEM_4]             = ItemLocation::Base(RC_KF_SHOP_ITEM_4,             0x2D, "KF Shop Item 4",         KF_SHOP_ITEM_4,             BUY_DEKU_STICK_1,  {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_KOKIRI_FOREST);
    locationTable[KF_SHOP_ITEM_5]             = ItemLocation::Base(RC_KF_SHOP_ITEM_5,             0x2D, "KF Shop Item 5",         KF_SHOP_ITEM_5,             BUY_DEKU_SEEDS_30, {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_KOKIRI_FOREST);
    locationTable[KF_SHOP_ITEM_6]             = ItemLocation::Base(RC_KF_SHOP_ITEM_6,             0x2D, "KF Shop Item 6",         KF_SHOP_ITEM_6,             BUY_ARROWS_10,     {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_KOKIRI_FOREST);
    locationTable[KF_SHOP_ITEM_7]             = ItemLocation::Base(RC_KF_SHOP_ITEM_7,             0x2D, "KF Shop Item 7",         KF_SHOP_ITEM_7,             BUY_ARROWS_30,     {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_KOKIRI_FOREST);
    locationTable[KF_SHOP_ITEM_8]             = ItemLocation::Base(RC_KF_SHOP_ITEM_8,             0x2D, "KF Shop Item 8",         KF_SHOP_ITEM_8,             BUY_HEART,         {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_KOKIRI_FOREST);

    locationTable[KAK_POTION_SHOP_ITEM_1]     = ItemLocation::Base(RC_KAK_POTION_SHOP_ITEM_1,     0x30, "Kak Potion Shop Item 1", KAK_POTION_SHOP_ITEM_1,     BUY_GREEN_POTION,  {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[KAK_POTION_SHOP_ITEM_2]     = ItemLocation::Base(RC_KAK_POTION_SHOP_ITEM_2,     0x30, "Kak Potion Shop Item 2", KAK_POTION_SHOP_ITEM_2,     BUY_BLUE_FIRE,     {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[KAK_POTION_SHOP_ITEM_3]     = ItemLocation::Base(RC_KAK_POTION_SHOP_ITEM_3,     0x30, "Kak Potion Shop Item 3", KAK_POTION_SHOP_ITEM_3,     BUY_RED_POTION_30, {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[KAK_POTION_SHOP_ITEM_4]     = ItemLocation::Base(RC_KAK_POTION_SHOP_ITEM_4,     0x30, "Kak Potion Shop Item 4", KAK_POTION_SHOP_ITEM_4,     BUY_FAIRYS_SPIRIT, {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[KAK_POTION_SHOP_ITEM_5]     = ItemLocation::Base(RC_KAK_POTION_SHOP_ITEM_5,     0x30, "Kak Potion Shop Item 5", KAK_POTION_SHOP_ITEM_5,     BUY_DEKU_NUT_5,    {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[KAK_POTION_SHOP_ITEM_6]     = ItemLocation::Base(RC_KAK_POTION_SHOP_ITEM_6,     0x30, "Kak Potion Shop Item 6", KAK_POTION_SHOP_ITEM_6,     BUY_BOTTLE_BUG,    {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[KAK_POTION_SHOP_ITEM_7]     = ItemLocation::Base(RC_KAK_POTION_SHOP_ITEM_7,     0x30, "Kak Potion Shop Item 7", KAK_POTION_SHOP_ITEM_7,     BUY_POE,           {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[KAK_POTION_SHOP_ITEM_8]     = ItemLocation::Base(RC_KAK_POTION_SHOP_ITEM_8,     0x30, "Kak Potion Shop Item 8", KAK_POTION_SHOP_ITEM_8,     BUY_FISH,          {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_KAKARIKO);

    locationTable[MARKET_BOMBCHU_SHOP_ITEM_1] = ItemLocation::Base(RC_MARKET_BOMBCHU_SHOP_ITEM_1, 0x32, "MK Bombchu Shop Item 1", MARKET_BOMBCHU_SHOP_ITEM_1, BUY_BOMBCHU_10,    {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);
    locationTable[MARKET_BOMBCHU_SHOP_ITEM_2] = ItemLocation::Base(RC_MARKET_BOMBCHU_SHOP_ITEM_2, 0x32, "MK Bombchu Shop Item 2", MARKET_BOMBCHU_SHOP_ITEM_2, BUY_BOMBCHU_10,    {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);
    locationTable[MARKET_BOMBCHU_SHOP_ITEM_3] = ItemLocation::Base(RC_MARKET_BOMBCHU_SHOP_ITEM_3, 0x32, "MK Bombchu Shop Item 3", MARKET_BOMBCHU_SHOP_ITEM_3, BUY_BOMBCHU_10,    {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);
    locationTable[MARKET_BOMBCHU_SHOP_ITEM_4] = ItemLocation::Base(RC_MARKET_BOMBCHU_SHOP_ITEM_4, 0x32, "MK Bombchu Shop Item 4", MARKET_BOMBCHU_SHOP_ITEM_4, BUY_BOMBCHU_10,    {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);
    locationTable[MARKET_BOMBCHU_SHOP_ITEM_5] = ItemLocation::Base(RC_MARKET_BOMBCHU_SHOP_ITEM_5, 0x32, "MK Bombchu Shop Item 5", MARKET_BOMBCHU_SHOP_ITEM_5, BUY_BOMBCHU_20,    {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);
    locationTable[MARKET_BOMBCHU_SHOP_ITEM_6] = ItemLocation::Base(RC_MARKET_BOMBCHU_SHOP_ITEM_6, 0x32, "MK Bombchu Shop Item 6", MARKET_BOMBCHU_SHOP_ITEM_6, BUY_BOMBCHU_20,    {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);
    locationTable[MARKET_BOMBCHU_SHOP_ITEM_7] = ItemLocation::Base(RC_MARKET_BOMBCHU_SHOP_ITEM_7, 0x32, "MK Bombchu Shop Item 7", MARKET_BOMBCHU_SHOP_ITEM_7, BUY_BOMBCHU_20,    {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);
    locationTable[MARKET_BOMBCHU_SHOP_ITEM_8] = ItemLocation::Base(RC_MARKET_BOMBCHU_SHOP_ITEM_8, 0x32, "MK Bombchu Shop Item 8", MARKET_BOMBCHU_SHOP_ITEM_8, BUY_BOMBCHU_20,    {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);

    locationTable[MARKET_POTION_SHOP_ITEM_1]  = ItemLocation::Base(RC_MARKET_POTION_SHOP_ITEM_1,  0x31, "MK Potion Shop Item 1",  MARKET_POTION_SHOP_ITEM_1,  BUY_GREEN_POTION,  {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);
    locationTable[MARKET_POTION_SHOP_ITEM_2]  = ItemLocation::Base(RC_MARKET_POTION_SHOP_ITEM_2,  0x31, "MK Potion Shop Item 2",  MARKET_POTION_SHOP_ITEM_2,  BUY_BLUE_FIRE,     {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);
    locationTable[MARKET_POTION_SHOP_ITEM_3]  = ItemLocation::Base(RC_MARKET_POTION_SHOP_ITEM_3,  0x31, "MK Potion Shop Item 3",  MARKET_POTION_SHOP_ITEM_3,  BUY_RED_POTION_30, {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);
    locationTable[MARKET_POTION_SHOP_ITEM_4]  = ItemLocation::Base(RC_MARKET_POTION_SHOP_ITEM_4,  0x31, "MK Potion Shop Item 4",  MARKET_POTION_SHOP_ITEM_4,  BUY_FAIRYS_SPIRIT, {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);
    locationTable[MARKET_POTION_SHOP_ITEM_5]  = ItemLocation::Base(RC_MARKET_POTION_SHOP_ITEM_5,  0x31, "MK Potion Shop Item 5",  MARKET_POTION_SHOP_ITEM_5,  BUY_DEKU_NUT_5,    {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);
    locationTable[MARKET_POTION_SHOP_ITEM_6]  = ItemLocation::Base(RC_MARKET_POTION_SHOP_ITEM_6,  0x31, "MK Potion Shop Item 6",  MARKET_POTION_SHOP_ITEM_6,  BUY_BOTTLE_BUG,    {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);
    locationTable[MARKET_POTION_SHOP_ITEM_7]  = ItemLocation::Base(RC_MARKET_POTION_SHOP_ITEM_7,  0x31, "MK Potion Shop Item 7",  MARKET_POTION_SHOP_ITEM_7,  BUY_POE,           {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);
    locationTable[MARKET_POTION_SHOP_ITEM_8]  = ItemLocation::Base(RC_MARKET_POTION_SHOP_ITEM_8,  0x31, "MK Potion Shop Item 8",  MARKET_POTION_SHOP_ITEM_8,  BUY_FISH,          {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);

    locationTable[MARKET_BAZAAR_ITEM_1]       = ItemLocation::Base(RC_MARKET_BAZAAR_ITEM_1,       0x2C, "MK Bazaar Item 1",       MARKET_BAZAAR_ITEM_1,       BUY_HYLIAN_SHIELD, {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);
    locationTable[MARKET_BAZAAR_ITEM_2]       = ItemLocation::Base(RC_MARKET_BAZAAR_ITEM_2,       0x2C, "MK Bazaar Item 2",       MARKET_BAZAAR_ITEM_2,       BUY_BOMBS_535,     {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);
    locationTable[MARKET_BAZAAR_ITEM_3]       = ItemLocation::Base(RC_MARKET_BAZAAR_ITEM_3,       0x2C, "MK Bazaar Item 3",       MARKET_BAZAAR_ITEM_3,       BUY_DEKU_NUT_5,    {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);
    locationTable[MARKET_BAZAAR_ITEM_4]       = ItemLocation::Base(RC_MARKET_BAZAAR_ITEM_4,       0x2C, "MK Bazaar Item 4",       MARKET_BAZAAR_ITEM_4,       BUY_HEART,         {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);
    locationTable[MARKET_BAZAAR_ITEM_5]       = ItemLocation::Base(RC_MARKET_BAZAAR_ITEM_5,       0x2C, "MK Bazaar Item 5",       MARKET_BAZAAR_ITEM_5,       BUY_ARROWS_10,     {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);
    locationTable[MARKET_BAZAAR_ITEM_6]       = ItemLocation::Base(RC_MARKET_BAZAAR_ITEM_6,       0x2C, "MK Bazaar Item 6",       MARKET_BAZAAR_ITEM_6,       BUY_ARROWS_50,     {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);
    locationTable[MARKET_BAZAAR_ITEM_7]       = ItemLocation::Base(RC_MARKET_BAZAAR_ITEM_7,       0x2C, "MK Bazaar Item 7",       MARKET_BAZAAR_ITEM_7,       BUY_DEKU_STICK_1,  {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);
    locationTable[MARKET_BAZAAR_ITEM_8]       = ItemLocation::Base(RC_MARKET_BAZAAR_ITEM_8,       0x2C, "MK Bazaar Item 8",       MARKET_BAZAAR_ITEM_8,       BUY_ARROWS_30,     {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_HYRULE_CASTLE);

    locationTable[KAK_BAZAAR_ITEM_1]          = ItemLocation::Base(RC_KAK_BAZAAR_ITEM_1,          0x2C, "Kak Bazaar Item 1",      KAK_BAZAAR_ITEM_1,          BUY_HYLIAN_SHIELD, {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[KAK_BAZAAR_ITEM_2]          = ItemLocation::Base(RC_KAK_BAZAAR_ITEM_2,          0x2C, "Kak Bazaar Item 2",      KAK_BAZAAR_ITEM_2,          BUY_BOMBS_535,     {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[KAK_BAZAAR_ITEM_3]          = ItemLocation::Base(RC_KAK_BAZAAR_ITEM_3,          0x2C, "Kak Bazaar Item 3",      KAK_BAZAAR_ITEM_3,          BUY_DEKU_NUT_5,    {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[KAK_BAZAAR_ITEM_4]          = ItemLocation::Base(RC_KAK_BAZAAR_ITEM_4,          0x2C, "Kak Bazaar Item 4",      KAK_BAZAAR_ITEM_4,          BUY_HEART,         {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[KAK_BAZAAR_ITEM_5]          = ItemLocation::Base(RC_KAK_BAZAAR_ITEM_5,          0x2C, "Kak Bazaar Item 5",      KAK_BAZAAR_ITEM_5,          BUY_ARROWS_10,     {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[KAK_BAZAAR_ITEM_6]          = ItemLocation::Base(RC_KAK_BAZAAR_ITEM_6,          0x2C, "Kak Bazaar Item 6",      KAK_BAZAAR_ITEM_6,          BUY_ARROWS_50,     {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[KAK_BAZAAR_ITEM_7]          = ItemLocation::Base(RC_KAK_BAZAAR_ITEM_7,          0x2C, "Kak Bazaar Item 7",      KAK_BAZAAR_ITEM_7,          BUY_DEKU_STICK_1,  {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_KAKARIKO);
    locationTable[KAK_BAZAAR_ITEM_8]          = ItemLocation::Base(RC_KAK_BAZAAR_ITEM_8,          0x2C, "Kak Bazaar Item 8",      KAK_BAZAAR_ITEM_8,          BUY_ARROWS_30,     {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_KAKARIKO);

    locationTable[ZD_SHOP_ITEM_1]             = ItemLocation::Base(RC_ZD_SHOP_ITEM_1,             0x2F, "ZD Shop Item 1",         ZD_SHOP_ITEM_1,             BUY_ZORA_TUNIC,    {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_ZORAS_DOMAIN);
    locationTable[ZD_SHOP_ITEM_2]             = ItemLocation::Base(RC_ZD_SHOP_ITEM_2,             0x2F, "ZD Shop Item 2",         ZD_SHOP_ITEM_2,             BUY_ARROWS_10,     {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_ZORAS_DOMAIN);
    locationTable[ZD_SHOP_ITEM_3]             = ItemLocation::Base(RC_ZD_SHOP_ITEM_3,             0x2F, "ZD Shop Item 3",         ZD_SHOP_ITEM_3,             BUY_HEART,         {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_ZORAS_DOMAIN);
    locationTable[ZD_SHOP_ITEM_4]             = ItemLocation::Base(RC_ZD_SHOP_ITEM_4,             0x2F, "ZD Shop Item 4",         ZD_SHOP_ITEM_4,             BUY_ARROWS_30,     {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_ZORAS_DOMAIN);
    locationTable[ZD_SHOP_ITEM_5]             = ItemLocation::Base(RC_ZD_SHOP_ITEM_5,             0x2F, "ZD Shop Item 5",         ZD_SHOP_ITEM_5,             BUY_DEKU_NUT_5,    {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_ZORAS_DOMAIN);
    locationTable[ZD_SHOP_ITEM_6]             = ItemLocation::Base(RC_ZD_SHOP_ITEM_6,             0x2F, "ZD Shop Item 6",         ZD_SHOP_ITEM_6,             BUY_ARROWS_50,     {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_ZORAS_DOMAIN);
    locationTable[ZD_SHOP_ITEM_7]             = ItemLocation::Base(RC_ZD_SHOP_ITEM_7,             0x2F, "ZD Shop Item 7",         ZD_SHOP_ITEM_7,             BUY_FISH,          {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_ZORAS_DOMAIN);
    locationTable[ZD_SHOP_ITEM_8]             = ItemLocation::Base(RC_ZD_SHOP_ITEM_8,             0x2F, "ZD Shop Item 8",         ZD_SHOP_ITEM_8,             BUY_RED_POTION_50, {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_ZORAS_DOMAIN);

    locationTable[GC_SHOP_ITEM_1]             = ItemLocation::Base(RC_GC_SHOP_ITEM_1,             0x2E, "GC Shop Item 1",         GC_SHOP_ITEM_1,             BUY_BOMBS_525,     {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_GORON_CITY);
    locationTable[GC_SHOP_ITEM_2]             = ItemLocation::Base(RC_GC_SHOP_ITEM_2,             0x2E, "GC Shop Item 2",         GC_SHOP_ITEM_2,             BUY_BOMBS_10,      {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_GORON_CITY);
    locationTable[GC_SHOP_ITEM_3]             = ItemLocation::Base(RC_GC_SHOP_ITEM_3,             0x2E, "GC Shop Item 3",         GC_SHOP_ITEM_3,             BUY_BOMBS_20,      {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_GORON_CITY);
    locationTable[GC_SHOP_ITEM_4]             = ItemLocation::Base(RC_GC_SHOP_ITEM_4,             0x2E, "GC Shop Item 4",         GC_SHOP_ITEM_4,             BUY_BOMBS_30,      {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_GORON_CITY);
    locationTable[GC_SHOP_ITEM_5]             = ItemLocation::Base(RC_GC_SHOP_ITEM_5,             0x2E, "GC Shop Item 5",         GC_SHOP_ITEM_5,             BUY_GORON_TUNIC,   {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_GORON_CITY);
    locationTable[GC_SHOP_ITEM_6]             = ItemLocation::Base(RC_GC_SHOP_ITEM_6,             0x2E, "GC Shop Item 6",         GC_SHOP_ITEM_6,             BUY_HEART,         {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_GORON_CITY);
    locationTable[GC_SHOP_ITEM_7]             = ItemLocation::Base(RC_GC_SHOP_ITEM_7,             0x2E, "GC Shop Item 7",         GC_SHOP_ITEM_7,             BUY_RED_POTION_40, {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_GORON_CITY);
    locationTable[GC_SHOP_ITEM_8]             = ItemLocation::Base(RC_GC_SHOP_ITEM_8,             0x2E, "GC Shop Item 8",         GC_SHOP_ITEM_8,             BUY_HEART,         {Category::cShop}, SpoilerCollectionCheck::ShopItem(), SpoilerCollectionCheckGroup::GROUP_GORON_CITY);

    /*-------------------------------
          --- GOSSIP STONES ---
      -------------------------------*/
    // These are not actual locations, but are filler spots used for hint reachability. - OoT Randomizer
    locationTable[DMC_GOSSIP_STONE]                      = ItemLocation::HintStone(RC_DMC_GOSSIP_STONE,                "DMC Gossip Stone");
    locationTable[DMT_GOSSIP_STONE]                      = ItemLocation::HintStone(RC_DMT_GOSSIP_STONE,                "DMT Gossip Stone");
    locationTable[COLOSSUS_GOSSIP_STONE]                 = ItemLocation::HintStone(RC_COLOSSUS_GOSSIP_STONE,           "Colossus Gossip Stone");
    locationTable[DODONGOS_CAVERN_GOSSIP_STONE]          = ItemLocation::HintStone(RC_DODONGOS_CAVERN_GOSSIP_STONE,    "Dodongo's Cavern Gossip Stone");
    locationTable[GV_GOSSIP_STONE]                       = ItemLocation::HintStone(RC_GV_GOSSIP_STONE,                 "GV Gossip Stone");
    locationTable[GC_MAZE_GOSSIP_STONE]                  = ItemLocation::HintStone(RC_GC_MAZE_GOSSIP_STONE,            "GC Maze Gossip Stone");
    locationTable[GC_MEDIGORON_GOSSIP_STONE]             = ItemLocation::HintStone(RC_GC_MEDIGORON_GOSSIP_STONE,       "GC Medigoron Gossip Stone");
    locationTable[GRAVEYARD_GOSSIP_STONE]                = ItemLocation::HintStone(RC_GY_GOSSIP_STONE,                 "GY Gossip Stone");
    locationTable[HC_MALON_GOSSIP_STONE]                 = ItemLocation::HintStone(RC_HC_MALON_GOSSIP_STONE,           "HC Malon Gossip Stone");
    locationTable[HC_ROCK_WALL_GOSSIP_STONE]             = ItemLocation::HintStone(RC_HC_ROCK_WALL_GOSSIP_STONE,       "HC Rock Wall Gossip Stone");
    locationTable[HC_STORMS_GROTTO_GOSSIP_STONE]         = ItemLocation::HintStone(RC_HC_STORMS_GROTTO_GOSSIP_STONE,   "HC Storms Grotto Gossip Stone");
    locationTable[KF_DEKU_TREE_GOSSIP_STONE_LEFT]        = ItemLocation::HintStone(RC_KF_DEKU_TREE_LEFT_GOSSIP_STONE,  "KF Deku Tree Left Gossip Stone");
    locationTable[KF_DEKU_TREE_GOSSIP_STONE_RIGHT]       = ItemLocation::HintStone(RC_KF_DEKU_TREE_RIGHT_GOSSIP_STONE, "KF Deku Tree Right Gossip Stone");
    locationTable[KF_GOSSIP_STONE]                       = ItemLocation::HintStone(RC_KF_GOSSIP_STONE,                 "KF Gossip Stone");
    locationTable[LH_LAB_GOSSIP_STONE]                   = ItemLocation::HintStone(RC_LH_LAB_GOSSIP_STONE,             "LH Lab Gossip Stone");
    locationTable[LH_GOSSIP_STONE_SOUTHEAST]             = ItemLocation::HintStone(RC_LH_SOUTHEAST_GOSSIP_STONE,       "LH Southeast Gossip Stone");
    locationTable[LH_GOSSIP_STONE_SOUTHWEST]             = ItemLocation::HintStone(RC_LH_SOUTHWEST_GOSSIP_STONE,       "LH Southwest Gossip Stone");
    locationTable[LW_GOSSIP_STONE]                       = ItemLocation::HintStone(RC_LW_GOSSIP_STONE,                 "LW Gossip Stone");
    locationTable[SFM_MAZE_GOSSIP_STONE_LOWER]           = ItemLocation::HintStone(RC_SFM_MAZE_LOWER_GOSSIP_STONE,     "SFM Maze Lower Gossip Stone");
    locationTable[SFM_MAZE_GOSSIP_STONE_UPPER]           = ItemLocation::HintStone(RC_SFM_MAZE_UPPER_GOSSIP_STONE,     "SFM Maze Upper Gossip Stone");
    locationTable[SFM_SARIA_GOSSIP_STONE]                = ItemLocation::HintStone(RC_SFM_SARIA_GOSSIP_STONE,          "SFM Saria Gossip Stone");
    locationTable[TOT_GOSSIP_STONE_LEFT]                 = ItemLocation::HintStone(RC_TOT_LEFT_GOSSIP_STONE,           "ToT Left Gossip Stone");
    locationTable[TOT_GOSSIP_STONE_RIGHT]                = ItemLocation::HintStone(RC_TOT_RIGHT_GOSSIP_STONE,          "ToT Left Center Gossip Stone");
    locationTable[TOT_GOSSIP_STONE_RIGHT_CENTER]         = ItemLocation::HintStone(RC_TOT_RIGHT_CENTER_GOSSIP_STONE,   "ToT Right Center Gossip Stone");
    locationTable[TOT_GOSSIP_STONE_LEFT_CENTER]          = ItemLocation::HintStone(RC_TOT_LEFT_CENTER_GOSSIP_STONE,    "ToT Right Gossip Stone");
    locationTable[ZD_GOSSIP_STONE]                       = ItemLocation::HintStone(RC_ZD_GOSSIP_STONE,                 "ZD Gossip Stone");
    locationTable[ZF_FAIRY_GOSSIP_STONE]                 = ItemLocation::HintStone(RC_FAIRY_GOSSIP_STONE,              "Fairy Gossip Stone");
    locationTable[ZF_JABU_GOSSIP_STONE]                  = ItemLocation::HintStone(RC_JABU_GOSSIP_STONE,               "Jabu Gossip Stone");
    locationTable[ZR_NEAR_GROTTOS_GOSSIP_STONE]          = ItemLocation::HintStone(RC_ZR_NEAR_GROTTOS_GOSSIP_STONE,    "ZR Near Grottos Gossip Stone");
    locationTable[ZR_NEAR_DOMAIN_GOSSIP_STONE]           = ItemLocation::HintStone(RC_ZR_NEAR_DOMAIN_GOSSIP_STONE,     "ZR Near Domain Gossip Stone");
    locationTable[HF_COW_GROTTO_GOSSIP_STONE]            = ItemLocation::HintStone(RC_HF_COW_GROTTO_GOSSIP_STONE,      "HF Cow Grotto Gossip Stone");

    locationTable[HF_NEAR_MARKET_GROTTO_GOSSIP_STONE]    = ItemLocation::HintStone(RC_HF_NEAR_MARKET_GOSSIP_STONE,     "HF Near Market Gossip Stone");
    locationTable[HF_SOUTHEAST_GROTTO_GOSSIP_STONE]      = ItemLocation::HintStone(RC_HF_SOUTHEAST_GOSSIP_STONE,       "HF Southeast Gossip Stone");
    locationTable[HF_OPEN_GROTTO_GOSSIP_STONE]           = ItemLocation::HintStone(RC_HF_OPEN_GROTTO_GOSSIP_STONE,     "HF Open Grotto Gossip Stone");
    locationTable[KAK_OPEN_GROTTO_GOSSIP_STONE]          = ItemLocation::HintStone(RC_KAK_OPEN_GROTTO_GOSSIP_STONE,    "Kak Open Grotto Gossip Stone");
    locationTable[ZR_OPEN_GROTTO_GOSSIP_STONE]           = ItemLocation::HintStone(RC_ZR_OPEN_GROTTO_GOSSIP_STONE,     "ZR Open Grotto Gossip Stone");
    locationTable[KF_STORMS_GROTTO_GOSSIP_STONE]         = ItemLocation::HintStone(RC_KF_STORMS_GOSSIP_STONE,          "KF Storms Gossip Stone");
    locationTable[LW_NEAR_SHORTCUTS_GROTTO_GOSSIP_STONE] = ItemLocation::HintStone(RC_LW_NEAR_SHORTCUTS_GOSSIP_STONE,  "LW Near Shortcuts Gossip Stone");
    locationTable[DMT_STORMS_GROTTO_GOSSIP_STONE]        = ItemLocation::HintStone(RC_DMT_STORMS_GROTTO_GOSSIP_STONE,  "DMT Storms Grotto Gossip Stone");
    locationTable[DMC_UPPER_GROTTO_GOSSIP_STONE]         = ItemLocation::HintStone(RC_DMC_UPPER_GROTTO_GOSSIP_STONE,   "DMC Upper Grotto Gossip Stone");

    locationTable[GANONDORF_HINT]                        = ItemLocation::OtherHint(RC_GANONDORF_HINT,                  "Ganondorf Hint");
<<<<<<< HEAD
    locationTable[TRIFORCE_COMPLETED]                    = ItemLocation::Reward (RC_TRIFORCE_COMPLETED, 0xFF, "Completed Triforce", NONE, TRIFORCE_COMPLETED, {}, SpoilerCollectionCheck::None(), SpoilerCollectionCheckGroup::GROUP_NO_GROUP);
=======
    locationTable[DAMPE_HINT]                            = ItemLocation::OtherHint(RC_DAMPE_HINT,                      "Dampe's Diary Hint");
    locationTable[GREG_HINT]                             = ItemLocation::OtherHint(RC_GREG_HINT,                       "Greg Hint");
<<<<<<< HEAD
>>>>>>> 6042cd1a (Initial implementation of no-duplicates of special hints)
=======
    locationTable[ALTAR_HINT_CHILD]                      = ItemLocation::OtherHint(RC_ALTAR_HINT_CHILD,                "ToT Child Altar Text");
    locationTable[ALTAR_HINT_ADULT]                      = ItemLocation::OtherHint(RC_ALTAR_HINT_ADULT,                "ToT Adult Altar Text");

>>>>>>> 9dd1158a (stupid fixes)

    for (int i = NONE; i != KEY_ENUM_MAX; i++)
        locationLookupTable.insert(std::make_pair(locationTable[i].GetRandomizerCheck(), static_cast<Key>(i)));
}

std::vector<uint32_t> KF_ShopLocations = {
  KF_SHOP_ITEM_1,
  KF_SHOP_ITEM_2,
  KF_SHOP_ITEM_3,
  KF_SHOP_ITEM_4,
  KF_SHOP_ITEM_5,
  KF_SHOP_ITEM_6,
  KF_SHOP_ITEM_7,
  KF_SHOP_ITEM_8,
};
std::vector<uint32_t> Kak_PotionShopLocations = {
  KAK_POTION_SHOP_ITEM_1,
  KAK_POTION_SHOP_ITEM_2,
  KAK_POTION_SHOP_ITEM_3,
  KAK_POTION_SHOP_ITEM_4,
  KAK_POTION_SHOP_ITEM_5,
  KAK_POTION_SHOP_ITEM_6,
  KAK_POTION_SHOP_ITEM_7,
  KAK_POTION_SHOP_ITEM_8,
};
std::vector<uint32_t> MK_BombchuShopLocations = {
  MARKET_BOMBCHU_SHOP_ITEM_1,
  MARKET_BOMBCHU_SHOP_ITEM_2,
  MARKET_BOMBCHU_SHOP_ITEM_3,
  MARKET_BOMBCHU_SHOP_ITEM_4,
  MARKET_BOMBCHU_SHOP_ITEM_5,
  MARKET_BOMBCHU_SHOP_ITEM_6,
  MARKET_BOMBCHU_SHOP_ITEM_7,
  MARKET_BOMBCHU_SHOP_ITEM_8,
};
std::vector<uint32_t> MK_PotionShopLocations = {
  MARKET_POTION_SHOP_ITEM_1,
  MARKET_POTION_SHOP_ITEM_2,
  MARKET_POTION_SHOP_ITEM_3,
  MARKET_POTION_SHOP_ITEM_4,
  MARKET_POTION_SHOP_ITEM_5,
  MARKET_POTION_SHOP_ITEM_6,
  MARKET_POTION_SHOP_ITEM_7,
  MARKET_POTION_SHOP_ITEM_8,
};
std::vector<uint32_t> MK_BazaarLocations = {
  MARKET_BAZAAR_ITEM_1,
  MARKET_BAZAAR_ITEM_2,
  MARKET_BAZAAR_ITEM_3,
  MARKET_BAZAAR_ITEM_4,
  MARKET_BAZAAR_ITEM_5,
  MARKET_BAZAAR_ITEM_6,
  MARKET_BAZAAR_ITEM_7,
  MARKET_BAZAAR_ITEM_8,
};
std::vector<uint32_t> Kak_BazaarLocations = {
  KAK_BAZAAR_ITEM_1,
  KAK_BAZAAR_ITEM_2,
  KAK_BAZAAR_ITEM_3,
  KAK_BAZAAR_ITEM_4,
  KAK_BAZAAR_ITEM_5,
  KAK_BAZAAR_ITEM_6,
  KAK_BAZAAR_ITEM_7,
  KAK_BAZAAR_ITEM_8,
};
std::vector<uint32_t> ZD_ShopLocations = {
  ZD_SHOP_ITEM_1,
  ZD_SHOP_ITEM_2,
  ZD_SHOP_ITEM_3,
  ZD_SHOP_ITEM_4,
  ZD_SHOP_ITEM_5,
  ZD_SHOP_ITEM_6,
  ZD_SHOP_ITEM_7,
  ZD_SHOP_ITEM_8,
};
std::vector<uint32_t> GC_ShopLocations = {
  GC_SHOP_ITEM_1,
  GC_SHOP_ITEM_2,
  GC_SHOP_ITEM_3,
  GC_SHOP_ITEM_4,
  GC_SHOP_ITEM_5,
  GC_SHOP_ITEM_6,
  GC_SHOP_ITEM_7,
  GC_SHOP_ITEM_8,
};
//List of shop location lists, used for shop shuffle
std::vector<std::vector<uint32_t>> ShopLocationLists = {
  KF_ShopLocations,
  Kak_PotionShopLocations,
  MK_BombchuShopLocations,
  MK_PotionShopLocations,
  MK_BazaarLocations,
  Kak_BazaarLocations,
  ZD_ShopLocations,
  GC_ShopLocations,
};

//List of scrubs, used for pricing the scrubs
std::vector<uint32_t> ScrubLocations = {
  LW_DEKU_SCRUB_NEAR_DEKU_THEATER_RIGHT,
  LW_DEKU_SCRUB_NEAR_DEKU_THEATER_LEFT,
  LW_DEKU_SCRUB_NEAR_BRIDGE,
  LW_DEKU_SCRUB_GROTTO_REAR,
  LW_DEKU_SCRUB_GROTTO_FRONT,
  SFM_DEKU_SCRUB_GROTTO_REAR,
  SFM_DEKU_SCRUB_GROTTO_FRONT,
  HF_DEKU_SCRUB_GROTTO,
  LH_DEKU_SCRUB_GROTTO_LEFT,
  LH_DEKU_SCRUB_GROTTO_RIGHT,
  LH_DEKU_SCRUB_GROTTO_CENTER,
  GV_DEKU_SCRUB_GROTTO_REAR,
  GV_DEKU_SCRUB_GROTTO_FRONT,
  COLOSSUS_DEKU_SCRUB_GROTTO_REAR,
  COLOSSUS_DEKU_SCRUB_GROTTO_FRONT,
  GC_DEKU_SCRUB_GROTTO_LEFT,
  GC_DEKU_SCRUB_GROTTO_RIGHT,
  GC_DEKU_SCRUB_GROTTO_CENTER,
  DMC_DEKU_SCRUB,
  DMC_DEKU_SCRUB_GROTTO_LEFT,
  DMC_DEKU_SCRUB_GROTTO_RIGHT,
  DMC_DEKU_SCRUB_GROTTO_CENTER,
  ZR_DEKU_SCRUB_GROTTO_REAR,
  ZR_DEKU_SCRUB_GROTTO_FRONT,
  LLR_DEKU_SCRUB_GROTTO_LEFT,
  LLR_DEKU_SCRUB_GROTTO_RIGHT,
  LLR_DEKU_SCRUB_GROTTO_CENTER,
  DEKU_TREE_MQ_DEKU_SCRUB,
  DODONGOS_CAVERN_DEKU_SCRUB_NEAR_BOMB_BAG_LEFT,
  DODONGOS_CAVERN_DEKU_SCRUB_SIDE_ROOM_NEAR_DODONGOS,
  DODONGOS_CAVERN_DEKU_SCRUB_NEAR_BOMB_BAG_RIGHT,
  DODONGOS_CAVERN_DEKU_SCRUB_LOBBY,
  DODONGOS_CAVERN_MQ_DEKU_SCRUB_LOBBY_REAR,
  DODONGOS_CAVERN_MQ_DEKU_SCRUB_LOBBY_FRONT,
  DODONGOS_CAVERN_MQ_DEKU_SCRUB_STAIRCASE,
  DODONGOS_CAVERN_MQ_DEKU_SCRUB_SIDE_ROOM_NEAR_LOWER_LIZALFOS,
  JABU_JABUS_BELLY_DEKU_SCRUB,
  GANONS_CASTLE_DEKU_SCRUB_CENTER_LEFT,
  GANONS_CASTLE_DEKU_SCRUB_CENTER_RIGHT,
  GANONS_CASTLE_DEKU_SCRUB_RIGHT,
  GANONS_CASTLE_DEKU_SCRUB_LEFT,
  GANONS_CASTLE_MQ_DEKU_SCRUB_RIGHT,
  GANONS_CASTLE_MQ_DEKU_SCRUB_CENTER_LEFT,
  GANONS_CASTLE_MQ_DEKU_SCRUB_CENTER,
  GANONS_CASTLE_MQ_DEKU_SCRUB_CENTER_RIGHT,
  GANONS_CASTLE_MQ_DEKU_SCRUB_LEFT,
};

//List of gossip stone locations for hints
std::vector<uint32_t> gossipStoneLocations = {
  DMC_GOSSIP_STONE,
  DMT_GOSSIP_STONE,
  COLOSSUS_GOSSIP_STONE,
  DODONGOS_CAVERN_GOSSIP_STONE,
  GV_GOSSIP_STONE,
  GC_MAZE_GOSSIP_STONE,
  GC_MEDIGORON_GOSSIP_STONE,
  GRAVEYARD_GOSSIP_STONE,
  HC_MALON_GOSSIP_STONE,
  HC_ROCK_WALL_GOSSIP_STONE,
  HC_STORMS_GROTTO_GOSSIP_STONE,
  KF_DEKU_TREE_GOSSIP_STONE_LEFT,
  KF_DEKU_TREE_GOSSIP_STONE_RIGHT,
  KF_GOSSIP_STONE,
  LH_LAB_GOSSIP_STONE,
  LH_GOSSIP_STONE_SOUTHEAST,
  LH_GOSSIP_STONE_SOUTHWEST,
  LW_GOSSIP_STONE,
  SFM_MAZE_GOSSIP_STONE_LOWER,
  SFM_MAZE_GOSSIP_STONE_UPPER,
  SFM_SARIA_GOSSIP_STONE,
  TOT_GOSSIP_STONE_LEFT,
  TOT_GOSSIP_STONE_RIGHT,
  TOT_GOSSIP_STONE_RIGHT_CENTER,
  TOT_GOSSIP_STONE_LEFT_CENTER,
  ZD_GOSSIP_STONE,
  ZF_FAIRY_GOSSIP_STONE,
  ZF_JABU_GOSSIP_STONE,
  ZR_NEAR_GROTTOS_GOSSIP_STONE,
  ZR_NEAR_DOMAIN_GOSSIP_STONE,
  HF_COW_GROTTO_GOSSIP_STONE,
  HF_NEAR_MARKET_GROTTO_GOSSIP_STONE,
  HF_SOUTHEAST_GROTTO_GOSSIP_STONE,
  HF_OPEN_GROTTO_GOSSIP_STONE,
  KAK_OPEN_GROTTO_GOSSIP_STONE,
  ZR_OPEN_GROTTO_GOSSIP_STONE,
  KF_STORMS_GROTTO_GOSSIP_STONE,
  LW_NEAR_SHORTCUTS_GROTTO_GOSSIP_STONE,
  DMT_STORMS_GROTTO_GOSSIP_STONE,
  DMC_UPPER_GROTTO_GOSSIP_STONE,
};

std::vector<uint32_t> dungeonRewardLocations = {
  //Bosses
  QUEEN_GOHMA,
  KING_DODONGO,
  BARINADE,
  PHANTOM_GANON,
  VOLVAGIA,
  MORPHA,
  TWINROVA,
  BONGO_BONGO,
  LINKS_POCKET,
};
std::vector<uint32_t> overworldLocations = {
  //Kokiri Forest
  KF_KOKIRI_SWORD_CHEST,
  KF_MIDOS_TOP_LEFT_CHEST,
  KF_MIDOS_TOP_RIGHT_CHEST,
  KF_MIDOS_BOTTOM_LEFT_CHEST,
  KF_MIDOS_BOTTOM_RIGHT_CHEST,
  KF_STORMS_GROTTO_CHEST,
  KF_LINKS_HOUSE_COW,

  //Shop
  KF_SHOP_ITEM_1,
  KF_SHOP_ITEM_2,
  KF_SHOP_ITEM_3,
  KF_SHOP_ITEM_4,
  KF_SHOP_ITEM_5,
  KF_SHOP_ITEM_6,
  KF_SHOP_ITEM_7,
  KF_SHOP_ITEM_8,

  //Lost Woods
  LW_GIFT_FROM_SARIA,
  LW_SKULL_KID,
  LW_TRADE_COJIRO,
  LW_TRADE_ODD_POTION,
  LW_OCARINA_MEMORY_GAME,
  LW_TARGET_IN_WOODS,
  LW_DEKU_SCRUB_NEAR_DEKU_THEATER_RIGHT,
  LW_DEKU_SCRUB_NEAR_DEKU_THEATER_LEFT,
  LW_DEKU_SCRUB_NEAR_BRIDGE,
  LW_NEAR_SHORTCUTS_GROTTO_CHEST,
  LW_DEKU_SCRUB_GROTTO_REAR,
  LW_DEKU_SCRUB_GROTTO_FRONT,
  DEKU_THEATER_SKULL_MASK,
  DEKU_THEATER_MASK_OF_TRUTH,

  //Sacred Forest Meadow
  SONG_FROM_SARIA,
  SHEIK_IN_FOREST,
  SFM_WOLFOS_GROTTO_CHEST,
  SFM_DEKU_SCRUB_GROTTO_REAR,
  SFM_DEKU_SCRUB_GROTTO_FRONT,

  //Hyrule Field
  HF_SOUTHEAST_GROTTO_CHEST,
  HF_OPEN_GROTTO_CHEST,
  HF_NEAR_MARKET_GROTTO_CHEST,
  HF_OCARINA_OF_TIME_ITEM,
  SONG_FROM_OCARINA_OF_TIME,
  HF_TEKTITE_GROTTO_FREESTANDING_POH,
  HF_DEKU_SCRUB_GROTTO,
  HF_COW_GROTTO_COW,

  //Lake Hylia
  LH_CHILD_FISHING,
  LH_ADULT_FISHING,
  LH_LAB_DIVE,
  LH_TRADE_FROG,
  LH_UNDERWATER_ITEM,
  LH_SUN,
  LH_FREESTANDING_POH,
  LH_DEKU_SCRUB_GROTTO_LEFT,
  LH_DEKU_SCRUB_GROTTO_RIGHT,
  LH_DEKU_SCRUB_GROTTO_CENTER,

  //Gerudo Valley
  GV_CHEST,
  GV_TRADE_SAW,
  GV_WATERFALL_FREESTANDING_POH,
  GV_CRATE_FREESTANDING_POH,
  GV_DEKU_SCRUB_GROTTO_REAR,
  GV_DEKU_SCRUB_GROTTO_FRONT,
  GV_COW,

  //Gerudo Fortress
  GF_CHEST,
  GF_HBA_1000_POINTS,
  GF_HBA_1500_POINTS,
  GF_NORTH_F1_CARPENTER,
  GF_NORTH_F2_CARPENTER,
  GF_SOUTH_F1_CARPENTER,
  GF_SOUTH_F2_CARPENTER,
  GF_GERUDO_MEMBERSHIP_CARD,

  //Haunted Wasteland
  WASTELAND_CHEST,
  WASTELAND_BOMBCHU_SALESMAN,

  //Desert Colossus
  SHEIK_AT_COLOSSUS,
  COLOSSUS_FREESTANDING_POH,
  COLOSSUS_GREAT_FAIRY_REWARD,
  COLOSSUS_DEKU_SCRUB_GROTTO_REAR,
  COLOSSUS_DEKU_SCRUB_GROTTO_FRONT,

  //Market
  MARKET_TREASURE_CHEST_GAME_REWARD,
  MARKET_BOMBCHU_BOWLING_FIRST_PRIZE,
  MARKET_BOMBCHU_BOWLING_SECOND_PRIZE,
  MARKET_BOMBCHU_BOWLING_BOMBCHUS,
  MARKET_LOST_DOG,
  MARKET_SHOOTING_GALLERY_REWARD,
  MARKET_10_BIG_POES,
  MARKET_TREASURE_CHEST_GAME_ITEM_1,
  MARKET_TREASURE_CHEST_GAME_ITEM_2,
  MARKET_TREASURE_CHEST_GAME_ITEM_3,
  MARKET_TREASURE_CHEST_GAME_ITEM_4,
  MARKET_TREASURE_CHEST_GAME_ITEM_5,

  //Market Shops
  MARKET_BOMBCHU_SHOP_ITEM_1,
  MARKET_BOMBCHU_SHOP_ITEM_2,
  MARKET_BOMBCHU_SHOP_ITEM_3,
  MARKET_BOMBCHU_SHOP_ITEM_4,
  MARKET_BOMBCHU_SHOP_ITEM_5,
  MARKET_BOMBCHU_SHOP_ITEM_6,
  MARKET_BOMBCHU_SHOP_ITEM_7,
  MARKET_BOMBCHU_SHOP_ITEM_8,
  MARKET_POTION_SHOP_ITEM_1,
  MARKET_POTION_SHOP_ITEM_2,
  MARKET_POTION_SHOP_ITEM_3,
  MARKET_POTION_SHOP_ITEM_4,
  MARKET_POTION_SHOP_ITEM_5,
  MARKET_POTION_SHOP_ITEM_6,
  MARKET_POTION_SHOP_ITEM_7,
  MARKET_POTION_SHOP_ITEM_8,
  MARKET_BAZAAR_ITEM_1,
  MARKET_BAZAAR_ITEM_2,
  MARKET_BAZAAR_ITEM_3,
  MARKET_BAZAAR_ITEM_4,
  MARKET_BAZAAR_ITEM_5,
  MARKET_BAZAAR_ITEM_6,
  MARKET_BAZAAR_ITEM_7,
  MARKET_BAZAAR_ITEM_8,

  //Hyrule Castle
  HC_MALON_EGG,
  HC_ZELDAS_LETTER,
  SONG_FROM_IMPA,
  HC_GREAT_FAIRY_REWARD,
  OGC_GREAT_FAIRY_REWARD,

  //Temple of Time
  SHEIK_AT_TEMPLE,
  TOT_LIGHT_ARROWS_CUTSCENE,

  //Kakariko
  SHEIK_IN_KAKARIKO,
  KAK_REDEAD_GROTTO_CHEST,
  KAK_OPEN_GROTTO_CHEST,
  KAK_10_GOLD_SKULLTULA_REWARD,
  KAK_20_GOLD_SKULLTULA_REWARD,
  KAK_30_GOLD_SKULLTULA_REWARD,
  KAK_40_GOLD_SKULLTULA_REWARD,
  KAK_50_GOLD_SKULLTULA_REWARD,
  KAK_100_GOLD_SKULLTULA_REWARD,
  KAK_MAN_ON_ROOF,
  KAK_SHOOTING_GALLERY_REWARD,
  KAK_TRADE_ODD_MUSHROOM,
  KAK_GRANNYS_SHOP,
  KAK_ANJU_AS_CHILD,
  KAK_ANJU_AS_ADULT,
  KAK_TRADE_POCKET_CUCCO,
  KAK_IMPAS_HOUSE_FREESTANDING_POH,
  KAK_WINDMILL_FREESTANDING_POH,
  SONG_FROM_WINDMILL,
  KAK_IMPAS_HOUSE_COW,

  //Kakariko Shops
  KAK_POTION_SHOP_ITEM_1,
  KAK_POTION_SHOP_ITEM_2,
  KAK_POTION_SHOP_ITEM_3,
  KAK_POTION_SHOP_ITEM_4,
  KAK_POTION_SHOP_ITEM_5,
  KAK_POTION_SHOP_ITEM_6,
  KAK_POTION_SHOP_ITEM_7,
  KAK_POTION_SHOP_ITEM_8,
  KAK_BAZAAR_ITEM_1,
  KAK_BAZAAR_ITEM_2,
  KAK_BAZAAR_ITEM_3,
  KAK_BAZAAR_ITEM_4,
  KAK_BAZAAR_ITEM_5,
  KAK_BAZAAR_ITEM_6,
  KAK_BAZAAR_ITEM_7,
  KAK_BAZAAR_ITEM_8,

  //Graveyard
  GRAVEYARD_HOOKSHOT_CHEST,
  GRAVEYARD_SHIELD_GRAVE_CHEST,
  GRAVEYARD_HEART_PIECE_GRAVE_CHEST,
  GRAVEYARD_COMPOSERS_GRAVE_CHEST,
  SONG_FROM_COMPOSERS_GRAVE,
  GRAVEYARD_FREESTANDING_POH,
  GRAVEYARD_DAMPE_RACE_FREESTANDING_POH,
  GRAVEYARD_DAMPE_GRAVEDIGGING_TOUR,

  //Death Mountain Trail
  DMT_CHEST,
  DMT_STORMS_GROTTO_CHEST,
  DMT_TRADE_BROKEN_SWORD,
  DMT_TRADE_EYEDROPS,
  DMT_TRADE_CLAIM_CHECK,
  DMT_GREAT_FAIRY_REWARD,
  DMT_FREESTANDING_POH,
  DMT_COW_GROTTO_COW,

  //Goron City
  GC_MAZE_LEFT_CHEST,
  GC_MAZE_CENTER_CHEST,
  GC_MAZE_RIGHT_CHEST,
  GC_ROLLING_GORON_AS_CHILD,
  GC_ROLLING_GORON_AS_ADULT,
  GC_DARUNIAS_JOY,
  GC_POT_FREESTANDING_POH,
  GC_DEKU_SCRUB_GROTTO_LEFT,
  GC_DEKU_SCRUB_GROTTO_RIGHT,
  GC_DEKU_SCRUB_GROTTO_CENTER,
  GC_MEDIGORON,

  //Goron City Shop
  GC_SHOP_ITEM_1,
  GC_SHOP_ITEM_2,
  GC_SHOP_ITEM_3,
  GC_SHOP_ITEM_4,
  GC_SHOP_ITEM_5,
  GC_SHOP_ITEM_6,
  GC_SHOP_ITEM_7,
  GC_SHOP_ITEM_8,

  //Death Mountain
  DMC_UPPER_GROTTO_CHEST,
  DMC_WALL_FREESTANDING_POH,
  DMC_VOLCANO_FREESTANDING_POH,
  SHEIK_IN_CRATER,
  DMC_DEKU_SCRUB,
  DMC_GREAT_FAIRY_REWARD,
  DMC_DEKU_SCRUB_GROTTO_LEFT,
  DMC_DEKU_SCRUB_GROTTO_RIGHT,
  DMC_DEKU_SCRUB_GROTTO_CENTER,

  //Zoras River
  ZR_OPEN_GROTTO_CHEST,
  ZR_MAGIC_BEAN_SALESMAN,
  ZR_FROGS_ZELDAS_LULLABY,
  ZR_FROGS_EPONAS_SONG,
  ZR_FROGS_SARIAS_SONG,
  ZR_FROGS_SUNS_SONG,
  ZR_FROGS_SONG_OF_TIME,
  ZR_FROGS_IN_THE_RAIN,
  ZR_FROGS_OCARINA_GAME,
  ZR_NEAR_OPEN_GROTTO_FREESTANDING_POH,
  ZR_NEAR_DOMAIN_FREESTANDING_POH,
  ZR_DEKU_SCRUB_GROTTO_REAR,
  ZR_DEKU_SCRUB_GROTTO_FRONT,

  //Zoras Domain
  ZD_CHEST,
  ZD_DIVING_MINIGAME,
  ZD_KING_ZORA_THAWED,
  ZD_TRADE_PRESCRIPTION,

  //Zora's Domain Shop
  ZD_SHOP_ITEM_1,
  ZD_SHOP_ITEM_2,
  ZD_SHOP_ITEM_3,
  ZD_SHOP_ITEM_4,
  ZD_SHOP_ITEM_5,
  ZD_SHOP_ITEM_6,
  ZD_SHOP_ITEM_7,
  ZD_SHOP_ITEM_8,

  //Zoras Fountain
  ZF_ICEBERG_FREESTANDING_POH,
  ZF_BOTTOM_FREESTANDING_POH,
  ZF_GREAT_FAIRY_REWARD,

  //Lon Lon Ranch
  SONG_FROM_MALON,
  LLR_TALONS_CHICKENS,
  LLR_FREESTANDING_POH,
  LLR_DEKU_SCRUB_GROTTO_LEFT,
  LLR_DEKU_SCRUB_GROTTO_RIGHT,
  LLR_DEKU_SCRUB_GROTTO_CENTER,
  LLR_STABLES_LEFT_COW,
  LLR_STABLES_RIGHT_COW,
  LLR_TOWER_LEFT_COW,
  LLR_TOWER_RIGHT_COW,

  /*-------------------------------
     --- GOLD SKULLTULA TOKENS ---
    -------------------------------*/

  //Overworld
  KF_GS_BEAN_PATCH,
  KF_GS_KNOW_IT_ALL_HOUSE,
  KF_GS_HOUSE_OF_TWINS,

  LW_GS_BEAN_PATCH_NEAR_BRIDGE,
  LW_GS_BEAN_PATCH_NEAR_THEATER,
  LW_GS_ABOVE_THEATER,
  SFM_GS,

  HF_GS_COW_GROTTO,
  HF_GS_NEAR_KAK_GROTTO,

  LH_GS_BEAN_PATCH,
  LH_GS_SMALL_ISLAND,
  LH_GS_LAB_WALL,
  LH_GS_LAB_CRATE,
  LH_GS_TREE,

  GV_GS_BEAN_PATCH,
  GV_GS_SMALL_BRIDGE,
  GV_GS_PILLAR,
  GV_GS_BEHIND_TENT,

  GF_GS_ARCHERY_RANGE,
  GF_GS_TOP_FLOOR,

  WASTELAND_GS,
  COLOSSUS_GS_BEAN_PATCH,
  COLOSSUS_GS_HILL,
  COLOSSUS_GS_TREE,

  OGC_GS,
  HC_GS_STORMS_GROTTO,
  HC_GS_TREE,
  MARKET_GS_GUARD_HOUSE,

  KAK_GS_HOUSE_UNDER_CONSTRUCTION,
  KAK_GS_SKULLTULA_HOUSE,
  KAK_GS_GUARDS_HOUSE,
  KAK_GS_TREE,
  KAK_GS_WATCHTOWER,
  KAK_GS_ABOVE_IMPAS_HOUSE,

  DMC_GS_BEAN_PATCH,
  DMC_GS_CRATE,

  DMT_GS_BEAN_PATCH,
  DMT_GS_NEAR_KAK,
  DMT_GS_ABOVE_DODONGOS_CAVERN,
  DMT_GS_FALLING_ROCKS_PATH,

  GC_GS_CENTER_PLATFORM,
  GC_GS_BOULDER_MAZE,
  GRAVEYARD_GS_WALL,
  GRAVEYARD_GS_BEAN_PATCH,

  ZR_GS_LADDER,
  ZR_GS_TREE,
  ZR_GS_ABOVE_BRIDGE,
  ZR_GS_NEAR_RAISED_GROTTOS,

  ZD_GS_FROZEN_WATERFALL,
  ZF_GS_ABOVE_THE_LOG,
  ZF_GS_HIDDEN_CAVE,
  ZF_GS_TREE,

  LLR_GS_BACK_WALL,
  LLR_GS_RAIN_SHED,
  LLR_GS_HOUSE_WINDOW,
  LLR_GS_TREE,
};

ItemLocation* Location(uint32_t locKey) {
    return &(locationTable[locKey]);
}

ItemLocation* Location(RandomizerCheck rc) {
    return &(locationTable[locationLookupTable[rc]]);
}

std::vector<uint32_t> allLocations = {};
std::vector<uint32_t> everyPossibleLocation = {};

//set of overrides to write to the patch
std::set<ItemOverride, ItemOverride_Compare> overrides = {};
std::unordered_map<RandomizerCheck, uint8_t> iceTrapModels = {};

std::vector<std::vector<uint32_t>> playthroughLocations;
std::vector<uint32_t> wothLocations;
bool playthroughBeatable = false;
bool allLocationsReachable = false;
bool showItemProgress = false;

uint16_t itemsPlaced = 0;

void AddLocation(uint32_t loc, std::vector<uint32_t>* destination = &allLocations) {
  destination->push_back(loc);
}

template <typename Container>
void AddLocations(const Container& locations, std::vector<uint32_t>* destination = &allLocations) {
  destination->insert(destination->end(), std::cbegin(locations), std::cend(locations));
}

//sort through Vanilla and MQ dungeon locations
void GenerateLocationPool() {

  allLocations.clear();
  AddLocation(LINKS_POCKET);
  if (Settings::TriforceHunt.Is(TRIFORCE_HUNT_ON)) {
    AddLocation(TRIFORCE_COMPLETED);
  }
  AddLocations(overworldLocations);

  for (auto dungeon : Dungeon::dungeonList) {
    AddLocations(dungeon->GetDungeonLocations());
  }
}

void PlaceItemInLocation(uint32_t locKey, uint32_t item, bool applyEffectImmediately /*= false*/, bool setHidden /*= false*/) {
  auto loc = Location(locKey);
  SPDLOG_DEBUG("\n");
  SPDLOG_DEBUG(ItemTable(item).GetName().GetEnglish());
  SPDLOG_DEBUG(" placed at ");
  SPDLOG_DEBUG(loc->GetName());
  SPDLOG_DEBUG("\n\n");

  if (applyEffectImmediately || Settings::Logic.Is(LOGIC_NONE) || Settings::Logic.Is(LOGIC_VANILLA)) {
    ItemTable(item).ApplyEffect();
  }

  itemsPlaced++;
  if (showItemProgress) {
    double completion = (double) itemsPlaced / (double)(allLocations.size() + dungeonRewardLocations.size());
    std::string message = "\x1b[8;10HPlacing Items.";
    message += completion > 0.25 ? "." : " ";
    message += completion > 0.50 ? "." : " ";
    printf("%s", message.c_str());
  }

  //If we're placing a non-shop item in a shop location, we want to record it for custom messages
  if (ItemTable(item).GetItemType() != ITEMTYPE_SHOP && loc->IsCategory(Category::cShop)) {
    int index = TransformShopIndex(GetShopIndex(locKey));
    NonShopItems[index].Name = ItemTable(item).GetName();
    NonShopItems[index].Repurchaseable = ItemTable(item).GetItemType() == ITEMTYPE_REFILL || ItemTable(item).GetHintKey() == PROGRESSIVE_BOMBCHUS;
  }

  loc->SetPlacedItem(item);
  if (setHidden) {
    loc->SetHidden(true);
  }
}

std::vector<uint32_t> GetLocations(const std::vector<uint32_t>& locationPool, Category categoryInclude, Category categoryExclude /*= Category::cNull*/) {
  std::vector<uint32_t> locationsInCategory;
  for (uint32_t locKey : locationPool) {
    if (Location(locKey)->IsCategory(categoryInclude) && !Location(locKey)->IsCategory(categoryExclude)) {
      locationsInCategory.push_back(locKey);
    }
  }
  return locationsInCategory;
}

void LocationReset() {
  for (uint32_t il : allLocations) {
    Location(il)->RemoveFromPool();
  }

  for (uint32_t il : dungeonRewardLocations) {
    Location(il)->RemoveFromPool();
  }

  for (uint32_t il : gossipStoneLocations) {
    Location(il)->RemoveFromPool();
  }

  Location(GANONDORF_HINT)->RemoveFromPool();
  Location(DAMPE_HINT)->RemoveFromPool();
  Location(GREG_HINT)->RemoveFromPool();
  Location(ALTAR_HINT_CHILD)->RemoveFromPool();
  Location(ALTAR_HINT_ADULT)->RemoveFromPool();
 
}

void ItemReset() {
  for (uint32_t il : allLocations) {
    Location(il)->ResetVariables();
  }

  for (uint32_t il : dungeonRewardLocations) {
    Location(il)->ResetVariables();
  }

  itemsPlaced = 0;
}

void HintReset() {
  for (uint32_t il : gossipStoneLocations) {
    Location(il)->ResetVariables();
  }
}

//Fills everyPossibleLocation and creates an exclusion option for each location.
//everyPossibleLocation is used in the menu to lock/hide excluding locations
void AddExcludedOptions() {
  AddLocations(overworldLocations, &everyPossibleLocation);

  for (auto dungeon : Dungeon::dungeonList) {
    AddLocations(dungeon->GetEveryLocation(), &everyPossibleLocation);
  }

  for (uint32_t il: everyPossibleLocation) {
    Location(il)->AddExcludeOption();
  }
}

void CreateItemOverrides() {
    SPDLOG_DEBUG("NOW CREATING OVERRIDES\n\n");
    for (uint32_t locKey : allLocations) {
        auto loc = Location(locKey);
        ItemOverride_Value val = ItemTable(loc->GetPlaceduint32_t()).Value();
        // If this is an ice trap, store the disguise model in iceTrapModels
        if (loc->GetPlaceduint32_t() == ICE_TRAP) {
            iceTrapModels[loc->GetRandomizerCheck()] = val.looksLikeItemId;
            // If this is ice trap is in a shop, change the name based on what the model will look like
            if (loc->IsCategory(Category::cShop)) {
                NonShopItems[TransformShopIndex(GetShopIndex(locKey))].Name = GetIceTrapName(val.looksLikeItemId);
            }
        }
        overrides.insert({
            .key = loc->Key(),
            .value = val,
        });
        SPDLOG_DEBUG("\tScene: ");
        SPDLOG_DEBUG(std::to_string(loc->Key().scene));
        SPDLOG_DEBUG("\tType: ");
        SPDLOG_DEBUG(std::to_string(loc->Key().type));
        SPDLOG_DEBUG("\t");
        SPDLOG_DEBUG(loc->GetName());
        SPDLOG_DEBUG(": ");
        SPDLOG_DEBUG(loc->GetPlacedItemName().GetEnglish());
        SPDLOG_DEBUG("\n");
    }
    SPDLOG_DEBUG("Overrides Created: ");
    SPDLOG_DEBUG(std::to_string(overrides.size()));
}

