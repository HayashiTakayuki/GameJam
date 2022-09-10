#include"Move.h"
//File
#include <fstream>
#include <cassert>


void Move::Update(int levelNum)
{
	keyInput_->Update();
	
#pragma region キーで動くがあとでクリックした矢印によってに変える
	//左
	if (keyInput_->IsKeyTrigger(KEY_INPUT_A))
	{
		DrawFormatString(100, 200, 0xFF, "AAAAAA");
		//パターン０
		PlayerMoveStart(1,1,0, levelNum);
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

void Move::Initialize()
{
	loadFile_ = LoadFile::GetInstance();
}

void Move::PlayerMoveStart(int objX, int objY, int movePattern, int mapNum)
{
	//コマンド回数を実行
	for (int i = 0; i < loadFile_->GetObjectNum(); i++)
	{
		//このままだとコマンドを一気に消化します。

		int x = 0; int y = 0;
		//指定されたコマンドの移動を代入
		if		(loadFile_->commandPosition[movePattern][i] == (int)MoveNum::LEFT)		x = -1;
		else if (loadFile_->commandPosition[movePattern][i] == (int)MoveNum::RIGHT)	x = 1;
		else if (loadFile_->commandPosition[movePattern][i] == (int)MoveNum::UP)	y = -1;
		else if (loadFile_->commandPosition[movePattern][i] == (int)MoveNum::DOWN)	y = 1;

		//当たり対象ごとの判定
		if (loadFile_->mapDate[mapNum][objY + y][objX + x] == 3) {

		}
		else if (loadFile_->mapDate[mapNum][objY + y][objX + x] == 4) {

		}
		else if (loadFile_->mapDate[mapNum][objY + y][objX + x] == 6) {

		}
		else {
			//当たり対象がなければ進む位置に移動し元にいた位置に地面
			loadFile_->mapDate[mapNum][objY + y][objX + x] = loadFile_->mapDate[mapNum][objY][objX];
			loadFile_->mapDate[mapNum][objY][objX] = 2;
		}
	}
}
