#include "DxLib.h"
#include "MapMake.h"
#include "Mouse.h"
#include "Struct.h"
#include "KeyInput.h"
#include "LevelSelect.h"
#include "Move.h"
#include "CreateArrow.h"

//bool LevelSelect(Level a, int &n, Mouse* m, Point mousePos);

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
	int graphHandle[36];
	LoadDivGraph("Resource/mapchip.png", 36, 6, 6, 128, 128, graphHandle);

	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	int sceneNum = 0;
	int levelNum = 0;

	const char* c_mapName[] = { "mapSample.csv","END" };
	MapMake* map_ = new MapMake(6, 6, c_mapName);
	CreateArrow* createArrow_ = new CreateArrow;

	Level level1{ 170,300,300,300,static_cast<int>(LevelInfo::LEVEL1) };
	/*level1.x = 170;
	level1.y = 300;
	level1.width = 300;
	level1.height = 300;
	level1.level = static_cast<int>(LevelInfo::LEVEL1);*/

	Level level2{ 810,300,300,300,static_cast<int>(LevelInfo::LEVEL2) };
	//level2.x = 810;
	//level2.y = 300;
	//level2.width = 300;
	//level2.height = 300;
	//level2.level = static_cast<int>(LevelInfo::LEVEL2);

	Level level3{ 1450,300,300,300,static_cast<int>(LevelInfo::LEVEL3) };
	//level3.x = 1450;
	//level3.y = 300;
	//level3.width = 300;
	//level3.height = 300;
	//level3.level = static_cast<int>(LevelInfo::LEVEL3);

	Level level4{ 170,690,300,300,static_cast<int>(LevelInfo::LEVEL4) };
	//level4.x = 170;
	//level4.y = 690;
	//level4.width = 300;
	//level4.height = 300;
	//level4.level = static_cast<int>(LevelInfo::LEVEL4);

	Level level5{ 810,690,300,300,static_cast<int>(LevelInfo::LEVEL5) };
	//level5.x = 810;
	//level5.y = 690;
	//level5.width = 300;
	//level5.height = 300;
	//level5.level = static_cast<int>(LevelInfo::LEVEL5);

	Level level6{ 1450,690,300,300,static_cast<int>(LevelInfo::LEVEL6) };
	//level6.x = 1450;
	//level6.y = 690;
	//level6.width = 300;
	//level6.height = 300;
	//level6.level = static_cast<int>(LevelInfo::LEVEL6);

	int titleGraph = LoadGraph("title.png");
	int stageSelectGraph = LoadGraph("stageselect.png");
	int stage1Graph = LoadGraph("stage1.png");
	int stage2Graph = LoadGraph("stage2.png");
	int stage3Graph = LoadGraph("stage3.png");
	int stage4Graph = LoadGraph("stage4.png");
	int stage5Graph = LoadGraph("stage5.png");
	int stage6Graph = LoadGraph("stage6.png");

	// �ŐV�̃L�[�{�[�h���p

	Mouse* mouse_;
	mouse_ = new Mouse;
	Point mousePos = { 0,0 };

	KeyInput* keyInput_;
	keyInput_ = new KeyInput;

	//���[�u�֐��̐���
	Move* move_ = nullptr;

	//���[�u�֐��̏�����
	move_ = new Move();
	move_->Initialize();

	LevelSelect* levelSelect1_;
	levelSelect1_ = new LevelSelect(level1, mouse_);
	LevelSelect* levelSelect2_;
	levelSelect2_ = new LevelSelect(level2, mouse_);
	LevelSelect* levelSelect3_;
	levelSelect3_ = new LevelSelect(level3, mouse_);
	LevelSelect* levelSelect4_;
	levelSelect4_ = new LevelSelect(level4, mouse_);
	LevelSelect* levelSelect5_;
	levelSelect5_ = new LevelSelect(level5, mouse_);
	LevelSelect* levelSelect6_;
	levelSelect6_ = new LevelSelect(level6, mouse_);

	static bool isStart_ = false;
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
		if (sceneNum == static_cast<int>(Scene::TITLE))
		{
			DrawCircle(mousePos.x, mousePos.y, 5, 0xFF0000, true);
			DrawFormatString(0, 0, 0xFFFFFF, "�^�C�g��");
			if (mouse_->MouseInput(MOUSE_INPUT_LEFT))sceneNum = 1;

		}

		else if (sceneNum == static_cast<int>(Scene::MEMU))
		{
			DrawFormatString(0, 0, 0xFFFFFF, "���x���I��");

			if (levelSelect1_->Pic(levelNum, mousePos))sceneNum = 2;
			if (levelSelect2_->Pic(levelNum, mousePos))sceneNum = 2;
			if (levelSelect3_->Pic(levelNum, mousePos))sceneNum = 2;
			if (levelSelect4_->Pic(levelNum, mousePos))sceneNum = 2;
			if (levelSelect5_->Pic(levelNum, mousePos))sceneNum = 2;
			if (levelSelect6_->Pic(levelNum, mousePos))sceneNum = 2;
		}

		//�Q�[���V�[��
		else if (sceneNum == static_cast<int>(Scene::GAMESCENE))
		{
			//�X�e�[�W�̍s���̓ǂݍ��݂���x�����ǂݍ���
			if (!isStart_) {
				move_->LoadCommand("moveCommand.csv");
				isStart_ = true;
			}
			move_->Update((int)LevelInfo::LEVEL1);
			if (levelNum == static_cast<int>(LevelInfo::LEVEL1))
			{
				DrawFormatString(0, 0, 0xFFFFFF, "�Q�[���V�[��");
				if (keyInput_->IsKeyTrigger(KEY_INPUT_SPACE))sceneNum = 0;
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
			levelSelect1_->Draw(stage1Graph);
			levelSelect2_->Draw(stage2Graph);
			levelSelect3_->Draw(stage3Graph);
			levelSelect4_->Draw(stage4Graph);
			levelSelect5_->Draw(stage5Graph);
			levelSelect6_->Draw(stage6Graph);

		}
		else if (sceneNum == static_cast<int>(Scene::GAMESCENE))
		{
			map_->Draw(0, graphHandle);
			move_->Draw(levelNum);
			if (levelNum == 0)DrawFormatString(0, 0, 0xFFFFFF, "1");
			else if (levelNum == 1) DrawFormatString(0, 0, 0xFFFFFF, "2");
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
	// ����I��
	return 0;
}
/*
class IScene
{
public:
	virtual ~IScene() {}
	virtual void Update() = 0;	//�������z�֐�
	virtual void Draw() = 0;	//��΂Ɏ����Ȃ��Ƃ����Ȃ�
	virtual bool IsEnd() = 0;
	virtual IScene* GetNextScene() = 0;
};

#include "IScene.h"
class GameScene : public IScene
{
public:
	void Update() override;
	void Draw() override;
	bool IsEnd() override;
	IScene* GetNextScene() override;

};

*/

//bool LevelSelect(Level a, int &n,Mouse *m,Point mousePos)
//{
//	Box b;
//	Mouse* mouse_=m;
//	
//	b.Left = a.x;
//	b.Top = a.y;
//	b.Right = a.x + a.width;
//	b.Bottom = a.y + a.height;
//	if (b.Left <= mousePos.x && b.Right >= mousePos.x && b.Bottom >= mousePos.y && b.Top <= mousePos.y && mouse_->MouseInput(MOUSE_INPUT_LEFT))
//	{
//		n = a.level;
//		return true;
//	}
//	return false;
//}