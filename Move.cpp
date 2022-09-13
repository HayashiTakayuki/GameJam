#include"Move.h"
//File
#include <fstream>
#include <cassert>
void Move::Initialize()
{
	mouse_ = new Mouse();
	SelectSetObject::Initialize();
	loadFile_ = LoadFile::GetInstance();
	for (int i = 0; i < 5; i++) {
		movePatarn[i] = -1;
		keepPos[i] = { -1,-1 };

		for (int j = 0; j < 5; j++)
		{
			isAction_[j][i] = false;
		}
	}

	isCrear = false;
	isMove = false;
}


Move::~Move()
{
}

void Move::Update(int& levelNum, int cardbordSE, int truckSE, int rockSE)
{
	Reset();
	mouse_->MouseUpdate();
	keyInput_->Update();
	SelectSetObject::Update(levelNum);

	DrawFormatString(0, 40, 0xFFFFF, "levelNum%d", levelNum);

	if (keyInput_->IsKeyTrigger(KEY_INPUT_SPACE))
	{
		static int k = 0;
		k = 0;
		objectPos = SelectSetObject::array;
		int* movePatternSet = SelectSetObject::selectNo_;
		//マップの
		for (int i = 0; i < 5; i++) {
			//先頭のアドレスから次の番地の数をいれる
			Point* point_ = objectPos + i;
			//番地の数字をmoveクラス内で保持
			keepPos[i] = { point_->x, point_->y };
			for (int j = 0; j < 5; j++) {
				int* moveCharacter = movePatternSet + j;

				if (keepPos[i].x == -1 || keepPos[i].y == -1) {
					k += 1;
					break;
				}
				//マップの配列位置に何が入っているか求めてる
				if (loadFile_->mapDate[levelNum][point_->y][point_->x] == *moveCharacter)
				{
					movePatarn[k] = j;
					k += 1;
					j = 5;
				}
			}
		}
		isMove = true;
	}

	if (isMove) {
		waitTimer++;
		for (int i = 0; i < 5; i++) {
			actionSet = i;
			ObjectMoveStart(keepPos[i], movePatarn[i], levelNum, cardbordSE, truckSE, rockSE);
		}
	}

}


