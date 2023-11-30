//==========================================================
//
// �M�~�b�N��]�h�A [gimmick_rotatedoor.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _GIMMICK_ROTATEDOOR_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _GIMMICK_ROTATEDOOR_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "gimmick.h"		// ����Ńt�@�C���C���N���[�h�ł��܂�

class CModel;

//==========================================================
// ��]�h�A�̃N���X��`
//==========================================================
class CGimmickRotateDoor : public CGimmick
{
private:

public:

	// ��ԗ񋓌^
	enum STATE
	{
		STATE_NONE = 0,	// �����Ȃ�
		STATE_ROTATE,		// ��]��
		STATE_MAX
	};

public:	// �N�ł��A�N�Z�X�\

	CGimmickRotateDoor();		// �R���X�g���N�^(�I�[�o�[���[�h)
	~CGimmickRotateDoor();		// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CGimmickRotateDoor *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);

	// �����o�֐�(�擾)
	STATE GetState(void) { return m_state; }
	CModel *GetModel(void) { return m_pObj; }
	CGimmickRotateDoor *GetRotateDoor(void) { return this; }

	// �����o�֐�(�ݒ�)

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	bool CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, D3DXVECTOR3 &SetPos, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, int nAction, CGimmick **ppGimmick, bool* bLand = nullptr);

	// �����o�ϐ�
	CModel *m_pObj;			// �I�u�W�F�N�g�̃|�C���^
	STATE m_state;			// ���
	D3DXVECTOR3 m_RotDest;		// �ڕW�̊p�x
	static char *m_pFileName;	// ���f���t�@�C���l�[��

};

#endif
