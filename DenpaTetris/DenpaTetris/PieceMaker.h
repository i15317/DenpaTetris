#pragma once
#include<random>
#include<memory>
//前方宣言
class Piece;

//こ↑こ↓から追加ピース
class Piece0;
class Piece1;
class Piece2;
class Piece3;
class Piece4;
class Piece5;
class Piece6;


class PieceMaker {
public:
	PieceMaker();
	~PieceMaker();

	Piece* createPiece();

private:
	std::random_device rnd;
	std::mt19937_64 mt;
	std::uniform_int_distribution<> rand;
};