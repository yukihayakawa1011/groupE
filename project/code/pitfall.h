//==========================================================
//
// ���Ƃ��� [pitfall.h]
// Author : Soma Ishihara
//
//==========================================================
#ifndef _PITFALL_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _PITFALL_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "task.h"

//�O���錾
class CObjectX;

//==========================================================
// �T���v���̃N���X��`
//==========================================================
class CPitFall : public CTask
{

public:	// �N�ł��A�N�Z�X�\

	CPitFall();	// �R���X�g���N�^(�I�[�o�[���[�h)
	~CPitFall();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CPitFall *Create(const D3DXVECTOR3 pos);

	// �����o�֐�(�擾)

	// �����o�֐�(�ݒ�)
	void IsOpen(const bool bOpen) { m_bOpen = bOpen; }

private:	// �����������A�N�Z�X�\

	// �����o�֐�

	// �����o�ϐ�
	CObjectX* m_pObjFloor[2];	//���̏�
	float m_fAngle;				//���̊J���
	bool m_bOpen;				//�����J���Ă��邩
};

#endif

