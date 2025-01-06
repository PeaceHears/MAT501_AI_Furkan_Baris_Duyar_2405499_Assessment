#pragma once

class RBS_Demon_Database
{
public:
	RBS_Demon_Database();
	~RBS_Demon_Database();

	/*
	const int GetNearbyRobotCount() const { return nearbyRobotCount; }
	const int GetDemonCountAtTheBase() const { return demonCountAtTheBase; }

	void SetNearbyRobotCount(const int _nearbyRobotCount) { nearbyRobotCount = _nearbyRobotCount; }
	void SetDemonCountAtTheBase(const int _demonCountAtTheBase) { demonCountAtTheBase = _demonCountAtTheBase; }
	*/

//private:
	int nearbyRobotCount = 0;
	int demonCountAtTheBase = 0;
	bool isReady = false;
	bool isFirstCreated = false;
};