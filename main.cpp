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
const char TITLE[] = "6001_ツミコミパズル";

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
	int spotLightHandle[5];
	LoadDivGraph("Resource/spotLight.png", 5, 5, 1, 1920, 1080, spotLightHandle);

	int arrowPanel[4];
	LoadDivGraph("Resource/arrowPanel.png", 4, 4, 1, 128, 128, arrowPanel);

	int markerGraph[4];
	LoadDivGraph("Resource/marker.png", 4, 4, 1, 64, 64, markerGraph);
	//sound
	int picSE = LoadSoundMem("Resource/pic.wav");
	int bgm = LoadSoundMem("Resource/bgm.mp3");
	int clearSE = LoadSoundMem("Resource/clear.mp3");
	int truckSE = LoadSoundMem("Resource/track.mp3");
	int cardbordSE = LoadSoundMem("Resource/cardbord.mp3");
	int rockSE = LoadSoundMem("Resource/rock.mp3");
	int failedSE = LoadSoundMem("Resource/failed.mp3");
	int resetSE = LoadSoundMem("Resource/reset.mp3");
	int ketteiSE = LoadSoundMem("Resource/kettei.mp3");

	//メニューのレベルごと
	int levelGraph_[] = {
		LoadGraph("Resource/stage1.png"),
		LoadGraph("Resource/stage2.png")	,
		LoadGraph("Resource/stage3.png")	,
		LoadGraph("Resource/stage4.png")	,
		LoadGraph("Resource/stage5.png")	,
		LoadGraph("Resource/stage6.png")
	};
	int noGraph_[] = {
		LoadGraph("Resource/no1.png"),
		LoadGraph("Resource/no2.png")	,
		LoadGraph("Resource/no3.png")	,
		LoadGraph("Resource/no4.png")	,
		LoadGraph("Resource/no5.png")	,
		LoadGraph("Resource/no6.png")
	};

	//背景
	int clearGraph = LoadGraph("Resource/clear.png");
	int failedGraph = LoadGraph("Resource/failed.png");
	int toracGraph = LoadGraph("Resource/torac.png");
	int haikei5X5 = LoadGraph("Resource/5X5.png");
	int haikei6X6 = LoadGraph("Resource/6X6.png");
	int titleGraph = LoadGraph("Resource/title.png");
	int stageSelectGraph = LoadGraph("Resource/stageselect.png");
	int hintGraph = LoadGraph("Resource/hint.png");
	int speedPic[2]; LoadDivGraph("Resource/speedPic.png",2,2,1,72,64,speedPic);

	// ゲームループで使う変数の宣言
	//ステージ数
	const int stageNum_ = 6;

	//マップやファイル読み込み
	LoadFile* loadFile_ = LoadFile::GetInstance();
	const char* c_mapName[] = { "level1.csv","level2.csv","level3.csv","level4.csv","level5.csv","level6.csv","END" };
	
	const char* c_comamndName[] = { "moveCommand.csv","moveCommand2.csv","moveCommand3.csv","moveCommand4.csv","moveCommand5.csv","moveCommand6.csv","END" };

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

	Box stageSelect = { 1561,20,238,64 };
	Box reset = {1211, 20, 238, 64};
	Box hint5x5 = {764,84,90,90};
	Box hint6x6 = {830,30,90,90};
	bool hintFlag = false;
	Point hinPos[6] = { {3,3},{1,1},{3,2},{2,2},{2,3},{2,4} };
	int firstSetX = 160;
	int firstSetY = 128;


	//ムーブ関数の生成
	Move* move_ = nullptr;
	//ムーブ関数の初期化
	move_ = new Move();
	
	//始まった時にtureにしステージを出るときにfalse、一度だけ実行するため
	static bool isStart_ = false;


	// 最新のキーボード情報用
	
	Mouse* mouse_;
	mouse_ = Mouse::GetInstance();
	mouse_->Initialize();
	mouse_->SetSound(picSE);
	Point mousePos = { 0,0 };

	KeyInput* keyInput_;
	keyInput_ = new KeyInput;                                     

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
			SetVolumeSoundMem(8300, bgm);
			SetVolumeSoundMem(9900,truckSE);
			SetVolumeSoundMem(9000, cardbordSE);
			SetVolumeSoundMem(8700, rockSE);
			SetVolumeSoundMem(8900, failedSE);
			SetVolumeSoundMem(8300, resetSE); 
			SetVolumeSoundMem(8900, picSE);
			
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

				//ステージの行動の読み込みを一度だけ読み込む
				if (!isStart_)
				{
					loadFile_->LoadCommand(c_comamndName[levelNum]);
					move_->Initialize();
					move_->Reset(resetSE);
					hintFlag = false;
				}
			}
		}

		//ゲームシーン
		else if (sceneNum == static_cast<int>(Scene::GAMESCENE))
		{
			//ステージの行動の読み込みを一度だけ読み込む
			if (!isStart_) 
			{
				loadFile_->LoadCommand(c_comamndName[levelNum]);
				move_->Initialize();
				move_->Reset(resetSE);
				isStart_ = true;
				hintFlag = false;
			}

			if (move_->GetIsCrear())
			{
				if (mouse_->MouseInput(MOUSE_INPUT_LEFT))
				{
					if (levelNum == static_cast<int>(LevelInfo::LEVEL6))
					{
						sceneNum = static_cast<int>(Scene::MEMU);
						isStart_ = false;
					}
					else {
						levelNum++;
						isStart_ = false;
					}
				}
			}
			
			move_->Update(levelNum, cardbordSE, truckSE, rockSE,failedSE,clearSE,resetSE,ketteiSE);
			
			if (mouse_->MouseCheckHitBox(stageSelect, mousePos))
			{
				isStart_ = false;
				sceneNum = static_cast<int>(Scene::MEMU);
			}
			if (mouse_->MouseCheckHitBox(reset, mousePos))
			{
				move_->Reset(resetSE);
				hintFlag = false;
			}

			if (levelNum == 0 || levelNum == 1 || levelNum == 4)
			{
				if (mouse_->MouseCheckHitBox(hint5x5, mousePos))
				{
					hintFlag = true;
				}
			}
			else 
			{
				if (mouse_->MouseCheckHitBox(hint6x6, mousePos))
				{
					hintFlag = true;
				}
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
			if (levelNum == static_cast<int>(LevelInfo::LEVEL1) || levelNum == static_cast<int>(LevelInfo::LEVEL2) || levelNum == static_cast<int>(LevelInfo::LEVEL5))
			{
				firstSetX = 224;
				firstSetY = 192;

				DrawGraph(0, 0, haikei5X5, TRUE);
				DrawGraph(600, 0, noGraph_[levelNum], TRUE);
			}
			if (levelNum == static_cast<int>(LevelInfo::LEVEL3)|| levelNum == static_cast<int>(LevelInfo::LEVEL4) || levelNum == static_cast<int>(LevelInfo::LEVEL6))
			{
				firstSetX = 160;
				firstSetY = 128;
				DrawGraph(0, 0, haikei6X6, TRUE);
				DrawGraph(600, 0, noGraph_[levelNum], TRUE);
			}

			if (hintFlag)
			{
				int mapChip = 128;
				DrawGraph(firstSetX + hinPos[levelNum].x * mapChip, firstSetY + hinPos[levelNum].y * mapChip, hintGraph, true);
			}

			map_->Draw(levelNum, graphHandle, cardboardHandle, truckHandle);
			createArrow_->Draw(arrowHandle);
			move_->Draw(levelNum, graphHandle, cardboardHandle, truckHandle, spotLightHandle, setumeiHandle,rightChip, arrowPanel,speedPic);
			mouse_->DrawMarker(markerGraph);
			if (move_->GetIsCrear())
			{
				DrawGraph(0, 0, clearGraph, true);
			}
			if (move_->GetIsFaile())
			{
				DrawGraph(0, 0, failedGraph, true);
			}
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
	delete keyInput_;
	delete[] levelSelect_;

	// 正常終了
	return 0;
}