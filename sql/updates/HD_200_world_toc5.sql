DELETE FROM `spell_script_names` WHERE spell_id IN (66867);
INSERT INTO `spell_script_names` VALUES
(66867, 'spell_eadric_hammer_of_righteous'), -- Hammer can be picked by target if isn't under HoJ effect
(67534, 'spell_toc5_hex_mending');           -- Hex of mending spell effect

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = 66905;
INSERT INTO `spell_linked_spell` VALUES
(66905, -66904, 0, 'Eadric Hammer of Righteous');  -- Remove the Hammer of Righteous spell after using it

DELETE FROM `conditions` WHERE SourceTypeOrReferenceId = 13 AND SourceEntry = 66905;
INSERT INTO `conditions` VALUES
(13, 0, 66905, 0, 18, 1, 35119, 0, 0, '', 'Eadric Hammer of Rigtheous'); -- Target Eadric with Hammer of Righteous

UPDATE `creature_template` SET `spell3` = 68284 WHERE `entry` = 36558;

-- Achievements
DELETE FROM achievement_criteria_data WHERE criteria_id IN (12310, 12311, 12312, 12313, 12314, 12318, 12319, 12320, 12321, 12322);
INSERT INTO `achievement_criteria_data` VALUES
(12310, 18, 0, 0, ''),
(12311, 18, 0, 0, ''),
(12312, 18, 0, 0, ''),
(12313, 18, 0, 0, ''),
(12314, 18, 0, 0, ''),
(12318, 18, 0, 0, ''),
(12319, 18, 0, 0, ''),
(12320, 18, 0, 0, ''),
(12321, 18, 0, 0, ''),
(12322, 18, 0, 0, '');

-- Script Names for ArgentSoilders
UPDATE creature_template SET ScriptName = 'npc_argent_monk' WHERE entry = 35305;
UPDATE creature_template SET ScriptName = 'npc_argent_lightwielder' WHERE entry = 35309;
UPDATE creature_template SET ScriptName = 'npc_argent_priest' WHERE entry = 35307;