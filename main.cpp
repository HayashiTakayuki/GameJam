#include "DxLib.h"
#include "MapMake.h"
#include "Mouse.h"
#include "Struct.h"
#include "KeyInput.h"
#include "LevelSelect.h"
#include "Move.h"
#include "CreateArrow.h"

//bool LevelSelect(Level a, int &n, Mouse* m, Point mousePos);
//aaaaa


// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "GE1A_ハヤシタカユキ: タイトル";

// ウィンドウ横幅
const int WIN_WIDTH =1920;

// ウィンドウ縦幅
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
	END
};

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み
	int graphHandle[36];
	LoadDivGraph("Resource/mapchip.png", 36, 6, 6, 128, 128, graphHandle);

	// ゲームループで使う変数の宣言
	int sceneNum = 0;
	int levelNum = 0;


	const char *c_mapName[] = {"mapSample.csv","END"};
	MapMake* map_ = new MapMake(6,6, c_mapName);
	CreateArrow* createArrow_ = new CreateArrow;
	
	Level level1;
	level1.x = 100;
	level1.y = 100;
	level1.width = 100;
	level1.height = 100;
	level1.level = static_cast<int>(LevelInfo::LEVEL1);

	Level level2;
	level2.x = 200;
	level2.y = 200;
	level2.width = 100;
	level2.height = 100;
	level2.level = static_cast<int>(LevelInfo::LEVEL2);
	
	// 最新のキーボード情報用

	Mouse* mouse_;
	mouse_ = new Mouse;
	Point mousePos = { 0,0 };

	KeyInput* keyInput_;
	keyInput_ = new KeyInput;

	//ムーブ関数の生成
	Move* move_ = nullptr;
	
	//ムーブ関数の初期化
	move_ = new Move();
	move_->Initialize();

	LevelSelect* levelSelect1_;
	levelSelect1_ = new LevelSelect(level1, mouse_);
	LevelSelect* levelSelect2_;
	levelSelect2_ = new LevelSelect(level2, mouse_);

	static bool isStart_ = false;
	// ゲームループ
	while (true) {
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存

		// 最新のキーボード情報を取得
		keyInput_->Update();

		//マウス
		mouse_->MouseUpdate();
		mousePos = mouse_->GetMousePos();

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理
		//タイトル
		if (sceneNum == static_cast<int>(Scene::TITLE))
		{
			DrawCircle(mousePos.x, mousePos.y, 5, 0xFF0000, true);
			DrawFormatString(0, 0, 0xFFFFFF, "タイトル");
			if (mouse_->MouseInput(MOUSE_INPUT_LEFT))sceneNum = 1;

		}

		else if (sceneNum == static_cast<int>(Scene::MEMU))
		{
			DrawFormatString(0, 0, 0xFFFFFF, "レベル選択");

			if (levelSelect1_->Pic(levelNum,mousePos))sceneNum = 2;
			if (levelSelect2_->Pic(levelNum, mousePos))sceneNum = 2;
		}

		//ゲームシーン
		else if (sceneNum == static_cast<int>(Scene::GAMESCENE))
		{
			//ステージの行動の読み込みを一度だけ読み込む
			if (!isStart_) {
				move_->LoadCommand("moveCommand.csv");
				isStart_ = true;
			}
			move_->Update((int)LevelInfo::LEVEL1);
			if (levelNum == static_cast<int>(LevelInfo::LEVEL1))
			{
				DrawFormatString(0, 0, 0xFFFFFF, "ゲームシーン");
				if (keyInput_->IsKeyTrigger(KEY_INPUT_SPACE))sceneNum = 0;
			}
		}

		// 描画処理
		if (sceneNum == static_cast<int>(Scene::TITLE))
		{

		}
		else if (sceneNum == static_cast<int>(Scene::MEMU))
		{
			levelSelect1_->Draw();
			levelSelect2_->Draw();
			
		}
		else if (sceneNum == static_cast<int>(Scene::GAMESCENE))
		{
			map_->Draw(0, graphHandle);
			move_->Draw(levelNum);
			if (levelNum == 0)DrawFormatString(0, 0, 0xFFFFFF, "1");
			else if(levelNum == 1) DrawFormatString(0, 0, 0xFFFFFF, "2");
		}

		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1) {
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dxライブラリ終了処理
	DxLib_End();

	delete map_;
	delete createArrow_;
	// 正常終了
	return 0;
}
/*
class IScene
{
public:
	virtual ~IScene() {}
	virtual void Update() = 0;	//純粋仮想関数
	virtual void Draw() = 0;	//絶対に持たないといけない
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