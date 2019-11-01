#include"Piece.h"
#include<random>
#include"PieceMaker.h"

PieceMaker::PieceMaker() {
	//シード値初期化
	mt.seed(rnd());
}

Piece* PieceMaker::createPiece()
{
	//乱数取得
	int value = rnd() % 7;

	switch (value)
	{
	case 0:
		return new Piece0();
	case 1:
		return new Piece1();
	case 2:
		return new Piece2();
	case 3:
		return new Piece3();
	case 4:
		return new Piece4();
	case 5:
		return new Piece5();
	case 6:
		return new Piece6();
	}
	return nullptr;
}