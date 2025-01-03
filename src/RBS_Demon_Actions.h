#pragma once

#include <vector>
#include <functional>
#include <Windows.h>

class RBS_Demon_Action_Parameters;
class DemonBase;
class GameEngine;
class Bitmap;

class RBS_Demon_Actions
{
public:
	RBS_Demon_Actions();
	~RBS_Demon_Actions();

	const std::vector<std::function<void(RBS_Demon_Action_Parameters&)>>& GetActionList() const { return actionList; }

private:
	std::vector<std::function<void(RBS_Demon_Action_Parameters&)>> actionList;

	void Create();
};