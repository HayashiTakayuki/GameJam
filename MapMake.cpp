#include "MapMake.h"
#include "DxLib.h"


MapMake::MapMake(int mapx, int mapy, const char** Name)
{
	this->mapx = mapx;
	this->mapy = mapy;
	this->mapName = Name;

	LoadMap();
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
	// 一個目を表示したい位置に変える
	int firstSetX = 160;
	int firstSetY = 128;

	for (int y = 0; y < mapy; y++) {
		int posY = firstSetY + (boxsize * y);
		for (int x = 0; x < mapx; x++) {
			int posX = (boxsize * x) + firstSetX;
			DrawGraph(posX, posY, graphMap[mapDate[stage][y][x]], true);

			if (mapDate[stage][y][x] == 3)
			{
				DrawGraph(posX, posY, graphPlayer[0], true);
			}

			if (mapDate[stage][y][x] == 4)
			{
				DrawGraph(posX, posY, graphTruck[0], true);
			}

		}
	}
}
