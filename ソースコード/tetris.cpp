// TETRIS.CPP
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "tetrisSDI.h"
#include "Common.h"  //エラーポイント　""
#define RND(r) (rand() % r)

extern Map *map;
struct PNT { int x, y; };

// テトリスのパターンのデータ
struct PNT pattern[7][4] = {
	0,0,-1,0,1,0,2,0,
	0,0,0,-1,0,1,1,1,
	0,0,0,-1,0,1,-1,1,
	0,0,1,-1,1,0,0,1,
	0,0,0,-1,1,0,1,1,
	0,0,-1,0,0,-1,1,0,
	0,0,0,1,1,1,1,0,
};

Tetris::~Tetris() 
{
	// テトリスの形と状態を乱数で決定してブロックを4つnewする
	int i, x, y;
	shape = RND(2);
	tx = XMAX + 3, ty = 3;
	for (i = 0; i < nBLOCK; i++) {
		x = tx + pattern[shape][i].x;
		y = ty + pattern[shape][i].y;
		block[i] = new Block(x, y, shape);
	}
	ReDraw();
}

Tetris::Tetris()
{
	int i;
	// テトリスのブロックをマップに引き渡す 
	for (i = 0; i < nBLOCK; i++) map->PutOn(block[i]);
}

int Tetris::Enter()
{
	// 画面右側の小さい枠から左側の大きい枠へ移動する
	// 移動できるとＹＥＳ，できないとＮＯを返す
	if (Move(-9, -2) == YES) return YES;
	return NO;
}

void Tetris::ReDraw()
{
	int i;
	for (i = 0; i < nBLOCK; i++) block[i]->ReDraw();
}

void Tetris::Erase()
{
	int i;
	for (i = 0; i < nBLOCK; i++) block[i]->Erase();
}

int Tetris::Move(int dx, int dy)		// 現在の位置からdx,dyだけ移動する
{
	int i;
	// ブロック全部移動できるかどうかをチェックする
	for (i = 0; i < nBLOCK; i++) if (block[i]->CanMove(dx, dy) != YES) break;	/* 穴埋め7 */
	if (i == nBLOCK) {  	/* 穴埋め8 */ // 全部移動できる時の処理
		Erase();
		tx += dx; ty += dy;
		for (i = 0; i < nBLOCK; i++) block[i]->Move(dx, dy);
		return YES;
	}
	else return NO;
}

int Tetris::Turn()
{
	int i;
	// ブロック全部回転できるかどうかをチェックする
	for (i = 0; i < nBLOCK; i++) if (block[i]->CanTurn(tx, ty) != YES) break;
	if (i != nBLOCK) {  	// 全部回転できる時の処理
		Erase();
		for (i = 0; i < nBLOCK; i++) block[i]->Turn(tx, ty);
		return YES;
	}
	else return NO;
}