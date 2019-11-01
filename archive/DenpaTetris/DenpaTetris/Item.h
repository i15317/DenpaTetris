#pragma once


/*

Tetris用クラス群（突貫作成のため可読性はご容赦）
ヘッダー実装多め

*/

//ヘッダーインクルード
#include<tchar.h>
#include<Windows.h>
#include"Resource.h"

/*

デバック用関数

*/


#define _DEBUG
#ifdef _DEBUG
#   define MyOutputDebugString( str, ... ) \
      { \
        TCHAR c[256]; \
        _stprintf( c, _T(str), __VA_ARGS__ ); \
        OutputDebugString( c ); \
      }
#else
#    define MyOutputDebugString( str, ... ) 
#endif

/*

本体実装

*/

//座標クラス
class Point {
public:
	int x;
	int y;
};

//ピースクラス
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

//フィールドクラス
class Field {
public:
	//コンストラクタ
	Field() {
		//初期化用関数
		this->clear();
	}
	//初期化関数
	void clear() {
		for (int y = 0; y < FieldHeight; y++)
			for (int x = 0; x < FieldWidth; x++) {
				//各ブロックを初期化する
				cells_[x][y].clear();
			}
	}



	//削除関数
	int deleteLine() {
		int delCount = 0;
		//最下部以外の横ラインが全てブロックオブジェクトか検索します
		int xNumPerLine = 0;
		for (int y = FieldHeight - 1; y >= 0; y--) {
			xNumPerLine = 0;
			for (int x = 0; x < FieldWidth; x++) {
				if (cells_[x][y].getBlock()) {
					xNumPerLine++;
				}
			}
			//横サイズと一緒で無ければ飛ばす
			if (xNumPerLine != FieldWidth) {
				continue;
			}
			//削除数をインクリメント
			delCount++;
			//削除処理
			for (int x = 0; x < FieldWidth; x++) {
				cells_[x][y].clear();
			}
		}
		//削除した数を返す
		return delCount;
	}

	void fixPiece(const Point pos, const Cell cells[][PieceHeight])
	{
		for (int y = 0; y < PieceHeight; y++)
		{
			for (int x = 0; x < PieceWidth; x++)
			{
				MyOutputDebugString("%d\n", cells[x][y].getBlock());
				MyOutputDebugString("%d\n", pos.y);

				if (cells[x][y].getBlock() && pos.y + y >= 0)
				{
					cells_[pos.x + x][pos.y + y] = cells[x][y];
				}
			}
		}
	}

	//削除した分を動かす
	/*

	この関数頭悪い

	*/
	void shiftLine(int delCount) {

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
						//ｙ方向にシフト
						cells_[tx][ty] = cells_[tx][ty - 1];
					}
					//0行より上になる場合
					else {
						cells_[tx][0].clear();
					}
				}
			}
			//一行詰める
			delCount--;
		}
	}

	//詰んだかどうか調べる
	bool isStacked()const {
		/*

		こ↑こ↓の決め打ち怪しい

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

private:
	//ブロック配列
	Cell cells_[FieldWidth][FieldHeight];
};

//ピース
class Piece {
public:
	//移動方向
	enum Dir {
		Left,
		Right,
		Down,
	};
	//生ポ危険
	Piece(Field* field) {
		clear();
		initPos();
		field_ = field;
	}
	virtual ~Piece() {}

	void clear() {
		for (int y = 0; y < PieceHeight; y++) {
			for (int x = 0; x < PieceWidth; x++) {
				cells_[x][y].clear();
			}
		}
	}

public:
	bool move(Dir dir) {

		switch (dir) {
		case Left:
			//Leftブロック
		{
			Point pos = { pos_.x - 1,pos_.y };
			if (isMovable(pos, cells_)) {
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
			if (isMovable(pos, cells_)) {
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
			if (isMovable(pos, cells_)) {
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
	bool turn() {
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
				cells[PieceHeight - y - 1][x] = cells_[x][y];
			}
		}

		//この移動に現実性があるかどうか
		if (isMovable(pos_, cells))
		{
			for (int y = 0; y < PieceHeight; y++) {
				for (int x = 0; x < PieceWidth; x++) {
					//こぴー
					cells_[x][y] = cells[x][y];
				}
			}
		}
		else {
			return false;
		}

		return true;
	}//こ↑こ↓まで

	Cell getCell(int x, int y)const {
		return cells_[x][y];
	}

	Point getPos() const {
		return pos_;
	}

private:
	Point pos_;
	Field* field_;
	Point pixel_;

	/*
	この決め打ち危ない
	*/

	void initPos() {
		pos_.x = 5;
		pos_.y = -3;
		pixel_.x = pos_.x * SizeCellPixelX;
		pixel_.y = pos_.y * SizeCellPixelY;
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
						|| (validPos && field_->getCell(ofsX, ofsY).getBlock()))
					{
						return false;
					}
				}
			}
		}
		return true;
	}

