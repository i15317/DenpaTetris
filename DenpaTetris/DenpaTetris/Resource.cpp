#include"Resource.h"



//グローバル変数の実態作成
TetrisRender g_tetrisRender;
std::queue<WPARAM>keyBuf;
HWND hMainWnd;
WNDPROC dxWndProc;


//自作メッセージプロシージャー
LRESULT CALLBACK messageProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		//キューにキーイベントのキーを格納する
		keyBuf.push(wparam);
		break;

	//Dxlibはウィンドウクローズのイベントをうまいこと処理してくれないのでこちらで何とかする
	case WM_CLOSE:
		PostQuitMessage(0);
		break;

	}

}

