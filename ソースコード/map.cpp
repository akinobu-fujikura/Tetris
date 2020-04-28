// MAP.CPP
#include "stdafx.h"
#include <stdio.h>
#include "tetrisSDI.h"
#include "Common.h"

// �u���b�N���Ȃ���Ԃ�\��
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

// �}�b�v��Ƀu���b�N���Ȃ���΂x�d�r�A����΂m�n��Ԃ�
// �u���b�N���ʒu(x,y)�Ɉړ��ł��邩���`�F�b�N���鎞�ɗp����
int Map::IsVacant(int x, int y)		/* ������9, ������10 */
{
	if (x > XMAX - 1) return  NO;
	if (x < 0)      return  NO;
	if (y > YMAX - 1) return  NO;
	if (y < 0)      return  NO;
	if (map[x][y] == EMPTY) return YES;
	return NO;
}

// �u���b�N���}�b�v�̃����o�ɉ�����
int Map::PutOn(Block *blk)
{
	int x = blk->GetX(), y = blk->GetY();
	if (map[x][y] == EMPTY) {		/* ������11 */
		map[x][y] = blk;
		lineCount[y]++;	// ���̍s�ɂ���u���b�N�����������
		return YES;
	}
	return NO;
}

// �}�b�v��ɂ���u���b�N���ēx�`��
void Map::ReDraw()
{
	int x, y;
	for (y = 0; y < YMAX; y++)
		for (x = 0; x < XMAX; x++)
			if (map[x][y] != EMPTY) map[x][y]->ReDraw();	/* ������12, ������13 */
}

// ���C���𗎂�
int Map::DropLine()
{
	int x, y, startY;
	for (y = YMAX - 1; y >= 0; y--) if (lineCount[y] == XMAX) break;	// �S���������sy��T��
	if (y == -1) return(NO);
	//���̍s��startY�Ƃ��āA���̍s�̃u���b�N�������B
	startY = y; lineCount[startY] = 0;
	for (x = 0; x < XMAX; x++) {
		delete(map[x][startY]); // breakpoint
		map[x][startY] = EMPTY;
	}
	//startY����̍s���P�s���ɂ��炷�B	
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