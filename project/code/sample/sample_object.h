//==========================================================
//
// �T���v���I�u�W�F�N�g [sample.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _SAMPLEOBJECT_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _SAMPLEOBJECT_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "../object.h"
//#include "object.h"	// ����Ńt�@�C���C���N���[�h�ł��܂�

//==========================================================
// �T���v���̃N���X��`
//==========================================================
class CSampleObject : public CObject
{

public:	// �N�ł��A�N�Z�X�\

	//CSample();	// �R���X�g���N�^
	CSampleObject(int nPriOrity = 3);	// �R���X�g���N�^(�I�[�o�[���[�h)
	~CSampleObject();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Draw(void);
	static CSampleObject *Create(void);

	// �����o�֐�(�擾)
	

	// �����o�֐�(�ݒ�)

private:	// �����������A�N�Z�X�\

	// �����o�֐�

	// �����o�ϐ�
};

#endif

