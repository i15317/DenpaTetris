#include"Field.h"
#include"Piece.h"
#include"Point.h"
#include"Cell.h"
#include"TetrisManager.h"

bool TetrisManager::movePiece(Dir dir) {
	auto pos_ = m_currentPiece->getPos();
	switch (dir) {
	case Left:
		//Left�u���b�N
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
	}//Left�u���b�N�I�[
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
	}//Right�u���b�N
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
	}//Down�u���b�N
	}//Switch�u���b�N
	return true;
}//�֐��I�[

//�E�ɃN���N��
bool TetrisManager::turn()
{
	Cell cells[PieceWidth][PieceHeight];

	//�E��]
	for (int y = 0; y < PieceHeight; y++) {
		for (int x = 0; x < PieceWidth; x++) {
			//��Ɨp�R�s�s�s�s�s�s�s�B�B�B�B�B
			/*
			-pi/2�̉�]�s����������
			x' = -y , y' = x
			�ƂȂ邱�Ƃ�������
			*/
			//��]�ϊ�
			cells[PieceHeight - y - 1][x] = m_currentPiece->getCell[x][y];
		}
	}

	//���̈ړ��Ɍ����������邩�ǂ���
	if (isMovable(m_currentPiece->getPos(), cells))
	{
		for (int y = 0; y < PieceHeight; y++) {
			for (int x = 0; x < PieceWidth; x++) {
				//���ҁ[
				m_currentPiece->updateCell(x, y, cells[x][y]);
			}
		}
	}
	else {
		return false;
	}

	return true;
}//���������܂�

void TetrisManager::SubmitPiece(Piece* add_piece) {
	//�o�b�N�A�b�v�p�|�C���^�[�̍쐬
	std::shared_ptr<Piece>back_ptr(m_currentPiece.get());
	//�o�b�N�A�b�v����
	m_oldPieces.push_back(back_ptr);
	//�V�����s�[�X�̈ʒu���Q�Ƃ���
	m_currentPiece.reset(add_piece);
}