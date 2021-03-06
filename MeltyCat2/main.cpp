#include "DxLib.h"
#include "Player.h"
#include "Block.h"
#include "Item.h"
#include "Cursor.h"

#include "GameStart.h"
#include "StageSelect.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "MeltyCat";

// ウィンドウ横幅
const int WIN_WIDTH = 1280;

// ウィンドウ縦幅
const int WIN_HEIGHT = 768;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
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
	SetBackgroundColor(0x80, 0x80, 0xFF);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み
	int buck = LoadGraph("graphic/buckground.png");//start背景
	int game_name[8];//ゲーム名
	LoadDivGraph("graphic/MeltyCat.png", 8, 8, 1, 64, 64, game_name);

	// ゲームループで使う変数の宣言
	int frame = 0;

	int scene = 0;
	
	//startで使用する
	int buck_pos_x = 0,buck_pos_y = 0;//背景座標

	//背景のパーティクル
	const int staet_particle_num = 200;
	GameStart gamestart[staet_particle_num];
	StageSelect stage_select;
	
	//ゲーム名移動
	float name_x[8], name_y[8];
	int name_flag[8];
	int name_count = 0;
	float name_move[8];
	for (int i = 0; i < 8; i++)
	{
		if (i < 5)
		{
			name_x[i] = 200 + i * 100;
		} else
		{
			name_x[i] = 350 + i * 100;
		}
		name_y[i] = -70;
		name_move[i] = 0;
		name_flag[i] = 0;
	}
	//

	//ステージ選択
	char key_A = false, key_D = false;
	
	/*Player*/
	enum Cat { SOLID/*固体*/, LIQUID/*液体*/ };
	Player* player = new Player(800, 352, 32, 2, 0, SOLID);
	/*Item*/
	Item* item = new Item(1120, 160, 8, 1);
	/*PlayArea*/
	const int edgeL = 320;
	/*JampBlock*/
	enum Jamp { LU, LD, RD, RU };/*Left,Right,Up,Down*/
	Block* block = new Block(0, 0, 32, 0, LU);
	/*Cursor*/
	Cursor* cursor = new Cursor(0, 0, 32, 0, 0, LU);


	//あとで消す
	/*MapChip*/
	int map[12][15] = {
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
	};

	//
	
	// 最新のキーボード情報用
	char keys[256] = { 0 };
	int click = 0;

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };
	int oldclick = 0;

	// ゲームループ
	while (1) {
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		for (int i = 0; i < 256; i++) {
			oldkeys[i] = keys[i];
		}
		oldclick = click;
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);
		click = GetMouseInput();

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理
		frame++;

		//スタート画面
		if (scene == 0)
		{
			//初期化
			if (frame == 1)
			{
				for (int i = 0; i < staet_particle_num; i++)
				{
					gamestart[i].start(i);
				}
			}

			//題名
			if (frame % 30 == 1 && name_y[name_count] < -60 && name_flag[name_count] == 0)
			{
				name_flag[name_count] = 1;
				name_move[name_count] = 10;
				name_count++;
				if (name_count == 8)
				{
					name_count = 0;
				}
			}

			//文字移動
			for (int i = 0; i < 8; i++)
			{
				if (name_flag[i] == 1)
				{
					name_move[i] = name_move[i] * 1.09;
				}

				if (name_y[i] + name_move[i] > 330)
				{
					name_flag[i] = 2;
				}
			}

			//particle処理
			for (int i = 0; i < staet_particle_num; i++)
			{
				gamestart[i].update();
			}

			//次に行く
			if (keys[KEY_INPUT_SPACE] == true && oldkeys[KEY_INPUT_SPACE] == false)
			{
				scene = 1;
			}
		}

		//ステージ選択
		else if (scene == 1)
		{
			//Aキーの処理
			if (keys[KEY_INPUT_A] == 1 && oldkeys[KEY_INPUT_A] == 0)
			{
				key_A = true;
			}
			else
			{
				key_A = false;
			}
			//Dキーの処理
			if (keys[KEY_INPUT_D] == 1 && oldkeys[KEY_INPUT_D] == 0)
			{
				key_D = true;
			}
			else
			{
				key_D = false;
			}
			if (keys[KEY_INPUT_SPACE] == true && oldkeys[KEY_INPUT_SPACE] == false)
			{
				scene = 2;
			}
		}
		
		else if (scene == 2)
		{
			player->update(edgeL, WIN_WIDTH, WIN_HEIGHT, block, item);
			block->update();
			item->update();
			cursor->update(edgeL, keys, oldkeys, click, oldclick, block, WIN_WIDTH, WIN_HEIGHT);
		}
		
		// 描画処理
		if (scene == 0)
		{
			//背景
			DrawGraph(buck_pos_x, buck_pos_y, buck, true);
			//パーティクル
			for (int i = 0; i < staet_particle_num; i++)
			{
				gamestart[i].draw(i);
			}
			//ゲーム名
			for (int i = 0; i < 8; i++)
			{
				DrawRotaGraph(name_x[i], name_y[i] + name_move[i], 1.6, 0, game_name[i], true);
			}
		}

		/*PlaeArea*/
		if (scene == 2)
		{
			DrawBox(edgeL, 0, WIN_WIDTH, WIN_HEIGHT, GetColor(255, 192, 192), true);
			for (int i = 0; i < 15; i++) {
				for (int j = 0; j < 12; j++) {
					DrawBox(i * 64 + edgeL, j * 64, (i + 1) * 64 + edgeL, (j + 1) * 64, GetColor(255, 255, 255), false);
				}
			}
			cursor->draw(edgeL, WIN_WIDTH, WIN_HEIGHT);
			block->draw();
			item->draw();
			player->draw();
		}
		/*デバッグコード*/
		DrawFormatString(0, 0, GetColor(255, 255, 255), "%f", name_y[0] + name_move[0]);

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

	// 正常終了
	return 0;
}