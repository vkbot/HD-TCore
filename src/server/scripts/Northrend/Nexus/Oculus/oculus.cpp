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

#include "ScriptPCH.h"
#include "oculus.h"

#define GOSSIP_ITEM_DRAKES         "So where do we go from here?"
#define GOSSIP_ITEM_BELGARISTRASZ1 "I want to fly on the wings of the Red Flight"
#define GOSSIP_ITEM_BELGARISTRASZ2 "What abilities do Ruby Drakes have?"
#define GOSSIP_ITEM_VERDISA1       "I want to fly on the wings of the Green Flight"
#define GOSSIP_ITEM_VERDISA2       "What abilities do Emerald Drakes have?"
#define GOSSIP_ITEM_ETERNOS1       "I want to fly on the wings of the Bronze Flight"
#define GOSSIP_ITEM_ETERNOS2       "What abilities do Amber Drakes have?"

#define HAS_ESSENCE(a) ((a)->HasItemCount(ITEM_EMERALD_ESSENCE, 1) || (a)->HasItemCount(ITEM_AMBER_ESSENCE, 1) || (a)->HasItemCount(ITEM_RUBY_ESSENCE, 1))

enum Drakes
{
    GOSSIP_TEXTID_DRAKES                          = 13267,
    GOSSIP_TEXTID_BELGARISTRASZ1                  = 12916,
    GOSSIP_TEXTID_BELGARISTRASZ2                  = 13466,
    GOSSIP_TEXTID_BELGARISTRASZ3                  = 13254,
    GOSSIP_TEXTID_VERDISA1                        = 1,
    GOSSIP_TEXTID_VERDISA2                        = 1,
    GOSSIP_TEXTID_VERDISA3                        = 1,
    GOSSIP_TEXTID_ETERNOS1                        = 1,
    GOSSIP_TEXTID_ETERNOS2                        = 1,
    GOSSIP_TEXTID_ETERNOS3                        = 13256,

    ITEM_EMERALD_ESSENCE                          = 37815,
    ITEM_AMBER_ESSENCE                            = 37859,
    ITEM_RUBY_ESSENCE                             = 37860,

    NPC_VERDISA                                   = 27657,
    NPC_BELGARISTRASZ                             = 27658,
    NPC_ETERNOS                                   = 27659
};

class npc_oculus_drake : public CreatureScript
{
public:
    npc_oculus_drake() : CreatureScript("npc_oculus_drake") { }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
    {
        player->PlayerTalkClass->ClearMenus();
        switch(creature->GetEntry())
        {
        case NPC_VERDISA: //Verdisa
            switch(uiAction)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:
                if (!HAS_ESSENCE(player))
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_VERDISA1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_VERDISA2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                    player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_VERDISA1, creature->GetGUID());
                }
                else
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_VERDISA2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                    player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_VERDISA2, creature->GetGUID());
                }
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
            {
                player->AddItem(ITEM_EMERALD_ESSENCE, 1);
                player->CLOSE_GOSSIP_MENU();
                break;
            }
            case GOSSIP_ACTION_INFO_DEF + 3:
                player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_VERDISA3, creature->GetGUID());
                break;
            }
            break;
        case NPC_BELGARISTRASZ: //Belgaristrasz
            switch(uiAction)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:
                if (!HAS_ESSENCE(player))
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_BELGARISTRASZ1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_BELGARISTRASZ2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                    player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_BELGARISTRASZ1, creature->GetGUID());
                }
                else
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_BELGARISTRASZ2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                    player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_BELGARISTRASZ2, creature->GetGUID());
                }
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
            {
                player->AddItem(ITEM_RUBY_ESSENCE, 1);
                player->CLOSE_GOSSIP_MENU();
                break;
            }
            case GOSSIP_ACTION_INFO_DEF + 3:
                player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_BELGARISTRASZ3, creature->GetGUID());
                break;
            }
            break;
        case NPC_ETERNOS: //Eternos
            switch(uiAction)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:
                if (!HAS_ESSENCE(player))
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_ETERNOS1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_ETERNOS2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                    player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ETERNOS1, creature->GetGUID());
                }
                else
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_ETERNOS2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                    player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ETERNOS2, creature->GetGUID());
                }
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
            {
                player->AddItem(ITEM_AMBER_ESSENCE, 1);
                player->CLOSE_GOSSIP_MENU();
                break;
            }
            case GOSSIP_ACTION_INFO_DEF + 3:
                player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ETERNOS3, creature->GetGUID());
                break;
            }
            break;
        }

        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->isQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (InstanceScript* instance = creature->GetInstanceScript())
        {
            if (instance->GetBossState(DATA_DRAKOS_EVENT) == DONE)
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_DRAKES, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_DRAKES, creature->GetGUID());
            }
        }

        return true;
    }

};

