#pragma once

/// <summary>
/// ���`��N���X
/// </summary>
class CreateArrow {
private:
	int** arrowDirec_;
	const int firstPosX_ = 1120;//�`��J�n�����W
	const int firstPosY_ = 182;//�`��J�n�����W
	int spaceY_ = 96;//�`��Ԋu
	int boxSize_ = 96;//�T�C�Y
public:
	void SetDirectArrow(int** arrow) { this->arrowDirec_ = arrow; }

	/// <summary>
	/// �`��֐�
	/// </summary>
	/// <param name="graphHandle"></param>
	void Draw(int* graphHandle);

};

