#include"Point.h"
#include"Cell.h"
#include"Field.h"

//コンストラクタ実装

Field::Field() {
	//初期化用関数
	this->clear();
}

//初期化関数
void Field::clear() {
	for (int y = 0; y < FieldHeight; y++)
		for (int x = 0; x < FieldWidth; x++) {
			//各ブロックを初期化する
			cells_[x][y].clear();
		}
}

//削除関数
int Field::deleteLine() {
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

void Field::fixPiece(const Point pos, const Cell cells[][PieceHeight])
{
	for (int y = 0; y < PieceHeight; y++)
	{
		for (int x = 0; x < PieceWidth; x++)
		{

			if (cells[x][y].getBlock() && pos.y + y >= 0)
			{
				cells_[pos.x + x][pos.y + y] = cells[x][y];
			}
		}
	}
}

/*

この関数頭悪い

*/
void Field::shiftLine(int delCount)
{

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

