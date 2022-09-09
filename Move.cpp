#include"Move.h"
//File
#include <fstream>
#include <cassert>
#include "MapMake.h"
#include "CreateArrow.h"
void Move::Initialize()
{
	keyInput_ = new KeyInput();

	fopen_s(&fp, "playerPos.csv", "r");
	if (fp != NULL)
	{
		for (int y = 0; y < mapNum; y++)
		{
			for (int x = 0; x < XY; x++)
			{
				fscanf_s(fp, "%d,", &playerPos[y][x]);
			}
		}
		fclose(fp);
	}
}

void Move::Draw() {
}

void Move::Update(int levelNum)
{
	keyInput_->Update();
	/*
#pragma region �L�[�œ��������ƂŃN���b�N�������ɂ���Ăɕς���
	//��
	if (keyInput_->IsKeyTrigger(KEY_INPUT_A))
	{
		DrawFormatString(100, 200, 0xFF, "AAAAAA");
		//�p�^�[���O
		PlayerMoveStart(0, levelNum);
	}
	//�E
	if (keyInput_->IsKeyTrigger(KEY_INPUT_B))
	{
		DrawFormatString(100, 200, 0xFF, "AAAAAA");

		//�p�^�[���P
		PlayerMoveStart(1, levelNum);
	}
	//��
	if (keyInput_->IsKeyTrigger(KEY_INPUT_C))
	{
		DrawFormatString(100, 200, 0xFF, "AAAAAA");
		//�p�^�[���O
		PlayerMoveStart(2, levelNum);
	}
	//��
	if (keyInput_->IsKeyTrigger(KEY_INPUT_D))
	{
		DrawFormatString(100, 200, 0xFF, "AAAAAA");

		//�p�^�[���P
		PlayerMoveStart(3, levelNum);
	}

#pragma endregion
*/
}

void Move::PlayerMoveStart(int objX, int objY, int movePattern, int mapNum)
{
	//�R�}���h�񐔂����s
	for (int i = 0; i < commandNum; i++)
	{
		//���̂܂܂��ƃR�}���h����C�ɏ������܂��B

		int x = 0; int y = 0;
		//�w�肳�ꂽ�R�}���h�̈ړ�����
		if (commandPosition[movePattern][i] == (int)MoveNum::LEFT)x = -1;
		else if (commandPosition[movePattern][i] == (int)MoveNum::RIGHT)x = 1;
		else if (commandPosition[movePattern][i] == (int)MoveNum::UP)y = -1;
		else if (commandPosition[movePattern][i] == (int)MoveNum::DOWN)x = 1;

		//������Ώۂ��Ƃ̔���
		if (mapMake_->mapDate[mapNum][objY + y][objX + x] == MapChip::ROCK) {

		}
		else if (mapMake_->mapDate[mapNum][objY + y][objX + x] == MapChip::GROUND) {

		}
		else if (mapMake_->mapDate[mapNum][objY + y][objX + x] == MapChip::PLAYER) {

		}
		else {
			//������Ώۂ��Ȃ���ΐi�ވʒu�Ɉړ������ɂ����ʒu�ɒn��
			mapMake_->mapDate[mapNum][objY + y][objX + x] = mapMake_->mapDate[mapNum][objY][objX];
			mapMake_->mapDate[mapNum][objY][objX] = MapChip::GROUND;
		}
	}
}

