// TetrisSDI.h : TETRISSDI �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C��
//

#if !defined(AFX_TETRISSDI_H__830D4D95_4BED_11D3_9DE7_00902756041C__INCLUDED_)
#define AFX_TETRISSDI_H__830D4D95_4BED_11D3_9DE7_00902756041C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // ���C�� �V���{��

/////////////////////////////////////////////////////////////////////////////
// CTetrisSDIApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� TetrisSDI.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CTetrisSDIApp : public CWinApp
{
public:
	CTetrisSDIApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CTetrisSDIApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
	//{{AFX_MSG(CTetrisSDIApp)
	afx_msg void OnAppAbout();
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_TETRISSDI_H__830D4D95_4BED_11D3_9DE7_00902756041C__INCLUDED_)
