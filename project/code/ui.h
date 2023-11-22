//==========================================================
//
// �T���v���^�X�N [sample_task.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _UI_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _UI_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

//#include "../task.h"
#include "task.h"	// ����Ńt�@�C���C���N���[�h�ł��܂�

//�O���錾
class CObject2D;

//==========================================================
// UI�̃N���X��`
//==========================================================
class CUI : public CTask
{

public:	// �N�ł��A�N�Z�X�\

	CUI();	// �R���X�g���N�^(�I�[�o�[���[�h)
	~CUI();	// �f�X�g���N�^

					// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CUI *Create(void);

	// �����o�֐�(�擾)
	D3DXVECTOR3 GetPosition(void) { return m_pos; }

	// �����o�֐�(�ݒ�)
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }

private:	// �����������A�N�Z�X�\

			// �����o�֐�

			// �����o�ϐ�
	CObject2D *m_pObject;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;

};

#endif


