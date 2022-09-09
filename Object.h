#pragma once
#pragma once
#include <vector>

enum class ObjectType//�I�u�W�F�N�g�̎��
{
	NONE,
	PLAYER,
	ROCK,
	KEY,
	GOAL,
	WALL,
};

enum class actionType
{
	RIGHT,
	LEFT,
	UP,
	DOWN,
	STOP,
	END,
};

int map[6][6];

typedef struct Object//�����I�u�W�F�N�g�̍\����
{
public:

	static const int MapSize = 6;

	int posx = 0;//����obj�͉��s����ɂ���̂�
	int posy = 0;

	int action = 0;//���̍s��������̂�
	int actionNum = 0;//�c��̃A�N�V������
	int actionCount = 0;//�����Ԗڂ̍s�������Ă���̂�

	static const int comandMaxNum = 7;//�A�N�V�����̍ő吔 //��ސ��̕ϐ����̂͂߂�ǂ�����

	int comandBox[comandMaxNum]{};//���̒��ɃR�}���h�̎��

	bool finish = false;//�s������I�u�W�F�N�g�S�̂̒��ōs�����I��点����

	int attribute = 0;//����obj�͉���obj���@�v���C���[���₩�S�[����
}Object;


Object ObjectInit(int posx_, int posy_, int attribute_)//�������֐�
{
	Object temp;

	temp.posx = posx_;
	temp.posy = posy_;

	temp.action = (int)actionType::END;

	for (int i = 0; i < Object::comandMaxNum; i++)
	{
		temp.comandBox[i] = temp.action;
	}

	temp.attribute = attribute_;

	temp.finish = false;

	return temp;
}

class ActionManager
{
public:
	ActionManager();
	~ActionManager();


	void ActionExecution(Object object);
	void ActionOnce(Object object);
	bool ActionEnd();


private:
	Object player_{};
};

ActionManager::ActionManager()
{
}

ActionManager::~ActionManager()
{
}

inline void ActionManager::ActionExecution(Object object)
{
	switch (object.attribute)
	{
	case (int)ObjectType::PLAYER:


		if (object.actionNum > 0) {//�c��̃A�N�V��������0�ł͂Ȃ��Ȃ�
			int tempObjectType = (int)ObjectType::NONE;

			if (object.comandBox[object.actionCount] == (int)actionType::UP)//�A�N�V�����^�C�v����̎�
			{
				int nextx;
				int nexty = object.posy - 1;

				if (nexty > 0 && map[object.posy - 1][object.posx] == (int)ObjectType::WALL)//��Ɉړ������Ƃ�map�O�ɏo�Ȃ��@���@�ǂł͂Ȃ��Ȃ�
				{
					if (map[object.posy - 1][object.posx] == (int)ObjectType::NONE)
					{
						map[object.posy][object.posx] = tempObjectType;
						map[object.posy - 1][object.posx] = (int)ObjectType::PLAYER;
						object.posy = -1;
					}
					else if (map[object.posy - 1][object.posx] == (int)ObjectType::ROCK)
					{

					}
					else if (map[object.posy - 1][object.posx] == (int)ObjectType::GOAL)
					{
						map[object.posy][object.posx] = tempObjectType;
						map[object.posy - 1][object.posx] = (int)ObjectType::PLAYER;
						tempObjectType = (int)ObjectType::GOAL;
						object.posy = -1;
					}
					object.actionCount++;
					object.actionNum--;
				}
			}
			else if (object.actionNum <= 0)
			{
				if (tempObjectType == (int)ObjectType::GOAL)
				{
					bool clear;
				}
				bool finish = true;
			}

		}


	default:
		break;
	}
}

inline void ActionManager::ActionOnce(Object object)
{
	if (true) {
		ActionExecution(object);
	}
}

inline bool ActionManager::ActionEnd()
{
	return false;
}
