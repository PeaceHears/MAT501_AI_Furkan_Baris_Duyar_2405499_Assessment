#pragma once
#include <vector>

class Demon;
class DemonBase;
class GameEngine;
class Bitmap;

class RBS_Demon_Action_Parameters
{
public:
	RBS_Demon_Action_Parameters(const std::vector<std::vector<int>>& _currentMap, const std::vector<DemonBase*>& _demonBases,
		Demon& demon, GameEngine& _gameEngine, Bitmap& _bmDemonBullet);
	~RBS_Demon_Action_Parameters();

	const std::vector<std::vector<int>>& currentMap;
	const std::vector<DemonBase*>& demonBases;

	Demon* demon = nullptr;
	GameEngine* gameEngine = nullptr;
	Bitmap* bmDemonBullet = nullptr;
};