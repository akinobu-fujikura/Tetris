// TetrisSDI.h : TETRISSDI アプリケーションのメイン ヘッダー ファイル
//

#if !defined(AFX_TETRISSDI_H__830D4D95_4BED_11D3_9DE7_00902756041C__INCLUDED_)
#define AFX_TETRISSDI_H__830D4D95_4BED_11D3_9DE7_00902756041C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CTetrisSDIApp:
// このクラスの動作の定義に関しては TetrisSDI.cpp ファイルを参照してください。
//

class CTetrisSDIApp : public CWinApp
{
public:
	CTetrisSDIApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CTetrisSDIApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション
	//{{AFX_MSG(CTetrisSDIApp)
	afx_msg void OnAppAbout();
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_TETRISSDI_H__830D4D95_4BED_11D3_9DE7_00902756041C__INCLUDED_)
