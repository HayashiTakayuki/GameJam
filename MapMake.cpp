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
/// ステージごとに描画
/// </summary>
/// <param name="stage">ステージの番号</param>
/// <param name="graphMap">マップチップのデータを入れる</param>
void MapMake::Draw(int stage, int* graphMap, int* graphPlayer, int* graphTruck)
{
	int boxsize = 128;
	int firstSetX = 160;
	int firstSetY = 128;

	// 一個目を表示したい位置に変える
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
		int posY = firstSetY + (boxsize * y);
		for (int x = 0; x < loadFile_->GetMapX(); x++) {
			int posX = (boxsize * x) + firstSetX;
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
