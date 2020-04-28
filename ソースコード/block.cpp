// BLOCK.CPP
#include "stdafx.h"
#include <stdio.h>
#include "TetrisSDIView.h"
#include "tetrisSDI.h"
#include "Common.h"
extern Map *map;		/* ������4 */

// �u���b�N�̐F�̃f�[�^��`
char *bColor[7] = {
	"blue", "green", "magenta", "yellow", "cyan", "red", "white"
};

Block::Block(int x, int y, int sh) // �G���[�|�C���g ::
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

// �w�肵���ړ���(dx,dy)�����u���b�N���ړ����邱�Ƃ��ł��邩��������
int Block::CanMove(int dx, int dy)		/* ������5 */
{
	// �ړ���̈ʒu���󂫂ł��邩�ǂ����}�b�v�ɖ₢���킹��
	if (map->IsVacant(bx+dx,by+dy) == YES) return YES;	/* ������6 */
	else return NO;
}

// �w�肵���ʒu(tx,ty)�𒆐S�Ƀu���b�N���X�O�x�����v���ɉ�]���邱�Ƃ��ł��邩��������
int Block::CanTurn(int tx, int ty)
{
	// �ړ���̈ʒu���󂫂ł��邩�ǂ����}�b�v�ɖ₢���킹��
	if (map->IsVacant(tx - (by - ty), ty + (bx - tx)) == YES) return YES;//�G���[�|�C���g�@,
	else return NO;
}

void Block::ReDraw()
{
	graphicView->gDrawBlock(bx, by, bColor[shape]);
}

// �w�肵���ړ���(dx,dy)�����u���b�N���ړ�����
void Block::Move(int dx, int dy)
{
	bx += dx; by += dy;
	graphicView->gDrawBlock(bx, by, bColor[shape]);
}

// �w�肵���ʒu(tx,ty)�𒆐S�Ƀu���b�N���X�O�x�����v���ɉ�]����
void Block::Turn(int tx, int ty)
{
	int oldBx = bx;
	bx = tx - (by - ty); by = ty + (oldBx - tx);
	graphicView->gDrawBlock(bx, by, bColor[shape]);
}
