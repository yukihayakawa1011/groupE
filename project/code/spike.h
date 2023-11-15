//==========================================================
//
// �܂��т� [spike.h]
// Author : Soma Ishihara
//
//==========================================================
#ifndef _SPIKE_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _SPIKE_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "task.h"

//�O���錾
class CObjectX;

//==========================================================
// �T���v���̃N���X��`
//==========================================================
class CSpike : public CTask
{
private:
	// ���\����
	struct SInfo
	{
		D3DXVECTOR3 pos;		// �ʒu
		D3DXVECTOR3 rot;		// ����
		D3DXVECTOR3 move;		// �ړ���
		D3DXVECTOR3 posOld;		// �ݒ�ʒu
		int nLife;
	};

public:	// �N�ł��A�N�Z�X�\

	CSpike();	// �R���X�g���N�^(�I�[�o�[���[�h)
	~CSpike();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CSpike *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float move);

	// �����o�֐�(�擾)
	D3DXVECTOR3 GetPosition(void) { return m_info.pos; }
	D3DXVECTOR3 GetRotation(void) { return m_info.rot; }
	D3DXVECTOR3 GetMove(void) { return m_info.move; }
	D3DXVECTOR3 GetPositionOld(void) { return m_info.posOld; }
	int GetLife(void) { return m_info.nLife; }
	static CSpike* GetTop(void) { return m_pTop; }
	CSpike* GetNext(void) { return m_pNext; }

	// �����o�֐�(�ݒ�)
	void SetPosition(const D3DXVECTOR3 pos) { m_info.pos = pos; }
	void SetRotation(const D3DXVECTOR3 rot) { m_info.rot = rot; }
	void SetMove(const D3DXVECTOR3 move) { m_info.move = move; }
	void SetPositionOld(const D3DXVECTOR3 pos) { m_info.posOld = pos; }
	void SetLife(const int nLife) { m_info.nLife = nLife; }

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void CollisionCloss(void);
	void Collision(void);

	// �����o�ϐ�
	static CSpike *m_pTop;	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CSpike *m_pCur;	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^
	CSpike *m_pPrev;	// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CSpike *m_pNext;	// ���̃I�u�W�F�N�g�ւ̃|�C���^
	CObjectX* m_pObj;	//�I�u�W�F�N�g
	SInfo m_info;		//���
	static int m_nNumCount;
};

#endif

