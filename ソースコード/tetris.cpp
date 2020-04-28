// TETRIS.CPP
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "tetrisSDI.h"
#include "Common.h"  //�G���[�|�C���g�@""
#define RND(r) (rand() % r)

extern Map *map;
struct PNT { int x, y; };

// �e�g���X�̃p�^�[���̃f�[�^
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
	// �e�g���X�̌`�Ə�Ԃ𗐐��Ō��肵�ău���b�N��4��new����
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
	// �e�g���X�̃u���b�N���}�b�v�Ɉ����n�� 
	for (i = 0; i < nBLOCK; i++) map->PutOn(block[i]);
}

int Tetris::Enter()
{
	// ��ʉE���̏������g���獶���̑傫���g�ֈړ�����
	// �ړ��ł���Ƃx�d�r�C�ł��Ȃ��Ƃm�n��Ԃ�
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

int Tetris::Move(int dx, int dy)		// ���݂̈ʒu����dx,dy�����ړ�����
{
	int i;
	// �u���b�N�S���ړ��ł��邩�ǂ������`�F�b�N����
	for (i = 0; i < nBLOCK; i++) if (block[i]->CanMove(dx, dy) != YES) break;	/* ������7 */
	if (i == nBLOCK) {  	/* ������8 */ // �S���ړ��ł��鎞�̏���
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
	// �u���b�N�S����]�ł��邩�ǂ������`�F�b�N����
	for (i = 0; i < nBLOCK; i++) if (block[i]->CanTurn(tx, ty) != YES) break;
	if (i != nBLOCK) {  	// �S����]�ł��鎞�̏���
		Erase();
		for (i = 0; i < nBLOCK; i++) block[i]->Turn(tx, ty);
		return YES;
	}
	else return NO;
}