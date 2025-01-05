#pragma once

#include <vector>
#include "fl/Engine.h"

class DemonBase;
class Demon;
class GameEngine;
class Bitmap;

class fl::Engine;

class FL_Demon_Main
{
public:
	FL_Demon_Main();
	~FL_Demon_Main();

	void Run(const std::vector<std::vector<int>>& currentMap, const std::vector<DemonBase*>& demonBases,
		Demon& demon, GameEngine& gameEngine, Bitmap& bmDemonBullet);

	void SetInputValue(const std::string& name, const int value);
	void SetOutputValue(const std::string& name, int& value);
	void ProcessEngine();

private:
	fl::Engine* engine = nullptr;
	
	void SetRules();
};

