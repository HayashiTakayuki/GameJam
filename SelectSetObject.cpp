#include "SelectSetObject.h"
#include "DxLib.h"

SelectSetObject::SelectSetObject() {

	for (int i = 0; i < 5; i++)
	{
		orderBox_[i] = { 82 + (i * 198),orderSetPosY_,128,128 };
		selectBox_[i] = { 1168,323 + (i * 144),96,96 };
	}
	//initialize()�ɏ��������
	loadFile_ = LoadFile::GetInstance();
	mouse_ = new Mouse();
}

void SelectSetObject::Initialize()
{
	for (int i = 0; i < 5; i++)
	{
		array[i] = { -1,-1 };

		whatObj[i] = 0;
		selectWhatObj[i] = 0;
	}
	spotGraphNum = 0;
	setumeiGraphNum = 0;
}

SelectSetObject::~SelectSetObject()
{
	delete mouse_;
}

void SelectSetObject::CheckMapChipDate(int stage)
{
	Point objectPoint = { 0,0 };

	int firstSetX = 0, firstSetY = 0;

	// ��ڂ�\���������ʒu�ɕς���
	//5x5���� , 6x6����
	if (stage == 0 || stage == 1 || stage == 4) { firstSetX = 224; firstSetY = 192; }
	if (stage == 2 || stage == 3 || stage == 5) { firstSetX = 160; firstSetY = 128; }

	mouse_->MouseUpdate();

	//�N���b�N�����s����擾

	//�������ꂽ��
	if (mouse_->MouseInput(MOUSE_INPUT_LEFT))
	{
		objectPoint.x = (mouse_->GetMousePos().x - firstSetX) / mapChipSize_;
		objectPoint.y = (mouse_->GetMousePos().y - firstSetY) / mapChipSize_;

		if (objectPoint.y >= 0 && objectPoint.y <= 5 && objectPoint.x >= 0 && objectPoint.x <= 5)
		{
			//�}�E�X���擾�����z��̔ԍ����m�F
			//�n�ʂ���Ȃ�������
			if (loadFile_->mapDate[stage][objectPoint.y][objectPoint.x] != MapChip::NONE)
			{
				if (loadFile_->mapDate[stage][objectPoint.y][objectPoint.x] == MapChip::ANA)
				{
					return;
				}
				if (loadFile_->mapDate[stage][objectPoint.y][objectPoint.x] == MapChip::ROCK)
				{
					if (enemy > 5)
					{
						return;
					}
					loadFile_->mapDate[stage][objectPoint.y][objectPoint.x] = MapChip::ROCK + enemy;
					enemy++;
				}

				//0�̏ꍇ���̔z��ԍ���ۑ�
				whatObjSelectNow = loadFile_->mapDate[stage][objectPoint.y][objectPoint.x];
				haveMapChip = objectPoint;
				isOrder_ = false;
				isSelect_ = false;
				if (stage == 0 && setumeiGraphNum == 0) { setumeiGraphNum++; spotGraphNum++; }
			}
		}
	}
}


void SelectSetObject::Draw(int stage, int* graphMap, int* graphPlayer, int* graphTruck, int* spotLightHandle, int* setumeiHandle)
{
	if (stage == 0)
	{
		DrawGraph(0, 0, spotLightHandle[spotGraphNum], TRUE);
		DrawGraph(0, 0, setumeiHandle[setumeiGraphNum], TRUE);
	}

	for (int i = 0; i < 5; i++)
	{
		//�����̕`��
		if (whatObj[i] != MapChip::NONE)
		{
			DrawGraph(orderBox_[i].Left, orderSetPosY_, graphMap[whatObj[i]], true);
	
		if (whatObj[i] == MapChip::CARDBORD)
			{
				DrawGraph(orderBox_[i].Left, orderSetPosY_, graphPlayer[0], true);
			}

			if (whatObj[i] == MapChip::TRUCK)
			{
				DrawGraph(orderBox_[i].Left, orderSetPosY_, graphTruck[0], true);
			}
		}
		//�E�I�𑤂̕`��
		if (selectWhatObj[i] != MapChip::NONE)
		{
			DrawGraph(selectBox_[i].Left, selectBox_[i].Top, graphMap[selectWhatObj[i]], true);
			if (selectWhatObj[i] == MapChip::CARDBORD)
			{
				DrawGraph(selectBox_[i].Left, selectBox_[i].Top, graphPlayer[0], true);
			}

			if (selectWhatObj[i] == MapChip::TRUCK)
			{
				DrawGraph(selectBox_[i].Left, selectBox_[i].Top, graphTruck[0], true);
			}
		}
	}

	if (!isOrder_ || !isSelect_) {
		Point mousePos = mouse_->GetMousePos();
		Point nearMouse = { 0,0 };
		if (isOrder_ && mousePos.y > 900 && mousePos.x > 82 && mousePos.x < 1005) {}
		else if (isSelect_ && mousePos.x >= 1088) {}
		else if (whatObjSelectNow == MapChip::TRUCK) {
			nearMouse = { -32,-12 };
			DrawGraph(mousePos.x + nearMouse.x, mousePos.y + nearMouse.y, graphTruck[0], true);
		}
		else if (whatObjSelectNow == MapChip::CARDBORD) {
			nearMouse = { -32,-32 };
			DrawGraph(mousePos.x + nearMouse.x, mousePos.y + nearMouse.y, graphPlayer[0], true);
		}
		else if (whatObjSelectNow != MapChip::NONE) {
			DrawGraph(mousePos.x, mousePos.y, graphMap[whatObjSelectNow], true);
		}
	}
}

void SelectSetObject::Update(int stage)
{
	//���N���b�N�����Ƃ���̃}�b�v�`�b�v�ԍ���ϐ��ɓ����֐�
	CheckMapChipDate(stage);
	//�Z���N�g�{�b�N�X���T������

	for (int i = 0; i < 5; i++)
	{
		//�Z���N�g�{�b�N�X��N�Ԗڂ����N���b�N�����Ƃ�
		if (mouse_->MouseCheckHitBox(orderBox_[i], mouse_->GetMousePos()) && !isOrder_)
		{
			if (stage == 0 && setumeiGraphNum == 1){ setumeiGraphNum++; spotGraphNum++; }
			
			//���ϐ��ɓ���ĕۑ����Ă����ԍ����i�[
			whatObj[i] = whatObjSelectNow; //who
			//�z��ԍ������ԖڂɎ��s���邩�A�}�b�v�̈ʒu�������Ă�
			array[i] = haveMapChip;
			isOrder_ = true;
		}

		if (mouse_->MouseCheckHitBox(selectBox_[i], mouse_->GetMousePos()) && !isSelect_)
		{
			if (stage == 0 && setumeiGraphNum == 2) { setumeiGraphNum++; spotGraphNum++; }
			//���ϐ��ɓ���ĕۑ����Ă����ԍ����i�[
			selectWhatObj[i] = whatObjSelectNow; //who

			selectNo_[i] = whatObjSelectNow;
			isSelect_ = true;
		}

		//�R�}���h���I�[�_�[�ɓ��ꂽ��
		if (isOrder_ || isSelect_) {
			//���ƐV���݂āA����������������V�����̂��c��
			for (int j = 0; j < 5; j++) {
				if (i == j)continue;
				if (isOrder_ && whatObj[i] == whatObj[j]) {
					array[j] = { -1,-1 };
					whatObj[j] = MapChip::NONE;
				}
				if (isSelect_ && selectWhatObj[i] == selectWhatObj[j]) { 
					selectNo_[j] = -1;
					selectWhatObj[j] = MapChip::NONE; 
				}
			}
		}
	}
}