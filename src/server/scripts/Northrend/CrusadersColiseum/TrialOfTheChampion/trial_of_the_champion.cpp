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
SDName: Trial Of the Champion
SD%Complete:
SDComment:
SDCategory: trial_of_the_champion
EndScriptData */

/* ContentData
npc_announcer_toc5
EndContentData */

#include "ScriptPCH.h"
#include "trial_of_the_champion.h"
#include "Vehicle.h"

#define GOSSIP_START_EVENT1     "I'm ready to start challenge."
#define GOSSIP_START_EVENT2     "I'm ready for the next challenge."

#define ORIENTATION             4.714f

/*######
## npc_announcer_toc5
######*/

const Position SpawnPosition = {746.261f, 657.401f, 411.681f, 4.65f};
const Position OutStadiumPosition = {747.03f, 687.483f, 412.373f, 1.53475f};
const Position AnnouncerPosition = {733.877f, 662.269f, 412.393f, 4.61586f};
const Position IntroPosition[3] =
{
    {724.854f, 640.344f, 411.829f, 5.60704f}, // Boss
    {714.172f, 618.206f, 411.604f, 0.0f},     // Boss
    {724.300f, 595.99f, 411.568f, 0.819248f}  // Boss
};

//class npc_announcer_toc5 : public CreatureScript
//{
//public:
//    npc_announcer_toc5() : CreatureScript("npc_announcer_toc5") { }
//
//    struct npc_announcer_toc5AI : public ScriptedAI
//    {
//        npc_announcer_toc5AI(Creature* creature) : ScriptedAI(creature)
//        {
//            pInstance = creature->GetInstanceScript();
//
//            uiSummonTimes = 0;
//            uiPosition = 0;
//            uiLesserChampions = 0;
//
//            uiFirstBoss = 0;
//            uiSecondBoss = 0;
//            uiThirdBoss = 0;
//
//            uiArgentChampion = 0;
//
//            uiPhase = 0;
//            uiTimer = 0;
//
//            uiVehicle1GUID = 0;
//            uiVehicle2GUID = 0;
//            uiVehicle3GUID = 0;
//
//            Champion1List.clear();
//            Champion2List.clear();
//            Champion3List.clear();
//
//            me->SetReactState(REACT_PASSIVE);
//            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
//            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
//
//            SetGrandChampionsForEncounter();
//            SetArgentChampion();
//        }
//
//        InstanceScript* pInstance;
//
//        uint8 uiSummonTimes;
//        uint8 uiPosition;
//        uint8 uiLesserChampions;
//
//        uint32 uiArgentChampion;
//
//        uint32 uiFirstBoss;
//        uint32 uiSecondBoss;
//        uint32 uiThirdBoss;
//
//        uint32 uiPhase;
//        uint32 uiTimer;
//
//        uint64 uiVehicle1GUID;
//        uint64 uiVehicle2GUID;
//        uint64 uiVehicle3GUID;
//
//        uint64 uiGrandChampionBoss1;
//
//        std::list<uint64> Champion1List;
//        std::list<uint64> Champion2List;
//        std::list<uint64> Champion3List;
//
//        void NextStep(uint32 uiTimerStep, bool bNextStep = true, uint8 uiPhaseStep = 0)
//        {
//            uiTimer = uiTimerStep;
//            if (bNextStep)
//                ++uiPhase;
//            else
//                uiPhase = uiPhaseStep;
//        }
//
//        void SetData(uint32 uiType, uint32 /*uiData*/)
//        {
//            switch (uiType)
//            {
//                case DATA_START:
//                    DoSummonGrandChampion(uiFirstBoss);
//                    NextStep(10000, false, 1);
//                    break;
//                case DATA_IN_POSITION: //movement done.
//                    me->GetMotionMaster()->MovePoint(1, 735.81f, 661.92f, 412.39f);
//                    if (GameObject* pGO = GameObject::GetGameObject(*me, pInstance->GetData64(DATA_MAIN_GATE)))
//                        pInstance->HandleGameObject(pGO->GetGUID(), false);
//                    NextStep(10000, false, 3);
//                    break;
//                case DATA_LESSER_CHAMPIONS_DEFEATED:
//                {
//                    ++uiLesserChampions;
//                    std::list<uint64> TempList;
//                    if (uiLesserChampions == 3 || uiLesserChampions == 6)
//                    {
//                        switch(uiLesserChampions)
//                        {
//                            case 3:
//                                TempList = Champion2List;
//                                break;
//                            case 6:
//                                TempList = Champion3List;
//                                break;
//                        }
//
//                        for (std::list<uint64>::const_iterator itr = TempList.begin(); itr != TempList.end(); ++itr)
//                            if (Creature* summon = Unit::GetCreature(*me, *itr))
//                                AggroAllPlayers(summon);
//                    }else if (uiLesserChampions == 9)
//                        StartGrandChampionsAttack();
//
//                    break;
//                }
//            }
//        }
//
//        void StartGrandChampionsAttack()
//        {
//            Creature* pGrandChampion1 = Unit::GetCreature(*me, uiVehicle1GUID);
//            Creature* pGrandChampion2 = Unit::GetCreature(*me, uiVehicle2GUID);
//            Creature* pGrandChampion3 = Unit::GetCreature(*me, uiVehicle3GUID);
//
//            if (pGrandChampion1 && pGrandChampion2 && pGrandChampion3)
//            {
//                AggroAllPlayers(pGrandChampion1);
//                AggroAllPlayers(pGrandChampion2);
//                AggroAllPlayers(pGrandChampion3);
//            }
//        }
//
//        void MovementInform(uint32 uiType, uint32 uiPointId)
//        {
//            if (uiType != POINT_MOTION_TYPE)
//                return;
//
//            if (uiPointId == 1)
//            {
//                me->SetOrientation(ORIENTATION);
//                me->SendMovementFlagUpdate();
//            }
//        }
//
//        void DoSummonGrandChampion(uint32 uiBoss)
//        {
//            ++uiSummonTimes;
//            uint32 VEHICLE_TO_SUMMON1 = 0;
//            uint32 VEHICLE_TO_SUMMON2 = 0;
//            switch(uiBoss)
//            {
//                case 0:
//                    VEHICLE_TO_SUMMON1 = VEHICLE_MOKRA_SKILLCRUSHER_MOUNT;
//                    VEHICLE_TO_SUMMON2 = VEHICLE_ORGRIMMAR_WOLF;
//                    break;
//                case 1:
//                    VEHICLE_TO_SUMMON1 = VEHICLE_ERESSEA_DAWNSINGER_MOUNT;
//                    VEHICLE_TO_SUMMON2 = VEHICLE_SILVERMOON_HAWKSTRIDER;
//                    break;
//                case 2:
//                    VEHICLE_TO_SUMMON1 = VEHICLE_RUNOK_WILDMANE_MOUNT;
//                    VEHICLE_TO_SUMMON2 = VEHICLE_THUNDER_BLUFF_KODO;
//                    break;
//                case 3:
//                    VEHICLE_TO_SUMMON1 = VEHICLE_ZUL_TORE_MOUNT;
//                    VEHICLE_TO_SUMMON2 = VEHICLE_DARKSPEAR_RAPTOR;
//                    break;
//                case 4:
//                    VEHICLE_TO_SUMMON1 = VEHICLE_DEATHSTALKER_VESCERI_MOUNT;
//                    VEHICLE_TO_SUMMON2 = VEHICLE_FORSAKE_WARHORSE;
//                    break;
//                default:
//                    return;
//            }
//
//            if (Creature* pBoss = me->SummonCreature(VEHICLE_TO_SUMMON1, SpawnPosition))
//            {
//                switch(uiSummonTimes)
//                {
//                    case 1:
//                    {
//                        uiVehicle1GUID = pBoss->GetGUID();
//                        uint64 uiGrandChampionBoss1 = 0;
//                        if (Creature* pBoss = Unit::GetCreature(*me, uiVehicle1GUID))
//                            if (Vehicle* pVehicle = pBoss->GetVehicleKit())
//                                if (Unit* pUnit = pVehicle->GetPassenger(0))
//                                    uiGrandChampionBoss1 = pUnit->GetGUID();
//                        if (pInstance)
//                        {
//                            pInstance->SetData64(DATA_GRAND_CHAMPION_VEHICLE_1, uiVehicle1GUID);
//                            pInstance->SetData64(DATA_GRAND_CHAMPION_1, uiGrandChampionBoss1);
//                        }
//                        pBoss->AI()->SetData(1, 0);
//                        break;
//                    }
//                    case 2:
//                    {
//                        uiVehicle2GUID = pBoss->GetGUID();
//                        uint64 uiGrandChampionBoss2 = 0;
//                        if (Creature* pBoss = Unit::GetCreature(*me, uiVehicle2GUID))
//                            if (Vehicle* pVehicle = pBoss->GetVehicleKit())
//                                if (Unit* pUnit = pVehicle->GetPassenger(0))
//                                    uiGrandChampionBoss2 = pUnit->GetGUID();
//                        if (pInstance)
//                        {
//                            pInstance->SetData64(DATA_GRAND_CHAMPION_VEHICLE_2, uiVehicle2GUID);
//                            pInstance->SetData64(DATA_GRAND_CHAMPION_2, uiGrandChampionBoss2);
//                        }
//                        pBoss->AI()->SetData(2, 0);
//                        break;
//                    }
//                    case 3:
//                    {
//                        uiVehicle3GUID = pBoss->GetGUID();
//                        uint64 uiGrandChampionBoss3 = 0;
//                        if (Creature* pBoss = Unit::GetCreature(*me, uiVehicle3GUID))
//                            if (Vehicle* pVehicle = pBoss->GetVehicleKit())
//                                if (Unit* pUnit = pVehicle->GetPassenger(0))
//                                    uiGrandChampionBoss3 = pUnit->GetGUID();
//                        if (pInstance)
//                        {
//                            pInstance->SetData64(DATA_GRAND_CHAMPION_VEHICLE_3, uiVehicle3GUID);
//                            pInstance->SetData64(DATA_GRAND_CHAMPION_3, uiGrandChampionBoss3);
//                        }
//                        pBoss->AI()->SetData(3, 0);
//                        break;
//                    }
//                    default:
//                        return;
//                }
//
//                for (uint8 i = 0; i < 3; ++i)
//                {
//                    if (Creature* pAdd = me->SummonCreature(VEHICLE_TO_SUMMON2, SpawnPosition, TEMPSUMMON_CORPSE_DESPAWN))
//                    {
//                        switch(uiSummonTimes)
//                        {
//                            case 1:
//                                Champion1List.push_back(pAdd->GetGUID());
//                                break;
//                            case 2:
//                                Champion2List.push_back(pAdd->GetGUID());
//                                break;
//                            case 3:
//                                Champion3List.push_back(pAdd->GetGUID());
//                                break;
//                        }
//
//                        switch(i)
//                        {
//                            case 0:
//                                pAdd->GetMotionMaster()->MoveFollow(pBoss, 2.0f, M_PI);
//                                break;
//                            case 1:
//                                pAdd->GetMotionMaster()->MoveFollow(pBoss, 2.0f, M_PI / 2);
//                                break;
//                            case 2:
//                                pAdd->GetMotionMaster()->MoveFollow(pBoss, 2.0f, M_PI / 2 + M_PI);
//                                break;
//                        }
//                    }
//
//                }
//            }
//        }
//
//        void DoStartArgentChampionEncounter()
//        {
//            me->GetMotionMaster()->MovePoint(1, 735.81f, 661.92f, 412.39f);
//
//            if (me->SummonCreature(uiArgentChampion, SpawnPosition))
//            {
//                for (uint8 i = 0; i < 3; ++i)
//                {
//                    if (Creature* pTrash = me->SummonCreature(NPC_ARGENT_LIGHWIELDER, SpawnPosition))
//                        pTrash->AI()->SetData(i, 0);
//                    if (Creature* pTrash = me->SummonCreature(NPC_ARGENT_MONK, SpawnPosition))
//                        pTrash->AI()->SetData(i, 0);
//                    if (Creature* pTrash = me->SummonCreature(NPC_PRIESTESS, SpawnPosition))
//                        pTrash->AI()->SetData(i, 0);
//                }
//            }
//        }
//
//        void SetGrandChampionsForEncounter()
//        {
//            uiFirstBoss = urand(0, 4);
//
//            while (uiSecondBoss == uiFirstBoss || uiThirdBoss == uiFirstBoss || uiThirdBoss == uiSecondBoss)
//            {
//                uiSecondBoss = urand(0, 4);
//                uiThirdBoss = urand(0, 4);
//            }
//        }
//
//        void SetArgentChampion()
//        {
//           uint8 uiTempBoss = urand(0, 1);
//
//           switch(uiTempBoss)
//           {
//                case 0:
//                    uiArgentChampion = NPC_EADRIC;
//                    break;
//                case 1:
//                    uiArgentChampion = NPC_PALETRESS;
//                    break;
//           }
//        }
//
//        void StartEncounter()
//        {
//            if (!pInstance)
//                return;
//
//            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
//
//            if (pInstance->GetData(BOSS_BLACK_KNIGHT) == NOT_STARTED)
//            {
//                if (pInstance->GetData(BOSS_ARGENT_CHALLENGE_E) == NOT_STARTED && pInstance->GetData(BOSS_ARGENT_CHALLENGE_P) == NOT_STARTED)
//                {
//                    if (pInstance->GetData(BOSS_GRAND_CHAMPIONS) == NOT_STARTED)
//                        me->AI()->SetData(DATA_START, 0);
//
//                    if (pInstance->GetData(BOSS_GRAND_CHAMPIONS) == DONE)
//                        DoStartArgentChampionEncounter();
//                }
//
//               if ((pInstance->GetData(BOSS_GRAND_CHAMPIONS) == DONE &&
//                   pInstance->GetData(BOSS_ARGENT_CHALLENGE_E) == DONE) ||
//                   pInstance->GetData(BOSS_ARGENT_CHALLENGE_P) == DONE)
//                    me->SummonCreature(VEHICLE_BLACK_KNIGHT, 769.834f, 651.915f, 447.035f, 0);
//            }
//        }
//
//        void AggroAllPlayers(Creature* pTemp)
//        {
//            Map::PlayerList const &PlList = me->GetMap()->GetPlayers();
//
//            if (PlList.isEmpty())
//                return;
//
//            for (Map::PlayerList::const_iterator i = PlList.begin(); i != PlList.end(); ++i)
//            {
//                if (Player* player = i->getSource())
//                {
//                    if (player->isGameMaster())
//                        continue;
//
//                    if (player->isAlive())
//                    {
//                        pTemp->SetHomePosition(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation());
//                        pTemp->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
//                        pTemp->SetReactState(REACT_AGGRESSIVE);
//                        pTemp->SetInCombatWith(player);
//                        player->SetInCombatWith(pTemp);
//                        pTemp->AddThreat(player, 0.0f);
//                    }
//                }
//            }
//        }
//
//       void UpdateAI(const uint32 uiDiff)
//        {
//            ScriptedAI::UpdateAI(uiDiff);
//
//            if (uiTimer <= uiDiff)
//            {
//                switch(uiPhase)
//                {
//                    case 1:
//                        DoSummonGrandChampion(uiSecondBoss);
//                        NextStep(10000, true);
//                        break;
//                    case 2:
//                        DoSummonGrandChampion(uiThirdBoss);
//                        NextStep(0, false);
//                        break;
//                    case 3:
//                        if (!Champion1List.empty())
//                        {
//                            for (std::list<uint64>::const_iterator itr = Champion1List.begin(); itr != Champion1List.end(); ++itr)
//                                if (Creature* summon = Unit::GetCreature(*me, *itr))
//                                    AggroAllPlayers(summon);
//                            NextStep(0, false);
//                        }
//                        break;
//                }
//            } else uiTimer -= uiDiff;
//
//            if (!UpdateVictim())
//                return;
//        }
//
//        void JustSummoned(Creature* summon)
//        {
//            if (pInstance && pInstance->GetData(BOSS_GRAND_CHAMPIONS) == NOT_STARTED)
//            {
//                summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
//                summon->SetReactState(REACT_PASSIVE);
//            }
//        }
//
//        void SummonedCreatureDespawn(Creature* summon)
//        {
//            switch(summon->GetEntry())
//            {
//                case VEHICLE_DARNASSIA_NIGHTSABER:
//                case VEHICLE_EXODAR_ELEKK:
//                case VEHICLE_STORMWIND_STEED:
//                case VEHICLE_GNOMEREGAN_MECHANOSTRIDER:
//                case VEHICLE_IRONFORGE_RAM:
//                case VEHICLE_FORSAKE_WARHORSE:
//                case VEHICLE_THUNDER_BLUFF_KODO:
//                case VEHICLE_ORGRIMMAR_WOLF:
//                case VEHICLE_SILVERMOON_HAWKSTRIDER:
//                case VEHICLE_DARKSPEAR_RAPTOR:
//                    me->AI()->SetData(DATA_LESSER_CHAMPIONS_DEFEATED, 0);
//                    break;
//            }
//        }
//    };
//
//    CreatureAI* GetAI(Creature* creature) const
//    {
//        return new npc_announcer_toc5AI(creature);
//    }
//
//    bool OnGossipHello(Player* player, Creature* creature)
//    {
//        InstanceScript* pInstance = creature->GetInstanceScript();
//
//        if (pInstance &&
//            ((pInstance->GetData(BOSS_GRAND_CHAMPIONS) == DONE &&
//            pInstance->GetData(BOSS_BLACK_KNIGHT) == DONE &&
//            pInstance->GetData(BOSS_ARGENT_CHALLENGE_E) == DONE) ||
//            pInstance->GetData(BOSS_ARGENT_CHALLENGE_P) == DONE))
//            return false;
//
//        if (pInstance &&
//            pInstance->GetData(BOSS_GRAND_CHAMPIONS) == NOT_STARTED &&
//            pInstance->GetData(BOSS_ARGENT_CHALLENGE_E) == NOT_STARTED &&
//            pInstance->GetData(BOSS_ARGENT_CHALLENGE_P) == NOT_STARTED &&
//            pInstance->GetData(BOSS_BLACK_KNIGHT) == NOT_STARTED)
//            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_START_EVENT1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
//        else if (pInstance)
//            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_START_EVENT2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
//
//        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
//
//        return true;
//    }
//
//    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
//    {
//        player->PlayerTalkClass->ClearMenus();
//        if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
//        {
//            player->CLOSE_GOSSIP_MENU();
//            CAST_AI(npc_announcer_toc5::npc_announcer_toc5AI, creature->AI())->StartEncounter();
//        }
//
//        return true;
//    }
//};

