#include "DxLib.h"
#include "MapMake.h"
#include "Mouse.h"
#include "Struct.h"
#include "KeyInput.h"
// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "GE1A_�n���V�^�J���L: �^�C�g��";

// �E�B���h�E����
const int WIN_WIDTH =1920;

// �E�B���h�E�c��
const int WIN_HEIGHT = 1080;

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


	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	int sceneNum = 0;

	Mouse* mouse;
	mouse = new Mouse;
	Point mousePos = { 0,0 };

	KeyInput* key;
	key = new KeyInput;

	// �Q�[�����[�v
	while (true) {
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�

		// �ŐV�̃L�[�{�[�h�����擾
		key->Update();

		//�}�E�X
		mouse->MouseUpdate();
		mousePos = mouse->GetMousePos();

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����
		//�^�C�g��
		if (sceneNum == 0)
		{
			DrawCircle(mousePos.x, mousePos.y, 5, 0xFF0000, true);
			DrawFormatString(0, 0, 0xFFFFFF, "�^�C�g��");
			if (mouse->MouseInput(MOUSE_INPUT_LEFT) )sceneNum = 1;
		}

		//���x���I��
		else if (sceneNum == 1)
		{
			DrawFormatString(0, 0, 0xFFFFFF, "���x���I��");
			if (key->IsKeyTrigger(KEY_INPUT_SPACE))sceneNum = 2;
		}

		//�Q�[���V�[��
		else if (sceneNum == 2)
		{
			DrawFormatString(0, 0, 0xFFFFFF, "�Q�[���V�[��");
			if (key->IsKeyTrigger(KEY_INPUT_SPACE))sceneNum = 0;
		}

		// �`�揈��

		if (sceneNum == 0)
		{

		}

		else if (sceneNum == 1)
		{

		}

		else if (sceneNum == 2)
		{

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