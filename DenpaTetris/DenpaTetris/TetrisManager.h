#pragma once
#include<memory>
#include<stack>
#include<vector>

class Field;
class Piece;
class Point;
/*
テトリスの１ゲームを管理するやつ（のはず）
高速化を図るためヘッダー実装多め
*/

class TetrisManager {
public:
	//移動方向
	enum Dir {
		Default,
		Left,
		Right,
		Down,
		Rotate
	};

	TetrisManager(Field* field);
	TetrisManager();
	~TetrisManager();

	//ピースを登録する
	void SubmitPiece(Piece* piece);
	//メインアップデート
	bool update(Dir dir = Dir::Default);
	//メイン描画命令用
	void render();
	//初期化
	void init(Field* field);

private:

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

	void resetState();
	bool turn();
	void fixPiece(const Point pos);
	//ピース移動
	bool movePiece(Dir dir);

private:
	UINT m_score;
	UINT m_deletedPieceNum;
	std::shared_ptr<Field> m_field;
	std::shared_ptr<Piece> m_currentPiece;
	//スタック
	std::vector<std::shared_ptr<Piece>>m_oldPieces;
};