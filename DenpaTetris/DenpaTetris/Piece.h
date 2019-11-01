#pragma once


/*

Tetris用クラス群（突貫作成のため可読性はご容赦）
ヘッダー実装多め

*/

//ヘッダーインクルード
#include<tchar.h>
#include<Windows.h>
#include"Resource.h"
#include<vector>
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

class Point;
class Cell;
//ピース
class Piece {
public:

	//生ポ危険
	Piece()
	{
		clear();
		initPos();

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

	//ステートチェック
	int checkStateBlock(int x, int y) 
	{
		// todo: インデックスチェック
		return cells_[x][y].getBlock();
	}

	Cell getCell(int x, int y)const
	{
		return cells_[x][y];
	}

	Point getPos() const 
	{
		return pos_;
	}

	void UpdatePosition(Point new_pos) 
	{
		m_oldPos.push_back(new_pos);
		this->pos_ = new_pos;
	}

	void updateCell(int x, int y, Cell cell)
	{
		this->cells_[x][y] = cell;
	}
private:
	Point pos_;
	std::vector<Point>m_oldPos;
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

protected:
	Cell cells_[PieceWidth][PieceHeight];
};


/*

ここから各ピース形状の定義

*/


class Piece0 :public Piece {
public:
	Piece0() :Piece() {
		//めちゃくちゃ頭良いやん（頭悪い）
		cells_[1][1].create(RGB(0x00, 0x8f, 0xff));
		cells_[2][1].create(RGB(0x00, 0x8f, 0xff));
		cells_[1][2].create(RGB(0x00, 0x8f, 0xff));
		cells_[2][2].create(RGB(0x00, 0x8f, 0xff));
	}
};

class Piece1 :public Piece {
public:
	Piece1() :Piece() {
		cells_[1][0].create(RGB(0x4f, 0xaf, 0xdf));
		cells_[1][1].create(RGB(0x4f, 0xaf, 0xdf));
		cells_[1][2].create(RGB(0x4f, 0xaf, 0xdf));
		cells_[1][3].create(RGB(0x4f, 0xaf, 0xdf));
	}
};

class Piece2 : public Piece {
public:
	Piece2()
		: Piece()
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
	Piece3()
		: Piece()
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
	Piece4()
		: Piece()
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
	Piece5()
		: Piece()
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
	Piece6()
		: Piece()
	{
		cells_[1][1].create(RGB(0xff, 0x4f, 0x4f));
		cells_[1][2].create(RGB(0xff, 0x4f, 0x4f));
		cells_[2][2].create(RGB(0xff, 0x4f, 0x4f));
		cells_[2][3].create(RGB(0xff, 0x4f, 0x4f));
	}
};



