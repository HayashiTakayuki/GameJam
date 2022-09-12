#pragma once
#include <ctype.h>
#include <fstream>
#include "LoadFile.h"
#include"Struct.h"


class MapMake
{
private:
	LoadFile* loadFile_ = nullptr;

	int mapChipSize = 128;
	

public:
	void Initialize();
	MapMake();
	~MapMake();

	void Draw(int stage, int* graphMap, int* graphPlayer, int* graphTruck);

};

