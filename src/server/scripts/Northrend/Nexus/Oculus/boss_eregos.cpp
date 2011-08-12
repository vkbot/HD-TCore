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

//Types of drake mounts: Ruby(Tank),  Amber(DPS),  Emerald(Healer)
//Two Repeating phases

enum Events
{
    EVENT_ARCANE_BARRAGE = 1,
    EVENT_ARCANE_VOLLEY,
    EVENT_ENRAGED_ASSAULT,
    EVENT_SUMMON_LEY_WHELP
};

enum Says
{
    SAY_SPAWN  = -1578022,
    SAY_AGGRO  = -1578023,
    SAY_ENRAGE = -1578024,
    SAY_KILL_1 = -1578025,
    SAY_KILL_2 = -1578026,
    SAY_KILL_3 = -1578027,
    SAY_DEATH  = -1578028,
};

enum Spells
{
    SPELL_ARCANE_BARRAGE                          = 50804,
    SPELL_ARCANE_VOLLEY                           = 51153,
    SPELL_ENRAGED_ASSAULT                         = 51170,
    SPELL_PLANAR_ANOMALIES                        = 57959,
    SPELL_PLANAR_SHIFT                            = 51162,
    SPELL_SUMMON_LEY_WHELP                        = 51175,
};

enum Npcs
{
    NPC_PLANAR_ANOMALY = 30879
};

enum Phases
{
    PHASE_NORMAL = 1,
    PHASE_FIRST_PLANAR = 2,
    PHASE_SECOND_PLANAR = 3
};

enum Actions
{
    ACTION_SET_NORMAL_EVENTS = 1
};

/*Ruby Drake ,
(npc 27756) (item 37860)
(summoned by spell Ruby Essence = 37860 ---> Call Amber Drake == 49462 ---> Summon 27756)
*/
enum RubyDrake
{
    NPC_RUBY_DRAKE_VEHICLE                        = 27756,
    SPELL_RIDE_RUBY_DRAKE_QUE                     = 49463,          //Apply Aura: Periodic Trigger, Interval: 3 seconds ---> 49464
    SPELL_RUBY_DRAKE_SADDLE                       = 49464,          //Allows you to ride on the back of an Amber Drake. ---> Dummy
    SPELL_RUBY_SEARING_WRATH                      = 50232,          //(60 yds) - Instant - Breathes a stream of fire at an enemy dragon, dealing 6800 to 9200 Fire damage and then jumping to additional dragons within 30 yards. Each jump increases the damage by 50%. Affects up to 5 total targets
    SPELL_RUBY_EVASIVE_AURA                       = 50248,          //Instant - Allows the Ruby Drake to generate Evasive Charges when hit by hostile attacks and spells.
    SPELL_RUBY_EVASIVE_MANEUVERS                  = 50240,          //Instant - 5 sec. cooldown - Allows your drake to dodge all incoming attacks and spells. Requires Evasive Charges to use. Each attack or spell dodged while this ability is active burns one Evasive Charge. Lasts 30 sec. or until all charges are exhausted.
    //you do not have acces to until you kill Mage-Lord Urom
    SPELL_RUBY_MARTYR                             = 50253,          //Instant - 10 sec. cooldown - Redirect all harmful spells cast at friendly drakes to yourself for 10 sec.
    SPELL_DRAKE_FLAG_VISUAl                       = 53797,
};
/*Amber Drake,
(npc 27755)  (item 37859)
(summoned by spell Amber Essence = 37859 ---> Call Amber Drake == 49461 ---> Summon 27755)
*/
enum AmberDrake
{
    NPC_AMBER_DRAKE_VEHICLE                       = 27755,
    SPELL_RIDE_AMBER_DRAKE_QUE                    = 49459,          //Apply Aura: Periodic Trigger, Interval: 3 seconds ---> 49460
    SPELL_AMBER_DRAKE_SADDLE                      = 49460,          //Allows you to ride on the back of an Amber Drake. ---> Dummy
    SPELL_AMBER_SHOCK_LANCE                       = 49840,         //(60 yds) - Instant - Deals 4822 to 5602 Arcane damage and detonates all Shock Charges on an enemy dragon. Damage is increased by 6525 for each detonated.
    SPELL_SHOCK_CHARGE                            = 49836,
//  SPELL_AMBER_STOP_TIME                                    //Instant - 1 min cooldown - Halts the passage of time, freezing all enemy dragons in place for 10 sec. This attack applies 5 Shock Charges to each affected target.
    //you do not have access to until you kill the  Mage-Lord Urom.
    SPELL_AMBER_TEMPORAL_RIFT                     = 49592         //(60 yds) - Channeled - Channels a temporal rift on an enemy dragon for 10 sec. While trapped in the rift, all damage done to the target is increased by 100%. In addition, for every 15, 000 damage done to a target affected by Temporal Rift, 1 Shock Charge is generated.
};

