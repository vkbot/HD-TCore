-- Logros
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