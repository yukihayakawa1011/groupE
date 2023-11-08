//==========================================================
//
// �A�C�e���̏��� [item.h]
// Author : Yuuka Sakuma
//
//==========================================================
#ifndef _ITEM_H_	// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _ITEM_H_	// ��d�C���N���[�h�h�~�p�}�N�����`

#include "task.h"

// �O���錾
class CObjectX;

//==========================================================
// �A�C�e���N���X�̒�`(�h���N���X)
//==========================================================
class CItem : public CTask
{
public:	// �N�ł��A�N�Z�X�\

	CItem();		// �R���X�g���N�^
	~CItem();		// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	HRESULT Init(const char *pFileName);
	void Uninit(void);
	void Update(void);

	static CItem *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *pFileName, int nType = 0, const int nPriority = 3);

	// �����o�֐�(�ݒ�)
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	void SetOldPos(D3DXVECTOR3 posOld) { m_posOld = posOld; }
	void SetPosition(const D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRotation(const D3DXVECTOR3 rot) { m_rot = rot; }
	void SetType(TYPE type);

	// �����o�֐�(�擾)
	D3DXVECTOR3 GetMove(void) { return m_move; }
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	D3DXVECTOR3 GetOldPos(void) { return m_posOld; }
	int GetType(void) { return m_nType; }

private:	// �����������A�N�Z�X�\

	// �����o��
	CObjectX *m_pObject;
	D3DXVECTOR3 m_move;	// �ړ���
	D3DXVECTOR3 m_posOld;	// �O��̍��W
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	float m_fCurve;
	int m_nType;
};

#endif