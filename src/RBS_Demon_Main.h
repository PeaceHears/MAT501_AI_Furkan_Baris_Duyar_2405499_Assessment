#pragma once

#include <vector>
#include <functional>
#include <Windows.h>

class RBS_Demon_Database;
class Demon;
class DemonBase;
class GameEngine;
class Bitmap;

typedef std::pair<std::function<bool(const RBS_Demon_Database&)>, std::function<void(Demon& demon)>> ruleActionPair;

class RBS_Demon_Main
{
public:
	RBS_Demon_Main(const std::vector<std::vector<int>>& currentMap, const std::vector<DemonBase*>& demonBases,
		GameEngine* gameEngine, Bitmap* bmDemonBullet, HINSTANCE hInstance);
	~RBS_Demon_Main();

private:
	std::vector<ruleActionPair> ruleActionList;

	void CreateRuleActionList(const std::vector<std::vector<int>>& currentMap, const std::vector<DemonBase*>& demonBases,
		GameEngine* gameEngine, Bitmap* bmDemonBullet, HINSTANCE hInstance);
};

