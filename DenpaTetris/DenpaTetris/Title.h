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
		fontHandle = CreateFontToHandle(L"HGP創英角ポップ体", 40, 3);
		fontHandle = CreateFontToHandle(L"HGP創英角ポップ体", 32, 3);

	}

	void Render() {

		DrawExtendGraph(200, 150, 200 + img_x * 0.1, 150 + img_y * 0.1, kosenHandle, FALSE);

		DrawStringToHandle(250, 50, L"テトリス", GetColor(255, 255, 255), fontHandle);


		DrawStringToHandle(185, 420, L"Press The S Key!!", GetColor(255, 255, 255), fontHandle);

	}
private:
	int kosenHandle;
	int fontHandle;
	int img_x;
	int img_y;
};