/*Emerald Drake,
(npc 27692)  (item 37815),
 (summoned by spell Emerald Essence = 37815 ---> Call Emerald Drake == 49345 ---> Summon 27692)
*/
enum EmeraldDrake
{
    NPC_EMERALD_DRAKE_VEHICLE                     = 27692,
    SPELL_RIDE_EMERALD_DRAKE_QUE                  = 49427,         //Apply Aura: Periodic Trigger, Interval: 3 seconds ---> 49346
    SPELL_EMERALD_DRAKE_SADDLE                    = 49346,         //Allows you to ride on the back of an Amber Drake. ---> Dummy
    SPELL_EMERALD_LEECHING_POISON                 = 50328,         //(60 yds) - Instant - Poisons the enemy dragon, leeching 1300 to the caster every 2 sec. for 12 sec. Stacks up to 3 times.
    SPELL_EMERALD_TOUCH_THE_NIGHTMARE             = 50341,         //(60 yds) - Instant - Consumes 30% of the caster's max health to inflict 25, 000 nature damage to an enemy dragon and reduce the damage it deals by 25% for 30 sec.
    // you do not have access to until you kill the Mage-Lord Urom
    SPELL_EMERALD_DREAM_FUNNEL                    = 50344         //(60 yds) - Channeled - Transfers 5% of the caster's max health to a friendly drake every second for 10 seconds as long as the caster channels.
};

#define DATA_EMERALD_VOID  0
#define DATA_RUBY_VOID     1
#define DATA_AMBER_VOID    2

