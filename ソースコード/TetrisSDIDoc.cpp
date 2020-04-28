// TetrisSDIDoc.cpp : CTetrisSDIDoc クラスの動作の定義を行います。
//

#include "stdafx.h"
#include "TetrisSDI.h"

#include "TetrisSDIDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTetrisSDIDoc

IMPLEMENT_DYNCREATE(CTetrisSDIDoc, CDocument)

BEGIN_MESSAGE_MAP(CTetrisSDIDoc, CDocument)
	//{{AFX_MSG_MAP(CTetrisSDIDoc)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTetrisSDIDoc クラスの構築/消滅

CTetrisSDIDoc::CTetrisSDIDoc()
{
	// TODO: この位置に１度だけ呼ばれる構築用のコードを追加してください。

}

CTetrisSDIDoc::~CTetrisSDIDoc()
{
}

BOOL CTetrisSDIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: この位置に再初期化処理を追加してください。
	// (SDI ドキュメントはこのドキュメントを再利用します。)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTetrisSDIDoc シリアライゼーション

void CTetrisSDIDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: この位置に保存用のコードを追加してください。
	}
	else
	{
		// TODO: この位置に読み込み用のコードを追加してください。
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTetrisSDIDoc クラスの診断

#ifdef _DEBUG
void CTetrisSDIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTetrisSDIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTetrisSDIDoc コマンド
