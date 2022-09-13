#include "LoadFile.h"
#include <fstream>
#include <cassert>

LoadFile::LoadFile()
	:commandPosition(),mapDate(),mapName(),mapX_(),mapY_()
{
}
LoadFile::~LoadFile()
{
}

void LoadFile::MoveDate()
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

		else if (word.find('3') == 0)
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

		else if (word.find('4') == 0)
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


void LoadFile::LoadCommand(const char** c_commandName)
{
	//�t�@�C�����J��
	std::ifstream file;
	file.open(*c_commandName);
	assert(file.is_open());

	//�t�@�C���̓��e�𕶎���X�g���[���ɃR�s�[
	command << file.rdbuf();

	//�t�@�C�������
	file.close();

	MoveDate();
}

LoadFile* LoadFile::GetInstance()
{
	static LoadFile instance;
	return &instance;
}

void LoadFile::LoadMap(int mapX, int mapY, const char** Name) {
	mapX_ = mapX;
	mapY_ = mapY;
	mapName = Name;
	int stage = 0;
	while (1) {
		FILE* fp = NULL;
		fopen_s(&fp, mapName[stage], "r");
		if (fp == NULL) break;

		for (int y = 0; y < mapY_; y++) {

			for (int x = 0; x < mapX_; x++) {

				fscanf_s(fp, "%d,", &mapDate[stage][y][x]);
			}
		}
		fclose(fp);
		stage++;
	}
};
