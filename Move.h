#pragma once
#include "DxLib.h"
#include <sstream>
#include"KeyInput.h"
#include "LoadFile.h"
#include "MapMake.h"
#include"Mouse.h"
#include"Struct.h"

class Move
{
public:
	void Update(int levelNum);
	void Initialize();
	//プレイヤー移動関数
	void PlayerMoveStart(int objX, int objY, int movePattern, int mapNum);

private:
	//配列要素数
	//マップ数
	int mapNum = 2;
	const int mapChipSize = 128;
	LoadFile* loadFile_ = nullptr;

	//プレイヤーのXY
	const int XY = 2;

	static const int playerPosX = 2;
	static const int playerPosY = 2;
	int playerPos[playerPosY][playerPosX] = { 0 };
	int playerGraph = LoadGraph("player.png");
	//キーボード
	KeyInput* keyInput_ = new KeyInput;
	Mouse* mouse_;
	bool selectNumberFlag = false;
	Box selectNumberBox[5];
	int selectNumber[5] = { 0 };

	//上下左右の番号
	enum class MoveNum
	{
		ZERO,
		LEFT,
		RIGHT,
		UP,
		DOWN
	};
};