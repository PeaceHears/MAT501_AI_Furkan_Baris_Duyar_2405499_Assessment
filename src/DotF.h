//-----------------------------------------------------------------
// DotF Application
// C++ Header - DotF.h
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include <windows.h>
#include <vector>
#include <algorithm>
#include <queue> 
#include <stack>
#include <cstdlib>
#include <ctime>
#include <random>
#include <string>


#include "Resource.h"
#include "GameEngine.h"
#include "Bitmap.h"
#include "Sprite.h"
#include "WallSprite.h"
#include "Character.h"
#include "Robot.h"
#include "Button.h"
#include "DemonBase.h"

#include "R_Captain.h"
#include "R_Wololo.h"
#include "R_Constrobot.h"
#include "R_Pulsar2280.h"

#include "Demon.h"
#include "DemonBoss.h"

#include "Portal.h"

//-----------------------------------------------------------------
// Consts
//-----------------------------------------------------------------
const int RES_W = 1200;
const int RES_H = 768;
const int NUM_MAP = 8;

const string RobotDemonSpottedMessages[5] = {
	"\"Demons!\"",
	"\"Atack!\"",
	"\"Here!\"",
	"\"Die demons!\"",
	"\"!@%#!\""
};

//-----------------------------------------------------------------
// Custom types
//-----------------------------------------------------------------

typedef vector<vector<int>> Map;

class Coordinate {
public:
	int x;
	int y;
	int dist;
	Coordinate* prev;
	POINT screenPos;

public:
	Coordinate(int _x, int _y) {
		x = _x; 
		y = _y;
		dist = 0;    
		prev = NULL;
		screenPos = { (x*32), (y*32) };
	}
	Coordinate(int _x, int _y, int _dist, Coordinate* _prev) {
		x = _x; 
		y = _y;
		dist = _dist; 
		prev = _prev;
		screenPos = { (x * 32), (y * 32) };
	}
};

//-----------------------------------------------------------------
// Scene Flags
//-----------------------------------------------------------------
enum Scene {
	MENU_MAIN = 0,
	MENU_SELECT_PLAYERS = 1,
	MENU_SELECT_ROBOTS = 2,
	GAME_PLAY = 3,
	GAME_PAUSE = 4
};

enum FogMapStatus {
	FMS_UNDISCOVERED = 0,
	FMS_DISCOVERED = 1,
	FMS_VISIBLE = 2
};

enum MapStatus {
	MAP_EMPTY = 0,
	MAP_BASE = 1,
	MAP_WALL = 2,
	MAP_ROBOT = 3,
	MAP_DEMON = 4,
	MAP_VISITED = 99, // path finding
};

//-----------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------
HINSTANCE   hInstance;
GameEngine* game;
HDC         offScreenDC;
HBITMAP     offScreenBitmap;
Scene		currentScene;

//-----------------------------------------------------------------
// Game
//-----------------------------------------------------------------
vector<DemonBase*> demonBases;
vector<Robot*>	robots; // all robots
vector<Robot*>	inGameRobots; // robots that are selected and will be loaded into actual game
vector<int>		selectedRobotIndexes; // store indexes of robots that are selected in robots vector
int				playerCount; // single player or multiplayer
int				numEnemyBases;
Map				maps[NUM_MAP];
Map				currentMap;
Map				fogMap;
int				currentMapIdx;
int				currentScore;
time_t			lastHealTime;//for general heal process
time_t			now;
bool			fow; // fog of war
int				portalCount;
POINT			portals[2];
wchar_t			textBuffer[1024];
POINT			gateWayPos;

//-----------------------------------------------------------------
// Input contorls
//-----------------------------------------------------------------
int		dlPlayer1Switch;
int		dlPlayer2Switch;
int		numSwitch; // counter for switching robots
int		fowSwitchDelay;
int		nextMapSwitchDelay;

//-----------------------------------------------------------------
// Bitmaps / Sprites
//-----------------------------------------------------------------

// Menu
Bitmap  	*bmMenuBackground;
Bitmap  	*bmMenuBackground2;
Bitmap  	*bmMenuTitle;
Bitmap  	*bmMenuStar;
Bitmap		*bmNormalRect, *bmBlackRect, *bmDarkRect; // for fog of war

