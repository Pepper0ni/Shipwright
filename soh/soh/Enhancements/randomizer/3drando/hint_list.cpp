#include "hint_list.hpp"
#include "custom_messages.hpp"

#include "../randomizerTypes.h"
#include "../context.h"

using namespace CustomMessages;

// Big thanks to Lioncache, Gabyelnuevo, Danius88, and Charade for their translations!

// Text is {english, french, spanish}

// there are special characters that are read for certain in game commands:
// ^ is a box break
// & is a new line
// @ will print the player name
// surrounding text with '#' will make it a different color
// - OoT Randomizer

// '[[d]]' indicates a number will be placed there, numbers in [[]] will be replaced by other text in hints

std::array<HintText, RHT_MAX> hintTable;

void HintTable_Init() {
    /*--------------------------
    |       GENERAL TEXT        |
    ---------------------------*/
    hintTable[RHT_NONE] = HintText(CustomMessage("No Hint", "", "Pas d'Indice" ));
    //hintTable[RHT_PREFIX] =
        //HintText::Exclude({ Text{ "They say that ", /*french*/ "Selon moi, ", /*spanish*/ "Según dicen, " } }); RANDOTODO delete
    hintTable[RHT_WAY_OF_THE_HERO] =
        HintText(CustomMessage( "They say that #[[1]]# is on #the way of the hero#.", 
                                "",
                     /*french*/ "Selon moi, #[[1]]# est sur #la voie du héros#.", {QM_RED, QM_LBLUE}));
                 // /*spanish*/ "Según dicen, #[[1]]# conduce a la senda del héroe."
    hintTable[RHT_FOOLISH] = 
        HintText(CustomMessage( "They say that plundering #[[1]]# is #a foolish choice#.",
                                "",
                        /*french*/ "Selon moi, explorer #[[1]]# est #futile#.", {QM_RED, QM_PINK}));
                    // /*spanish*/ "Según dicen, inspeccionar #[[1]]# #no es una sabia decisión#." 
    hintTable[RHT_CAN_BE_FOUND_AT] =
        HintText(CustomMessage( "They say that #[[1]]# can be found at #[[2]]#.",
                                "",
                        /*french*/ "Selon moi, #[[1]]# se trouve dans #[[2]]#.", {QM_GREEN, QM_RED}));
                    // /*spanish*/ "Según dicen, #[[1]]# aguarda en #[[2]]#." 
    hintTable[RHT_HOARDS] = 
        HintText(CustomMessage( "They say that #[[2]]# hoards #[[1]]#.",
                                "",
                     /*french*/ "Selon moi, #[[2]]# recèle #[[1]]#.", {QM_RED, QM_GREEN}));
                    // /*spanish*/ "Según dicen, #[[2]]# acapara #[[1]]#."

    HintTable_Init_Item();
    HintTable_Init_Exclude_Overworld();
    HintTable_Init_Exclude_Dungeon();


    /*--------------------------
    |    SOMETIMES HINT TEXT   |
    ---------------------------*/

    hintTable[RHT_KF_LINKS_HOUSE_COW] = HintText(CustomMessage("#Malon's obstacle course# leads to",
                                                    /*german*/ "",
                                                    /*french*/ "la #course à obstacle de Malon# amène à"),
                                                 // /*spanish*/la #carrera de obstáculos de Malon# brinda
                                                 {},
                                                 {CustomMessage("the #bovine bounty of a horseback hustle# gifts",
                                                     /*german*/ "",
                                                     /*french*/ "le cadeau #qui découle d'une réussite équestre# est")});
                                                  // /*spanish*/la #recompensa bovina de un paseo a caballo# brinda

    hintTable[RHT_KAK_100_GOLD_SKULLTULA_REWARD] = HintText(CustomMessage("slaying #100 Gold Skulltulas# reveals",
                                                               /*german*/ "",
                                                               /*french*/ "détruire #100 Skulltulas d'or# donne"),
                                                            // /*spanish*/exterminar #100 skulltulas doradas# revela
                                                            {},
                                                            {CustomMessage("#100 bug badges# rewards",
                                                                /*german*/ "",
                                                                /*french*/ "#100 écussons# donnent"),
                                                             // /*spanish*/#100 medallas de insectos# otorgan
                                                             CustomMessage("#100 spider souls# yields",
                                                                /*german*/ "",
                                                                /*french*/ "#100 âmes d'arachnide# donnent"),
                                                             // /*spanish*/#100 almas de araña# otorgan
                                                             CustomMessage("#100 auriferous arachnids# lead to",
                                                                /*german*/ "",
                                                                /*french*/ "#100 arachnides aurifères# donnent")});
                                                             // /*spanish*/#100 arácnidos auríferos# otorgan

    hintTable[RHT_SONG_FROM_OCARINA_OF_TIME] = HintText(CustomMessage("the #Ocarina of Time# teaches",
                                                           /*german*/ "",
                                                           /*french*/ "l'#Ocarina du Temps# est accompagné par"));
                                                        // /*spanish*/la #Ocarina del Tiempo# enseña

    hintTable[RHT_SONG_FROM_ROYAL_FAMILYS_TOMB] = HintText(CustomMessage("#ReDead in the Composers' Grave# guard",
                                                              /*german*/ "",
                                                              /*french*/ "les #Éffrois du tombeau des compositeurs# protègent"));
                                                           // /*spanish*/los #ReDeads del Panteón Real# guardan

    hintTable[RHT_SHEIK_IN_FOREST] = HintText(CustomMessage("#in a meadow# Sheik teaches",
                                                 /*german*/ "",
                                                 /*french*/ "Sheik confiera, #dans un bosquet#,"));
                                              // /*spanish*/#en la pradera sagrada# Sheik enseña

    hintTable[RHT_SHEIK_AT_TEMPLE] = HintText(CustomMessage("Sheik waits at a #monument to time# to teach",
                                                 /*german*/ "",
                                                 /*french*/ "Sheik confiera, #au pied de l'épée légendaire#,"));
                                              // /*spanish*/Sheik espera en el #momumento del tiempo# para enseñar

    hintTable[RHT_SHEIK_IN_CRATER] = HintText(CustomMessage("the #crater's melody# is",
                                                 /*german*/ "",
                                                 /*french*/ "Sheik confiera, #entouré de lave#,"));
                                              // /*spanish*/la #melodía del cráter# otorga

    hintTable[RHT_SHEIK_IN_ICE_CAVERN] = HintText(CustomMessage("the #frozen cavern# echoes with",
                                                     /*german*/ "",
                                                     /*french*/ "Sheik confiera, #dans une caverne enneigée#,"));
                                                  // /*spanish*/en la #caverna de hielo# retumban los ecos de

    hintTable[RHT_SHEIK_IN_KAKARIKO] = HintText(CustomMessage("a #ravaged village# mourns with",
                                                   /*german*/ "",
                                                   /*french*/ "Sheik confirera, #au coeur d'un village ravagé#,"));
                                                // /*spanish*/un #arrasado pueblo# llora

    hintTable[RHT_SHEIK_AT_COLOSSUS] = HintText(CustomMessage("a hero ventures #beyond the wasteland# to learn",
                                                   /*german*/ "",
                                                   /*french*/ "Sheik confiera, #au bout d'un chemin sableux#,"));
                                                // /*spanish*/el héroe que se adentre #más allá del desierto# aprenderá

    hintTable[RHT_MARKET_10_BIG_POES] = HintText(CustomMessage("catching #Big Poes# leads to",
                                                    /*german*/ "",
                                                    /*french*/ "#d'attraper des Àmes# donne"),
                                                 // /*spanish*/hacerte con #Grandes Poes# conduce a
                                                 {},
                                                 {CustomMessage("#ghost hunters# will be rewarded with",
                                                     /*german*/ "",
                                                     /*french*/ "#les chasseurs de fantômes# sont récompensés avec")});
                                                  // /*spanish*/los #cazafantasmas# son premiados con

    hintTable[RHT_DEKU_THEATER_SKULL_MASK] = HintText(CustomMessage("the #Skull Mask# yields",
                                                         /*german*/ "",
                                                         /*french*/ "le #Masque de Mort# donne"));
                                                      // /*spanish*/la #máscara de calavera# otorga

    hintTable[RHT_DEKU_THEATER_MASK_OF_TRUTH] = HintText(CustomMessage("the #Mask of Truth# yields",
                                                            /*german*/ "",
                                                            /*french*/ "le #Masque de Vérité# donne"),
                                                         // /*spanish*/la #máscara de la verdad# premia
                                                         {},
                                                         {CustomMessage("showing a #truthful eye to the crowd# rewards",
                                                             /*german*/ "",
                                                             /*french*/ "montrer #l'oeil de vérité à la foule# donne")});
                                                          // /*spanish*/#mostrarle el ojo verdadero# a una multitud brinda

    hintTable[RHT_HF_OCARINA_OF_TIME_ITEM] = HintText(CustomMessage("the #treasure thrown by Princess Zelda# is",
                                                         /*german*/ "",
                                                         /*french*/ "le trésor #laissé par la princesse# est"));
                                                      // /*spanish*/el #tesoro arrojado por la Princesa Zelda# se trata de

    hintTable[RHT_DMT_TRADE_BROKEN_SWORD] = HintText(CustomMessage("a #blinded Biggoron# entrusts",
                                                        /*german*/ "",
                                                        /*french*/ "un #Grogoron aveuglé# confie"));
                                                     // /*spanish*/un #miope Biggoron# otorga

    hintTable[RHT_DMT_TRADE_EYEDROPS] = HintText(CustomMessage("while you wait, #Biggoron# gives",
                                                    /*german*/ "",
                                                    /*french*/ "pendant que tu attends, #Biggoron# donne"));
                                                 // /*spanish*/#Biggoron# está a la espera de otorgar

    hintTable[RHT_DMT_TRADE_CLAIM_CHECK] = HintText(CustomMessage("#Biggoron# crafts",
                                                       /*german*/ "",
                                                       /*french*/ "#Biggoron# fabrique"));
                                                    // /*spanish*/#Biggoron# forja

    hintTable[RHT_KAK_50_GOLD_SKULLTULA_REWARD] = HintText(CustomMessage("slaying #50 Gold Skulltulas# reveals",
                                                              /*german*/ "",
                                                              /*french*/ "détruire #50 Skulltulas d'or# donne"),
                                                           // /*spanish*/exterminar #50 skulltulas doradas# revela
                                                           {},
                                                           {CustomMessage("#50 bug badges# rewards",
                                                               /*german*/ "",
                                                               /*french*/ "#50 écussons# donnent"),
                                                            // /*spanish*/#50 medallas de insectos# otorgan
                                                            CustomMessage("#50 spider souls# yields",
                                                               /*german*/ "",
                                                               /*french*/ "#50 âmes d'arachnide# donnent"),
                                                            // /*spanish*/#50 almas de araña# otorgan
                                                            CustomMessage("#50 auriferous arachnids# lead to",
                                                               /*german*/ "",
                                                               /*french*/ "#50 arachnides aurifères# donnent")});
                                                            // /*spanish*/#50 arácnidos auríferos# otorgan

    hintTable[RHT_KAK_40_GOLD_SKULLTULA_REWARD] = HintText(CustomMessage("slaying #40 Gold Skulltulas# reveals",
                                                              /*german*/ "",
                                                              /*french*/ "détruire #40 Skulltulas d'or# donne"),
                                                           // /*spanish*/exterminar #40 skulltulas doradas# revela
                                                           {},
                                                           {CustomMessage("#40 bug badges# rewards",
                                                               /*german*/ "",
                                                               /*french*/ "#40 écussons# donnent"),
                                                            // /*spanish*/#40 medallas de insectos# otorgan
                                                            CustomMessage("#40 spider souls# yields",
                                                               /*german*/ "",
                                                               /*french*/ "#40 âmes d'arachnide# donnent"),
                                                            // /*spanish*/#40 almas de araña# otorgan
                                                            CustomMessage("#40 auriferous arachnids# lead to",
                                                               /*german*/ "",
                                                               /*french*/ "#40 arachnides aurifères# donnent")});
                                                            // /*spanish*/#40 arácnidos auríferos# otorgan

    hintTable[RHT_KAK_30_GOLD_SKULLTULA_REWARD] = HintText(CustomMessage("slaying #30 Gold Skulltulas# reveals",
                                                              /*german*/ "",
                                                              /*french*/ "détruire #30 Skulltulas d'or# donne"),
                                                           // /*spanish*/exterminar #30 skulltulas doradas# revela
                                                           {},
                                                           {CustomMessage("#30 bug badges# rewards",
                                                               /*german*/ "",
                                                               /*french*/ "#30 écussons# donnent"),
                                                            // /*spanish*/#30 medallas de insectos# otorgan
                                                            CustomMessage("#30 spider souls# yields",
                                                               /*german*/ "",
                                                               /*french*/ "#30 âmes d'arachnide# donnent"),
                                                            // /*spanish*/#30 almas de araña# otorgan
                                                            CustomMessage("#30 auriferous arachnids# lead to",
                                                               /*german*/ "",
                                                               /*french*/ "#30 arachnides aurifères# donnent")});
                                                            // /*spanish*/#30 arácnidos auríferos# otorgan

    hintTable[RHT_KAK_20_GOLD_SKULLTULA_REWARD] = HintText(CustomMessage("slaying #20 Gold Skulltulas# reveals",
                                                              /*german*/ "",
                                                              /*french*/ "détruire #20 Skulltulas d'or# donne"),
                                                           // /*spanish*/exterminar #20 skulltulas doradas# revela
                                                           {},
                                                           {CustomMessage("#20 bug badges# rewards",
                                                               /*german*/ "",
                                                               /*french*/ "#20 écussons# donnent"),
                                                            // /*spanish*/#20 medallas de insectos# otorgan
                                                            CustomMessage("#20 spider souls# yields",
                                                               /*german*/ "",
                                                               /*french*/ "#20 âmes d'arachnide# donnent"),
                                                            // /*spanish*/#20 almas de araña# otorgan
                                                            CustomMessage("#20 auriferous arachnids# lead to",
                                                               /*german*/ "",
                                                               /*french*/ "#20 arachnides aurifères# donnent")});
                                                            // /*spanish*/#20 arácnidos auríferos# otorgan

    hintTable[RHT_KAK_ANJU_AS_CHILD] = HintText(CustomMessage("#collecting cuccos# rewards",
                                                   /*german*/ "",
                                                   /*french*/ "#rapporter les Cocottes# donne"),
                                                // /*spanish*/#hacerte con todos los cucos# premia
                                                {},
                                                {CustomMessage("#wrangling roosters# rewards",
                                                    /*german*/ "",
                                                    /*french*/ "#plumer des poulets# donne"),
                                                 // /*spanish*/#atrapar a las gallinas# premia
                                                 CustomMessage("#chucking chickens# gifts",
                                                    /*german*/ "",
                                                    /*french*/ "#lancer des poulets# donne")});
                                                 // /*spanish*/#reunir a unos emplumados# premia

    hintTable[RHT_KAK_TRADE_POCKET_CUCCO] = HintText(CustomMessage("an adult's #happy Cucco# awards",
                                                        /*german*/ "",
                                                        /*french*/ "un adulte avec une #poulette joyeuse# obtient"));
                                                     // /*spanish*/un #alegre cuco# en la madurez otorga

    hintTable[RHT_KAK_TRADE_ODD_MUSHROOM] = HintText(CustomMessage("the #potion shop lady# entrusts",
                                                        /*german*/ "",
                                                        /*french*/ "la #gribiche du magasin de potion# confie"));
                                                     // /*spanish*/la #señora de la tienda de pociones# otorga

    hintTable[RHT_GC_DARUNIAS_JOY] = HintText(CustomMessage("#Darunia's dance# leads to",
                                                 /*german*/ "",
                                                 /*french*/ "#la dance de Darunia# donne"),
                                              // /*spanish*/#el baile de Darunia# conduce a
                                              {},
                                              {CustomMessage("a #groovin' goron# gifts",
                                                  /*german*/ "",
                                                  /*french*/ "#le Goron joyeux# donne")});
                                               // /*spanish*/#un goron marchoso# otorga

    hintTable[RHT_LW_SKULL_KID] = HintText(CustomMessage("the #Skull Kid# grants",
                                              /*german*/ "",
                                              /*french*/ "le #Skull Kid# donne"));
                                           // /*spanish*/#Skull Kid# otorga

    hintTable[RHT_LW_TRADE_COJIRO] = HintText(CustomMessage("returning a #special Cucco# awards",
                                                 /*german*/ "",
                                                 /*french*/ "ramener une #poulette précieuse# donne"));
                                              // /*spanish*/quien devuelva un #cuco especial# encontrará

    hintTable[RHT_LW_TRADE_ODD_POTION] = HintText(CustomMessage("a #Kokiri girl in the woods# leaves",
                                                     /*german*/ "",
                                                     /*french*/ "la #fillette Kokiri dans les bois# laisse"));
                                                  // /*spanish*/una #chica kokiri del bosque# otorga

    hintTable[RHT_LH_SUN] = HintText(CustomMessage("shooting #the sun# grants",
                                        /*german*/ "",
                                        /*french*/ "tirer une flèche dans #sur le soleil# donne"),
                                     // /*spanish*/#disparar al sol# revela
                                     {},
                                     {CustomMessage("staring into #the sun# grants",
                                         /*german*/ "",
                                         /*french*/ "regarder #le soleil# donne")});
                                      // /*spanish*/#mirar al sol# revela

    hintTable[RHT_LH_TRADE_FROG] = HintText(CustomMessage("#Lake Hylia's scientist# hurriedly entrusts",
                                               /*german*/ "",
                                               /*french*/ "le #scientifique du lac# confie rapidement"));
                                            // /*spanish*/el #científico del Lago Hylia# otorga con prisa

    hintTable[RHT_MARKET_TREASURE_CHEST_GAME_REWARD] = HintText(CustomMessage("the #treasure chest game# grants",
                                                                   /*german*/ "",
                                                                   /*french*/ "la #Chasse-aux-Trésors# donne"),
                                                                // /*spanish*/#el Cofre del Tesoro# premia
                                                                {},
                                                                {CustomMessage("#gambling# grants",
                                                                    /*german*/ "",
                                                                    /*french*/ "#parier# donne"),
                                                                 // /*spanish*/#los juegos de azar# revelan
                                                                 CustomMessage("there is a #1/32 chance# to win",
                                                                    /*german*/ "",
                                                                    /*french*/ "être #le gagnant parmi 32# donne")});
                                                                 // /*spanish*/hay una #probabilidad de 1/32# de ganar

    hintTable[RHT_MARKET_TREASURE_CHEST_GAME_ITEM_1] = HintText(CustomMessage("the #first locked room# in the chest game contains",
                                                                   /*german*/ "",
                                                                   /*french*/ "la #première salle# de la Chasse-aux-Trésors contient"),
                                                                // /*spanish*/#en la primera sala del Cofre del Tesoro# aguarda
                                                                {},
                                                                {CustomMessage("#gambling once# grants",
                                                                    /*german*/ "",
                                                                    /*french*/ "#parier une fois# donne"),
                                                                 // /*spanish*/#apostar solo una vez# revelará
                                                                 CustomMessage("the #first or second game chest# contains",
                                                                    /*german*/ "",
                                                                    /*french*/ "le #premier ou deuxième coffre à jeu# contient")});
                                                                 // /*spanish*/#el primer o segundo cofre del azar# revela

    hintTable[RHT_MARKET_TREASURE_CHEST_GAME_ITEM_2] = HintText(CustomMessage("the #second locked room# in the chest game contains",
                                                                   /*german*/ "",
                                                                   /*french*/ "la #deuxième salle# de la Chasse-aux-Trésors contient"),
                                                                // /*spanish*/#en la segunda sala del Cofre del Tesoro# aguarda
                                                                {},
                                                                {CustomMessage("#gambling twice# grants",
                                                                    /*german*/ "",
                                                                    /*french*/ "#parier deux fois# donne"),
                                                                 // /*spanish*/#apostar dos veces# revelará
                                                                 CustomMessage("the #third or fourth game chest# contains",
                                                                    /*german*/ "",
                                                                    /*french*/ "le #troisième ou quatrième coffre à jeu# contient")});
                                                                 // /*spanish*/#el tercer o cuarto cofre del azar# revela

    hintTable[RHT_MARKET_TREASURE_CHEST_GAME_ITEM_3] = HintText(CustomMessage("the #third locked room# in the chest game contains",
                                                                   /*german*/ "",
                                                                   /*french*/ "la #troisième salle# de la Chasse-aux-Trésors contient"),
                                                                // /*spanish*/#en la tercera sala del Cofre del Tesoro# aguarda
                                                                {},
                                                                {CustomMessage("#gambling 3 times# grants",
                                                                    /*german*/ "",
                                                                    /*french*/ "#parier trois fois# donne"),
                                                                 // /*spanish*/#apostar tres veces# revelará
                                                                 CustomMessage("the #fifth or sixth game chest# contains",
                                                                    /*german*/ "",
                                                                    /*french*/ "le #cinquième ou sixième coffre à jeu# contient")});
                                                                 // /*spanish*/#el quinto o sexto cofre del azar# revela

    hintTable[RHT_MARKET_TREASURE_CHEST_GAME_ITEM_4] = HintText(CustomMessage("the #fourth locked room# in the chest game contains",
                                                                   /*german*/ "",
                                                                   /*french*/ "la #quatrième salle# de la Chasse-aux-Trésors contient"),
                                                                // /*spanish*/#en la cuarta sala del Cofre del Tesoro# aguarda
                                                                {},
                                                                {CustomMessage("#gambling 4 times# grants",
                                                                    /*german*/ "",
                                                                    /*french*/ "#parier quatre fois# donne"),
                                                                 // /*spanish*/#apostar cuatro veces# revelará
                                                                 CustomMessage("the #seventh or eighth game chest# contains",
                                                                    /*german*/ "",
                                                                    /*french*/ "le #septième ou huitième coffre à jeu# contient")});
                                                                 // /*spanish*/#el séptimo u octavo cofre del azar# revela

    hintTable[RHT_MARKET_TREASURE_CHEST_GAME_ITEM_5] = HintText(CustomMessage("the #fifth locked room# in the chest game contains",
                                                                   /*german*/ "",
                                                                   /*french*/ "la #cinquième salle# de la Chasse-aux-Trésors contient"),
                                                                // /*spanish*/#en la quinta sala del Cofre del Tesoro# aguarda
                                                                {},
                                                                {CustomMessage("#gambling 5 times# grants",
                                                                    /*german*/ "",
                                                                    /*french*/ "#parier cinq fois# donne"),
                                                                 // /*spanish*/#apostar cinco veces# revelará
                                                                 CustomMessage("the #ninth or tenth game chest# contains",
                                                                    /*german*/ "",
                                                                    /*french*/ "le #neuvième ou dixième coffre à jeu# contient")});
                                                                 // /*spanish*/#el noveno o décimo cofre del azar# revela

    hintTable[RHT_GF_HBA_1500_POINTS] = HintText(CustomMessage("scoring 1500 in #horseback archery# grants",
                                                    /*german*/ "",
                                                    /*french*/ "obtenir 1500 points dans l'#archerie équestre# donne"),
                                                 // /*spanish*/conseguir 1500 puntos en el #tiro con arco a caballo# premia
                                                 {},
                                                 {CustomMessage("mastery of #horseback archery# grants",
                                                     /*german*/ "",
                                                     /*french*/ "maîtriser l'#archerie équestre# donne")});
                                                  // /*spanish*/dominar el #tiro con arco a caballo# premia con

    hintTable[RHT_GRAVEYARD_HEART_PIECE_GRAVE_CHEST] = HintText(CustomMessage("playing #Sun's Song# in a grave spawns",
                                                                   /*german*/ "",
                                                                   /*french*/ "jouer le #chant du soleil# dans un tombeau donne"));
                                                                // /*spanish*/#tocar la Canción del Sol# en una cripta conduce a

    hintTable[RHT_GC_MAZE_LEFT_CHEST] = HintText(CustomMessage("in #Goron City# the hammer unlocks",
                                                    /*german*/ "",
                                                    /*french*/ "dans le #village Goron#, le marteau donne accès à"));
                                                 // /*spanish*/en la #Ciudad Goron# el martillo desbloquea

    hintTable[RHT_GV_CHEST] = HintText(CustomMessage("in #Gerudo Valley# the hammer unlocks",
                                          /*german*/ "",
                                          /*french*/ "dans la #Vallée Gerudo#, le marteau donne accès à"));
                                       // /*spanish*/en el #Valle Gerudo# el martillo desbloquea
                                       

    hintTable[RHT_GV_TRADE_SAW] = HintText(CustomMessage("the #boss of the carpenters# leaves",
                                              /*german*/ "",
                                              /*french*/ "le #patron des ouvriers# laisse"));
                                           // /*spanish*/el #capataz de los carpinteros# otorga

    hintTable[RHT_GV_COW] = HintText(CustomMessage("a #cow in Gerudo Valley# gifts",
                                        /*german*/ "",
                                        /*french*/ "la #vache de la Vallée Gerudo# donne"));
                                     // /*spanish*/una #vaca del Valle Gerudo# brinda

    hintTable[RHT_HC_GS_STORMS_GROTTO] = HintText(CustomMessage("a #spider behind a muddy wall# in a grotto holds",
                                                     /*german*/ "",
                                                     /*french*/ "l'#araignée derrière un mur de boue# dans une grotte donne"));
                                                  // /*spanish*/una #Skulltula tras la agrietada pared# de una cueva otorga

    hintTable[RHT_HF_GS_COW_GROTTO] = HintText(CustomMessage("a #spider behind webs# in a grotto holds",
                                                  /*german*/ "",
                                                  /*french*/ "l'#araignée derrière une toile# dans une grotte donne"));
                                               // /*spanish*/una #Skulltula tras la telaraña# de una cueva otorga

    hintTable[RHT_HF_COW_GROTTO_COW] = HintText(CustomMessage("a #cow behind webs# in a grotto gifts",
                                                   /*german*/ "",
                                                   /*french*/ "la #vache derrière les toiles# d'une grotte donne"),
                                                // /*spanish*/una #vaca tras la telaraña# de una cueva brinda
                                                {},
                                                {CustomMessage("the #cobwebbed cow# gifts",
                                                    /*german*/ "",
                                                    /*french*/ "la #vache prisonnière d'araignées# donne")});
                                                 // /*spanish*/una #vaca tras una telaraña# brinda

    hintTable[RHT_ZR_FROGS_OCARINA_GAME] = HintText(CustomMessage("the final reward from the #Frogs of Zora's River# is",
                                                       /*german*/ "",
                                                       /*french*/ "la dernière récompense des #grenouilles de la Rivière Zora# est"),
                                                    // /*spanish*/la recompensa final de las #ranas del Río Zora# premia
                                                    {},
                                                    {CustomMessage("an #amphibian feast# yields",
                                                        /*german*/ "",
                                                        /*french*/ "un #festin d'amphibiens# donne"),
                                                     // /*spanish*/una #fiesta anfibia# brinda
                                                     CustomMessage("the #croaking choir's magnum opus# awards",
                                                        /*german*/ "",
                                                        /*french*/ "la #chorale coassante# donne"),
                                                     // /*spanish*/un #coro maestro de ancas# premia
                                                     CustomMessage("the #froggy finale# yields",
                                                        /*german*/ "",
                                                        /*french*/ "la #finale amphibienne# donne")});
                                                     // /*spanish*/el #gran final batracio# brinda

    hintTable[RHT_ZF_GS_HIDDEN_CAVE] = HintText(CustomMessage("a spider high #above the icy waters# holds",
                                                   /*german*/ "",
                                                   /*french*/ "l'araignée #en haut des eaux glacées# donne"));
                                                // /*spanish*/una Skulltula en lo #alto de las congeladas aguas# otorga

    hintTable[RHT_WASTELAND_CHEST] = HintText(CustomMessage("#deep in the wasteland# is",
                                                 /*german*/ "",
                                                 /*french*/ "#loin dans le désert# gît"));
                                              // /*spanish*/en lo #profundo del desierto encantado# yace

    hintTable[RHT_WASTELAND_GS] = HintText(CustomMessage("a #spider in the wasteland# holds",
                                              /*german*/ "",
                                              /*french*/ "#l'araignée dans le désert# donne"));
                                           // /*spanish*/una #Skulltula del desierto encantado# otorga

    hintTable[RHT_GRAVEYARD_ROYAL_FAMILYS_TOMB_CHEST] = HintText(CustomMessage("#flames in the Composers' Grave# reveal",
                                                                    /*german*/ "",
                                                                    /*french*/ "#les flammes dans le tombeau des compositeurs# cachent"));
                                                                 // /*spanish*/#las llamas del Panteón Real# revelan

    hintTable[RHT_ZF_BOTTOM_FREESTANDING_POH] = HintText(CustomMessage("#under the icy waters# lies",
                                                            /*german*/ "",
                                                            /*french*/ "#sous les eaux glacées# se cache"));
                                                         // /*spanish*/#bajo las congeladas aguas# yace

    hintTable[RHT_GC_POT_FREESTANDING_POH] = HintText(CustomMessage("spinning #Goron pottery# contains",
                                                         /*german*/ "",
                                                         /*french*/ "la #potterie Goron# contient"));
                                                      // /*spanish*/una #cerámica goron# contiene

    hintTable[RHT_ZD_KING_ZORA_THAWED] = HintText(CustomMessage("unfreezing #King Zora# grants",
                                                     /*german*/ "",
                                                     /*french*/ "dégeler # le Roi Zora# donne"),
                                                  // /*spanish*/#descongelar al Rey Zora# conduce a
                                                  {},
                                                  {CustomMessage("a #defrosted dignitary# gifts",
                                                      /*german*/ "",
                                                      /*french*/ "le #monarque libéré# donne")});
                                                   // /*spanish*/una #liberación monárquica# brinda

    hintTable[RHT_ZD_TRADE_PRESCRIPTION] = HintText(CustomMessage("#King Zora# hurriedly entrusts",
                                                       /*german*/ "",
                                                       /*french*/ "le #roi Zora# confie rapidement"));
                                                    // /*spanish*/el #Rey Zora# otorga con prisa

    hintTable[RHT_DMC_DEKU_SCRUB] = HintText(CustomMessage("a single #scrub in the crater# sells",
                                                /*german*/ "",
                                                /*french*/ "la #peste Mojo dans le cratère# vend"));
                                             // /*spanish*/un solitario #deku del cráter# vende
    hintTable[RHT_DMC_GS_CRATE] = HintText(CustomMessage("a spider under a #crate in the crater# holds",
                                              /*german*/ "",
                                              /*french*/ "la Skulltula dans une #boîte volcanique# a"));
                                           // /*spanish*/una Skulltula bajo una #caja del cráter# otorga

    hintTable[RHT_DEKU_TREE_MQ_AFTER_SPINNING_LOG_CHEST] = HintText(CustomMessage("a #temporal stone within the Deku Tree# contains",
                                                                       /*german*/ "",
                                                                       /*french*/ "la #pierre temporelle dans l'Arbre Mojo# cache"),
                                                                    // /*spanish*/un #bloque temporal del Gran Árbol Deku# contiene
                                                                    {},
                                                                    {CustomMessage("a #temporal stone within a tree# contains",
                                                                        /*german*/ "",
                                                                        /*french*/ "la #pierre bleue dans un arbre# mène à")});
                                                                     // /*spanish*/un #bloque temporal de un árbol# contiene
                                                                     

    hintTable[RHT_DEKU_TREE_MQ_GS_BASEMENT_GRAVES_ROOM] = HintText(CustomMessage("a #spider on a ceiling in the Deku Tree# holds",
                                                                      /*german*/ "",
                                                                      /*french*/ "la#Skulltula dans le Cimetière de l'Arbre Mojo# a"),
                                                                   // /*spanish*/una #Skulltula en el techo del Gran Árbol Deku# otorga
                                                                   {},
                                                                   {CustomMessage("a #spider on a ceiling in a tree# holds",
                                                                       /*german*/ "",
                                                                       /*french*/ "l'#araignée haut-perchée dans un arbre# a")});
                                                                    // /*spanish*/una #Skulltula en el techo de un árbol# otorga

    hintTable[RHT_DODONGOS_CAVERN_MQ_GS_SONG_OF_TIME_BLOCK_ROOM] = HintText(CustomMessage("a spider under #temporal stones in Dodongo's Cavern# holds",
                                                                               /*german*/ "",
                                                                               /*french*/ "la Skulltula sous #la pierre temporelle dans la Caverne Dodongo# a"),
                                                                            // /*spanish*/una Skulltula bajo #bloques temporales de la Cueva de los Dodongos# otorga
                                                                            {},
                                                                            {CustomMessage("a spider under #temporal stones in a cavern# holds",
                                                                                /*german*/ "",
                                                                                /*french*/ "l'araignée sous #une pierre bleue dans une caverne# a")});
                                                                             // /*spanish*/una Skulltula bajo #bloques temporales de una cueva# otorga
                                                                             

    hintTable[RHT_JABU_JABUS_BELLY_BOOMERANG_CHEST] = HintText(CustomMessage("a school of #stingers swallowed by Jabu-Jabu# guard",
                                                                  /*german*/ "",
                                                                  /*french*/ "les #raies dans Jabu-Jabu# protègent"),
                                                               // /*spanish*/unos #stingers engullidos por Jabu-Jabu# guardan
                                                               {},
                                                               {CustomMessage("a school of #stingers swallowed by a deity# guard",
                                                                   /*german*/ "",
                                                                   /*french*/ "les #raies dans un gardien# protègent")});
                                                                // /*spanish*/unos de #stingers engullidos por cierta deidad# guardan

    hintTable[RHT_JABU_JABUS_BELLY_MQ_GS_INVISIBLE_ENEMIES_ROOM] = HintText(CustomMessage("a spider surrounded by #shadows in Jabu-Jabu's Belly# holds",
                                                                               /*german*/ "",
                                                                               /*french*/ "la Skulltula entourée d'#ombres dans Jabu-Jabu# possède"),
                                                                            // /*spanish*/una Skulltula rodeada de #sombras en la Tripa de Jabu-Jabu# otorga
                                                                            {},
                                                                            {CustomMessage("a spider surrounded by #shadows in the belly of a deity# holds",
                                                                                /*german*/ "",
                                                                                /*french*/ "l'araignée entourée d'#ombres dans le ventre du gardien# possède")});
                                                                             // /*spanish*/una Skulltula rodeada de #sombras en la tripa de cierta diedad# otorga
                                                                             

    hintTable[RHT_JABU_JABUS_BELLY_MQ_COW] = HintText(CustomMessage("a #cow swallowed by Jabu-Jabu# gifts",
                                                         /*german*/ "",
                                                         /*french*/ "la #vache avallée par Jabu-Jabu# donne"),
                                                      // /*spanish*/una #vaca engullida por Jabu-Jabu# brinda
                                                      {},
                                                      {CustomMessage("a #cow swallowed by a deity# gifts",
                                                          /*german*/ "",
                                                          /*french*/ "la #vache dans le gardien# donne")});
                                                       // /*spanish*/una #vaca engullida por cierta deidad# brinda

    hintTable[RHT_FIRE_TEMPLE_SCARECROW_CHEST] = HintText(CustomMessage("#Pierre atop the Fire Temple# hides",
                                                             /*german*/ "",
                                                             /*french*/ "#Pierre au sommet du Temple du Feu# donne"),
                                                          // /*spanish*/#Pierre en lo alto del Templo del Fuego# esconde
                                                          {},
                                                          {CustomMessage("a #scarecrow atop the volcano# hides",
                                                              /*german*/ "",
                                                              /*french*/ "l'#épouvantail au sommet d'un volcan# donne")});
                                                           // /*spanish*/un #espantapájaros en lo alto del volcán# esconde

    hintTable[RHT_FIRE_TEMPLE_MEGATON_HAMMER_CHEST] = HintText(CustomMessage("the #Flare Dancer atop the Fire Temple# guards a chest containing",
                                                                  /*german*/ "",
                                                                  /*french*/ "le #Danse-Flamme au sommet du Temple du Feu# protège"),
                                                               // /*spanish*/el #Bailaguego en lo alto del Templo del Fuego# otorga
                                                               {},
                                                               {CustomMessage("the #Flare Dancer atop the volcano# guards a chest containing",
                                                                   /*german*/ "",
                                                                   /*french*/ "le #danseur au sommet du volcan# protège")});
                                                                // /*spanish*/el #Bailafuego en lo alto del volcán# otorga

    hintTable[RHT_FIRE_TEMPLE_MQ_CHEST_ON_FIRE] = HintText(CustomMessage("the #Flare Dancer atop the Fire Temple# guards a chest containing",
                                                              /*german*/ "",
                                                              /*french*/ "le #Danse-Flamme au sommet du Temple du Feu# protège"),
                                                           // /*spanish*/el #Bailafuego en lo alto del Templo del Fuego# otorga
                                                           {},
                                                           {CustomMessage("the #Flare Dancer atop the volcano# guards a chest containing",
                                                               /*german*/ "",
                                                               /*french*/ "le #danseur au sommet du volcan# protège")});
                                                            // /*spanish*/el #Bailafuego en lo alto del volcán# otorga

    hintTable[RHT_FIRE_TEMPLE_MQ_GS_SKULL_ON_FIRE] = HintText(CustomMessage("a #spider under a block in the Fire Temple# holds",
                                                                 /*german*/ "",
                                                                 /*french*/ "une #Skulltula sous un bloc dans le Temple du Feu# a"),
                                                              // /*spanish*/una #Skulltula bajo un bloque del Templo del Fuego# otorga
                                                              {},
                                                              {CustomMessage("a #spider under a block in the volcano# holds",
                                                                  /*german*/ "",
                                                                  /*french*/ "l'#araignée sous un bloc dans le volcan# a")});
                                                               // /*spanish*/una #Skulltula bajo el bloque de un volcán# otorga
                                                               

    hintTable[RHT_WATER_TEMPLE_RIVER_CHEST] = HintText(CustomMessage("beyond the #river in the Water Temple# waits",
                                                          /*german*/ "",
                                                          /*french*/ "au delà de #la rivière dans le Temple de l'Eau# se cache"),
                                                       // /*spanish*/tras el #río del Templo del Agua# yace
                                                       {},
                                                       {CustomMessage("beyond the #river under the lake# waits",
                                                           /*german*/ "",
                                                           /*french*/ "au delà de #la rivière sous le lac# se cache")});
                                                        // /*spanish*/tras el #río bajo el lago# yace

    hintTable[RHT_WATER_TEMPLE_BOSS_KEY_CHEST] = HintText(CustomMessage("dodging #rolling boulders in the Water Temple# leads to",
                                                             /*german*/ "",
                                                             /*french*/ "éviter des #rochers roulants dans le Temple de l'Eau# mène à"),
                                                          // /*spanish*/esquivar #rocas rondantes del Templo del Agua# conduce a
                                                          {},
                                                          {CustomMessage("dodging #rolling boulders under the lake# leads to",
                                                              /*german*/ "",
                                                              /*french*/ "éviter des #rochers roulants sous le lac# mène à")});
                                                           // /*spanish*/esquivar #rocas rodantes bajo el lago# conduce a

    hintTable[RHT_WATER_TEMPLE_GS_BEHIND_GATE] = HintText(CustomMessage("a spider behind a #gate in the Water Temple# holds",
                                                             /*german*/ "",
                                                             /*french*/ "la Skulltula derrière une #barrière dans le Temple de l'Eau# a"),
                                                          // /*spanish*/una Skulltula tras #una valla del Templo del Agua# otorga
                                                          {},
                                                          {CustomMessage("a spider behind a #gate under the lake# holds",
                                                              /*german*/ "",
                                                              /*french*/ "l'araignée derrière une #barrière sous le lac# a")});
                                                           // /*spanish*/una Skulltula tras #una valla bajo el lago# otorga

    hintTable[RHT_WATER_TEMPLE_MQ_FREESTANDING_KEY] = HintText(CustomMessage("hidden in a #box in the Water Temple# lies",
                                                                  /*german*/ "",
                                                                  /*french*/ "dans une #boîte dans le Temple de l'Eau# gît"),
                                                               // /*spanish*/en una #caja del Templo del Agua# yace
                                                               {},
                                                               {CustomMessage("hidden in a #box under the lake# lies",
                                                                   /*german*/ "",
                                                                   /*french*/ "dans une #boîte sous le lac# gît")});
                                                                // /*spanish*/en una #caja bajo el lago# yace

    hintTable[RHT_WATER_TEMPLE_MQ_GS_FREESTANDING_KEY_AREA] = HintText(CustomMessage("the #locked spider in the Water Temple# holds",
                                                                          /*german*/ "",
                                                                          /*french*/ "une #Skulltula emprisonnée dans le Temple de l'Eau# a"),
                                                                       // /*spanish*/la #Skulltula enjaulada del Templo del Agua# otorga
                                                                       {},
                                                                       {CustomMessage("the #locked spider under the lake# holds",
                                                                           /*german*/ "",
                                                                           /*french*/ "l'#araignée emprisonnée sous le lac# a")});
                                                                        // /*spanish*/la #Skulltula enjaulada bajo el lago# otorga

    hintTable[RHT_WATER_TEMPLE_MQ_GS_TRIPLE_WALL_TORCH] = HintText(CustomMessage("a spider behind a #gate in the Water Temple# holds",
                                                                      /*german*/ "",
                                                                      /*french*/ "une #Skulltula derrière une barrière dans le Temple de l'Eau# a"),
                                                                   // /*spanish*/una Skulltula tras una #valla del Templo del Agua#
                                                                   {},
                                                                   {CustomMessage("a spider behind a #gate under the lake# holds",
                                                                       /*german*/ "",
                                                                       /*french*/ "l'#araignée derrière une barrière sous le lac# a")});
                                                                    // /*spanish*/una Skulltula tras una #valla bajo el lago# otorga

    hintTable[RHT_GERUDO_TRAINING_GROUND_UNDERWATER_SILVER_RUPEE_CHEST] = HintText(CustomMessage("those who seek #sunken silver rupees# will find",
                                                                                      /*german*/ "",
                                                                                      /*french*/ "ceux qui pêchent les #joyaux argentés# trouveront"));
                                                                                   // /*spanish*/aquellos que busquen las #rupias plateadas sumergidas# encontrarán

    hintTable[RHT_GERUDO_TRAINING_GROUND_MQ_UNDERWATER_SILVER_RUPEE_CHEST] = HintText(CustomMessage("those who seek #sunken silver rupees# will find",
                                                                                         /*german*/ "",
                                                                                         /*french*/ "ceux qui pêchent les #joyaux argentés# trouveront"));
                                                                                      // /*spanish*/aquellos que busquen las #rupias plateadas sumergidas# encontrarán

    hintTable[RHT_GERUDO_TRAINING_GROUND_MAZE_PATH_FINAL_CHEST] = HintText(CustomMessage("the final prize of #the thieves' training# is",
                                                                              /*german*/ "",
                                                                              /*french*/ "la récompense ultime de #l'épreuve des voleurs# est"));
                                                                           // /*spanish*/la recompensa final de la #instrucción de las bandida# brinda

    hintTable[RHT_GERUDO_TRAINING_GROUND_MQ_ICE_ARROWS_CHEST] = HintText(CustomMessage("the final prize of #the thieves' training# is",
                                                                            /*german*/ "",
                                                                            /*french*/ "la récompense ultime de #l'épreuve des voleurs# est"));
                                                                         // /*spanish*/el premio final de la #instrucción de las bandidas# brinda

    hintTable[RHT_BOTTOM_OF_THE_WELL_LENS_OF_TRUTH_CHEST] = HintText(CustomMessage("#Dead Hand in the well# holds",
                                                                        /*german*/ "",
                                                                        /*french*/ "le #Poigneur dans le Puits# cache"),
                                                                     // /*spanish*/la #Mano Muerta del pozo# concede
                                                                     {},
                                                                     {CustomMessage("the well's #grasping ghoul# hides",
                                                                         /*german*/ "",
                                                                         /*french*/ "la #terreur du Puits# cache"),
                                                                      // /*spanish*/en las #profundidades del pozo# se esconde
                                                                      CustomMessage("a #nether dweller in the well# holds",
                                                                         /*german*/ "",
                                                                         /*french*/ "le #spectre qui réside dans le Puits# a")});
                                                                      // /*spanish*/el #temido morador del pozo# concede

    hintTable[RHT_BOTTOM_OF_THE_WELL_MQ_COMPASS_CHEST] = HintText(CustomMessage("#Dead Hand in the well# holds",
                                                                     /*german*/ "",
                                                                     /*french*/ "le #Poigneur dans le Puits# cache"),
                                                                  // /*spanish*/la #Mano Muerta del pozo# concede
                                                                  {},
                                                                  {CustomMessage("the well's #grasping ghoul# hides",
                                                                      /*german*/ "",
                                                                      /*french*/ "la #terreur du Puits# cache"),
                                                                   // /*spanish*/en las #profundidades del pozo# se esconde
                                                                   CustomMessage("a #nether dweller in the well# holds",
                                                                      /*german*/ "",
                                                                      /*french*/ "le #spectre qui réside dans le Puits# a")});
                                                                   // /*spanish*/el #temido morador del pozo# concede

    hintTable[RHT_SPIRIT_TEMPLE_SILVER_GAUNTLETS_CHEST] = HintText(CustomMessage("upon the #Colossus's right hand# is",
                                                                      /*german*/ "",
                                                                      /*french*/ "sur la #main droite du colosse# repose"),
                                                                   // /*spanish*/en la #mano derecha del Coloso# yace
                                                                   {},
                                                                   {CustomMessage("the treasure #sought by Nabooru# is",
                                                                       /*german*/ "",
                                                                       /*french*/ "le trésor que #recherche Nabooru# est")});
                                                                    // /*spanish*/el #ansiado tesoro de Nabooru# brinda

    hintTable[RHT_SPIRIT_TEMPLE_MIRROR_SHIELD_CHEST] = HintText(CustomMessage("upon the #Colossus's left hand# is",
                                                                   /*german*/ "",
                                                                   /*french*/ "sur la #main gauche du colosse# repose"));
                                                                // /*spanish*/en la #mano izquierda del Coloso# yace

    hintTable[RHT_SPIRIT_TEMPLE_MQ_CHILD_HAMMER_SWITCH_CHEST] = HintText(CustomMessage("a #temporal paradox in the Spirit Temple# yields",
                                                                            /*german*/ "",
                                                                            /*french*/ "le #paradoxe temporel dans le Temple de l'Esprit# révèle"),
                                                                         // /*spanish*/una #paradoja temporal del Coloso# conduce a
                                                                         {},
                                                                         {CustomMessage("a #temporal paradox in the Colossus# yields",
                                                                             /*german*/ "",
                                                                             /*french*/ "un #paradoxe temporel dans le colosse# révèle")});
                                                                          // /*spanish*/una #paradoja temporal del Coloso# conduce a

    hintTable[RHT_SPIRIT_TEMPLE_MQ_SYMPHONY_ROOM_CHEST] = HintText(CustomMessage("a #symphony in the Spirit Temple# yields",
                                                                      /*german*/ "",
                                                                      /*french*/ "les #cinq chansons du Temple de l'Esprit# révèlent"),
                                                                   // /*spanish*/una #sinfonía del Coloso# conduce a
                                                                   {},
                                                                   {CustomMessage("a #symphony in the Colossus# yields",
                                                                       /*german*/ "",
                                                                       /*french*/ "la #symphonie du colosse# révèle")});
                                                                    // /*spanish*/una #sinfonía del Coloso# conduce a

    hintTable[RHT_SPIRIT_TEMPLE_MQ_GS_SYMPHONY_ROOM] = HintText(CustomMessage("a #spider's symphony in the Spirit Temple# yields",
                                                                   /*german*/ "",
                                                                   /*french*/ "la #mélodie de la Skulltula du Temple de l'Esprit# révèle"),
                                                                // /*spanish*/la #Skulltula de la sinfonía del Coloso# otorga
                                                                {},
                                                                {CustomMessage("a #spider's symphony in the Colossus# yields",
                                                                    /*german*/ "",
                                                                    /*french*/ "la #mélodie de l'araignée du colosse# révèle")});
                                                                 // /*spanish*/la #Skulltula de la sinfonía del Coloso# otorga

    hintTable[RHT_SHADOW_TEMPLE_INVISIBLE_FLOORMASTER_CHEST] = HintText(CustomMessage("shadows in an #invisible maze# guard",
                                                                           /*german*/ "",
                                                                           /*french*/ "les ombres dans le #labyrinthe invisible# protègent"));
                                                                        // /*spanish*/las sombras del #laberinto misterioso# esconden

    hintTable[RHT_SHADOW_TEMPLE_MQ_BOMB_FLOWER_CHEST] = HintText(CustomMessage("shadows in an #invisible maze# guard",
                                                                    /*german*/ "",
                                                                    /*french*/ "les ombres dans le #labyrinthe invisible# protègent"));
                                                                 // /*spanish*/las sombras del #laberinto invisible# esconden

    /*--------------------------
    |    ENTRANCE HINT TEXT    |
    ---------------------------*/

    hintTable[RHT_DESERT_COLOSSUS_TO_COLOSSUS_GROTTO] = HintText(CustomMessage("lifting a #rock in the desert# reveals",
                                                                    /*german*/ "",
                                                                    /*french*/ "soulever une #roche dans le désert# révèle"));
                                                                 // /*spanish*/levantar una #roca del desierto# revela

    hintTable[RHT_GV_GROTTO_LEDGE_TO_GV_OCTOROK_GROTTO] = HintText(CustomMessage("a rock on #a ledge in the valley# hides",
                                                                      /*german*/ "",
                                                                      /*french*/ "soulever une #roche dans la vallée# révèle"));
                                                                   // /*spanish*/levantar una #roca al borde del valle# esconde

    hintTable[RHT_GC_GROTTO_PLATFORM_TO_GC_GROTTO] = HintText(CustomMessage("a #pool of lava# in Goron City blocks the way to",
                                                                 /*german*/ "",
                                                                 /*french*/ "l'#étang de lave# dans le village Goron renferme"));
                                                              // /*spanish*/un #estanque de lava# en la Ciudad Goron bloquea el paso a
                                                              

    hintTable[RHT_GERUDO_FORTRESS_TO_GF_STORMS_GROTTO] = HintText(CustomMessage("a #storm within Gerudo's Fortress# reveals",
                                                                     /*german*/ "",
                                                                     /*french*/ "la #tempête dans la forteresse# révèle"));
                                                                  // /*spanish*/una #tormenta en la Fortaleza Gerudo# revela
                                                                  

    hintTable[RHT_ZORAS_DOMAIN_TO_ZD_STORMS_GROTTO] = HintText(CustomMessage("a #storm within Zora's Domain# reveals",
                                                                  /*german*/ "",
                                                                  /*french*/ "la #tempête dans le Domaine Zora# révèle"));
                                                               // /*spanish*/una #tormenta en la Región de los Zora# revela
                                                               

    hintTable[RHT_HYRULE_CASTLE_GROUNDS_TO_HC_STORMS_GROTTO] = HintText(CustomMessage("a #storm near the castle# reveals",
                                                                           /*german*/ "",
                                                                           /*french*/ "la #tempête près du château# révèle"));
                                                                        // /*spanish*/una #tormenta junto al castillo# revela

    hintTable[RHT_GV_FORTRESS_SIDE_TO_GV_STORMS_GROTTO] = HintText(CustomMessage("a #storm in the valley# reveals",
                                                                      /*german*/ "",
                                                                      /*french*/ "la #tempête dans la vallée# révèle"));
                                                                   // /*spanish*/una #tormenta en el valle# revela

    hintTable[RHT_DESERT_COLOSSUS_TO_COLOSSUS_GREAT_FAIRY_FOUNTAIN] = HintText(CustomMessage("a #fractured desert wall# hides",
                                                                                  /*german*/ "",
                                                                                  /*french*/ "le #mur fragile du désert# cache"));
                                                                               // /*spanish*/una #agrietada pared del desierto# esconde

    hintTable[RHT_GANONS_CASTLE_GROUNDS_TO_OGC_GREAT_FAIRY_FOUNTAIN] = HintText(CustomMessage("a #heavy pillar# outside the castle obstructs",
                                                                                   /*german*/ "",
                                                                                   /*french*/ "le #rocher fragile près du château# cache"));
                                                                                // /*spanish*/una #pesada columna# fuera del castillo obstruye
                                                                                

    hintTable[RHT_ZORAS_FOUNTAIN_TO_ZF_GREAT_FAIRY_FOUNTAIN] = HintText(CustomMessage("a #fountain wall# hides",
                                                                           /*german*/ "",
                                                                           /*french*/ "le #mur fragile du réservoir# cache"));
                                                                        // /*spanish*/una #pared de la fuente# esconde

    hintTable[RHT_GV_FORTRESS_SIDE_TO_GV_CARPENTER_TENT] = HintText(CustomMessage("a #tent in the valley# covers",
                                                                       /*german*/ "",
                                                                       /*french*/ "la #tente dans la vallée# recouvre"));
                                                                    // /*spanish*/una #tienda de campaña del valle# cubre

    hintTable[RHT_GRAVEYARD_WARP_PAD_REGION_TO_SHADOW_TEMPLE_ENTRYWAY] = HintText(CustomMessage("at the #back of the Graveyard#, there is",
                                                                                     /*german*/ "",
                                                                                     /*french*/ "#derrière le Cimetière# gît"));
                                                                                  // /*spanish*/en la #parte trasera del cementerio# se halla
                                                                                  

    hintTable[RHT_LAKE_HYLIA_TO_WATER_TEMPLE_LOBBY] = HintText(CustomMessage("deep #under a vast lake#, one can find",
                                                                  /*german*/ "",
                                                                  /*french*/ "#sous le lac# gît"));
                                                               // /*spanish*/en las #profundidades de un lago inmenso# se halla
                                                               

    hintTable[RHT_GERUDO_FORTRESS_TO_GERUDO_TRAINING_GROUNDS_LOBBY] = HintText(CustomMessage("paying a #fee to the Gerudos# grants access to",
                                                                                  /*german*/ "",
                                                                                  /*french*/ "l'#entrée payante des Gerudo# donne accès à"));
                                                                               // /*spanish*/pagarle una #tasa a las gerudo# da acceso a

    hintTable[RHT_ZORAS_FOUNTAIN_TO_JABU_JABUS_BELLY_BEGINNING] = HintText(CustomMessage("inside #Jabu-Jabu#, one can find",
                                                                              /*german*/ "",
                                                                              /*french*/ "#dans Jabu-Jabu# se trouve"));
                                                                           // /*spanish*/dentro de #Jabu-Jabu# se halla

    hintTable[RHT_KAKARIKO_VILLAGE_TO_BOTTOM_OF_THE_WELL] = HintText(CustomMessage("a #village well# leads to",
                                                                        /*german*/ "",
                                                                        /*french*/ "dans le fond du #Puits du village# gît"));
                                                                     // /*spanish*/el #pozo de un pueblo# conduce a

    /*--------------------------
    |      EXIT HINT TEXT      |
    ---------------------------*/

    hintTable[RHT_LINKS_POCKET] = HintText(CustomMessage("Link's Pocket",
                                              /*german*/ "",
                                              /*french*/ "les Poches de @"));
                                           // /*spanish*/el bolsillo de @

    hintTable[RHT_KOKIRI_FOREST] = HintText(CustomMessage("Kokiri Forest",
                                               /*german*/ "",
                                               /*french*/ "la Forêt Kokiri"));
                                            // /*spanish*/el Bosque Kokiri

    hintTable[RHT_THE_LOST_WOODS] = HintText(CustomMessage("the Lost Woods",
                                                /*german*/ "",
                                                /*french*/ "les Bois Perdus"));
                                             // /*spanish*/el Bosque Perdido
    hintTable[RHT_SACRED_FOREST_MEADOW] = HintText(CustomMessage("Sacred Forest Meadow",
                                                      /*german*/ "",
                                                      /*french*/ "le Bosquet Sacré"));
                                                   // /*spanish*/la pradera sagrada del bosque

    hintTable[RHT_HYRULE_FIELD] = HintText(CustomMessage("Hyrule Field",
                                              /*german*/ "",
                                              /*french*/ "la Plaine d'Hyrule"));
                                           // /*spanish*/la Llanura de Hyrule

    hintTable[RHT_LAKE_HYLIA] = HintText(CustomMessage("Lake Hylia",
                                            /*german*/ "",
                                            /*french*/ "le Lac Hylia"));
                                         // /*spanish*/el Lago Hylia

    hintTable[RHT_GERUDO_VALLEY] = HintText(CustomMessage("Gerudo Valley",
                                               /*german*/ "",
                                               /*french*/ "la Vallée Gerudo"));
                                            // /*spanish*/el Valle Gerudo

    hintTable[RHT_GERUDO_FORTRESS] = HintText(CustomMessage("Gerudo's Fortress",
                                                 /*german*/ "",
                                                 /*french*/ "le Repaire des Voleurs"));
                                              // /*spanish*/la Fortaleza Gerudo

    hintTable[RHT_HAUNTED_WASTELAND] = HintText(CustomMessage("Haunted Wasteland",
                                                   /*german*/ "",
                                                   /*french*/ "le Désert Hanté"));
                                                // /*spanish*/el desierto encantado

    hintTable[RHT_DESERT_COLOSSUS] = HintText(CustomMessage("Desert Colossus",
                                                 /*german*/ "",
                                                 /*french*/ "le Colosse du Désert"));
                                              // /*spanish*/el Coloso del Desierto

    hintTable[RHT_THE_MARKET] = HintText(CustomMessage("the Market",
                                            /*german*/ "",
                                            /*french*/ "la Place du Marché"));
                                         // /*spanish*/la plaza del mercado

    hintTable[RHT_TEMPLE_OF_TIME] = HintText(CustomMessage("Temple of Time",
                                                /*german*/ "",
                                                /*french*/ "le Temple du Temps"));
                                             // /*spanish*/el Templo del Tiempo
    hintTable[RHT_CASTLE_GROUNDS] = HintText(CustomMessage("the Castle Grounds",
                                                /*german*/ "",
                                                /*french*/ "le Château d'Hyrule"));
                                             // /*spanish*/
    hintTable[RHT_HYRULE_CASTLE] = HintText(CustomMessage("Hyrule Castle",
                                               /*german*/ "",
                                               /*french*/ "le Château d'Hyrule"));
                                            // /*spanish*/el Castillo de Hyrule

    hintTable[RHT_OUTSIDE_GANONS_CASTLE] = HintText(CustomMessage("outside Ganon's Castle",
                                                       /*german*/ "",
                                                       /*french*/ "les alentours du Château de Ganon"));
                                                    // /*spanish*/el exterior del Castillo de Ganon

    hintTable[RHT_CASTLE_GROUNDS] = HintText(CustomMessage("the Castle Grounds",
                                                /*german*/ "",
                                                /*french*/ "le Château d'Hyrule"));
                                             // /*spanish*/
    hintTable[RHT_KAKARIKO_VILLAGE] = HintText(CustomMessage("Kakariko Village",
                                                  /*german*/ "",
                                                  /*french*/ "le Village Cocorico"));
                                               // /*spanish*/Kakariko

    hintTable[RHT_THE_GRAVEYARD] = HintText(CustomMessage("the Graveyard",
                                               /*german*/ "",
                                               /*french*/ "le Cimetière"));
                                            // /*spanish*/el cementerio

    hintTable[RHT_DEATH_MOUNTAIN_TRAIL] = HintText(CustomMessage("Death Mountain Trail",
                                                      /*german*/ "",
                                                      /*french*/ "le Chemin du Péril"));
                                                   // /*spanish*/el sendero de la Montaña de la Muerte

    hintTable[RHT_GORON_CITY] = HintText(CustomMessage("Goron City",
                                            /*german*/ "",
                                            /*french*/ "le Village Goron"));
                                         // /*spanish*/la Ciudad Goron

    hintTable[RHT_DEATH_MOUNTAIN_CRATER] = HintText(CustomMessage("Death Mountain Crater",
                                                       /*german*/ "",
                                                       /*french*/ "le Cratère du Péril"));
                                                    // /*spanish*/el cráter de la Montaña de la Muerte

    hintTable[RHT_ZORAS_RIVER] = HintText(CustomMessage("Zora's River",
                                             /*german*/ "",
                                             /*french*/ "la Rivière Zora"));
                                          // /*spanish*/el Río Zora

    hintTable[RHT_ZORAS_DOMAIN] = HintText(CustomMessage("Zora's Domain",
                                              /*german*/ "",
                                              /*french*/ "le Domaine Zora"));
                                           // /*spanish*/la Región de los Zora

    hintTable[RHT_ZORAS_FOUNTAIN] = HintText(CustomMessage("Zora's Fountain",
                                                /*german*/ "",
                                                /*french*/ "la Fontaine Zora"));
                                             // /*spanish*/la Fuente Zora
    hintTable[RHT_LON_LON_RANCH] = HintText(CustomMessage("Lon Lon Ranch",
                                               /*german*/ "",
                                               /*french*/ "le Ranch Lon Lon"));
                                            // /*spanish*/el Rancho Lon Lon

    /*--------------------------
    |     REGION HINT TEXT     |
    ---------------------------*/

    hintTable[RHT_KF_LINKS_HOUSE] = HintText(CustomMessage("Link's House",
                                                /*german*/ "",
                                                /*french*/ "la #maison de @#"));
                                             // /*spanish*/la casa de @

    hintTable[RHT_KF_MIDOS_HOUSE] = HintText(CustomMessage("Mido's house",
                                                /*german*/ "",
                                                /*french*/ "la Cabane du Grand Mido"));
                                             // /*spanish*/la casa de Mido
    hintTable[RHT_KF_SARIAS_HOUSE] = HintText(CustomMessage("Saria's House",
                                                 /*german*/ "",
                                                 /*french*/ "la Cabane de Saria"));
                                              // /*spanish*/la casa de Saria

    hintTable[RHT_KF_HOUSE_OF_TWINS] = HintText(CustomMessage("the #House of Twins#",
                                                   /*german*/ "",
                                                   /*french*/ "la Cabane des Jumelles"));
                                                // /*spanish*/la casa de las gemelas

    hintTable[RHT_KF_KNOW_IT_ALL_HOUSE] = HintText(CustomMessage("Know-It-All Brothers' House",
                                                      /*german*/ "",
                                                      /*french*/ "la Cabane des frères Je-Sais-Tout"));
                                                   // /*spanish*/la casa de los hermanos Sabelotodo

    hintTable[RHT_KF_KOKIRI_SHOP] = HintText(CustomMessage("the #Kokiri Shop#",
                                                /*german*/ "",
                                                /*french*/ "le #Magasin Kokiri#"));
                                             // /*spanish*/la tienda kokiri
    hintTable[RHT_LH_LAB] = HintText(CustomMessage("the #Lakeside Laboratory#",
                                        /*german*/ "",
                                        /*french*/ "le #Laboratoire du Lac#"));
                                     // /*spanish*/el laboratorio del lago

    hintTable[RHT_LH_FISHING_HOLE] = HintText(CustomMessage("the #Fishing Pond#",
                                                 /*german*/ "",
                                                 /*french*/ "l'#Étang#"));
                                              // /*spanish*/el estanque

    hintTable[RHT_GV_CARPENTER_TENT] = HintText(CustomMessage("the #Carpenters' tent#",
                                                   /*german*/ "",
                                                   /*french*/ "la #Tente des charpentiers#"));
                                                // /*spanish*/la #tienda de campaña de los carpinteros#

    hintTable[RHT_MARKET_GUARD_HOUSE] = HintText(CustomMessage("the #Guard House#",
                                                    /*german*/ "",
                                                    /*french*/ "le #poste de garde#"));
                                                 // /*spanish*/la caseta de guardia

    hintTable[RHT_MARKET_MASK_SHOP] = HintText(CustomMessage("the #Happy Mask Shop#",
                                                  /*german*/ "",
                                                  /*french*/ "la #Foire Aux Masques#"));
                                               // /*spanish*/la tienda de La Máscara Feliz

    hintTable[RHT_MARKET_BOMBCHU_BOWLING] = HintText(CustomMessage("the #Bombchu Bowling Alley#",
                                                        /*german*/ "",
                                                        /*french*/ "le #Bowling Teigneux#"));
                                                     // /*spanish*/la Bolera Bombchu

    hintTable[RHT_MARKET_POTION_SHOP] = HintText(CustomMessage("the #Market Potion Shop#",
                                                    /*german*/ "",
                                                    /*french*/ "l'#apothicaire de la Place du Marché#"));
                                                 // /*spanish*/la tienda de pociones de la plaza del mercado

    hintTable[RHT_MARKET_TREASURE_CHEST_GAME] = HintText(CustomMessage("the #Treasure Chest Shop#",
                                                            /*german*/ "",
                                                            /*french*/ "la #Chasse-aux-Trésors#"));
                                                         // /*spanish*/el Cofre del Tesoro

    hintTable[RHT_MARKET_BOMBCHU_SHOP] = HintText(CustomMessage("the #Bombchu Shop#",
                                                     /*german*/ "",
                                                     /*french*/ "le #Magasin de Missiles#"));
                                                  // /*spanish*/la Tienda Bombchu

    hintTable[RHT_MARKET_MAN_IN_GREEN_HOUSE] = HintText(CustomMessage("Man in Green's House",
                                                           /*german*/ "",
                                                           /*french*/ "la #Maison de l'Homme en Vert#"));
                                                        // /*spanish*/la casa del hombre de verde

    hintTable[RHT_KAK_WINDMILL] = HintText(CustomMessage("the #Windmill#",
                                              /*german*/ "",
                                              /*french*/ "le #Moulin#"));
                                           // /*spanish*/el #molino#

    hintTable[RHT_KAK_CARPENTER_BOSS_HOUSE] = HintText(CustomMessage("the #Carpenters' Boss House#",
                                                          /*german*/ "",
                                                          /*french*/ "la #Maison du Chef des ouvriers#"));
                                                       // /*spanish*/la casa del capataz de los carpinteros

    hintTable[RHT_KAK_HOUSE_OF_SKULLTULA] = HintText(CustomMessage("the #House of Skulltula#",
                                                        /*german*/ "",
                                                        /*french*/ "la #Maison des Skulltulas#"));
                                                     // /*spanish*/la casa de las Skulltulas

    hintTable[RHT_KAK_IMPAS_HOUSE] = HintText(CustomMessage("Impa's House",
                                                 /*german*/ "",
                                                 /*french*/ "la #Maison d'Impa#"));
                                              // /*spanish*/la casa de Impa

    hintTable[RHT_KAK_IMPAS_HOUSE_BACK] = HintText(CustomMessage("Impa's cow cage",
                                                      /*german*/ "",
                                                      /*french*/ "la #cage à vache d'Impa#"));
                                                   // /*spanish*/la jaula de la vaca de Impa

    hintTable[RHT_KAK_ODD_POTION_BUILDING] = HintText(CustomMessage("Granny's Potion Shop",
                                                         /*german*/ "",
                                                         /*french*/ "la #maison bleue de Cocorico#"));
                                                      // /*spanish*/la tienda de pociones de la abuela

    hintTable[RHT_GRAVEYARD_DAMPES_HOUSE] = HintText(CustomMessage("Dampé's Hut",
                                                        /*german*/ "",
                                                        /*french*/ "la #Cabane du Fossoyeur#"));
                                                     // /*spanish*/la cabaña de Dampé

    hintTable[RHT_GC_SHOP] = HintText(CustomMessage("the #Goron Shop#",
                                         /*german*/ "",
                                         /*french*/ "la #Boutique Goron#"));
                                      // /*spanish*/la #tienda goron#

    hintTable[RHT_ZD_SHOP] = HintText(CustomMessage("the #Zora Shop#",
                                         /*german*/ "",
                                         /*french*/ "la #Boutique Zora#"));
                                      // /*spanish*/la #tienda zora#

    hintTable[RHT_LLR_TALONS_HOUSE] = HintText(CustomMessage("Talon's House",
                                                  /*german*/ "",
                                                  /*french*/ "la #Maison de Talon#"));
                                               // /*spanish*/la casa de Talon

    hintTable[RHT_LLR_STABLES] = HintText(CustomMessage("a #stable#",
                                             /*german*/ "",
                                             /*french*/ "l'#Étable#"));
                                          // /*spanish*/el establo

    hintTable[RHT_LLR_TOWER] = HintText(CustomMessage("the #Lon Lon Tower#",
                                           /*german*/ "",
                                           /*french*/ "le #silo du Ranch Lon Lon#"));
                                        // /*spanish*/la torre Lon Lon

    hintTable[RHT_MARKET_BAZAAR] = HintText(CustomMessage("the #Market Bazaar#",
                                               /*german*/ "",
                                               /*french*/ "le #Bazar de la Place du Marché#"));
                                            // /*spanish*/el bazar de la plaza del mercado

    hintTable[RHT_MARKET_SHOOTING_GALLERY] = HintText(CustomMessage("a #Slingshot Shooting Gallery#",
                                                         /*german*/ "",
                                                         /*french*/ "le #Jeu d'Adresse de la Place du Marché#"));
                                                      // /*spanish*/el Tiro al Blanco con tirachinas

    hintTable[RHT_KAK_BAZAAR] = HintText(CustomMessage("the #Kakariko Bazaar#",
                                            /*german*/ "",
                                            /*french*/ "le #Bazar de Cocorico#"));
                                         // /*spanish*/el bazar de Kakariko

    hintTable[RHT_KAK_POTION_SHOP_FRONT] = HintText(CustomMessage("the #Kakariko Potion Shop#",
                                                       /*german*/ "",
                                                       /*french*/ "l'#apothicaire de Cocorico#"));
                                                    // /*spanish*/la tienda de pociones de Kakariko

    hintTable[RHT_KAK_POTION_SHOP_BACK] = HintText(CustomMessage("the #Kakariko Potion Shop#",
                                                      /*german*/ "",
                                                      /*french*/ "l'#apothicaire de Cocorico#"));
                                                   // /*spanish*/la tienda de pociones de Kakariko

    hintTable[RHT_KAK_SHOOTING_GALLERY] = HintText(CustomMessage("a #Bow Shooting Gallery#",
                                                      /*german*/ "",
                                                      /*french*/ "le #jeu d'adresse de Cocorico#"));
                                                   // /*spanish*/el Tiro al Blanco con arco

    hintTable[RHT_COLOSSUS_GREAT_FAIRY_FOUNTAIN] = HintText(CustomMessage("a #Great Fairy Fountain#",
                                                               /*german*/ "",
                                                               /*french*/ "une #Fontaine Royale des Fées#"));
                                                            // /*spanish*/una fuente de la Gran Hada

    hintTable[RHT_HC_GREAT_FAIRY_FOUNTAIN] = HintText(CustomMessage("a #Great Fairy Fountain#",
                                                         /*german*/ "",
                                                         /*french*/ "une #Fontaine Royale des Fées#"));
                                                      // /*spanish*/una fuente de la Gran Hada

    hintTable[RHT_OGC_GREAT_FAIRY_FOUNTAIN] = HintText(CustomMessage("a #Great Fairy Fountain#",
                                                          /*german*/ "",
                                                          /*french*/ "une #Fontaine Royale des Fées#"));
                                                       // /*spanish*/una fuente de la Gran Hada

    hintTable[RHT_DMC_GREAT_FAIRY_FOUNTAIN] = HintText(CustomMessage("a #Great Fairy Fountain#",
                                                          /*german*/ "",
                                                          /*french*/ "une #Fontaine Royale des Fées#"));
                                                       // /*spanish*/una fuente de la Gran Hada

    hintTable[RHT_DMT_GREAT_FAIRY_FOUNTAIN] = HintText(CustomMessage("a #Great Fairy Fountain#",
                                                          /*german*/ "",
                                                          /*french*/ "une #Fontaine Royale des Fées#"));
                                                       // /*spanish*/una fuente de la Gran Hada

    hintTable[RHT_ZF_GREAT_FAIRY_FOUNTAIN] = HintText(CustomMessage("a #Great Fairy Fountain#",
                                                         /*german*/ "",
                                                         /*french*/ "une #Fontaine Royale des Fées#"));
                                                      // /*spanish*/una fuente de la Gran Hada

    hintTable[RHT_GRAVEYARD_SHIELD_GRAVE] = HintText(CustomMessage("a #grave with a free chest#",
                                                        /*german*/ "",
                                                        /*french*/ "le #tombeau avec un trésor#"));
                                                     // /*spanish*/la #tumba con un cofre#

    hintTable[RHT_GRAVEYARD_HEART_PIECE_GRAVE] = HintText(CustomMessage("a chest spawned by #Sun's Song#",
                                                             /*german*/ "",
                                                             /*french*/ "un #coffre apparaît avec le Chant du Soleil#"));
                                                          // /*spanish*/la #tumba de la Canción del Sol#

    hintTable[RHT_GRAVEYARD_COMPOSERS_GRAVE] = HintText(CustomMessage("the #Composers' Grave#",
                                                           /*german*/ "",
                                                           /*french*/ "la #Tombe royale#"));
                                                        // /*spanish*/el #Panteón Real#

    hintTable[RHT_GRAVEYARD_DAMPES_GRAVE] = HintText(CustomMessage("Dampé's Grave",
                                                        /*german*/ "",
                                                        /*french*/ "la #Tombe d'Igor#"));
                                                     // /*spanish*/la #tumba de Dampé#

    hintTable[RHT_DMT_COW_GROTTO] = HintText(CustomMessage("a solitary #Cow#",
                                                /*german*/ "",
                                                /*french*/ "la #grotte avec une vache#"));
                                             // /*spanish*/una #vaca# solitaria
    hintTable[RHT_HC_STORMS_GROTTO] = HintText(CustomMessage("a sandy grotto with #fragile walls#",
                                                  /*german*/ "",
                                                  /*french*/ "la #grotte avec des murs fragiles#"));
                                               // /*spanish*/la arenosa gruta de #frágiles paredes#

    hintTable[RHT_HF_TEKTITE_GROTTO] = HintText(CustomMessage("a pool guarded by a #Tektite#",
                                                   /*german*/ "",
                                                   /*french*/ "l'#étang sous-terrain avec un Araknon#"));
                                                // /*spanish*/un charco custodiado por un #Tektite#

    hintTable[RHT_HF_NEAR_KAK_GROTTO] = HintText(CustomMessage("a #Big Skulltula# guarding a Gold one",
                                                    /*german*/ "",
                                                    /*french*/ "la #grotte d'araignées#"));
                                                 // /*spanish*/una #gran Skulltula# custodiando una dorada

    hintTable[RHT_HF_COW_GROTTO] = HintText(CustomMessage("a grotto full of #spider webs#",
                                               /*german*/ "",
                                               /*french*/ "la #grotte couverte de toiles d'araignées#"));
                                            // /*spanish*/una gruta llena de #telarañas#

    hintTable[RHT_KAK_REDEAD_GROTTO] = HintText(CustomMessage("#ReDeads# guarding a chest",
                                                   /*german*/ "",
                                                   /*french*/ "le tombeau de #deux morts#"));
                                                // /*spanish*/los #ReDeads# que custodian un cofre

    hintTable[RHT_SFM_WOLFOS_GROTTO] = HintText(CustomMessage("#Wolfos# guarding a chest",
                                                   /*german*/ "",
                                                   /*french*/ "la #grotte iridescente#"));
                                                // /*spanish*/los #Wolfos# que custodian un cofre

    hintTable[RHT_GV_OCTOROK_GROTTO] = HintText(CustomMessage("an #Octorok# guarding a rich pool",
                                                   /*german*/ "",
                                                   /*french*/ "un #étang sous-terrain avec un Octorok#"));
                                                // /*spanish*/un #Octorok# que custodia un lujoso charco

    hintTable[RHT_DEKU_THEATER] = HintText(CustomMessage("the #Lost Woods Stage#",
                                              /*german*/ "",
                                              /*french*/ "le #théâtre sylvestre#"));
                                           // /*spanish*/el #escenario del Bosque Perdido#

    hintTable[RHT_ZR_OPEN_GROTTO] = HintText(CustomMessage("a #generic grotto#",
                                                /*german*/ "",
                                                /*french*/ "une #grotte avec un trésor#"));
                                             // /*spanish*/una #cueva genérica#
    hintTable[RHT_DMC_UPPER_GROTTO] = HintText(CustomMessage("a #generic grotto#",
                                                  /*german*/ "",
                                                  /*french*/ "une #grotte avec un trésor#"));
                                               // /*spanish*/una #cueva genérica#

    hintTable[RHT_DMT_STORMS_GROTTO] = HintText(CustomMessage("a #generic grotto#",
                                                   /*german*/ "",
                                                   /*french*/ "une #grotte avec un trésor#"));
                                                // /*spanish*/una #cueva genérica#

    hintTable[RHT_KAK_OPEN_GROTTO] = HintText(CustomMessage("a #generic grotto#",
                                                 /*german*/ "",
                                                 /*french*/ "une #grotte avec un trésor#"));
                                              // /*spanish*/una #cueva genérica#

    hintTable[RHT_HF_NEAR_MARKET_GROTTO] = HintText(CustomMessage("a #generic grotto#",
                                                       /*german*/ "",
                                                       /*french*/ "une #grotte avec un trésor#"));
                                                    // /*spanish*/una #cueva genérica#

    hintTable[RHT_HF_OPEN_GROTTO] = HintText(CustomMessage("a #generic grotto#",
                                                /*german*/ "",
                                                /*french*/ "une #grotte avec un trésor#"));
                                             // /*spanish*/una #cueva genérica#
    hintTable[RHT_HF_SOUTHEAST_GROTTO] = HintText(CustomMessage("a #generic grotto#",
                                                     /*german*/ "",
                                                     /*french*/ "une #grotte avec un trésor#"));
                                                  // /*spanish*/una #cueva genérica#

    hintTable[RHT_KF_STORMS_GROTTO] = HintText(CustomMessage("a #generic grotto#",
                                                  /*german*/ "",
                                                  /*french*/ "une #grotte avec un trésor#"));
                                               // /*spanish*/una #cueva genérica#

    hintTable[RHT_LW_NEAR_SHORTCUTS_GROTTO] = HintText(CustomMessage("a #generic grotto#",
                                                          /*german*/ "",
                                                          /*french*/ "une #grotte avec un trésor#"));
                                                       // /*spanish*/una #cueva genérica#

    hintTable[RHT_HF_INSIDE_FENCE_GROTTO] = HintText(CustomMessage("a #single Upgrade Deku Scrub#",
                                                        /*german*/ "",
                                                        /*french*/ "une #grotte avec une peste Mojo#"));
                                                     // /*spanish*/una cueva con un #solitario mercader deku#

    hintTable[RHT_LW_SCRUBS_GROTTO] = HintText(CustomMessage("#2 Deku Scrubs# including an Upgrade one",
                                                  /*german*/ "",
                                                  /*french*/ "une #grotte avec deux pestes Mojo#"));
                                               // /*spanish*/una cueva con #dos mercaderes deku#

    hintTable[RHT_COLOSSUS_GROTTO] = HintText(CustomMessage("2 Deku Scrubs",
                                                 /*german*/ "",
                                                 /*french*/ "une #grotte avec deux pestes Mojo#"));
                                              // /*spanish*/una cueva con #dos mercaderes deku#

    hintTable[RHT_ZR_STORMS_GROTTO] = HintText(CustomMessage("2 Deku Scrubs",
                                                  /*german*/ "",
                                                  /*french*/ "une #grotte avec deux pestes Mojo#"));
                                               // /*spanish*/una cueva con #dos mercaderes deku#

    hintTable[RHT_SFM_STORMS_GROTTO] = HintText(CustomMessage("2 Deku Scrubs",
                                                   /*german*/ "",
                                                   /*french*/ "une #grotte avec deux pestes Mojo#"));
                                                // /*spanish*/una cueva con #dos mercaderes deku#

    hintTable[RHT_GV_STORMS_GROTTO] = HintText(CustomMessage("2 Deku Scrubs",
                                                  /*german*/ "",
                                                  /*french*/ "une #grotte avec deux pestes Mojo#"));
                                               // /*spanish*/una cueva con #dos mercaderes deku#

    hintTable[RHT_LH_GROTTO] = HintText(CustomMessage("3 Deku Scrubs",
                                           /*german*/ "",
                                           /*french*/ "une #grotte avec trois pestes Mojo#"));
                                        // /*spanish*/una cueva con #tres mercaderes deku#

    hintTable[RHT_DMC_HAMMER_GROTTO] = HintText(CustomMessage("3 Deku Scrubs",
                                                   /*german*/ "",
                                                   /*french*/ "une #grotte avec trois pestes Mojo#"));
                                                // /*spanish*/una cueva con #tres mercaderes deku#

    hintTable[RHT_GC_GROTTO] = HintText(CustomMessage("3 Deku Scrubs",
                                           /*german*/ "",
                                           /*french*/ "une #grotte avec trois pestes Mojo#"));
                                        // /*spanish*/una cueva con #tres mercaderes deku#

    hintTable[RHT_LLR_GROTTO] = HintText(CustomMessage("3 Deku Scrubs",
                                            /*german*/ "",
                                            /*french*/ "une #grotte avec trois pestes Mojo#"));
                                         // /*spanish*/una cueva con #tres mercaderes deku#

    hintTable[RHT_ZR_FAIRY_GROTTO] = HintText(CustomMessage("a small #Fairy Fountain#",
                                                 /*german*/ "",
                                                 /*french*/ "une #fontaine de fées#"));
                                              // /*spanish*/una pequeña #fuente de hadas#

    hintTable[RHT_HF_FAIRY_GROTTO] = HintText(CustomMessage("a small #Fairy Fountain#",
                                                 /*german*/ "",
                                                 /*french*/ "une #fontaine de fées#"));
                                              // /*spanish*/una pequeña #fuente de hadas#

    hintTable[RHT_SFM_FAIRY_GROTTO] = HintText(CustomMessage("a small #Fairy Fountain#",
                                                  /*german*/ "",
                                                  /*french*/ "une #fontaine de fées#"));
                                               // /*spanish*/una pequeña #fuente de hadas#

    hintTable[RHT_ZD_STORMS_GROTTO] = HintText(CustomMessage("a small #Fairy Fountain#",
                                                  /*german*/ "",
                                                  /*french*/ "une #fontaine de fées#"));
                                               // /*spanish*/una pequeña #fuente de hadas#

    hintTable[RHT_GF_STORMS_GROTTO] = HintText(CustomMessage("a small #Fairy Fountain#",
                                                  /*german*/ "",
                                                  /*french*/ "une #fontaine de fées#"));
                                               // /*spanish*/una pequeña #fuente de hadas#

    /*--------------------------
    |      JUNK HINT TEXT      |
    ---------------------------*/

    hintTable[RHT_JUNK02] = HintText(CustomMessage("They say you must read the names of \"Special Deal\" shop items carefully.",
                                                  /*german*/ "",
                                                  /*french*/ "Selon moi, les \"Offres spéciales\" sont parfois trompeuses... Lisez les attentivement!"));
                                               // /*spanish*/"Según dicen, se debería prestar atención a los nombres de las ofertas especiales."


 hintTable[RHT_JUNK03] = HintText(CustomMessage("They say that Zelda is a poor leader.",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, Zelda ne ferait pas un bon monarque."));
                                     // /*spanish*/Según dicen, Zelda es mala líder.

    hintTable[RHT_JUNK04] = HintText(CustomMessage("These hints can be quite useful. This is an exception.",
                                        /*german*/ "",
                                        /*french*/ "Ces indices sont très utiles, à l'exception de celui-ci."));
                                     // /*spanish*/Las pistas suelen servir de ayuda. En cambio, esta no.

    hintTable[RHT_JUNK05] = HintText(CustomMessage("They say that the Lizalfos in Dodongo's Cavern like to play in lava.",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, les Lézalfos de la Caverne Dodongo aiment patauger dans la lave."));
                                     // /*spanish*/Según dicen, a los Lizalfos de la Cueva de los Dodongos les gusta jugar en la lava.

    hintTable[RHT_JUNK06] = HintText(CustomMessage("They say that all the Zora drowned in Wind Waker.",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, les Zoras se sont noyés dans Wind Waker."));
                                     // /*spanish*/Según dicen, en Wind Waker todos los zora se ahogaron.

    hintTable[RHT_JUNK07] = HintText(CustomMessage("If Gorons eat rocks, does that mean I'm in danger?",
                                        /*german*/ "",
                                        /*french*/ "Ne dis pas au Gorons que je suis ici. Ils mangent des roches, tu sais!"));
                                     // /*spanish*/Si los Goron se tragan las piedras, ¿no me hace ser una especia vulnarable o algo así

    hintTable[RHT_JUNK08] = HintText(CustomMessage("'Member when Ganon was a blue pig?^I 'member.",
                                        /*german*/ "",
                                        /*french*/ "Dans mon temps, Ganon était un cochon bleu...^Pff! Les jeunes de nos jours, et leur Ganondorf!"));
                                     // /*spanish*/¿T'acuerdas cuando Ganon era un cerdo azul?^Qué tiempos, chico.

    hintTable[RHT_JUNK09] = HintText(CustomMessage("One who does not have Triforce can't go in.",
                                        /*german*/ "",
                                        /*french*/ "Ceux sans Triforce doivent rebrousser chemin."));
                                     // /*spanish*/Aquel que no porte la Trifuerza no podrá pasar.

    hintTable[RHT_JUNK10] = HintText(CustomMessage("Save your future, end the Happy Mask Salesman.",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, tu t'éviteras des jours de malheur si tu vaincs le vendeur de masques..."));
                                     // /*spanish*/Salva tu futuro, acaba con el dueño de La Máscara Feliz.

    hintTable[RHT_JUNK11] = HintText(CustomMessage("Glitches are a pathway to many abilities some consider to be... Unnatural.",
                                        /*german*/ "Los glitches son el camino a muchas habilidades que varios consideran... nada natural.",
                                        /*french*/ "Les glitchs sont un moyen d'acquérir de nombreuses facultés considérées par certains comme... contraire "));
                                     // /*spanish*/à la nature.

    hintTable[RHT_JUNK12] = HintText(CustomMessage("I'm stoned. Get it?",
                                        /*german*/ "",
                                        /*french*/ "Allez, roche, papier, ciseau...&Roche."));
                                     // /*spanish*/Me he quedado de piedra. ¿Lo pillas?

    hintTable[RHT_JUNK13] = HintText(CustomMessage("Hoot! Hoot! Would you like me to repeat that?",
                                        /*german*/ "",
                                        /*french*/ "Hou hou! Veux-tu que je répète tout ça?"));
                                     // /*spanish*/¡Buuu, buuu! ¿Te lo vuelvo a repetir?

    hintTable[RHT_JUNK14] = HintText(CustomMessage("Gorons are stupid. They eat rocks.",
                                        /*german*/ "",
                                        /*french*/ "Les Gorons sont des vraies têtes dures."));
                                     // /*spanish*/Los Goron son tontos. Se comen las piedras.

    hintTable[RHT_JUNK15] = HintText(CustomMessage("They say that Lon Lon Ranch prospered under Ingo.",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, le Ranch Lon Lon était plus prospère sous Ingo."));
                                     // /*spanish*/Según dicen, el Rancho Lon Lon prosperó gracias a Ingo.

    hintTable[RHT_JUNK16] = HintText(CustomMessage("The single rupee is a unique item.",
                                        /*german*/ "",
                                        /*french*/ "Nul objet n'est plus unique que le rubis vert."));
                                     // /*spanish*/La rupia de uno es un objeto singular.

    hintTable[RHT_JUNK17] = HintText(CustomMessage("Without the Lens of Truth, the Treasure Chest Mini-Game is a 1 out of 32 chance.^Good luck!",
                                        /*german*/ "",
                                        /*french*/ "Gagner la Chasse-aux-Trésors est 1 chance sur 32.^Bonne chance!"));
                                     // /*spanish*/Sin la Lupa de la Verdad, ganarías 1/32 veces en el Cofre del Tesoro.^¡Buena suerte con ello!

    hintTable[RHT_JUNK18] = HintText(CustomMessage("Use bombs wisely.",
                                        /*german*/ "",
                                        /*french*/ "Utilise les bombes avec précaution."));
                                     // /*spanish*/No desperdicies las bombas.

    hintTable[RHT_JUNK19] = HintText(CustomMessage("They say that Volvagia hates splinters",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, Volvagia déteste les échardes."));
                                     // /*spanish*/Según dicen, Volvagia le teme a las astillas.

    hintTable[RHT_JUNK20] = HintText(CustomMessage("They say that funky monkeys can be spotted on Friday.",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, des capucins coquins sortent le vendredi."));
                                     // /*spanish*/Según dicen, en los viernes puedes hallar monos marchosos.

    hintTable[RHT_JUNK21] = HintText(CustomMessage("I found you, faker!",
                                        /*german*/ "",
                                        /*french*/ "Ah-ha! Je t'ai trouvé!"));
                                     // /*spanish*/¡Ahí estás, impostor!

    hintTable[RHT_JUNK22] = HintText(CustomMessage("They say the Groose is loose.",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, Hergo est le vrai héros."));
                                     // /*spanish*/Según dicen, Malton es un espanto.
                                
    hintTable[RHT_JUNK23] = HintText(CustomMessage("They say that players who select the \"ON\" option for \"MOTION CONTROL\" are the real \"Zelda players!\"",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, ceux qui utilisent les contrôles gyroscopiques sont les VRAIS joueurs."));
                                        // /*spanish*/ "Según dicen, aquellos que juegan usando el control por movimiento son los verdaderos jugadores de Zelda."

    hintTable[RHT_JUNK24] = HintText(CustomMessage("What happened to Sheik?",
                                        /*german*/ "",
                                        /*french*/ "Donc... Qu'est-ce qui arrive avec Sheik?"));
                                     // /*spanish*/¿Qué la habrá pasado a Sheik?

    hintTable[RHT_JUNK25] = HintText(CustomMessage("L2P @.",
                                        /*german*/ "",
                                        /*french*/ "Arrête de lire les indices et joue comme un grand, @."));
                                     // /*spanish*/Mira que eres novato, @.

    hintTable[RHT_JUNK26] = HintText(CustomMessage("I've heard you can cheat at Sploosh Kaboom.",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, il y a une carte aux trésors à Mercantîle... Duh!"));
                                     // /*spanish*/He oído por ahí que puedes hacer trampa en el Sploosh Kaboom.

    hintTable[RHT_JUNK27] = HintText(CustomMessage("I'm Lonk from Pennsylvania.",
                                        /*german*/ "",
                                        /*french*/ "Je suis Lonk, le héros de Pennsylvanie!"));
                                     // /*spanish*/Soy Lonk, de Pensilvania.

    hintTable[RHT_JUNK28] = HintText(CustomMessage("I bet you'd like to have more bombs.",
                                        /*german*/ "",
                                        /*french*/ "Je parie que tu veux plus de bombes."));
                                     // /*spanish*/Me apuesto a que quisieras tener más bombas.

    hintTable[RHT_JUNK29] = HintText(CustomMessage("When all else fails, use Fire.",
                                        /*german*/ "",
                                        /*french*/ "Quand rien ne marche, utilise le feu."));
                                     // /*spanish*/Cuando nada funcione, usa el fuego.

    hintTable[RHT_JUNK30] = HintText(CustomMessage("Here's a hint, @. Don't be bad.",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, la #Triforce# n'est pas dans le jeu... Duh!"));
                                     // /*spanish*/Aquí tienes una pista, @: deja de ser manco.

    hintTable[RHT_JUNK31] = HintText(CustomMessage("Game Over. Return of Ganon.",
                                        /*german*/ "",
                                        /*french*/ "Partie terminée. RETour de Ganon."));
                                     // /*spanish*/Fin de la partida. El regreso de Ganon.

    hintTable[RHT_JUNK32] = HintText(CustomMessage("May the way of the Hero lead to the Triforce.",
                                        /*german*/ "",
                                        /*french*/ "Que le chemin du héros te mène à la Triforce."));
                                     // /*spanish*/Puede que la senda del héroe te lleve hacia la Trifuerza.

    hintTable[RHT_JUNK33] = HintText(CustomMessage("Can't find an item? Scan an Amiibo.",
                                        /*german*/ "",
                                        /*french*/ "Tu cherches de quoi? Utilise un Amiibo!"));
                                     // /*spanish*/¿No encuentras algo? Escanea un amiibo.

    hintTable[RHT_JUNK34] = HintText(CustomMessage("They say this game has just a few glitches.",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, ce jeu est complètement exempt de glitchs."));
                                     // /*spanish*/Dicen que este juego apenas tiene glitches.

    hintTable[RHT_JUNK35] = HintText(CustomMessage("BRRING BRRING This is Ulrira. Wrong number?",
                                        /*german*/ "",
                                        /*french*/ "DRING DRING!! Pépé le Ramollo à l'appareil... Quoi? Faux numéro?"));
                                     // /*spanish*/¡Ring! ¡Ring! Al habla Ulrira. ¿Me he equivocado de número?

    hintTable[RHT_JUNK36] = HintText(CustomMessage("Tingle Tingle Kooloo Limpah!",
                                        /*german*/ "",
                                        /*french*/ "Tingle! Tingle! Kooloolin... Pah!"));
                                     // /*spanish*/Tingle, Tingle, Kurulín... ¡PA!

    hintTable[RHT_JUNK37] = HintText(CustomMessage("L is real 2401",
                                        /*german*/ "",
                                        /*french*/ "L is real 2401"));
                                     // /*spanish*/L es real 2401.

    hintTable[RHT_JUNK38] = HintText(CustomMessage("They say that Ganondorf will appear in the next Mario Tennis.",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, Ganondorf sera la nouvelle recrue dans Mario Tennis."));
                                     // /*spanish*/Según dicen, Ganondorf estará en el próximo Mario Tennis.

    hintTable[RHT_JUNK39] = HintText(CustomMessage("Medigoron sells the earliest Breath of the Wild demo.",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, Medigoron vend une démo de #Breath of the Wild#."));
                                     // /*spanish*/Medigoron vende la primera demo del Breath of the Wild.

    hintTable[RHT_JUNK40] = HintText(CustomMessage("Can you move me? I don't get great service here.",
                                        /*german*/ "",
                                        /*french*/ "Peux-tu me déplacer? J'ai pas une bonne réception ici."));
                                     // /*spanish*/¿Puedes llevarme a otro lado? Aquí nadie me presta atención.

    hintTable[RHT_JUNK41] = HintText(CustomMessage("They say if you use Strength on the truck, you can find Mew.",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, #Mew# se trouve dessous le camion... Duh!"));
                                     // /*spanish*/Según dicen, puedes hallar un Mew usando Fuerza contra el camión de Ciudad Carmín.

    hintTable[RHT_JUNK42] = HintText(CustomMessage("I'm a helpful hint Gossip Stone!^See, I'm helping.",
                                        /*german*/ "",
                                        /*french*/ "Salut! Je suis une pierre de bons conseils!^Tiens, tu vois? J'aide bien, hein?"));
                                     // /*spanish*/Soy una Piedra Sheikah muy útil.^¡Mira cómo te ayudo!

    hintTable[RHT_JUNK43] = HintText(CustomMessage("Dear @, please come to the castle. I've baked a cake for you.&Yours truly, Princess Zelda.",
                                        /*german*/ "",
                                        /*french*/ "Mon très cher @:&Viens vite au château, je t'ai préparé&un délicieux gâteau...^À bientôt, Princesse Zelda"));
                                     // /*spanish*/Querido @: Por favor, ven al castillo. He hecho una tarta para ti.&Sinceramente tuya: Princesa Zelda.

    hintTable[RHT_JUNK44] = HintText(CustomMessage("They say all toasters toast toast.",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, les grille-pains grillent du pain."));
                                     // /*spanish*/Según dicen, todas las tostadoras tostan tostadas tostadas.

    hintTable[RHT_JUNK45] = HintText(CustomMessage("You thought it would be a useful hint, but it was me, junk hint!",
                                        /*german*/ "",
                                        /*french*/ "Tu t'attendais à un bon indice... Mais c'était moi, un mauvais indice!"));
                                     // /*spanish*/Je... Creeías que iba a ser una piedra de utilidad, ¡pero no, era yo, la piedra de la agonía!

    hintTable[RHT_JUNK46] = HintText(CustomMessage("They say that quest guidance can be found at a talking rock.",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, des #indices# se trouvent auprès d'une pierre parlante... Duh!"));
                                     // /*spanish*/Según dicen, puedes consultarle ayuda a rocas parlanchinas.

    hintTable[RHT_JUNK47] = HintText(CustomMessage("They say that the final item you're looking for can be found somewhere in Hyrule.",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, le #dernier objet# se trouve quelque part dans Hyrule... Duh!"));
                                     // /*spanish*/Según dicen, el último objeto que te falte puede estar en cualquier rincón de Hyrule.

    hintTable[RHT_JUNK48] = HintText(CustomMessage("Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.",
                                        /*german*/ "",
                                        /*french*/ "Mwip.^Mwip.^Mwip.^Mwip.^Mwip.^Mwip.^Mwip.^Mwip.^Mwip.^Mwip.^Mwip.^Mwip."));
                                     // /*spanish*/Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.

    hintTable[RHT_JUNK49] = HintText(CustomMessage("They say that Barinade fears Deku Nuts.",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, Barinade a la frousse des noix Mojo."));
                                     // /*spanish*/Según dicen, lo que más teme a Barinade son las nueces deku.

    hintTable[RHT_JUNK50] = HintText(CustomMessage("They say that Flare Dancers do not fear Goron-crafted blades.",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, le danse-flamme n'a pas peur des armes de Goron."));
                                     // /*spanish*/Según dicen, los Bailafuegos no le temen a las armas forjadas por Gorons.

    hintTable[RHT_JUNK51] = HintText(CustomMessage("They say that Morpha is easily trapped in a corner.",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, Morpha est facilement coincé."));
                                     // /*spanish*/Según dicen, puedes atrapar a Morpha con facilidad en una esquina.

    hintTable[RHT_JUNK52] = HintText(CustomMessage("They say that Bongo Bongo really hates the cold.",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, Bongo Bongo a facilement froid aux doigts."));
                                     // /*spanish*/Según dicen, Bongo Bongo odia a muerte el frío.

    hintTable[RHT_JUNK53] = HintText(CustomMessage("They say that your sword is most powerful when you put it away.",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, ton épée est à pleine puissance quand tu la rengaines."));
                                     // /*spanish*/Según dicen, tu espada se vuelve más poderosa si la guardas.

    hintTable[RHT_JUNK54] = HintText(CustomMessage("They say that bombing the hole Volvagia last flew into can be rewarding.",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, le trou où se creuse Volvagia est vulnérable aux bombes."));
                                     // /*spanish*/Según dicen, trae buena suerte colocar una bomba en el último agujero de donde salió Volvagia.

    hintTable[RHT_JUNK55] = HintText(CustomMessage("They say that invisible ghosts can be exposed with Deku Nuts.",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, des fantômes invisibles apparaissent avec des noix Mojo."));
                                     // /*spanish*/Según dicen, puedes exponer a los espectros invisibles con nueces deku.

    hintTable[RHT_JUNK56] = HintText(CustomMessage("They say that the real Phantom Ganon is bright and loud.",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, le vrai spectre de Ganon est clair et bruyant."));
                                     // /*spanish*/Según dicen, el verdadero Ganon Fantasma es brillante y ruidoso.

    hintTable[RHT_JUNK57] = HintText(CustomMessage("They say that walking backwards is very fast.",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, tu fais marche arrière très rapidement pour un héros."));
                                     // /*spanish*/Según dicen, es más rápido caminar hacia atrás.

    hintTable[RHT_JUNK58] = HintText(CustomMessage("They say that leaping above the Market entrance enriches most children.",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, les enfants riches se pavanent en haut du pont-levis."));
                                     // /*spanish*/Según dicen, saltar por las cadenas a la entrada de la plaza enriquece a muchos chiquillos.

    hintTable[RHT_JUNK59] = HintText(CustomMessage("They say Ingo is not very good at planning ahead.",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, Ingo ne fait pas un très bon geôlier."));
                                     // /*spanish*/Según dicen, a Ingo no se le da especialmente bien planificar con antelación.

    hintTable[RHT_JUNK60] = HintText(CustomMessage("You found a spiritual Stone! By which I mean, I worship Nayru.",
                                        /*german*/ "",
                                        /*french*/ "Vous avez trouvé une Pierre Ancestrale! En effet, je vénère la déesse Hylia."));
                                     // /*spanish*/¡Has encontrado una piedra espiritual! Es que le rindo culto a Nayru...

    hintTable[RHT_JUNK61] = HintText(CustomMessage("They say that a flying strike with a Deku Stick is no stronger than a grounded one.",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, un coup de bâton sauté n'est pas meilleur qu'au sol."));
                                     // /*spanish*/Según dicen, los golpes aéreos con palos deku son tan fuertes como los normales.

    hintTable[RHT_JUNK62] = HintText(CustomMessage("Open your eyes.^Open your eyes.^Wake up, @.",
                                        /*german*/ "",
                                        /*french*/ "Réveille-toi...^Réveille-toi.^Ouvre les yeux, @."));
                                     // /*spanish*/Abre los ojos...^Abre los ojos...^Despierta, @...

    hintTable[RHT_JUNK63] = HintText(CustomMessage("They say that the Nocturne of Shadow can bring you very close to Ganon.",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, le nocturne de l'ombre peut t'amener très près de Ganon."));
                                     // /*spanish*/Según dicen, el Nocturno de la sombra te puede acercar mucho a Ganon.

    hintTable[RHT_JUNK64] = HintText(CustomMessage("They say that Twinrova always casts the same spell the first three times.",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, Twinrova lance toujours les mêmes trois premiers sorts."));
                                     // /*spanish*/Según dicen, Birova siempre lanza el mismo hechizo las tres primeras veces.

    hintTable[RHT_JUNK65] = HintText(CustomMessage("They say that the nightly builds may be unstable.",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, les \"nightly builds\" peuvent être instables."));
                                     // /*spanish*/Según dicen, las últimas nightlies pueden llegar a ser algo inestables.

    hintTable[RHT_JUNK66] = HintText(CustomMessage("You're playing a Randomizer. I'm randomized!^Here's a random number:  #4#.&Enjoy your Randomizer!",
                                        /*german*/ "",
                                        /*french*/ "Tu joues à un randomizer. Je suis aléatoire!^Voici un nombre aléatoire: #4#.&Bonne partie!"));
                                     // /*spanish*/¡Estás jugando un Randomizer! ¡Yo también estoy aleatorizada!^Aquí tienes un número aleatorio: #8#.&¡Diviértete!  

    hintTable[RHT_JUNK67] = HintText(CustomMessage("They say Ganondorf's bolts can be reflected with glass or steel.",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, les éclairs de Ganon se reflètent sur l'acier et le verre."));
                                     // /*spanish*/Según dicen, puedes reflejar las esferas de energía de Ganondorf con cristal y acero.

    hintTable[RHT_JUNK68] = HintText(CustomMessage("They say Ganon's tail is vulnerable to nuts, arrows, swords, explosives, hammers...^...sticks, seeds, "
                                                   "boomerangs...^...rods, shovels, iron balls, angry bees...",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, la queue de Ganon est vulnérable aux noix, flèches, épées, bombes, marteaux...^...bâtons, "
                                                   "graines, boomerangs...^...baguettes, pelles, boulets de fer, abeilles enragées..."));
                                     // /*spanish*/Según dicen, la cola de Ganon es vulnerable a nueces, flechas, espadas, explosivos, 
                                                // martillos...^...palos, semillas, bumeráns...^...cetros, palas, bolas de hierro, abejas...

    hintTable[RHT_JUNK69] = HintText(CustomMessage("They say that you're wasting time reading this hint, but I disagree. Talk to me again!",
                                        /*german*/ "",
                                        /*french*/ "Selon moi... tu sais quoi? Parle-moi encore, et je te le dirai!"));
                                     // /*spanish*/Según dicen, pierdes el tiempo en leer esta pista, pero no pienso igual. ¡Vuelve a hablarme, ya verás!

    hintTable[RHT_JUNK70] = HintText(CustomMessage("They say Ganondorf knows where to find the instrument of his doom.",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, Ganondorf sait où il a caché son point faible."));
                                     // /*spanish*/Según dicen, Ganondorf sabe dónde hallar el instrumento de su perdición.

    hintTable[RHT_JUNK71] = HintText(CustomMessage("I heard @ is pretty good at Zelda.",
                                        /*german*/ "",
                                        /*french*/ "Apparemment, @ est super bon à Zelda."));
                                     // /*spanish*/He oído que a @ se le dan muy bien los Zelda.

    hintTable[RHT_JUNK72] = HintText(CustomMessage("Hi @, we've been trying to reach you about your car's extended warranty. ",
                                        /*german*/ "",
                                        /*french*/ "Bonjour, @. Vous avez une voiture? Vous savez, nous offrons des assurances abordables..."));
                                     // /*spanish*/Buenas, @. Le llamamos para ofrecerle un nuevo seguro de hogar que puede pagar en cómodos plazos, sin 
                                                // intereses ni comisiones.

    hintTable[RHT_JUNK73] = HintText(CustomMessage("They say that the best weapon against Iron Knuckles is item 176.",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, les hache-viandes sont vulnérables contre l'objet 176."));
                                     // /*spanish*/Según dicen, la mejor arma para enfrentarse a los Nudillos de hierro es el objeto 176.

    hintTable[RHT_JUNK74] = HintText(CustomMessage("They say that it's actually possible to beat the running man.",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, il est possible de battre le coureur.&Donc, tu prends ton arc, et..."));
                                     // /*spanish*/Según dicen, con mucha perseverancia puedes ganarle al corredor con la capucha de conejo.

    hintTable[RHT_JUNK75] = HintText(CustomMessage("They say that the stone-cold guardian of the Well is only present during work hours.",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, le gardien de pierre du Puits quitte le soir pour aller se coucher."));
                                     // /*spanish*/Según dicen, la inmensa roca que bloquea el pozo solo trabaja en horas laborales.

    hintTable[RHT_JUNK76] = HintText(CustomMessage("They say this hint makes more sense in other languages.",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, ces indices auraient pu être mieux traduits... Duh!"));
                                     // /*spanish*/Según dicen, esta pista revela algo de vital importancia si cambias el idioma del juego...

    hintTable[RHT_JUNK77] = HintText(CustomMessage("BOK? No way.",
                                        /*german*/ "",
                                        /*french*/ "BD'accord? Hors de question."));
                                     // /*spanish*/¿BVale? Ni hablar.

    // ^ junk hints above are from 3drando
    // v junk hints below are new to soh rando

#define HINT_TEXT_NEEDS_TRANSLATION_FR \
    "Erreur 0x69a504:&Traduction manquante^C'est de la faute à Purple Hato!&J'vous jure!"

    hintTable[RHT_JUNK78] = HintText(CustomMessage("They say blarg...^...or at least briaguya does.",
                                        /*german*/ "",
                                        /*french*/ "Tout ce que j'ai à dire, c'est blarg...^... 'fin c'est plutôt ce que briaguya dirait."));
                                     // /*spanish*/blarg

    hintTable[RHT_JUNK79] = HintText(CustomMessage("They say this peace is what all true warriors strive for.",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, cette paix est ce pour quoi luttent tous les vrais guerriers."));
                                     // /*spanish*/blarg

    hintTable[RHT_JUNK80] = HintText(CustomMessage("They say this ship is what all true gamers strive for.",
                                        /*german*/ "",
                                        /*french*/ "Selon moi, cette version du port est ce pour quoi luttent tous les vrais gamers."));
                                     // /*spanish*/blarg

    hintTable[RHT_JUNK81] = HintText(CustomMessage("They say that Glowsticks can be found in the Raveyard.",
                                        /*german*/ "",
                                        /*french*/ "On peut trouver des Bâtons Lumineux sur le dancefloor du cimetière."));
                                     // /*spanish*/blarg

    hintTable[RHT_JUNK_WTC_1] = HintText(CustomMessage("They say %rthere are no more than 18&people on this island.",
                                            /*german*/ "",
                                            /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_WTC_2] = HintText(CustomMessage("They say I am one yet many",
                                            /*german*/ "",
                                            /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_WTC_3] = HintText(CustomMessage("They say its all in the name of guiding&humanity down the right path.",
                                            /*german*/ "",
                                            /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_WTC_4] = HintText(CustomMessage("They say \"Repetition requested\"",
                                            /*german*/ "",
                                            /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_WTC_5] = HintText(CustomMessage("They say %rThe red tells only the truth!",
                                            /*german*/ "",
                                            /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_WTC_6] = HintText(CustomMessage("They say good tidings to you^my traitorous @",
                                            /*german*/ "",
                                            /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_WTC_7] = HintText(CustomMessage("They say when the seagulls cried,&none were left alive.",
                                            /*german*/ "",
                                            /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_WTC_8] = HintText(CustomMessage("They say she is lying with the red letters!",
                                            /*german*/ "",
                                            /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_WTC_9] = HintText(CustomMessage("They say we'll meet again,&when something else cries.",
                                            /*german*/ "",
                                            /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_WTC_10] = HintText(CustomMessage("They say \"Forgive me, but-^Your script will not be used.&....After all...^The one writing the rest of "
                                                        "the script...&will be me.\"",
                                             /*german*/ "",
                                             /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_WTC_11] = HintText(CustomMessage("They say tea is best enjoyed...^\"\"With your fellow monsters.\"\"",
                                             /*german*/ "",
                                             /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));


    hintTable[RHT_JUNK_WTC_12] = HintText(CustomMessage("They say I shall make you some black tea. With my own hands, not magic.",
                                             /*german*/ "",
                                             /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_SEI_1] = HintText(CustomMessage("They say you know I've kiboshed before...^and I will kibosh again.",
                                            /*german*/ "",
                                            /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_SEI_2] = HintText(CustomMessage("They say if relationship @ walks through that door,^they will KILL independent @.",
                                            /*german*/ "",
                                            /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_SEI_3] = HintText(CustomMessage("They say you gotta have the BIG Salad.",
                                            /*german*/ "",
                                            /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_SEI_4] = HintText(CustomMessage("They say it's a festivus miracle",
                                            /*german*/ "",
                                            /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_SEI_5] = HintText(CustomMessage("They say there are no houses in Tuscany to rent.",
                                            /*german*/ "",
                                            /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_SEI_6] = HintText(CustomMessage("They say my last boyfriend had a real&Kroner comprehension problem.",
                                            /*german*/ "",
                                            /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_SEI_7] = HintText(CustomMessage("They say it's a festivus miracle.",
                                            /*german*/ "",
                                            /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_SEI_8] = HintText(CustomMessage("They say Louis quit the importing&to focus on the exporting.",
                                            /*german*/ "",
                                            /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_SEI_9] = HintText(CustomMessage("They say no thanks, I can't drink coffee&late at night, it keeps me up.",
                                            /*german*/ "",
                                            /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_SEI_10] = HintText(CustomMessage("They say it's not a lie if you believe it.",
                                             /*german*/ "",
                                             /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_SEI_11] = HintText(CustomMessage("They say there was a second spitter.",
                                             /*german*/ "",
                                             /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_SEI_12] = HintText(CustomMessage("They say there was a second spitter.",
                                             /*german*/ "",
                                             /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_SEI_13] = HintText(CustomMessage("They say the jerk store called,^they're running out of YOU.",
                                             /*german*/ "",
                                             /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_SEI_14] = HintText(CustomMessage("They say when you look annoyed all the time,&people thing you are busy.",
                                             /*german*/ "",
                                             /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_SEI_15] = HintText(CustomMessage("They say when you look annoyed all the time,&people think you are busy.",
                                             /*german*/ "",
                                             /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_SEI_16] = HintText(CustomMessage("They say he fires people like its a bodily function.",
                                             /*german*/ "",
                                             /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_SEI_17] = HintText(CustomMessage("They say he threatened to move the ship to New Jersey&just to upset people.",
                                             /*german*/ "",
                                             /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_SEI_18] = HintText(CustomMessage("They say there was significant shrinkage.",
                                             /*german*/ "",
                                             /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_SEI_19] = HintText(CustomMessage("They say if it wasn't for the toilet there'd be no books.",
                                             /*german*/ "",
                                             /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_SEI_20] = HintText(CustomMessage("They say if it wasn't for the toilet there'd be no books.",
                                             /*german*/ "",
                                             /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_SEI_21] = HintText(CustomMessage("They say don't trust men in capes.",
                                             /*german*/ "",
                                             /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_SEI_22] = HintText(CustomMessage("They say @'s uncle works for Nintendo.",
                                             /*german*/ "",
                                             /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_SEI_23] = HintText(CustomMessage("They say @'s stole the marble rye.",
                                             /*german*/ "",
                                             /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_SEI_24] = HintText(CustomMessage("They say there is no better harmony&than the black and white cookie.",
                                             /*german*/ "",
                                             /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_SEI_25] = HintText(CustomMessage("They say @ hasn't vomited since 1983.",
                                             /*german*/ "",
                                             /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_SEI_26] = HintText(CustomMessage("They say you gotta have the early bird special.",
                                             /*german*/ "",
                                             /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_SEI_27] = HintText(CustomMessage("They say a donation has been made in your name&to the human fund.",
                                             /*german*/ "",
                                             /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_SEI_28] = HintText(CustomMessage("They say you want to be my latex salesman.",
                                             /*german*/ "",
                                             /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_SEI_29] = HintText(CustomMessage("They say if every instinct you have is wrong...^... then the opposite would have to be right.",
                                             /*german*/ "",
                                             /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_OTR_MEANS_1] = HintText(CustomMessage("They say OTR stands for&Over the Rainbow",
                                                  /*german*/ "",
                                                  /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_OTR_MEANS_2] = HintText(CustomMessage("They say that OTR stands for&Onions, Tomatoes, and Radishes",
                                                  /*german*/ "",
                                                  /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_OTR_MEANS_3] = HintText(CustomMessage("They say that OTR stands for&Ocarina of Time Resources",
                                                  /*german*/ "",
                                                  /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_OTR_MEANS_4] = HintText(CustomMessage("They say that OTR stands for&Over the Road",
                                                  /*german*/ "",
                                                  /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_OTR_MEANS_5] = HintText(CustomMessage("They say that OTR stands for&Off the Record",
                                                  /*german*/ "",
                                                  /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_OTR_MEANS_6] = HintText(CustomMessage("They say that OTR stands for&Office of Tax and Revenue",
                                                  /*german*/ "",
                                                  /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_OTR_MEANS_7] = HintText(CustomMessage("They say OTR stands for&Over the Rainbow",
                                                  /*german*/ "",
                                                  /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_OTR_MEANS_8] = HintText(CustomMessage("They say that OTR stands for&Office of Trade Relations",
                                                  /*german*/ "",
                                                  /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_OTR_MEANS_9] = HintText(CustomMessage("They say that OTR stands for&Original Theatrical Release",
                                                  /*german*/ "",
                                                  /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_OTR_MEANS_10] = HintText(CustomMessage("They say that OTR stands for&Operational Test Requirement",
                                                   /*german*/ "",
                                                   /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_OTR_MEANS_11] = HintText(CustomMessage("They say that OTR stands for&Operational Trouble Report",
                                                   /*german*/ "",
                                                   /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_OTR_MEANS_12] = HintText(CustomMessage("They say that OTR stands for&Oxygen Transmission Rate",
                                                   /*german*/ "",
                                                   /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_OTR_MEANS_13] = HintText(CustomMessage("They say that OTR stands for&One Touch Recording",
                                                   /*german*/ "",
                                                   /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_OTR_MEANS_14] = HintText(CustomMessage("They say that OTR stands for&Olympic Torch Relay",
                                                   /*german*/ "",
                                                   /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_OTR_MEANS_15] = HintText(CustomMessage("They say that OTR stands for&Off the Rack",
                                                   /*german*/ "",
                                                   /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_OTR_MEANS_16] = HintText(CustomMessage("They say that OTR stands for&Overhead Transfer Rate",
                                                   /*german*/ "",
                                                   /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_OTR_MEANS_17] = HintText(CustomMessage("They say that OTR stands for&Operational TurnaRound",
                                                   /*german*/ "",
                                                   /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_OTR_MEANS_18] = HintText(CustomMessage("They say that OTR stands for&Opportunity to Recall",
                                                   /*german*/ "",
                                                   /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_OTR_MEANS_19] = HintText(CustomMessage("They say that OTR stands for&Operability Test Report",
                                                   /*german*/ "",
                                                   /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_OTR_MEANS_20] = HintText(CustomMessage("They say that OTR stands for&Overall Tuning Range",
                                                   /*german*/ "",
                                                   /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_OTR_MEANS_21] = HintText(CustomMessage("They say that OTR stands for&One Time Requisition",
                                                   /*german*/ "",
                                                   /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_OTR_MEANS_22] = HintText(CustomMessage("They say that OTR stands for&Oblivious to Reality",
                                                   /*german*/ "",
                                                   /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_OTR_MEANS_23] = HintText(CustomMessage("They say that OTR stands for&On the Run",
                                                   /*german*/ "",
                                                   /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_OTR_MEANS_24] = HintText(CustomMessage("They say that OTR stands for&On Time Reporting",
                                                   /*german*/ "",
                                                   /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_OTR_MEANS_25] = HintText(CustomMessage("They say that OTR stands for&Order to Receipt",
                                                   /*german*/ "",
                                                   /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_OTR_MEANS_26] = HintText(CustomMessage("They say that OTR stands for&Other Terrestrial Radio",
                                                   /*german*/ "",
                                                   /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_OTR_MEANS_27] = HintText(CustomMessage("They say that OTR stands for&On Target Reports",
                                                   /*german*/ "",
                                                   /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_OTR_MEANS_28] = HintText(CustomMessage("They say that OTR stands for&One Time Repair",
                                                   /*german*/ "",
                                                   /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_OTR_MEANS_29] = HintText(CustomMessage("They say that OTR stands for&Own the Room",
                                                   /*german*/ "",
                                                   /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_OTR_MEANS_30] = HintText(CustomMessage("They say that OTR stands for&Online Text Repository",
                                                   /*german*/ "",
                                                   /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_MISC_1] = HintText(CustomMessage("They say #Kenix# isn't a developer...^...Just a PR guy",
                                             /*german*/ "",
                                             /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR,
                                                        {QM_GREEN}));

    hintTable[RHT_JUNK_MISC_2] = HintText(CustomMessage("They say... No",
                                             /*german*/ "",
                                             /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_MISC_3] = HintText(CustomMessage("They say BIG RIGS: OTR",
                                             /*german*/ "",
                                             /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_MISC_4] = HintText(CustomMessage("They say you wanted to see me #Mr. Kenix#?",
                                             /*german*/ "",
                                             /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR,
                                                        {QM_PINK}));

    hintTable[RHT_JUNK_MISC_5] = HintText(CustomMessage("They say Louis once saw an&equals not get set equals",
                                             /*german*/ "",
                                             /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_MISC_6] = HintText(CustomMessage("They say only you can find your rom.",
                                             /*german*/ "",
                                             /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_MISC_7] = HintText(CustomMessage("They say ZAPD is good software.",
                                             /*german*/ "",
                                             /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_MISC_8] = HintText(CustomMessage("They say you can encounter&a parascode in tall grass.",
                                             /*german*/ "",
                                             /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_MISC_9] = HintText(CustomMessage("They say the ship sails on March 32nd.",
                                             /*german*/ "",
                                             /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_MISC_10] = HintText(CustomMessage("They say bombing dodongos is fun.",
                                              /*german*/ "",
                                              /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_MISC_11] = HintText(CustomMessage("They say shopkeepers don't give credits.",
                                              /*german*/ "",
                                              /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_MISC_12] = HintText(CustomMessage("They say shopkeepers don't give credits.",
                                              /*german*/ "",
                                              /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_MISC_13] = HintText(CustomMessage("They say Malon is glitched.",
                                              /*german*/ "",
                                              /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_MISC_14] = HintText(CustomMessage("They say do I look like I know&what a DList is?",
                                              /*german*/ "",
                                              /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_MISC_15] = HintText(CustomMessage("They say do I look like I know&what an AList is?",
                                              /*german*/ "",
                                              /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_MISC_16] = HintText(CustomMessage("They say the king drinks enthusiastically",
                                              /*german*/ "",
                                              /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_MISC_17] = HintText(CustomMessage("They say Rubies are on the path to&Lamp Oil, Rope, and Bombs",
                                              /*german*/ "",
                                              /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_SG_1] = HintText(CustomMessage("They say %rError. Human is dead, mismatch.",
                                           /*german*/ "",
                                           /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_SG_2] = HintText(CustomMessage("They say this is the choice of the&steins gate.",
                                           /*german*/ "",
                                           /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_SG_3] = HintText(CustomMessage("They say el psy kongroo.",
                                           /*german*/ "",
                                           /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_SG_4] = HintText(CustomMessage("They say tutturu~.",
                                           /*german*/ "",
                                           /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_SG_5] = HintText(CustomMessage("They say im not Christina!.",
                                           /*german*/ "",
                                           /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_SG_6] = HintText(CustomMessage("They say you know where to find an IBN5100.",
                                           /*german*/ "",
                                           /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_SG_7] = HintText(CustomMessage("They say when you're on a chicken bender&grab a box of chicken tenders.",
                                           /*german*/ "",
                                           /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    hintTable[RHT_JUNK_SG_8] = HintText(CustomMessage("Juicy Chicken #1! Wow!.",
                                           /*german*/ "",
                                           /*french*/ HINT_TEXT_NEEDS_TRANSLATION_FR));

    /*--------------------------
    |     DUNGEON HINT TEXT    |
    ---------------------------*/

    
    hintTable[RHT_DEKU_TREE] = HintText(CustomMessage("Deku Tree",
                                           /*german*/ "",
                                           /*french*/ "l'Arbre Mojo"),
                                        // /*spanish*/el Gran Árbol Deku
                                        {},
                                        {CustomMessage("an ancient tree",
                                            /*german*/ "",
                                            /*french*/ "le vieil arbre")});
                                         // /*spanish*/un ancestral árbol

    hintTable[RHT_DODONGOS_CAVERN] = HintText(CustomMessage("Dodongo's Cavern",
                                                 /*german*/ "",
                                                 /*french*/ "la Caverne Dodongo"),
                                              // /*spanish*/la Cueva de los Dodongos
                                              {},
                                              {CustomMessage("an immense cavern",
                                                  /*german*/ "",
                                                  /*french*/ "l'immense caverne")});
                                               // /*spanish*/una descomunal cueva

    hintTable[RHT_JABU_JABUS_BELLY] = HintText(CustomMessage("Jabu-Jabu's Belly",
                                                  /*german*/ "",
                                                  /*french*/ "le Ventre de Jabu-Jabu"),
                                               // /*spanish*/tripa de Jabu-Jabu
                                               {},
                                               {CustomMessage("the belly of a deity",
                                                   /*german*/ "",
                                                   /*french*/ "le ventre d'un gardien")});
                                                // /*spanish*/la tripa de cierta deidad

    hintTable[RHT_FOREST_TEMPLE] = HintText(CustomMessage("Forest Temple",
                                               /*german*/ "",
                                               /*french*/ "le Temple de la Forêt"),
                                            // /*spanish*/el Templo del Bosque
                                            {},
                                            {CustomMessage("a deep forest",
                                                /*german*/ "",
                                                /*french*/ "la profonde forêt")});
                                             // /*spanish*/las profundidades del bosque

    hintTable[RHT_FIRE_TEMPLE] = HintText(CustomMessage("Fire Temple",
                                             /*german*/ "",
                                             /*french*/ "le Temple du Feu"),
                                          // /*spanish*/el Templo del Fuego
                                          {},
                                          {CustomMessage("a high mountain",
                                              /*german*/ "",
                                              /*french*/ "la grande montagne")});
                                           // /*spanish*/una alta montaña

    hintTable[RHT_WATER_TEMPLE] = HintText(CustomMessage("Water Temple",
                                              /*german*/ "",
                                              /*french*/ "le Temple de l'Eau"),
                                           // /*spanish*/el Templo del Agua
                                           {},
                                           {CustomMessage("a vast lake",
                                               /*german*/ "",
                                               /*french*/ "le vaste lac")});
                                            // /*spanish*/un lago inmenso

    hintTable[RHT_SPIRIT_TEMPLE] = HintText(CustomMessage("Spirit Temple",
                                               /*german*/ "",
                                               /*french*/ "le Temple de l'Esprit"),
                                            // /*spanish*/el Templo del Espíritu
                                            {},
                                            {CustomMessage("the goddess of the sand",
                                                /*german*/ "",
                                                /*french*/ "la déesse des sables")});
                                             // /*spanish*/la diosa de las arenas

    hintTable[RHT_SHADOW_TEMPLE] = HintText(CustomMessage("Shadow Temple",
                                               /*german*/ "",
                                               /*french*/ "le Temple de l'Ombre"),
                                            // /*spanish*/el Templo de las Sombras
                                            {},
                                            {CustomMessage("the house of the dead",
                                                /*german*/ "",
                                                /*french*/ "la maison des morts")});
                                             // /*spanish*/la casa de la muerte    
                                             
    hintTable[RHT_ICE_CAVERN] = HintText(CustomMessage("Ice Cavern",
                                            /*german*/ "",
                                            /*french*/ "la caverne de glace"),
                                         // /*spanish*/la caverna de hielo
                                         {},
                                         {CustomMessage("a frozen maze",
                                             /*german*/ "",
                                             /*french*/ "le dédale glacé")});
                                          // /*spanish*/un gélido laberinto

    hintTable[RHT_BOTTOM_OF_THE_WELL] = HintText(CustomMessage("Bottom of the Well",
                                                    /*german*/ "",
                                                    /*french*/ "le fonds du Puits"),
                                                 // /*spanish*/el fondo del pozo
                                                 {},
                                                 {CustomMessage("a shadow\'s prison",
                                                     /*german*/ "",
                                                     /*french*/ "la prison d'une ombre")});
                                                  // /*spanish*/la prisión de las sombras

    hintTable[RHT_GERUDO_TRAINING_GROUND] = HintText(CustomMessage("Gerudo Training Grounds",
                                                        /*german*/ "",
                                                        /*french*/ "le Gymnase Gerudo"),
                                                     // /*spanish*/el Centro de Instrucción Gerudo
                                                     {},
                                                     {CustomMessage("the test of thieves",
                                                         /*german*/ "",
                                                         /*french*/ "l'épreuve des voleurs")});
                                                      // /*spanish*/la prueba de las bandidas

    hintTable[RHT_GANONS_CASTLE] = HintText(CustomMessage("Inside Ganon's Castle",
                                               /*german*/ "",
                                               /*french*/ "l'intérieur du Château de Ganon"),
                                            // /*spanish*/el interior del Castillo de Ganon
                                            {},
                                            {CustomMessage("a conquered citadel",
                                                /*german*/ "",
                                                /*french*/ "la citadelle assiégée")});
                                             // /*spanish*/una conquistada ciudadela

    /*--------------------------
    |      BOSS HINT TEXT      |
    ---------------------------*/

    hintTable[RHT_QUEEN_GOHMA] = HintText(CustomMessage("#Queen Gohma# holds",
                                             /*german*/ "",
                                             /*french*/ "la #Reine Gohma# possède"),
                                          // /*spanish*/la #Reina Goma# porta
                                          {},
                                          {CustomMessage("the #Parasitic Armored Arachnid# holds",
                                              /*german*/ "",
                                              /*french*/ "le #monstre insectoïde géant# possède")});
                                           // /*spanish*/el #arácnido parasitario acorazado# porta

    hintTable[RHT_KING_DODONGO] = HintText(CustomMessage("#King Dodongo# holds",
                                              /*german*/ "",
                                              /*french*/ "le #Roi Dodongo# possède"),
                                           // /*spanish*/el #Rey Dodongo# porta
                                           {},
                                           {CustomMessage("the #Infernal Dinosaur# holds",
                                               /*german*/ "",
                                               /*french*/ "le #dinosaure infernal# possède")});
                                            // /*spanish*/el #dinosaurio infernal# porta

    hintTable[RHT_BARINADE] = HintText(CustomMessage("#Barinade# holds",
                                          /*german*/ "",
                                          /*french*/ "#Barinade# possède"),
                                       // /*spanish*/#Barinade# porta
                                       {},
                                       {CustomMessage("the #Bio-Electric Anemone# holds",
                                           /*german*/ "",
                                           /*french*/ "l'#anémone bioélectrique# possède")});
                                        // /*spanish*/la #anémona bioeléctrica# porta

    hintTable[RHT_PHANTOM_GANON] = HintText(CustomMessage("#Phantom Ganon# holds",
                                               /*german*/ "",
                                               /*french*/ "#Ganon Spectral# possède"),
                                            // /*spanish*/#Ganon Fantasma# porta
                                            {},
                                            {CustomMessage("the #Evil Spirit from Beyond# holds",
                                                /*german*/ "",
                                                /*french*/ "l'#esprit maléfique de l'au-delà# possède")});
                                             // /*spanish*/el #espíritu maligno de ultratumba# porta

    hintTable[RHT_VOLVAGIA] = HintText(CustomMessage("#Volvagia# holds",
                                          /*german*/ "",
                                          /*french*/ "#Volvagia# possède"),
                                       // /*spanish*/#Volvagia# porta
                                       {},
                                       {CustomMessage("the #Subterranean Lava Dragon# holds",
                                           /*german*/ "",
                                           /*french*/ "le #dragon des profondeurs# possède")});
                                        // /*spanish*/el #dragón de lava subterráneo# porta

    hintTable[RHT_MORPHA] = HintText(CustomMessage("#Morpha# holds",
                                        /*german*/ "",
                                        /*french*/ "#Morpha# possède"),
                                     // /*spanish*/#Morpha# porta
                                     {},
                                     {CustomMessage("the #Giant Aquatic Amoeba# holds",
                                         /*german*/ "",
                                         /*french*/ "l'#amibe aquatique géante# possède")});
                                      // /*spanish*/la #ameba acuática gigante# porta

    hintTable[RHT_BONGO_BONGO] = HintText(CustomMessage("#Bongo Bongo# holds",
                                             /*german*/ "",
                                             /*french*/ "#Bongo Bongo# possède"),
                                          // /*spanish*/#Bongo Bongo# porta
                                          {},
                                          {CustomMessage("the #Phantom Shadow Beast# holds",
                                              /*german*/ "",
                                              /*french*/ "le #monstre de l'ombre# possède")});
                                           // /*spanish*/la #alimaña oscura espectral# porta

    hintTable[RHT_TWINROVA] = HintText(CustomMessage("#Twinrova# holds",
                                          /*german*/ "",
                                          /*french*/ "#Twinrova# possède"),
                                       // /*spanish*/#Birova# porta
                                       {},
                                       {CustomMessage("the #Sorceress Sisters# hold",
                                           /*german*/ "",
                                           /*french*/ "#les sorcières jumelles# possède")});
                                        // /*spanish*/las #hermanas hechiceras# portan
    /*--------------------------
    |     BRIDGE HINT TEXT     |
    ---------------------------*/

    hintTable[RHT_BRIDGE_OPEN_HINT] = HintText(CustomMessage("$lThe awakened ones have #already created a bridge# to the castle where the evil dwells.^",
                                                  /*german*/ "$lDie Weisen haben #bereits&eine Brücke zum Portal von&Ganons Schloss gelegt#...^",
                                                  /*french*/ "$lLes êtres de sagesse ont#déjà créé un pont# vers le repaire du mal.^",
                                                             {QM_LBLUE}));
                                               // /*spanish*/$lLos sabios #ya habrán creado un puente#&al castillo, de donde emana el mal.^


    hintTable[RHT_BRIDGE_VANILLA_HINT] = HintText(CustomMessage("$6The awakened ones require the #Shadow and Spirit Medallions# as well as the #Light Arrows#.^",
                                                    /*german*/ "$6Die Weisen werden darauf warten, dass der Held das #Amulett des Schattens, Amulett der Geister# und die #Licht-Pfeile# sammelt.^",
                                                    /*french*/ "$6Les êtres de sagesse attendront le héros muni des #Médaillons de l'Ombre et l'Esprit# et des #Flèches de Lumière#.^",
                                                               {QM_RED, QM_YELLOW}));
                                                 // /*spanish*/$6Los sabios aguardarán a que el héroe obtenga tanto el #Medallón de las Sombras y el del Espíritu# junto 
                                                            // a la #flecha de luz#.^

    hintTable[RHT_BRIDGE_STONES_HINT] = HintText(CustomMessage("$0The awakened ones will await for the Hero to collect #[[d]] Spiritual Stone||s|#.^",
                                                    /*german*/ "$0Die Weisen werden darauf warten, dass der Held #[[d]] |Heiligen Stein|Heilige Steine|# sammelt.^",
                                                    /*french*/ "$0Les êtres de sagesse attendront le héros muni de #[[d]] |Pierre Ancestrale|Pierres Ancestrales|#.^",
                                                               {QM_BLUE}));
                                                 // /*spanish*/$0Los sabios aguardarán a que el héroe&obtenga #[[d]] |piedra espiritual|piedras espirituales|#.^

    hintTable[RHT_BRIDGE_MEDALLIONS_HINT] = HintText(CustomMessage("$8The awakened ones will await for the Hero to collect #[[d]] Medallion||s|#.^",
                                                        /*german*/ "$8Die Weisen werden darauf warten, dass der Held #[[d]] Amulett||e|# sammelt.^",
                                                        /*french*/ "$8Les êtres de sagesse attendront le héros muni de #[[d]] Médaillon||s|#.^",
                                                                   {QM_RED}));
                                                     // /*spanish*/$8Los sabios aguardarán a que el héroe&obtenga #[[d]] |medallón|medallones|#.^

    hintTable[RHT_BRIDGE_MEDALLIONS_HINT] = HintText(CustomMessage("$CThe awakened ones will await for the Hero to collect #[[d]]# |#Spiritual Stone# or #Medallion#|"
                                                                   "#Spiritual Stones# and #Medallions#|.^",
                                                        /*german*/ "$CDie Weisen werden darauf warten, dass der Held #[[d]]# |#Heiligen Stein# oder #Amulett#|"
                                                                   "#Heilige Steine# oder #Amulette#| sammelt.^",
                                                        /*french*/ "$CLes êtres de sagesse attendront le héros muni de #[[d]]# |#Pierre Ancestrale# ou #Médaillon#"
                                                                   "|#Pierres Ancestrales# ou #Médaillons#|.^",
                                                                   {QM_YELLOW, QM_BLUE, QM_RED}));
                                                     // /*spanish*/$CLos sabios aguardarán a que el héroe obtenga #[[d]]# |#piedra espiritual# o #medallón#|
                                                                //#piedras espirtuales# y #medallones#|.^

    hintTable[RHT_BRIDGE_DUNGEONS_HINT] = HintText(CustomMessage("$mThe awakened ones will await for the Hero to conquer #[[d]] Dungeon||s|#.^",
                                                      /*german*/ "$mDie Weisen werden darauf warten, dass der Held #[[d]] Labyrinth||e|# abschließt.^",
                                                      /*french*/ "$mLes êtres de sagesse attendront la conquête de #[[d]] Donjon||s|#.^",
                                                                 {QM_PINK}));
                                                   // /*spanish*/$mLos sabios aguardarán a que el héroe complete #[[d]] mazmorra||s|#.^

    hintTable[RHT_BRIDGE_TOKENS_HINT] = HintText(CustomMessage("$sThe awakened ones will await for the Hero to collect #[[d]] Gold Skulltula Token||s|#.^",
                                                    /*german*/ "$sDie Weisen werden darauf warten, dass der Held #[[d]] Skulltula-Symbol||e|# sammelt.^",
                                                    /*french*/ "$sLes êtres de sagesse attendront le héros muni de #[[d]] Symbole||s| de Skulltula d'or#.^",
                                                               {QM_YELLOW}));
                                                 // /*spanish*/$sLos sabios aguardarán a que el héroe obtenga #[[d]] símbolo||s| de skulltula dorada#.^

    hintTable[RHT_BRIDGE_GREG_HINT] = HintText(CustomMessage("$gThe awakened ones will await for the Hero to find #Greg#.^",
                                                             {QM_GREEN}));


    /*--------------------------
    | GANON BOSS KEY HINT TEXT |
    ---------------------------*/

    hintTable[RHT_GANON_BK_START_WITH_HINT] = HintText(CustomMessage("$bAnd the #evil one#'s key will be #given from the start#.^",
                                                          /*german*/ "$bUnd der #Schlüssel des Bösen#, wird #von Anfang an, im Besitz des Helden# sein.^",
                                                          /*french*/ "$bAussi, la #clé du Malin# sera #possession même du héros#.^",
                                                                     {QM_PINK, QM_LBLUE}));
                                                       // /*spanish*/$bY obtendrás la llave del #señor del mal# desde el #inicio#.^

    hintTable[RHT_GANON_BK_VANILLA_HINT] = HintText(CustomMessage("$bAnd the #evil one#'s key will be kept in a big chest #inside its tower#.^",
                                                       /*german*/ "$bUnd der #Schlüssel des Bösen#, wird in der großen Truhe #im Teufelsturm# zu finden sein.^",
                                                       /*french*/ "$bAussi, la #clé du Malin# sera encoffrée #dans sa tour#.^",
                                                                  {QM_PINK, QM_LBLUE}));
                                                    // /*spanish*/$bY la llave del #señor del mal# aguardará en un gran cofre de #su torre#.^

    hintTable[RHT_GANON_BK_OWN_DUNGEON_HINT] = HintText(CustomMessage("$bAnd the #evil one#'s key will be hidden somewhere #inside its castle#.^",
                                                           /*german*/ "$bUnd der #Schlüssel des Bösen#, wird irgendwo #in Ganons Schloss# zu finden sein.^",
                                                           /*french*/ "$bAussi, la #clé du Malin# sera cachée #dans son vaste château#.^",
                                                                      {QM_PINK, QM_PINK}));
                                                        // /*spanish*/$bY la llave del #señor del mal# aguardará en #algún lugar de su castillo#.^

    hintTable[RHT_GANON_BK_OVERWORLD_HINT] = HintText(CustomMessage("$bAnd the #evil one#'s key will be hidden #outside of dungeons# in Hyrule.^",
                                                         /*german*/ "$bUnd der #Schlüssel des Bösen#, wird irgendwo #in Hyrule, außerhalb von Labyrinthen# zu finden sein.^",
                                                         /*french*/ "$bAussi, la #clé du Malin# se trouve #hors des donjons# d'Hyrule.^",
                                                                    {QM_PINK, QM_GREEN}));
                                                      // /*spanish*/$bY la llave del #señor del mal# aguardará #fuera de las mazmorras# de Hyrule.^

    hintTable[RHT_GANON_BK_ANY_DUNGEON_HINT] = HintText(CustomMessage("$bAnd the #evil one#'s key will be hidden #inside a dungeon# in Hyrule.^",
                                                           /*german*/ "$bUnd der #Schlüssel des Bösen#, wird irgendwo #in Hyrule, innerhalb eines Labyrinths# zu finden sein.^",
                                                           /*french*/ "$bAussi, la #clé du Malin# se trouve #dans un donjon# d'Hyrule.^",
                                                                      {QM_PINK, QM_PINK}));
                                                        // /*spanish*/$bY la llave del #señor del mal# aguardará #en una mazmorra# de Hyrule.^

    hintTable[RHT_GANON_BK_ANYWHERE_HINT] = HintText(CustomMessage("$bAnd the #evil one#'s key will be hidden somewhere&#in Hyrule#.^",
                                                        /*german*/ "$bUnd der #Schlüssel des Bösen#, wird irgendwo #in Hyrule# zu finden sein.^",
                                                        /*french*/ "$bAussi, la #clé du Malin# se trouve quelque part #dans Hyrule#.^",
                                                                   {QM_PINK, QM_BLUE}));
                                                     // /*spanish*/$bY la llave del #señor del mal# aguardará en #cualquier lugar de Hyrule#.^

    hintTable[RHT_GANON_BK_TRIFORCE_HINT] = HintText(CustomMessage("$bAnd the #evil one#'s key will be given to the Hero once the #Triforce## is completed.^",
                                                        /*german*/ "$bUnd der #Schlüssel des Bösen# wird verliehen, sobald das #Triforce# vervollständigt wurde.^",
                                                        /*french*/ "$bAussi, la #clé du Malin# se&révèlera une fois la #Triforce#&assemblée.^",
                                                                   {QM_PINK, QM_YELLOW}));
                                                     // /*spanish*/$bY el héroe recibirá la llave del #señor del mal# cuando haya completado la #Trifuerza#.^

    hintTable[RHT_GANON_BK_SKULLTULA_HINT] = HintText(CustomMessage("$bAnd the #evil one#'s key will be provided by the cursed rich man once #100 Gold Skulltula Tokens# are retrieved.^",
                                                         /*german*/ "",
                                                         /*french*/ "$bAussi, la #clé du Malin# sera&donnée par l'homme maudit une fois que #100 Symboles de Skulltula d'or# auront été trouvés.^",
                                                                    {QM_PINK, QM_YELLOW}));
                                                      // /*spanish*/$bY el rico maldito entregará la llave&del #señor de mal# tras obtener&100 símbolos de skulltula dorada#.^

    hintTable[RHT_LACS_VANILLA_HINT] = HintText(CustomMessage("$bAnd the #evil one#'s key will be provided by #Zelda# once the #Shadow and Spirit Medallions# are retrieved.^",
                                                   /*german*/ "$bUnd der #Schlüssel des Bösen# wird von #Zelda# verliehen, sobald #die Amulette des Schattens und der Geister# geborgen wurden.^",
                                                   /*french*/ "$bAussi, la #clé du Malin# sera fournie par #Zelda# une fois que les #Médaillons de l'Ombre et de l'Esprit# seront récupérés.^",
                                                              {QM_PINK, QM_YELLOW, QM_RED}));
                                                // /*spanish*/$bY #Zelda# entregará la llave del #señor del mal# tras obtener #el medallón de las sombras y del espíritu#.^

    hintTable[RHT_LACS_MEDALLIONS_HINT] = HintText(CustomMessage("$bAnd the #evil one#'s key will be provided by #Zelda# once #[[d]] Medallion|# is|s# are| retrieved.^",
                                                      /*german*/ "$bUnd der #Schlüssel des Bösen# wird von #Zelda# verliehen, sobald #[[d]] Amulett|# geborgen wurde|e# geborgen wurden|.^",
                                                      /*french*/ "$bAussi, la #clé du Malin# sera fournie par #Zelda# une fois |qu' #[[d]] Médaillon# aura été récupéré|que #[[d]] Médaillons# auront été récupérés|.^",
                                                                 {QM_PINK, QM_YELLOW, QM_RED}));
                                                   // /*spanish*/$bY #Zelda# entregará la llave&del #señor del mal# tras obtener #[[d]] |medallón|medallones|#.^  

    hintTable[RHT_LACS_STONES_HINT] = HintText(CustomMessage("$bAnd the #evil one#'s key will be provided by #Zelda# once #[[d]] Spiritual Stone|# is|s# are| retrieved.^",
                                                  /*german*/ "$bUnd der #Schlüssel des Bösen# wird von #Zelda# verliehen, sobald #[[d]] Heilige|r Stein# geborgen wurde| Steine# geborgen wurden|.^",
                                                  /*french*/ "$bAussi, la #clé du Malin# sera fournie par #Zelda# une fois |qu' #[[d]] Pierre Ancestrale# aura été&récupérée|que #[[d]] Pierres Ancestrales# auront été récupérées|.^",
                                                             {QM_PINK, QM_YELLOW, QM_BLUE}));
                                               // /*spanish*/$bY #Zelda# entregará la llave del #señor del mal# tras obtener #[[d]] piedra| espiritual|s espirituales|#.^

    hintTable[RHT_LACS_REWARDS_HINT] = HintText(CustomMessage("$bAnd the #evil one#'s key will be provided by #Zelda# once #[[d]]# #Spiritual Stone|# or #Medallion# is|s# and #Medallions# are| retrieved.^",
                                                   /*german*/ "$bUnd der #Schlüssel des Bösen# wird von #Zelda# verliehen, sobald #[[d]]# #Heilige|r Stein# oder #Amulett#&geborgen wurde| Steine# oder #Amulette#&geborgen wurden|.^",
                                                   /*french*/ "$bAussi, la #clé du Malin# sera fournie par #Zelda# une fois qu|' #[[d]]# #Pierre Ancestrale# ou #[[d]] Médaillon# sera récupéré|e&#[[d]]# #Pierres Ancestrales# et&#Médaillons# seront récupérés|.^",
                                                              {QM_PINK, QM_YELLOW, QM_YELLOW, QM_BLUE, QM_RED}));
                                                // /*spanish*/$bY #Zelda# entregará la llave del #señor del mal# tras obtener #[[d]]# piedra| espiritual o medallón|s espirituales o medallones|#.^

    hintTable[RHT_LACS_DUNGEONS_HINT] = HintText(CustomMessage("$bAnd the #evil one#'s key will be provided by #Zelda# once #[[d]] Dungeon|# is|s# are| conquered.^",
                                                    /*german*/ "$bUnd der #Schlüssel des Bösen# wird von #Zelda# verliehen, sobald #[[d]] Labyrinth|# abgeschlossen wurde|e# abgeschlossen wurden|.^",
                                                    /*french*/ "$bAussi, la #clé du Malin# sera fournie par #Zelda# une fois qu|' #[[d]] donjon #sera conquis|e #[[d]] donjons# seront conquis|.^",
                                                              {QM_PINK, QM_YELLOW, QM_PINK}));
                                                 // /*spanish*/$bY #Zelda# entregará la llave del #señor del mal# tras completar #[[d]] mazmorra||s|#.^

    hintTable[RHT_LACS_TOKENS_HINT] = HintText(CustomMessage("$bAnd the #evil one#'s key will be provided by #Zelda# once #[[d]] Gold Skulltula Token|# is|s# are| retrieved.^",
                                                  /*german*/ "$bUnd der #Schlüssel des Bösen# wird von #Zelda# verliehen, sobald #[[d]] Skulltula-Symbol|# gesammelt wurde|e# gesammelt wurden|.^",
                                                  /*french*/ "$bAussi, la #clé du Malin# sera fournie par #Zelda# une fois |qu' #[[d]] symbole de Skulltula d'or #sera récupuéré"
                                                             "|que &#[[d]] symboles de Skulltula d'or&#seront recupérés|.^",
                                                              {QM_PINK, QM_YELLOW, QM_YELLOW}));
                                                // /*spanish*/$bY #Zelda# entregará la llave del #señor del mal# tras obtener #[[d]] símbolo
                                                          // ||s| de skulltula dorada#.^

    /*--------------------------
    |     TRIAL HINT TEXT      |
    ---------------------------*/

    hintTable[RHT_SIX_TRIALS] = HintText(CustomMessage("They say that #Ganon's Tower# is protected by a powerful barrier.",
                                            /*german*/ "Man erzählt sich, daß der #Teufelsturm# sei von einer mächtigen Barriere geschützt sei.",
                                            /*french*/ "Selon moi, #la Tour de Ganon# est protégée par une puissante barrière", {QM_PINK}));
                                         // /*spanish*/Según dicen, la #torre de Ganon# está protegida por una poderosa barrera

    hintTable[RHT_ZERO_TRIALS] = HintText(CustomMessage("They say that Sheik dispelled the barrier around #Ganon's Tower#.",
                                             /*german*/ "Man erzählt sich, Shiek habe die Barriere um den #Teufelsturm# aufgelöst sei.",
                                             /*french*/ "Selon moi, Sheik a dissipé la barrière autour de #la Tour de Ganon#", {QM_YELLOW}));
                                          // /*spanish*/Según dicen, Sheik disipó la barrera alrededor de la #torre de Ganon#.

    hintTable[RHT_TRIAL_OFF] = HintText(CustomMessage("They say that #[[1]]# was dispelled by Sheik.",
                                           /*german*/ "Man erzählt sich, daß #[[1]]# sei von Shiek aufgelöst worden sei.",
                                           /*french*/ "Selon moi, #[[1]]# a été dissipée par Sheik.", {QM_YELLOW}));
                                        // /*spanish*/Según dicen, #[[1]]# se disipó gracias a Sheik.

    hintTable[RHT_TRIAL_ON] = HintText(CustomMessage("They say that #[[1]]# protects Ganons Tower.",
                                          /*german*/ "Man erzählt sich, daß #[[1]]# schütze den Teufelsturm sei.",
                                          /*french*/ "Selon moi, #[[1]]# protège la Tour de Ganon.", {QM_PINK}));
                                       // /*spanish*/Según dicen, #[[1]]# protege la torre de Ganon

    hintTable[RHT_LIGHT_TRIAL] = HintText(CustomMessage("the Light Trial",
                                             /*german*/ "",
                                             /*french*/ "l'épreuve de la Lumière"));
                                          // /*spanish*/la prueba de la luz

    hintTable[RHT_FOREST_TRIAL] = HintText(CustomMessage("the Forest Trial",
                                              /*german*/ "",
                                              /*french*/ "l'épreuve de la Forêt"));
                                           // /*spanish*/la prueba del bosque

    hintTable[RHT_FIRE_TRIAL] = HintText(CustomMessage("the Fire Trial",
                                            /*german*/ "",
                                            /*french*/ "l'épreuve du Feu"));
                                         // /*spanish*/la prueba del fuego

    hintTable[RHT_WATER_TRIAL] = HintText(CustomMessage("the Water Trial",
                                             /*german*/ "",
                                             /*french*/ "l'épreuve de l'Eau"));
                                          // /*spanish*/la prueba del agua

    hintTable[RHT_SPIRIT_TRIAL] = HintText(CustomMessage("the Spirit Trial",
                                              /*german*/ "",
                                              /*french*/ "l'épreuve de l'Esprit"));
                                           // /*spanish*/la prueba del espíritu

    hintTable[RHT_SHADOW_TRIAL] = HintText(CustomMessage("the Shadow Trial",
                                              /*german*/ "",
                                              /*french*/ "l'épreuve de l'Ombre"));
                                           // /*spanish*/la prueba de las sombras

    /*--------------------------
    |        ALTAR TEXT        |
    ---------------------------*/

    hintTable[RHT_CHILD_ALTAR_STONES] = HintText(CustomMessage("3 Spiritual Stone4s found in Hyrule...^$0#[[1]]#...^$1#[[2]]#...^$2#[[3]]#...^",
                                                    /*german*/ "Drei Heilige Steine, zu finden in Hyrule...$0#[[1]]#...^$1#[[2]]#...^$2#[[3]]#...^",
                                                    /*french*/ "Les trois Pierres Ancestrales cachées&dans Hyrule...$0#[[1]]#...^$1#[[2]]#...^$2#[[3]]#...^", 
                                                    {QM_GREEN, QM_RED, QM_BLUE}, {true, true, true}));
                                                // /*spanish*/ Tres piedras espirituales halladas por Hyrule...$0#[[1]]#...^$1#[[2]]#...^$2#[[3]]#...^

    hintTable[RHT_CHILD_ALTAR_TEXT_END_DOTOPEN] = HintText(CustomMessage("$oYe who may become a Hero...&The path to the future is open...",
                                                              /*german*/ "$oJener auf dem Weg des Helden...&Der Pfad zur Zukunft sei geöffnet...",
                                                              /*french*/ "$oÀ celui qui a quête de devenir&héros...&Le futur vous accueille béant..."));
                                                           // /*spanish*/$oPara aquel que se convierta en el héroe...&La puerta al futuro está a su disposición...

    hintTable[RHT_CHILD_ALTAR_TEXT_END_DOTSONGONLY] = HintText(CustomMessage("$cYe who may become a Hero...&Stand with the Ocarina and&play the Song of Time.",
                                                                  /*german*/ "$cJener auf dem Weg des Helden...&Nehme er seine Okarina zur Hand und&spiele hier die Hymne der Zeit.",
                                                                  /*french*/ "$cÀ celui qui a quête de devenir&héros...&Portez l'Ocarina et jouez&le chant du temps."));
                                                               // /*spanish*/$cPara aquel que se convierta en el héroe...&Tome la ocarina y&entone la Canción del Tiempo.
    
    hintTable[RHT_CHILD_ALTAR_TEXT_END_DOTCLOSED] = HintText(CustomMessage("$iYe who may become a Hero...&Offer the spiritual stones and&play the Song of Time.",
                                                                /*german*/ "$iJener mit den drei Heiligen Steinen&nehme seine Okarina zur Hand und&spiele hier die Hymne der Zeit.",
                                                                /*french*/ "$iÀ celui qui a quête de devenir&héros... Présentez les Pierres&Ancestrales et jouez&le chant du temps."));
                                                             // /*spanish*/$iPara aquel que se convierta en el héroe...&Tome las piedras espirituales y&entone la Canción del Tiempo.

    hintTable[RHT_ADULT_ALTAR_MEDALLIONS] = HintText(CustomMessage("An awakening voice from the Sacred Realm will call those destined to be Sages, who dwell in the #five temples#.^"
                                                                   "$8#[[1]]#...^$3#[[2]]#...^$4#[[3]]#...^$5#[[4]]#...^$6#[[5]]#...^$7#[[6]]#...^" ,
                                                        /*german*/ "Beherrscht das Böse die Welt, weilen&jene Weisen, die von der Stimme des Heiligen Reiches erweckt werden, noch&in den #fünf Tempeln#.^"
                                                                   "$8#[[1]]#...^$3#[[2]]#...^$4#[[3]]#...^$5#[[4]]#...^$6#[[5]]#...^$7#[[6]]#...^",
                                                        /*french*/ "Quand le mal aura triomphé, une voix du Saint Royaume appellera ceux cachés dans les #cinq temples#, destinés^à être Sages.^"
                                                                   "$8#[[1]]#...^$3#[[2]]#...^$4#[[3]]#...^$5#[[4]]#...^$6#[[5]]#...^$7#[[6]]#...^",
                                                                   { QM_RED, QM_YELLOW, QM_GREEN, QM_RED, QM_BLUE, QM_YELLOW, QM_PINK}, {true, true, true, true, true, true}, TEXTBOX_TYPE_BLUE));
                                                     // /*spanish*/Cuando el mal lo impregne todo, desde el Reino Sagrado surgirá una voz que hará despertar a los sabios que moran en los #cinco templos#.^
                                                                // $8#[[1]]#...^$3#[[2]]#...^$4#[[3]]#...^$5#[[4]]#...^$6#[[5]]#...^$7#[[6]]#...^

    hintTable[RHT_ADULT_ALTAR_TEXT_END] = HintText(CustomMessage("$kTogether with the Hero of Time, the awakened ones will return the light of peace to the world...",
                                                    /*german*/ "$kZusammen mit dem Auserwählten wer-den diese ihre Kräfte einsetzen, um der Welt den Frieden wiederzugeben.",
                                                    /*french*/ "$kEnsemble avec le Héros du Temps, ces Sages emprisonneront le mal et réinstaureront la lumière de paix dans le monde..."));
                                                    // /*spanish*/Con el Héroe del Tiempo, aquellos&que despierten detendrán el mal y&volverán al mundo de luz la paz...

    hintTable[RHT_YOUR_POCKET] = HintText(CustomMessage("your pocket",
                                             /*german*/ "",
                                             /*french*/ "tes poches"));
                                          // /*spanish*/tu bolsillo

    /*--------------------------
    |     Static Item Hints     |
    ---------------------------*/

    hintTable[RHT_GANONDORF_HINT_LA_ONLY] = HintText(CustomMessage("Ha ha ha... You'll never beat me by reflecting my lightning bolts and unleashing the arrows from #[[1]]#!",
                                                        /*german*/ "",
                                                        /*french*/ "Ha ha ha... Pauvre fou! Tu ne pourras jamais me vaincre sans les flèches que j'ai cachées dans #[[1]]#!",
                                                                   {QM_RED}));
                                                     // /*spanish*/Ja, ja, ja... Nunca me derrotarás reflejando mis esferas de energía y desplegando la flecha de luz de #[[1]]#!

    hintTable[RHT_GANONDORF_HINT_MS_ONLY] = HintText(CustomMessage("Ha ha ha... You'll never defeat me, drop a castle on me and finish me off with the sacred blade from #[[2]]#!",
                                                        /*german*/ "",
                                                        /*french*/ "",
                                                                   {QM_RED}));

    hintTable[RHT_GANONDORF_HINT_LA_AND_MS] = HintText(CustomMessage("Ha ha ha... You'll never beat me by reflecting my lightning bolts and unleashing the arrows from #[[1]]#!"
                                                                     "^And even if you do, you'll never find the legendary blade hidden in #[[2]]#!",
                                                          /*german*/ "",
                                                          /*french*/ "Ha ha ha... Pauvre fou! Tu ne pourras jamais me vaincre sans les flèches que j'ai cachées dans #[[1]]#!"
                                                                     "^Et même si tu les trouves, tu ne touveras jamais l'épée de légende cachée dans #[[2]]#!",
                                                                     {QM_RED, QM_RED}));
                                                       // /*spanish*/Ja, ja, ja... Nunca me derrotarás reflejando mis esferas de energía y desplegando la flecha de luz de #[[1]]#!
                                                                  // ^E incluso si lo haces, nunca encontrarás la espada legendaria escondida en #[[2]]#!

    hintTable[RHT_SHEIK_HINT_LA_ONLY] = HintText(CustomMessage("I overheard Ganondorf say that he misplaced the #Light Arrows# in #[[1]]#.",
                                                    /*german*/ "",
                                                    /*french*/ "J'ai entendu dire que Ganondorf aurait caché les #Flèches de Lumière# dans #[[1]]#.",
                                                               {QM_YELLOW, QM_RED}));

    hintTable[RHT_DAMPE_DIARY] = HintText(CustomMessage("Whoever reads this, please enter #[[1]]#. I will let you have my #stretching, shrinking keepsake#.^I'm waiting for you.&--Dampé",
                                             /*german*/ "Wer immer dies liest, der möge folgenden Ort aufsuchen: #[[1]]#. Ihm gebe ich meinen langen, kurzen Schatz.^Ich warte!&Boris", //RANDOTODO color in whatever refers to the hookshot
                                             /*french*/ "Toi qui lit ce journal, rends-toi dans #[[1]]#. Et peut-être auras-tu droit à mon précieux #trésor#.^Je t'attends...&--Igor",
                                                        {QM_RED, QM_RED}));

    hintTable[RHT_GREG_HINT] = HintText(CustomMessage("By the way, if you're interested, I saw the shiniest #Green Rupee# somewhere in #[[1]]#.^It's said to have #mysterious powers#...^But then, it could just be another regular rupee.&Oh well.",
                                           /*german*/ "",
                                           /*french*/ "Au fait, si ça t'intéresse, j'ai aperçu le plus éclatant des #Rubis Verts# quelque part à #[[1]]#. On dit qu'il possède des pouvoirs mystérieux... Mais bon, ça pourrait juste être un autre rubis ordinaire.",//RANDOTODO color in mysterious powers
                                                      {QM_GREEN, QM_RED, QM_RED}));

    hintTable[RHT_SARIA_HINT] = HintText(CustomMessage("Did you feel the #surge of magic# recently? A mysterious bird told me it came from #[[1]]#.^You should check that place out, @!",
                                            /*german*/ "",
                                            /*french*/ "As-tu récemment ressenti une vague de #puissance magique#? Un mystérieux hibou m'a dit  qu'elle provenait du #[[1]]#. Tu devrais aller y jeter un coup d'oeil, @!",
                                                       {QM_GREEN, QM_RED}));

    hintTable[RHT_FISHING_POLE_HINT] = HintText(CustomMessage("^If I remember correctly, I lost it somewhere in #[[1]]#...&Let me know if you find it!",
                                                              {QM_RED}));

    /*--------------------------
    |    Static Entrance Hint   |
    ---------------------------*/

    hintTable[RHT_WARP_SONG] = HintText(CustomMessage("Warp to&#[[1]]#?&" + TWO_WAY_CHOICE() + "#OK&No#",
                                           /*german*/ "Zu&#[[1]]}?&" + TWO_WAY_CHOICE() + "#OK&No#",
                                           /*french*/ "Se téléporter vers&#[[1]]#?&" + TWO_WAY_CHOICE() + "#OK!&Non#",
                                                      {QM_RED, QM_GREEN}));

    /*--------------------------
    |   STATIC LOCATION HINTS   |
    ---------------------------*/

    hintTable[RHT_MEDIGORON_HINT] = HintText(CustomMessage("How about buying #[[1]]# for #200 Rupees#?&" + TWO_WAY_CHOICE() + "#Buy&Don't buy#",
                                                /*german*/ "Möchtest du #[[1]]# für #200 Rubine# kaufen?&" + TWO_WAY_CHOICE() + "#Klar!&Nie im Leben!#",
                                                /*french*/ "Veux-tu acheter #[[1]]# pour #200 rubis#?&" + TWO_WAY_CHOICE() + "#Acheter&Ne pas acheter#",
                                                           {QM_GREEN, QM_YELLOW, QM_GREEN}));
                                            /*spanish*/ // ¿Me compras #[[1]]# por #200 rupias#?&" + TWO_WAY_CHOICE() + "#Comprar&No comprar#

    hintTable[RHT_CARPET_SALESMAN_DIALOG_FIRST] = HintText(CustomMessage("Welcome!^I am selling stuff, strange and rare, from all over the world to everybody. Today's special is...^",
                                                              /*german*/ "Sei gegrüßt!^Ich verkaufe allerlei Kuriorisäten.&Stets sonderliche und seltene Ware&aus "
                                                                         "aller Welt für jedermann.&Das heutige Angebot bleibt...^#",
                                                              /*french*/ "Bienvenue!^Je vends des objets rares et merveilleux du&monde entier. En spécial aujourd'hui...^"));
                                                          /*spanish*/ // ¡Acércate!^Vendo productos extraños y difíciles de&encontrar... De todo el mundo a todo el&mundo. La oferta de hoy es...^#¡

    hintTable[RHT_CARPET_SALESMAN_DIALOG_MYSTERIOUS] = HintText(CustomMessage("Terrifying! I won't tell you what it is until I see the #money#...^How about #200 Rupees#?&&" +
                                                                              TWO_WAY_CHOICE() + "#Buy&Don't buy#",
                                                                   /*german*/ "Furchterregend oder? Ich erzähle Euch mehr, wenn ich #Geld# sehe...^Wie wär's mit #200 Rubinen#?&&" +
                                                                              TWO_WAY_CHOICE() + "#Aber sicher!&Ich bin weg!#",
                                                                   /*french*/ "Un concentré de puissance! Mais montre tes #rubis# avant que je te dise ce que c'est...^Disons #200 "
                                                                              "rubis#?&&" + TWO_WAY_CHOICE() + "#Acheter&Ne pas acheter#",
                                                                              {QM_RED, QM_YELLOW, QM_GREEN}));
                                                               /*spanish*/ // ¡Terrorífico! No te revelaré su nombre hasta que vea el #dinero#...^#200 rupias#, ¿qué te parece?&&" +
                                                                           // TWO_WAY_CHOICE() + "#Comprar&No comprar#

    hintTable[RHT_CARPET_SALESMAN_DIALOG_HINTED] = HintText(CustomMessage("#[[1]]!# It's real, I promise! A lonely man such as myself wouldn't #lie# to you, hmm?^"
                                                                          "How about #200 Rupees#?&&" + TWO_WAY_CHOICE() + "#Buy&Don't buy#",
                                                              /*german*/ "#[[1]]#! Ich kann versichern es ist ein aufrichtiges Angebot!^Ein einsamer Mann wie ich würde dich doch "
                                                                         "nicht #anlügen#, oder?^Wie wär's mit #200 Rubinen#?&&" + TWO_WAY_CHOICE() + "#Aber sicher!&Ich bin weg!#",
                                                              /*french*/ "#[[1]]!# C'est vrai! J'te jure! Un gars comme moi ne te #mentirai# pas tu ne crois pas?^Disons #200 "
                                                                         "rubis#?&&" + TWO_WAY_CHOICE() + "#Acheter&Ne pas acheter#",
                                                                         {QM_GREEN, QM_YELLOW, QM_GREEN}));

    hintTable[RHT_BEAN_SALESMAN_HINT] = HintText(CustomMessage("I tried to be a #magic bean#&salesman, but it turns out my&marketing skills weren't worth&"
                                                               "beans!^Anyway, want to buy #[[1]]# for #60 Rupees#?&" + TWO_WAY_CHOICE() + "#Yes&No#",
                                                    /*german*/ "Möchten Sie #[[1]]# für #60 Rubine#?&" + TWO_WAY_CHOICE() + "#Ja&Nein#",
                                                    /*french*/ "J'ai essayé d'être un vendeur&de #haricots magiques#, mais&j'étais mauvais au niveau du&marketing et ça "
                                                               "me courait sur&le haricot...^Enfin bref, ça te dirait de m'acheter #[[1]]# pour #60 Rubis#?&" + TWO_WAY_CHOICE() + "#Oui&Non#",
                                                               {QM_RED, QM_GREEN, QM_YELLOW, QM_GREEN}));

    hintTable[RHT_GRANNY_HINT] = HintText(CustomMessage("#[[1]]#! How about #100 Rupees#?&" + TWO_WAY_CHOICE() + "#Buy&Don't buy#",
                                            /*german*/ "#[[1]]#! Sagen wir #100 Rubine#!&" + TWO_WAY_CHOICE() + "#Gerne!&Auf keinen Fall!#",
                                            /*french*/ "#[[1]]#! Que dis-tu de #100 rubis#?&" + TWO_WAY_CHOICE() + "#Acheter&Ne pas acheter#",
                                                       {QM_GREEN, QM_YELLOW, QM_GREEN}, {true}));
                                         // /*spanish*/#[[1]]#. Vendo por #100 rupias#.&" + TWO_WAY_CHOICE() + "#Comprar&No comprar#

    hintTable[RHT_HBA_HINT_SIGN] = HintText(CustomMessage("#Horseback Archery# Range Prizes:&1000: #[[1]]#&1500: #[[2]]#^@'s Record: #\x1E\x00#",
                                                          {QM_RED, QM_GREEN, QM_GREEN, QM_GREEN}));

    hintTable[RHT_HBA_HINT_NOT_ON_HORSE] = HintText(CustomMessage("Hey, rookie!&Come back on your #horse#&and take on the&#Horseback Archery# challenge!^"
                                                                  "Impress me with a high score of 1000&to win a #[[1]]#&or score 1500 for my&#[[2]]#!",
                                                                  {QM_RED, QM_RED, QM_GREEN, QM_GREEN}));

    hintTable[RHT_HBA_HINT_INITIAL] = HintText(CustomMessage("Hey, rookie!&Want to take on the&#Horseback Archery# challenge?^"
                                                             "Impress me with a high score of 1000&to win a #[[1]]#&or score 1500 for my&#[[2]]#!\x0B",
                                                             {QM_RED, QM_GREEN, QM_GREEN}));

    hintTable[RHT_HBA_HINT_HAVE_1000] = HintText(CustomMessage("Hey, newcomer!&Want to take on the&#Horseback Archery# challenge?^"
                                                               "Prove yourself to be a horsemaster&by scoring 1500 points to win &my #[[1]]#!\x0B",
                                                               {QM_RED, QM_GREEN}));

    hintTable[RHT_MALON_HINT_HOW_IS_EPONA] = HintText(CustomMessage("@! You should come back &with Epona and try to beat my time&on the #Obsticle Course#!^"
                                                                    "If you beat my time, I'll give you&my favourite #cow# Elsie and&her toy #[[1]]#!",
                                                                    {QM_RED, QM_BLUE, QM_GREEN}));

    hintTable[RHT_MALON_HINT_OBSTICLE_COURSE] = HintText(CustomMessage("How about trying the #Obsticle Course?#&If you beat my time I'll let you keep&my favourite #cow# Elsie and&her toy #[[1]]#!^"
                                                                       "Challenge the #Obsticle Course?#&\x1B&#Let's go&No thanks#",
                                                                       {QM_RED, QM_BLUE, QM_GREEN, QM_RED, QM_GREEN}));

    hintTable[RHT_MALON_HINT_TURNING_EVIL] = HintText(CustomMessage("@? Is that you? ^If I ran the ranch, I'd build an &#Obsticle Course#, and whoever gets&the best time would win a #cow#!^"
                                                                    "Elsie loves sharing her #[[1]]#&with new people, It'll be fun!^...But Ingo won't let me...",
                                                                    {QM_RED, QM_BLUE, QM_GREEN}));

    hintTable[RHT_MALON_HINT_INGO_TEMPTED] = HintText(CustomMessage("@! You should come back in&the morning and try to beat my time&on the #Obsticle Course#!^"
                                                                    "If you beat my time, I'll give you&my favourite #cow# Elsie and&her toy #[[1]]#!",
                                                                    {QM_RED, QM_BLUE, QM_GREEN}));

    hintTable[RHT_CHICKENS_HINT] = HintText(CustomMessage("You! Please!&Bring my Cucco's back to my pen!&I'll give you my #[[1]]#!",
                                                          {QM_GREEN}));

    hintTable[RHT_BIG_POES_HINT] = HintText(CustomMessage("You have #\x1E\x01 Poe Points#!&Reach 1000 and you'll get a&#[[1]]#!",
                                                          {QM_YELLOW, QM_GREEN}));

    hintTable[RHT_BIGGORON_HINT] = HintText(CustomMessage("Arrrrrre you here to claim my finest&#[[1]]#?&Shoooooow me your #Claim Check#.",
                                                          {QM_GREEN, QM_RED}));

    hintTable[RHT_FROGS_HINT] = HintText(CustomMessage("Some frogs holding #[[1]]# are looking at you from underwater...",
                                            /*german*/ "Unter Wasser gibt es Frösche, die #[[1]]# bei sich haben und Dich neugierig beobachten...",
                                            /*french*/ "Des grenouilles se trouvant sous l'eau vous fixent attentivement, tenant fermement #[[1]]#.",
                                                       {QM_GREEN}));

    hintTable[RHT_SKULLS_HINT] = HintText(CustomMessage("Yeaaarrgh! I'm cursed!!^Please save me by destroying&#[[d]] Spiders of the Curse#&and I will give you my&#[[1]]#!",
                                             /*german*/ "Yeaaarrgh! Ich bin verflucht!^Bitte rette mich, indem du #[[d]] Skulltulas#&zerstörst und ich werde dir dafür&#[[1]]# geben!",
                                             /*french*/ "Yeaaarrgh! Je suis maudit!^Détruit encore #[[d]] Araignées de&la Malédiction# et j'aurai quelque&chose à te donner!&#([[1]])#",
                                                        {QM_YELLOW, QM_GREEN}));

    /*--------------------------
    |      GANON LINE TEXT     |
    ---------------------------*/

    hintTable[RHT_GANON_JOKE01] = HintText(CustomMessage("Oh! It's @.&I was expecting someone called Sheik.&Do you know what happened to them?",
                                              /*german*/ "",
                                              /*french*/ "Ah, c'est @.&J'attendais un certain Sheik.&Tu sais ce qui lui est arrivé?"));
                                           // /*spanish*/¡Oh! Pero si es @.&Estaba esperando a alguien llamado Sheik. ¿Sabes qué puede haberle pasado?

    hintTable[RHT_GANON_JOKE02] = HintText(CustomMessage("I knew I shouldn't have put the key on the other side of my door.",
                                              /*german*/ "",
                                              /*french*/ "J'aurais dû garder la clé ici. Hélas..."));
                                           // /*spanish*/Sabía que no tendría que haber dejado la llave al otro lado de la puerta.

    hintTable[RHT_GANON_JOKE03] = HintText(CustomMessage("Looks like it's time for a round of tennis.",
                                              /*german*/ "",
                                              /*french*/ "C'est l'heure de jouer au tennis."));
                                           // /*spanish*/Parece que es hora de una pachanga de tenis.

    hintTable[RHT_GANON_JOKE04] = HintText(CustomMessage("You'll never deflect my bolts of energy with your sword, then shoot me with those Light Arrows you happen to have.",
                                              /*german*/ "",
                                              /*french*/ "Ne perds pas ton temps à frapper mes éclairs d'énergie avec ton épée et me tirer avec tes flèches de Lumière!"));
                                           // /*spanish*/Nunca reflejarás mis esferas de energía con tu espada, para después dispararme con las flechas de luz que tendrás.

    hintTable[RHT_GANON_JOKE05] = HintText(CustomMessage("Why did I leave my trident back in the desert?",
                                              /*german*/ "",
                                              /*french*/ "Sale bêtise... Et j'ai oublié mon trident dans le désert!"));
                                           // /*spanish*/Santa Hylia... ¿Por qué me habré dejado el tridente en el desierto?

    hintTable[RHT_GANON_JOKE06] = HintText(CustomMessage("Zelda is probably going to do something stupid, like send you back to your own timeline.^So this is "
                                                         "quite meaningless. Do you really want to save this moron?",
                                              /*german*/ "",
                                              /*french*/ "Même si je suis vaincu... Zelda te renverra dans ton ère, et je reviendrai conquérir!^Telle est la "
                                                         "prophécie d'Hyrule Historia!"));
                                           // /*spanish*/Seguro que Zelda trata de hacer alguna tontería, como enviarte de vuelta a tu línea temporal.^No tiene 
                                                     // ningún sentido alguno. ¿De verdad quieres salvar a esa tonta?

    hintTable[RHT_GANON_JOKE07] = HintText(CustomMessage("What about Zelda makes you think&she'd be a better ruler than I?^I saved Lon Lon Ranch,&fed the "
                                                         "hungry,&and my castle floats.",
                                              /*german*/ "",
                                              /*french*/ "Zelda ne sera jamais un meilleur monarque que moi!^J'ai un château volant, mes sujets sont des belles "
                                                         "amazones... et mes Moblins sont clairement plus puissants que jamais!"));
                                           // /*spanish*/¿Qué te hace pensar que Zelda gobierna mejor que yo?^Yo he salvado el Rancho Lon Lon,&he alimentado a 
                                                      // los hambrientos&y hasta hago que mi castillo flote.

    hintTable[RHT_GANON_JOKE08] = HintText(CustomMessage("I've learned this spell,&it's really neat,&I'll keep it later&for your treat!",
                                              /*german*/ "",
                                              /*french*/ "Gamin, ton destin achève,&sous mon sort tu périras!&Cette partie ne fut pas brève,&et cette mort, tu subiras!"));
                                           // /*spanish*/Veamos ahora que harás,&la batalla ha de comenzar,&te enviaré de una vez al más allá,&¿listo para 
                                                      // afrontar la verdad?

    hintTable[RHT_GANON_JOKE09] = HintText(CustomMessage("Many tricks are up my sleeve,&to save yourself&you'd better leave!",
                                              /*german*/ "",
                                              /*french*/ "Sale petit garnement,&tu fais erreur!&C'est maintenant que marque&ta dernière heure!"));
                                           // /*spanish*/¿No osarás a mí enfrentarte?&Rimas aparte,&¡voy a matarte!

    hintTable[RHT_GANON_JOKE10] = HintText(CustomMessage("After what you did to Koholint Island, how can you call me the bad guy?",
                                              /*german*/ "",
                                              /*french*/ "J'admire ce que tu as fait à l'Île Koholint... Toi et moi, nous devrions faire équipe!"));
                                           // /*spanish*/Después de lo que le hiciste a la Isla Koholint, ¿cómo te atreves a llamarme malvado?

    hintTable[RHT_GANON_JOKE10] = HintText(CustomMessage("Today, let's begin down&'The Hero is Defeated' timeline.",
                                              /*german*/ "",
                                              /*french*/ "Si tu me vaincs, Hyrule sera englouti... mais si tu meurs, on aura A Link to the Past, le meilleur opus "
                                                         "de la série!"));
                                           // /*spanish*/Hoy daremos lugar a la línea temporal del Héroe Derrotado.&¡Prepárate para el culmen de esta saga!
}

int32_t StonesRequiredBySettings() {
    auto ctx = Rando::Context::GetInstance();
    int32_t stones = 0;
    if (ctx->GetOption(RSK_RAINBOW_BRIDGE).Is(RO_BRIDGE_STONES)) {
        stones = std::max<int32_t>({ stones, (int32_t)ctx->GetOption(RSK_RAINBOW_BRIDGE_STONE_COUNT).Value<uint8_t>() });
    }
    if (ctx->GetOption(RSK_RAINBOW_BRIDGE).Is(RO_BRIDGE_DUNGEON_REWARDS)) {
        stones = std::max<int32_t>({ stones, (int32_t)ctx->GetOption(RSK_RAINBOW_BRIDGE_REWARD_COUNT).Value<uint8_t>() - 6 });
    }
    if ((ctx->GetOption(RSK_RAINBOW_BRIDGE).Is(RO_BRIDGE_DUNGEONS)) && (ctx->GetOption(RSK_SHUFFLE_DUNGEON_REWARDS).Is(RO_DUNGEON_REWARDS_END_OF_DUNGEON))) {
        stones = std::max<int32_t>({ stones, (int32_t)ctx->GetOption(RSK_RAINBOW_BRIDGE_DUNGEON_COUNT).Value<uint8_t>() - 6 });
    }
    if (ctx->GetOption(RSK_GANONS_BOSS_KEY).Is(RO_GANON_BOSS_KEY_LACS_STONES)) {
        stones = std::max<int32_t>({ stones, (int32_t)ctx->GetOption(RSK_LACS_STONE_COUNT).Value<uint8_t>() });
    }
    if (ctx->GetOption(RSK_GANONS_BOSS_KEY).Is(RO_GANON_BOSS_KEY_LACS_STONES)) {
        stones = std::max<int32_t>({ stones, (int32_t)ctx->GetOption(RSK_LACS_REWARD_COUNT).Value<uint8_t>() - 6 });
    }
    if (ctx->GetOption(RSK_GANONS_BOSS_KEY).Is(RO_GANON_BOSS_KEY_LACS_DUNGEONS)) {
        stones = std::max<int32_t>({ stones, (int32_t)ctx->GetOption(RSK_LACS_DUNGEON_COUNT).Value<uint8_t>() - 6 });
    }
    return stones;
}

int32_t MedallionsRequiredBySettings() {
    auto ctx = Rando::Context::GetInstance();
    int32_t medallions = 0;
    if (ctx->GetOption(RSK_RAINBOW_BRIDGE).Is(RO_BRIDGE_MEDALLIONS)) {
        medallions = std::max<int32_t>({ medallions, (int32_t)ctx->GetOption(RSK_RAINBOW_BRIDGE_MEDALLION_COUNT).Value<uint8_t>() });
    }
    if (ctx->GetOption(RSK_RAINBOW_BRIDGE).Is(RO_BRIDGE_DUNGEON_REWARDS)) {
        medallions = std::max<int32_t>({ medallions, (int32_t)ctx->GetOption(RSK_RAINBOW_BRIDGE_REWARD_COUNT).Value<uint8_t>() - 3 });
    }
    if ((ctx->GetOption(RSK_RAINBOW_BRIDGE).Is(RO_BRIDGE_DUNGEONS)) && (ctx->GetOption(RSK_SHUFFLE_DUNGEON_REWARDS).Is(RO_DUNGEON_REWARDS_END_OF_DUNGEON))) {
        medallions = std::max<int32_t>({ medallions, (int32_t)ctx->GetOption(RSK_RAINBOW_BRIDGE_DUNGEON_COUNT).Value<uint8_t>() - 3 });
    }
    if (ctx->GetOption(RSK_GANONS_BOSS_KEY).Is(RO_GANON_BOSS_KEY_LACS_MEDALLIONS)) {
        medallions = std::max<int32_t>({ medallions, (int32_t)ctx->GetOption(RSK_LACS_MEDALLION_COUNT).Value<uint8_t>() });
    }
    if (ctx->GetOption(RSK_GANONS_BOSS_KEY).Is(RO_GANON_BOSS_KEY_LACS_REWARDS)) {
        medallions = std::max<int32_t>({ medallions, (int32_t)ctx->GetOption(RSK_LACS_REWARD_COUNT).Value<uint8_t>() - 3 });
    }
    if (ctx->GetOption(RSK_GANONS_BOSS_KEY).Is(RO_GANON_BOSS_KEY_LACS_DUNGEONS)) {
        medallions = std::max<int32_t>({ medallions, (int32_t)ctx->GetOption(RSK_LACS_DUNGEON_COUNT).Value<uint8_t>() - 3 });
    }
    return medallions;
}

int32_t TokensRequiredBySettings() {
    auto ctx = Rando::Context::GetInstance();
    int32_t tokens = 0;
    if (ctx->GetOption(RSK_RAINBOW_BRIDGE).Is(RO_BRIDGE_TOKENS)) {
        tokens = std::max<int32_t>({ tokens, (int32_t)ctx->GetOption(RSK_RAINBOW_BRIDGE_TOKEN_COUNT).Value<uint8_t>() });
    }
    if (ctx->GetOption(RSK_GANONS_BOSS_KEY).Is(RO_GANON_BOSS_KEY_LACS_TOKENS)) {
        tokens = std::max<int32_t>({ tokens, (int32_t)ctx->GetOption(RSK_LACS_TOKEN_COUNT).Value<uint8_t>() });
    }
    return tokens;
}

std::vector<ConditionalAlwaysHint> conditionalAlwaysHints = {
    std::make_pair(RC_MARKET_10_BIG_POES,
                   []() {
                       auto ctx = Rando::Context::GetInstance();
                       return ctx->GetOption(RSK_BIG_POE_COUNT).Value<uint8_t>() >= 3 && !ctx->GetOption(RSK_BIG_POES_HINT);
                   }), // Remember, the option's value being 3 means 4 are required
    std::make_pair(RC_DEKU_THEATER_MASK_OF_TRUTH,
                   []() {
                       auto ctx = Rando::Context::GetInstance();
                       return !ctx->GetOption(RSK_COMPLETE_MASK_QUEST);
                   }),
    std::make_pair(RC_SONG_FROM_OCARINA_OF_TIME, []() { return StonesRequiredBySettings() < 2; }),
    std::make_pair(RC_HF_OCARINA_OF_TIME_ITEM, []() { return StonesRequiredBySettings() < 2; }),
    std::make_pair(RC_SHEIK_IN_KAKARIKO, []() { return MedallionsRequiredBySettings() < 5; }),
    std::make_pair(RC_DMT_TRADE_CLAIM_CHECK,
                   []() {
                       auto ctx = Rando::Context::GetInstance();
                       return !ctx->GetOption(RSK_BIGGORON_HINT);
                   }),
    std::make_pair(RC_KAK_30_GOLD_SKULLTULA_REWARD,
                   []() {
                       auto ctx = Rando::Context::GetInstance();
                       return TokensRequiredBySettings() < 30 && !ctx->GetOption(RSK_KAK_30_SKULLS_HINT);
                   }),
    std::make_pair(RC_KAK_40_GOLD_SKULLTULA_REWARD,
                   []() {
                       auto ctx = Rando::Context::GetInstance();
                       return TokensRequiredBySettings() < 40 && !ctx->GetOption(RSK_KAK_40_SKULLS_HINT);
                   }),
    std::make_pair(RC_KAK_50_GOLD_SKULLTULA_REWARD,
                   []() {
                       auto ctx = Rando::Context::GetInstance();
                       return TokensRequiredBySettings() < 50 && !ctx->GetOption(RSK_KAK_50_SKULLS_HINT);
                   }),
    std::make_pair(RC_ZR_FROGS_OCARINA_GAME,
                   []() {
                       auto ctx = Rando::Context::GetInstance();
                       return !ctx->GetOption(RSK_FROGS_HINT);
                   }),
    std::make_pair(RC_KF_LINKS_HOUSE_COW,
                   []() {
                       auto ctx = Rando::Context::GetInstance();
                       return !ctx->GetOption(RSK_MALON_HINT);
                   }),
    std::make_pair(RC_KAK_100_GOLD_SKULLTULA_REWARD,
                   []() {
                       auto ctx = Rando::Context::GetInstance();
                       return !ctx->GetOption(RSK_KAK_100_SKULLS_HINT);
                   }),
};

const HintText& GetHintText(const RandomizerHintTextKey hintKey) {
    return hintTable[hintKey];
}
