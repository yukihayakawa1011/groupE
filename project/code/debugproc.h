//==========================================================
//
// �f�o�b�O�\������ [debugproc.h]
// Author Ibuki Okusada
//
//==========================================================
#ifndef _DEBUGPROC_H_		//���̃}�N������`����Ă��Ȃ��ꍇ
#define _DEBUGPROC_H_

#include "main.h"
#include "manager.h"

//**********************************************************
//�}�N����`
//**********************************************************
#define MAX_DEBUGSTRING	(2048)	//�f�o�b�O�\���̍ő啶����

//**********************************************************
//�N���X�̒�`
//**********************************************************
class CDebugProc
{
public:	// �N�ł��A�N�Z�X�\

	CDebugProc();	// �R���X�g���N�^
	~CDebugProc();	// �f�X�g���N�^

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Print(const char *fmt, ...);

private:	// �����������A�N�Z�X�\
	static LPD3DXFONT m_pFont;	//�t�H���g�ւ̃|�C���^
	char m_aStr[MAX_DEBUGSTRING];	//�f�o�b�O�\���p�̕�����
	bool m_bDisp;		//�f�o�b�O�\����ON/OFF
	static const char *m_apMode[CScene::MODE_MAX];
};

#endif