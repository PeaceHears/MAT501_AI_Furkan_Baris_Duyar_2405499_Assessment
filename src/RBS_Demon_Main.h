#pragma once

#include <vector>
#include <functional>

class RBS_Demon_Database;
class RBS_Demon_Action_Parameters;
class DemonBase;
class Demon;
class GameEngine;
class Bitmap;

typedef std::pair<std::function<bool(const RBS_Demon_Database&)>, std::function<void(RBS_Demon_Action_Parameters&)>> ruleActionPair;

class RBS_Demon_Main
{
public:
	RBS_Demon_Main();
	~RBS_Demon_Main();

	void Run(const RBS_Demon_Database& database,
		const std::vector<std::vector<int>>& currentMap, const std::vector<DemonBase*>& demonBases,
		Demon& demon, GameEngine& gameEngine, Bitmap& bmDemonBullet);

private:
	std::vector<ruleActionPair> ruleActionList;
	RBS_Demon_Action_Parameters* actionParameters = nullptr;

	void CreateRuleActionList();
};

