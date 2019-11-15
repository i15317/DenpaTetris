#include"Field.h"
#include"Piece.h"
#include"Point.h"
#include"Cell.h"
#include"PieceMaker.h"
#include"TetrisManager.h"


TetrisManager::TetrisManager(Field* field)
{
	init(field);
}

TetrisManager::TetrisManager() {

}

TetrisManager::~TetrisManager()
{
	for (auto piece : m_oldPieces)
	{
		piece.reset();
	}
	m_oldPieces.clear();
	m_oldPieces.shrink_to_fit();
}


void TetrisManager::init(Field* field)
{
	m_field.reset(field);
}


void TetrisManager::fixPiece(const Point pos)
{
	for (int y = 0; y < PieceHeight; y++)
	{
		for (int x = 0; x < PieceWidth; x++)
		{
			if (m_currentPiece->checkStateBlock(x, y) && pos.y + y >= 0)
			{
				m_field->updateState(pos.x + x, pos.y + y, m_currentPiece->getCell(x, y));
			}
		}
	}
}

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
			//ピースの固定処理
			fixPiece(pos);
			return false;
		}
		break;
	}//Downブロック

	case Rotate:
	{
		turn();
		break;

	}//Rotateブロック

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


//ピースを登録する
void TetrisManager::SubmitPiece(Piece* add_piece) {
	//バックアップ用ポインターの作成
	std::shared_ptr<Piece>back_ptr(m_currentPiece.get());
	//バックアップ処理
	m_oldPieces.push_back(back_ptr);
	//新しいピースの位置を参照する
	m_currentPiece.reset(add_piece);
}

bool TetrisManager::update(Dir dir) {
	bool isSucceeded = movePiece(Dir::Down);
	if (!isSucceeded)
	{
		int line = m_field->deleteLine();
		if (line > 0)
		{
			m_currentPiece->clear();

			if (line == 4)
			{
				m_score += 1000;
			}
			else
			{
				m_score += (line * 100);
			}
			m_field->shiftLine(line);
		}
		m_deletedPieceNum;
	}
	else
	{
		movePiece(dir);
	}
	return isSucceeded;
}

void TetrisManager::resetState()
{
	m_score = 0;
	m_deletedPieceNum = 0;
}