#include"Field.h"
#include"Piece.h"
#include"Point.h"
#include"Cell.h"
#include"TetrisManager.h"

bool TetrisManager::movePiece(Dir dir) {
	auto pos_ = m_currentPiece->getPos();
	switch (dir) {
	case Left:
		//Leftブロック
	{
		Point pos = { pos_.x - 1,pos_.y };
		if (isMovable(pos)) {
			pos_ = pos;
		}
		else
		{
			return false;
		}
		break;
	}//Leftブロック終端
	case Right:
	{
		Point pos = { pos_.x + 1,pos_.y };
		if (isMovable(pos)) {
			pos_ = pos;
		}
		else {
			return false;
		}

		break;
	}//Rightブロック
	case Down:
	{
		Point pos = { pos_.x,pos_.y + 1 };
		if (isMovable(pos)) {
			pos_ = pos;
		}
		else
		{
			field_->fixPiece(pos_, cells_);
			return false;
		}
		break;
	}//Downブロック
	}//Switchブロック
	return true;
}//関数終端

//右にクルクル
bool TetrisManager::turn()
{
	Cell cells[PieceWidth][PieceHeight];

	//右回転
	for (int y = 0; y < PieceHeight; y++) {
		for (int x = 0; x < PieceWidth; x++) {
			//作業用コピピピピピピピィィィィィ
			/*
			-pi/2の回転行列をかければ
			x' = -y , y' = x
			となることが分かる
			*/
			//回転変換
			cells[PieceHeight - y - 1][x] = m_currentPiece->getCell[x][y];
		}
	}

	//この移動に現実性があるかどうか
	if (isMovable(m_currentPiece->getPos(), cells))
	{
		for (int y = 0; y < PieceHeight; y++) {
			for (int x = 0; x < PieceWidth; x++) {
				//こぴー
				m_currentPiece->updateCell(x, y, cells[x][y]);
			}
		}
	}
	else {
		return false;
	}

	return true;
}//こ↑こ↓まで

void TetrisManager::SubmitPiece(Piece* add_piece) {
	//バックアップ用ポインターの作成
	std::shared_ptr<Piece>back_ptr(m_currentPiece.get());
	//バックアップ処理
	m_oldPieces.push_back(back_ptr);
	//新しいピースの位置を参照する
	m_currentPiece.reset(add_piece);
}