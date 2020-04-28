// MAP.CPP
#include "stdafx.h"
#include <stdio.h>
#include "tetrisSDI.h"
#include "Common.h"

// ブロックがない状態を表す
Block *EMPTY = new Block(-1, -1, 0);

Map::Map()
{
	int x, y;
	for (y = 0; y < YMAX; y++) {
		lineCount[y] = 0;
		for (x = 0; x < XMAX; x++) {
			map[x][y] = EMPTY;
		}
	}
}

// マップ上にブロックがなければＹＥＳ、あればＮＯを返す
// ブロックが位置(x,y)に移動できるかをチェックする時に用いる
int Map::IsVacant(int x, int y)		/* 穴埋め9, 穴埋め10 */
{
	if (x > XMAX - 1) return  NO;
	if (x < 0)      return  NO;
	if (y > YMAX - 1) return  NO;
	if (y < 0)      return  NO;
	if (map[x][y] == EMPTY) return YES;
	return NO;
}

// ブロックをマップのメンバに加える
int Map::PutOn(Block *blk)
{
	int x = blk->GetX(), y = blk->GetY();
	if (map[x][y] == EMPTY) {		/* 穴埋め11 */
		map[x][y] = blk;
		lineCount[y]++;	// その行にあるブロック数が一つ増える
		return YES;
	}
	return NO;
}

// マップ上にあるブロックを再度描く
void Map::ReDraw()
{
	int x, y;
	for (y = 0; y < YMAX; y++)
		for (x = 0; x < XMAX; x++)
			if (map[x][y] != EMPTY) map[x][y]->ReDraw();	/* 穴埋め12, 穴埋め13 */
}

// ラインを落す
int Map::DropLine()
{
	int x, y, startY;
	for (y = YMAX - 1; y >= 0; y--) if (lineCount[y] == XMAX) break;	// 全部揃った行yを探す
	if (y == -1) return(NO);
	//この行をstartYとして、この行のブロックを消す。
	startY = y; lineCount[startY] = 0;
	for (x = 0; x < XMAX; x++) {
		delete(map[x][startY]); // breakpoint
		map[x][startY] = EMPTY;
	}
	//startYより上の行を１行下にずらす。	
	for (y = startY - 1; y > 0; y--)
		for (x = 0; x < XMAX; x++)
			if (map[x][y] != EMPTY) {
				map[x][y]->Erase();
				map[x][y]->Move(0, 1);
				map[x][y + 1] = map[x][y]; lineCount[y + 1]++;
				map[x][y] = EMPTY; lineCount[y]--;
			}
	return(YES);
}