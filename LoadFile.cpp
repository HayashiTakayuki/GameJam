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
	//1行分の文字列を入れる変数
	std::string line;

	//コマンド実行ループ
	while (getline(command, line))
	{
		std::istringstream line_stream(line);
		std::string word;
		//,区切りで行の先頭文字を取得
		getline(line_stream, word, ',');

		//"//"から始まる行はコメント
		if (word.find("//") == 0)
		{
			//コメント行を飛ばす
			continue;
		}

#pragma region 最初の数字を読み取りCSVの文字を数字に変え配列に入れる
		if (word.find('1') == 0)
		{
			while (1)
			{
				//左に進む
				getline(line_stream, word, ',');
				if (word.find("L") == 0)
				{
					commandPosition[commandNumA][comandOrder] = (int)MoveNum::LEFT;
					comandOrder++;
				}
				//左に進む
				else if (word.find("R") == 0)
				{
					commandPosition[commandNumA][comandOrder] = (int)MoveNum::RIGHT;
					comandOrder++;
				}
				//左に進む
				else if (word.find("U") == 0)
				{
					commandPosition[commandNumA][comandOrder] = (int)MoveNum::UP;
					comandOrder++;
				}
				//左に進む
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
				//左に進む
				getline(line_stream, word, ',');
				if (word.find("L") == 0)
				{
					commandPosition[commandNumA][comandOrder] = (int)MoveNum::LEFT;
					comandOrder++;
				}
				//左に進む
				else if (word.find("R") == 0)
				{
					commandPosition[commandNumA][comandOrder] = (int)MoveNum::RIGHT;
					comandOrder++;
				}
				//左に進む
				else if (word.find("U") == 0)
				{
					commandPosition[commandNumA][comandOrder] = (int)MoveNum::UP;
					comandOrder++;
				}
				//左に進む
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
				//左に進む
				getline(line_stream, word, ',');
				if (word.find("L") == 0)
				{
					commandPosition[commandNumA][comandOrder] = (int)MoveNum::LEFT;
					comandOrder++;
				}
				//左に進む
				else if (word.find("R") == 0)
				{
					commandPosition[commandNumA][comandOrder] = (int)MoveNum::RIGHT;
					comandOrder++;
				}
				//左に進む
				else if (word.find("U") == 0)
				{
					commandPosition[commandNumA][comandOrder] = (int)MoveNum::UP;
					comandOrder++;
				}
				//左に進む
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
				//左に進む
				getline(line_stream, word, ',');
				if (word.find("L") == 0)
				{
					commandPosition[commandNumA][comandOrder] = (int)MoveNum::LEFT;
					comandOrder++;
				}
				//左に進む
				else if (word.find("R") == 0)
				{
					commandPosition[commandNumA][comandOrder] = (int)MoveNum::RIGHT;
					comandOrder++;
				}
				//左に進む
				else if (word.find("U") == 0)
				{
					commandPosition[commandNumA][comandOrder] = (int)MoveNum::UP;
					comandOrder++;
				}
				//左に進む
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
		//次の行に移動するときに配列の番号をインクリメント
		commandNumA++;
	}
}


void LoadFile::LoadCommand(const char** c_commandName)
{
	//ファイルを開く
	std::ifstream file;
	file.open(*c_commandName);
	assert(file.is_open());

	//ファイルの内容を文字列ストリームにコピー
	command << file.rdbuf();

	//ファイルを閉じる
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
