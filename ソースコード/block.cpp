// BLOCK.CPP
#include "stdafx.h"
#include <stdio.h>
#include "TetrisSDIView.h"
#include "tetrisSDI.h"
#include "Common.h"
extern Map *map;		/* 穴埋め4 */

// ブロックの色のデータ定義
char *bColor[7] = {
	"blue", "green", "magenta", "yellow", "cyan", "red", "white"
};

Block::Block(int x, int y, int sh) // エラーポイント ::
{
	bx = x; by = y;
	shape = sh;
}

Block::~Block()
{
	Erase();
}

void Block::Erase()
{
	graphicView->gEraseBlock(bx, by);
}

// 指定した移動量(dx,dy)だけブロックを移動することができるか検査する
int Block::CanMove(int dx, int dy)		/* 穴埋め5 */
{
	// 移動後の位置が空きであるかどうかマップに問い合わせる
	if (map->IsVacant(bx+dx,by+dy) == YES) return YES;	/* 穴埋め6 */
	else return NO;
}

// 指定した位置(tx,ty)を中心にブロックを９０度反時計回りに回転することができるか検査する
int Block::CanTurn(int tx, int ty)
{
	// 移動後の位置が空きであるかどうかマップに問い合わせる
	if (map->IsVacant(tx - (by - ty), ty + (bx - tx)) == YES) return YES;//エラーポイント　,
	else return NO;
}

void Block::ReDraw()
{
	graphicView->gDrawBlock(bx, by, bColor[shape]);
}

// 指定した移動量(dx,dy)だけブロックを移動する
void Block::Move(int dx, int dy)
{
	bx += dx; by += dy;
	graphicView->gDrawBlock(bx, by, bColor[shape]);
}

// 指定した位置(tx,ty)を中心にブロックを９０度反時計回りに回転する
void Block::Turn(int tx, int ty)
{
	int oldBx = bx;
	bx = tx - (by - ty); by = ty + (oldBx - tx);
	graphicView->gDrawBlock(bx, by, bColor[shape]);
}