void Move::MoveDate()
{
	//1�s���̕����������ϐ�
	std::string line;

	//�R�}���h���s���[�v
	while (getline(command, line))
	{
		std::istringstream line_stream(line);
		std::string word;
		//,��؂�ōs�̐擪�������擾
		getline(line_stream, word, ',');

		//"//"����n�܂�s�̓R�����g
		if (word.find("//") == 0)
		{
			//�R�����g�s���΂�
			continue;
		}

#pragma region �ŏ��̐�����ǂݎ��CSV�̕����𐔎��ɕς��z��ɓ����
		if (word.find('1') == 0)
		{
			while (1)
			{
				//���ɐi��
				getline(line_stream, word, ',');
				if (word.find("L") == 0)
				{
					commandPosition[commandNumA][comandOrder] = (int)MoveNum::LEFT;
					comandOrder++;
				}
				//���ɐi��
				else if (word.find("R") == 0)
				{
					commandPosition[commandNumA][comandOrder] = (int)MoveNum::RIGHT;
					comandOrder++;
				}
				//���ɐi��
				else if (word.find("U") == 0)
				{
					commandPosition[commandNumA][comandOrder] = (int)MoveNum::UP;
					comandOrder++;
				}
				//���ɐi��
				else if (word.find("D") == 0)
				{
					commandPosition[commandNumA][comandOrder] = (int)MoveNum::DOWN;
					comandOrder++;
				}
				else if (word.find("E") == 0)
				{
					comandOrder = 0;
					break;
				}
			}
		}
		else if (word.find('2') == 0)
		{
			while (1)
			{
				//���ɐi��
				getline(line_stream, word, ',');
				if (word.find("L") == 0)
				{
					commandPosition[commandNumA][comandOrder] = 1;
					comandOrder++;
				}
				//���ɐi��
				else if (word.find("R") == 0)
				{
					commandPosition[commandNumA][comandOrder] = 2;
					comandOrder++;
				}
				//���ɐi��
				else if (word.find("U") == 0)
				{
					commandPosition[commandNumA][comandOrder] = 3;
					comandOrder++;
				}
				//���ɐi��
				else if (word.find("D") == 0)
				{
					commandPosition[commandNumA][comandOrder] = 4;
					comandOrder++;
				}
				else if (word.find("E") == 0)
				{
					comandOrder = 0;
					break;
				}
			}
		}

		else if (word.find('3') == 0)
		{
			while (1)
			{
				//���ɐi��
				getline(line_stream, word, ',');
				if (word.find("L") == 0)
				{
					commandPosition[commandNumA][comandOrder] = 1;
					comandOrder++;
				}
				//���ɐi��
				else if (word.find("R") == 0)
				{
					commandPosition[commandNumA][comandOrder] = 2;
					comandOrder++;
				}
				//���ɐi��
				else if (word.find("U") == 0)
				{
					commandPosition[commandNumA][comandOrder] = 3;
					comandOrder++;
				}
				//���ɐi��
				else if (word.find("D") == 0)
				{
					commandPosition[commandNumA][comandOrder] = 4;
					comandOrder++;
				}
				else if (word.find("E") == 0)
				{
					comandOrder = 0;
					break;
				}
			}
		}

		else if (word.find('4') == 0)
		{
			while (1)
			{
				//���ɐi��
				getline(line_stream, word, ',');
				if (word.find("L") == 0)
				{
					commandPosition[commandNumA][comandOrder] = 1;
					comandOrder++;
				}
				//���ɐi��
				else if (word.find("R") == 0)
				{
					commandPosition[commandNumA][comandOrder] = 2;
					comandOrder++;
				}
				//���ɐi��
				else if (word.find("U") == 0)
				{
					commandPosition[commandNumA][comandOrder] = 3;
					comandOrder++;
				}
				//���ɐi��
				else if (word.find("D") == 0)
				{
					commandPosition[commandNumA][comandOrder] = 4;
					comandOrder++;
				}
				else if (word.find("E") == 0)
				{
					comandOrder = 0;
					break;
				}
			}
		}
#pragma endregion
		else
		{
			comandOrder = 0;
			break;
		}
		//���̍s�Ɉړ�����Ƃ��ɔz��̔ԍ����C���N�������g
		commandNumA++;
	}
}

void Move::LoadCommand(const char* c_commandName)
{
	//�t�@�C�����J��
	std::ifstream file;
	file.open(c_commandName);
	assert(file.is_open());

	//�t�@�C���̓��e�𕶎���X�g���[���ɃR�s�[
	command << file.rdbuf();

	//�t�@�C�������
	file.close();

	MoveDate();
}
