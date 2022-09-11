#include"Move.h"
//File
#include <fstream>
#include <cassert>
void Move::Initialize()
{
	mouse_ = new Mouse();
	loadFile_ = LoadFile::GetInstance();
	for (int i = 0; i < 5; i++)
	{
		selectNumberBox[i] = { 1168,323 + (i * 144),96,96 };
	}
}


void Move::Update(int levelNum)
{
	mouse_->MouseUpdate();
	keyInput_->Update();

	DrawFormatString(0, 800, 0xFF, "%d,%d", mouse_->GetMousePos().x, mouse_->GetMousePos().y);

	for (int i = 0; i < 5; i++)
	{
		DrawBox(selectNumberBox[i].Left, selectNumberBox[i].Top, selectNumberBox[i].Left + selectNumberBox[i].Right, selectNumberBox[i].Top + selectNumberBox[i].Bottom, 0xFF, TRUE);

		if ((mouse_->MouseCheckHitBox(selectNumberBox[i], mouse_->GetMousePos())))
		{
			selectNumberFlag = true;
		}

		if (selectNumberFlag == true)
		{
			if (keyInput_->IsKeyTrigger(KEY_INPUT_1))
			{
				selectNumber[i] = 0;
				selectNumberFlag = false;
			}
			if (keyInput_->IsKeyTrigger(KEY_INPUT_2))
			{
				selectNumber[i] = 1;
				selectNumberFlag = false;
			}
			if (keyInput_->IsKeyTrigger(KEY_INPUT_3))
			{
				selectNumber[i] = 2;
				selectNumberFlag = false;
			}
			if (keyInput_->IsKeyTrigger(KEY_INPUT_4))
			{
				selectNumber[i] = 3;
				selectNumberFlag = false;
			}
			if (keyInput_->IsKeyTrigger(KEY_INPUT_5))
			{
				selectNumber[i] = 4;
				selectNumberFlag = false;
			}
		}
	}

	if (keyInput_->IsKeyTrigger(KEY_INPUT_SPACE))
	{
		for (int i = 0; i < 5; i++)
		{
			PlayerMoveStart(2, 2, selectNumber[i], levelNum);
		}
	}

#pragma region キーで動くがあとでクリックした矢印によってに変える
	//左
	if (keyInput_->IsKeyTrigger(KEY_INPUT_A))
	{
		DrawFormatString(100, 200, 0xFF, "AAAAAA");
		//パターン０
		PlayerMoveStart(2,2,0, levelNum);
	}
	//右
	if (keyInput_->IsKeyTrigger(KEY_INPUT_B))
	{
		DrawFormatString(100, 200, 0xFF, "AAAAAA");

		//パターン１
		PlayerMoveStart(1, 1, 1, levelNum);
	}
	//上
	if (keyInput_->IsKeyTrigger(KEY_INPUT_C))
	{
		DrawFormatString(100, 200, 0xFF, "AAAAAA");
		//パターン０
		PlayerMoveStart(1, 1, 2, levelNum);
	}
	//下
	if (keyInput_->IsKeyTrigger(KEY_INPUT_D))
	{
		DrawFormatString(100, 200, 0xFF, "AAAAAA");

		//パターン１
		PlayerMoveStart(1, 1, 3, levelNum);
	}

#pragma endregion

}


void Move::PlayerMoveStart(int objX, int objY, int movePattern, int mapNum)
{
	//コマンド回数を実行
	for (int i = 0; i < loadFile_->GetObjectNum(); i++)
	{
		//このままだとコマンドを一気に消化します。

		int x = 0; int y = 0;
		//指定されたコマンドの移動を代入
		if		(loadFile_->commandPosition[movePattern][i] == 0) break;
		else if (loadFile_->commandPosition[movePattern][i] == (int)MoveNum::LEFT)	x = -1;
		else if (loadFile_->commandPosition[movePattern][i] == (int)MoveNum::RIGHT) x = 1;
		else if (loadFile_->commandPosition[movePattern][i] == (int)MoveNum::UP)	y = -1;
		else if (loadFile_->commandPosition[movePattern][i] == (int)MoveNum::DOWN)	y = 1;

		//当たり対象ごとの判定
		if (loadFile_->mapDate[mapNum][objY + y][objX + x] == 3) {

		}
		else if (loadFile_->mapDate[mapNum][objY + y][objX + x] == 4) {

		}
		else if (loadFile_->mapDate[mapNum][objY + y][objX + x] == 6) {

		}
		else 
		{
			//当たり対象がなければ進む位置に移動し元にいた位置に地面
			loadFile_->mapDate[mapNum][objY + y][objX + x] = loadFile_->mapDate[mapNum][objY][objX];
			loadFile_->mapDate[mapNum][objY][objX] = 2;
		}
	}
}
