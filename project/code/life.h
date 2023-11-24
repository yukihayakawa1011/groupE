//==========================================================
//
// �T���v���^�X�N [sample_task.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _LIFE_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _LIFE_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "task.h"	// ����Ńt�@�C���C���N���[�h�ł��܂�


class CObject2D;
//==========================================================
// �T���v���̃N���X��`
//==========================================================
class CLife : public CTask
{

public:	// �N�ł��A�N�Z�X�\

	CLife();	// �R���X�g���N�^(�I�[�o�[���[�h)
	~CLife();	// �f�X�g���N�^

					// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CLife *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	// �����o�֐�(�擾)
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	int GetLife(void) { return m_life; }

	// �����o�֐�(�ݒ�)
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }

private:	// �����������A�N�Z�X�\

#define NUM_LIFE (6)	//�I�u�W�F�N�g�̐�
			// �����o�֐�

			// �����o�ϐ�
	CObject2D *m_pObject[NUM_LIFE];
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	int m_life;

};

#endif


