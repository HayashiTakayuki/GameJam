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
	void Update(int& levelNum);
	void Initialize();
	//プレイヤー移動関数
	void ObjectMoveStart(Point &pos, int movePattern, int& mapNum);
	void Draw(int stage, int* graphMap, int* graphPlayer, int* graphTruck, int* spotLightHandle, int* setumeiHandle , int* rightChip);
	void Reset();

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


	bool isMove = false;
	//コマンドのステップのため
	int waitTimer = 60;
	int waitTime = 60;
	bool isAction_[5][5] = { false };
	int actionSet = 0;

	bool isClear = false;
	bool isFaile = false;
};