/*
 * Copyright (C) 2008-2011 TrinityCore <http://www.trinitycore.org/>
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

/* ScriptData
SDName: Instance Trial of the Champion
SDComment:
SDCategory: Trial Of the Champion
EndScriptData */

#include "ScriptPCH.h"
#include "trial_of_the_champion.h"

#define MAX_ENCOUNTER  4

class instance_trial_of_the_champion : public InstanceMapScript
{
public:
    instance_trial_of_the_champion() : InstanceMapScript("instance_trial_of_the_champion", 650) { }

    InstanceScript* GetInstanceScript(InstanceMap* pMap) const
    {
        return new instance_trial_of_the_champion_InstanceMapScript(pMap);
    }

    struct instance_trial_of_the_champion_InstanceMapScript : public InstanceScript
    {
        instance_trial_of_the_champion_InstanceMapScript(Map* pMap) : InstanceScript(pMap) {}

        uint32 m_auiEncounter[MAX_ENCOUNTER];

        uint16 uiMovementDone;
        uint16 uiGrandChampionsDeaths;
        uint8 uiArgentSoldierDeaths;

        uint64 uiAnnouncerGUID;
        uint64 uiMainGateGUID;
        uint64 uiPortcullisGUID;
        uint64 uiGrandChampionVehicle1GUID;
        uint64 uiGrandChampionVehicle2GUID;
        uint64 uiGrandChampionVehicle3GUID;
        uint32 grandChampionEntry[3];
        uint32 memoryEntry;
        uint64 uiChampionLootGUID;
        uint64 uimemoryEntryGUID;

        std::list<uint64> VehicleList;
        uint32 TeamInInstance;

        std::string str_data;

        bool bDone;

