DELETE FROM npc_text WHERE id BETWEEN 400000 AND 400005;
INSERT INTO npc_text (id, text0_0) VALUES
(400000,'Who dares interrupt the Grand Commander?'),
(400001,'I''m listening.'),
(400002,'Oh? Of course you have papers documenting this request.'),
(400003,'Listen to me, peon.$B$B We have a process for the delivery and safekeeping of the cipher fragment.$B$B The envoy delivers the missive, which is sealed by Lord Illidan.$B$B No missive, no transfer.'),
(400004,'I... what do you mean?'),
(400005,'Wait. Where are you going?$B$B You needed a transfer, correct?$B$B Let''s just get it done and over with, ok?$B$B Zuluhed at Dragonmaw? It will be done.$B$B Please let Lord Illidan know that his orders were carried out with the full cooperation of the Eclipsion.
$B$BI will dispatch Ruul the Darkener to personally deliver the fragment!
$B$BYou heard me right - Ruul...');

DELETE FROM gossip_menu WHERE entry BETWEEN 40000 AND 40005;
INSERT INTO gossip_menu VALUES
(40000,400000),
(40001,400001),
(40002,400002),
(40003,400003),
(40004,400004),
(40005,400005);

DELETE FROM gossip_menu_option WHERE menu_id BETWEEN 40000 AND 40005;
INSERT INTO gossip_menu_option (menu_id, id, option_icon, option_text, option_id, npc_option_npcflag, action_menu_id) VALUES
(40000,0,0,'I bring word from Lord Illidan.',1,1,40001),
(40001,0,0,'The cipher fragment is to be moved. Have it delivered to Zuluhed.',1,1,40002),
(40002,0,0,'Perhaps you did not hear me, Ruusk. I am giving you an order from Illidan himself!',1,1,40003),
(40003,0,0,'Very well. I will return to the Black Temple and notify Lord Illidan of your unwillingness to carry out his wishes. I suggest you make arrangements with your subordinates and let them know that you will soon be leaving this world.',1,1,40004),
(40004,0,0,'Do I need to go into all the gory details? I think we are both well aware of what Lord Illidan does with those that would oppose his word. Now, I must be going! Farewell, Ruusk! Forever...',1,1,40005),
(40005,0,0,'Ah, good of you to come around, Ruusk. Thank you and farewell.',1,1,0);

UPDATE creature_template SET gossip_menu_id=40000, AIName='SmartAI' WHERE entry=20563;
DELETE FROM smart_scripts WHERE entryorguid=20563;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(20563,0,0,1,62,0,100,0,40005,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Commander Ruusk - On gossip option select - Close gossip'),
(20563,0,1,0,61,0,100,0,0,0,0,0,26,10577,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Commander Ruusk - On gossip option select - Call GroupEventHappens to player');