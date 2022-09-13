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
	}

	isCrear = false;
}


Move::~Move()
{
}

void Move::Update(int& levelNum)
{
	mouse_->MouseUpdate();
	keyInput_->Update();
	SelectSetObject::Update(levelNum);

	DrawFormatString(0, 40, 0xFFFFF, "levelNum%d", levelNum);

	if (keyInput_->IsKeyTrigger(KEY_INPUT_SPACE))
	{
		objectPos = SelectSetObject::array;
		int* movePatternSet = SelectSetObject::selectNo_;
		//�}�b�v��
		for (int i = 0; i < 5; i++) {
			//�擪�̃A�h���X���玟�̔Ԓn�̐��������
			Point* point_ = objectPos + i;
			//�Ԓn�̐�����move�N���X���ŕێ�
			keepPos[i] = { point_->x, point_->y };
			for (int j = 0; j < 5; j++) {
				int* moveCharacter = movePatternSet + j;
				static int k = 0;
				if (keepPos[i].x == -1 || keepPos[i].y == -1) {
					k += 1;
					break;
				}
				//�}�b�v�̔z��ʒu�ɉ��������Ă��邩���߂Ă�
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
			ObjectMoveStart(keepPos[i], movePatarn[i], levelNum);
		}
	}

}


void Move::ObjectMoveStart(Point& pos, int movePattern, int& stageNum)
{
	if (waitTimer <= waitTime) return;
	//�R�}���h�񐔂����s
	for (int i = 0; i < loadFile_->GetObjectNum(); i++)
	{
		//��x�����Ă����玟�̍s����
		if (isAction_[actionSet][i])continue;

		if (pos.x == -1 || pos.y == -1 || movePattern == -1) {
			break;
		}
		int x = 0; int y = 0;
		//�w�肳�ꂽ�R�}���h�̈ړ�����
		if (loadFile_->commandPosition[movePattern][i] == NONE) break;
		else if (loadFile_->commandPosition[movePattern][i] == (int)MoveNum::LEFT)	x = -1;
		else if (loadFile_->commandPosition[movePattern][i] == (int)MoveNum::RIGHT) x = 1;
		else if (loadFile_->commandPosition[movePattern][i] == (int)MoveNum::UP)	y = -1;
		else if (loadFile_->commandPosition[movePattern][i] == (int)MoveNum::DOWN)	y = 1;

		bool hitFlag = false;

		for (int j = 1; j < MapChip::END; j++)
		{
			//������Ώۂ��Ƃ̔���
			if (loadFile_->mapDate[stageNum][pos.y + y][pos.x + x] == j) 
			{
				hitFlag = true;
			}
		}

		//�i�ސ悪�g���b�N��
		if (loadFile_->mapDate[stageNum][pos.y + y][pos.x + x] == MapChip::TRUCK) 
		{
			//�i��ł���̂��i�{�[����������
			if ((loadFile_->mapDate[stageNum][pos.y][pos.x] == MapChip::CARDBORD))
			{
				loadFile_->mapDate[stageNum][pos.y + y][pos.x + x] = MapChip::TRUCK;
				loadFile_->mapDate[stageNum][pos.y][pos.x] = NONE;//�n��
				//stageNum++;
				isCrear = true;
			}
		}
		//�i�ސ悪�i�{�[����
		else if (loadFile_->mapDate[stageNum][pos.y + y][pos.x + x] == MapChip::CARDBORD)
		{
			//�i��ł���̂��g���b�N��������
			if ((loadFile_->mapDate[stageNum][pos.y][pos.x] == MapChip::TRUCK))
			{
				loadFile_->mapDate[stageNum][pos.y + y][pos.x + x] = MapChip::TRUCK;
				loadFile_->mapDate[stageNum][pos.y][pos.x] = NONE;//�n��
				//stageNum++;
				isCrear = true;
			}
		}
		else if(!hitFlag)
		{
			//������Ώۂ��Ȃ���ΐi�ވʒu�Ɉړ������ɂ����ʒu�ɒn��
			loadFile_->mapDate[stageNum][pos.y + y][pos.x + x] = loadFile_->mapDate[stageNum][pos.y][pos.x];
			loadFile_->mapDate[stageNum][pos.y][pos.x] = NONE;//�n��
			pos.x += x;
			pos.y += y;
		}
		//��s���̂��ƂɎ��Ԃ�߂��B
		waitTimer = 0;
		isAction_[actionSet][i] = true;
		return;
	}

}

void Move::Draw(int stage, int* graphMap, int* graphPlayer, int* graphTruck)
{
	SelectSetObject::Draw(stage, graphMap, graphPlayer, graphTruck);
}


