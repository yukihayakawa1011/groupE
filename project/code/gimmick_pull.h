//==========================================================
//
// �M�~�b�N��������� [gimmick_rotatedoor.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _GIMMICK_PULL_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _GIMMICK_PULL_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "gimmick.h"		// ����Ńt�@�C���C���N���[�h�ł��܂�

class CModel;

//==========================================================
// ��]�h�A�̃N���X��`
//==========================================================
class CGimmickPull : public CGimmick
{
private:

public:

	// ��ԗ񋓌^
	enum STATE
	{
		STATE_NONE = 0,	// �����Ȃ�
		STATE_PULL,		// ������
		STATE_MAX
	};

public:	// �N�ł��A�N�Z�X�\

	CGimmickPull();		// �R���X�g���N�^(�I�[�o�[���[�h)
	~CGimmickPull();		// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CGimmickPull *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);

	// �����o�֐�(�擾)
	STATE GetState(void) { return m_state; }
	CModel *GetModel(void) { return m_pObj; }
	virtual CGimmickPull *GetPull(void) override { return this; }

	// �����o�֐�(�ݒ�)
	virtual void SetMtxParent(D3DXMATRIX *pMtx) override { m_pMtxParent = pMtx; }

private:	// �����������A�N�Z�X�\



	// �����o�֐�
	bool CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, D3DXVECTOR3 &SetPos, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, int nAction, CGimmick **ppGimmick, bool* bLand = nullptr);
	void SetParentMatrix(void);

	// �����o�ϐ�
	D3DXMATRIX *m_pMtxParent;	// �e�̃}�g���b�N�X
	CModel *m_pObj;			// �I�u�W�F�N�g�̃|�C���^
	STATE m_state;			// ���
	D3DXVECTOR3 m_RotDest;		// �ڕW�̊p�x
	static char *m_pFileName;	// ���f���t�@�C���l�[��

};

#endif
