#include "MapMake.h"
#include "DxLib.h"


void MapMake::Initialize()
{
	loadFile_ = LoadFile::GetInstance();
}

MapMake::MapMake()
{
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

	int boxsize = 128;
	// ��ڂ�\���������ʒu�ɕς���
	int firstSetX = 160;
	int firstSetY = 128;

	for (int y = 0; y < loadFile_->GetMapY(); y++) {
		int posY = firstSetY + (boxsize * y);
		for (int x = 0; x < loadFile_->GetMapX(); x++) {
			int posX = (boxsize * x) + firstSetX;
			DrawGraph(posX, posY, graphMap[loadFile_->mapDate[stage][y][x]], true);
			
			if (loadFile_->mapDate[stage][y][x] == 3)
			{
				DrawGraph(posX, posY, graphPlayer[0], true);
			}

			if (loadFile_->mapDate[stage][y][x] == 4)
			{
				DrawGraph(posX, posY, graphTruck[0], true);
			}

			if (loadFile_->mapDate[stage][y][x] == 3)
			{
				DrawGraph(posX, posY, graphPlayer[0], true);
			}
		}
	}
}
