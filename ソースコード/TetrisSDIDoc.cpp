// TetrisSDIDoc.cpp : CTetrisSDIDoc �N���X�̓���̒�`���s���܂��B
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
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTetrisSDIDoc �N���X�̍\�z/����

CTetrisSDIDoc::CTetrisSDIDoc()
{
	// TODO: ���̈ʒu�ɂP�x�����Ă΂��\�z�p�̃R�[�h��ǉ����Ă��������B

}

CTetrisSDIDoc::~CTetrisSDIDoc()
{
}

BOOL CTetrisSDIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���̈ʒu�ɍď�����������ǉ����Ă��������B
	// (SDI �h�L�������g�͂��̃h�L�������g���ė��p���܂��B)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTetrisSDIDoc �V���A���C�[�[�V����

void CTetrisSDIDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���̈ʒu�ɕۑ��p�̃R�[�h��ǉ����Ă��������B
	}
	else
	{
		// TODO: ���̈ʒu�ɓǂݍ��ݗp�̃R�[�h��ǉ����Ă��������B
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTetrisSDIDoc �N���X�̐f�f

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
// CTetrisSDIDoc �R�}���h
