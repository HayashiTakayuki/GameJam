#pragma once
#include"Struct.h"
class Mouse
{
protected:
	Point mousePoint;
	int click;
	int oldclick;
	int sound;
public:
	Mouse(int sound);
	void MouseUpdate();
	Point GetMousePos();
	bool MouseInput(int b);
	bool MouseOutput(int b);
	bool MouseKeepput(int b);
};
