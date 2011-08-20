DELETE FROM `spell_script_names` WHERE spell_id IN (66867);
INSERT INTO `spell_script_names` VALUES
(66867, 'spell_eadric_hammer_of_righteous'); -- Hammer can be picked by target if isn't under HoJ effect

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = 66905;
INSERT INTO `spell_linked_spell` VALUES
(66905, -66904, 0, 'Eadric Hammer of Righteous');  -- Remove the Hammer of Righteous spell after using it

DELETE FROM `conditions` WHERE SourceTypeOrReferenceId = 13 AND SourceEntry = 66905;
INSERT INTO `conditions` VALUES
(13, 0, 66905, 0, 18, 1, 35119, 0, 0, '', 'Eadric Hammer of Rigtheous'); -- Target Eadric with Hammer of Righteous