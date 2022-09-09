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
#pragma region キーで動くがあとでクリックした矢印によってに変える
	//左
	if (keyInput_->IsKeyTrigger(KEY_INPUT_A))
	{
		DrawFormatString(100, 200, 0xFF, "AAAAAA");
		//パターン０
		PlayerMoveStart(0, levelNum);
	}
	//右
	if (keyInput_->IsKeyTrigger(KEY_INPUT_B))
	{
		DrawFormatString(100, 200, 0xFF, "AAAAAA");

		//パターン１
		PlayerMoveStart(1, levelNum);
	}
	//上
	if (keyInput_->IsKeyTrigger(KEY_INPUT_C))
	{
		DrawFormatString(100, 200, 0xFF, "AAAAAA");
		//パターン０
		PlayerMoveStart(2, levelNum);
	}
	//下
	if (keyInput_->IsKeyTrigger(KEY_INPUT_D))
	{
		DrawFormatString(100, 200, 0xFF, "AAAAAA");

		//パターン１
		PlayerMoveStart(3, levelNum);
	}

#pragma endregion
*/
}

void Move::PlayerMoveStart(int objX, int objY, int movePattern, int mapNum)
{
	//コマンド回数を実行
	for (int i = 0; i < commandNum; i++)
	{
		//このままだとコマンドを一気に消化します。

		int x = 0; int y = 0;
		//指定されたコマンドの移動を代入
		if (commandPosition[movePattern][i] == (int)MoveNum::LEFT)x = -1;
		else if (commandPosition[movePattern][i] == (int)MoveNum::RIGHT)x = 1;
		else if (commandPosition[movePattern][i] == (int)MoveNum::UP)y = -1;
		else if (commandPosition[movePattern][i] == (int)MoveNum::DOWN)x = 1;

		//当たり対象ごとの判定
		if (mapMake_->mapDate[mapNum][objY + y][objX + x] == MapChip::ROCK) {

		}
		else if (mapMake_->mapDate[mapNum][objY + y][objX + x] == MapChip::GROUND) {

		}
		else if (mapMake_->mapDate[mapNum][objY + y][objX + x] == MapChip::PLAYER) {

		}
		else {
			//当たり対象がなければ進む位置に移動し元にいた位置に地面
			mapMake_->mapDate[mapNum][objY + y][objX + x] = mapMake_->mapDate[mapNum][objY][objX];
			mapMake_->mapDate[mapNum][objY][objX] = MapChip::GROUND;
		}
	}
}

void Move::MoveDate()
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
					commandPosition[commandNumA][comandOrder] = 1;
					comandOrder++;
				}
				//左に進む
				else if (word.find("R") == 0)
				{
					commandPosition[commandNumA][comandOrder] = 2;
					comandOrder++;
				}
				//左に進む
				else if (word.find("U") == 0)
				{
					commandPosition[commandNumA][comandOrder] = 3;
					comandOrder++;
				}
				//左に進む
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
				//左に進む
				getline(line_stream, word, ',');
				if (word.find("L") == 0)
				{
					commandPosition[commandNumA][comandOrder] = 1;
					comandOrder++;
				}
				//左に進む
				else if (word.find("R") == 0)
				{
					commandPosition[commandNumA][comandOrder] = 2;
					comandOrder++;
				}
				//左に進む
				else if (word.find("U") == 0)
				{
					commandPosition[commandNumA][comandOrder] = 3;
					comandOrder++;
				}
				//左に進む
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
				//左に進む
				getline(line_stream, word, ',');
				if (word.find("L") == 0)
				{
					commandPosition[commandNumA][comandOrder] = 1;
					comandOrder++;
				}
				//左に進む
				else if (word.find("R") == 0)
				{
					commandPosition[commandNumA][comandOrder] = 2;
					comandOrder++;
				}
				//左に進む
				else if (word.find("U") == 0)
				{
					commandPosition[commandNumA][comandOrder] = 3;
					comandOrder++;
				}
				//左に進む
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
		//次の行に移動するときに配列の番号をインクリメント
		commandNumA++;
	}
}

void Move::LoadCommand(const char* c_commandName)
{
	//ファイルを開く
	std::ifstream file;
	file.open(c_commandName);
	assert(file.is_open());

	//ファイルの内容を文字列ストリームにコピー
	command << file.rdbuf();

	//ファイルを閉じる
	file.close();

	MoveDate();
}
