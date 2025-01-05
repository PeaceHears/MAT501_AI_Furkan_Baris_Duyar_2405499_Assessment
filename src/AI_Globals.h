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

	constexpr const int MinRobotDistanceFactor = 1;
	constexpr const int MaxRobotDistanceFactor = 8;
}