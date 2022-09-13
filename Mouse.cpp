#include"DxLib.h"
#include"Mouse.h"
#include"Struct.h"

Mouse::Mouse() {}

Mouse::~Mouse() {}

void Mouse::MouseUpdate()
{
	GetMousePoint(&mousePoint.x, &mousePoint.y);
	oldclick = click;
	click = GetMouseInput();
}

Point Mouse::GetMousePos()
{
	return mousePoint;
}

//mouse�������ꂽ��
bool Mouse::MouseInput(int b)
{
	int a = (oldclick & b);
	int b_ = GetMouseInput() & b;
	if ((oldclick & b) == 0 && (GetMouseInput() & b) != 0)
	{
		PlaySoundMem(sound_, DX_PLAYTYPE_BACK, TRUE);
		return true;

	}
	return false;
}

//mouse�������ꂽ��
bool Mouse::MouseOutput(int b)
{
	if ((oldclick & b) != 0 && (click & b) == 0)return true;
	return false;
}

//mouse�������ꑱ������
bool Mouse::MouseKeepput(int b)
{
	if ((oldclick & b) != 0 && (click & b) != 0)return true;
	return false;
}

bool Mouse::MouseCheckHitBox(Box box, Point mousePos)
{
	box.Right = box.Left + box.Right;
	box.Bottom = box.Top + box.Bottom;
	if (box.Left <= mousePos.x && box.Right >= mousePos.x && box.Bottom >= mousePos.y && box.Top <= mousePos.y && MouseInput(MOUSE_INPUT_LEFT))
	{
		return true;
	}
	return false;
}




void Mouse::DrawMarker(int* graphMarker)
{
	markerOldClick = markerClick;
	markerClick = GetMouseInput() & MOUSE_INPUT_RIGHT;
	if (!markerOldClick && markerClick) {
		//�}�E�X�����ꂽ��}�[�J�[�̍Ō�̃t���O�������Ă���t���O�͕ς��Ȃ�
		if (isDrawMarker_[3] == false) isDrawMarker_[changeMarker_] = true;
		//0~3�𑫂��ĉ񂵂ĕ`��ʒu��ς���
		changeMarker_ = changeMarker_ % markerNum_;
		drawPos_[changeMarker_] = mousePoint;
		changeMarker_++;
	}

	int graphSize = 64;
	for (int i = 0; i < markerNum_; i++) {
		if (isDrawMarker_[i]) {
			//�摜������̈ʒu�ɔ����ړ�
			int x = drawPos_[i].x - graphSize / 2;
			int y = drawPos_[i].y - graphSize / 2;
			DrawGraph(x, y, graphMarker[i], true);
		}
	}
}

void Mouse::Initialize()
{

}


Mouse* Mouse::GetInstance()
{
	static Mouse instance;
	return &instance;
}



void Mouse::Reset()
{
	click = false;
	oldclick = false;

	for (int i = 0; i < markerNum_; i++) {
		drawPos_[i] = { 0,0 };
		isDrawMarker_[i] = false;
		changeMarker_ = 0;
	}
}