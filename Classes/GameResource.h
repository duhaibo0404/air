#ifndef __RESOURCE_TESTGAME_H__
#define __RESOURCE_TESTGAME_H__

enum objecy_type
{
	BULLET_TYPE = 0,
	ENEMY_TYPE_1,
	ENEMY_TYPE_2,
	ENEMY_TYPE_3,
	PLANE_TYPE
};
class ResourceGame
{
public:
	static const char* back_ground_path;
	static const char* back_ground_list;
	static const char* shoot_list;
	static const char* hero_1_key;
	static const char* hero_2_key;
	static const char* hero_path;
};

#endif