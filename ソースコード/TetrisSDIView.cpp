// TetrisSDIView.cpp : CTetrisSDIView �N���X�̓���̒�`���s���܂��B


#include "stdafx.h"
#include "TetrisSDI.h"
#include "TetrisSDIDoc.h"
#include "TetrisSDIView.h"
#include "GameOverDialog.h"
#include "common.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Map    *map;
Tetris *tetris, *nextTetris;
int SCORE[4] = { 40,100,300,1200 };
extern char *bColor[7];
int rgbColor[7] = {
	0x00ff0000,0x0000ff00,0xff00ff,0x0000ffff,0x008f8f8f,0x000000ff,0x00ffffff
};//�u���b�N�̐F��RBG�Œ�`����

int numOfColor = 7;
int State;//�Q�[���̏��
int Touched;//�e�g���X���ڒn�������̃t���O
CPoint previousPoint;//�}�E�X�̑O�̈ʒu��ۑ�
int totalDelLine = 0, level = 0, score = 0;//��񂻂���č폜���ꂽ�s�̐��A���x���A���_
GameOverDialog *gameOverDialog;//�Q�[���I�[�o�[��m�点��_�C�A���O

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTetrisSDIView

IMPLEMENT_DYNCREATE(CTetrisSDIView, CView)

BEGIN_MESSAGE_MAP(CTetrisSDIView, CView)
	//{{AFX_MSG_MAP(CTetrisSDIView)
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(START, OnStart)
	//}}AFX_MSG_MAP
	// �W������R�}���h
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTetrisSDIView �N���X�̍\�z/����

CTetrisSDIView::CTetrisSDIView()
{
	// TODO: ���̏ꏊ�ɍ\�z�p�̃R�[�h��ǉ����Ă��������B
	gameOverDialog = new GameOverDialog(this);
}

CTetrisSDIView::~CTetrisSDIView()
{
}

BOOL CTetrisSDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C������ Window �N���X�܂��̓X�^�C����
	//  �C�����Ă��������B
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTetrisSDIView �N���X�̕`��

void CTetrisSDIView::OnDraw(CDC* pDC)
{
	CTetrisSDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: ���̏ꏊ�Ƀl�C�e�B�u �f�[�^�p�̕`��R�[�h��ǉ����܂��B
	CDC      MemDC;
	MemDC.CreateCompatibleDC(pDC);
	MemDC.SelectObject(&SaveBitmap);
	pDC->BitBlt(0, 0, BMP_WIDTH, BMP_HEIGHT, &MemDC, 0, 0, SRCCOPY);
}

/////////////////////////////////////////////////////////////////////////////
// CTetrisSDIView �N���X�̈��

BOOL CTetrisSDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �f�t�H���g�̈������
	return DoPreparePrinting(pInfo);
}

void CTetrisSDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ����O�̓��ʂȏ�����������ǉ����Ă��������B
}

void CTetrisSDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �����̌㏈����ǉ����Ă��������B
}

/////////////////////////////////////////////////////////////////////////////
// CTetrisSDIView �N���X�̐f�f

#ifdef _DEBUG
void CTetrisSDIView::AssertValid() const
{
	CView::AssertValid();
}

void CTetrisSDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTetrisSDIDoc* CTetrisSDIView::GetDocument() // ��f�o�b�O �o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTetrisSDIDoc)));
	return (CTetrisSDIDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTetrisSDIView �N���X�̃��b�Z�[�W �n���h��


void CTetrisSDIView::InitializeBitmap() {
	SaveBitmap.DeleteObject();//����Bitmap������΁A�폜����
	CDC* pDC = GetDC();
	CDC  MemDC;
	MemDC.CreateCompatibleDC(pDC);
	SaveBitmap.CreateCompatibleBitmap(pDC, BMP_WIDTH, BMP_HEIGHT);
	MemDC.SelectObject(&SaveBitmap);
	MemDC.PatBlt(0, 0, BMP_WIDTH, BMP_HEIGHT, WHITENESS);
	ReleaseDC(pDC);
}

// �F�̖��O����F��RGB�l��Ԃ��֐�
int CTetrisSDIView::Color(char *color)
{
	int i;
	for (i = 0; i < numOfColor; i++) {
		if (strcmp((char*)bColor[i], color) == 0) break;
	}
	return(rgbColor[i]);
}

// �E�C���h�E�ɃQ�[���Ղ̘g��`��
void CTetrisSDIView::gFlame()
{
	CDC* pDC = GetDC();
	CDC  MemDC;
	MemDC.CreateCompatibleDC(pDC);
	MemDC.SelectObject(&SaveBitmap);
	MemDC.FillSolidRect(0, 0, blWIDTH*(XMAX + 1 + 6 + 1), blHIGHT*(YMAX + 1 + 1), GRAY);//�S��
	MemDC.FillSolidRect(XLEFT, YTOP, blWIDTH*XMAX, blHIGHT*YMAX, BLACK);//�}�b�v
	MemDC.FillSolidRect(XLEFT + blWIDTH*(XMAX + 1), YTOP + blHIGHT, blWIDTH * 6, blHIGHT * 6, BLACK);//�o��G���A
	pDC->BitBlt(0, 0, BMP_WIDTH, BMP_HEIGHT, &MemDC, 0, 0, SRCCOPY);
	ReleaseDC(pDC);
	Invalidate(FALSE);
}

// �ʒu(x,y)�Ɏw�肵���F�Ŏl�p��`��
void CTetrisSDIView::gDrawBlock(int x, int y, char *color)
{
	CDC* pDC = GetDC();
	CDC  MemDC;
	MemDC.CreateCompatibleDC(pDC);
	MemDC.SelectObject(&SaveBitmap);
	MemDC.FillSolidRect(XLEFT + x*blWIDTH, YTOP + y*blHIGHT, blWIDTH - 2, blHIGHT - 2, Color(color));
	MemDC.BitBlt(0, 0, BMP_WIDTH, BMP_HEIGHT, &MemDC, 0, 0, SRCCOPY);
	pDC->BitBlt(0, 0, BMP_WIDTH, BMP_HEIGHT, &MemDC, 0, 0, SRCCOPY);
	ReleaseDC(pDC);
	Invalidate(FALSE);
}

// �ʒu(x,y)�̃u���b�N�������B�܂荕�œh��Ԃ��B
void CTetrisSDIView::gEraseBlock(int x, int y)
{
	CDC* pDC = GetDC();
	CDC  MemDC;
	MemDC.CreateCompatibleDC(pDC);
	MemDC.SelectObject(&SaveBitmap);
	MemDC.FillSolidRect(XLEFT + x*blWIDTH, YTOP + y*blHIGHT, blWIDTH - 2, blHIGHT - 2, BLACK);
	MemDC.BitBlt(0, 0, BMP_WIDTH, BMP_HEIGHT, &MemDC, 0, 0, SRCCOPY);
	pDC->BitBlt(0, 0, BMP_WIDTH, BMP_HEIGHT, &MemDC, 0, 0, SRCCOPY);
	ReleaseDC(pDC);
	Invalidate(FALSE);
}

// �ʒu(x,y)�ɕ���(string)�������B���_�Ȃǂ������B
void CTetrisSDIView::gDrawStr(int x, int y, char *str) {
	CFont	font;
	CDC* pDC = GetDC();
	CDC  MemDC;
	int size = 10;
	MemDC.CreateCompatibleDC(pDC);
	MemDC.SelectObject(&SaveBitmap);
	font.CreateFont(size, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "�l�r ����");
	CFont* oldFont = MemDC.SelectObject(&font);
	MemDC.TextOut(XLEFT + x, YTOP + y, str);
	MemDC.SelectObject(oldFont);
	pDC->BitBlt(0, 0, BMP_WIDTH, BMP_HEIGHT, &MemDC, 0, 0, SRCCOPY);
	ReleaseDC(pDC);
	Invalidate(FALSE);
}

//���_�G���A�̎l�p��`��
void CTetrisSDIView::gEraseArea(int x, int y, int width, int hight)
{
	CDC* pDC = GetDC();
	CDC  MemDC;
	MemDC.CreateCompatibleDC(pDC);
	MemDC.SelectObject(&SaveBitmap);
	MemDC.FillSolidRect(x, y, width, hight, Color("white"));
	MemDC.BitBlt(0, 0, BMP_WIDTH, BMP_HEIGHT, &MemDC, 0, 0, SRCCOPY);
	pDC->BitBlt(0, 0, BMP_WIDTH, BMP_HEIGHT, &MemDC, 0, 0, SRCCOPY);
	ReleaseDC(pDC);
	Invalidate(FALSE);
}

//���_������
void CTetrisSDIView::gDrawScore(int line, int level, int score)
{
	int r;
	char string[20];
	gEraseArea(XLEFT + blWIDTH*(XMAX + 1), blHIGHT * 16 - 6, blWIDTH * 6, 150);
	r = sprintf(string, "Line : %7d", line);
	gDrawStr(XLEFT + blWIDTH*(XMAX + 1), blHIGHT * 19, string);
	r = sprintf(string, "Level: %7d", level);
	gDrawStr(XLEFT + blWIDTH*(XMAX + 1), blHIGHT * 21, string);
	r = sprintf(string, "Score: %7d", score);
	gDrawStr(XLEFT + blWIDTH*(XMAX + 1), blHIGHT * 23, string);
}

// �X�^�[�g���j���[�������ꂽ���A�Q�[���I�[�o�[�_�C�A���O�ōĊJ���I�΂ꂽ�Ƃ�
void CTetrisSDIView::OnStart()
{
	InitializeBitmap();
	level = 0;
	gFlame();	// ��ʂ�`��
	map = new Map;
	tetris = new Tetris;
	tetris->Enter();
	nextTetris = new Tetris;
	gDrawScore(totalDelLine, level, score);
	SetTimer(1, (10 - level) * 50, NULL);
	State = PLAYING;
	Touched = NO;
}

// �}�E�X���������Ƃ�
void CTetrisSDIView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����邩�܂��̓f�t�H���g�̏������Ăяo���Ă�������
	if (State == PLAYING&& nFlags == MK_LBUTTON) { //�Q�[�����ł����āA���{�^����������Ă���Ƃ��i�܂�h���b�O���j
		if (point.x > previousPoint.x) {
			tetris->Move(LEFT);
		}
		if (point.x < previousPoint.x) {
			tetris->Move(RIGHT);
		}
		previousPoint = point;
	}
	CView::OnMouseMove(nFlags, point);
}

// �w�肵���Z�����Ԃ��ƂɁA���̃��\�b�h��windows����Ăяo�����B
void CTetrisSDIView::OnTimer(UINT nIDEvent)
{
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����邩�܂��̓f�t�H���g�̏������Ăяo���Ă�������
	if (State == PLAYING) {//�Q�[������
		if (Touched == YES) {		// �e�g���X���ڒn�������̏���
			int delLines = 0;
			delete tetris;
			tetris = nextTetris;
			while (map->DropLine() == YES) delLines++;
			if (delLines) {
				score += (SCORE[delLines - 1] * (level + 1)); // �X�R�A�[�̉��Z
				totalDelLine += delLines;
			}
			gDrawScore(totalDelLine, level, score);
			if ((tetris->Enter() == NO)) {	// �Q�[���I�[�o�[�̎�
				State = IDLE;
				delete tetris;
				delete map;
				gameOverDialog->DoModal();
			}
			else {	// �Q�[���I�[�o�[�łȂ���
				nextTetris = new Tetris;
				Touched = NO;
			}
		}
		else {	// �e�g���X���ڒn���Ă��Ȃ����̏���
		 // �e�g���X���P���Ɉړ�����B�ړ��ł��Ȃ��Ƃ��͐ڒn��ԃt���O�����Ă�
			if (tetris->Move(DRAW) == NO) Touched = YES;
		}
	}
	CView::OnTimer(nIDEvent);
}

// �E�{�^�����_�u���N���b�N���ꂽ�Ƃ�
void CTetrisSDIView::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����邩�܂��̓f�t�H���g�̏������Ăяo���Ă�������
	if (State == PLAYING) {
		while ((tetris->Move(DOWN)) == YES) score += 10;
		Touched = YES;
	}
	CView::OnRButtonDblClk(nFlags, point);
}

// ���{�^�����_�u���N���b�N���ꂽ�Ƃ�
void CTetrisSDIView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����邩�܂��̓f�t�H���g�̏������Ăяo���Ă�������
	if (State == PLAYING) {
		tetris->Turn();
	}
	CView::OnLButtonDblClk(nFlags, point);
}

//�Q�[���I�[�o�[�_�C�A���O�ŏI�����I�΂ꂽ�Ƃ�
void CTetrisSDIView::OnExit()
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	exit(-1);
}

