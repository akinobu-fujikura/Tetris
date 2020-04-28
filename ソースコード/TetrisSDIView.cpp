// TetrisSDIView.cpp : CTetrisSDIView クラスの動作の定義を行います。


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
};//ブロックの色をRBGで定義する

int numOfColor = 7;
int State;//ゲームの状態
int Touched;//テトリスが接地したかのフラグ
CPoint previousPoint;//マウスの前の位置を保存
int totalDelLine = 0, level = 0, score = 0;//一列そろって削除された行の数、レベル、得点
GameOverDialog *gameOverDialog;//ゲームオーバーを知らせるダイアログ

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
	// 標準印刷コマンド
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTetrisSDIView クラスの構築/消滅

CTetrisSDIView::CTetrisSDIView()
{
	// TODO: この場所に構築用のコードを追加してください。
	gameOverDialog = new GameOverDialog(this);
}

CTetrisSDIView::~CTetrisSDIView()
{
}

BOOL CTetrisSDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTetrisSDIView クラスの描画

void CTetrisSDIView::OnDraw(CDC* pDC)
{
	CTetrisSDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: この場所にネイティブ データ用の描画コードを追加します。
	CDC      MemDC;
	MemDC.CreateCompatibleDC(pDC);
	MemDC.SelectObject(&SaveBitmap);
	pDC->BitBlt(0, 0, BMP_WIDTH, BMP_HEIGHT, &MemDC, 0, 0, SRCCOPY);
}

/////////////////////////////////////////////////////////////////////////////
// CTetrisSDIView クラスの印刷

BOOL CTetrisSDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// デフォルトの印刷準備
	return DoPreparePrinting(pInfo);
}

void CTetrisSDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷前の特別な初期化処理を追加してください。
}

void CTetrisSDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷後の後処理を追加してください。
}

/////////////////////////////////////////////////////////////////////////////
// CTetrisSDIView クラスの診断

#ifdef _DEBUG
void CTetrisSDIView::AssertValid() const
{
	CView::AssertValid();
}

void CTetrisSDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTetrisSDIDoc* CTetrisSDIView::GetDocument() // 非デバッグ バージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTetrisSDIDoc)));
	return (CTetrisSDIDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTetrisSDIView クラスのメッセージ ハンドラ


void CTetrisSDIView::InitializeBitmap() {
	SaveBitmap.DeleteObject();//既にBitmapがあれば、削除する
	CDC* pDC = GetDC();
	CDC  MemDC;
	MemDC.CreateCompatibleDC(pDC);
	SaveBitmap.CreateCompatibleBitmap(pDC, BMP_WIDTH, BMP_HEIGHT);
	MemDC.SelectObject(&SaveBitmap);
	MemDC.PatBlt(0, 0, BMP_WIDTH, BMP_HEIGHT, WHITENESS);
	ReleaseDC(pDC);
}

// 色の名前から色のRGB値を返す関数
int CTetrisSDIView::Color(char *color)
{
	int i;
	for (i = 0; i < numOfColor; i++) {
		if (strcmp((char*)bColor[i], color) == 0) break;
	}
	return(rgbColor[i]);
}

// ウインドウにゲーム盤の枠を描く
void CTetrisSDIView::gFlame()
{
	CDC* pDC = GetDC();
	CDC  MemDC;
	MemDC.CreateCompatibleDC(pDC);
	MemDC.SelectObject(&SaveBitmap);
	MemDC.FillSolidRect(0, 0, blWIDTH*(XMAX + 1 + 6 + 1), blHIGHT*(YMAX + 1 + 1), GRAY);//全体
	MemDC.FillSolidRect(XLEFT, YTOP, blWIDTH*XMAX, blHIGHT*YMAX, BLACK);//マップ
	MemDC.FillSolidRect(XLEFT + blWIDTH*(XMAX + 1), YTOP + blHIGHT, blWIDTH * 6, blHIGHT * 6, BLACK);//登場エリア
	pDC->BitBlt(0, 0, BMP_WIDTH, BMP_HEIGHT, &MemDC, 0, 0, SRCCOPY);
	ReleaseDC(pDC);
	Invalidate(FALSE);
}

// 位置(x,y)に指定した色で四角を描く
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

// 位置(x,y)のブロックを消す。つまり黒で塗りつぶす。
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

// 位置(x,y)に文字(string)を書く。得点などを書く。
void CTetrisSDIView::gDrawStr(int x, int y, char *str) {
	CFont	font;
	CDC* pDC = GetDC();
	CDC  MemDC;
	int size = 10;
	MemDC.CreateCompatibleDC(pDC);
	MemDC.SelectObject(&SaveBitmap);
	font.CreateFont(size, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "ＭＳ 明朝");
	CFont* oldFont = MemDC.SelectObject(&font);
	MemDC.TextOut(XLEFT + x, YTOP + y, str);
	MemDC.SelectObject(oldFont);
	pDC->BitBlt(0, 0, BMP_WIDTH, BMP_HEIGHT, &MemDC, 0, 0, SRCCOPY);
	ReleaseDC(pDC);
	Invalidate(FALSE);
}

//得点エリアの四角を描く
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

//得点を書く
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

// スタートメニューが押されたか、ゲームオーバーダイアログで再開が選ばれたとき
void CTetrisSDIView::OnStart()
{
	InitializeBitmap();
	level = 0;
	gFlame();	// 画面を描く
	map = new Map;
	tetris = new Tetris;
	tetris->Enter();
	nextTetris = new Tetris;
	gDrawScore(totalDelLine, level, score);
	SetTimer(1, (10 - level) * 50, NULL);
	State = PLAYING;
	Touched = NO;
}

// マウスが動いたとき
void CTetrisSDIView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	if (State == PLAYING&& nFlags == MK_LBUTTON) { //ゲーム中であって、左ボタンが押されているとき（つまりドラッグ中）
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

// 指定した短い時間ごとに、このメソッドがwindowsから呼び出される。
void CTetrisSDIView::OnTimer(UINT nIDEvent)
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	if (State == PLAYING) {//ゲーム中か
		if (Touched == YES) {		// テトリスが接地した時の処理
			int delLines = 0;
			delete tetris;
			tetris = nextTetris;
			while (map->DropLine() == YES) delLines++;
			if (delLines) {
				score += (SCORE[delLines - 1] * (level + 1)); // スコアーの加算
				totalDelLine += delLines;
			}
			gDrawScore(totalDelLine, level, score);
			if ((tetris->Enter() == NO)) {	// ゲームオーバーの時
				State = IDLE;
				delete tetris;
				delete map;
				gameOverDialog->DoModal();
			}
			else {	// ゲームオーバーでない時
				nextTetris = new Tetris;
				Touched = NO;
			}
		}
		else {	// テトリスが接地していない時の処理
		 // テトリスが１つ下に移動する。移動できないときは接地状態フラグをたてる
			if (tetris->Move(DRAW) == NO) Touched = YES;
		}
	}
	CView::OnTimer(nIDEvent);
}

// 右ボタンがダブルクリックされたとき
void CTetrisSDIView::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	if (State == PLAYING) {
		while ((tetris->Move(DOWN)) == YES) score += 10;
		Touched = YES;
	}
	CView::OnRButtonDblClk(nFlags, point);
}

// 左ボタンがダブルクリックされたとき
void CTetrisSDIView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	if (State == PLAYING) {
		tetris->Turn();
	}
	CView::OnLButtonDblClk(nFlags, point);
}

//ゲームオーバーダイアログで終了が選ばれたとき
void CTetrisSDIView::OnExit()
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	exit(-1);
}

