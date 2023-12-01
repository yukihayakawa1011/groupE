//==========================================================
//
// �Q�[�W [gage.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _GAGE_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _GAGE_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "task.h"	// ����Ńt�@�C���C���N���[�h�ł��܂�

// �O���錾
class CObjectBillboard;

//==========================================================
// �T���v���̃N���X��`
//==========================================================
class CGage : public CTask
{
private:

	// ��ޗ񋓌^
	enum TYPE
	{
		TYPE_FRAME = 0,	// �g
		TYPE_CONTENT,		// ���g
		TYPE_MAX
	};

public:	// �N�ł��A�N�Z�X�\

	CGage();	// �R���X�g���N�^(�I�[�o�[���[�h)
	~CGage();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CGage *Create(void);

	// �����o�֐�(�擾)

	// �����o�֐�(�ݒ�)

private:	// �����������A�N�Z�X�\

	// �����o�֐�

	// �����o�ϐ�
};

#endif

