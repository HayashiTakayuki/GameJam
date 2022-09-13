#include "SelectSetObject.h"
#include "DxLib.h"

SelectSetObject::SelectSetObject() {

	for (int i = 0; i < 5; i++)
	{
		orderBox_[i] = { 82 + (i * 198),orderSetPosY_,128,128 };
		selectBox_[i] = { 1168,323 + (i * 144),96,96 };
	}
	//initialize()に書くか問題
	loadFile_ = LoadFile::GetInstance();
	mouse_ = new Mouse();
}

void SelectSetObject::Initialize()
{
	for (int i = 0; i < 5; i++)
	{
		array[i] = { -1,-1 };

		whatObj[i] = 0;
		selectWhatObj[i] = 0;
	}
	spotGraphNum = 0;
	setumeiGraphNum = 0;
}

SelectSetObject::~SelectSetObject()
{
	delete mouse_;
}

void SelectSetObject::CheckMapChipDate(int stage)
{
	Point objectPoint = { 0,0 };

	int firstSetX = 0, firstSetY = 0;

	// 一個目を表示したい位置に変える
	//5x5が上 , 6x6が下
	if (stage == 0 || stage == 1 || stage == 4) { firstSetX = 224; firstSetY = 192; }
	if (stage == 2 || stage == 3 || stage == 5) { firstSetX = 160; firstSetY = 128; }

	mouse_->MouseUpdate();

	//クリックした行列を取得

	//左押されたら
	if (mouse_->MouseInput(MOUSE_INPUT_LEFT))
	{
		objectPoint.x = (mouse_->GetMousePos().x - firstSetX) / mapChipSize_;
		objectPoint.y = (mouse_->GetMousePos().y - firstSetY) / mapChipSize_;

		if (objectPoint.y >= 0 && objectPoint.y <= 5 && objectPoint.x >= 0 && objectPoint.x <= 5)
		{
			//マウスが取得した配列の番号を確認
			//地面じゃなかったら
			if (loadFile_->mapDate[stage][objectPoint.y][objectPoint.x] != MapChip::NONE)
			{
				if (loadFile_->mapDate[stage][objectPoint.y][objectPoint.x] == MapChip::ANA)
				{
					return;
				}
				if (loadFile_->mapDate[stage][objectPoint.y][objectPoint.x] == MapChip::ROCK)
				{
					if (enemy > 5)
					{
						return;
					}
					loadFile_->mapDate[stage][objectPoint.y][objectPoint.x] = MapChip::ROCK + enemy;
					enemy++;
				}

				//0の場合その配列番号を保存
				whatObjSelectNow = loadFile_->mapDate[stage][objectPoint.y][objectPoint.x];
				haveMapChip = objectPoint;
				isOrder_ = false;
				isSelect_ = false;
				if (stage == 0 && setumeiGraphNum == 0) { setumeiGraphNum++; spotGraphNum++; }
			}
		}
	}
}


void SelectSetObject::Draw(int stage, int* graphMap, int* graphPlayer, int* graphTruck, int* spotLightHandle, int* setumeiHandle)
{
	if (stage == 0)
	{
		DrawGraph(0, 0, spotLightHandle[spotGraphNum], TRUE);
		DrawGraph(0, 0, setumeiHandle[setumeiGraphNum], TRUE);
	}

	for (int i = 0; i < 5; i++)
	{
		//左下の描画
		if (whatObj[i] != MapChip::NONE)
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
		if (selectWhatObj[i] != MapChip::NONE)
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

	if (!isOrder_ || !isSelect_) {
		Point mousePos = mouse_->GetMousePos();
		Point nearMouse = { 0,0 };
		if (isOrder_ && mousePos.y > 900 && mousePos.x > 82 && mousePos.x < 1005) {}
		else if (isSelect_ && mousePos.x >= 1088) {}
		else if (whatObjSelectNow == MapChip::TRUCK) {
			nearMouse = { -32,-12 };
			DrawGraph(mousePos.x + nearMouse.x, mousePos.y + nearMouse.y, graphTruck[0], true);
		}
		else if (whatObjSelectNow == MapChip::CARDBORD) {
			nearMouse = { -32,-32 };
			DrawGraph(mousePos.x + nearMouse.x, mousePos.y + nearMouse.y, graphPlayer[0], true);
		}
		else if (whatObjSelectNow != MapChip::NONE) {
			DrawGraph(mousePos.x, mousePos.y, graphMap[whatObjSelectNow], true);
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
			if (stage == 0 && setumeiGraphNum == 1){ setumeiGraphNum++; spotGraphNum++; }
			
			//今変数に入れて保存していた番号を格納
			whatObj[i] = whatObjSelectNow; //who
			//配列番号が何番目に実行するか、マップの位置を持ってる
			array[i] = haveMapChip;
			isOrder_ = true;
		}

		if (mouse_->MouseCheckHitBox(selectBox_[i], mouse_->GetMousePos()) && !isSelect_)
		{
			if (stage == 0 && setumeiGraphNum == 2) { setumeiGraphNum++; spotGraphNum++; }
			//今変数に入れて保存していた番号を格納
			selectWhatObj[i] = whatObjSelectNow; //who

			selectNo_[i] = whatObjSelectNow;
			isSelect_ = true;
		}

		//コマンドかオーダーに入れたら
		if (isOrder_ || isSelect_) {
			//旧と新をみて、もし同じだったら新しいのを残す
			for (int j = 0; j < 5; j++) {
				if (i == j)continue;
				if (isOrder_ && whatObj[i] == whatObj[j]) {
					array[j] = { -1,-1 };
					whatObj[j] = MapChip::NONE;
				}
				if (isSelect_ && selectWhatObj[i] == selectWhatObj[j]) { 
					selectNo_[j] = -1;
					selectWhatObj[j] = MapChip::NONE; 
				}
			}
		}
	}
}