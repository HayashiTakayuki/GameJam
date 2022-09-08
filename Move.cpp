#include"Move.h"
//FIle
#include <fstream>
#include <cassert>

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

	//�t�@�C�����J��
	std::ifstream file;
	file.open("moveCommand.csv");
	assert(file.is_open());

	//�t�@�C���̓��e�𕶎���X�g���[���ɃR�s�[
	command << file.rdbuf();

	//�t�@�C�������
	file.close();

	MoveDate();
}

void Move::Draw(int levelNum)
{
	DrawGraph(playerPos[levelNum][0] * mapChipSize, playerPos[levelNum][1] * mapChipSize, playerGraph, true);
	DrawFormatString(100, 400, 0xFFFFF, "%d,%d", playerPos[levelNum][0], playerPos[levelNum][1]);
}

void Move::Update(int levelNum)
{
	keyInput_->Update();

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
}

void Move::PlayerMoveStart(int movePattern, int mapNum)
{
	for (int i = 0; i < commandNum; i++)
	{
		if (commandPosition[movePattern][i] == (int)MoveNum::LEFT)
		{
			playerPos[mapNum][0] -= 1;
		}
		else if (commandPosition[movePattern][i] == (int)MoveNum::RIGHT)
		{
			playerPos[mapNum][0] += 1;
		}
		else if (commandPosition[movePattern][i] == (int)MoveNum::UP)
		{
			playerPos[mapNum][1] += 1;
		}
		else if (commandPosition[movePattern][i] == (int)MoveNum::DOWN)
		{
			playerPos[mapNum][1] -= 1;
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
		else
		{
			comandOrder = 0;
			break;
		}

		commandNumA++;
	}
}