#include "RBS_Demon_Main.h"
#include "RBS_Demon_Rules.h"
#include "RBS_Demon_Actions.h"

RBS_Demon_Main::RBS_Demon_Main()
{
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