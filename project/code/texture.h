//===============================================
//
// �e�N�X�`���̊Ǘ��S�� [texture.h]
// Author : Ibuki Okusada
//
//===============================================
#ifndef _TEXTURE_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _TEXTURE_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"

// �}�N����`
#define MAX_TEXTURE		(256)	// �e�N�X�`���̍ő吔
#define MAX_FILENAME	(256)	// �t�@�C�����ő啶����

//**********************************************************
// �e�N�X�`���N���X�̒�`
//**********************************************************
class CTexture
{
public:	// �N�ł��A�N�Z�X�\�Ȓ�`
	
	// �����ǂݍ��ݎ��
	enum TYPE
	{
		TYPE_EFFECT = 0,		// �G�t�F�N�g
		TYPE_MONEY,				//�X�R�A�̒P��
		TYPE_FRAME0,			//�g0
		TYPE_FRAME1,			//�g1
		TYPE_FRAME2,			//�g2
		TYPE_FRAME3,			//�g3
		TYPE_PLAYER0,			//�v���C���[�̊�0
		TYPE_PLAYER1,			//�v���C���[�̊�1
		TYPE_PLAYER2,			//�v���C���[�̊�2
		TYPE_PLAYER3,			//�v���C���[�̊�3
		TYPE_MAX
	};

private:	// �����������A�N�Z�X�\�Ȓ�`
	
	// �t�@�C�����
	typedef struct
	{
		LPDIRECT3DTEXTURE9 pTexture;	// �e�N�X�`���̃|�C���^
		char aName[MAX_FILENAME];		// �t�@�C����
	}File;

public:	// �N�ł��A�N�Z�X�\

	CTexture();		// �R���X�g���N�^
	~CTexture();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Load(void);
	void Unload(void);
	int Regist(const char* pFileName);
	LPDIRECT3DTEXTURE9 SetAddress(int nIdx);

	// �����o�֐�(�擾)
	int GetNumAll(void) { return m_nNumAll; }
	const static char *GetFileName(int nIdx);

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	File m_aFile[MAX_TEXTURE];	// �e�N�X�`���ւ̃|�C���^
	static int m_nNumAll;		// �ǂݍ��ݑ���
	const static char *m_apDefFileName[TYPE_MAX];	// �����ǂݍ��݃t�@�C����
};

#endif
