-- == Logros ==
DELETE FROM `achievement_criteria_data` WHERE criteria_id IN (7323, 7324, 7325, 7177, 7178, 7179);
INSERT INTO `achievement_criteria_data` VALUES
-- Drake Voids
(7323, 11, 0, 0, 'achievement_ruby_void'),
(7324, 11, 0, 0, 'achievement_emerald_void'),
(7325, 11, 0, 0, 'achievement_amber_void'),
-- Drake Rider
(7177, 11, 0, 0, 'achievement_amber_drake_rider'),
(7178, 11, 0, 0, 'achievement_emerald_drake_rider'),
(7179, 11, 0, 0, 'achievement_ruby_drake_rider');

-- Delete disables
DELETE FROM `disables` WHERE sourcetype = 4 AND entry IN(7323, 7324, 7325, 7177, 7178, 7179);

-- == Creature ==

-- Scripts de mobs de "tierra"
UPDATE `creature_template` SET `ScriptName` = 'npc_centrifuge_construct' WHERE `entry` = 27641;
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_ringlord_conjurer' WHERE `entry` = 27640;
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_ringlord_sorceress' WHERE `entry` = 27639;

-- VAROS --
-- Haz arcano
-- Spell visual
DELETE FROM `conditions` WHERE SourceTypeOrReferenceId = 13 AND SourceEntry = 51024;
INSERT INTO `conditions` VALUES
(13, 0, 51024, 0, 18, 1, 28239, 0, 0, '', NULL);
UPDATE `creature_template` SET `modelid2` = 11686, `faction_A` = 35, `faction_H` = 35 WHERE `entry` IN (28239, 31628);

-- EREGOS --

-- Anomalia plana
UPDATE `creature_template` SET `modelid2` = 0, `ScriptName` = 'mob_planar_anomaly' WHERE `entry` = 30879;

-- Textos
DELETE FROM `creature_text` WHERE entry = 27656;
DELETE FROM script_texts WHERE npc_entry = 27656;
INSERT INTO script_texts (npc_entry, entry, content_default, content_loc6, content_loc7, sound, TYPE) VALUES
(27656, -1578022, 'Simpletons! You cannot comprehend the forces you have set in motion. The ley line conduit will not be disrupted! Your defeat shall be absolute!', '¡Simplones! No podeis comprender las fuerzas que habeis puesto en marcha. ¡El conducto de lineas Ley no sera interrumpido! ¡Vuestra derrota será total!', content_loc6, 13622, 1),
(27656, -1578023, 'You brash interlopers are out of your element! I will ground you!', '¡Entrometidos descarados, estais fuera de vuestro elemento! ¡Os enterraré!', content_loc6, 13623, 1),
(27656, -1578024, 'It\'s a long way down...', 'Hay mucha caida...', content_loc6, 13628, 1),
(27656, -1578025, 'Back to the earth with you!', '¡Vuelve a la tierra!', content_loc6, 13629, 1),
(27656, -1578026, 'Enjoy the fall!', '¡Disfruta de la caida!', content_loc6, 13630, 1),
(27656, -1578027, 'Such insolence... such arrogance... must be PUNISHED!', '¡Tanta insolencia... tanta arrogancia... deben ser CASTIGADAS!', content_loc6, 13624, 1),
(27656, -1578028, 'Savor this small victory, foolish little creatures. You and your dragon allies have won this battle. But we will win... the Nexus War.', 'Saboread esta pequeña victoria, criaturitas insensatas. Vosotros y vuestros aliados dragones habeis ganado esta batalla... pero nosotros ganaremos la guerra del nexo...', content_loc6, 13631, 1);

-- == Game Objects ==
UPDATE `gameobject_template` SET `flags` = 32 WHERE `entry` IN (191349, 193603);
UPDATE `gameobject` SET `spawntimesecs` = 608400 WHERE `id` IN (191349, 193603);
UPDATE `gameobject` SET `spawntimesecs` = 608400 WHERE `id` = 191351;

-- == Spells de los dragones ==
DELETE FROM `spell_script_names` WHERE spell_id IN (49840, 49838, 49592, 50341, 50344);
INSERT INTO `spell_script_names` VALUES
(49840, 'spell_oculus_shock_lance'),
(49838, 'spell_oculus_stop_time'),
(49592, 'spell_oculus_temporal_rift'),
(50341,'spell_oculus_touch_nightmare'),
(50344,'spell_oculus_dream_funnel');