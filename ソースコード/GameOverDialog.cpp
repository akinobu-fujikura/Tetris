// GameOverDialog.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "TetrisSDI.h"
#include "GameOverDialog.h"
#include "TetrisSDIView.h"
#include "common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GameOverDialog ダイアログ


GameOverDialog::GameOverDialog(CWnd* pParent /*=NULL*/)
	: CDialog(GameOverDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(GameOverDialog)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}


void GameOverDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GameOverDialog)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GameOverDialog, CDialog)
	//{{AFX_MSG_MAP(GameOverDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GameOverDialog メッセージ ハンドラ



void GameOverDialog::OnOK() //再開ボタンが押されたとき 
{
	// TODO: この位置にその他の検証用のコードを追加してください
	graphicView->OnStart();
	CDialog::OnOK();
}

void GameOverDialog::OnCancel() //終了ボタンが押されたとき
{
	// TODO: この位置に特別な後処理を追加してください。
	graphicView->OnExit();	
	CDialog::OnCancel();
}
