#include "RBS_Demon_Rules.h"
#include "RBS_Demon_Database.h"

RBS_Demon_Rules::RBS_Demon_Rules()
{
	Create();
}

RBS_Demon_Rules::~RBS_Demon_Rules()
{

}

void RBS_Demon_Rules::Create()
{
	const auto& rule1 = [](const RBS_Demon_Database& database) -> bool
	{
		if (database.nearbyRobotCount == 0)
		{
			return true;
		}

		return false;
	};

	const auto& rule2 = [rule1](const RBS_Demon_Database& database) -> bool
	{
		if (rule1(database) && database.isReady && database.isFirstCreated)
		{
			return true;
		}

		return false;
	};

	const auto& rule3 = [rule1](const RBS_Demon_Database& database) -> bool
	{
		if (rule1(database) && database.isReady && !database.isFirstCreated)
		{
			return true;
		}

		return false;
	};

	const auto& rule4 = [rule1](const RBS_Demon_Database& database) -> bool
	{
		if (!rule1(database) && database.nearbyRobotCount <= 2)
		{
			return true;
		}

		return false;
	};

	const auto& rule5 = [rule1, &rule4](const RBS_Demon_Database& database) -> bool
	{
		if (!rule1(database) && rule4(database) && (rand() % 2))
		{
			return true;
		}

		return false;
	};

	const auto& rule6 = [rule1, &rule4, &rule5](const RBS_Demon_Database& database) -> bool
	{
		if (!rule1(database) && rule4(database) && !(rand() % 2))
		{
			return true;
		}

		return false;
	};

	const auto& rule7 = [rule1, &rule4](const RBS_Demon_Database& database) -> bool
	{
		if (!rule1(database) && !rule4(database))
		{
			return true;
		}

		return false;
	};

	const auto& rule8 = [rule1, &rule7](const RBS_Demon_Database& database) -> bool
	{
		if (!rule1(database) && rule7(database) && database.demonCountAtTheBase < 2 * database.nearbyRobotCount)
		{
			return true;
		}

		return false;
	};

	const auto& rule9 = [rule1](const RBS_Demon_Database& database) -> bool
	{
		if (!rule1(database) && database.demonCountAtTheBase >= 2 * database.nearbyRobotCount)
		{
			return true;
		}

		return false;
	};

	ruleList.push_back(rule1);
	ruleList.push_back(rule2);
	ruleList.push_back(rule3);
	ruleList.push_back(rule4);
	ruleList.push_back(rule5);
	ruleList.push_back(rule6);
	ruleList.push_back(rule7);
	ruleList.push_back(rule8);
	ruleList.push_back(rule9);
}