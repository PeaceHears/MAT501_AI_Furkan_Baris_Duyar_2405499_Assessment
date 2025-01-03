#pragma once

#include <vector>
#include <functional>

class RBS_Demon_Database;

class RBS_Demon_Rules
{
public:
	RBS_Demon_Rules();
	~RBS_Demon_Rules();

	const std::vector<std::function<bool(const RBS_Demon_Database&)>>& GetRuleList() const { return ruleList; }

private:
	std::vector<std::function<bool(const RBS_Demon_Database&)>> ruleList;

	void Create();
};

