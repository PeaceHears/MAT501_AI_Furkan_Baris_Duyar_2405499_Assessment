//-----------------------------------------------------------------
// Demon Object
// C++ Header - Demon.h
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
using namespace std;
#include <windows.h>
#include <string>
#include <vector>
#include <queue>
#include <random>

#include "Sprite.h"
#include "Robot.h"
#include "GameEngine.h"

#ifndef DEMONBASE_H
#define DEMONBASE_H
#endif

class RBS_Demon_Database;
class DemonBase; // reference
class RBS_Demon_Main;
class FL_Demon_Main;

//-----------------------------------------------------------------
// Custom Data Types
//-----------------------------------------------------------------
typedef vector<vector<int>> Map;

enum DemonType {
	D_DEMON,
	D_EXPLODE,
	D_RANDOM,
	D_BOSS1
};

class Coordinate2 {
public:
	int x;
	int y;
	int dist;
	Coordinate2* prev;
	POINT screenPos;

public:
	Coordinate2(int _x, int _y) {
		x = _x;
		y = _y;
		dist = 0;
		prev = NULL;
		screenPos = { (x * 32), (y * 32) };
	}
	Coordinate2(int _x, int _y, int _dist, Coordinate2* _prev) {
		x = _x;
		y = _y;
		dist = _dist;
		prev = _prev;
		screenPos = { (x * 32), (y * 32) };
	}
};


//-----------------------------------------------------------------
// Demon Class
//-----------------------------------------------------------------
class Demon :public Character
{
protected:
	// Member Variables
	DemonType demonType;
	int base_number;
	int base_number_that_warned_by_the_helpless_demon;
	//vector<Robot*> currentTargets;
	DemonBase* base;

public:
	// Constructor(s)/Destructor
	Demon(Sprite* _sprite, POINT _mapPosition, DemonBase* base);
	virtual ~Demon();

	// Overload operator
	bool operator==(const Demon& other) {
		return sprite->GetPosition().left == other.sprite->GetPosition().left
			&& sprite->GetPosition().top == other.sprite->GetPosition().top
			&& sprite->GetPosition().right == other.sprite->GetPosition().right
			&& sprite->GetPosition().bottom == other.sprite->GetPosition().bottom;
	}

	// General Methods
	int				EuclideanDistance(Demon* demon, Robot* robot, DemonBase* demonBase);
	void			AttackByMaintainingTheDistance(const int taskNumber, Demon* demon, const Map& currentMap, Robot* robot, 
		GameEngine* game, Bitmap* bmDemonBullet, HINSTANCE hInstance);
	void			Situations(const Map& currentMap, const vector<DemonBase*>& demonBases,
		GameEngine* gameEngine, Bitmap* bmDemonBullet,
		RBS_Demon_Main& rbsDemonMain, FL_Demon_Main& flDemonMain);
	//void			seekTheRobots(Demon* demon, Map currentmap);
	void			WarnTheBaseDemons(const int taskNumber, Demon* demon, const Map& currentMap, Demon* helplessDemon, 
		GameEngine* game, Bitmap* bmDemonBullet, HINSTANCE hInstance);
	void			Chase(int taskNumber, Demon* demon, Robot* robot, const Map& currentMap);
	void			Evade(int taskNumber, Demon* demon, Robot* robot, const Map& currentMap);

	Robot*			FindTheClosestRobot(Demon* demon, const vector<Character*>& robots_around_the_demon);
	DemonBase*		FindTheClosestBase(Demon* demon, DemonBase* _pEnemyBase, const vector<DemonBase*>& demonBases);
	BOOL			RestrictForTheBaseBoundaries(Demon* demon, POINT dp, const Map& currentMap);
	int				CoordinateDistance(Coordinate2* c1, Coordinate2* c2);
	stack<POINT>	FindPathBFS(POINT _src, POINT _dst, const Map& _currentMap);
	void			Attack(Demon* demon, GameEngine* game, Bitmap* bmDemonBullet, HINSTANCE hInstance);
	stack<POINT>	Roam(Demon *_demon, POINT robotposition, POINT baselocation, const Map& currentmap);

	// Accessor Methods
	int				GetBaseNumber() { return base_number; };
	void			SetBaseNumber(int __base_number) { base_number = __base_number; };
	int				GetBaseNumberThatWarnedByTheHelplessDemon() { return base_number_that_warned_by_the_helpless_demon; };
	void			SetBaseNumberThatWarnedByTheHelplessDemon(int __base_number_that_warned_by_the_helpless_demon) { base_number_that_warned_by_the_helpless_demon = __base_number_that_warned_by_the_helpless_demon; };
	/*vector<Robot*>	GetCurrentTargets() { return currentTargets; };
	void			SetCurrentTargets(vector<Robot*> _currentTargets) { currentTargets = _currentTargets; };*/
	DemonBase*		GetBase() { return base; };
	void			SetBase(DemonBase* _base) { base = _base; };
	DemonType		GetDemonType() { return demonType; };
	void			SetDemonType(DemonType dt) { demonType = dt; };

	void SetRobotDistanceFactor(FL_Demon_Main& flDemonMain);
	void SetRoamRangeFactor(FL_Demon_Main& flDemonMain);
	void SetBaseBoundaryFactor(FL_Demon_Main& flDemonMain);

	const int GetRobotDistanceFactor() const { return robotDistanceFactor; }
	const int GetRoamRangeFactor() const { return roamRangeFactor; }
	const int GetBaseBoundaryFactor() const { return baseBoundaryFactor; }

private:
	int robotDistanceFactor = 4;
	int roamRangeFactor = 3;
	int baseBoundaryFactor = 3;

	RBS_Demon_Database* rbs_Demon_Database = nullptr;

};