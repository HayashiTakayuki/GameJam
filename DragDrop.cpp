#include "DragDrop.h"

DragDrop::DragDrop()
{
}

DragDrop::~DragDrop()
{
}

void DragDrop::Update()
{
	if (GetMouseInput() & MOUSE_INPUT_LEFT) {
		int posX, posY;

		// マウスの座標を取得(何を選択したかを判定する要素)
		GetMousePoint(&posX, &posY);
		if ((posX >= komaX) && (posX < (komaX + sizeX))) {  // 駒の上か判定(X座標)
			if ((posY >= komaY) && (posY < (komaY + sizeY))) {  // 同様(Y座標)    

				while (GetMouseInput() & MOUSE_INPUT_LEFT) {

					//アニメーションなどをつけたければここに処理を書く
					GetMousePoint(&posX, &posY);

					DrawBox(banX, banY, banX + sizeX, banY + sizeY, GetColor(0xff, 0x00, 0x00), false);

					DrawBox(posX, posY, sizeX + posX, sizeY + posY, GetColor(0xff, 0xff, 0xff), true);
				}

				// マウスの座標を取得(どこに置いたかを判定する要素)
				GetMousePoint(&posX, &posY);
				if ((posX >= banX) && (posX < (banX + sizeX))) {
					if ((posY >= banY) && (posY < (banY + sizeY))) {

						komaX = banX;
						komaY = banY;
						DrawString(0, 0, "Conguratulation!", GetColor(255, 0, 0));
					}
				}
			}
		}
	}


	DrawBox(komaX, komaY, komaX + sizeX, komaY + sizeY, GetColor(0xff, 0xff, 0xff), true);
	DrawBox(banX, banY, banX + sizeX, banY + sizeY, GetColor(0xff, 0x00, 0x00), false);
}
