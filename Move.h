#pragma once
#pragma once
#include "DxLib.h"
#include <sstream>
#include"KeyInput.h"


class Move
{
public:

	//初期化
	void Initialize();
	//描画
	void Draw(int levelNum);

	//マップチップ
	FILE* fp = NULL;

	//読み込んだCSVから配列に格納する関数
	void MoveDate();
	void LoadCommand(const char* c_commandName);

	//更新
	void Update(int levelNum);

	//プレイヤー移動関数
	void PlayerMoveStart(int movePattern, int mapNum);
	int GetCommandPosition() { return **commandPosition; }
private:
	//配列要素数

	//マップ数
	int mapNum = 2;
	const int mapChipSize = 128;

	//プレイヤーが持つ次数
	const int XY = 2;

	static const int playerPosX = 2;
	static const int playerPosY = 2;
	int playerPos[playerPosY][playerPosX] = { 0 };//

	//プレイヤーの画像
	int playerGraph = LoadGraph("player.png");

	//コマンドの数
	static const int commandNum = 8;
	//コマンドを割り当てる物体の数
	static const int objctNum = 100;

	//コマンドの順番を決める数
	int comandOrder = 0;
	//コマンドの数
	int commandNumA = 0;

	//コマンド[オブジェクトNo.][コマンド数]
	int commandPosition[objctNum][commandNum] = { 0 };

	//移動方向コマンド
	std::stringstream command;

	//キーボード
	KeyInput* keyInput_ = nullptr;

	//上下左右の番号
	enum class MoveNum
	{
		ZERO,//無し
		LEFT,//左
		RIGHT,//右
		UP,//上
		DOWN//下
	};
};