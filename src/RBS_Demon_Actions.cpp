#include "RBS_Demon_Actions.h"
#include "Demon.h"
#include "DemonBase.h"

RBS_Demon_Actions::RBS_Demon_Actions(const std::vector<std::vector<int>>& currentMap, const std::vector<DemonBase*>& demonBases,
	GameEngine* gameEngine, Bitmap* bmDemonBullet, HINSTANCE hInstance)
{
	Create(currentMap, demonBases, gameEngine, bmDemonBullet, hInstance);
}

RBS_Demon_Actions::~RBS_Demon_Actions()
{
	 
}

void RBS_Demon_Actions::Create(const std::vector<std::vector<int>>& currentMap, const std::vector<DemonBase*>& demonBases,
	GameEngine* gameEngine, Bitmap* bmDemonBullet, HINSTANCE hInstance)
{
	const auto& action1 = [](Demon& demon) -> void
	{
		demon.SetTask(AT_IDLE);
	};

	const auto& action2 = [&currentMap](Demon& demon) -> void
	{
		auto& demonBase = *demon.GetBase();

		demon.SetFirstCreated(false);
		demon.SetPath(demon.DemonRoam(&demon, demonBase.GetMapPosition(), demonBase.GetMapPosition(), currentMap));
	};

	const auto& action3 = [&currentMap](Demon& demon) -> void
	{
		auto& demonBase = *demon.GetBase();

		demon.SetPath(demon.DemonRoam(&demon, demon.GetMapPosition(), demonBase.GetMapPosition(), currentMap));
	};

	const auto& action4 = [&currentMap, &gameEngine, &bmDemonBullet, &hInstance](Demon& demon) -> void
	{
		const auto& nearbyRobots = demon.GetNearbyRobots();
		const int nearbyRobotCount = nearbyRobots.size();
		const int demonCountAtTheBase = demon.GetBase()->GetCurrentDemons().size();
		std::vector<Robot*> robots = reinterpret_cast<std::vector<Robot*> const&>(nearbyRobots);

		for (size_t i = 0; i < nearbyRobotCount; i++)
		{
			demon.AttackByMaintainingTheDistance(2, &demon, currentMap, robots[i], gameEngine, bmDemonBullet, hInstance);
		}
	};

	const auto& action5 = [](Demon& demon) -> void
	{
		time_t now;

		demon.AddStatusMessage("\"Metal scum!\"", time(&now) + 2, RGB(200, 15, 15));
	};

	const auto& action6 = [](Demon& demon) -> void
	{
		time_t now;

		demon.AddStatusMessage("\"You die!\"", time(&now) + 2, RGB(200, 15, 15));
	};

	const auto& action7 = [&currentMap, &gameEngine, &bmDemonBullet, &hInstance](Demon& demon) -> void
	{
		time_t now;
		const auto& demonsAtTheBase = demon.GetBase()->GetCurrentDemons();
		const int demonCountAtTheBase = demonsAtTheBase.size();

		demon.AddStatusMessage("Help, maggots!", time(&now) + 2, RGB(200, 15, 15));

		for (size_t i = 0; i < demonCountAtTheBase; i++)
		{
			demon.WarnTheBaseDemons(3, demonsAtTheBase[i], currentMap, &demon, gameEngine, bmDemonBullet, hInstance);
		}
	};

	const auto& action8 = [&demonBases, &currentMap, &gameEngine, &bmDemonBullet, &hInstance](Demon& demon) -> void
	{
		auto& closestBase = *demon.FindTheClosestBase(&demon, demon.GetBase(), demonBases);
		const auto& currentDemonsAtClosestBase = closestBase.GetCurrentDemons();
		const int demonCountAtTheClosestBase = closestBase.GetCurrentDemons().size();

		for (size_t i = 0; i < demonCountAtTheClosestBase; i++)
		{
			demon.WarnTheBaseDemons(5, currentDemonsAtClosestBase[i], currentMap, &demon, gameEngine, bmDemonBullet, hInstance);
		}
	};

	const auto& action9 = [&currentMap, &gameEngine, &bmDemonBullet, &hInstance](Demon& demon) -> void
	{
		const auto& nearbyRobots = demon.GetNearbyRobots();
		const int nearbyRobotCount = nearbyRobots.size();
		std::vector<Robot*> robots = reinterpret_cast<std::vector<Robot*> const&>(nearbyRobots);

		for (size_t i = 0; i < nearbyRobotCount; i++)
		{
			demon.AttackByMaintainingTheDistance(4, &demon, currentMap, robots[i], gameEngine, bmDemonBullet, hInstance);
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