class boss_eregos : public CreatureScript
{
public:
    boss_eregos() : CreatureScript("boss_eregos") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_eregosAI (creature);
    }

    struct boss_eregosAI : public BossAI
    {
        boss_eregosAI(Creature* creature) : BossAI(creature, DATA_EREGOS_EVENT) 
        {
            pInstance = creature->GetInstanceScript();
        }

        InstanceScript* pInstance;

        void Reset()
        {
            _Reset();

            phase = PHASE_NORMAL;

            me->SetSpeed(MOVE_FLIGHT, 2.8f);
            DoAction(ACTION_SET_NORMAL_EVENTS);
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();

            DoScriptText(SAY_AGGRO, me);
        }

        void DoAction(const int32 action)
        {
            if (action != ACTION_SET_NORMAL_EVENTS)
                return;

            events.ScheduleEvent(EVENT_ARCANE_BARRAGE, urand(3, 10) * IN_MILLISECONDS, 0, PHASE_NORMAL);
            events.ScheduleEvent(EVENT_ARCANE_VOLLEY, urand(10, 25) * IN_MILLISECONDS, 0, PHASE_NORMAL);
            events.ScheduleEvent(EVENT_ENRAGED_ASSAULT, urand(35, 50) * IN_MILLISECONDS, 0, PHASE_NORMAL);
            events.ScheduleEvent(EVENT_SUMMON_LEY_WHELP, urand(15, 30) * IN_MILLISECONDS, 0, PHASE_NORMAL);
        }


        void DamageTaken(Unit* /*attacker*/, uint32& /*damage*/)
        {
            if (!me->GetMap()->IsHeroic())
                return;

            if ((me->HealthBelowPct(60) && me->HealthAbovePct(20) && phase < PHASE_FIRST_PLANAR) ||
                (me->HealthBelowPct(20) && phase < PHASE_SECOND_PLANAR))
            {
                events.Reset();
                phase = (me->HealthBelowPct(60)  && me->HealthAbovePct(20)) ? PHASE_FIRST_PLANAR : PHASE_SECOND_PLANAR;
                // Planar anomalies are summoned on SpellScript
                DoCast(SPELL_PLANAR_SHIFT);
            }
        }

        void UpdateAI(const uint32 diff)
        {
            //Return since we have no target
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STAT_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_ARCANE_BARRAGE:
                        DoCast(me->getVictim(), SPELL_ARCANE_BARRAGE);
                        events.ScheduleEvent(EVENT_ARCANE_BARRAGE, urand(3, 10) * IN_MILLISECONDS, 0, PHASE_NORMAL);
                        break;
                    case EVENT_ARCANE_VOLLEY:
                        DoCastAOE(SPELL_ARCANE_VOLLEY);
                        events.ScheduleEvent(EVENT_ARCANE_VOLLEY, urand(10, 25) * IN_MILLISECONDS, 0, PHASE_NORMAL);
                        break;
                    case EVENT_ENRAGED_ASSAULT:
                        DoScriptText(SAY_ENRAGE, me);
                        DoCast(SPELL_ENRAGED_ASSAULT);
                        events.ScheduleEvent(EVENT_ENRAGED_ASSAULT, urand(35, 50) * IN_MILLISECONDS, 0, PHASE_NORMAL);
                        break;
                    case EVENT_SUMMON_LEY_WHELP:
                        for (uint8 i = 0; i < 3; i++)
                            DoCast(SPELL_SUMMON_LEY_WHELP);
                        events.ScheduleEvent(EVENT_SUMMON_LEY_WHELP, urand(15, 30) * IN_MILLISECONDS, 0, PHASE_NORMAL);
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

        uint32 GetData(uint32 type)
        {
            switch(type)
            {
                case DATA_AMBER_VOID:
                    return bWereAmberDrakes ? 0 : 1;
                case DATA_EMERALD_VOID:
                    return bWereEmeraldDrakes ? 0 : 1;
                case DATA_RUBY_VOID:
                    return bWereRubyDrakes ? 0 : 1;
            }

            return 0;
        }

        void KilledUnit(Unit* /*victim*/)
        {
            DoScriptText(RAND(SAY_KILL_1, SAY_KILL_2, SAY_KILL_3), me);
        }

        void JustDied(Unit* /*killer*/)
        {
            DoScriptText(SAY_DEATH, me);

            //Achievements
            bWereRubyDrakes = false;
            bWereEmeraldDrakes = false;
            bWereAmberDrakes = false;

            if (IsHeroic())
            {
                Map::PlayerList const &players = pInstance->instance->GetPlayers();
                for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                {
                    // Check every player's drake for void achievements
                    if (Unit* drake = itr->getSource()->GetVehicleBase())
                    {
                        switch(drake->GetEntry())
                        {
                            case NPC_AMBER_DRAKE_VEHICLE:
                                bWereAmberDrakes = true;
                                break;
                            case NPC_RUBY_DRAKE_VEHICLE:
                                bWereRubyDrakes = true;
                                break;
                            case NPC_EMERALD_DRAKE_VEHICLE:
                                bWereEmeraldDrakes = true;
                                break;
                            default:
                                break;
                        }
                    }
                }
            }

            _JustDied();
        }

    private:
        uint8 phase;
        bool bWereRubyDrakes;
        bool bWereEmeraldDrakes;
        bool bWereAmberDrakes;
    };
};

enum AnomalySpells
{
    SPELL_PLANAR_BLAST      = 57976, // Final damage spell
    SPELL_PLANAR_DISTORTION = 59379, // Periodic damage aura
    SPELL_PLANAR_SPARK      = 57971, // Visual
};

class mob_planar_anomaly : public CreatureScript
{
public:
    mob_planar_anomaly() : CreatureScript("mob_planar_anomaly") { }

    struct mob_planar_anomalyAI : public ScriptedAI
    {
        mob_planar_anomalyAI(Creature *creature) : ScriptedAI(creature) {}

        uint32 uiBlastTimer;

        void Reset()
        {
            uiBlastTimer = 16000;
            me->SetFlying(true);
            me->SetSpeed(MOVE_FLIGHT, 2.1f);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE);
            me->AddAura(SPELL_PLANAR_DISTORTION, me);
            me->AddAura(SPELL_PLANAR_SPARK, me);
            me->DespawnOrUnsummon(18000);
        }

        void UpdateAI(const uint32 uiDiff)
        {
            if(!UpdateVictim())
                return;

            if(uiBlastTimer && uiBlastTimer <= uiDiff)
            {
                DoCastAOE(SPELL_PLANAR_BLAST, true);
                uiBlastTimer = 0;
            }
            else
                uiBlastTimer -= uiDiff;
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_planar_anomalyAI(creature);
    }
};

class spell_eregos_planar_shift : public SpellScriptLoader
{
    public:
        spell_eregos_planar_shift() : SpellScriptLoader("spell_eregos_planar_shift") { }