enum AllianceRaces
{
    HUMAN = 0,
    GNOME,
    DRAWF,
    NIGHT_ELF,
    DRANEI,
};

enum HordeRaces
{
    ORC = 0,
    TROLL,
    UNDEAD,
    TAUREN,
    BLOOD_ELF,
};

enum Data
{
    DATA_INTRO = 0,
    DATA_MAX,
};

enum AnnouncerPhases
{
    EVENT_INTRO = 0, // Presentation of champions
    EVENT_WAVES,
    EVENT_CHAMPIONS,
    EVENTS_MAX,
};
//uint32 Alliance 
class npc_announcer_toc5 : public CreatureScript
{
public:
    npc_announcer_toc5() : CreatureScript("npc_announcer_toc5") { }

    struct npc_announcer_toc5AI : public ScriptedAI
    {
        npc_announcer_toc5AI(Creature* creature) : ScriptedAI(creature)
        {
            pInstance = me->GetInstanceScript();
        }

        InstanceScript* pInstance;
        EventMap events;

        uint32 eventIds[EVENTS_MAX];

        uint64 stalkerGUID;
        uint64 bossGUID[3];
        uint64 addsGUID[3][3];
        uint32 bossEntry[3];

        bool addsAttacking;
        uint8 defeatedCount;

