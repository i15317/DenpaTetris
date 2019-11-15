#pragma once
/*

Tetris用クラス群（突貫作成のため可読性はご容赦）

*/

//ヘッダーインクルード
#include<tchar.h>
#include<Windows.h>
#include<random>
#include"Resource.h"
#include"DxLib.h"
#include <mmsystem.h>
#include <stdlib.h>
#include <tchar.h>
#include <ctime>
#include <process.h>


/*

Tetrisのゲーム全体を管理するクラス
テトリスの処理の進行はManagerに任せる

*/

//前方宣言
class Field;
class Piece;
class TetrisManager;
class PieceMaker;

class Tetris {
public:
	//コンストラクタ実装
	explicit Tetris() :
		field_(nullptr),playTime_(0), isGameover(false)
	{

		field_ = new Field();

		m_tetrisManager = TetrisManager(field_);

	}

	//デストラクタ実装
	~Tetris()
	{
		delete field_;
	}
	void Update()
	{
		//ゲームのステータス更新
		if (!m_tetrisManager.update())
		{

			if (field_->isStacked())
			{
				isGameover = true;
				//		SendMessage(nullptr, WM_RESTART, 0, 0);
			}

			//新しいピースの生成
			auto new_piece = m_pieceMaker.createPiece();

			//ピースの更新処理
			m_tetrisManager.SubmitPiece(new_piece);
		}
	}

	void Render();

private:


private:
	Field* field_;
	TetrisManager m_tetrisManager;
	PieceMaker m_pieceMaker;

	int       playTime_;
	bool	isGameover;
};

