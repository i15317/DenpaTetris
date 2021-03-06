#pragma once

#include"DxLib.h"
#include<tchar.h>
class Title {
public:
	//コンストラクタ

	Title() { Init(); }
	~Title() { DeleteGraph(kosenHandle); }
	void Init() {
		//校章ロード
		kosenHandle = LoadGraph(L"kosen.png");
		//画像サイズの取得
		GetGraphSize(kosenHandle, &img_x, &img_y);
		//フォントデータ
		//fontHandle = CreateFontToHandle(L"HGP創英角ポップ体", 40, 3);
		fontHandle = CreateFontToHandle(L"HGP創英角ポップ体", 32, 3);
		fontHandleMini = CreateFontToHandle(L"HGP創英角ポップ体", 16, 4);

	}

	void Render() {

		DrawExtendGraph(200, 150, 200 + img_x * 0.1, 150 + img_y * 0.1, kosenHandle, FALSE);
		DrawStringToHandle(250, 50, L"テトリス", GetColor(255, 255, 255), fontHandle);
		DrawStringToHandle(185, 420, L"Press the S key!!", GetColor(255, 255, 255), fontHandle);
		DrawStringToHandle(480, 460, L"ESCAPE is Exit Key!", GetColor(255, 0, 255), fontHandleMini);

	}
private:
	int kosenHandle;
	int fontHandle;
	int fontHandleMini;
	int img_x;
	int img_y;
};