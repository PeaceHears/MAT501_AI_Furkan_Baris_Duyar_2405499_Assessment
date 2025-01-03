#pragma once

#include <vector>
#include <functional>
#include <Windows.h>

class RBS_Demon_Database;
class RBS_Demon_Action_Parameters;

typedef std::pair<std::function<bool(const RBS_Demon_Database&)>, std::function<void(RBS_Demon_Action_Parameters&)>> ruleActionPair;

class RBS_Demon_Main
{
public:
	RBS_Demon_Main();
	~RBS_Demon_Main();

private:
	std::vector<ruleActionPair> ruleActionList;

	void CreateRuleActionList();
};

