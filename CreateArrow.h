#pragma once
class CreateArrow {
private:
	int** arrowDirec_;
	const int firstPosX_ = 1120;
	const int firstPosY_ = 182;
	int spaceY_ = 96;
	int boxSize_ = 96;
public:
	void SetDirectArrow(int** arrow) { this->arrowDirec_ = arrow; }

	void Draw(int* graphHandle);

};