        void Reset()
        {
            events.Reset();
            //summons[0]->DespawnAll();
            for(uint8 i=0; i<EVENTS_MAX; i++)
                eventIds[i] = 0;

            for(uint8 i=0; i<3; i++)
            {
                bossEntry[i] = NPC_MOUNTED_JACOB;//0;
                bossGUID[i] = 0;
            }

            for(uint8 i=0; i<3; i++)
                for(uint8 j=0; j<3; j++)
                    addsGUID[i][j] = 0;

            stalkerGUID = 0;
            defeatedCount = 0;
            addsAttacking = false;
        }

        void JustSummoned(Creature* summon)
        {
            summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            summon->SetReactState(REACT_PASSIVE);
        }

        void SetData(uint32 type, uint32 data)
        {
            eventIds[type] = data;
            if(data == IN_PROGRESS)
            {
                events.ScheduleEvent(1, 0);
                if(type == EVENT_INTRO)
                    SetGrandChampionsForEncounter();
            }
        }

        void SetGrandChampionsForEncounter()
        {
            bossEntry[0] = RAND(NPC_MOUNTED_JACOB, NPC_MOUNTED_AMBROSE, NPC_MOUNTED_COLOSOS, NPC_MOUNTED_JAELYNE, NPC_MOUNTED_LANA);

            while (bossEntry[1] == bossEntry[0] || bossEntry[2] == bossEntry[0] || bossEntry[2] == bossEntry[1])
            {
                bossEntry[1] = RAND(NPC_MOUNTED_JACOB, NPC_MOUNTED_AMBROSE, NPC_MOUNTED_COLOSOS, NPC_MOUNTED_JAELYNE, NPC_MOUNTED_LANA);
                bossEntry[2] = RAND(NPC_MOUNTED_JACOB, NPC_MOUNTED_AMBROSE, NPC_MOUNTED_COLOSOS, NPC_MOUNTED_JAELYNE, NPC_MOUNTED_LANA);
            }
        }

