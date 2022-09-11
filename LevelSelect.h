#pragma once
#include "DxLib.h"
#include "Mouse.h"

class LevelSelect
{
public:
	LevelSelect(Level Lv);
	~LevelSelect();
	bool Pic(int &levelNum,Point mousePos);
	void Draw(int graph);


private:
	Level level;
};