#include"DxLib.h"
#include"Mouse.h"
#include"Struct.h"

Mouse::Mouse()
:sound(0)
{
	mousePoint = { 0,0 };
	click = 0;
	oldclick = 0;
}

Mouse::Mouse(int sound)
{
	mousePoint = { 0,0 };
	click = 0;
	oldclick = 0;
	this->sound = sound;
}

void Mouse::MouseUpdate()
{
	GetMousePoint(&mousePoint.x, &mousePoint.y);
	oldclick = click;
	click = GetMouseInput();
}

Point Mouse::GetMousePos()
{
	return mousePoint;
}

bool Mouse::MouseInput(int b)
{
	if ((oldclick & b) == 0 && (click & b) != 0)
	{
		PlaySoundMem(sound, DX_PLAYTYPE_BACK, TRUE);
		return 1;
	}
	return 0;
}

bool Mouse::MouseOutput(int b)
{
	if ((oldclick & b) != 0 && (click & b) == 0)return 1;
	return 0;
}

bool Mouse::MouseKeepput(int b)
{
	if ((oldclick & b) != 0 && (click & b) != 0)return 1;
	return 0;
}



