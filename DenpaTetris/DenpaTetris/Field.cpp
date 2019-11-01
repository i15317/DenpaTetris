#include"Point.h"
#include"Cell.h"
#include"Field.h"

//�R���X�g���N�^����

Field::Field() {
	//�������p�֐�
	this->clear();
}

//�������֐�
void Field::clear() {
	for (int y = 0; y < FieldHeight; y++)
		for (int x = 0; x < FieldWidth; x++) {
			//�e�u���b�N������������
			cells_[x][y].clear();
		}
}

//�폜�֐�
int Field::deleteLine() {
	int delCount = 0;
	//�ŉ����ȊO�̉����C�����S�ău���b�N�I�u�W�F�N�g���������܂�
	int xNumPerLine = 0;
	for (int y = FieldHeight - 1; y >= 0; y--) {
		xNumPerLine = 0;
		for (int x = 0; x < FieldWidth; x++) {
			if (cells_[x][y].getBlock()) {
				xNumPerLine++;
			}
		}
		//���T�C�Y�ƈꏏ�Ŗ�����Δ�΂�
		if (xNumPerLine != FieldWidth) {
			continue;
		}
		//�폜�����C���N�������g
		delCount++;
		//�폜����
		for (int x = 0; x < FieldWidth; x++) {
			cells_[x][y].clear();
		}
	}
	//�폜��������Ԃ�
	return delCount;
}

void Field::fixPiece(const Point pos, const Cell cells[][PieceHeight])
{
	for (int y = 0; y < PieceHeight; y++)
	{
		for (int x = 0; x < PieceWidth; x++)
		{

			if (cells[x][y].getBlock() && pos.y + y >= 0)
			{
				cells_[pos.x + x][pos.y + y] = cells[x][y];
			}
		}
	}
}

/*

���̊֐�������

*/
void Field::shiftLine(int delCount)
{

	int xNumPerLine = 0;
	for (int y = FieldHeight - 1; y >= 0 && delCount;) {
		xNumPerLine = 0;
		for (int x = 0; x < FieldWidth; x++) {
			if (cells_[x][y].getBlock()) {
				xNumPerLine++;
			}
		}
		if (xNumPerLine != 0) {
			y--;
			continue;
		}
		for (int ty = y; ty >= 0; ty--) {
			for (int tx = 0; tx < FieldWidth; tx++) {
				if (ty - 1 >= 0) {
					//�������ɃV�t�g
					cells_[tx][ty] = cells_[tx][ty - 1];
				}
				//0�s����ɂȂ�ꍇ
				else {
					cells_[tx][0].clear();
				}
			}
		}
		//��s�l�߂�
		delCount--;
	}
}

