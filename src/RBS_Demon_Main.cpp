#include "RBS_Demon_Main.h"
#include "RBS_Demon_Database.h"
#include "Demon.h"
#include "DemonBase.h"
#include "RBS_Demon_Rules.h"
#include "RBS_Demon_Actions.h"

RBS_Demon_Main::RBS_Demon_Main(const std::vector<std::vector<int>>& currentMap, const std::vector<DemonBase*>& demonBases,
	GameEngine* gameEngine, Bitmap* bmDemonBullet, HINSTANCE hInstance)
{
	CreateRuleActionList(currentMap, demonBases, gameEngine, bmDemonBullet, hInstance);
}

RBS_Demon_Main::~RBS_Demon_Main()
{

}

void RBS_Demon_Main::CreateRuleActionList(const std::vector<std::vector<int>>& currentMap, const std::vector<DemonBase*>& demonBases, 
	GameEngine* gameEngine, Bitmap* bmDemonBullet, HINSTANCE hInstance)
{
	auto* ruleClass = new RBS_Demon_Rules();
	auto* actionClass = new RBS_Demon_Actions(currentMap, demonBases, gameEngine, bmDemonBullet, hInstance);

	const auto& rules = ruleClass->GetRuleList();
	const auto& actions = actionClass->GetActionList();

	for (int i = 0; i < rules.size(); i++)
	{
		ruleActionList.push_back(std::make_pair(rules[i], actions[i]));
	}
}