#include"Move.h"
//File
#include <fstream>
#include <cassert>
void Move::Initialize()
{
	mouse_ = new Mouse();
	loadFile_ = LoadFile::GetInstance();
	for (int i = 0; i < 5; i++) {
		movePatarn[i] = -1;
		keepPos[i] = { -1,-1 };
	}
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
		int *movePatternSet = SelectSetObject::selectNo_;
		//マップの
		for (int i = 0; i < 5; i++) {
			//先頭のアドレスから次の番地の数をいれる
			Point* point_ =  objectPos + i;
			//番地の数字をmoveクラス内で保持
			keepPos[i] = { point_->x, point_->y };
			for (int j = 0; j < 5; j++) {
				int* moveCharacter = movePatternSet + j;

				//マップの配列位置に何が入っているか求めてる
				static int k = 0;
				if (loadFile_->mapDate[levelNum][point_->y][point_->x] == *moveCharacter) {
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
		for (int i = 0; i < 5; i++) {
			
			ObjectMoveStart(keepPos[i], movePatarn[i], levelNum);
			if (i == 1) { 
				int aa = 1;
			};

		}
		isMove = false;
	}	

}


void Move::ObjectMoveStart(Point& pos, int movePattern, int stageNum)
{

	//コマンド回数を実行
	for (int i = 0; i < loadFile_->GetObjectNum(); i++)
	{
		if (pos.x == -1 || pos.y == -1 || movePattern == -1) {
			continue;
		}
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
		else if (loadFile_->mapDate[stageNum][pos.y + y][pos.x + x] == 4) {

		}
		else if (loadFile_->mapDate[stageNum][pos.y + y][pos.x + x] == 5) {

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


