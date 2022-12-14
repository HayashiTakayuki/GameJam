#pragma once
#include <sstream>

//上下左右の番号
enum class MoveNum
{
	ZERO,
	LEFT,
	RIGHT,
	UP,
	DOWN
};
//マップのなまえ番号
enum MapChip
{
	NONE,
	CARDBORD,
	TRUCK,
	ROCK,
	ROCK2,
	ROCK3,
	ROCK4,
	ROCK5,
	ROCK6,
	ANA,
	END,
};

class LoadFile
{
private:
	LoadFile();
	~LoadFile();

	LoadFile(const LoadFile& obj) = delete;
	LoadFile& operator=(const LoadFile& obj) = delete;
	//移動方向コマンド
	std::stringstream command;

	//コマンドの順番を決める数
	int comandOrder = 0;
	//コマンドの数
	int commandNumA = 0;


	void MoveDate();
	const char **mapName;

	static const int stageNum = 10;
	int mapX_;
	int mapY_;
	//コマンドの数(矢印の数)
	static const int commandNum = 7;
	//コマンドを割り当てる物体の数(セットの数)
	static const int objectNum = 5;
	//コマンド
public:
	int GetMapY() { return mapY_; }
	int GetMapX() { return mapX_; }
	const char** GetMapName() { return mapName; }
	int GetCommandNum() { return commandNum; }
	int GetObjectNum() { return objectNum; }
	void LoadCommand(const char* c_commandName);
	void LoadMap(int mapX, int mapY, const char** Name);

	int mapDate[stageNum][8][8];
	//配列[何番目のセット][実行の]


	int commandPosition[objectNum][commandNum];

	static LoadFile* GetInstance();

};

