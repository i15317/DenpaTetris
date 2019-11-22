//{{NO_DEPENDENCIES}}
// Microsoft Visual C++ で生成されたインクルード ファイルです。
// 次で使用: DenpaTetris.rc
#pragma once
#include"Render.h"
#include<queue>

#define IDS_APP_TITLE			103
#define IDR_MAINFRAME			128
#define IDD_DENPATETRIS_DIALOG	102
#define IDD_ABOUTBOX			103
#define IDM_ABOUT				104
#define IDM_EXIT				105
#define IDI_DENPATETRIS			107
#define IDI_SMALL				108
#define IDC_DENPATETRIS			109
#define IDC_MYICON				2
#ifndef IDC_STATIC
#define IDC_STATIC				-1
#endif
// 新しいオブジェクトの次の既定値
//
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS

#define _APS_NO_MFC					130
#define _APS_NEXT_RESOURCE_VALUE	129
#define _APS_NEXT_COMMAND_VALUE		32771
#define _APS_NEXT_CONTROL_VALUE		1000
#define _APS_NEXT_SYMED_VALUE		110
#endif
#endif


/*

Tetris用リソース

*/

constexpr int PieceWidth = 4;
constexpr int PieceHeight = 4;
constexpr int FieldWidth = 14;
constexpr int FieldHeight = 23;
constexpr int SizeCellPixelX = 20;
constexpr int SizeCellPixelY = 20;
constexpr int MovePixcel = 19;
constexpr int SizeBmPixelX = 420;
constexpr int SizeBmPixelY = 520;


//レンダー
extern TetrisRender g_tetrisRender;
//ウィンドウハンドル
extern HWND hMainWnd;
//ウィンドウプロシージャのアドレス
extern WNDPROC dxWndProc;
//キー入力処理を貯めておくキュー
extern std::queue<WPARAM>keyBuf;

//自作メッセージプロシージャー
LRESULT CALLBACK messageProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam);