        class spell_eregos_planar_shift_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_eregos_planar_shift_AuraScript);

            void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                    if (Creature* creatureCaster = caster->ToCreature())
                        if(InstanceScript* instance = caster->GetInstanceScript())
                        {
                            Map::PlayerList const &players = instance->instance->GetPlayers();
                            for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                                if (Player* player = itr->getSource())
                                    if(Creature* anomaly = player->SummonCreature(NPC_PLANAR_ANOMALY, player->GetPositionX() + urand(5, 10), player->GetPositionY() + urand(5, 10), player->GetPositionZ()))
                                        anomaly->GetMotionMaster()->MoveChase(player);
                        }
            }

            void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                    if (Creature* creatureCaster = caster->ToCreature())
                        creatureCaster->AI()->DoAction(ACTION_SET_NORMAL_EVENTS);
            }

            void Register()
            {
                AfterEffectApply += AuraEffectApplyFn(spell_eregos_planar_shift_AuraScript::OnApply, EFFECT_0, SPELL_AURA_SCHOOL_IMMUNITY, AURA_EFFECT_HANDLE_REAL);
                AfterEffectRemove += AuraEffectRemoveFn(spell_eregos_planar_shift_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_SCHOOL_IMMUNITY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_eregos_planar_shift_AuraScript();
        }
};

class achievement_amber_void : public AchievementCriteriaScript
{
    public:
        achievement_amber_void() : AchievementCriteriaScript("achievement_amber_void") {}

        bool OnCheck(Player* player, Unit* target)
        {
            if (!target || !player)
                return false;

            if (Creature* eregos = target->ToCreature())
                if (eregos->AI()->GetData(DATA_AMBER_VOID))
                    return true;

            return false;
        }
};

class achievement_amber_drake_rider : public AchievementCriteriaScript
{
    public:
        achievement_amber_drake_rider() : AchievementCriteriaScript("achievement_amber_drake_rider") {}

        bool OnCheck(Player* player, Unit* target)
        {
            if (!target || !player)
                return false;

            if (Unit* drake = player->GetVehicleBase())
                if (drake->GetEntry() == NPC_AMBER_DRAKE_VEHICLE)
                    return true;

            return false;
        }
};

class achievement_ruby_void : public AchievementCriteriaScript
{
    public:
        achievement_ruby_void() : AchievementCriteriaScript("achievement_ruby_void") {}

        bool OnCheck(Player* player, Unit* target)
        {
            if (!target || !player)
                return false;

            if (Creature* eregos = target->ToCreature())
                if (eregos->AI()->GetData(DATA_RUBY_VOID))
                    return true;

            return false;
        }
};

class achievement_ruby_drake_rider : public AchievementCriteriaScript
{
    public:
        achievement_ruby_drake_rider() : AchievementCriteriaScript("achievement_ruby_drake_rider") {}

        bool OnCheck(Player* player, Unit* target)
        {
            if (!target || !player)
                return false;

            if (Unit* drake = player->GetVehicleBase())
                if (drake->GetEntry() == NPC_RUBY_DRAKE_VEHICLE)
                    return true;

            return false;
        }
};

class achievement_emerald_void : public AchievementCriteriaScript
{
    public:
        achievement_emerald_void() : AchievementCriteriaScript("achievement_emerald_void") {}

        bool OnCheck(Player* player, Unit* target)
        {
            if (!target || !player)
                return false;

            if (Creature* eregos = target->ToCreature())
                if (eregos->AI()->GetData(DATA_EMERALD_VOID))
                    return true;

            return false;
        }
};

class achievement_emerald_drake_rider : public AchievementCriteriaScript
{
    public:
        achievement_emerald_drake_rider() : AchievementCriteriaScript("achievement_emerald_drake_rider") {}

        bool OnCheck(Player* player, Unit* target)
        {
            if (!target || !player)
                return false;

            if (Unit* drake = player->GetVehicleBase())
                if (drake->GetEntry() == NPC_EMERALD_DRAKE_VEHICLE)
                    return true;

            return false;
        }
};

class spell_oculus_shock_lance : public SpellScriptLoader
{
    public:
        spell_oculus_shock_lance() : SpellScriptLoader("spell_oculus_shock_lance") {}

        class spell_oculus_shock_lanceSpellScript : public SpellScript
        {
            PrepareSpellScript(spell_oculus_shock_lanceSpellScript)

            void HandleBeforeHit()
            {
                // Modify the damage acording to the number of charges
                uint32 damage = GetHitDamage();
                uint32 damageFromCharges = 0;

                if(Aura* shockCharges = GetTargetUnit()->GetAura(SPELL_SHOCK_CHARGE, GetCaster()->GetGUID()))
                {
                    uint32 baseDamage = shockCharges->GetSpellInfo()->Effects[0].BasePoints;
                    uint32 chargeNumber = shockCharges->GetStackAmount();
                    damageFromCharges = baseDamage*chargeNumber;
                }

                damage += damageFromCharges;
                SetHitDamage(damage);

            }

