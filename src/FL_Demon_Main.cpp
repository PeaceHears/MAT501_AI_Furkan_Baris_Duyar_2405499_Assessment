#include "FL_Demon_Main.h"
#include "FlsImporter.h"
#include <fl/Headers.h>
#include "Demon.h"
#include "DemonBase.h"
#include "AI_Globals.h"

using namespace fl;

FL_Demon_Main::FL_Demon_Main()
{
	SetRules();
}

FL_Demon_Main::~FL_Demon_Main()
{

}

void FL_Demon_Main::SetRules()
{
	engine = new Engine();

	const int minRobotDistanceFactor = AI_Globals::MinRobotDistanceFactor;
	const int maxRobotDistanceFactor = AI_Globals::MaxRobotDistanceFactor;
	const int middleRobotDistanceFactor = AI_Globals::MaxRobotDistanceFactor / 2;

	auto* robot = new InputVariable;
	robot->setName(AI_Globals::RobotName);
	robot->setRange(minRobotDistanceFactor, maxRobotDistanceFactor);
	robot->addTerm(new Triangle("close", minRobotDistanceFactor, 2, middleRobotDistanceFactor + 1));
	robot->addTerm(new Triangle("away", middleRobotDistanceFactor - 1, 7, maxRobotDistanceFactor));
	engine->addInputVariable(robot);

	const int minDemonRoamRangeFactor = AI_Globals::MinDemonRoamRangeFactor;
	const int maxDemonRoamRangeFactor = AI_Globals::MaxDemonRoamRangeFactor;
	const int middleDemonRoamRangeFactor = AI_Globals::MaxDemonRoamRangeFactor / 2;

	auto* demonRoamRange = new InputVariable;
	demonRoamRange->setName(AI_Globals::DemonRoamRangeName);
	demonRoamRange->setRange(minDemonRoamRangeFactor, maxDemonRoamRangeFactor);
	demonRoamRange->addTerm(new Triangle("less", minDemonRoamRangeFactor, 2.1, middleDemonRoamRangeFactor + 1));
	demonRoamRange->addTerm(new Triangle("much", middleDemonRoamRangeFactor - 1, 5.5, maxDemonRoamRangeFactor));
	engine->addInputVariable(demonRoamRange);

	const int minBaseBoundaryFactor = AI_Globals::MinBaseBoundaryFactor;
	const int maxBaseBoundaryFactor = AI_Globals::MaxBaseBoundaryFactor;
	const int middleBaseBoundaryFactor = AI_Globals::MaxBaseBoundaryFactor / 2;

	auto* baseBoundary = new InputVariable;
	baseBoundary->setName(AI_Globals::BaseBoundaryName);
	baseBoundary->setRange(minBaseBoundaryFactor, maxBaseBoundaryFactor);
	baseBoundary->addTerm(new Triangle("less", minBaseBoundaryFactor, 4, middleBaseBoundaryFactor + 1));
	baseBoundary->addTerm(new Triangle("much", middleBaseBoundaryFactor - 1, 12, maxBaseBoundaryFactor));
	engine->addInputVariable(baseBoundary);

	auto* robotDistanceFactor = new OutputVariable;
	robotDistanceFactor->setName(AI_Globals::RobotDistanceFactorName);
	robotDistanceFactor->setRange(minRobotDistanceFactor, maxRobotDistanceFactor);
	robotDistanceFactor->addTerm(new Triangle("low", minRobotDistanceFactor, 2.5, middleRobotDistanceFactor + 1));
	robotDistanceFactor->addTerm(new Triangle("high", middleRobotDistanceFactor - 1, 6, maxRobotDistanceFactor));
	robotDistanceFactor->setDefuzzifier(new Centroid(100));
	robotDistanceFactor->setAggregation(new Maximum);
	robotDistanceFactor->setDefaultValue(fl::nan);
	engine->addOutputVariable(robotDistanceFactor);

	auto* demonRoamRangeFactor = new OutputVariable;
	demonRoamRangeFactor->setName(AI_Globals::DemonRoamRangeFactorName);
	demonRoamRangeFactor->setRange(minDemonRoamRangeFactor, maxDemonRoamRangeFactor);
	demonRoamRangeFactor->addTerm(new Triangle("low", minDemonRoamRangeFactor, 2.5, middleDemonRoamRangeFactor + 1));
	demonRoamRangeFactor->addTerm(new Triangle("high", middleDemonRoamRangeFactor - 1, 4.5, maxDemonRoamRangeFactor));
	demonRoamRangeFactor->setDefuzzifier(new Centroid(100));
	demonRoamRangeFactor->setAggregation(new Maximum);
	demonRoamRangeFactor->setDefaultValue(fl::nan);
	engine->addOutputVariable(demonRoamRangeFactor);

	auto* baseBoundaryFactor = new OutputVariable;
	baseBoundaryFactor->setName(AI_Globals::BaseBoundaryFactorName);
	baseBoundaryFactor->setRange(minBaseBoundaryFactor, maxBaseBoundaryFactor);
	baseBoundaryFactor->addTerm(new Triangle("low", minBaseBoundaryFactor, 5, middleBaseBoundaryFactor + 1));
	baseBoundaryFactor->addTerm(new Triangle("high", middleBaseBoundaryFactor - 1, 11, maxBaseBoundaryFactor));
	baseBoundaryFactor->setDefuzzifier(new Centroid(100));
	baseBoundaryFactor->setAggregation(new Maximum);
	baseBoundaryFactor->setDefaultValue(fl::nan);
	engine->addOutputVariable(baseBoundaryFactor);

	auto* ruleBlock = new RuleBlock;
	ruleBlock->setName("ruleBlock");
	ruleBlock->setConjunction(new AlgebraicProduct);
	ruleBlock->setDisjunction(new Maximum);
	ruleBlock->setImplication(new AlgebraicProduct);
	ruleBlock->setActivation(new General);
	ruleBlock->addRule(Rule::parse("if robot is close then robotDistanceFactor is low", engine));
	ruleBlock->addRule(Rule::parse("if robot is away then robotDistanceFactor is high", engine));
	ruleBlock->addRule(Rule::parse("if demonRoamRange is less then demonRoamRangeFactor is low", engine));
	ruleBlock->addRule(Rule::parse("if demonRoamRange is much then demonRoamRangeFactor is high", engine));
	ruleBlock->addRule(Rule::parse("if baseBoundary is less then baseBoundaryFactor is low", engine));
	ruleBlock->addRule(Rule::parse("if baseBoundary is much then baseBoundaryFactor is high", engine));
	engine->addRuleBlock(ruleBlock);
}

