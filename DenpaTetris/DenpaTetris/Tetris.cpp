#include"Field.h"
#include<tchar.h>
#include<Windows.h>
#include<random>
#include"Resource.h"
#include"DxLib.h"
#include"Piece.h"
#include <mmsystem.h>
#include <stdlib.h>
#include <tchar.h>
#include <ctime>
#include <process.h>
#include"Tetris.h"

void  Tetris::releasePiece(Piece* piece)
{
	if (piece != nullptr)
	{
		delete piece;
		piece = nullptr;
	}
}