            void HandleAfterHit()
            {
                // Remove auras after the hit
                if(Aura* shockCharges = GetTargetUnit()->GetAura(SPELL_SHOCK_CHARGE, GetCaster()->GetGUID()))
                    shockCharges->Remove();
            }
            void Register()
            {
                BeforeHit += SpellHitFn(spell_oculus_shock_lanceSpellScript::HandleBeforeHit);
                AfterHit += SpellHitFn(spell_oculus_shock_lanceSpellScript::HandleAfterHit);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_oculus_shock_lanceSpellScript();
        }
};

class spell_oculus_stop_time : public SpellScriptLoader
{
    public:
        spell_oculus_stop_time() : SpellScriptLoader("spell_oculus_stop_time") { }

        class spell_oculus_stop_timeAuraScript : public AuraScript
        {
            PrepareAuraScript(spell_oculus_stop_timeAuraScript);

            void HandleOnEffectApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if(!GetTarget())
                    return;

                for(uint8 i = 0; i<5; i++)
                    GetCaster()->CastSpell(GetTarget(), SPELL_SHOCK_CHARGE, true);
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_oculus_stop_timeAuraScript::HandleOnEffectApply, EFFECT_0, SPELL_AURA_MOD_STUN, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_oculus_stop_timeAuraScript();
        }
};

class spell_oculus_temporal_rift : public SpellScriptLoader
{
    public:
        spell_oculus_temporal_rift() : SpellScriptLoader("spell_oculus_temporal_rift") { }

        class spell_oculus_temporal_riftAuraScript : public AuraScript
        {
            PrepareAuraScript(spell_oculus_temporal_riftAuraScript);

            uint32 previousHealth;
            uint32 acumulatedDamage;

            bool Load()
            {
                acumulatedDamage = 0;
                previousHealth = 0;
                return true;
            }

            void HandleEffectPeriodic(AuraEffect const* /*aurEff*/)
            {
                uint32 charges = 0;
                uint32 damageTaken = previousHealth - GetTarget()->GetHealth() + acumulatedDamage;

                if ((double) damageTaken / 15000 >= 1)
                {
                    charges = (uint32) ((double) damageTaken / 15000);
                    acumulatedDamage = damageTaken % 15000;
                }

                if (charges > 0)
                {
                    for(uint8 i = 0; i<charges; i++)
                        GetCaster()->CastSpell(GetTarget(), SPELL_SHOCK_CHARGE, true);
                    previousHealth = GetTarget()->GetHealth();
                    charges = 0;
                }
            }

            void HandleOnEffectApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if(!GetTarget())
                    return;

                previousHealth = GetTarget()->GetHealth();
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_oculus_temporal_riftAuraScript::HandleEffectPeriodic, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
                OnEffectApply += AuraEffectApplyFn(spell_oculus_temporal_riftAuraScript::HandleOnEffectApply, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_oculus_temporal_riftAuraScript();
        }
};

class spell_oculus_touch_nightmare : public SpellScriptLoader
{
    public:
        spell_oculus_touch_nightmare() : SpellScriptLoader("spell_oculus_touch_nightmare") {}

        class spell_oculus_touch_nightmareSpellScript : public SpellScript
        {
            PrepareSpellScript(spell_oculus_touch_nightmareSpellScript)

            void HandleDamage(SpellEffIndex /*effIndex*/)
            {
                uint32 damage = 0;

                damage = (double) (GetCaster()->GetMaxHealth()) * 0.30;

                SetHitDamage(damage);
            }

            void Register()
            {
                OnEffect += SpellEffectFn(spell_oculus_touch_nightmareSpellScript::HandleDamage, EFFECT_2, SPELL_EFFECT_SCHOOL_DAMAGE);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_oculus_touch_nightmareSpellScript();
        }
};

void AddSC_boss_eregos()
{
    new boss_eregos();
    new mob_planar_anomaly();
    new spell_eregos_planar_shift();
    new achievement_amber_void();
    new achievement_ruby_void();
    new achievement_emerald_void();
    new achievement_amber_drake_rider();
    new achievement_ruby_drake_rider();
    new achievement_emerald_drake_rider();
    // Amber Drake spells
    new spell_oculus_shock_lance();
    new spell_oculus_stop_time();
    new spell_oculus_temporal_rift();
    // Emerald Drake spells
    new spell_oculus_touch_nightmare();
}
