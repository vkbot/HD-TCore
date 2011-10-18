 
#include "ScriptPCH.h"
 
#define NPC_ENTRY_TO_SUMMON 31099
#define UNSUMMON_TIME 200000 //30 sec
 
class npc_custom_summon : public CreatureScript
{
public:
    npc_custom_summon() : CreatureScript("npc_custom_summon") { }
 
    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
            if (pPlayer->getClass() == CLASS_DEATH_KNIGHT)
                {
                        pPlayer->ADD_GOSSIP_ITEM(10, "Призыв Лоскутика", GOSSIP_SENDER_MAIN, 123);
        }
 
        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
        return true;
    }
            bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
         switch (uiAction)
         {
     case 123:
        if (pPlayer->getClass() == CLASS_DEATH_KNIGHT)
        {
                pPlayer->SummonCreature(NPC_ENTRY_TO_SUMMON, pPlayer->GetPositionX()+1, pPlayer->GetPositionY(), pPlayer->GetPositionZ()+2, 0, TEMPSUMMON_TIMED_DESPAWN, UNSUMMON_TIME);
                return false;
        }
        else
        {
                pCreature->MonsterWhisper("You a not a DEATH KNIGHT", pPlayer->GetGUID(), false);
        }
        pPlayer->CLOSE_GOSSIP_MENU();
        break;
                }
                return true;
        }
};
 
void AddSC_npc_custom_summon()
{
        new npc_custom_summon();
}