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
	//現在押したマップチップの番号
	int whatObjSelectNow;
	//セレクトの当たり判定に使う
	Box orderBox_[5] = { 0 };

	//なんの画像を描画するか番号が入る
	int whatObj[5] = { 0 };
	//下のセレクトに表示する画像のXY
	int orderSetPosY_ = 891;

	bool isOrder_ = false;
	//配列番号が何番目に実行するか、マップの位置を保存
	//クリックした持っているマップ配列を保存
	Point haveMapChip;

	//右はし
	int selectWhatObj[5] = { 0 };
	Box selectBox_[5];
	bool isSelect_ = false;

	int enemy = 1;

	int spotGraphNum = 0;
	int setumeiGraphNum = 0;
};

