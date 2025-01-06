#pragma once

namespace AI_Globals
{
	enum class AI_TECHNIQUE
	{
		RULE_BASED_SYSTEM,
		FUZZY_LOGIC
	};

	extern AI_TECHNIQUE DemonAITechnique;

	constexpr const char* RobotName = "robot";
	constexpr const char* RobotDistanceFactorName = "robotDistanceFactor";

	constexpr const char* DemonRoamRangeName = "demonRoamRange";
	constexpr const char* DemonRoamRangeFactorName = "demonRoamRangeFactor";

	constexpr const char* BaseBoundaryName = "baseBoundary";
	constexpr const char* BaseBoundaryFactorName = "baseBoundaryFactor";

	constexpr const int MinRobotDistanceFactor = 0;
	constexpr const int MaxRobotDistanceFactor = 10;

	constexpr const int MinDemonRoamRangeFactor = 1;
	constexpr const int MaxDemonRoamRangeFactor = 8;

	constexpr const int MinBaseBoundaryFactor = 2;
	constexpr const int MaxBaseBoundaryFactor = 15;
}