#pragma once
#include<memory>
#include<stack>
#include<vector>

class Field;
class Piece;

class TetrisManager {
public:
	//�ړ�����
	enum Dir {
		Left,
		Right,
		Down,
	};
	TetrisManager(Field* field);
	~TetrisManager();

	//�s�[�X��o�^����
	void SubmitPiece(Piece* piece);
	//�ړ��\���`�F�b�N������
	bool isMovable(const Point& pos)const
	{
		for (int y = 0; y < PieceHeight; y++) {
			for (int x = 0; x < PieceWidth; x++) {
				if (m_currentPiece->checkStateBlock(x, y)) {
					int ofsX = pos.x + x;
					int ofsY = pos.y + y;
					bool validPos = (0 <= ofsX && ofsX <= FieldWidth - 1)
						&&
						(0 <= ofsY && ofsY <= FieldHeight - 1);
					if (ofsX < 0 || ofsX >= FieldWidth
						|| ofsY >= FieldHeight
						|| (validPos && m_field->getCell(ofsX, ofsY).getBlock()))
					{
						return false;
					}
				}
			}
		}
		return true;
	}

	//�ړ��\���`�F�b�N������
	bool isMovable(const Point& pos, const Cell cells[][PieceHeight])const {
		for (int y = 0; y < PieceHeight; y++) {
			for (int x = 0; x < PieceWidth; x++) {
				if (cells[x][y].getBlock()) {
					int ofsX = pos.x + x;
					int ofsY = pos.y + y;
					bool validPos = (0 <= ofsX && ofsX <= FieldWidth - 1)
						&&
						(0 <= ofsY && ofsY <= FieldHeight - 1);
					if (ofsX < 0 || ofsX >= FieldWidth
						|| ofsY >= FieldHeight
						|| (validPos && m_field->getCell(ofsX, ofsY).getBlock()))
					{
						return false;
					}
				}
			}
		}
		return true;
	}

	bool turn();

	bool movePiece(Dir dir);

private:
	std::shared_ptr<Field> m_field;
	std::shared_ptr<Piece> m_currentPiece;
	//�X�^�b�N
	std::vector<std::shared_ptr<Piece>>m_oldPieces;
};