//==========================================================
//
// �S�[�� [goal.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _GOAL_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _GOAL_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "task.h"	// ����Ńt�@�C���C���N���[�h�ł��܂�

// �O���錾
class CMeshField;

//==========================================================
// �T���v���̃N���X��`
//==========================================================
class CGoal : public CTask
{
public:	// �N�ł��A�N�Z�X�\

	CGoal();	// �R���X�g���N�^(�I�[�o�[���[�h)
	~CGoal();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CGoal *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, float fWidth);
	static bool Collision(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld);
	void ListOut(void);

	// �����o�֐�(�擾)
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }

	// �����o�֐�(�ݒ�)
	void SetPosition(const D3DXVECTOR3& pos) { m_pos = pos; }
	void SetRotation(const D3DXVECTOR3& rot) { m_rot = rot; }

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	bool CollisionCheck(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld);

	// �����o�ϐ�
	static CGoal *m_pTop;	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CGoal *m_pCur;	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^
	CGoal *m_pPrev;		// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CGoal *m_pNext;		// ���̃I�u�W�F�N�g�ւ̃|�C���^
	CMeshField *m_pObject;	// ���b�V���t�B�[���h���g�p
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_rot;	// ����
};

#endif
