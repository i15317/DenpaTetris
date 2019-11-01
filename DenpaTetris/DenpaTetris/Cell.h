#pragma once


/*

1ブロックのカラーと状態を管理するクラス

*/
class Cell {
private:
	//メンバー変数
	int block_;
	int color_;
public:
	//初期化関数
	void clear() {
		block_ = 0;
		color_ = 0;
	}
	//ピース作成関数？
	void create(const int color) {
		block_ = 1;
		color_ = color;
	}
	//ゲッター
	int getBlock() const {
		return block_;
	}

	//カラーゲッター
	int getColor() const {
		return color_;
	}

};