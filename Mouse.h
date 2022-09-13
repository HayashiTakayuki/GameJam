#pragma once
#include"Struct.h"
class Mouse
{
protected:
	Point mousePoint;
	bool click;
	bool oldclick;
	int sound;
public:
	Mouse();
	Mouse(int sound);
	void MouseUpdate();
	Point GetMousePos();
	bool MouseInput(int b);
	bool MouseOutput(int b);
	bool MouseKeepput(int b);
	bool MouseCheckHitBox(Box box, Point mousePos);

};
