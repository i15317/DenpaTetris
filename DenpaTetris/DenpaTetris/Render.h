#pragma once

//�����_���[

class Render {
public:
	Render() {
		fontHandleLarge = CreateFontToHandle(L"HGP�n�p�p�|�b�v��", 40, 3);
		fontHandle = CreateFontToHandle(L"HGP�n�p�p�|�b�v��", 32, 8);
	}
	//�`�揈��
	void Render() {
		//	field_->clear();
			//�Q�[���t�B�[���h�̃����_�[
		{
			for (int y = 0; y < FieldHeight; y++) {
				for (int x = 0; x < FieldWidth; x++) {
					int pixelX = (x + 1) * SizeCellPixelX;
					int pixelY = (y + 1) * SizeCellPixelY;
					Cell cell = field_->getCell(x, y);
					//��`�\��
					drawRectangle(cell, pixelX, pixelY);
				}
			}
		}

		//���݂̃u���b�N�̃����_�[
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
		//���̃u���b�N
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

	/*

�`��n

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

	//�e�L�X�g�`��
	void renderText() {
		DrawStringToHandle(330, 130, L"�������", GetColor(255, 255, 255), fontHandleLarge);
		DrawStringToHandle(330, 180, L"R�L�[�E�E�E��]", GetColor(255, 255, 255), fontHandle);
		DrawStringToHandle(330, 230, L"���L�[�F �ړ�", GetColor(255, 255, 255), fontHandle);
		DrawStringToHandle(330, 280, L"Q�L�[�E�E�E�I���", GetColor(255, 255, 255), fontHandle);

	}

	int		fontHandle;
	int		fontHandleLarge;
};