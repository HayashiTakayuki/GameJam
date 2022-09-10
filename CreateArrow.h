#pragma once
#include "LoadFile.h"
class CreateArrow
{
private:
	const int firstPosX_ = 1120;
	const int firstPosY_ = 182;
	int spaceY_ = 96;
	int boxSize_ = 96;
	LoadFile* loadFile_ = nullptr;
public:
	CreateArrow();
	void Draw(int* graphHandle);
};

