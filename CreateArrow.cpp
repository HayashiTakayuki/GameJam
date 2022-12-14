#include "CreateArrow.h"
#include "DxLib.h"

CreateArrow::CreateArrow()
	:arrowDirec_(nullptr),
	firstPosX_(1264),
	firstPosY_(327),
	spaceY_(48),
	boxSize_(96)
{
	loadFile_ = LoadFile::GetInstance();
};
void CreateArrow::Draw(int* graphHandle)
{
	if (!loadFile_->commandPosition)return;
	for (int y = 0; y < 5; y++) {
		int posY = firstPosY_ + ((spaceY_ + boxSize_) * y);
		for (int x = 0; x < 6; x++) {
			int posX = firstPosX_ + boxSize_ * x;

			if (loadFile_->commandPosition[y][x] > 0 && loadFile_->commandPosition[y][x] <= 4) {
				DrawGraph(posX, posY, graphHandle[loadFile_->commandPosition[y][x]], TRUE);
			}
			else {
				DrawGraph(posX, posY, graphHandle[0], TRUE);
			}

		}
	}
}