// TetrisSDIView.h : CTetrisSDIView �N���X�̐錾����уC���^�[�t�F�C�X�̒�`�����܂��B
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
protected: // �V���A���C�Y�@�\�݂̂���쐬���܂��B
	CTetrisSDIView();
	DECLARE_DYNCREATE(CTetrisSDIView)

// �A�g���r���[�g
public:
	CTetrisSDIDoc* GetDocument();

// �I�y���[�V����
public:
/* �O���t�B�b�N�֌W�̊֐��錾*/
	int		Color (char*);
	void	gFlame();
	void	gDrawStr(int,int,char*);
	void	gDrawScore(int,int,int);
	void	gEraseArea(int,int,int,int);
	void	gDrawBlock(int, int, char*);
	void	gEraseBlock(int,int);
	void	OnStart(void);
	void	OnExit(void);
	void  InitializeBitmap();//�r�b�g�}�b�v�̏�����

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CTetrisSDIView)
	public:
	virtual void OnDraw(CDC* pDC);  // ���̃r���[��`�悷��ۂɃI�[�o�[���C�h����܂��B
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CTetrisSDIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CTetrisSDIView)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CBitmap SaveBitmap;  //�E�C���h�E�̃C���[�W���L�����Ă���

};

#ifndef _DEBUG  // TetrisSDIView.cpp �t�@�C�����f�o�b�O���̎��g�p����܂��B
inline CTetrisSDIDoc* CTetrisSDIView::GetDocument()
   { return (CTetrisSDIDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_TETRISSDIVIEW_H__830D4D9D_4BED_11D3_9DE7_00902756041C__INCLUDED_)
