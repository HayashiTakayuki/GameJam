#pragma once
#include "DxLib.h"
#include "Mouse.h"

class LevelSelect
{
public:
	LevelSelect(Level Lv,Mouse *m);
	~LevelSelect();
	bool Pic(int &levelNum,Point mousePos);
	void Draw();


private:
	Level level;
	Mouse* mouse_;
};