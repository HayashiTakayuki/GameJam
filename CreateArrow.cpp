#include "CreateArrow.h"
#include "DxLib.h"

CreateArrow::CreateArrow()
	:firstPosX_(1120),
	firstPosY_(182),
	spaceY_(96),
	boxSize_(96)
{
	loadFile_ = LoadFile::GetInstance();
};
void CreateArrow::Draw(int* graphHandle)
{
	if (!loadFile_->commandPosition)return;
	for (int y = 0; y < 5; y++) {
		int posY = firstPosY_ + ((spaceY_ + boxSize_) * y);
		for (int x = 0; x < 7; x++) {
			int posX = firstPosX_ + boxSize_ * x;

			if (loadFile_->commandPosition[y][x] >= 0 && loadFile_->commandPosition[y][x] < 4) {
				DrawGraph(posX, posY, graphHandle[loadFile_->commandPosition[y][x]], TRUE);
			}
			else {
				DrawGraph(posX, posY, graphHandle[4], TRUE);
			}

		}
	}
}