#pragma once

#include "../include/macros.h"

typedef enum {
    TEXT_NONE = 0x000,
    TEXT_SKULLTULA_PEOPLE_CURSE_BROKEN = 0x0021,
    TEXT_SKULLTULA_PEOPLE_IM_CURSED = 0x0022,
    TEXT_SKULLTULA_PEOPLE_WELL_BE_CAREFUL = 0x0023,
    TEXT_SKULLTULA_PEOPLE_STARTING_TO_WEAKEN = 0x0024,
    TEXT_SKULLTULA_PEOPLE_WE_LOOK_LIKE_THIS = 0x0025,
    TEXT_SKULLTULA_PEOPLE_GS_TUTORIAL = 0x0026,
    TEXT_SKULLTULA_PEOPLE_MAKE_YOU_VERY_RICH = 0x0027, 
    TEXT_SKULLTULA_PEOPLE_CURSE_HAS_BEEN_BROKEN = 0x0028,
    TEXT_SKULLTULA_PEOPLE_SAVING_MY_KIDS = 0x0029,
    TEXT_ITEM_KEY_SMALL = 0x0060,
    TEXT_ITEM_DUNGEON_MAP = 0x0066,
    TEXT_CHEST_GAME_REAL_GAMBLER = 0x006E,
    TEXT_ITEM_COMPASS = 0x0067,
    TEXT_CHEST_GAME_THANKS_A_LOT = 0x0084,
    TEXT_BUY_BOMBCHUS_10_PROMPT = 0x008C,
    TEXT_GS_NO_FREEZE = 0x00B4,
    TEXT_GS_FREEZE = 0x00B5,
    TEXT_BUY_BOMBCHUS_10_DESC = 0x00BC,
    TEXT_HEART_PIECE = 0x00C2,
    TEXT_HEART_CONTAINER = 0x00C6,
    TEXT_ITEM_KEY_BOSS = 0x00C7,
    TEXT_BLUE_RUPEE = 0x00CC,
    TEXT_RED_RUPEE = 0x00F0,
    TEXT_PURPLE_RUPEE = 0x00F1,
    TEXT_HUGE_RUPEE = 0x00F2,
    TEXT_RANDOMIZER_CUSTOM_ITEM = 0x00F8,
    TEXT_NAVI_DEKU_TREE_SUMMONS = 0x0140,
    TEXT_NAVI_CMON_BE_BRAVE = 0x0141,
    TEXT_NAVI_VISIT_THE_PRINCESS = 0x0142,
    TEXT_NAVI_FIND_MALONS_FATHER = 0x0143,
    TEXT_NAVI_FIND_THE_PRINCESS = 0x0144,
    TEXT_NAVI_WHAT_WOULD_SARIA_SAY = 0x0145,
    TEXT_NAVI_IMPA_SAID_DEATH_MOUNTAIN = 0x0146,
    TEXT_NAVI_USE_BOMB_FLOWER = 0x0147,
    TEXT_NAVI_FAIRY_LIVES_ON_DEATH_MOUNTAIN = 0x0148,
    TEXT_NAVI_SARIA_KNOWS_ABOUT_STONES = 0x0149,
    TEXT_NAVI_RUTO_INSIDE_JABUS_BELLY = 0x014A,
    TEXT_NAVI_COLLECTED_THREE_STONES = 0x014B,
    TEXT_NAVI_THREW_SOMETHING_IN_MOAT = 0x014C,
    TEXT_NAVI_CHECK_TEMPLE_OF_TIME = 0x014D,
    TEXT_NAVI_SHOULD_WE_BELIEVE_SHEIK = 0x014E,
    TEXT_UNUSED_014F = 0x014F,
    TEXT_NAVI_WHATS_GOING_ON_IN_FOREST = 0x0150,
    TEXT_NAVI_CLOUD_OVER_DEATH_MOUNTAIN = 0x0151,
    TEXT_NAVI_ARTIC_WIND_IS_BLOWING = 0x0152,
    TEXT_NAVI_IRON_BOOTS_WEIGH_A_TON = 0x0153,
    TEXT_NAVI_LOOK_FOR_SOMONE_WHO_KNOWS = 0x0154,
    TEXT_NAVI_IT_CAME_OUT_OF_THE_WELL = 0x0155,
    TEXT_NAVI_WHO_BUILT_THE_SPIRIT_TEMPLE = 0x0156,
    TEXT_NAVI_HAVE_YOU_EVER_PLAYED_NOCTURNE = 0x0157,
    TEXT_NAVI_WHERE_GANONDORF_WAS_BORN = 0x0158,
    TEXT_UNUSED_0159 = 0x0159,
    TEXT_NAVI_EQUIP_THE_SILVER_GAUNTLETS = 0x015A,
    TEXT_NAVI_WHO_IS_WAITING_FOR_US = 0x015B,
    TEXT_NAVI_SAVE_PRINCESS_ZELDA = 0x015C,
    TEXT_UNUSED_015D = 0x015D,
    TEXT_UNUSED_015E = 0x015E,
    TEXT_NAVI_TRY_TO_KEEP_MOVING = 0x015F,
    TEXT_SARIAS_SONG_FACE_TO_FACE = 0x0160,
    TEXT_SARIAS_SONG_FOREST_SOUNDS = 0x0161,
    TEXT_SARIAS_SONG_MR_DARUNIA = 0x0162,
    TEXT_SARIAS_SONG_SPIRITUAL_WATER = 0x0163,
    TEXT_SARIAS_SONG_SPIRITUAL_FIRE = 0x0164,
    TEXT_SARIAS_SONG_DREAD_CASTLE = 0x0165,
    TEXT_SARIAS_SONG_DIFFERENT_OCARINA = 0x0166,
    TEXT_SARIAS_SONG_EYES_DARKNESS_STORM = 0x0167,
    TEXT_SARIAS_SONG_DESERT_GODDESS = 0x0168,
    TEXT_SARIAS_SONG_TEMPLES = 0x0169,
    TEXT_SARIAS_SONG_FOREST_TEMPLE = 0x016A,
    TEXT_SARIAS_SONG_GLAD_NOW = 0x016B,
    TEXT_SARIAS_SONG_IMPRISON_GANONDORF = 0x016C,
    TEXT_SARIAS_SONG_CHANNELING_POWER = 0x016D,
    TEXT_LAKE_HYLIA_WATER_SWITCH_NAVI = 0x01B3, // 0x1yy for Navi msg range
    TEXT_MASK_SHOP_SIGN = 0x0207,
    TEXT_FROGS_UNDERWATER = 0x022E,
    TEXT_GF_HBA_SIGN = 0x031A,
    TEXT_LAKE_HYLIA_WATER_SWITCH_SIGN = 0x0346, // 0x3yy for cuttable sign range
    TEXT_WARP_MINUET_OF_FOREST = 0x088D,
    TEXT_WARP_BOLERO_OF_FIRE = 0x088E,
    TEXT_WARP_SERENADE_OF_WATER = 0x088F,
    TEXT_WARP_REQUIEM_OF_SPIRIT = 0x0890,
    TEXT_WARP_NOCTURNE_OF_SHADOW = 0x0891,
    TEXT_WARP_PRELUDE_OF_LIGHT = 0x0892,
    TEXT_SCRUB_POH = 0x10A2,
    TEXT_SARIA_SFM = 0x10AD,
    TEXT_SCRUB_STICK_UPGRADE = 0x10DC,
    TEXT_SCRUB_NUT_UPGRADE = 0x10DD,
    TEXT_MALON_FIRST_TALK_AFTER_RESCUE = 0x2000, // RANDOTODO SKIP IN RANDO
    TEXT_MALON_HOW_IS_EPONA_DOING = 0x2001,
    TEXT_MALON_EPONA_LOOKS_GREAT = 0x2002,
    TEXT_MALON_OBSTICLE_COURSE = 0x2003,
    TEXT_MALON_EVERYONE_TURNING_EVIL = 0x204C, 
    TEXT_MALON_I_SING_THIS_SONG = 0x2050,
    TEXT_MALON_EVERYONE_LIKED_SONG = 0x2051,
    TEXT_MALON_EPONA_LIKED_SONG = 0x2052,
    TEXT_RANDOMIZER_GOSSIP_STONE_HINTS = 0x2053,
    TEXT_MALON_INGO_MUST_HAVE_BEEN_TEMPTED = 0x2056,
    TEXT_MALON_LINK_HAS_TIME_BUT_NO_RECORD = 0x2090,
    TEXT_MALON_LINK_HAS_RECORD = 0x2091,
    TEXT_MALON_FIRST_BEAT_THIS_RECORD = 0x2092,
    TEXT_BIGGORON_I_MAAAADE_THISSSS = 0x3002,
    TEXT_MEDIGORON = 0x304C,
    TEXT_FIRE_TEMPLE_GORON_OWE_YOU_BIG_TIME = 0x3052,
    TEXT_BIGGORON_BETTER_AT_SMITHING = 0x3053,
    TEXT_BIGGORON_BROKEN_KNIFE = 0x3054,
    TEXT_BIGGORON_GET_THE_EYEDROPS = 0x3055,
    TEXT_BIGGORON_IM_FINISHED_EYES_ITCHY = 0x3056,
    TEXT_BIGGORON_WAITING_FOR_YOU = 0x3058,
    TEXT_BIGGORON_BROUGHT_THE_EYE_DROPS = 0x3059,
    TEXT_BIGGORON_THIS_IS_STIMULATING = 0x305A,
    TEXT_BIGGORON_RETURN_AFTER_A_FEW_DAYS = 0x305C,
    TEXT_BIGGORON_YOU_ARE_IMPATIENT = 0x305D,
    TEXT_BIGGORON_MY_FINEST_WORK = 0x305E,
    TEXT_FIRE_TEMPLE_GORON_FALLING_DOORS_SECRET = 0x3069,
    TEXT_FIRE_TEMPLE_GORON_FIRE_SECRET = 0x306A,
    TEXT_FIRE_TEMPLE_GORON_FLAME_DANCER_SECRET = 0x306B,
    TEXT_FIRE_TEMPLE_GORON_SWITCH_SECRET = 0x306C,
    TEXT_FIRE_TEMPLE_GORON_OCARINA_SECRET = 0x306D,
    TEXT_FIRE_TEMPLE_GORON_PILLAR_SECRET = 0x306E,
    TEXT_FIRE_TEMPLE_GORON_HIDDEN_DOOR_SECRET = 0x306F,
    TEXT_FIRE_TEMPLE_GORON_SOUNDS_DIFFERENT_SECRET = 0x3070,
    TEXT_BEAN_SALESMAN_BUY_FOR_10 = 0x405E,
    TEXT_BEAN_SALESMAN_BUY_FOR_20 = 0x405F,
    TEXT_BEAN_SALESMAN_BUY_FOR_30 = 0x4060,
    TEXT_BEAN_SALESMAN_BUY_FOR_40 = 0x4061,
    TEXT_BEAN_SALESMAN_BUY_FOR_50 = 0x4062,
    TEXT_BEAN_SALESMAN_BUY_FOR_60 = 0x4063,
    TEXT_BEAN_SALESMAN_BUY_FOR_70 = 0x4064,
    TEXT_BEAN_SALESMAN_BUY_FOR_80 = 0x4065,
    TEXT_BEAN_SALESMAN_BUY_FOR_90 = 0x4066,
    TEXT_BEAN_SALESMAN_BUY_FOR_100 = 0x4067,
    TEXT_BEAN_SALESMAN_OH_WELL = 0x4068,
    TEXT_BEAN_SALESMAN_NOT_ENOUGH_MONEY = 0x4069,
    TEXT_BEAN_SALESMAN_SET_A_BEAN_TO_C = 0x406A,
    TEXT_BEAN_SALESMAN_SOLD_OUT = 0x406B,
    TEXT_BEAN_SALESMAN_WANT_TO_PLANT = 0x406C,
    TEXT_FISHING_POND_START = 0x407B,
    TEXT_FISHING_TALK_ABOUT_SOMETHING = 0x4088,
    TEXT_FISHING_TRY_ANOTHER_LURE = 0x408D,
    TEXT_FISHING_SECRETS = 0x408E,
    TEXT_FISHING_GOOD_FISHERMAN = 0x408F,
    TEXT_FISHING_POND_START_MET = 0x4093,
    TEXT_FISHING_DIFFERENT_POND = 0x4094,
    TEXT_FISHING_SCRATCHING = 0x4095,
    TEXT_FISHING_CLOUDY = 0x4096,
    TEXT_FISHING_TRY_ANOTHER_LURE_WITH_SINKING_LURE = 0x40AF,
    TEXT_DAMPES_DIARY = 0x5003,
    TEXT_GRANNYS_SHOP = 0x500C,
    TEXT_ANJU_PLEASE_BRING_MY_CUCCOS_BACK = 0x5036,
    TEXT_ANJU_PLEASE_BRING_4_CUCCOS = 0x5037,
    TEXT_ANJU_PLEASE_BRING_3_CUCCOS = 0x5038,
    TEXT_ANJU_PLEASE_BRING_2_CUCCOS = 0x5039,
    TEXT_ANJU_PLEASE_BRING_1_CUCCO = 0x503A,
    TEXT_ANJU_THANKS_FOR_FINDING_MY_CUCCOS = 0x503B,
    TEXT_ANJU_ROUND_THEM_UP_OR_YOULL_PAY = 0x503C,
    TEXT_ANJU_DONT_TEASE_MY_CUCCOS = 0x503D,
    TEXT_HBA_NOT_ON_HORSE = 0x603F,
    TEXT_HBA_INITIAL_EXPLAINATION = 0x6040,
    TEXT_HBA_WANT_TO_TRY_AGAIN_YES_NO = 0x6041,
    TEXT_HBA_ALREADY_HAVE_1000 = 0x6042,
    TEXT_CARPET_SALESMAN_CUSTOM_FAIL_TO_BUY = 0x6073,
    TEXT_CARPET_SALESMAN_1 = 0x6077,
    TEXT_CARPET_SALESMAN_2 = 0x6078,
    TEXT_MARKET_GUARD_NIGHT = 0x7003,
    TEXT_FISHERMAN_LEAVE = 0x409E,
    TEXT_SHEIK_NEED_HOOK = 0x700F,
    TEXT_SHEIK_HAVE_HOOK = 0x7010,
    TEXT_ALTAR_CHILD = 0x7040,
    TEXT_CHEST_GAME_PROCEED = 0x704C,
    TEXT_GHOST_SHOP_EXPLAINATION = 0x70F4,
    TEXT_GHOST_SHOP_CARD_HAS_POINTS = 0x70F5,
    TEXT_GHOST_SHOP_BUY_NORMAL_POE = 0x70F6,
    TEXT_GHOST_SHOP_BUY_BIG_POE = 0x70F7,
    TEXT_GHOST_SHOP_1000_POINTS = 0x70F8,
    TEXT_ALTAR_ADULT = 0x7088,
    TEXT_GANONDORF = 0x70CC,
    TEXT_GANONDORF_NOHINT = 0x70CD,
    TEXT_SCRUB_RANDOM = 0x9000,
    TEXT_SCRUB_RANDOM_FREE = 0x9001,
    TEXT_SHOP_ITEM_RANDOM = 0x9100,
    TEXT_SHOP_ITEM_RANDOM_CONFIRM = 0x9100 + NUM_SHOP_ITEMS,
    TEXT_SHOP_ITEM_RANDOM_CONFIRM_END = 0x9100 + (NUM_SHOP_ITEMS * 2) - 1,
    TEXT_WARP_RANDOM_REPLACED_TEXT = 0x9200,
    TEXT_SHOOTING_GALLERY_MAN_COME_BACK_WITH_BOW = 0x9210,
    TEXT_CARPET_SALESMAN_MYSTERIOUS = 0x9211,
    TEXT_CARPET_SALESMAN_ARMS_DEALER = 0x9212,
} TextIDs;

#ifdef __cplusplus

typedef struct {
    uint16_t giid;
    ItemID iid;
    std::string english;
    std::string german;
    std::string french;
} GetItemMessage;

#define GIMESSAGE(giid, iid, english, german, french) \
    { giid, iid, english, german, french }

#define GIMESSAGE_UNTRANSLATED(giid, iid, message) \
    { giid, iid, message, message, message }

#define GIMESSAGE_NO_GERMAN(giid, iid, english, french) \
    { giid, iid, english, english, french  }

#endif
