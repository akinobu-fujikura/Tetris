#if !defined(AFX_GAMEOVERDIALOG_H__2B727EF8_51E3_11D3_9DF9_00902756041C__INCLUDED_)
#define AFX_GAMEOVERDIALOG_H__2B727EF8_51E3_11D3_9DF9_00902756041C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GameOverDialog.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// GameOverDialog ダイアログ

class GameOverDialog : public CDialog
{
// コンストラクション
public:
	GameOverDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(GameOverDialog)
	enum { IDD = IDD_DIALOG_GAMEOVER };
		// メモ: ClassWizard はこの位置にデータ メンバを追加します。
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(GameOverDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(GameOverDialog)
	afx_msg void OnExit();
	afx_msg void OnRestart();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_GAMEOVERDIALOG_H__2B727EF8_51E3_11D3_9DF9_00902756041C__INCLUDED_)
