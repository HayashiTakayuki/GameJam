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

		// �}�E�X�̍��W���擾(����I���������𔻒肷��v�f)
		GetMousePoint(&posX, &posY);
		if ((posX >= komaX) && (posX < (komaX + sizeX))) {  // ��̏ォ����(X���W)
			if ((posY >= komaY) && (posY < (komaY + sizeY))) {  // ���l(Y���W)    

				while (GetMouseInput() & MOUSE_INPUT_LEFT) {

					//�A�j���[�V�����Ȃǂ���������΂����ɏ���������
					GetMousePoint(&posX, &posY);

					DrawBox(banX, banY, banX + sizeX, banY + sizeY, GetColor(0xff, 0x00, 0x00), false);

					DrawBox(posX, posY, sizeX + posX, sizeY + posY, GetColor(0xff, 0xff, 0xff), true);
				}

				// �}�E�X�̍��W���擾(�ǂ��ɒu�������𔻒肷��v�f)
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