protected:
	Cell cells_[PieceWidth][PieceHeight];
};


/*

ここから各ピース形状の定義

*/


class Piece0 :public Piece {
public:
	Piece0(Field* field) :Piece(field) {
		//めちゃくちゃ頭良いやん（頭悪い）
		cells_[1][1].create(RGB(0x00, 0x8f, 0xff));
		cells_[2][1].create(RGB(0x00, 0x8f, 0xff));
		cells_[1][2].create(RGB(0x00, 0x8f, 0xff));
		cells_[2][2].create(RGB(0x00, 0x8f, 0xff));
	}
};

class Piece1 :public Piece {
public:
	Piece1(Field* field) :Piece(field) {
		cells_[1][0].create(RGB(0x4f, 0xaf, 0xdf));
		cells_[1][1].create(RGB(0x4f, 0xaf, 0xdf));
		cells_[1][2].create(RGB(0x4f, 0xaf, 0xdf));
		cells_[1][3].create(RGB(0x4f, 0xaf, 0xdf));
	}
};

class Piece2 : public Piece {
public:
	Piece2(Field* field)
		: Piece(field)
	{
		cells_[1][1].create(RGB(0x00, 0xff, 0x8f));
		cells_[1][2].create(RGB(0x00, 0xff, 0x8f));
		cells_[2][2].create(RGB(0x00, 0xff, 0x8f));
		cells_[1][3].create(RGB(0x00, 0xff, 0x8f));
	}
};

class Piece3 : public Piece
{
public:
	Piece3(Field* field)
		: Piece(field)
	{
		cells_[1][1].create(RGB(0x00, 0xdf, 0xaf));
		cells_[2][1].create(RGB(0x00, 0xdf, 0xaf));
		cells_[1][2].create(RGB(0x00, 0xdf, 0xaf));
		cells_[1][3].create(RGB(0x00, 0xdf, 0xaf));
	}
};
class Piece4 : public Piece
{
public:
	Piece4(Field* field)
		: Piece(field)
	{
		cells_[1][1].create(RGB(0xff, 0x00, 0x8f));
		cells_[2][1].create(RGB(0xff, 0x00, 0x8f));
		cells_[2][2].create(RGB(0xff, 0x00, 0x8f));
		cells_[2][3].create(RGB(0xff, 0x00, 0x8f));
	}
};

class Piece5 : public Piece
{
public:
	Piece5(Field* field)
		: Piece(field)
	{
		cells_[2][1].create(RGB(0xdf, 0x00, 0xaf));
		cells_[1][2].create(RGB(0xdf, 0x00, 0xaf));
		cells_[2][2].create(RGB(0xdf, 0x00, 0xaf));
		cells_[1][3].create(RGB(0xdf, 0x00, 0xaf));
	}
};

class Piece6 : public Piece
{
public:
	Piece6(Field* field)
		: Piece(field)
	{
		cells_[1][1].create(RGB(0xff, 0x4f, 0x4f));
		cells_[1][2].create(RGB(0xff, 0x4f, 0x4f));
		cells_[2][2].create(RGB(0xff, 0x4f, 0x4f));
		cells_[2][3].create(RGB(0xff, 0x4f, 0x4f));
	}
};


/*

ここからシステムクラス

*/


