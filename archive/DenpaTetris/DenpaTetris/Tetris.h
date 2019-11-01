#pragma once
/*

Tetris用クラス群（突貫作成のため可読性はご容赦）
ヘッダー実装多め

*/

//ヘッダーインクルード
#include<tchar.h>
#include<Windows.h>
#include<random>
#include"Resource.h"
#include"DxLib.h"
#include"Item.h"
#include <mmsystem.h>
#include <stdlib.h>
#include <tchar.h>
#include <ctime>
#include <process.h>
#define MUTEX_NAME     _T("TetrisMutex")
#define WM_MUTEX       WM_APP
#define WM_RESTART     (WM_APP + 1)
/*

Tetris本体

*/

class Tetris {
public:
	//コンストラクタ実装
	explicit Tetris() :
		field_(nullptr), curPiece_(nullptr), nextPiece_(nullptr),
		playTime_(0), score_(0), isGameover_(false)
	{
		field_ = new Field();
		curPiece_ = createPiece();
		nextPiece_ = createPiece();
		//疑似乱数生成器の初期化
		mt.seed(rnd());


		fontHandleLarge = CreateFontToHandle(L"HGP創英角ポップ体", 40, 3);
		fontHandle = CreateFontToHandle(L"HGP創英角ポップ体", 32, 8);

	}
	//デストラクタ実装
	~Tetris()
	{
		releasePiece(nextPiece_);
		releasePiece(curPiece_);

		delete field_;
	}
	void  releasePiece(Piece* piece)
	{
		if (piece != nullptr)
		{
			delete piece;
			piece = nullptr;
		}
	}
	Piece* createPiece()
	{
		//乱数取得
		int value = rnd() % 7;

		switch (value)
		{
		case 0:
			return new Piece0(field_);
		case 1:
			return new Piece1(field_);
		case 2:
			return new Piece2(field_);
		case 3:
			return new Piece3(field_);
		case 4:
			return new Piece4(field_);
		case 5:
			return new Piece5(field_);
		case 6:
			return new Piece6(field_);
		}
		return nullptr;
	}

	Piece* getCurPiece() const
	{
		return curPiece_;
	}

	void Update()
	{
		bool isSucceeded = curPiece_->move(Piece::Down);
		if (!isSucceeded)
		{
			int line = field_->deleteLine();
			if (line > 0)
			{
				curPiece_->clear();
				if (line == 4)
				{
					score_ += 1000;
				}
				else
				{
					score_ += (line * 100);
				}
				field_->shiftLine(line);
			}
			if (field_->isStacked())
			{
				isGameover_ = true;
		//		SendMessage(nullptr, WM_RESTART, 0, 0);
			}
			releasePiece(curPiece_);
			curPiece_ = nextPiece_;
			nextPiece_ = createPiece();
		}
	}

	//描画処理
	void Render() {
	//	field_->clear();
		//ゲームフィールドのレンダー
		{
			for (int y = 0; y < FieldHeight; y++) {
				for (int x = 0; x < FieldWidth; x++) {
					int pixelX = (x + 1) * SizeCellPixelX;
					int pixelY = (y + 1) * SizeCellPixelY;
					Cell cell = field_->getCell(x, y);
					//矩形表示
					drawRectangle(cell, pixelX, pixelY);
				}
			}
		}

		//現在のブロックのレンダー
		{
			for (int y = 0; y < PieceHeight; y++) {
				Point pos = curPiece_->getPos();
				if (pos.y + y < 0) {
					continue;
				}
				for (int x = 0; x < PieceWidth; x++) {
					int pixelX = (pos.x + x + 1) * SizeCellPixelX;
					int pixelY = (pos.y + y + 1) * SizeCellPixelY;
					Cell cell = curPiece_->getCell(x, y);
					drawRectangle(cell, pixelX, pixelY);
				}
			}
		}
		//次のブロック
		{
			for (int y = 0; y < PieceHeight; y++)
			{
				for (int x = 0; x < PieceWidth; x++)
				{
					int pixelX = (FieldWidth + 2 + x) * SizeCellPixelX;
					int pixelY = (y + 1) * SizeCellPixelY;
					Cell cell = nextPiece_->getCell(x, y);
					drawRectangle(cell, pixelX, pixelY);
				}
			}
		}

		DrawBox(
			(FieldWidth + 2) * SizeCellPixelX, SizeCellPixelY,
			(FieldWidth + 2 + PieceWidth) * SizeCellPixelX, (PieceHeight + 1) * SizeCellPixelY, GetColor(255, 255, 255), false);
		DrawBox(
			SizeCellPixelX, SizeCellPixelY,
			(FieldWidth + 1) * SizeCellPixelX, (FieldHeight + 1) * SizeCellPixelY, GetColor(255, 255, 255), false);

		drawLine();

		renderText();

	}

