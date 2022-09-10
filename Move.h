#pragma once
#pragma once
#include "DxLib.h"
#include <sstream>
#include"KeyInput.h"


class Move
{
public:

	//������
	void Initialize();
	//�`��
	void Draw(int levelNum);

	//�}�b�v�`�b�v
	FILE* fp = NULL;

	//�ǂݍ���CSV����z��Ɋi�[����֐�
	void MoveDate();
	void LoadCommand(const char* c_commandName);

	//�X�V
	void Update(int levelNum);

	//�v���C���[�ړ��֐�
	void PlayerMoveStart(int movePattern, int mapNum);
	int GetCommandPosition() { return **commandPosition; }
private:
	//�z��v�f��

	//�}�b�v��
	int mapNum = 2;
	const int mapChipSize = 128;

	//�v���C���[��������
	const int XY = 2;

	static const int playerPosX = 2;
	static const int playerPosY = 2;
	int playerPos[playerPosY][playerPosX] = { 0 };//

	//�v���C���[�̉摜
	int playerGraph = LoadGraph("player.png");

	//�R�}���h�̐�
	static const int commandNum = 8;
	//�R�}���h�����蓖�Ă镨�̂̐�
	static const int objctNum = 100;

	//�R�}���h�̏��Ԃ����߂鐔
	int comandOrder = 0;
	//�R�}���h�̐�
	int commandNumA = 0;

	//�R�}���h[�I�u�W�F�N�gNo.][�R�}���h��]
	int commandPosition[objctNum][commandNum] = { 0 };

	//�ړ������R�}���h
	std::stringstream command;

	//�L�[�{�[�h
	KeyInput* keyInput_ = nullptr;

	//�㉺���E�̔ԍ�
	enum class MoveNum
	{
		ZERO,//����
		LEFT,//��
		RIGHT,//�E
		UP,//��
		DOWN//��
	};
};