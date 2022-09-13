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
	void Update(int& levelNum, int cardbordSE, int truckSE, int rockSE);
	void Initialize();
	//�v���C���[�ړ��֐�
	void ObjectMoveStart(Point &pos, int movePattern, int& mapNum,int cardbordSE_,int truckSE_,int rockSE_);
	void Draw(int stage, int* graphMap, int* graphPlayer, int* graphTruck, int* spotLightHandle, int* setumeiHandle ,int* rightChip);
	void Reset();

	bool GetIsCrear() { return isCrear; }
private:
	//�z��v�f��
	//�}�b�v��
	const int mapChipSize = 128;
	LoadFile* loadFile_ = nullptr;
	//�L�[�{�[�h
	KeyInput* keyInput_ = new KeyInput;
	Mouse* mouse_;

	int movePatarn[5] = {0};
	Point *objectPos;
	Point keepPos[5] = {0};


	bool isMove = false;
	//�R�}���h�̃X�e�b�v�̂���
	int waitTimer = 60;
	int waitTime = 60;
	bool isAction_[5][5] = { false };
	int actionSet = 0;

	bool isCrear = false;

};