/*
Trash mobs before Drakos are scripted here because
we need to check if attackers are mounted, if they
do, mobs will enter in evade mode.
*/
enum trashSpells
{
    // Centrifuge Constructs
    SPELL_EMPOWERING_BLOWS   = 50044,
    H_SPELL_EMPOWERING_BLOWS = 59213,

    // Ring-Lord Conjurer
    SPELL_CHARGED_SKIN       = 50717,
    H_SPELL_CHARGED_SKIN     = 59276,

    // Ring-Lord Sorceress
    SPELL_BLIZZARD           = 50175,
    H_SPELL_BLIZZARD         = 59278,
    SPELL_FLAMESTRIKE        = 16102,
    H_SPELL_FLAMESTRIKE      = 61402,

    // Greater Ley-Whelp
    SPELL_ARCANE_BOLT        = 62249,
    H_SPELL_ARCANE_BOLT      = 62250,

    // Azure ring guardian
    SPELL_ICE_BEAM           = 49549,
    H_SPELL_ICE_BEAM         = 59211,
};

class npc_centrifuge_construct : public CreatureScript
{
public:
    npc_centrifuge_construct() : CreatureScript("npc_centrifuge_construct") { }

    struct npc_centrifuge_constructAI : public ScriptedAI
    {
        npc_centrifuge_constructAI(Creature *creature) : ScriptedAI(creature) {}


        void Reset() {}

        void EnterCombat(Unit* who)
        {
            if(AttackersAreMounted())
                EnterEvadeMode();

            DoCast(IsHeroic() ? H_SPELL_EMPOWERING_BLOWS : SPELL_EMPOWERING_BLOWS);
        }

        void UpdateAI(const uint32 uiDiff)
        {
            if(!UpdateVictim())
                return;

            if(AttackersAreMounted())
            {
                EnterEvadeMode();
                return;
            }

            DoMeleeAttackIfReady();
        }

        bool AttackersAreMounted()
        {
           std::list<HostileReference*>::const_iterator i = me->getThreatManager().getThreatList().begin();
            for (; i != me->getThreatManager().getThreatList().end(); ++i)
            {
                Unit* target = (*i)->getTarget();
                if(Creature* drake = target->GetVehicleCreatureBase())
                    return true;
            }
            return false;
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_centrifuge_constructAI(creature);
    }
};

class npc_ringlord_conjurer : public CreatureScript
{
public:
    npc_ringlord_conjurer() : CreatureScript("npc_ringlord_conjurer") { }

    struct npc_ringlord_conjurerAI : public ScriptedAI
    {
        npc_ringlord_conjurerAI(Creature *creature) : ScriptedAI(creature) {}


        void Reset() {}

        void EnterCombat(Unit* who)
        {
            if(AttackersAreMounted())
                EnterEvadeMode();

            DoCast(IsHeroic() ? H_SPELL_CHARGED_SKIN : SPELL_CHARGED_SKIN);
        }

        void UpdateAI(const uint32 uiDiff)
        {
            if(!UpdateVictim())
                return;

            if(AttackersAreMounted())
            {
                EnterEvadeMode();
                return;
            }

            if(me->HealthBelowPct(15))
                me->DoFleeToGetAssistance();

            if(!(me->HasAura(IsHeroic() ? H_SPELL_CHARGED_SKIN : SPELL_CHARGED_SKIN)))
                DoCast(IsHeroic() ? H_SPELL_CHARGED_SKIN : SPELL_CHARGED_SKIN);

            DoMeleeAttackIfReady();
        }

        bool AttackersAreMounted()
        {
           std::list<HostileReference*>::const_iterator i = me->getThreatManager().getThreatList().begin();
            for (; i != me->getThreatManager().getThreatList().end(); ++i)
            {
                Unit* target = (*i)->getTarget();
                if(Creature* drake = target->GetVehicleCreatureBase())
                    return true;
            }
            return false;
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ringlord_conjurerAI(creature);
    }
};

class npc_ringlord_sorceress : public CreatureScript
{
public:
    npc_ringlord_sorceress() : CreatureScript("npc_ringlord_sorceress") { }

    struct npc_ringlord_sorceressAI : public ScriptedAI
    {
        npc_ringlord_sorceressAI(Creature *creature) : ScriptedAI(creature) {}


