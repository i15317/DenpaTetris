#include"Cell.h"
#include"DxLib.h"
#include"Field.h"
#include"Point.h"
#include"Piece.h"
#include"Render.h"

TetrisRender::TetrisRender() {
	//fontHandleLarge = CreateFontToHandle(L"HGP�n�p�p�|�b�v��", 40, 3);
	//fontHandle = CreateFontToHandle(L"HGP�n�p�p�|�b�v��", 32, 8);
}


void TetrisRender::Render() {
	//	field_->clear();
		//�Q�[���t�B�[���h�̃����_�[
	{
		for (int y = 0; y < FieldHeight; y++) {
			for (int x = 0; x < FieldWidth; x++) {
				int pixelX = (x + 1) * SizeCellPixelX;
				int pixelY = (y + 1) * SizeCellPixelY;
				Cell cell = m_field->getCell(x, y);
				//��`�\��
				drawRectangle(cell, pixelX, pixelY);
			}
		}
	}

	//���݂̃u���b�N�̃����_�[
	{
		for (int y = 0; y < PieceHeight; y++) {
			Point pos = m_currentPiece->getPos();
			if (pos.y + y < 0) {
				continue;
			}
			for (int x = 0; x < PieceWidth; x++) {
				int pixelX = (pos.x + x + 1) * SizeCellPixelX;
				int pixelY = (pos.y + y + 1) * SizeCellPixelY;
				Cell cell = m_currentPiece->getCell(x, y);
				drawRectangle(cell, pixelX, pixelY);
			}
		}
	}
	//���̃u���b�N
	{
		for (int y = 0; y < PieceHeight; y++)
		{
			for (int x = 0; x < PieceWidth; x++)
			{
				int pixelX = (FieldWidth + 2 + x) * SizeCellPixelX;
				int pixelY = (y + 1) * SizeCellPixelY;
				Cell cell = m_nextPiece->getCell(x, y);
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
}