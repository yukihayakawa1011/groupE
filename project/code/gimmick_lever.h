//==========================================================
//
// �M�~�b�N���o�[ [gimmick_lever.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _GIMMICK_LEVER_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _GIMMICK_LEVER_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "gimmick.h"			// ����Ńt�@�C���C���N���[�h�ł��܂�

class CModel;

//==========================================================
// �T���v���̃N���X��`
//==========================================================
class CGimmickLever : public CGimmick
{
private:

	// �g�p���f���񋓌^
	enum MODEL
	{
		MODEL_FRAME = 0,	// �g�g��
		MODEL_BUTTON,		// �{�^��
		MODEL_MAX
	};

public:

	// ��ԗ񋓌^
	enum STATE
	{
		STATE_NONE = 0,	// �����Ȃ�
		STATE_PRESS,		// ������Ă���
		STATE_MAX
	};

public:	// �N�ł��A�N�Z�X�\

	CGimmickLever();		// �R���X�g���N�^(�I�[�o�[���[�h)
	~CGimmickLever();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CGimmickLever *Create(const D3DXVECTOR3 pos);

	// �����o�֐�(�擾)
	STATE GetState(void) { return m_state; }

	// �����o�֐�(�ݒ�)

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	bool CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, D3DXVECTOR3 &SetPos, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, int nAction, CGimmick **ppGimmick, bool* bLand = nullptr);

	// �����o�ϐ�
	CModel *m_apObj[MODEL_MAX];			// �{�^����
	STATE m_state;						// ���
	D3DXVECTOR3 m_RotDest;					// �ڕW�̊p�x
	static char *m_apFileName[MODEL_MAX];	// ���f���t�@�C���l�[��
	int m_nInterval;						// �C���^�[�o��
};

#endif