        uint32 GetData(uint32 type)
        {
            return eventIds[type];
        }

        uint32 GetAddId(uint32 bossId)
        {
            switch(bossId)
            {
                case NPC_JACOB:
                case NPC_MOUNTED_JACOB:
                    return NPC_STORMWIND_CHAMPION;
                case NPC_AMBROSE:
                case NPC_MOUNTED_AMBROSE:
                    return NPC_GNOMEREGAN_CHAMPION;
                case NPC_COLOSOS:
                case NPC_MOUNTED_COLOSOS:
                    return NPC_EXODAR_CHAMPION;
                case NPC_JAELYNE:
                case NPC_MOUNTED_JAELYNE:
                    return NPC_DARNASSUS_CHAMPION;
                case NPC_LANA:
                case NPC_MOUNTED_LANA:
                    return NPC_IRONFORGE_CHAMPION;
            }
            return 0;
        }

        uint32 GetRealBossEntry(uint32 mountedBossID)
        {
            switch(mountedBossID)
            {
                case NPC_MOUNTED_JACOB:
                    return NPC_JACOB;
                case NPC_MOUNTED_AMBROSE:
                    return NPC_AMBROSE;
                case NPC_MOUNTED_COLOSOS:
                    return NPC_COLOSOS;
                case NPC_MOUNTED_JAELYNE:
                    return NPC_JAELYNE;
                case NPC_MOUNTED_LANA:
                    return NPC_LANA;
            }

            return 0;
        }

