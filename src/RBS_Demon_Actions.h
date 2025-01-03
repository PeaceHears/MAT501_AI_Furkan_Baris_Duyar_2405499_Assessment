#pragma once

#include <vector>
#include <functional>
#include <Windows.h>

class Demon;
class DemonBase;
class GameEngine;
class Bitmap;

class RBS_Demon_Actions
{
public:
	RBS_Demon_Actions(const std::vector<std::vector<int>>& currentMap, const std::vector<DemonBase*>& demonBases,
		GameEngine* gameEngine, Bitmap* bmDemonBullet, HINSTANCE hInstance);
	~RBS_Demon_Actions();

	const std::vector<std::function<void(Demon&)>>& GetActionList() const { return actionList; }

private:
	std::vector<std::function<void(Demon&)>> actionList;

	void Create(const std::vector<std::vector<int>>& currentMap, const std::vector<DemonBase*>& demonBases,
		GameEngine* gameEngine, Bitmap* bmDemonBullet, HINSTANCE hInstance);
};