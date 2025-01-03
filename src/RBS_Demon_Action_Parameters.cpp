#include "RBS_Demon_Action_Parameters.h"

RBS_Demon_Action_Parameters::RBS_Demon_Action_Parameters(const std::vector<std::vector<int>>& _currentMap, 
	const std::vector<DemonBase*>& _demonBases, Demon& _demon, 
	GameEngine& _gameEngine, Bitmap& _bmDemonBullet) :
	currentMap(_currentMap), demonBases(_demonBases), demon(&_demon), 
	gameEngine(&_gameEngine), bmDemonBullet(&_bmDemonBullet)
{

}

RBS_Demon_Action_Parameters::~RBS_Demon_Action_Parameters()
{

}