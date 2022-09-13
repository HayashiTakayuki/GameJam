#include "DxLib.h"
#include "MapMake.h"
#include "Mouse.h"
#include "Struct.h"
#include "KeyInput.h"
#include "LevelSelect.h"
#include "Move.h"
#include "CreateArrow.h"
#include "LoadFile.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "GE1A_ハヤシタカユキ: タイトル";

// ウィンドウ横幅
const int WIN_WIDTH = 1920;

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
	LEVEL3,
	LEVEL4,
	LEVEL5,
	LEVEL6,
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
	//マップチップの描画
	int graphHandle[36];
	LoadDivGraph("Resource/mapchip.png", 36, 6, 6, 128, 128, graphHandle);

	int cardboardHandle[2];
	LoadDivGraph("Resource/cardboard.png", 1, 1, 1, 128, 128, cardboardHandle);

	int truckHandle[2];
	LoadDivGraph("Resource/truck.png", 1, 1, 1, 128, 128, truckHandle);
	
	int arrowHandle[5];
	LoadDivGraph("Resource/arrow.png", 5, 5, 1, 96, 96, arrowHandle);

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

	int clickWaitTimer = 60;
	// ゲームループで使う変数の宣言
	//ステージ数
	const int stageNum_ = 6;

	//マップやファイル読み込み
	LoadFile* loadFile_ = LoadFile::GetInstance();
	const char* c_mapName[] = { "mapSample.csv","END" };
	loadFile_->LoadMap(6, 6, c_mapName);


	int sceneNum = 0;
	int levelNum = 0;

	//マップ描画用の変数
	MapMake* map_ = new MapMake();
	map_->Initialize();
	//矢印管理
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
	//メニューのlevelの表示など配列管理
	LevelSelect* levelSelect_;
	levelSelect_ = new LevelSelect[stageNum_]{
		{level1},
		{level2},
		{level3},
		{level4},
		{level5},
		{level6}
	};

	//ムーブ関数の生成
	Move* move_ = nullptr;
	//ムーブ関数の初期化
	move_ = new Move();
	move_->Initialize();
	
	//始まった時にtureにしステージを出るときにfalse、一度だけ実行するため
	static bool isStart_ = false;


	// 最新のキーボード情報用
	
	Mouse* mouse_;
	mouse_ = new Mouse(picSE);
	Point mousePos = { 0,0 };

	KeyInput* keyInput_;
	keyInput_ = new KeyInput;

	int waitclick = 60;

	

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
		if (CheckSoundMem(bgm) == FALSE)
		{
			SetVolumeSoundMem(8500, bgm);
			PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, TRUE);
		}
		if (sceneNum == static_cast<int>(Scene::TITLE))
		{
			DrawCircle(mousePos.x, mousePos.y, 5, 0xFF0000, true);
			DrawFormatString(0, 0, 0xFFFFFF, "タイトル");
			if (mouse_->MouseInput(MOUSE_INPUT_LEFT))sceneNum = 1;

		}

		else if (sceneNum == static_cast<int>(Scene::MEMU))
		{
			DrawFormatString(0, 0, 0xFFFFFF, "レベル選択");

			if (mouse_->MouseInput(mouse_->MouseInput(MOUSE_INPUT_LEFT))) {
				//メニュー画面にて選択したら抜ける
				for (int i = 0; i < stageNum_; i++) {
					if (levelSelect_[i].Pic(levelNum, mousePos)) {
						sceneNum = 2;
						break;
					}
				}
			}

		}

		//ゲームシーン
		else if (sceneNum == static_cast<int>(Scene::GAMESCENE))
		{
			waitclick--;
			//ステージの行動の読み込みを一度だけ読み込む
			if (!isStart_) {
				loadFile_->LoadCommand("moveCommand.csv");

				isStart_ = true;
			}
			if (waitclick <= 0)
			{
				move_->Update((int)LevelInfo::LEVEL1);
			}
			if (levelNum == static_cast<int>(LevelInfo::LEVEL1))
			{
				DrawFormatString(0, 0, 0xFFFFFF, "ゲームシーン");
			//	if (keyInput_->IsKeyTrigger(KEY_INPUT_SPACE))sceneNum = 0;
			}
		}

		// 描画処理
		if (sceneNum == static_cast<int>(Scene::TITLE))
		{
			DrawGraph(0, 0, titleGraph, true);
		}
		else if (sceneNum == static_cast<int>(Scene::MEMU))
		{
			DrawGraph(0, 0, stageSelectGraph, true);
			
			//メニューのステージの描画
			for (int i = 0; i < stageNum_; i++)
			{
				levelSelect_[i].Draw(levelGraph_[i]);
			}
		}
		else if (sceneNum == static_cast<int>(Scene::GAMESCENE))
		{
			if (levelNum == static_cast<int>(LevelInfo::LEVEL1))
			{
				DrawGraph(0, 0, haikei5X5, TRUE);
			}
			if (levelNum == static_cast<int>(LevelInfo::LEVEL2))
			{
				DrawGraph(0, 0, haikei6X6, TRUE);
			}

			map_->Draw(levelNum, graphHandle, cardboardHandle, truckHandle);
			createArrow_->Draw(arrowHandle);
			move_->Draw(levelNum, graphHandle, cardboardHandle, truckHandle);

			if (levelNum == 0)DrawFormatString(0, 0, 0xFFFFFF, "1");
			else if (levelNum == 1) DrawFormatString(0, 0, 0xFFFFFF, "2");
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
	delete mouse_;
	delete keyInput_;
	delete[] levelSelect_;

	// 正常終了
	return 0;
}