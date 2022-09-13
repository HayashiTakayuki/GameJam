#include"DxLib.h"
#include"Mouse.h"
#include"Struct.h"

Mouse::Mouse()
	:sound(0),
	click(false),
	oldclick(false),
	mousePoint({ 0,0 })
{
}

Mouse::Mouse(int sound)
	: click(false),
	oldclick(false),
	mousePoint({ 0,0 })
{
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

//mouse‚ª‰Ÿ‚³‚ê‚½‚ç
bool Mouse::MouseInput(int b)
{
	if ((oldclick & b) == 0 && (click & b) != 0)
	{
		PlaySoundMem(sound, DX_PLAYTYPE_BACK, TRUE);
		return 1;
	}
	return 0;
}

//mouse‚ª—£‚³‚ê‚½‚ç
bool Mouse::MouseOutput(int b)
{
	if ((oldclick & b) != 0 && (click & b) == 0)return 1;
	return 0;
}

//mouse‚ª‰Ÿ‚³‚ê‘±‚¯‚½‚ç
bool Mouse::MouseKeepput(int b)
{
	if ((oldclick & b) != 0 && (click & b) != 0)return 1;
	return 0;
}

bool Mouse::MouseCheckHitBox(Box box, Point mousePos)
{
	box.Right = box.Left + box.Right;
	box.Bottom = box.Top + box.Bottom;
	if (box.Left <= mousePos.x && box.Right >= mousePos.x && box.Bottom >= mousePos.y && box.Top <= mousePos.y && MouseInput(MOUSE_INPUT_LEFT))
	{
		return true;
	}
	return false;
}



