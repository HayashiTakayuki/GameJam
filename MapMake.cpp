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
void MapMake::Draw(int stage, int *graphMap)
{
	int boxsize = 4;
	// 一個目を表示したい位置に変える
	int firstSetX = 0;
	int firstSetY = 0;

	int posY  = firstSetY;
	for (int y = 0; y < mapy; y++) {
		
		for (int x = 0; x < mapx; x++) {
			int posX = (boxsize * x) + firstSetX;

			DrawBox(posX, posY, posX + boxsize, posY + boxsize, graphMap[mapDate[stage][y][x]], true);

		}
		posY += boxsize;
	}
}