        void UpdateAI(const uint32 diff)
        {
            events.Update(diff);

            if(GetData(EVENT_INTRO) == IN_PROGRESS)
            {
                switch(events.ExecuteEvent())
                {
                    case 1:
                        // TODO: Intro texts
                        // Open door
                        if (GameObject* pGO = GameObject::GetGameObject(*me, pInstance->GetData64(DATA_MAIN_GATE)))
                            pInstance->HandleGameObject(pGO->GetGUID(), true);
                        events.ScheduleEvent(2, 2000);
                        break;
                    case 2:
                        // Summon invisible trigger for orientation prupouses only
                        if(Creature* stalker = me->SummonCreature(22515, me->GetPositionX() , me->GetPositionY(), me->GetPositionZ()))
                            stalkerGUID = stalker->GetGUID();

                        // Summon 1st Boss and adds and make them follow him
                        if(Creature* boss = me->SummonCreature(bossEntry[0], SpawnPosition))
                        {
                            bossGUID[0] = boss->GetGUID();
                            boss->SetTarget(stalkerGUID);

                            for (uint8 i = 0; i < 3; ++i)
                            {
                                if(Creature* add = me->SummonCreature(GetAddId(boss->GetEntry()), SpawnPosition, TEMPSUMMON_MANUAL_DESPAWN))
                                {
                                    add->SetTarget(stalkerGUID);
                                    addsGUID[0][i] = add->GetGUID();
                                    switch(i)
                                    {
                                        case 0: add->GetMotionMaster()->MoveFollow(boss, 2.0f, M_PI); break;
                                        case 1: add->GetMotionMaster()->MoveFollow(boss, 2.0f, M_PI / 2); break;
                                        case 2: add->GetMotionMaster()->MoveFollow(boss, 2.0f, M_PI / 2 + M_PI); break;
                                    }
                                }
                            }
                        }
                        events.ScheduleEvent(3, 2000);
                        break;
                    case 3:
                        // Move first boss to the new position
                        if(Creature* boss1 = me->GetCreature(*me, bossGUID[0]))
                            boss1->GetMotionMaster()->MovePoint(0, IntroPosition[0]);

                        events.ScheduleEvent(4, 4000);
                        break;
                    case 4:
                        // Refresh the adds position
                        for(uint8 i=0; i<1; i++)
                        {
                            if(Creature* boss = me->GetCreature(*me, bossGUID[i]))
                            {
                                boss->SetFacingToObject(me);
                                for(uint8 j = 0; j<3; j++)
                                {
                                    if(Creature* add = me->GetCreature(*me, addsGUID[i][j]))
                                    {
                                        switch(j)
                                        {
                                            case 0: add->GetMotionMaster()->MoveFollow(boss, 2.0f, M_PI); break;
                                            case 1: add->GetMotionMaster()->MoveFollow(boss, 2.0f, M_PI / 2); break;
                                            case 2: add->GetMotionMaster()->MoveFollow(boss, 2.0f, M_PI / 2 + M_PI); break;
                                        }
                                    }
                                }
                            }
                        }
                        events.ScheduleEvent(5, 3000);
                        break;
                    case 5:
                        // Summon 2nd Boss and adds and make them follow him
                        if(Creature* boss = me->SummonCreature(bossEntry[1], SpawnPosition))
                        {
                            bossGUID[1] = boss->GetGUID();
                            boss->SetTarget(stalkerGUID);

                            for (uint8 i = 0; i < 3; ++i)
                            {
                                if(Creature* add = me->SummonCreature(GetAddId(boss->GetEntry()), SpawnPosition, TEMPSUMMON_MANUAL_DESPAWN))
                                {
                                    add->SetTarget(stalkerGUID);
                                    addsGUID[1][i] = add->GetGUID();
                                    switch(i)
                                    {
                                        case 0: add->GetMotionMaster()->MoveFollow(boss, 2.0f, M_PI); break;
                                        case 1: add->GetMotionMaster()->MoveFollow(boss, 2.0f, M_PI / 2); break;
                                        case 2: add->GetMotionMaster()->MoveFollow(boss, 2.0f, M_PI / 2 + M_PI); break;
                                    }
                                }
                            }
                        }
                        events.ScheduleEvent(6, 5000);
                        break;
                    case 6:
                        // Move first boss to the new position
                        if(Creature* boss1 = me->GetCreature(*me, bossGUID[0]))
                            boss1->GetMotionMaster()->MovePoint(0, IntroPosition[1]);

                        // Move second boss to the new position
                        if(Creature* boss2 = me->GetCreature(*me, bossGUID[1]))
                            boss2->GetMotionMaster()->MovePoint(0, IntroPosition[0]);

                        events.ScheduleEvent(7, 4000);
                        break;
                    case 7:
                        // Refresh the adds position
                        for(uint8 i=0; i<2; i++)
                        {
                            if(Creature* boss = me->GetCreature(*me, bossGUID[i]))
                            {
                                boss->SetFacingToObject(me);
                                for(uint8 j = 0; j<3; j++)
                                {
                                    if(Creature* add = me->GetCreature(*me, addsGUID[i][j]))
                                    {
                                        switch(j)
                                        {
                                            case 0: add->GetMotionMaster()->MoveFollow(boss, 2.0f, M_PI); break;
                                            case 1: add->GetMotionMaster()->MoveFollow(boss, 2.0f, M_PI / 2); break;
                                            case 2: add->GetMotionMaster()->MoveFollow(boss, 2.0f, M_PI / 2 + M_PI); break;
                                        }
                                    }
                                }
                            }
                        }
                        events.ScheduleEvent(8, 4000);
                        break;
                    case 8:
                        // Summon 3rd Boss and adds and make them follow him
                        if(Creature* boss = me->SummonCreature(bossEntry[2], SpawnPosition))
                        {
                            bossGUID[2] = boss->GetGUID();
                            boss->SetTarget(stalkerGUID);

                            for (uint8 i = 0; i < 3; ++i)
                            {
                                if(Creature* add = me->SummonCreature(GetAddId(boss->GetEntry()), SpawnPosition, TEMPSUMMON_MANUAL_DESPAWN))
                                {
                                    add->SetTarget(stalkerGUID);
                                    addsGUID[2][i] = add->GetGUID();
                                    switch(i)
                                    {
                                        case 0: add->GetMotionMaster()->MoveFollow(boss, 2.0f, M_PI); break;
                                        case 1: add->GetMotionMaster()->MoveFollow(boss, 2.0f, M_PI / 2); break;
                                        case 2: add->GetMotionMaster()->MoveFollow(boss, 2.0f, M_PI / 2 + M_PI); break;
                                    }
                                }
                            }
                        }
                        events.ScheduleEvent(9, 4000);
                        break;
                    case 9:
                        // Move first boss to the new position
                        if(Creature* boss1 = me->GetCreature(*me, bossGUID[0]))
                            boss1->GetMotionMaster()->MovePoint(0, IntroPosition[2]);

                        // Move second boss to the new position
                        if(Creature* boss2 = me->GetCreature(*me, bossGUID[1]))
                            boss2->GetMotionMaster()->MovePoint(0, IntroPosition[1]);

                        // Move third boss to the new position
                        if(Creature* boss2 = me->GetCreature(*me, bossGUID[2]))
                            boss2->GetMotionMaster()->MovePoint(0, IntroPosition[0]);

                        events.ScheduleEvent(10, 4000);
                        break;
                    case 10:
                        // Refresh the adds position
                        for(uint8 i=0; i<3; i++)
                        {
                            if(Creature* boss = me->GetCreature(*me, bossGUID[i]))
                            {
                                boss->SetFacingToObject(me);
                                for(uint8 j = 0; j<3; j++)
                                {
                                    if(Creature* add = me->GetCreature(*me, addsGUID[i][j]))
                                    {
                                        switch(j)
                                        {
                                            case 0: add->GetMotionMaster()->MoveFollow(boss, 2.0f, M_PI); break;
                                            case 1: add->GetMotionMaster()->MoveFollow(boss, 2.0f, M_PI / 2); break;
                                            case 2: add->GetMotionMaster()->MoveFollow(boss, 2.0f, M_PI / 2 + M_PI); break;
                                        }
                                    }
                                }
                            }
                        }
                        events.ScheduleEvent(11, 4000);
                        break;
                    case 11:
                        // Set home positions, in case of wipe, this avoids summons to go to the SpawnPos
                        for(uint8 i=0; i<3; i++)
                            if(Creature* boss = me->GetCreature(*me, bossGUID[i]))
                                boss->SetHomePosition(boss->GetPositionX(), boss->GetPositionY(), boss->GetPositionZ(), boss->GetOrientation());

                        for(uint8 i=0; i<3; i++)
                            for(uint8 j=0; j<3; j++)
                                if(Creature* add = me->GetCreature(*me, addsGUID[i][j]))
                                {
                                    add->SetFacingToObject(me);
                                    add->SetHomePosition(add->GetPositionX(), add->GetPositionY(), add->GetPositionZ(), add->GetOrientation());
                                }

                        // Move to the door position
                        me->SetUnitMovementFlags(MOVEMENTFLAG_WALKING);
                        me->GetMotionMaster()->MovePoint(0, AnnouncerPosition);
                        me->SetTarget(stalkerGUID);
                        events.ScheduleEvent(12, 19000);
                        break;
                    case 12:
                        //Close Door
                        if (GameObject* pGO = GameObject::GetGameObject(*me, pInstance->GetData64(DATA_MAIN_GATE)))
                            pInstance->HandleGameObject(pGO->GetGUID(), false);

                        events.Reset();
                        SetData(EVENT_INTRO, DONE);
                        SetData(EVENT_WAVES, IN_PROGRESS);
                        break;
                }
            }

            if(GetData(EVENT_WAVES) == IN_PROGRESS)
            {
                switch(events.ExecuteEvent())
                {
                    case 1:
                        // Future texts?
                        events.ScheduleEvent(2, 3000);
                        break;
                    case 2:
                        // Start attack of first wave of adds
                        if(!addsAttacking)
                        {
                            for(uint8 i=0; i<3; i++)
                            {
                                if(Creature* add = me->GetCreature(*me, addsGUID[0][i]))
                                {
                                    add->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                    add->SetReactState(REACT_AGGRESSIVE);
                                    add->setFaction(16);
                                    AggroAllPlayers(add);
                                }
                            }
                            addsAttacking = true;
                            events.ScheduleEvent(2, 1000);
                        } else // Wait for the death of all of them
                        {
                            defeatedCount = 0;
                            for(uint8 i=0; i<3; i++)
                                if(Creature* add = me->GetCreature(*me, addsGUID[0][i]))
                                    if(add->AI()->GetData(DATA_CHAMPION_DEFEATED) == 1)
                                        defeatedCount++;

                            if(defeatedCount>=3)
                            {
                                defeatedCount = 0;
                                addsAttacking = false;
                                events.ScheduleEvent(3, 4000);
                            } else
                                events.ScheduleEvent(2, 1000);
                        }
                        break;
                    case 3:
                        // Despawn previous wave
                        for(uint8 i=0; i<3; i++)
                            if(Creature* add = me->GetCreature(*me, addsGUID[0][i]))
                                add->DespawnOrUnsummon();

                        // Start attack of second wave of adds
                        if(!addsAttacking)
                        {
                            for(uint8 i=0; i<3; i++)
                            {
                                if(Creature* add = me->GetCreature(*me, addsGUID[1][i]))
                                {
                                    add->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                    add->SetReactState(REACT_AGGRESSIVE);
                                    add->setFaction(16);
                                    AggroAllPlayers(add);
                                }
                            }
                            addsAttacking = true;
                            events.ScheduleEvent(3, 1000);
                        } else // Wait for the death of all of them
                        {
                            defeatedCount = 0;
                            for(uint8 i=0; i<3; i++)
                                if(Creature* add = me->GetCreature(*me, addsGUID[1][i]))
                                    if(add->AI()->GetData(DATA_CHAMPION_DEFEATED) == 1)
                                        defeatedCount++;

                            if(defeatedCount>=3)
                            {
                                defeatedCount = 0;
                                addsAttacking = false;
                                events.ScheduleEvent(4, 4000);
                            } else
                                events.ScheduleEvent(3, 1000);
                        }
                        break;
                    case 4:
                        // Despawn previous wave
                        for(uint8 i=0; i<3; i++)
                            if(Creature* add = me->GetCreature(*me, addsGUID[1][i]))
                                add->DespawnOrUnsummon();

                        // Start attack of third wave of adds
                        if(!addsAttacking)
                        {
                            for(uint8 i=0; i<3; i++)
                            {
                                if(Creature* add = me->GetCreature(*me, addsGUID[2][i]))
                                {
                                    add->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                    add->SetReactState(REACT_AGGRESSIVE);
                                    add->setFaction(16);
                                    AggroAllPlayers(add);
                                }
                            }
                            addsAttacking = true;
                            events.ScheduleEvent(4, 1000);
                        } else // Wait for the death of all of them
                        {
                            defeatedCount = 0;
                            for(uint8 i=0; i<3; i++)
                                if(Creature* add = me->GetCreature(*me, addsGUID[2][i]))
                                    if(add->AI()->GetData(DATA_CHAMPION_DEFEATED) == 1)
                                        defeatedCount++;

                            if(defeatedCount>=3)
                            {
                                defeatedCount = 0;
                                addsAttacking = false;
                                events.ScheduleEvent(5, 4000);
                            } else
                                events.ScheduleEvent(4, 1000);
                        }
                        break;
                    case 5:
                        // Despawn previous wave
                        for(uint8 i=0; i<3; i++)
                            if(Creature* add = me->GetCreature(*me, addsGUID[2][i]))
                                add->DespawnOrUnsummon();

                        // Start attack of wave of bosses
                        if(!addsAttacking)
                        {
                            for(uint8 i=0; i<3; i++)
                            {
                                if(Creature* add = me->GetCreature(*me, bossGUID[i]))
                                {
                                    add->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                    add->SetReactState(REACT_AGGRESSIVE);
                                    add->setFaction(16);
                                    AggroAllPlayers(add);
                                }
                            }
                            addsAttacking = true;
                            events.ScheduleEvent(5, 1000);
                        } else // Wait for the death of all of them
                        {
                            defeatedCount = 0;
                            for(uint8 i=0; i<3; i++)
                                if(Creature* add = me->GetCreature(*me, bossGUID[i]))
                                    if(add->AI()->GetData(DATA_CHAMPION_DEFEATED) == 1)
                                        defeatedCount++;

                            if(defeatedCount>=3)
                            {
                                defeatedCount = 0;
                                addsAttacking = false;
                                events.ScheduleEvent(6, 0);
                            } else
                                events.ScheduleEvent(5, 1000);
                        }
                        break;
                    case 6:
                        // Despawn boss wave
                        for(uint8 i=0; i<3; i++)
                            if(Creature* add = me->GetCreature(*me, bossGUID[i]))
                                add->DespawnOrUnsummon();

                        events.Reset();
                        SetData(EVENT_WAVES, DONE);
                        SetData(EVENT_CHAMPIONS, IN_PROGRESS);
                        pInstance->SetData(DATA_LESSER_CHAMPIONS_DEFEATED, DONE);
                        break;
                }
            }

            if(GetData(EVENT_CHAMPIONS) == IN_PROGRESS)
            {
                switch(events.ExecuteEvent())
                {
                    case 1:
                        AreAllPlayersMounted(true);
                        events.ScheduleEvent(2, 0);
                        break;
                    case 2:
                        for(uint8 i=0; i<3; i++)
                        {
                            if(Creature* boss = me->SummonCreature(GetRealBossEntry(bossEntry[i]), SpawnPosition))
                            {
                                bossEntry[i] = boss->GetEntry();
                                bossGUID[i] = boss->GetGUID();
                                boss->SetTarget(stalkerGUID);
                                // Prevent bosses from falling down the ground
                                boss->SetPosition(boss->GetPositionX(), boss->GetPositionY(), boss->GetPositionZ()+0.1f, boss->GetOrientation());
                                // Set positions
                                switch(i)
                                {
                                    case 1: boss->GetMotionMaster()->MoveFollow(me->GetCreature(*me, bossGUID[0]), 5.0f, (M_PI / 2) + 0.5f); break;
                                    case 2: boss->GetMotionMaster()->MoveFollow(me->GetCreature(*me, bossGUID[0]), 5.0f, (M_PI / 2 + M_PI) - 0.5f); break;
                                }
                            }
                        }
                        events.ScheduleEvent(3, 2000);
                        break;
                    case 3:
                        for(uint8 i=0; i<3; i++)
                            if(Creature* boss = me->GetCreature(*me, bossGUID[i]))
                            {
                                boss->SetFacingToObject(me);
                                boss->SetHomePosition(boss->GetPositionX(), boss->GetPositionY(), boss->GetPositionZ() + 1.0f, boss->GetOrientation());
                                boss->SetReactState(REACT_AGGRESSIVE);
                                boss->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_OOC_NOT_ATTACKABLE);
                            }
                        events.ScheduleEvent(4, 10000);
                        break;
                    case 4: // Wait for the death of all of them
                        defeatedCount = 0;
                        for(uint8 i=0; i<3; i++)
                            if(Creature* boss = me->GetCreature(*me, bossGUID[i]))
                                if(boss->AI()->GetData(DATA_CHAMPION_DEFEATED) == 1)
                                    defeatedCount++;

                        if(defeatedCount>=3)
                        {
                            defeatedCount = 0;
                            addsAttacking = false;
                            events.ScheduleEvent(5, 0);
                        } else
                            events.ScheduleEvent(4, 1000);
                        break;
                    case 5:
                        for(uint8 i=0; i<3; i++)
                            if(Creature* boss = me->GetCreature(*me, bossGUID[i]))
                            {
                                boss->GetMotionMaster()->MovePoint(0, OutStadiumPosition);
                                boss->DespawnOrUnsummon(4000);
                            }
                        pInstance->SetData(BOSS_GRAND_CHAMPIONS, DONE);
                        break;
                }
            }
        }