void FL_Demon_Main::SetInputValue(const std::string& name, const int value)
{
	engine->setInputValue(name, value);
}

void FL_Demon_Main::SetOutputValue(const std::string& name, int& value)
{
	value = engine->getOutputValue(name);
}

void FL_Demon_Main::ProcessEngine()
{
	engine->process();
}

void FL_Demon_Main::Run(const std::vector<std::vector<int>>& currentMap, const std::vector<DemonBase*>& demonBases,
	Demon& demon, GameEngine& gameEngine, Bitmap& bmDemonBullet)
{
	if (demon.GetNearbyRobots().size() == 0)
	{
		demon.SetTask(AT_IDLE);

		if (demon.IsReady())
		{
			const auto& demonBasePosition = demon.GetBase()->GetMapPosition();

			if (demon.GetFirstCreated())
			{
				demon.SetFirstCreated(false);
				demon.SetPath(demon.Roam(&demon, demonBasePosition, demonBasePosition, currentMap));
			}
			else
			{
				demon.SetPath(demon.Roam(&demon, demon.GetMapPosition(), demonBasePosition, currentMap));
			}
		}
	}
	else
	{
		int robot_amount_around_the_demon = demon.GetNearbyRobots().size();
		int demon_amount_in_the_base = demon.GetBase()->GetCurrentDemons().size();
		const auto& nearbyRobots = demon.GetNearbyRobots();
		vector<Robot*> robots = reinterpret_cast<vector<Robot*> const&>(nearbyRobots);
		time_t now;

		if (robot_amount_around_the_demon <= 2) //TASK 2
		{
			if (rand() % 2)
			{
				demon.AddStatusMessage("\"Metal scum!\"", time(&now) + 2, RGB(200, 15, 15));
			}
			else
			{
				demon.AddStatusMessage("\"You die!\"", time(&now) + 2, RGB(200, 15, 15));
			}

			for (size_t i = 0; i < robot_amount_around_the_demon; i++)
			{
				demon.AttackByMaintainingTheDistance(2, &demon, currentMap, robots[i], &gameEngine, &bmDemonBullet, hInstance);
			}
		}
		else if (robot_amount_around_the_demon > 2) // TASK 3
		{
			demon.AddStatusMessage("Help, maggots!", time(&now) + 2, RGB(200, 15, 15));

			for (size_t i = 0; i < demon_amount_in_the_base; i++)
			{
				demon.WarnTheBaseDemons(3, demon.GetBase()->GetCurrentDemons()[i], currentMap, 
					&demon, &gameEngine, &bmDemonBullet, hInstance);
			}

			if (demon_amount_in_the_base < 2 * robot_amount_around_the_demon) // TASK 5
			{
				DemonBase* closestBase = demon.FindTheClosestBase(&demon, demon.GetBase(), demonBases);
				const auto& currentDemonsAtTheClosestBase = closestBase->GetCurrentDemons();
				const int demonCountAtTheClosestBase = currentDemonsAtTheClosestBase.size();

				for (size_t i = 0; i < demonCountAtTheClosestBase; i++)
				{
					demon.WarnTheBaseDemons(5, currentDemonsAtTheClosestBase[i], currentMap, 
						&demon, &gameEngine, &bmDemonBullet, hInstance);
				}
			}
		}

		if (demon_amount_in_the_base >= 2 * robot_amount_around_the_demon) //TASK 4
		{
			for (size_t i = 0; i < robot_amount_around_the_demon; i++)
			{
				demon.AttackByMaintainingTheDistance(4, &demon, currentMap, robots[i], &gameEngine, &bmDemonBullet, hInstance);
			}
		}
	}
}