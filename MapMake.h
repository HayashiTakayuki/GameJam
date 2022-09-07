#pragma once
#include <ctype.h>
#include <fstream>
class MapMake
{
private:
	int mapx;
	int mapy;
	static const int stageNum = 10;
	int mapDate[stageNum][8][8];
	const char** mapName;
public:
	MapMake(int mapx, int mapy, const char** Name);
	~MapMake();
	void LoadMap(int stage = 0) {
		while (1) {
			FILE* fp = NULL;
			fopen_s(&fp, mapName[stage], "r");
			if (fp == NULL) break;
			for (int y = 0; y < mapy; y++) {

				for (int x = 0; x < mapx; x++) {

					fscanf_s(fp, "%d,", &mapDate[stage][y][x]);
				}
			}

			fclose(fp);
			stage++;
		}
	}

	void Draw(int stage, int* graphMap);

};

