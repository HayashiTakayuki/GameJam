#pragma once
#include "DxLib.h"

class DragDrop
{
public:
	DragDrop();
	~DragDrop();

	void Update();
private:

	int komaX = 300, komaY = 300; // ������̍��W
	int banX = 100, banY = 100;   // ���u�����W
	int sizeX = 50, sizeY = 50;   // ��̃T�C�Y
};

