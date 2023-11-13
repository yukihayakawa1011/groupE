//==========================================================
//
// �X�e�[�W�J�ڃ{�^�� [gimmick_transbutton.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _GIMMICK_TRANSBUTTON_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _GIMMICK_TRANSBUTTON_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "gimmick.h"				// ����Ńt�@�C���C���N���[�h�ł��܂�

class CModel;
class CObjectX;

//==========================================================
// �T���v���̃N���X��`
//==========================================================
class CGimmickTransButton : public CGimmick
{
private:

	// �g�p���f���񋓌^
	enum MODEL
	{
		MODEL_FRAME = 0,	// �g�g��
		MODEL_BUTTON,		// �{�^��
		MODEL_MAX
	};

	// ��ԗ񋓌^
	enum STATE
	{
		STATE_NONE = 0,	// �����Ȃ�
		STATE_PRESS,		// ������Ă���
		STATE_MAX
	};

public:	// �N�ł��A�N�Z�X�\

	CGimmickTransButton();		// �R���X�g���N�^(�I�[�o�[���[�h)
	~CGimmickTransButton();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CGimmickTransButton *Create(const D3DXVECTOR3 pos);

	// �����o�֐�(�擾)

	// �����o�֐�(�ݒ�)

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	bool CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax);

	// �����o�ϐ�
	CModel *m_apObj[MODEL_MAX];	// �{�^����
	STATE m_state;				// ���
	static char *m_apFileName[MODEL_MAX];	// ���f���t�@�C���l�[��
};

#endif
