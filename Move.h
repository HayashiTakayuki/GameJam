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
	//�v���C���[�ړ��֐�
	void PlayerMoveStart(int objX, int objY, int movePattern, int mapNum);

private:
	//�z��v�f��
	//�}�b�v��
	int mapNum = 2;
	const int mapChipSize = 128;
	LoadFile* loadFile_ = nullptr;

	//�v���C���[��XY
	const int XY = 2;

	static const int playerPosX = 2;
	static const int playerPosY = 2;
	int playerPos[playerPosY][playerPosX] = { 0 };
	int playerGraph = LoadGraph("player.png");
	//�L�[�{�[�h
	KeyInput* keyInput_ = new KeyInput;
	Mouse* mouse_;
	bool selectNumberFlag = false;
	Box selectNumberBox[5];
	int selectNumber[5] = { 0 };

	//�㉺���E�̔ԍ�
	enum class MoveNum
	{
		ZERO,
		LEFT,
		RIGHT,
		UP,
		DOWN
	};
};