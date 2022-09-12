#include"Move.h"
//File
#include <fstream>
#include <cassert>
void Move::Initialize()
{
	mouse_ = new Mouse();
	loadFile_ = LoadFile::GetInstance();
}


Move::~Move()
{
}

void Move::Update(int levelNum)
{
	mouse_->MouseUpdate();
	keyInput_->Update();
	SelectSetObject::Update(levelNum);

	if (keyInput_->IsKeyTrigger(KEY_INPUT_SPACE))
	{
		objectPos = SelectSetObject::array;
		int* movePatternSet = SelectSetObject::selectNo_;
		//マップの
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 5; j++) {
				if (movePatternSet[j] == -1) {
					j = 5;
				}
				//マップの配列位置に何が入っているか求めてる
				static int k = 0;
				if (loadFile_->mapDate[levelNum][objectPos[i].y][objectPos[i].x] == *movePatternSet) {
					movePatarn[k] = j;
					k += 1;
					j = 5;
				}
			}
		}
		isMove = true;
	}

	if (isMove) {
		if (objectPos == nullptr)return;
		for (int i = 0; i < 4; i++) {
			ObjectMoveStart(objectPos[i], movePatarn[i], levelNum);
			int a = 1;
		}
		isMove = false;
	}	

}


void Move::ObjectMoveStart(Point& pos, int movePattern, int stageNum)
{

	//コマンド回数を実行
	for (int i = 0; i < loadFile_->GetObjectNum(); i++)
	{

		int x = 0; int y = 0;
		//指定されたコマンドの移動を代入
		if		(loadFile_->commandPosition[movePattern][i] == NONE) break;
		else if (loadFile_->commandPosition[movePattern][i] == (int)MoveNum::LEFT)	x = -1;
		else if (loadFile_->commandPosition[movePattern][i] == (int)MoveNum::RIGHT) x = 1;
		else if (loadFile_->commandPosition[movePattern][i] == (int)MoveNum::UP)	y = -1;
		else if (loadFile_->commandPosition[movePattern][i] == (int)MoveNum::DOWN)	y = 1;

		//当たり対象ごとの判定
		if (loadFile_->mapDate[stageNum][pos.y + y][pos.x + x] == MapChip::ROCK) {

		}
		else if (loadFile_->mapDate[stageNum][pos.y + y][pos.x + x] == MapChip::TRUCK) {

		}
		else if (loadFile_->mapDate[stageNum][pos.y + y][pos.x + x] == MapChip::CARDBORD) {

		}
		else 
		{
			if (waitTimer == 0) {
				//当たり対象がなければ進む位置に移動し元にいた位置に地面
				loadFile_->mapDate[stageNum][pos.y + y][pos.x + x] = loadFile_->mapDate[stageNum][pos.y][pos.x];
				loadFile_->mapDate[stageNum][pos.y][pos.x] = NONE;//地面
				pos.x += x;
				pos.y += y;
			}
			
		}
	}

}

void Move::Draw(int stage, int* graphMap, int* graphPlayer, int* graphTruck)
{
	SelectSetObject::Draw(stage, graphMap, graphPlayer, graphTruck);
}


