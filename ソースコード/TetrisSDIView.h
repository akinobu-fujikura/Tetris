// TetrisSDIView.h : CTetrisSDIView クラスの宣言およびインターフェイスの定義をします。
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TETRISSDIVIEW_H__830D4D9D_4BED_11D3_9DE7_00902756041C__INCLUDED_)
#define AFX_TETRISSDIVIEW_H__830D4D9D_4BED_11D3_9DE7_00902756041C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define BMP_WIDTH  300
#define BMP_HEIGHT 500

class CTetrisSDIDoc;

class CTetrisSDIView : public CView
{
protected: // シリアライズ機能のみから作成します。
	CTetrisSDIView();
	DECLARE_DYNCREATE(CTetrisSDIView)

// アトリビュート
public:
	CTetrisSDIDoc* GetDocument();

// オペレーション
public:
/* グラフィック関係の関数宣言*/
	int		Color (char*);
	void	gFlame();
	void	gDrawStr(int,int,char*);
	void	gDrawScore(int,int,int);
	void	gEraseArea(int,int,int,int);
	void	gDrawBlock(int, int, char*);
	void	gEraseBlock(int,int);
	void	OnStart(void);
	void	OnExit(void);
	void  InitializeBitmap();//ビットマップの初期化

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CTetrisSDIView)
	public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画する際にオーバーライドされます。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CTetrisSDIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CTetrisSDIView)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CBitmap SaveBitmap;  //ウインドウのイメージを記憶しておく

};

#ifndef _DEBUG  // TetrisSDIView.cpp ファイルがデバッグ環境の時使用されます。
inline CTetrisSDIDoc* CTetrisSDIView::GetDocument()
   { return (CTetrisSDIDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_TETRISSDIVIEW_H__830D4D9D_4BED_11D3_9DE7_00902756041C__INCLUDED_)
