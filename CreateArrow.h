#pragma once

/// <summary>
/// 矢印描画クラス
/// </summary>
class CreateArrow {
private:
	int** arrowDirec_;
	const int firstPosX_ = 1120;//描画開始ｘ座標
	const int firstPosY_ = 182;//描画開始ｙ座標
	int spaceY_ = 96;//描画間隔
	int boxSize_ = 96;//サイズ
public:
	void SetDirectArrow(int** arrow) { this->arrowDirec_ = arrow; }

	/// <summary>
	/// 描画関数
	/// </summary>
	/// <param name="graphHandle"></param>
	void Draw(int* graphHandle);

};