void Move::ObjectMoveStart(Point& pos, int movePattern, int& stageNum, int carbbordSE_, int truckSE_, int rockSE_)
{
	if (waitTimer <= waitTime) return;
	//コマンド回数を実行
	for (int i = 0; i < loadFile_->GetObjectNum(); i++)
	{
		//一度動いていたら次の行動へ
		if (isAction_[actionSet][i])continue;

		if (pos.x == -1 || pos.y == -1 || movePattern == -1) {
			break;
		}
		int x = 0; int y = 0;
		//指定されたコマンドの移動を代入
		if (loadFile_->commandPosition[movePattern][i] == NONE) break;
		else if (loadFile_->commandPosition[movePattern][i] == (int)MoveNum::LEFT)	x = -1;
		else if (loadFile_->commandPosition[movePattern][i] == (int)MoveNum::RIGHT) x = 1;
		else if (loadFile_->commandPosition[movePattern][i] == (int)MoveNum::UP)	y = -1;
		else if (loadFile_->commandPosition[movePattern][i] == (int)MoveNum::DOWN)	y = 1;

		bool hitFlag = false;

		int max = 0;

		if (stageNum == 0 || stageNum == 1 || stageNum == 4) { max = 5; }
		else { max = 6; }

		if (pos.x + x <= -1 || pos.x + x >= max)
		{
			if ((loadFile_->mapDate[stageNum][pos.y][pos.x] == MapChip::CARDBORD))
			{
				PlaySoundMem(carbbordSE_, DX_PLAYTYPE_BACK, TRUE);
			}
			if ((loadFile_->mapDate[stageNum][pos.y][pos.x] == MapChip::TRUCK))
			{
				PlaySoundMem(truckSE_, DX_PLAYTYPE_BACK, TRUE);
			}
			if ((loadFile_->mapDate[stageNum][pos.y][pos.x] >= MapChip::ROCK) && (loadFile_->mapDate[stageNum][pos.y][pos.x] <= MapChip::ROCK6))
			{
				PlaySoundMem(rockSE_, DX_PLAYTYPE_BACK, TRUE);
			}
			waitTimer = 0;
			isAction_[actionSet][i] = true;
			break;
		}

		if (pos.y + y == -1 || pos.y + y == max)
		{
			if ((loadFile_->mapDate[stageNum][pos.y][pos.x] == MapChip::CARDBORD))
			{
				PlaySoundMem(carbbordSE_, DX_PLAYTYPE_BACK, TRUE);
			}
			if ((loadFile_->mapDate[stageNum][pos.y][pos.x] == MapChip::TRUCK))
			{
				PlaySoundMem(truckSE_, DX_PLAYTYPE_BACK, TRUE);
			}
			if ((loadFile_->mapDate[stageNum][pos.y][pos.x] >= MapChip::ROCK) && (loadFile_->mapDate[stageNum][pos.y][pos.x] <= MapChip::ROCK6))
			{
				PlaySoundMem(rockSE_, DX_PLAYTYPE_BACK, TRUE);
			}
			waitTimer = 0;
			isAction_[actionSet][i] = true;
			break;
		}

		for (int j = 1; j < MapChip::END; j++)
		{
			//当たり対象ごとの判定
			if (loadFile_->mapDate[stageNum][pos.y + y][pos.x + x] == j)
			{
				if ((loadFile_->mapDate[stageNum][pos.y][pos.x] == MapChip::CARDBORD))
				{
					PlaySoundMem(carbbordSE_, DX_PLAYTYPE_BACK, TRUE);
				}
				if ((loadFile_->mapDate[stageNum][pos.y][pos.x] == MapChip::TRUCK))
				{
					PlaySoundMem(truckSE_, DX_PLAYTYPE_BACK, TRUE);
				}
				if ((loadFile_->mapDate[stageNum][pos.y][pos.x] >= MapChip::ROCK) && (loadFile_->mapDate[stageNum][pos.y][pos.x] <= MapChip::ROCK6))
				{
					PlaySoundMem(rockSE_, DX_PLAYTYPE_BACK, TRUE);
				}
				hitFlag = true;
			}
		}

		//進む先がトラックで
		if (loadFile_->mapDate[stageNum][pos.y + y][pos.x + x] == MapChip::TRUCK)
		{
			//進んでいるのが段ボールだったら
			if ((loadFile_->mapDate[stageNum][pos.y][pos.x] == MapChip::CARDBORD))
			{
				PlaySoundMem(carbbordSE_, DX_PLAYTYPE_BACK, TRUE);
				loadFile_->mapDate[stageNum][pos.y + y][pos.x + x] = MapChip::TRUCK;
				loadFile_->mapDate[stageNum][pos.y][pos.x] = NONE;//地面
				//stageNum++;
				isCrear = true;
			}
		}
		//進む先が段ボールで
		else if (loadFile_->mapDate[stageNum][pos.y + y][pos.x + x] == MapChip::CARDBORD)
		{
			//進んでいるのがトラックだったら
			if ((loadFile_->mapDate[stageNum][pos.y][pos.x] == MapChip::TRUCK))
			{
				PlaySoundMem(truckSE_, DX_PLAYTYPE_BACK, TRUE);
				loadFile_->mapDate[stageNum][pos.y + y][pos.x + x] = MapChip::TRUCK;
				loadFile_->mapDate[stageNum][pos.y][pos.x] = NONE;//地面
				//stageNum++;
				isCrear = true;
			}
		}
		else if (!hitFlag)
		{
			//当たり対象がなければ進む位置に移動し元にいた位置に地面
			loadFile_->mapDate[stageNum][pos.y + y][pos.x + x] = loadFile_->mapDate[stageNum][pos.y][pos.x];
			loadFile_->mapDate[stageNum][pos.y][pos.x] = NONE;//地面
			pos.x += x;
			pos.y += y;
			if ((loadFile_->mapDate[stageNum][pos.y][pos.x] == MapChip::CARDBORD))
			{
				PlaySoundMem(carbbordSE_, DX_PLAYTYPE_BACK, TRUE);
			}
			if ((loadFile_->mapDate[stageNum][pos.y][pos.x] == MapChip::TRUCK))
			{
				PlaySoundMem(truckSE_, DX_PLAYTYPE_BACK, TRUE);
			}
			if ((loadFile_->mapDate[stageNum][pos.y][pos.x] >= MapChip::ROCK) && (loadFile_->mapDate[stageNum][pos.y][pos.x] <= MapChip::ROCK6))
			{
				PlaySoundMem(rockSE_, DX_PLAYTYPE_BACK, TRUE);
			}
			
		}
		//一行動のあとに時間を戻す。
		waitTimer = 0;
		isAction_[actionSet][i] = true;
		return;
	}

}

void Move::Draw(int stage, int* graphMap, int* graphPlayer, int* graphTruck, int* spotLightHandle, int* setumeiHandle, int* rightChip)
{
	SelectSetObject::Draw(stage, graphMap, graphPlayer, graphTruck, spotLightHandle, setumeiHandle,rightChip);
}

void Move::Reset()
{
	if (keyInput_->IsKeyTrigger(KEY_INPUT_R))
	{
		SelectSetObject::Initialize();
		loadFile_ = LoadFile::GetInstance();
		for (int i = 0; i < 5; i++) {
			movePatarn[i] = -1;
			keepPos[i] = { -1,-1 };
		}
		for (int i = 0; i < loadFile_->GetObjectNum(); i++)
		{
			for (int j = 0; j < 4; j++)
			{
				isAction_[j][i] = false;
			}

		}
		loadFile_->LoadMap(loadFile_->GetMapX(), loadFile_->GetMapY(), loadFile_->GetMapName());
		isCrear = false;
	}
}


