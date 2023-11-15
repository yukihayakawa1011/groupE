//==========================================================
//
// �M�~�b�N�J�n�n�_�h�A [gimmick_startdoor.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _GIMMICK_STARTDOOR_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _GIMMICK_STARTDOOR_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "gimmick.h"			// ����Ńt�@�C���C���N���[�h�ł��܂�

class CModel;
class CGimmickLever;

//==========================================================
// �J�n�n�_�h�A�̃N���X��`
//==========================================================
class CGimmickStartDoor : public CGimmick
{
private:

public:

	// ��ԗ񋓌^
	enum STATE
	{
		STATE_NONE = 0,	// �����Ȃ�
		STATE_OPEN,		// ������Ă���
		STATE_MAX
	};

public:	// �N�ł��A�N�Z�X�\

	CGimmickStartDoor();		// �R���X�g���N�^(�I�[�o�[���[�h)
	~CGimmickStartDoor();		// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CGimmickStartDoor *Create(const D3DXVECTOR3 pos);

	// �����o�֐�(�擾)
	STATE GetState(void) { return m_state; }

	// �����o�֐�(�ݒ�)
	void SetLever(CGimmickLever *pLever) { m_pLever = pLever; }

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	bool CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, D3DXVECTOR3 &SetPos, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, int nAction, CGimmick **ppGimmick);

	// �����o�ϐ�
	CModel *m_pObj;			// �I�u�W�F�N�g�̃|�C���^
	STATE m_state;			// ���
	D3DXVECTOR3 m_PosDest;		// �ڕW�̊p�x
	CGimmickLever *m_pLever;	// ��������郌�o�[�̃|�C���^
	static char *m_pFileName;	// ���f���t�@�C���l�[��
	
};

#endif
