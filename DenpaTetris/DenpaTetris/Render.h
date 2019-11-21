#pragma once
#include<wrl.h>
//レンダラー
class Cell;
class Piece;
class Field;
class Point;
class TetrisRender {
public:

	//コンストラクタ
	TetrisRender();


	//描画処理
	void Render();
	//void Render(Piece* nextPiece) { m_currentPiece = m_nextPiece, m_nextPiece = nextPiece; Render(); }
	void submitCurrentPiece(Piece* currentPiece) { m_currentPiece = currentPiece; }
	void submitNextPiece(Piece* nextPiece) { m_nextPiece = nextPiece; }
	void submitField(Field* field) { m_field = field; }
	/*
	描画系
	*/
private:
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

	////テキスト描画
	//void renderText() {
	//	DrawStringToHandle(330, 130, L"操作説明", GetColor(255, 255, 255), fontHandleLarge);
	//	DrawStringToHandle(330, 180, L"Rキー・・・回転", GetColor(255, 255, 255), fontHandle);
	//	DrawStringToHandle(330, 230, L"矢印キー： 移動", GetColor(255, 255, 255), fontHandle);
	//	DrawStringToHandle(330, 280, L"Qキー・・・終わる", GetColor(255, 255, 255), fontHandle);
	//}
	//int		fontHandle;
	//int		fontHandleLarge;

private:
	Microsoft::WRL::ComPtr<Field>m_field;
	Microsoft::WRL::ComPtr<Piece>m_currentPiece;
	Microsoft::WRL::ComPtr<Piece>m_nextPiece;
};