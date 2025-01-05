#include "RBS_Demon_Actions.h"
#include "Demon.h"
#include "DemonBase.h"
#include "RBS_Demon_Action_Parameters.h"

RBS_Demon_Actions::RBS_Demon_Actions()
{
	Create();
}

RBS_Demon_Actions::~RBS_Demon_Actions()
{
	 
}

void RBS_Demon_Actions::Create()
{
	const auto& action1 = [](RBS_Demon_Action_Parameters& actionParameters) -> void
	{
		actionParameters.demon->SetTask(AT_IDLE);
	};

	const auto& action2 = [](RBS_Demon_Action_Parameters& actionParameters) -> void
	{
		auto& demonBase = *actionParameters.demon->GetBase();

		actionParameters.demon->SetFirstCreated(false);
		actionParameters.demon->SetPath(actionParameters.demon->Roam(actionParameters.demon, demonBase.GetMapPosition(), demonBase.GetMapPosition(),
			actionParameters.currentMap));
	};

	const auto& action3 = [](RBS_Demon_Action_Parameters& actionParameters) -> void
	{
		auto& demonBase = *actionParameters.demon->GetBase();

		actionParameters.demon->SetPath(actionParameters.demon->Roam(actionParameters.demon, actionParameters.demon->GetMapPosition(), 
			demonBase.GetMapPosition(), actionParameters.currentMap));
	};

	const auto& action4 = [](RBS_Demon_Action_Parameters& actionParameters) -> void
	{
		const auto& nearbyRobots = actionParameters.demon->GetNearbyRobots();
		const int nearbyRobotCount = nearbyRobots.size();
		const int demonCountAtTheBase = actionParameters.demon->GetBase()->GetCurrentDemons().size();
		std::vector<Robot*> robots = reinterpret_cast<std::vector<Robot*> const&>(nearbyRobots);

		for (size_t i = 0; i < nearbyRobotCount; i++)
		{
			actionParameters.demon->AttackByMaintainingTheDistance(2, actionParameters.demon, actionParameters.currentMap, robots[i],
				actionParameters.gameEngine, actionParameters.bmDemonBullet, hInstance);
		}
	};

	const auto& action5 = [](RBS_Demon_Action_Parameters& actionParameters) -> void
	{
		time_t now;

		actionParameters.demon->AddStatusMessage("\"Metal scum!\"", time(&now) + 2, RGB(200, 15, 15));
	};

	const auto& action6 = [](RBS_Demon_Action_Parameters& actionParameters) -> void
	{
		time_t now;

		actionParameters.demon->AddStatusMessage("\"You die!\"", time(&now) + 2, RGB(200, 15, 15));
	};

	const auto& action7 = [](RBS_Demon_Action_Parameters& actionParameters) -> void
	{
		time_t now;
		const auto& demonsAtTheBase = actionParameters.demon->GetBase()->GetCurrentDemons();
		const int demonCountAtTheBase = demonsAtTheBase.size();

		actionParameters.demon->AddStatusMessage("Help, maggots!", time(&now) + 2, RGB(200, 15, 15));

		for (size_t i = 0; i < demonCountAtTheBase; i++)
		{
			actionParameters.demon->WarnTheBaseDemons(3, demonsAtTheBase[i], actionParameters.currentMap, actionParameters.demon,
				actionParameters.gameEngine, actionParameters.bmDemonBullet, hInstance);
		}
	};

	const auto& action8 = [](RBS_Demon_Action_Parameters& actionParameters) -> void
	{
		auto& closestBase = *actionParameters.demon->FindTheClosestBase(actionParameters.demon, actionParameters.demon->GetBase(), 
			actionParameters.demonBases);
		const auto& currentDemonsAtClosestBase = closestBase.GetCurrentDemons();
		const int demonCountAtTheClosestBase = closestBase.GetCurrentDemons().size();

		for (size_t i = 0; i < demonCountAtTheClosestBase; i++)
		{
			actionParameters.demon->WarnTheBaseDemons(5, currentDemonsAtClosestBase[i], actionParameters.currentMap, 
				actionParameters.demon, actionParameters.gameEngine, actionParameters.bmDemonBullet, hInstance);
		}
	};

	const auto& action9 = [](RBS_Demon_Action_Parameters& actionParameters) -> void
	{
		const auto& nearbyRobots = actionParameters.demon->GetNearbyRobots();
		const int nearbyRobotCount = nearbyRobots.size();
		std::vector<Robot*> robots = reinterpret_cast<std::vector<Robot*> const&>(nearbyRobots);

		for (size_t i = 0; i < nearbyRobotCount; i++)
		{
			actionParameters.demon->AttackByMaintainingTheDistance(4, actionParameters.demon, actionParameters.currentMap, robots[i],
				actionParameters.gameEngine, actionParameters.bmDemonBullet, hInstance);
		}
	};

	actionList.push_back(action1);
	actionList.push_back(action2);
	actionList.push_back(action3);
	actionList.push_back(action4);
	actionList.push_back(action5);
	actionList.push_back(action6);
	actionList.push_back(action7);
	actionList.push_back(action8);
	actionList.push_back(action9);
}