SET @GO_GUID := 8010561;
SET @CREATURE_GUID := 600680;

DELETE FROM `areatrigger_scripts` WHERE `entry` IN (3991);
REPLACE INTO `areatrigger_scripts` VALUES
(3991, 'at_wickerman_festival');

UPDATE `gameobject_template` SET `flags` = 17 WHERE `entry` = 180433;
DELETE FROM `gameobject` WHERE `id` IN (180433, 180432, 180434, 180437);
replace INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(@GO_GUID+00,'180433','0','1','1','1734.04','504.05','42.2861','1.4131','0','0','0.649213','0.760607','300','0','0'),
(@GO_GUID+01,'180432','0','1','1','1749.28','507.611','39.2312','1.49635','0','0','0.680301','0.732933','300','0','1'),
(@GO_GUID+02,'180432','0','1','1','1712.63','507.05','38.2495','1.58824','0','0','0.713246','0.700914','300','0','1'),
(@GO_GUID+03,'180405','0','1','1','1746.07','517.066','38.936','2.83466','0','0','0.988247','0.152864','300','0','1'),
(@GO_GUID+04,'180406','0','1','1','1719.67','522.979','36.8828','2.93283','0','0','0.994557','0.10419','300','0','1'),
(@GO_GUID+05,'180405','0','1','1','1728','475.099','63.6779','3.08363','0','0','0.99958','0.0289791','300','0','1'),
(@GO_GUID+06,'180434','0','1','1','1758.89','513.276','35.8655','1.28897','0','0','0.600788','0.799409','300','0','1'),
(@GO_GUID+07,'180434','0','1','1','1704.48','518.689','35.4045','1.30704','0','0','0.607984','0.793949','300','0','1'),
(@GO_GUID+08,'180434','0','1','1','1739.78','473.238','61.6565','1.59371','0','0','0.71516','0.698961','300','0','1'),
(@GO_GUID+09,'180434','0','1','1','1717.32','472.723','61.6566','1.59371','0','0','0.71516','0.698961','300','0','1'),
(@GO_GUID+10,'180437','0','1','1','1744.62','504.954','40.8518','1.23403','0','0','0.578603','0.81561','300','0','1'),
(@GO_GUID+11,'180437','0','1','1','1729.13','510.378','40.8719','1.23403','0','0','0.578603','0.81561','300','0','1'),
(@GO_GUID+12,'180437','0','1','1','1721.77','503.938','41.1381','1.23403','0','0','0.578603','0.81561','300','0','1'),
(@GO_GUID+13,'180437','0','1','1','1744.96','496.25','41.44','1.24581','0','0','0.583397','0.812187','300','0','1');


DELETE FROM `creature` WHERE `id` IN (15195, 15197, 15199) AND `guid` BETWEEN @CREATURE_GUID+00 AND @CREATURE_GUID+05;
REPLACE INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CREATURE_GUID+00,15195,0,1,1,0,0,1713.1,511.295,37.2005,1.48063,300,0,0,45780,0,0,0,0,0),
(@CREATURE_GUID+01,15195,0,1,1,0,0,1750.57,511.697,37.7587,1.25444,300,0,0,45780,0,0,0,0,0),
(@CREATURE_GUID+02,15195,0,1,1,0,0,1732.31,520.874,36.3326,1.30942,300,0,0,45780,0,0,0,0,0),
(@CREATURE_GUID+03,15197,0,1,1,0,0,1734.6,508.803,41.2847,1.6173,300,0,0,15260,0,0,0,0,0),
(@CREATURE_GUID+04,15199,0,1,1,0,0,-813.614,-547.184,15.6377,1.69193,300,0,0,15260,0,0,0,0,0);

DELETE FROM `game_event_gameobject` WHERE `guid` BETWEEN @GO_GUID+00 AND @GO_GUID+09;
REPLACE INTO `game_event_gameobject` VALUES
(12, @GO_GUID+00),
(12, @GO_GUID+01),
(12, @GO_GUID+02),
(12, @GO_GUID+03),
(12, @GO_GUID+04),
(12, @GO_GUID+05),
(12, @GO_GUID+06),
(12, @GO_GUID+07),
(12, @GO_GUID+08),
(12, @GO_GUID+09),
(12, @GO_GUID+10),
(12, @GO_GUID+11),
(12, @GO_GUID+12),
(12, @GO_GUID+13);

DELETE FROM `game_event_creature` WHERE `guid` BETWEEN @CREATURE_GUID+00 AND @CREATURE_GUID+02;
REPLACE INTO `game_event_creature` VALUES
(12, @CREATURE_GUID+00),
(12, @CREATURE_GUID+01),
(12, @CREATURE_GUID+02),
(12, @CREATURE_GUID+03),
(12, @CREATURE_GUID+04);

-- Wickerman Ashes
DELETE FROM `gossip_menu` WHERE `entry` = 6535;
REPLACE INTO `gossip_menu` VALUES
(6535, 100);
DELETE FROM `npc_text` WHERE `ID` = 100;
REPLACE INTO `npc_text`(`ID`, `text0_0`) VALUES
(100, 'Las cenizas del hombre de mimbre irradian poder mágico.');
UPDATE `gameobject_template` SET `faction` = 0, `ScriptName` = 'go_wickerman_ember' WHERE `entry` = 180437;

-- Wickerman Guardians
UPDATE `creature_template` SET `Armor_mod` = 2.6, `minlevel` = 80, `maxlevel` = 80, `mechanic_immune_mask` = 748240635 WHERE `entry` = 15195;