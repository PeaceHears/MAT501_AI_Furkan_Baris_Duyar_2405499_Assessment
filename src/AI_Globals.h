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

	constexpr const int MinRobotDistanceFactor = 0;
	constexpr const int MaxRobotDistanceFactor = 10;

	constexpr const int MinDemonRoamRangeFactor = 3;
	constexpr const int MaxDemonRoamRangeFactor = 8;
}