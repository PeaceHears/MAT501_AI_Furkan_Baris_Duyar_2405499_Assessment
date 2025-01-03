#pragma once
#include <vector>

class Demon;
class DemonBase;
class GameEngine;
class Bitmap;

class RBS_Demon_Action_Parameters
{
public:
	RBS_Demon_Action_Parameters();
	~RBS_Demon_Action_Parameters();

	std::vector<std::vector<int>> currentMap;
	std::vector<DemonBase*> demonBases;

	Demon* demon = nullptr;
	GameEngine* gameEngine = nullptr;
	Bitmap* bmDemonBullet = nullptr;
};