        void Initialize()
        {
            uiMovementDone = 0;
            uiGrandChampionsDeaths = 0;
            uiArgentSoldierDeaths = 0;

            uiAnnouncerGUID        = 0;
            uiMainGateGUID         = 0;
            uiPortcullisGUID       = 0;
            uiGrandChampionVehicle1GUID   = 0;
            uiGrandChampionVehicle2GUID   = 0;
            uiGrandChampionVehicle3GUID   = 0;
            uiChampionLootGUID            = 0;
            uimemoryEntryGUID          = 0;
            memoryEntry         = 0;

            bDone = false;

            VehicleList.clear();
            TeamInInstance = 0;
            memset(&grandChampionEntry, 0, sizeof(grandChampionEntry));
            memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));
        }

        bool IsEncounterInProgress() const
        {
            if(GameObject* portcullis = instance->GetGameObject(GetData64(DATA_PORTCULLIS))
            {}
            for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
            {
                if (m_auiEncounter[i] == IN_PROGRESS)
                    return true;
            }

            return false;
        }

        void OnCreatureCreate(Creature* creature)
        {
            Map::PlayerList const &players = instance->GetPlayers();

            if (!players.isEmpty())
            {
                if (Player* player = players.begin()->getSource())
                    TeamInInstance = player->GetTeam();
            }

            switch(creature->GetEntry())
            {
                // Champions
                case VEHICLE_MOKRA_SKILLCRUSHER_MOUNT:
                    if (TeamInInstance == HORDE)
                        creature->UpdateEntry(VEHICLE_MARSHAL_JACOB_ALERIUS_MOUNT, ALLIANCE);
                    break;
                case VEHICLE_ERESSEA_DAWNSINGER_MOUNT:
                    if (TeamInInstance == HORDE)
                        creature->UpdateEntry(VEHICLE_AMBROSE_BOLTSPARK_MOUNT, ALLIANCE);
                    break;
                case VEHICLE_RUNOK_WILDMANE_MOUNT:
                    if (TeamInInstance == HORDE)
                        creature->UpdateEntry(VEHICLE_COLOSOS_MOUNT, ALLIANCE);
                    break;
                case VEHICLE_ZUL_TORE_MOUNT:
                    if (TeamInInstance == HORDE)
                        creature->UpdateEntry(VEHICLE_EVENSONG_MOUNT, ALLIANCE);
                    break;
                case VEHICLE_DEATHSTALKER_VESCERI_MOUNT:
                    if (TeamInInstance == HORDE)
                        creature->UpdateEntry(VEHICLE_LANA_STOUTHAMMER_MOUNT, ALLIANCE);
                    break;
                // Coliseum Announcer || Just NPC_JAEREN must be spawned.
                case NPC_JAEREN:
                    uiAnnouncerGUID = creature->GetGUID();
                    if (TeamInInstance == ALLIANCE)
                        creature->UpdateEntry(NPC_ARELAS, ALLIANCE);
                    break;
                case VEHICLE_ARGENT_WARHORSE:
                case VEHICLE_ARGENT_BATTLEWORG:
                    VehicleList.push_back(creature->GetGUID());
                    break;
                case NPC_EADRIC:
                case NPC_PALETRESS:
                    uimemoryEntryGUID = creature->GetGUID();
                    break;
            }
        }

        void OnGameObjectCreate(GameObject* go)
        {
            switch(go->GetEntry())
            {
                case GO_MAIN_GATE:
                    uiMainGateGUID = go->GetGUID();
                    break;
                case GO_PORTCULLIS:
                    uiPortcullisGUID = go->GetGUID();
                    break;
                case GO_CHAMPIONS_LOOT:
                case GO_CHAMPIONS_LOOT_H:
                    uiChampionLootGUID = go->GetGUID();
                    break;
            }
        }

        void SetData(uint32 uiType, uint32 uiData)
        {
            switch(uiType)
            {
                case DATA_MOVEMENT_DONE:
                    uiMovementDone = uiData;
                    if (uiMovementDone == 3)
                    {
                        if (Creature* pAnnouncer =  instance->GetCreature(uiAnnouncerGUID))
                            pAnnouncer->AI()->SetData(DATA_IN_POSITION, 0);
                    }
                    break;
                case BOSS_GRAND_CHAMPIONS:
                    m_auiEncounter[0] = uiData;
                    if (uiData == IN_PROGRESS)
                    {
                        for (std::list<uint64>::const_iterator itr = VehicleList.begin(); itr != VehicleList.end(); ++itr)
                            if (Creature* summon = instance->GetCreature(*itr))
                                summon->RemoveFromWorld();
                    }else if (uiData == DONE)
                    {
                        DoUpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET, SPELL_ACHIEVEMENT_CHAMPIONS);
                        if (Creature* pAnnouncer =  instance->GetCreature(uiAnnouncerGUID))
                        {
                            pAnnouncer->GetMotionMaster()->MovePoint(0, 748.309f, 619.487f, 411.171f);
                            pAnnouncer->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                            pAnnouncer->SummonGameObject(instance->IsHeroic()? GO_CHAMPIONS_LOOT_H : GO_CHAMPIONS_LOOT, 746.59f, 618.49f, 411.09f, 1.42f, 0, 0, 0, 0, 90000000);
                        }
                    }
                    break;
                case DATA_ARGENT_SOLDIER_DEFEATED:
                    uiArgentSoldierDeaths = uiData;
                    if (uiArgentSoldierDeaths == 9)
                    {
                        if (Creature* pBoss =  instance->GetCreature(uimemoryEntryGUID))
                        {
                            pBoss->GetMotionMaster()->MovePoint(0, 746.88f, 618.74f, 411.06f);
                            pBoss->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                            pBoss->SetReactState(REACT_AGGRESSIVE);
                        }
                    }
                    break;
                case BOSS_ARGENT_CHALLENGE_E:
                    m_auiEncounter[1] = uiData;
                    if (Creature* pAnnouncer = instance->GetCreature(uiAnnouncerGUID))
                    {
                        DoUpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET, SPELL_ACHIEVEMENT_EADRIC);
                        pAnnouncer->GetMotionMaster()->MovePoint(0, 748.309f, 619.487f, 411.171f);
                        pAnnouncer->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                        pAnnouncer->SummonGameObject(instance->IsHeroic()? GO_EADRIC_LOOT_H : GO_EADRIC_LOOT, 746.59f, 618.49f, 411.09f, 1.42f, 0, 0, 0, 0, 90000000);
                    }
                    break;
                case BOSS_ARGENT_CHALLENGE_P:
                    m_auiEncounter[2] = uiData;
                    if (Creature* pAnnouncer = instance->GetCreature(uiAnnouncerGUID))
                    {
                        DoUpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET, SPELL_ACHIEVEMENT_PALETRESS);
                        DoUpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET, SPELL_ACHIEVEMENT_MEMORIES);
                        pAnnouncer->GetMotionMaster()->MovePoint(0, 748.309f, 619.487f, 411.171f);
                        pAnnouncer->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                        pAnnouncer->SummonGameObject(instance->IsHeroic()? GO_PALETRESS_LOOT_H : GO_PALETRESS_LOOT, 746.59f, 618.49f, 411.09f, 1.42f, 0, 0, 0, 0, 90000000);
                    }
                    break;
                case DATA_GRAND_CHAMPION_1:
                    grandChampionEntry[0] = uiData;
                    break;
                case DATA_GRAND_CHAMPION_2:
                    grandChampionEntry[1] = uiData;
                    break;
                case DATA_GRAND_CHAMPION_3:
                    grandChampionEntry[2] = uiData;
                    break;
                case DATA_MEMORY:
                    memoryEntry = uiData;
                    break;
            }

            if (uiData == DONE)
                SaveToDB();
        }

        uint32 GetData(uint32 uiData)
        {
            switch(uiData)
            {
                case BOSS_GRAND_CHAMPIONS:  return m_auiEncounter[0];
                case BOSS_ARGENT_CHALLENGE_E: return m_auiEncounter[1];
                case BOSS_ARGENT_CHALLENGE_P: return m_auiEncounter[2];
                case BOSS_BLACK_KNIGHT: return m_auiEncounter[3];

                case DATA_TEAM: return TeamInInstance;
                case DATA_MOVEMENT_DONE: return uiMovementDone;
                case DATA_ARGENT_SOLDIER_DEFEATED: return uiArgentSoldierDeaths;
                case DATA_GRAND_CHAMPION_1: return grandChampionEntry[0];
                case DATA_GRAND_CHAMPION_2: return grandChampionEntry[1];
                case DATA_GRAND_CHAMPION_3: return grandChampionEntry[2];
                case DATA_MEMORY: return memoryEntry;
            }

            return 0;
        }

        uint64 GetData64(uint32 uiData)
        {
            switch(uiData)
            {
                case DATA_ANNOUNCER: return uiAnnouncerGUID;
                case DATA_MAIN_GATE: return uiMainGateGUID;
                case DATA_PORTCULLIS: return uiPortcullisGUID;
            }

            return 0;
        }

        bool CheckAchievementCriteriaMeet(uint32 criteria_id, Player const* /*source*/, Unit const* /*target*/, uint32 /*miscvalue1*/)
        {
            switch(criteria_id)
            {
                case CRITERIA_CHAMPION_JACOB:
                case CRITERIA_CHAMPION_LANA:
                case CRITERIA_CHAMPION_COLOSOS:
                case CRITERIA_CHAMPION_AMBROSE:
                case CRITERIA_CHAMPION_JAELYNE:
                case CRITERIA_CHAMPION_MOKRA:
                case CRITERIA_CHAMPION_VISCERI:
                case CRITERIA_CHAMPION_RUNOK:
                case CRITERIA_CHAMPION_ERESSEA:
                case CRITERIA_CHAMPION_ZULTORE:
                    for(uint8 i = 0; i<3; i++)
                        if(grandChampionEntry[i] == GetRelatedCreatureEntry(criteria_id))
                            return true;
                    return false;
                case CRITERIA_MEMORY_HOGGER:
                case CRITERIA_MEMORY_VANCLEEF:
                case CRITERIA_MEMORY_MUTANUS:
                case CRITERIA_MEMORY_HEROD:
                case CRITERIA_MEMORY_LUCIFROM:
                case CRITERIA_MEMORY_THUNDERAAN:
                case CRITERIA_MEMORY_CHROMAGGUS:
                case CRITERIA_MEMORY_HAKKAR:
                case CRITERIA_MEMORY_VEKNILASH:
                case CRITERIA_MEMORY_KALITHRESH:
                case CRITERIA_MEMORY_MALCHEZAAR:
                case CRITERIA_MEMORY_GRUUL:
                case CRITERIA_MEMORY_VASHJ:
                case CRITERIA_MEMORY_ARCHIMONDE:
                case CRITERIA_MEMORY_ILLIDAN:
                case CRITERIA_MEMORY_DELRISSA:
                case CRITERIA_MEMORY_MURU:
                case CRITERIA_MEMORY_INGVAR:
                case CRITERIA_MEMORY_CYANIGOSA:
                case CRITERIA_MEMORY_ECK:
                case CRITERIA_MEMORY_ONYXIA:
                case CRITERIA_MEMORY_HEIGAN:
                case CRITERIA_MEMORY_IGNIS:
                case CRITERIA_MEMORY_VEZAX:
                case CRITERIA_MEMORY_ALGALON:
                    return (memoryEntry == GetRelatedCreatureEntry(criteria_id));
            }

            return false;
        }
        uint32 GetRelatedCreatureEntry(uint32 criteria_id)
        {
            switch(criteria_id)
            {
                case CRITERIA_CHAMPION_JACOB:   return NPC_JACOB;
                case CRITERIA_CHAMPION_LANA:    return NPC_LANA;
                case CRITERIA_CHAMPION_COLOSOS: return NPC_COLOSOS;
                case CRITERIA_CHAMPION_AMBROSE: return NPC_AMBROSE;
                case CRITERIA_CHAMPION_JAELYNE: return NPC_JAELYNE;

                case CRITERIA_CHAMPION_MOKRA:   return NPC_MOKRA;
                case CRITERIA_CHAMPION_VISCERI: return NPC_VISCERI;
                case CRITERIA_CHAMPION_RUNOK:   return NPC_RUNOK;
                case CRITERIA_CHAMPION_ERESSEA: return NPC_ERESSEA;
                case CRITERIA_CHAMPION_ZULTORE: return NPC_ZULTORE;

                case CRITERIA_MEMORY_HOGGER:     return NPC_MEMORY_HOGGER;
                case CRITERIA_MEMORY_VANCLEEF:   return NPC_MEMORY_VANCLEEF;
                case CRITERIA_MEMORY_MUTANUS:    return NPC_MEMORY_MUTANUS;
                case CRITERIA_MEMORY_HEROD:      return NPC_MEMORY_HEROD;
                case CRITERIA_MEMORY_LUCIFROM:   return NPC_MEMORY_LUCIFROM;
                case CRITERIA_MEMORY_THUNDERAAN: return NPC_MEMORY_THUNDERAAN;
                case CRITERIA_MEMORY_CHROMAGGUS: return NPC_MEMORY_CHROMAGGUS;
                case CRITERIA_MEMORY_HAKKAR:     return NPC_MEMORY_HAKKAR;
                case CRITERIA_MEMORY_VEKNILASH:  return NPC_MEMORY_VEKNILASH;
                case CRITERIA_MEMORY_KALITHRESH: return NPC_MEMORY_KALITHRESH;
                case CRITERIA_MEMORY_MALCHEZAAR: return NPC_MEMORY_MALCHEZAAR;
                case CRITERIA_MEMORY_GRUUL:      return NPC_MEMORY_GRUUL;
                case CRITERIA_MEMORY_VASHJ:      return NPC_MEMORY_VASHJ;
                case CRITERIA_MEMORY_ARCHIMONDE: return NPC_MEMORY_ARCHIMONDE;
                case CRITERIA_MEMORY_ILLIDAN:    return NPC_MEMORY_ILLIDAN;
                case CRITERIA_MEMORY_DELRISSA:   return NPC_MEMORY_DELRISSA;
                case CRITERIA_MEMORY_MURU:       return NPC_MEMORY_MURU;
                case CRITERIA_MEMORY_INGVAR:     return NPC_MEMORY_INGVAR;
                case CRITERIA_MEMORY_CYANIGOSA:  return NPC_MEMORY_CYANIGOSA;
                case CRITERIA_MEMORY_ECK:        return NPC_MEMORY_ECK;
                case CRITERIA_MEMORY_ONYXIA:     return NPC_MEMORY_ONYXIA;
                case CRITERIA_MEMORY_HEIGAN:     return NPC_MEMORY_HEIGAN;
                case CRITERIA_MEMORY_IGNIS:      return NPC_MEMORY_IGNIS;
                case CRITERIA_MEMORY_VEZAX:      return NPC_MEMORY_VEZAX;
                case CRITERIA_MEMORY_ALGALON:    return NPC_MEMORY_ALGALON;
            }
            return 0;
        }
        std::string GetSaveData()
        {
            OUT_SAVE_INST_DATA;

            std::ostringstream saveStream;

            saveStream << "T C " << m_auiEncounter[0]
                << ' ' << m_auiEncounter[1]
                << ' ' << m_auiEncounter[2]
                << ' ' << m_auiEncounter[3]
                << ' ' << uiGrandChampionsDeaths
                << ' ' << uiMovementDone;

            str_data = saveStream.str();

            OUT_SAVE_INST_DATA_COMPLETE;
            return str_data;
        }

        void Load(const char* in)
        {
            if (!in)
            {
                OUT_LOAD_INST_DATA_FAIL;
                return;
            }

            OUT_LOAD_INST_DATA(in);

            char dataHead1, dataHead2;
            uint16 data0, data1, data2, data3, data4, data5;

            std::istringstream loadStream(in);
            loadStream >> dataHead1 >> dataHead2 >> data0 >> data1 >> data2 >> data3 >> data4 >> data5;

            if (dataHead1 == 'T' && dataHead2 == 'C')
            {
                m_auiEncounter[0] = data0;
                m_auiEncounter[1] = data1;
                m_auiEncounter[2] = data2;
                m_auiEncounter[3] = data3;

                for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                    if (m_auiEncounter[i] == IN_PROGRESS)
                        m_auiEncounter[i] = NOT_STARTED;

                uiGrandChampionsDeaths = data4;
                uiMovementDone = data5;
            } else OUT_LOAD_INST_DATA_FAIL;

            OUT_LOAD_INST_DATA_COMPLETE;
        }
    };

};

void AddSC_instance_trial_of_the_champion()
{
    new instance_trial_of_the_champion();
}
