#pragma once
#include<memory>
#include<stack>
#include<vector>

class Field;
class Piece;

/*
テトリスのゲームを管理するやつ（のはず）
*/

class TetrisManager {
public:
	//移動方向
	enum Dir {
		Left,
		Right,
		Down,
	};


	TetrisManager(Field* field);
	~TetrisManager();

	//ピースを登録する
	void SubmitPiece(Piece* piece);
	//移動可能かチェックするやつ
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

	//移動可能かチェックするやつ
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
	void fixPiece(const Point pos);
	
private:
	std::shared_ptr<Field> m_field;
	std::shared_ptr<Piece> m_currentPiece;
	//スタック
	std::vector<std::shared_ptr<Piece>>m_oldPieces;
};