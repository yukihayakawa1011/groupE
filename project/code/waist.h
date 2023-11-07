//==========================================================
//
// ���z�̍������S�� [waist.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _WAIST_H_	// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _WAIST_H_	// ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"		//main.h�Œ�`���Ă�����̂��K�v�Ȃ���include

//==========================================================
// ���N���X�̒�`
//==========================================================
class CWaist
{
public:	// �N�ł��A�N�Z�X�\

	CWaist();	// �R���X�g���N�^
	~CWaist();	// �f�X�g���N�^

	// �����o�֐�
	void SetMatrix(void);
	void SetParent(D3DXMATRIX *pMtx) { m_pParentMtx = pMtx; }
	void SetPosition(const D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRotation(const D3DXVECTOR3 rot) { m_rot = rot; }
	void SetHeight(D3DXVECTOR3& pPos);
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	D3DXVECTOR3 GetSetPosition(void) { return m_SetPos; }
	D3DXMATRIX *GetMtxWorld(void) { return &m_mtxWorld; }
	static CWaist *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:	// �����������A�N�Z�X�\

	// �����o�ϐ�
	D3DXVECTOR3 m_pos;		// �ʒu
	D3DXVECTOR3 m_rot;		// ����
	D3DXMATRIX m_mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_SetPos;	// �ݒ�ʒu
	D3DXMATRIX *m_pParentMtx;	// �e�̃��[���h�}�g���b�N�X
};
#endif