// DenpaTetris.cpp : アプリケーションのエントリ ポイントを定義します。
//
#define WIN32_LEAN_AND_MEAN

#define _CRT_SECURE_NO_WARNINGS

#define _CRT_NON_CONFORMING_SWPRINTFS
#include "framework.h"
#include "DenpaTetris.h"
#include"Tetris.h"
#include "DxLib.h"
#include<memory>

//Windowのセットアップコード
void SetupWindowConfig() {
	// 描画先画面を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);
	SetWindowSize(1280, 960);
	ChangeWindowMode(true);
}

void AppLoop() {
	char Buf[256];
	//tetris = new Tetris();
	std::shared_ptr<Tetris> tetris(new Tetris());
	//メインループ
	while (true) {
		GetHitKeyStateAll(Buf);
		// 画面全体を初期化
		ClearDrawScreen();

		//キーイベント処理
		if (Buf[KEY_INPUT_RIGHT] == 1)
		{
			tetris->getCurPiece()->move(Piece::Right);
		}
		else if (Buf[KEY_INPUT_LEFT] == 1)
		{
			tetris->getCurPiece()->move(Piece::Left);
		}
		else if (Buf[KEY_INPUT_DOWN] == 1) {
			tetris->getCurPiece()->move(Piece::Down);
		}
		else if (Buf[KEY_INPUT_R] == 1) {
			tetris->getCurPiece()->turn();
		}
		else if (Buf[KEY_INPUT_ESCAPE] == 1 || Buf[KEY_INPUT_Q] == 1) {
			break;
		}

		//状態更新
		tetris->Update();
		//描画
		tetris->Render();

		//ゲームの終了判定
		if (tetris->isGameover()) {
			break;
		}
		// 裏画面の内容を表画面に反映する
		ScreenFlip();
		Sleep(128);
	}
}

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	/*
	Windowの初期化コード
	*/
	SetupWindowConfig();

	char Buf[256];


	//最終初期化処理
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return false;			// エラーが起きたら直ちに終了
	}

	//メインループ
	while (true) {
		// 画面全体を初期化
		ClearDrawScreen();
		//キー応答待ち
		WaitKey();
		//キー操作取得
		GetHitKeyStateAll(Buf);
		if (Buf[KEY_INPUT_Q] == 1) {
			break;
		}
		else {
			//何もしない
		}
		AppLoop();
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}
