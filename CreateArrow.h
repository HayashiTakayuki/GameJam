#pragma once
#include "LoadFile.h"
class CreateArrow
{
private:
	int **arrowDirec_;
	const int firstPosX_ = 1264;
	const int firstPosY_ = 327;
	int spaceY_ = 48;//box“¯Žm‚ÌŠÔŠu
	int boxSize_ = 96;
	LoadFile* loadFile_ = nullptr;
public:
	CreateArrow();
	void Draw(int* graphHandle);
};
