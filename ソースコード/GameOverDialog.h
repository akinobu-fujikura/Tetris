#if !defined(AFX_GAMEOVERDIALOG_H__2B727EF8_51E3_11D3_9DF9_00902756041C__INCLUDED_)
#define AFX_GAMEOVERDIALOG_H__2B727EF8_51E3_11D3_9DF9_00902756041C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GameOverDialog.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// GameOverDialog �_�C�A���O

class GameOverDialog : public CDialog
{
// �R���X�g���N�V����
public:
	GameOverDialog(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(GameOverDialog)
	enum { IDD = IDD_DIALOG_GAMEOVER };
		// ����: ClassWizard �͂��̈ʒu�Ƀf�[�^ �����o��ǉ����܂��B
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(GameOverDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(GameOverDialog)
	afx_msg void OnExit();
	afx_msg void OnRestart();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_GAMEOVERDIALOG_H__2B727EF8_51E3_11D3_9DF9_00902756041C__INCLUDED_)
