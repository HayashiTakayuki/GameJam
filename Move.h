#pragma once
#include "DxLib.h"
#include <sstream>
#include"KeyInput.h"
#include "LoadFile.h"
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