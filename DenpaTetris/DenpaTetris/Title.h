#pragma once

#include"DxLib.h"
#include<tchar.h>
class Title {
public:
	//�R���X�g���N�^

	Title() { Init(); }
	~Title() { DeleteGraph(kosenHandle); }
	void Init() {
		//�Z�̓��[�h
		kosenHandle = LoadGraph(L"kosen.png");
		//�摜�T�C�Y�̎擾
		GetGraphSize(kosenHandle, &img_x, &img_y);
		//�t�H���g�f�[�^
		fontHandle = CreateFontToHandle(L"HGP�n�p�p�|�b�v��", 40, 3);
		fontHandle = CreateFontToHandle(L"HGP�n�p�p�|�b�v��", 32, 3);

	}

	void Render() {

		DrawExtendGraph(200, 150, 200 + img_x * 0.1, 150 + img_y * 0.1, kosenHandle, FALSE);

		DrawStringToHandle(250, 50, L"�e�g���X", GetColor(255, 255, 255), fontHandle);


		DrawStringToHandle(185, 420, L"Press The S Key!!", GetColor(255, 255, 255), fontHandle);

	}
private:
	int kosenHandle;
	int fontHandle;
	int img_x;
	int img_y;
};