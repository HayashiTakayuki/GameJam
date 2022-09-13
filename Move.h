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
	//�v���C���[�ړ��֐�
	void ObjectMoveStart(Point &pos, int movePattern, int& mapNum);
	void Draw(int stage, int* graphMap, int* graphPlayer, int* graphTruck);
private:
	//�z��v�f��
	//�}�b�v��
	const int mapChipSize = 128;
	LoadFile* loadFile_ = nullptr;
	//�L�[�{�[�h
	KeyInput* keyInput_ = new KeyInput;
	Mouse* mouse_;
	int waitTimer = 0;
	int waitTime = 60;
	bool waitFlag[5][5];

	bool isMove = false;
	int movePatarn[5] = {0};
	Point *objectPos;
	Point keepPos[5] = {0};
};