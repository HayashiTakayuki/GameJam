#include "CreateArrow.h"
#include "DxLib.h"
void CreateArrow::Draw(int* graphHandle)
{
	
	for (int y = 0; y < 5; y++) {
		int posY = firstPosY_ + ((spaceY_ + boxSize_) * y);
		for (int x = 0; x < 7; x++) {
			int posX = firstPosX_ + boxSize_ * x;

			if (arrowDirec_[y][x] >= 0 && arrowDirec_[y][x] < 4) {
				DrawGraph(posX, posY, graphHandle[arrowDirec_[y][x]], TRUE);
			}
			else {
				DrawGraph(posX, posY, graphHandle[4], TRUE);
			}

		}
	}
}