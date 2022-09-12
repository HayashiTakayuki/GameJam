#include "SelectSetObject.h"
#include "DxLib.h"

SelectSetObject::SelectSetObject() {
	for (int i = 0; i < 5; i++)
	{
		orderBox_[i] = { 82 + (i * 198),orderSetPosY_,128,128 };
		selectBox_[i] = { 1168,323 + (i * 144),96,96 };
	}
	mouse_ = new Mouse();

	//initialize()に書くか問題
	loadFile_ = LoadFile::GetInstance();
}

SelectSetObject::~SelectSetObject()
{
	delete mouse_;
}

void SelectSetObject::CheckMapChipDate(int stage)
{
	Point objectPoint = { 0,0 };

	int firstSetX = 160;
	int firstSetY = 128;
	// 一個目を表示したい位置に変える
	//5x5が上 , 6x6が下
	if (stage < 1) { firstSetX = 224; firstSetY = 192; }
	if (stage >= 1) { firstSetX = 160; firstSetY = 128; }

	mouse_->MouseUpdate();
	objectPoint.x = (mouse_->GetMousePos().x - firstSetX) / mapChipSize_;
	objectPoint.y = (mouse_->GetMousePos().y - firstSetY) / mapChipSize_;

	//左押されたら
	if (mouse_->MouseInput(MOUSE_INPUT_LEFT))
	{
		//マウスの配列の番号を確認
		//地面じゃなかったら
		if (loadFile_->mapDate[stage][objectPoint.y][objectPoint.x] != 0)
		{
			//0の場合その配列番号を保存
			whatObjSelectNow = loadFile_->mapDate[stage][objectPoint.y][objectPoint.x];
			haveMapChip = objectPoint;
			isOrder_ = false;
			isSelect_ = false;
		}
	}
}


void SelectSetObject::Draw(int stage, int* graphMap, int* graphPlayer, int* graphTruck)
{


	for (int i = 0; i < 5; i++)
	{
		//左下の描画
		if (whatObj[i] != 0)
		{
			DrawGraph(orderBox_[i].Left, orderSetPosY_, graphMap[whatObj[i]], true);
			if (whatObj[i] == MapChip::CARDBORD)
			{
				DrawGraph(orderBox_[i].Left, orderSetPosY_, graphPlayer[0], true);
			}

			if (whatObj[i] == MapChip::TRUCK)
			{
				DrawGraph(orderBox_[i].Left, orderSetPosY_, graphTruck[0], true);
			}
		}
		//右選択側の描画
		if (selectWhatObj[i] != 0)
		{
			DrawGraph(selectBox_[i].Left, selectBox_[i].Top, graphMap[selectWhatObj[i]], true);
			if (selectWhatObj[i] == MapChip::CARDBORD)
			{
				DrawGraph(selectBox_[i].Left, selectBox_[i].Top, graphPlayer[0], true);
			}

			if (selectWhatObj[i] == MapChip::TRUCK)
			{
				DrawGraph(selectBox_[i].Left, selectBox_[i].Top, graphTruck[0], true);
			}
		}
	}

}

void SelectSetObject::Update(int stage)
{

	//左クリックしたところのマップチップ番号を変数に入れる関数
	CheckMapChipDate(stage);
	//セレクトボックスが５個だから

	for (int i = 0; i < 5; i++)
	{
		//セレクトボックスのN番目を左クリックしたとき
		if (mouse_->MouseCheckHitBox(orderBox_[i], mouse_->GetMousePos()) && !isOrder_)
		{
			//今変数に入れて保存していた番号を格納
			whatObj[i] = whatObjSelectNow; //who
			//配列番号が何番目に実行するか、マップの位置を持ってる
			array[i] = haveMapChip;
			isOrder_ = true;
		}

		if (mouse_->MouseCheckHitBox(selectBox_[i], mouse_->GetMousePos()) && !isSelect_)
		{
			//今変数に入れて保存していた番号を格納
			selectWhatObj[i] = whatObjSelectNow; //who

			selectNo_[i] = whatObjSelectNow;
			isSelect_ = true;
		}
	}

}

