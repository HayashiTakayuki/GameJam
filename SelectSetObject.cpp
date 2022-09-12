#include "SelectSetObject.h"
#include "DxLib.h"

SelectSetObject::SelectSetObject() {
	for (int i = 0; i < 5; i++)
	{
		orderBox_[i] = { 82 + (i * 198),orderSetPosY_,128,128 };
		selectBox_[i] = { 1168,323 + (i * 144),96,96 };
	}
	mouse_ = new Mouse();

	//initialize()�ɏ��������
	loadFile_ = LoadFile::GetInstance();
}

SelectSetObject::~SelectSetObject()
{
	delete mouse_;
}

void SelectSetObject::CheckMapChipDate(int stage)
{
	Point objectPoint = { 0,0 };

	int firstSetX = 160;
	int firstSetY = 128;
	// ��ڂ�\���������ʒu�ɕς���
	//5x5���� , 6x6����
	if (stage < 1) { firstSetX = 224; firstSetY = 192; }
	if (stage >= 1) { firstSetX = 160; firstSetY = 128; }

	mouse_->MouseUpdate();
	objectPoint.x = (mouse_->GetMousePos().x - firstSetX) / mapChipSize_;
	objectPoint.y = (mouse_->GetMousePos().y - firstSetY) / mapChipSize_;

	//�������ꂽ��
	if (mouse_->MouseInput(MOUSE_INPUT_LEFT))
	{
		//�}�E�X�̔z��̔ԍ����m�F
		//�n�ʂ���Ȃ�������
		if (loadFile_->mapDate[stage][objectPoint.y][objectPoint.x] != 0)
		{
			//0�̏ꍇ���̔z��ԍ���ۑ�
			whatObjSelectNow = loadFile_->mapDate[stage][objectPoint.y][objectPoint.x];
			haveMapChip = objectPoint;
			isOrder_ = false;
			isSelect_ = false;
		}
	}
}


void SelectSetObject::Draw(int stage, int* graphMap, int* graphPlayer, int* graphTruck)
{


	for (int i = 0; i < 5; i++)
	{
		//�����̕`��
		if (whatObj[i] != 0)
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
		if (selectWhatObj[i] != 0)
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
			//���ϐ��ɓ���ĕۑ����Ă����ԍ����i�[
			whatObj[i] = whatObjSelectNow; //who
			//�z��ԍ������ԖڂɎ��s���邩�A�}�b�v�̈ʒu�������Ă�
			array[i] = haveMapChip;
			isOrder_ = true;
		}

		if (mouse_->MouseCheckHitBox(selectBox_[i], mouse_->GetMousePos()) && !isSelect_)
		{
			//���ϐ��ɓ���ĕۑ����Ă����ԍ����i�[
			selectWhatObj[i] = whatObjSelectNow; //who

			selectNo_[i] = whatObjSelectNow;
			isSelect_ = true;
		}
	}

}

