// TetrisSDIDoc.h : CTetrisSDIDoc クラスの宣言およびインターフェイスの定義をします。
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TETRISSDIDOC_H__830D4D9B_4BED_11D3_9DE7_00902756041C__INCLUDED_)
#define AFX_TETRISSDIDOC_H__830D4D9B_4BED_11D3_9DE7_00902756041C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTetrisSDIDoc : public CDocument
{
protected: // シリアライズ機能のみから作成します。
	CTetrisSDIDoc();
	DECLARE_DYNCREATE(CTetrisSDIDoc)

// アトリビュート
public:

// オペレーション
public:

//オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CTetrisSDIDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CTetrisSDIDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CTetrisSDIDoc)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_TETRISSDIDOC_H__830D4D9B_4BED_11D3_9DE7_00902756041C__INCLUDED_)