        void AggroAllPlayers(Creature* creature)
        {
            Map::PlayerList const &PlList = me->GetMap()->GetPlayers();

            if (PlList.isEmpty())
                return;

            for (Map::PlayerList::const_iterator i = PlList.begin(); i != PlList.end(); ++i)
            {
                if (Player* player = i->getSource())
                {
                    if (player->isGameMaster())
                        continue;

                    if (player->isAlive())
                    {
                        if(Unit* mount = player->GetVehicleBase())
                        {
                            creature->SetInCombatWith(mount);
                            mount->SetInCombatWith(creature);
                            creature->AddThreat(mount, 0.0f);
                        }
                        else
                        {
                            creature->SetInCombatWith(player);
                            player->SetInCombatWith(creature);
                            creature->AddThreat(player, 0.0f);
                        }
                    }
                }
            }
        }

        /**
        Used for checking if players are mounted before starting gauntlet
        and teleporting and unmounting them after defeating the mounted waves.
        */
        bool AreAllPlayersMounted(bool dismountAndTeleport = false)
        {
            Map::PlayerList const &PlList = me->GetMap()->GetPlayers();

            if (PlList.isEmpty())
                return false;

            for (Map::PlayerList::const_iterator i = PlList.begin(); i != PlList.end(); ++i)
                if (Player* player = i->getSource())
                {
                    if (player->isGameMaster())
                        continue;

                    if (player->isAlive())
                    {
                        if(Creature* mount = player->GetVehicleCreatureBase())
                        {
                            if(dismountAndTeleport)
                            {
                                player->ExitVehicle();
                                mount->DespawnOrUnsummon();
                            }
                        } else if(!dismountAndTeleport)
                            return false;

                        if(dismountAndTeleport)
                            player->NearTeleportTo(746.851f, 608.875f, 411.172f, 1.60308f);
                    }
                }

            return true;
            //if(dismountAndTeleport)
                //TODO: set all vehicles in dungeon as not selectable
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_announcer_toc5AI(creature);
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        InstanceScript* pInstance = creature->GetInstanceScript();

        if(pInstance->GetData(BOSS_GRAND_CHAMPIONS) != DONE)
        {
            if(CAST_AI(npc_announcer_toc5::npc_announcer_toc5AI, creature->AI())->AreAllPlayersMounted())
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_START_EVENT1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        }//else if
        //if (pInstance &&
        //    ((pInstance->GetData(BOSS_GRAND_CHAMPIONS) == DONE &&
        //    pInstance->GetData(BOSS_BLACK_KNIGHT) == DONE &&
        //    pInstance->GetData(BOSS_ARGENT_CHALLENGE_E) == DONE) ||
        //    pInstance->GetData(BOSS_ARGENT_CHALLENGE_P) == DONE))
        //    return false;

        //if (pInstance &&
        //    pInstance->GetData(BOSS_GRAND_CHAMPIONS) == NOT_STARTED &&
        //    pInstance->GetData(BOSS_ARGENT_CHALLENGE_E) == NOT_STARTED &&
        //    pInstance->GetData(BOSS_ARGENT_CHALLENGE_P) == NOT_STARTED &&
        //    pInstance->GetData(BOSS_BLACK_KNIGHT) == NOT_STARTED)
        //    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_START_EVENT1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        //else if (pInstance)
        //    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_START_EVENT2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
    {
        player->PlayerTalkClass->ClearMenus();
        if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
        {
            if(creature->AI()->GetData(EVENT_INTRO) != IN_PROGRESS)
            {
                creature->AI()->SetData(EVENT_INTRO, IN_PROGRESS);
                creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                player->CLOSE_GOSSIP_MENU();
            }
        }

        return true;
    }
};

void AddSC_trial_of_the_champion()
{
    new npc_announcer_toc5();
}
