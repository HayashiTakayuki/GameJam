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
	
	//下のセレクトに表示する画像のXY
	int whareObjPosY = 891;

	//なんの画像を描画するか番号が入る
	int whatObj[5];
	
	//現在押したマップチップの番号
	int whatObjSelectNow;
	//セレクトの当たり判定に使う
	Box selectBox[5];

	Point objectArrayNum;
	int selectBoxNum;

public:
	void Initialize();
	MapMake();
	~MapMake();

	void Draw(int stage, int* graphMap, int* graphPlayer, int* graphTruck);

	//マウスでマップチップのデータを調べる
	void CheckMapChipDate(int stage);

	void DrawSelectBox(int stage,int* graphMap, int* graphPlayer, int* graphTruck);

	Point SelectMapChipArray(int x, int y);

	Point GetObjectArrayNum() { return objectArrayNum; }

	int GetSelectBoxNum(){ return 0; }
};

