#pragma once
#include"Resource.h"
#include"Point.h"
//�O���錾
class Cell;

//�t�B�[���h�N���X
class Field {
public:
	//�R���X�g���N�^
	Field();

	//�������֐�
	void clear();

	//�폜�֐�
	int deleteLine();

	//�����낤����H
	/*
	�Ȃ񂾂���H
	*/
	void fixPiece(const Point pos, const Cell cells[][PieceHeight]);
	void updateState(int x, int y, Cell cell)
	{
		cells_[x][y] = cell;
	}
	//�폜�������𓮂���
	void shiftLine(int delCount);

	//�l�񂾂��ǂ������ׂ�
	bool isStacked()const
	{
		/*

		���������̌��ߑł�������

		*/
		if (cells_[6][0].getBlock() || cells_[7][0].getBlock()) {
			return true;
		}
		else {
			return false;
		}
	}

	Cell getCell(int x, int y) const
	{
		return cells_[x][y];
	}

	int getCellWidth()const { return sizeof(cells_[0] / cells_[0][0]); }
	int getCellWidth() const { return sizeof(cells_ / cells_[0]); }

private:
	//�u���b�N�z��
	Cell cells_[FieldWidth][FieldHeight];
};

