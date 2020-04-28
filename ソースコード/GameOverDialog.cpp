// GameOverDialog.cpp : �C���v�������e�[�V���� �t�@�C��
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
// GameOverDialog �_�C�A���O


GameOverDialog::GameOverDialog(CWnd* pParent /*=NULL*/)
	: CDialog(GameOverDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(GameOverDialog)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_INIT
}


void GameOverDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GameOverDialog)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GameOverDialog, CDialog)
	//{{AFX_MSG_MAP(GameOverDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GameOverDialog ���b�Z�[�W �n���h��



void GameOverDialog::OnOK() //�ĊJ�{�^���������ꂽ�Ƃ� 
{
	// TODO: ���̈ʒu�ɂ��̑��̌��ؗp�̃R�[�h��ǉ����Ă�������
	graphicView->OnStart();
	CDialog::OnOK();
}

void GameOverDialog::OnCancel() //�I���{�^���������ꂽ�Ƃ�
{
	// TODO: ���̈ʒu�ɓ��ʂȌ㏈����ǉ����Ă��������B
	graphicView->OnExit();	
	CDialog::OnCancel();
}
