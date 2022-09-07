#include "DxLib.h"
#include "MapMake.h"
// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "GE1A_ハヤシタカユキ: タイトル";

// ウィンドウ横幅
const int WIN_WIDTH =1920;

// ウィンドウ縦幅
const int WIN_HEIGHT = 1080;

enum Scene {
	STITLE,
	MEMU,
	GAMESCENE,
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
	int mousePosX, mousePosY;

	const char *c_mapName[] = {"mapSample.csv","END"};
	MapMake* map = new MapMake(6,6, c_mapName);
	// 最新のキーボード情報用
	char keys[256] = { 0 };
	int mouseInput = 0;

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };
	int oldmouseInput;

	// ゲームループ
	while (true) {
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		  //前のフレームを保存
		for (int i = 0; i < 256; i++)
		{
			oldkeys[i] = keys[i];
		}
		oldmouseInput = mouseInput;

		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);
		mouseInput = GetMouseInput();

		//マウスの座標取得
		GetMousePoint(&mousePosX, &mousePosY);

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理
		//タイトル
		if (sceneNum == Scene::STITLE)
		{
			DrawCircle(mousePosX, mousePosY, 5, 0xFF0000, true);
			DrawFormatString(0, 0, 0xFFFFFF, "タイトル");
			if ((mouseInput & MOUSE_INPUT_RIGHT) != 0 && (oldmouseInput & MOUSE_INPUT_RIGHT) == 0)sceneNum = 1;
		}

		//レベル選択
		if (sceneNum == Scene::MEMU)
		{
			DrawFormatString(0, 0, 0xFFFFFF, "レベル選択");
			if (keys[KEY_INPUT_2] == 1 && oldkeys[KEY_INPUT_2] == 0)sceneNum = 2;
		}

		//ゲームシーン
		if (sceneNum == GAMESCENE)
		{
			DrawFormatString(0, 0, 0xFFFFFF, "ゲームシーン");
			if (keys[KEY_INPUT_3] == 1 && oldkeys[KEY_INPUT_3] == 0)sceneNum = 0;
		}

		// 描画処理


		if (sceneNum == GAMESCENE) {
			map->Draw(0, graphHandle);

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

	delete map;

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