//==========================================================
//
// �K�w�\���̏����S�� [character.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _CHARACTER_H_	// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _CHARACTER_H_	// ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"		//main.h�Œ�`���Ă�����̂��K�v�Ȃ���include

// �O���錾
class CModel;
class CMotion;

//**********************************************************
// �L�����N�^�[�N���X�̒�`
//**********************************************************
class CCharacter
{
private:	// �����������A�N�Z�X�\�Ȓ�`

public:	// �N�ł��A�N�Z�X�\
	CCharacter();	// �R���X�g���N�^
	~CCharacter();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	HRESULT Init(const char* pFileName);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void OpenFile(const char *pFileData);
	static CCharacter *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pFileName);
	static CCharacter *Create(const char* pFileName);

	// �ݒ�
	void SetPosition(const D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRotation(const D3DXVECTOR3 rot);
	void SetParent(D3DXMATRIX *pMtx) { m_ParentMtx = pMtx; }
	void SetDraw(bool bDraw = true);
	void SetShadow(bool bShadow = false);
	void SetCharaMtx(void);

	// �����o�֐�(�擾)
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXMATRIX *GetMtxWorld(void) { return &m_mtxWorld; }
	CModel *GetParts(int nIdx);
	int GetNumParts(void) { return m_nNumParts; }
	CMotion *GetMotion(void) { return m_pMotion; }

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void LoadFile(FILE *pFile);
	void LoadXFile(FILE *pFile);
	void LoadSetData(FILE *pFile);

	// �����o�ϐ�
	CMotion *m_pMotion;		// ���[�V�������̃|�C���^
	CModel **m_ppParts;		// �p�[�c�̏��
	int m_nNumParts;		// �p�[�c��
	D3DXMATRIX m_mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXMATRIX *m_ParentMtx;// �e�̃}�g���b�N�X
	D3DXVECTOR3 m_pos;		// ���W
	D3DXVECTOR3 m_rot;		// ����
};

#endif