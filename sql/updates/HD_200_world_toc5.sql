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
(12322, 18, 0, 0, ''),
(11863, 18, 0, 0, ''),
(11904, 18, 0, 0, ''),
(11905, 18, 0, 0, ''),
(11906, 18, 0, 0, ''),
(11907, 18, 0, 0, ''),
(11908, 18, 0, 0, ''),
(11909, 18, 0, 0, ''),
(11910, 18, 0, 0, ''),
(11911, 18, 0, 0, ''),
(11912, 18, 0, 0, ''),
(11913, 18, 0, 0, ''),
(11914, 18, 0, 0, ''),
(11915, 18, 0, 0, ''),
(11916, 18, 0, 0, ''),
(11917, 18, 0, 0, ''),
(11918, 18, 0, 0, ''),
(11919, 18, 0, 0, ''),
(11920, 18, 0, 0, ''),
(11921, 18, 0, 0, ''),
(11922, 18, 0, 0, ''),
(11923, 18, 0, 0, ''),
(11924, 18, 0, 0, ''),
(11925, 18, 0, 0, ''),
(11926, 18, 0, 0, ''),
(11927, 18, 0, 0, '');

-- Script Names for ArgentSoilders
UPDATE creature_template SET ScriptName = 'npc_argent_monk' WHERE entry = 35305;
UPDATE creature_template SET ScriptName = 'npc_argent_lightwielder' WHERE entry = 35309;
UPDATE creature_template SET ScriptName = 'npc_argent_priest' WHERE entry = 35307;
UPDATE `creature_template` SET `mechanic_immune_mask` = '650854267' WHERE `entry` IN (35305, 35309, 35307, 12488, 12439, 12448);

-- Memories equip templates
UPDATE `creature_template` SET `equipment_id` = 22 WHERE `entry` IN  (34942, (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry` = 34942));
UPDATE `creature_template` SET `equipment_id` = 1431 WHERE `entry` = (35028, (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry` = 35028));
UPDATE `creature_template` SET `equipment_id` = 1178 WHERE `entry` = (35030, (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry` = 35030));
UPDATE `creature_template` SET `equipment_id` = 1330 WHERE `entry` = (35031, (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry` = 35031));
UPDATE `creature_template` SET `equipment_id` = 1808 WHERE `entry` = (35036, (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry` = 35036));
UPDATE `creature_template` SET `equipment_id` = 1496 WHERE `entry` = (35037, (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry` = 35037));
UPDATE `creature_template` SET `equipment_id` = 2216 WHERE `entry` = (35042, (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry` = 35042));
UPDATE `creature_template` SET `equipment_id` = 714 WHERE `entry` = (35045, (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry` = 35045));
UPDATE `creature_template` SET `equipment_id` = 271 WHERE `entry` = (35049, (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry` = 35049));
-- Argent Champions equip templates
SET @TemplateId := 2475;
DELETE FROM `creature_equip_template` WHERE `entry` BETWEEN 2475 AND 2477;
INSERT INTO `creature_equip_template` VALUES
(@TemplateId, 44244, 0, 0), -- Argent Lightwielder
(@TemplateId+1, 18608, 0, 0), -- Argent Priestess
(@TemplateId+2, 40343, 0, 0); -- The Black Knight

SET @NPC_LIGHTWIELDER   := 35309;
SET @NPC_PRIESTESS      := 35307;
SET @NPC_BLACK_KNIGHT   := 35451;
SET @NPC_LIGHTWIELDER_H := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry` = @NPC_LIGHTWIELDER);
SET @NPC_PRIESTESS_H := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry` = @NPC_PRIESTESS);
SET @NPC_BLACK_KNIGHT_H := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry` = @NPC_BLACK_KNIGHT);

UPDATE `creature_template` SET `equipment_id` = @TemplateId WHERE `entry` IN (@NPC_LIGHTWIELDER, @NPC_LIGHTWIELDER_H);
UPDATE `creature_template` SET `equipment_id` = @TemplateId+1 WHERE `entry` IN (@NPC_PRIESTESS, @NPC_PRIESTESS_H);
UPDATE `creature_template` SET `equipment_id` = @TemplateId+2 WHERE `entry` IN (@NPC_BLACK_KNIGHT, @NPC_BLACK_KNIGHT_H);