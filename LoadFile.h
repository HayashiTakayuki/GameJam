#pragma once
#include <sstream>

class LoadFile
{
private:
	LoadFile();
	~LoadFile();

	LoadFile(const LoadFile& obj) = delete;
	LoadFile& operator=(const LoadFile& obj) = delete;
	//�ړ������R�}���h
	std::stringstream command;

	//�R�}���h�̏��Ԃ����߂鐔
	int comandOrder = 0;
	//�R�}���h�̐�
	int commandNumA = 0;

	//�㉺���E�̔ԍ�
	enum class MoveNum
	{
		ZERO,
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

	void MoveDate();
	const char **mapName;

	static const int stageNum = 10;
	int mapX_;
	int mapY_;
	//�R�}���h�̐�(���̐�)
	static const int commandNum = 8;
	//�R�}���h�����蓖�Ă镨�̂̐�(�Z�b�g�̐�)
	static const int objectNum = 5;
	//�R�}���h
public:
	int GetMapY() { return mapY_; }
	int GetMapX() { return mapX_; }
	int GetCommandNum() { return commandNum; }
	int GetObjectNum() { return objectNum; }
	void LoadCommand(const char* c_commandName);
	void LoadMap(int mapX, int mapY, const char** Name);

	int mapDate[stageNum][8][8];
	int commandPosition[objectNum][commandNum];

	static LoadFile* GetInstance();

	//�㉺���E�̔ԍ�
	enum MapChip
	{
		ZERO,
		CARDBORD,
		TRUCK,
		ROCK,
	};


};

