#include<DxLib.h>
#include<Windows.h>
#include"Resource.h"
#include"Scene.h"
#include"Tetris.h"
#include"Executor.h"

//レンダー
extern TetrisRender g_tetrisRender;
//ウィンドウハンドル
extern HWND hMainWnd;
//キー入力処理を貯めておくキュー
extern std::queue<WPARAM>keyBuf;
//ウィンドウプロシージャのアドレス
extern WNDPROC dxWndProc;

Executor::Executor()
{
	prev_scene = DEFAULT;
	current_scene = DEFAULT;
	next_scene = TOP;
}

void Executor::init()
{
	//Dxlibの初期セットアップ
	{
		SetWindowSize(800, 600);
		ChangeWindowMode(true);
	}

	//Dxlibの初期化処理
	{
		//最終初期化処理
		if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
		{
			std::exit(1);			// エラーが起きたら直ちに終了
		}
	}

	//Dxlibの初期化後の処理
	{
		//バックバッファの設定かな？
		SetDrawScreen(DX_SCREEN_BACK);
		// 同期読み込み設定に変更
		SetUseASyncLoadFlag(FALSE);

		ClearDrawScreen();
	}

	//キーイベント処理の設定
	{
		//ウィンドウハンドルの取得
		hMainWnd = GetMainWindowHandle();
		//メインウィンドウのウィンドウプロシージャのアドレスを取得
		dxWndProc = (WNDPROC)GetWindowLong(hMainWnd, GWLP_WNDPROC);
		//ウィンドウプロシージャのアドレス登録
		SetWindowLongW(hMainWnd, GWLP_WNDPROC, (LONG)messageProc);
	}

	//シーンの作成
	{
		m_tetrisScene = new Tetris();
	}

}

void Executor::Run()
{
	while (true)
	{
		//メインアップデート
		update();

		render();
	}
}

void Executor::Update()
{
	m_currentScene->Update();
}


void Executor::update()
{

	/*
	自身のライフサイクルで行う処理
	*/

	//シーン決定
	switch (next_scene)
	{
	case DEFAULT:
		break;
	case TOP:
		prev_scene = current_scene;
		current_scene = TOP;
		break;
	case TETRIS:
		prev_scene = current_scene;
		current_scene = TETRIS;
	}

	switch (current_scene)
	{	
	case TOP:
		m_currentScene = m_topScene;
		break;
	case TETRIS:
		m_currentScene = m_tetrisScene;
		break;
	case DEFAULT:
		break;
	}
	
	while (!keyBuf.empty())
	{
		//現在のシーンにバッファーのキーボードイベントをすべて流す
		m_currentScene->RegistKeyValue(keyBuf.front());
		keyBuf.pop();
	}

	/*
	配下オブジェクトにライフサイクルを遷移する
	*/

	//Executor配下のオブジェクトのupdateを回す
	Update();
}

void Executor::render()
{
	/*
	自身のライフサイクルで行う処理
	*/

	//クリア処理
	ClearDrawScreen();


	/*
	配下オブジェクトにライフサイクルを遷移する
	*/

	//描画処理
	Render();
}

void Executor::Render()
{
	m_currentScene->Render();
}