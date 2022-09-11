#pragma once
#include <ctype.h>
#include <fstream>
#include "LoadFile.h"
#include"Mouse.h"
#include"Struct.h"

enum  MapChip {
	GROUND,
	GROUND2,
	PLAYER,
	ROCK
};
class MapMake
{
private:
	LoadFile* loadFile_ = nullptr;

	Mouse* mouse_;
	int mapChipSize = 128;
	
	//���̃Z���N�g�ɕ\������摜��XY
	int whareObjPosY = 891;

	//�Ȃ�̉摜��`�悷�邩�ԍ�������
	int whatObj[5];
	
	//���݉������}�b�v�`�b�v�̔ԍ�
	int whatObjSelectNow;
	//�Z���N�g�̓����蔻��Ɏg��
	Box selectBox[5];

	Point objectArrayNum;
	int selectBoxNum;

public:
	void Initialize();
	MapMake();
	~MapMake();

	void Draw(int stage, int* graphMap, int* graphPlayer, int* graphTruck);

	//�}�E�X�Ń}�b�v�`�b�v�̃f�[�^�𒲂ׂ�
	void CheckMapChipDate(int stage);

	void DrawSelectBox(int stage,int* graphMap, int* graphPlayer, int* graphTruck);

	Point SelectMapChipArray(int x, int y);

	Point GetObjectArrayNum() { return objectArrayNum; }

	int GetSelectBoxNum(){ return 0; }
};

