//==========================================================
//
// �T���v���^�X�N [sample_task.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _SAMPLETASK_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _SAMPLETASK_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "../task.h"
//#include "task.h"	// ����Ńt�@�C���C���N���[�h�ł��܂�

//==========================================================
// �T���v���̃N���X��`
//==========================================================
class CSampleTask : public CTask
{

public:	// �N�ł��A�N�Z�X�\

	CSampleTask();	// �R���X�g���N�^(�I�[�o�[���[�h)
	~CSampleTask();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CSampleTask *Create(void);

	// �����o�֐�(�擾)

	// �����o�֐�(�ݒ�)

private:	// �����������A�N�Z�X�\

	// �����o�֐�

	// �����o�ϐ�
};

#endif
