#include "MapMake.h"
#include "DxLib.h"


void MapMake::Initialize()
{
	loadFile_ = LoadFile::GetInstance();
}

MapMake::MapMake()
{
	mouse_ = new Mouse();
	mapChipSize = 128;
	for (int i = 0; i < 5; i++)
	{
		selectBox[i] = { 82 +(i*198),891,128,128};
	}
}

MapMake::~MapMake()
{
}

/// <summary>
/// �X�e�[�W���Ƃɕ`��
/// </summary>
/// <param name="stage">�X�e�[�W�̔ԍ�</param>
/// <param name="graphMap">�}�b�v�`�b�v�̃f�[�^������</param>
void MapMake::Draw(int stage, int* graphMap, int* graphPlayer, int* graphTruck)
{
	int firstSetX = 160;
	int firstSetY = 128;

	// ��ڂ�\���������ʒu�ɕς���
	if (stage < 1)
	{
		firstSetX = 224;
		firstSetY = 192;
	}
	if (stage >= 1)
	{
		firstSetX = 160;
		firstSetY = 128;
	}

	for (int y = 0; y < loadFile_->GetMapY(); y++) {
		int posY = firstSetY + (mapChipSize * y);
		for (int x = 0; x < loadFile_->GetMapX(); x++) {
			int posX = (mapChipSize * x) + firstSetX;
			DrawGraph(posX, posY, graphMap[loadFile_->mapDate[stage][y][x]], true);
			
			if (loadFile_->mapDate[stage][y][x] == loadFile_->CARDBORD)
			{
				DrawGraph(posX, posY, graphPlayer[0], true);
			}

			if (loadFile_->mapDate[stage][y][x] == loadFile_->TRUCK)
			{
				DrawGraph(posX, posY, graphTruck[0], true);
			}
		}
	}
}

void MapMake::CheckMapChipDate(int stage)
{
	Point MapChipDate = { 0,0 };

	int firstSetX = 160;
	int firstSetY = 128;
	// ��ڂ�\���������ʒu�ɕς���
	if (stage < 1) { firstSetX = 224; firstSetY = 192; }
	if (stage >= 1) { firstSetX = 160; firstSetY = 128; }

	mouse_->MouseUpdate();
	MapChipDate.x = (mouse_->GetMousePos().x - firstSetX) / mapChipSize;
	MapChipDate.y = (mouse_->GetMousePos().y - firstSetY) / mapChipSize;
	
	DrawFormatString(0, 60, 0xFFF, "AA%d%d", objectArrayNum.x, objectArrayNum.y);

	//�������ꂽ��
	if (mouse_->MouseInput(MOUSE_INPUT_LEFT))
	{
		//�}�E�X�̔z��̔ԍ����m�F
		//�n�ʂ���Ȃ�������
		if (loadFile_->mapDate[stage][MapChipDate.y][MapChipDate.x] != 0)
		{
			//0�̏ꍇ���̔z��ԍ���ۑ�
			whatObjSelectNow = loadFile_->mapDate[stage][MapChipDate.y][MapChipDate.x];
			objectArrayNum = SelectMapChipArray(MapChipDate.x, MapChipDate.y);
		}
	}
}

Point MapMake::SelectMapChipArray(int x, int y)
{
	Point point;
	point.x = x;
	point.y = y;
	return point;
}

void MapMake::DrawSelectBox(int stage,int* graphMap, int* graphPlayer, int* graphTruck)
{
	//���N���b�N�����Ƃ���̃}�b�v�`�b�v�ԍ���ϐ��ɓ����֐�
	CheckMapChipDate(stage);
	//�Z���N�g�{�b�N�X���T������

	for (int i = 0; i < 5; i++)
	{
		//�Z���N�g�{�b�N�X��N�Ԗڂ����N���b�N�����Ƃ�
		if (mouse_->MouseCheckHitBox(selectBox[i], mouse_->GetMousePos()))
		{
			int space = 198;
			//���ϐ��ɓ���ĕۑ����Ă����ԍ����i�[
			whatObj[i] = whatObjSelectNow;
			whatObjSelectNow = 0;
			//selectFlag[i] = TRUE;
			break;
		}
	}

	for (int i = 0; i < 5; i++)
	{
		if (whatObj[i] != 0)
		{
			DrawGraph(selectBox[i].Left, whareObjPosY, graphMap[whatObj[i]], true);
			if (whatObj[i] == loadFile_->CARDBORD)
			{
				DrawGraph(selectBox[i].Left, whareObjPosY, graphPlayer[0], true);
			}

			if (whatObj[i] == loadFile_->TRUCK)
			{
				DrawGraph(selectBox[i].Left, whareObjPosY, graphTruck[0], true);
			}
		}
	}
}
