#include "LevelSelect.h"

LevelSelect::LevelSelect(Level Lv, Mouse* m)
{
	level = Lv;
	mouse_ = m;
}

LevelSelect::~LevelSelect()
{
}

bool LevelSelect::Pic(int& levelNum,Point mousePos)
{
	Box b;
	b.Left = level.x;
	b.Top = level.y;
	b.Right = level.x + level.width;
	b.Bottom = level.y + level.height;
	if (b.Left <= mousePos.x && b.Right >= mousePos.x && b.Bottom >= mousePos.y && b.Top <= mousePos.y && mouse_->MouseInput(MOUSE_INPUT_LEFT))
	{
		levelNum = level.level;
		return true;
	}
	return false;
}

void LevelSelect::Draw(int graph)
{
	Box b;
	b.Left = level.x;
	b.Top = level.y;
	b.Right = level.x + level.width;
	b.Bottom = level.y + level.height;
	DrawGraph(b.Left, b.Top, graph, true);
}
