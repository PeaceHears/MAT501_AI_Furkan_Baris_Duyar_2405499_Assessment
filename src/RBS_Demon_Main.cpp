#include "RBS_Demon_Main.h"
#include "RBS_Demon_Rules.h"
#include "RBS_Demon_Actions.h"
#include "RBS_Demon_Action_Parameters.h"

RBS_Demon_Main::RBS_Demon_Main()
{
	actionParameters = new RBS_Demon_Action_Parameters();

	CreateRuleActionList();
}

RBS_Demon_Main::~RBS_Demon_Main()
{

}

void RBS_Demon_Main::CreateRuleActionList()
{
	auto* ruleClass = new RBS_Demon_Rules();
	auto* actionClass = new RBS_Demon_Actions();

	const auto& rules = ruleClass->GetRuleList();
	const auto& actions = actionClass->GetActionList();

	for (int i = 0; i < rules.size(); i++)
	{
		ruleActionList.push_back(std::make_pair(rules[i], actions[i]));
	}
}

void RBS_Demon_Main::Run(const RBS_Demon_Database& database, 
	const std::vector<std::vector<int>>& currentMap, const std::vector<DemonBase*>& demonBases,
	Demon& demon, GameEngine& gameEngine, Bitmap& bmDemonBullet)
{
	actionParameters->currentMap = currentMap;
	actionParameters->demonBases = demonBases;
	actionParameters->demon = &demon;
	actionParameters->gameEngine = &gameEngine;
	actionParameters->bmDemonBullet = &bmDemonBullet;

	for (const auto& ruleActionsListItem : ruleActionList)
	{
		const bool isRulePositive = ruleActionsListItem.first(database);

		if (isRulePositive)
		{
			//Fire action
			ruleActionsListItem.second(*actionParameters);
		}
	}
}