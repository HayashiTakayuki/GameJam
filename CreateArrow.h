#pragma once
class CreateArrow {
private:
	int** arrowDirec_;
	const int firstPosX_ = 1168;
	const int firstPosY_ = 323;
	int spaceY_ = 44;
	int boxSize_ = 96;
public:
	void SetDirectArrow(int** arrow) { this->arrowDirec_ = arrow; }

	void Draw(int* graphHandle);

};

