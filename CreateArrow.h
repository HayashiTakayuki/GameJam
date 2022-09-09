#pragma once
class CreateArrow {
private:
	static const int commandSetNum = 5;
	static const int commandNum = 8;
	int arrowDirec_[commandSetNum][commandNum];
	const int firstPosX_ = 1120;
	const int firstPosY_ = 182;
	int spaceY_ = 96;
	int boxSize_ = 96;
public:
	void SetDirectArrow(int arrow[][10]) {
		for (int y = 0; y < commandSetNum; y++) {
			for (int x = 0; x < commandNum; x++) {
				arrowDirec_[y][x] = arrow[y][x];
			}
		}
	}

	void Draw(int* graphHandle);

};

