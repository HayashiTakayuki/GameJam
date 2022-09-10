#pragma once
#include"Struct.h"

/// <summary>
/// マウス操作クラス
/// </summary>
class Mouse
{
protected:
	Point mousePoint;
	int click;
	int oldclick;
	int sound;
public:
	Mouse();
	Mouse(int sound);
	void MouseUpdate();
	Point GetMousePos();
	bool MouseInput(int b);
	bool MouseOutput(int b);
	bool MouseKeepput(int b);
};