// Game
Bitmap		*bmWall1, *bmWall2, *bmWall3;
Bitmap		*bmEnemyBase;
Bitmap		*bmBullet;
Bitmap		*bmDemonBullet;
Bitmap		*bmDemon;
Bitmap		*bmMonster;
Bitmap		*bmRobotMenu;
Bitmap		*bmExplosion;
Bitmap		*bmRobot1Walk;
Bitmap		*bmDemon1, *bmDemon1Explosion;
Bitmap		*bmBoss1;
Bitmap		*bmPortal;
Bitmap		*bmGateway;

Sprite		*spDemon;
WallSprite	*wallSprites[100];
Sprite		*demonBaseSprites[20];

DemonBoss	*demonBoss1;

Bitmap* animationBitmaps[20];

//-----------------------------------------------------------------
// Buttons
//-----------------------------------------------------------------
vector<Button*>	menuMainButtons, menuPlayersButtons, menuRobotsButtons;
Button			*btnPlay, *btnExit;
Button			*btn1Player, *btn2Player, *btnBackToMain;
Button			*btnReady, *btnBackToPlayers;


//-----------------------------------------------------------------
// FUNCTIONS
//-----------------------------------------------------------------
//-----------------------------------------------------------------
// Game (play) functions
//-----------------------------------------------------------------

// Initializing
void	CreateRobots(HDC _hDC);
void	InitializeGameWorld();
void	LoadNextLevel();
Map		CreateMap(bool _firstLevel);
Map		CreateBossMap();

// Update
void			Player1Controls();
void			Player2Controls();
Robot*			GetPlayersRobot(int _player);
void			SwitchRobot(int _player);
void			Fire(Character *character);
void			UpdateCharacters();
void			UpdateBases();
void			UpdateObstacles();
stack<POINT>	FollowRobot(POINT src, POINT dst, Map _map);
void			CheckAbilities();
void			HealWithPoints(); // her 10 sn bir healt pointi 50 den düşük olanlara total point üzerinden can verir.
Demon*			AddDemon(DemonBase* _base);
void			KillCharacter(Character* _character);
POINT			CheckCollisionBeforeMoving(Character *robot, POINT velocity);
stack<POINT>	DemonRoam(Demon *_demon, POINT robotposition, POINT baselocation, Map currentmap);
void			AddExplosion(POINT pos, int range, int damage);

//-----------------------------------------------------------------
// UI functions
//-----------------------------------------------------------------
void	DrawIndicators(HDC _hDC, Character* _character);
void	DrawRobotsOnMenu(HDC _hDC);
void	CreateButtons(HDC _hDC);
void	DrawRightMenu(HDC _hDC);

//-----------------------------------------------------------------
// Menu functions
//-----------------------------------------------------------------
void	HandleMenuButtonClick(int _x, int _y);
void	HandleMenuButtonHover(int _x, int _y);

//-----------------------------------------------------------------
// Utility functions
//-----------------------------------------------------------------
POINT			ScreenRectToArrayPoint(RECT _rect);
POINT			ScreenToArrayPoint(POINT _pt);
POINT			RectToPoint(RECT rect);
BOOL			CmpPoint(POINT p1, POINT p2);
void			PrintPath(stack<POINT> _path);
void			PrintPathOnScreen(HDC _hDC, stack<POINT> _path);
int				GetDistance(POINT p1, POINT p2);
LPWSTR			ConvertString(const string& instr);
int				CoordinateDistance(Coordinate *c1, Coordinate *c2);
stack<POINT>	FindPathBFS(POINT _src, POINT _dst, Map _currentMap);
Robot*			GetRobotAtMapPosition(int _x, int _y);
Demon*		    GetDemonAtMapPosition(int _x, int _y);
void			ResetFogMap(); // all to 0
void			ClearFogMap(); // all 2s to 1
void			SwitchFow();
void			ResetGame();

//-----------------------------------------------------------------
// AI Variables
//-----------------------------------------------------------------

class RBS_Demon_Main;
class FL_Demon_Main;

RBS_Demon_Main* rbsDemonMain = nullptr;
FL_Demon_Main* flDemonMain = nullptr;

Button* aiTechniqueButton = nullptr;