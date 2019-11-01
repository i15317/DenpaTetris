#pragma once


/*

1�u���b�N�̃J���[�Ə�Ԃ��Ǘ�����N���X

*/
class Cell {
private:
	//�����o�[�ϐ�
	int block_;
	int color_;
public:
	//�������֐�
	void clear() {
		block_ = 0;
		color_ = 0;
	}
	//�s�[�X�쐬�֐��H
	void create(const int color) {
		block_ = 1;
		color_ = color;
	}
	//�Q�b�^�[
	int getBlock() const {
		return block_;
	}

	//�J���[�Q�b�^�[
	int getColor() const {
		return color_;
	}

};