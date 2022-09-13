#pragma once
#include "LoadFile.h"
#include "Struct.h"
#include "Mouse.h"

class SelectSetObject
{
protected:
	SelectSetObject();
	~SelectSetObject();
	void CheckMapChipDate(int stage);
	void Draw(int stage, int* graphMap, int* graphPlayer, int* graphTruck, int* spotLightHandle, int* setumeiHandle);
	void Update(int stage);
	void Initialize();

	Point* GetNextMovePoint() { return array; }
	int* GetNextMoveNum() { return selectNo_; };
	Point array[5] = { 0 };
	int selectNo_[5] = { -1,-1,-1,-1,-1 };

private:
	Mouse* mouse_;
	int mapChipSize_ = 128;
	LoadFile* loadFile_;


	const int objNum_ = 10;
	//���݉������}�b�v�`�b�v�̔ԍ�
	int whatObjSelectNow;
	//�Z���N�g�̓����蔻��Ɏg��
	Box orderBox_[5] = { 0 };

	//�Ȃ�̉摜��`�悷�邩�ԍ�������
	int whatObj[5] = { 0 };
	//���̃Z���N�g�ɕ\������摜��XY
	int orderSetPosY_ = 891;

	bool isOrder_ = false;
	//�z��ԍ������ԖڂɎ��s���邩�A�}�b�v�̈ʒu��ۑ�
	//�N���b�N���������Ă���}�b�v�z���ۑ�
	Point haveMapChip;

	//�E�͂�
	int selectWhatObj[5] = { 0 };
	Box selectBox_[5];
	bool isSelect_ = false;

	int enemy = 1;

	int spotGraphNum = 0;
	int setumeiGraphNum = 0;
};

