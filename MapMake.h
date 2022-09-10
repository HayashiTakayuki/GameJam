#pragma once
#include <ctype.h>
#include <fstream>
#include "LoadFile.h"
enum  MapChip {
	GROUND,
	GROUND2,
	PLAYER,
	ROCK
};
class MapMake
{
private:
	LoadFile* loadFile_ = nullptr;
public:
	void Initialize();
	MapMake();
	~MapMake();

	void Draw(int stage, int* graphMap, int* graphPlayer, int* graphTruck);

};

