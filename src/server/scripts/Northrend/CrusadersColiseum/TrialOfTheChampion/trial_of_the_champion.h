/*
 * Copyright (C) 2008-2011 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DEF_TOC_H
#define DEF_TOC_H

enum eData
{
    BOSS_GRAND_CHAMPIONS,
    BOSS_ARGENT_CHALLENGE_E,
    BOSS_ARGENT_CHALLENGE_P,
    BOSS_BLACK_KNIGHT,
    DATA_TEAM,
    DATA_MOVEMENT_DONE,
    DATA_LESSER_CHAMPIONS_DEFEATED,
    DATA_START,
    DATA_IN_POSITION,
    DATA_ARGENT_SOLDIER_DEFEATED,
    DATA_CHAMPION_DEFEATED,

    DATA_GRAND_CHAMPION_1,
    DATA_GRAND_CHAMPION_2,
    DATA_GRAND_CHAMPION_3
};

enum Data64
{
    DATA_ANNOUNCER,
    DATA_MAIN_GATE,
};

enum achievementCriterias
{
    CRITERIA_CHAMPION_JACOB     = 12310,
    CRITERIA_CHAMPION_LANA      = 12311,
    CRITERIA_CHAMPION_COLOSOS   = 12312,
    CRITERIA_CHAMPION_AMBROSE   = 12313,
    CRITERIA_CHAMPION_JAELYNE   = 12314,

    CRITERIA_CHAMPION_MOKRA     = 12318,
    CRITERIA_CHAMPION_VISCERI   = 12319,
    CRITERIA_CHAMPION_RUNOK     = 12320,
    CRITERIA_CHAMPION_ERESSEA   = 12321,
    CRITERIA_CHAMPION_ZULTORE   = 12322,

    CRITERIA_MEMORIE_HOGGER     = 11863,
    CRITERIA_MEMORIE_VANCLEEF   = 11904,
    CRITERIA_MEMORIE_MUTANUS    = 11905,
    CRITERIA_MEMORIE_HEROD      = 11906,
    CRITERIA_MEMORIE_LUCIFROM   = 11907,
    CRITERIA_MEMORIE_THUNDERAAN = 11908,
    CRITERIA_MEMORIE_CHROMAGGUS = 11909,
    CRITERIA_MEMORIE_HAKKAR     = 11910,
    CRITERIA_MEMORIE_VEKNILASH  = 11911,
    CRITERIA_MEMORIE_KALITHRESH = 11912,
    CRITERIA_MEMORIE_MALCHEZAAR = 11913,
    CRITERIA_MEMORIE_GRUUL      = 11914,
    CRITERIA_MEMORIE_VASHJ      = 11915,
    CRITERIA_MEMORIE_ARCHIMONDE = 11916,
    CRITERIA_MEMORIE_ILLIDAN    = 11917,
    CRITERIA_MEMORIE_DELRISSA   = 11918,
    CRITERIA_MEMORIE_MURU       = 11919,
    CRITERIA_MEMORIE_INGVAR     = 11920,
    CRITERIA_MEMORIE_CYANIGOSA  = 11921,
    CRITERIA_MEMORIE_ECK        = 11922,
    CRITERIA_MEMORIE_ONYXIA     = 11923,
    CRITERIA_MEMORIE_HEIGAN     = 11924,
    CRITERIA_MEMORIE_IGNIS      = 11925,
    CRITERIA_MEMORIE_VEZAX      = 11926,
    CRITERIA_MEMORIE_ALGALON    = 11927,


    SPELL_ACHIEVEMENT_CHAMPIONS = 68572,
    SPELL_ACHIEVEMENT_PALETRESS = 68574,
    SPELL_ACHIEVEMENT_MEMORIES  = 68206,
    SPELL_ACHIEVEMENT_EADRIC    = 68574,
    SPELL_ACHIEVEMENT_BLACK_KNIGHT = 68663,
};

enum eNpcs
{
    // Horde Champions
    NPC_MOKRA                   = 35572,
    NPC_MOUNTED_MOKRA           = 355720,
    NPC_ERESSEA                 = 35569,
    NPC_MOUNTED_ERESSEA         = 355690,
    NPC_RUNOK                   = 35571,
    NPC_MOUNTED_RUNOK           = 355710,
    NPC_ZULTORE                 = 35570,
    NPC_MOUNTED_ZULTORE         = 355700,
    NPC_VISCERI                 = 35617,
    NPC_MOUNTED_VISCERI         = 356170,

    // Alliance Champions
    NPC_JACOB                   = 34705,
    NPC_MOUNTED_JACOB           = 347050,
    NPC_AMBROSE                 = 34702,
    NPC_MOUNTED_AMBROSE         = 347020,
    NPC_COLOSOS                 = 34701,
    NPC_MOUNTED_COLOSOS         = 347010,
    NPC_JAELYNE                 = 34657,
    NPC_MOUNTED_JAELYNE         = 346570,
    NPC_LANA                    = 34703,
    NPC_MOUNTED_LANA            = 347030,

    // Alliance Pre-Champs
    NPC_STORMWIND_CHAMPION      = 35328,
    NPC_IRONFORGE_CHAMPION      = 35329,
    NPC_GNOMEREGAN_CHAMPION     = 35331,
    NPC_DARNASSUS_CHAMPION      = 35332,
    NPC_EXODAR_CHAMPION         = 35330,

    // Horde Pre-Champs
    NPC_ORGRIMMAR_CHAMPION      = 35314,
    NPC_THUNDER_BLUFF_CHAMPION  = 35325,
    NPC_UNDERCITY_CHAMPION      = 35327,
    NPC_SENJIN_CHAMPION         = 35323,
    NPC_SILVERMOON_CHAMPION     = 35326,

    NPC_EADRIC                  = 35119,
    NPC_PALETRESS               = 34928,

    NPC_ARGENT_LIGHWIELDER      = 35309,
    NPC_ARGENT_MONK             = 35305,
    NPC_PRIESTESS               = 35307,

    NPC_BLACK_KNIGHT            = 35451,

    NPC_RISEN_JAEREN            = 35545,
    NPC_RISEN_ARELAS            = 35564,

    NPC_JAEREN                  = 35004,
    NPC_ARELAS                  = 35005
};

enum eGameObjects
{
    GO_MAIN_GATE                = 195647,

    GO_CHAMPIONS_LOOT           = 195709,
    GO_CHAMPIONS_LOOT_H            = 195710,

    GO_EADRIC_LOOT              = 195374,
    GO_EADRIC_LOOT_H            = 195375,

    GO_PALETRESS_LOOT           = 195323,
    GO_PALETRESS_LOOT_H            = 195324
};

enum eVehicles
{
    //Grand Champions Alliance Vehicles
    VEHICLE_MARSHAL_JACOB_ALERIUS_MOUNT             = 35637,
    VEHICLE_AMBROSE_BOLTSPARK_MOUNT                 = 35633,
    VEHICLE_COLOSOS_MOUNT                           = 35768,
    VEHICLE_EVENSONG_MOUNT                          = 34658,
    VEHICLE_LANA_STOUTHAMMER_MOUNT                  = 35636,
    //Faction Champions (ALLIANCE)
    VEHICLE_DARNASSIA_NIGHTSABER                    = 33319,
    VEHICLE_EXODAR_ELEKK                            = 33318,
    VEHICLE_STORMWIND_STEED                         = 33217,
    VEHICLE_GNOMEREGAN_MECHANOSTRIDER               = 33317,
    VEHICLE_IRONFORGE_RAM                           = 33316,
    //Grand Champions Horde Vehicles
    VEHICLE_MOKRA_SKILLCRUSHER_MOUNT                = 35638,
    VEHICLE_ERESSEA_DAWNSINGER_MOUNT                = 35635,
    VEHICLE_RUNOK_WILDMANE_MOUNT                    = 35640,
    VEHICLE_ZUL_TORE_MOUNT                          = 35641,
    VEHICLE_DEATHSTALKER_VESCERI_MOUNT              = 35634,
    //Faction Champions (HORDE)
    VEHICLE_FORSAKE_WARHORSE                        = 33324,
    VEHICLE_THUNDER_BLUFF_KODO                      = 33322,
    VEHICLE_ORGRIMMAR_WOLF                          = 33320,
    VEHICLE_SILVERMOON_HAWKSTRIDER                  = 33323,
    VEHICLE_DARKSPEAR_RAPTOR                        = 33321,

    VEHICLE_ARGENT_WARHORSE                         = 35644,
    VEHICLE_ARGENT_BATTLEWORG                       = 36558,

    VEHICLE_BLACK_KNIGHT                            = 35491
};

#endif