	//テキスト描画
	void renderText() {
		DrawStringToHandle(330, 130, L"操作説明", GetColor(255, 255, 255), fontHandleLarge);
		DrawStringToHandle(330, 180, L"Rキー・・・回転", GetColor(255, 255, 255), fontHandle);
		DrawStringToHandle(330, 230, L"矢印キー： 移動", GetColor(255, 255, 255), fontHandle);
		DrawStringToHandle(330, 280, L"Qキー・・・終わる", GetColor(255, 255, 255), fontHandle);

	}


	/*DWORD WINAPI executeThread()
	{
		HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, MUTEX_NAME);

		DWORD  signal = -1;
		DWORD  prevTime = timeGetTime();
		DWORD  sleeptime = 1000;
		DWORD  minute = 0;

		while (true)
		{
			DWORD difftime = timeGetTime() - prevTime;
			if (difftime < sleeptime)
			{
				signal = WaitForSingleObject(hMutex, sleeptime - difftime);
			}
			difftime = timeGetTime() - prevTime;
			playTime_ += difftime;
			minute += difftime;
			if (minute >= 60 * 1000 && sleeptime > 100)
			{
				sleeptime -= 100;
				minute = 0;
			}
			prevTime = timeGetTime();

			bool isSucceeded = curPiece_->move(Piece::Down);
			if (!isSucceeded)
			{
				int line = field_->deleteLine();
				if (line > 0)
				{
					curPiece_->clear();
					if (line == 4)
					{
						score_ += 1000;
					}
					else
					{
						score_ += (line * 100);
					}
					InvalidateRect(nullptr, NULL, FALSE);

					Sleep(500);
					field_->shiftLine(line);
				}
				if (field_->isStacked())
				{
					isGameover_ = true;
					ReleaseMutex(hMutex);
					CloseHandle(hMutex);
					int ans = MessageBox(nullptr, _T("Continue ?"), _T("Gameover"), MB_YESNO);
					if (ans == IDYES)
					{
						SendMessage(nullptr, WM_RESTART, 0, 0);
					}
					else if (ans == IDNO)
					{
						SendMessage(nullptr, WM_DESTROY, 0, 0);
					}
					return 0;
				}
				releasePiece(curPiece_);
				curPiece_ = nextPiece_;
				nextPiece_ = createPiece();
			}
			InvalidateRect(nullptr, NULL, FALSE);
			if (signal == WAIT_OBJECT_0)
			{
				ReleaseMutex(hMutex);
				SendMessage(nullptr, WM_MUTEX, 0, 0);
			}

		}
		return 0;
	}*/
	
	bool isGameover() {
		return isGameover_;
	}

	void resetState() {
		score_ = 0;
		playTime_ = 0;
		isGameover_ = false;
	}
	//static UINT WINAPI threadProc(void* parameter)
	//{
	//	return (reinterpret_cast<Tetris*>(parameter))->executeThread();
	//}
private:

	/*

	描画系

	*/

	void drawRectangle(Cell cell, int pixelX, int pixelY) {
		if (cell.getBlock())
		{
			DrawBox(
				pixelX,
				pixelY,
				pixelX + SizeCellPixelX,
				pixelY + SizeCellPixelY,
				cell.getColor(),
				true
			);
		}
	}

	void drawLine()
	{
		int LineColor = GetColor(127, 127, 127);
		for (int x = 1; x < FieldWidth; x++)
		{
			int pixelX = (x + 1) * SizeCellPixelX;
			int pixelY = 1 * SizeCellPixelY;
			DrawLine(pixelX, pixelY, pixelX, (FieldHeight + 1) * SizeCellPixelY, LineColor);
		}
		for (int y = 1; y < FieldHeight; y++)
		{
			int pixelX = 1 * SizeCellPixelX;
			int pixelY = (y + 1) * SizeCellPixelX;
			DrawLine(pixelX, pixelY, (FieldWidth + 1) * SizeCellPixelX, pixelY, LineColor);
		}
	}



private:
	Piece* nextPiece_;
	Piece* curPiece_;
	Field* field_;
	int       playTime_;
	int       score_;
	bool      isGameover_;
	std::random_device rnd;
	std::mt19937_64 mt;
	std::uniform_int_distribution<> rand;
	int		fontHandle;
	int		fontHandleLarge;

};

