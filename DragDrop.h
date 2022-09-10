#pragma once
#include "DxLib.h"

class DragDrop
{
public:
	DragDrop();
	~DragDrop();

	void Update();
private:

	int komaX = 300, komaY = 300; // 持ち駒の座標
	int banX = 100, banY = 100;   // 駒を置く座標
	int sizeX = 50, sizeY = 50;   // 駒のサイズ
};

