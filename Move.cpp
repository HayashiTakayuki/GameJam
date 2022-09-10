#include"Move.h"
//File
#include <fstream>
#include <cassert>


void Move::Update(int levelNum)
{
	keyInput_->Update();
	
#pragma region �L�[�œ��������ƂŃN���b�N�������ɂ���Ăɕς���
	//��
	if (keyInput_->IsKeyTrigger(KEY_INPUT_A))
	{
		DrawFormatString(100, 200, 0xFF, "AAAAAA");
		//�p�^�[���O
		PlayerMoveStart(1,1,0, levelNum);
	}
	//�E
	if (keyInput_->IsKeyTrigger(KEY_INPUT_B))
	{
		DrawFormatString(100, 200, 0xFF, "AAAAAA");

		//�p�^�[���P
		PlayerMoveStart(1, 1, 1, levelNum);
	}
	//��
	if (keyInput_->IsKeyTrigger(KEY_INPUT_C))
	{
		DrawFormatString(100, 200, 0xFF, "AAAAAA");
		//�p�^�[���O
		PlayerMoveStart(1, 1, 2, levelNum);
	}
	//��
	if (keyInput_->IsKeyTrigger(KEY_INPUT_D))
	{
		DrawFormatString(100, 200, 0xFF, "AAAAAA");

		//�p�^�[���P
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
	//�R�}���h�񐔂����s
	for (int i = 0; i < loadFile_->GetObjectNum(); i++)
	{
		//���̂܂܂��ƃR�}���h����C�ɏ������܂��B

		int x = 0; int y = 0;
		//�w�肳�ꂽ�R�}���h�̈ړ�����
		if		(loadFile_->commandPosition[movePattern][i] == (int)MoveNum::LEFT)		x = -1;
		else if (loadFile_->commandPosition[movePattern][i] == (int)MoveNum::RIGHT)	x = 1;
		else if (loadFile_->commandPosition[movePattern][i] == (int)MoveNum::UP)	y = -1;
		else if (loadFile_->commandPosition[movePattern][i] == (int)MoveNum::DOWN)	y = 1;

		//������Ώۂ��Ƃ̔���
		if (loadFile_->mapDate[mapNum][objY + y][objX + x] == 3) {

		}
		else if (loadFile_->mapDate[mapNum][objY + y][objX + x] == 4) {

		}
		else if (loadFile_->mapDate[mapNum][objY + y][objX + x] == 6) {

		}
		else {
			//������Ώۂ��Ȃ���ΐi�ވʒu�Ɉړ������ɂ����ʒu�ɒn��
			loadFile_->mapDate[mapNum][objY + y][objX + x] = loadFile_->mapDate[mapNum][objY][objX];
			loadFile_->mapDate[mapNum][objY][objX] = 2;
		}
	}
}
