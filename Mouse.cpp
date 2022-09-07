#include"DxLib.h"
#include"Mouse.h"
#include"Struct.h"

Mouse::Mouse()
{
	mousePoint = { 0,0 };
	click = 0;
	oldclick = 0;
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
	if ((oldclick & b) == 0 && (click & b) != 0)return 1;
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



