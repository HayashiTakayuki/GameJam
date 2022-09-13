#include "MapMake.h"
#include "DxLib.h"


void MapMake::Initialize()
{
	loadFile_ = LoadFile::GetInstance();
}

MapMake::MapMake()
{
	mapChipSize = 128;
}

MapMake::~MapMake()
{
}

/// <summary>
/// ステージごとに描画
/// </summary>
/// <param name="stage">ステージの番号</param>
/// <param name="graphMap">マップチップのデータを入れる</param>
void MapMake::Draw(int stage, int* graphMap, int* graphPlayer, int* graphTruck)
{
	int firstSetX = 160;
	int firstSetY = 128;

	// 一個目を表示したい位置に変える
	if (stage == 0 || stage == 1 || stage == 4)
	{
		firstSetX = 224;
		firstSetY = 192;
	}
	if (stage == 2 || stage == 3 || stage == 5)
	{
		firstSetX = 160;
		firstSetY = 128;
	}

	for (int y = 0; y < loadFile_->GetMapY(); y++) {
		int posY = firstSetY + (mapChipSize * y);
		for (int x = 0; x < loadFile_->GetMapX(); x++) {
			int posX = (mapChipSize * x) + firstSetX;
			DrawGraph(posX, posY, graphMap[loadFile_->mapDate[stage][y][x]], true);
			
			if (loadFile_->mapDate[stage][y][x] == MapChip::CARDBORD)
			{
				DrawGraph(posX, posY, graphPlayer[0], true);
			}

			if (loadFile_->mapDate[stage][y][x] == MapChip::TRUCK)
			{
				DrawGraph(posX, posY, graphTruck[0], true);
			}
		}
	}
}
