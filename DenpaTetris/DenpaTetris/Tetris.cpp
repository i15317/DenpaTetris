#include"Field.h"
#include<tchar.h>
#include<Windows.h>
#include<random>
#include"Resource.h"
#include"DxLib.h"
#include"Scene.h"
#include"Piece.h"
#include <mmsystem.h>
#include <stdlib.h>
#include <tchar.h>
#include <ctime>
#include <process.h>
#include"TetrisManager.h"
#include"PieceMaker.h"
#include"Tetris.h"


void Tetris::Update()
{
	while (!m_keyValue.empty())
	{
		auto key = m_keyValue.front();

		switch (key)
		{
		case VK_ESCAPE:
			//�I������
			break;

		default:
			m_tetrisManager.registKeyValue(key);
		}
		//�|�b�v�͕K���Ō�
		m_keyValue.pop();
	}
}

void Tetris::Render() {
	m_tetrisManager.render();
}