        bool chasing;
        void Reset() {}

        void EnterCombat(Unit* who)
        {
            if(AttackersAreMounted())
                EnterEvadeMode();

            ChaseVictim(false);
        }

        void UpdateAI(const uint32 uiDiff)
        {
            if(!UpdateVictim())
                return;

            if(AttackersAreMounted())
            {
                EnterEvadeMode();
                return;
            }

            if(me->HasUnitState(UNIT_STAT_CASTING))
                return;

            if(((double) me->GetPower(POWER_MANA)/(double) me->GetMaxPower(POWER_MANA))*100 <= 5) // Mana below 5
            {
                if(!chasing)
                    ChaseVictim(true);
                DoMeleeAttackIfReady();
            }
            else
            {
                if(chasing)
                    ChaseVictim(false);

                if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                    DoCast(target, RAND(IsHeroic() ? H_SPELL_BLIZZARD : SPELL_BLIZZARD, IsHeroic() ? H_SPELL_FLAMESTRIKE : SPELL_FLAMESTRIKE));
            }

        }

        void ChaseVictim(bool on)
        {
            if (on)
                me->GetMotionMaster()->MoveChase(me->getVictim());
            else
                me->GetMotionMaster()->MoveIdle();

            chasing = on;

        }
        bool AttackersAreMounted()
        {
           std::list<HostileReference*>::const_iterator i = me->getThreatManager().getThreatList().begin();
            for (; i != me->getThreatManager().getThreatList().end(); ++i)
            {
                Unit* target = (*i)->getTarget();
                if(Creature* drake = target->GetVehicleCreatureBase())
                    return true;
            }
            return false;
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ringlord_sorceressAI(creature);
    }
};

class npc_greater_ley_whelp : public CreatureScript
{
public:
    npc_greater_ley_whelp() : CreatureScript("npc_greater_ley_whelp") { }

    struct npc_greater_ley_whelpAI : public ScriptedAI
    {
        npc_greater_ley_whelpAI(Creature *creature) : ScriptedAI(creature) {}

        uint32 boltTimer;
        void Reset()
        {
            boltTimer = urand(3000, 6000);
            me->SetFlying(true);
            me->SetSpeed(MOVE_FLIGHT, 2.1f);
        }

        void UpdateAI(const uint32 diff)
        {
            if(!UpdateVictim())
                return;

            if(boltTimer <= diff)
            {
                if(Unit* target = this->SelectTarget(SELECT_TARGET_TOPAGGRO))
                    if(Unit* drake = target->GetVehicleBase())
                        DoCast(drake, IsHeroic() ? H_SPELL_ARCANE_BOLT : SPELL_ARCANE_BOLT);
                    else
                        DoCast(target, IsHeroic() ? H_SPELL_ARCANE_BOLT : SPELL_ARCANE_BOLT);
                boltTimer = urand(5000, 8000);
            }
            else boltTimer -= diff;

            DoMeleeAttackIfReady();
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_greater_ley_whelpAI(creature);
    }
};

class npc_azure_ring_guardian : public CreatureScript
{
public:
    npc_azure_ring_guardian() : CreatureScript("npc_azure_ring_guardian") { }

    struct npc_azure_ring_guardianAI : public ScriptedAI
    {
        npc_azure_ring_guardianAI(Creature *creature) : ScriptedAI(creature) {}

        uint32 boltTimer;
        void Reset()
        {
            boltTimer = urand(6000, 12000);
            me->SetFlying(true);
            me->SetSpeed(MOVE_FLIGHT, 3.1f);
        }

        void UpdateAI(const uint32 diff)
        {
            if(!UpdateVictim())
                return;

            if(boltTimer <= diff)
            {
                if(Unit* target = this->SelectTarget(SELECT_TARGET_TOPAGGRO))
                    if(Unit* drake = target->GetVehicleBase())
                        DoCast(drake, IsHeroic() ? H_SPELL_ICE_BEAM : SPELL_ICE_BEAM);
                    else
                        DoCast(target, IsHeroic() ? H_SPELL_ICE_BEAM : SPELL_ICE_BEAM);

                boltTimer = urand(6000, 12000);
            }
            else boltTimer -= diff;

            DoMeleeAttackIfReady();
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_azure_ring_guardianAI(creature);
    }
};

void AddSC_oculus()
{
    new npc_oculus_drake();
    new npc_centrifuge_construct();
    new npc_ringlord_conjurer();
    new npc_ringlord_sorceress();
    new npc_greater_ley_whelp();
    new npc_azure_ring_guardian();
}
