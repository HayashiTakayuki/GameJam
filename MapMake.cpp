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
/// ステージごとに描画
/// </summary>
/// <param name="stage">ステージの番号</param>
/// <param name="graphMap">マップチップのデータを入れる</param>
void MapMake::Draw(int stage, int* graphMap, int* graphPlayer, int* graphTruck)
{
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
	// 一個目を表示したい位置に変える
	if (stage < 1) { firstSetX = 224; firstSetY = 192; }
	if (stage >= 1) { firstSetX = 160; firstSetY = 128; }

	mouse_->MouseUpdate();
	MapChipDate.x = (mouse_->GetMousePos().x - firstSetX) / mapChipSize;
	MapChipDate.y = (mouse_->GetMousePos().y - firstSetY) / mapChipSize;
	
	DrawFormatString(0, 60, 0xFFF, "AA%d%d", objectArrayNum.x, objectArrayNum.y);

	//左押されたら
	if (mouse_->MouseInput(MOUSE_INPUT_LEFT))
	{
		//マウスの配列の番号を確認
		//地面じゃなかったら
		if (loadFile_->mapDate[stage][MapChipDate.y][MapChipDate.x] != 0)
		{
			//0の場合その配列番号を保存
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
	//左クリックしたところのマップチップ番号を変数に入れる関数
	CheckMapChipDate(stage);
	//セレクトボックスが５個だから

	for (int i = 0; i < 5; i++)
	{
		//セレクトボックスのN番目を左クリックしたとき
		if (mouse_->MouseCheckHitBox(selectBox[i], mouse_->GetMousePos()))
		{
			int space = 198;
			//今変数に入れて保存していた番号を格納
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
