#pragma once
#pragma once
#include <vector>

enum class ObjectType//オブジェクトの種類
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

typedef struct Object//動くオブジェクトの構造体
{
public:

	static const int MapSize = 6;

	int posx = 0;//このobjは何行何列にいるのか
	int posy = 0;

	int action = 0;//何の行動をするのか
	int actionNum = 0;//残りのアクション数
	int actionCount = 0;//今何番目の行動をしているのか

	static const int comandMaxNum = 7;//アクションの最大数 //種類数の変数作るのはめんどかった

	int comandBox[comandMaxNum]{};//この中にコマンドの種類

	bool finish = false;//行動するオブジェクト全体の中で行動を終わらせたか

	int attribute = 0;//このobjは何のobjか　プレイヤーか岩かゴールか
}Object;


Object ObjectInit(int posx_, int posy_, int attribute_)//初期化関数
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


		if (object.actionNum > 0) {//残りのアクション数が0ではないなら
			int tempObjectType = (int)ObjectType::NONE;

			if (object.comandBox[object.actionCount] == (int)actionType::UP)//アクションタイプが上の時
			{
				int nextx;
				int nexty = object.posy - 1;

				if (nexty > 0 && map[object.posy - 1][object.posx] == (int)ObjectType::WALL)//上に移動したときmap外に出ない　かつ　壁ではないなら
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
