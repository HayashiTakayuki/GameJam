#include "DxLib.h"
#include "MapMake.h"
#include "Mouse.h"
#include "Struct.h"
#include "KeyInput.h"
#include "LevelSelect.h"
#include "Move.h"
#include "CreateArrow.h"
#include "LoadFile.h"

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "GE1A_�n���V�^�J���L: �^�C�g��";

// �E�B���h�E����
const int WIN_WIDTH = 1920;

// �E�B���h�E�c��
const int WIN_HEIGHT = 1080;

enum class Scene {
	TITLE,
	MEMU,
	GAMESCENE,
	END
};

enum class LevelInfo {
	LEVEL1,
	LEVEL2,
	LEVEL3,
	LEVEL4,
	LEVEL5,
	LEVEL6,
	END
};

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���
	//�}�b�v�`�b�v�̕`��
	int graphHandle[36];
	LoadDivGraph("Resource/mapchip.png", 36, 6, 6, 128, 128, graphHandle);

	int rightChip[36];
	LoadDivGraph("Resource/rightChip.png", 36, 6, 6, 96, 96, rightChip);

	int cardboardHandle[2];
	LoadDivGraph("Resource/cardboard.png", 1, 1, 1, 128, 128, cardboardHandle);

	int truckHandle[2];
	LoadDivGraph("Resource/truck.png", 1, 1, 1, 128, 128, truckHandle);
	
	int arrowHandle[5];
	LoadDivGraph("Resource/arrow.png", 5, 5, 1, 96, 96, arrowHandle);
	int setumeiHandle[4];
	LoadDivGraph("Resource/setumei.png", 4, 4, 1, 1920, 1080, setumeiHandle);
	int spotLightHandle[3];
	LoadDivGraph("Resource/spotLight.png", 3, 3, 1, 1920, 1080, spotLightHandle);


	int toracGraph = LoadGraph("Resource/torac.png");
	int haikei5X5 = LoadGraph("Resource/5X5.png");
	int haikei6X6 = LoadGraph("Resource/6X6.png");

	int picSE = LoadSoundMem("pic.wav");
	int bgm = LoadSoundMem("bgm.mp3");

	int titleGraph = LoadGraph("Resource/title.png");
	int stageSelectGraph = LoadGraph("Resource/stageselect.png");
	int levelGraph_[] = {
		LoadGraph("Resource/stage1.png"),
		LoadGraph("Resource/stage2.png")	,
		LoadGraph("Resource/stage3.png")	,
		LoadGraph("Resource/stage4.png")	,
		LoadGraph("Resource/stage5.png")	,
		LoadGraph("Resource/stage6.png")
	};
	int clearGraph = LoadGraph("Resource / clear.png");
	int failedGraph = LoadGraph("Resource / failed.png");

	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	//�X�e�[�W��
	const int stageNum_ = 6;

	//�}�b�v��t�@�C���ǂݍ���
	LoadFile* loadFile_ = LoadFile::GetInstance();
	const char* c_mapName[] = { "level1.csv","level2.csv","END" };
	
	const char* c_comamndName[] = { "moveCommand.csv","moveCommand2.csv","END" };

	loadFile_->LoadMap(6, 6, c_mapName);

	int sceneNum = 0;
	int levelNum = 0;

	//�}�b�v�`��p�̕ϐ�
	MapMake* map_ = new MapMake();
	map_->Initialize();
	//���Ǘ�
	CreateArrow* createArrow_ = new CreateArrow;

	Level level1 = { 170,300,300,300 };
	level1.level = static_cast<int>(LevelInfo::LEVEL1);

	Level level2 = { 810,300,300,300 };
	level2.level = static_cast<int>(LevelInfo::LEVEL2);

	Level level3 = { 1450,300,300,300 };
	level3.level = static_cast<int>(LevelInfo::LEVEL3);

	Level level4 = { 170,690,300,300 };
	level4.level = static_cast<int>(LevelInfo::LEVEL4);

	Level level5 = { 810,690,300,300 };
	level5.level = static_cast<int>(LevelInfo::LEVEL5);

	Level level6 = { 1450,690,300,300 };
	level6.level = static_cast<int>(LevelInfo::LEVEL6);
	//���j���[��level�̕\���Ȃǔz��Ǘ�
	LevelSelect* levelSelect_;
	levelSelect_ = new LevelSelect[stageNum_]{
		{level1},
		{level2},
		{level3},
		{level4},
		{level5},
		{level6}
	};

	//���[�u�֐��̐���
	Move* move_ = nullptr;
	//���[�u�֐��̏�����
	move_ = new Move();
	
	//�n�܂�������ture�ɂ��X�e�[�W���o��Ƃ���false�A��x�������s���邽��
	static bool isStart_ = false;


	// �ŐV�̃L�[�{�[�h���p
	
	Mouse* mouse_;
	mouse_ = new Mouse(picSE);
	Point mousePos = { 0,0 };

	KeyInput* keyInput_;
	keyInput_ = new KeyInput;

	

	// �Q�[�����[�v
	while (true) {
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�

		// �ŐV�̃L�[�{�[�h�����擾
		keyInput_->Update();

		//�}�E�X
		mouse_->MouseUpdate();
		mousePos = mouse_->GetMousePos();

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����
		//�^�C�g��
		if (CheckSoundMem(bgm) == FALSE)
		{
			SetVolumeSoundMem(8500, bgm);
			PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, TRUE);
		}
		if (sceneNum == static_cast<int>(Scene::TITLE))
		{
			DrawCircle(mousePos.x, mousePos.y, 5, 0xFF0000, true);
			DrawFormatString(0, 0, 0xFFFFFF, "�^�C�g��");
			if (mouse_->MouseInput(MOUSE_INPUT_LEFT))sceneNum = 1;

		}

		else if (sceneNum == static_cast<int>(Scene::MEMU))
		{
			DrawFormatString(0, 0, 0xFFFFFF, "���x���I��");

			if (mouse_->MouseInput(mouse_->MouseInput(MOUSE_INPUT_LEFT))) {
				//���j���[��ʂɂđI�������甲����
				for (int i = 0; i < stageNum_; i++) {
					if (levelSelect_[i].Pic(levelNum, mousePos)) {
						sceneNum = 2;
						break;
					}
				}
			}

		}

		//�Q�[���V�[��
		else if (sceneNum == static_cast<int>(Scene::GAMESCENE))
		{
			//�X�e�[�W�̍s���̓ǂݍ��݂���x�����ǂݍ���
			if (!isStart_) 
			{
				loadFile_->LoadCommand(c_comamndName[levelNum]);
				move_->Initialize();
				isStart_ = true;
			}

			if (move_->GetIsCrear())
			{
				DrawFormatString(0, 400, 0xFFF, "gameClear");
				if (mouse_->MouseInput(MOUSE_INPUT_LEFT))
				{
					levelNum++;
					isStart_ = false;
				}
			}
			
			move_->Update(levelNum);
			
			if (levelNum == static_cast<int>(LevelInfo::LEVEL1))
			{

			}
		}

		// �`�揈��
		if (sceneNum == static_cast<int>(Scene::TITLE))
		{
			DrawGraph(0, 0, titleGraph, true);
		}
		else if (sceneNum == static_cast<int>(Scene::MEMU))
		{
			DrawGraph(0, 0, stageSelectGraph, true);
			
			//���j���[�̃X�e�[�W�̕`��
			for (int i = 0; i < stageNum_; i++)
			{
				levelSelect_[i].Draw(levelGraph_[i]);
			}
		}
		else if (sceneNum == static_cast<int>(Scene::GAMESCENE))
		{
			if (levelNum == static_cast<int>(LevelInfo::LEVEL1) || levelNum == static_cast<int>(LevelInfo::LEVEL2) || levelNum == static_cast<int>(LevelInfo::LEVEL5))
			{
				DrawGraph(0, 0, haikei5X5, TRUE);
			}
			if (levelNum == static_cast<int>(LevelInfo::LEVEL3)|| levelNum == static_cast<int>(LevelInfo::LEVEL4) || levelNum == static_cast<int>(LevelInfo::LEVEL6))
			{
				DrawGraph(0, 0, haikei6X6, TRUE);
			}

			map_->Draw(levelNum, graphHandle, cardboardHandle, truckHandle);
			createArrow_->Draw(arrowHandle);
			move_->Draw(levelNum, graphHandle, cardboardHandle, truckHandle, spotLightHandle, setumeiHandle,rightChip);

			//DrawGraph(0, 0, spotLightHandle[0], TRUE);
			//DrawGraph(0, 0, setumeiHandle[0], TRUE);

			if (levelNum == 0)DrawFormatString(0, 0, 0xFFFFFF, "levelNum1");
			else if (levelNum == 1) DrawFormatString(0, 0, 0xFFFFFF, "levelNum2");
		}

		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1) {
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dx���C�u�����I������
	DxLib_End();

	delete map_;
	delete createArrow_;
	delete mouse_;
	delete keyInput_;
	delete[] levelSelect_;

	// ����I��
	return 0;
}