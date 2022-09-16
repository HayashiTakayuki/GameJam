#pragma once
#include "DxLib.h"
#include <sstream>
#include"KeyInput.h"
#include "LoadFile.h"
#include "MapMake.h"
#include"Mouse.h"
#include"Struct.h"
#include "SelectSetObject.h"
class Move : public SelectSetObject
{
public:
	~Move();
	void Update(int& levelNum, int cardbordSE, int truckSE, int rockSE, int failedSE, int clearSE,int resetSE,int ketteiSE);
	void Initialize();
	//プレイヤー移動関数
	void ObjectMoveStart(Point &pos, int movePattern, int& mapNum,int cardbordSE_,int truckSE_,int rockSE_, int clearSE_);
	void Draw(int stage, int* graphMap, int* graphPlayer, int* graphTruck, int* spotLightHandle, int* setumeiHandle ,int* rightChip, int* arrowPanel,int * sppedPanel);
	void Reset(int resetSE_);

	bool GetIsCrear() { return isClear; }
	bool GetIsFaile() { return isFaile; }
private:
	//配列要素数
	//マップ数
	const int mapChipSize = 128;
	LoadFile* loadFile_ = nullptr;
	//キーボード
	KeyInput* keyInput_ = new KeyInput;
	Mouse* mouse_;

	int movePatarn[5] = {0};
	Point *objectPos;
	Point keepPos[5] = {0};

	Box moveSpeedUp = { 1116,20,82,84 };
	bool isMove = false;
	//コマンドのステップのため
	int waitTimer = 60;
	int waitTime = 61;
	bool isAction_[5][6] = { false };
	int actionSet = 0;
	bool isClear = false;
	bool isFaile = false;
	bool isOldFaile = false;

	int arrowX = 0;
	int arrowY = 0;
	int arrowPosX = 0;
	int arrowPosY = 0;
};