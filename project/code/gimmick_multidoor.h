//==========================================================
//
// �M�~�b�N���̓h�A [gimmick_multidoor.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _GIMMICK_MULTIDOOR_H_	// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _GIMMICK_MULTIDOOR_H_	// ��d�C���N���[�h�h�~�p�}�N�����`

#include "gimmick.h"	// ����Ńt�@�C���C���N���[�h�ł��܂�

class CModel;
class CGimmickButton;

//==========================================================
// �����鑄�̃N���X��`
//==========================================================
class CGimmickMultiDoor : public CGimmick
{
public:

	// ��ԗ񋓌^
	enum STATE {
		STATE_NEUTRAL = 0,	// �ҋ@
		STATE_OPEN,			// �J��
		STATE_CLOSE,			// ����
		STATE_MAX
	};

private:

	// �g�p�I�u�W�F�N�g��ޗ�
	enum TYPE 
	{
		TYPE_LEFT = 0,	// ����
		TYPE_RIGHT,		// �E��
		TYPE_MAX
	};

	// �I�u�W�F�N�g���\����
	struct SObj {
		CModel *pModel;		// �I�u�W�F�N�g�̃|�C���^
		D3DXVECTOR3 posDest;	// �ڕW�̍��W
		D3DXVECTOR3 posOld;	// �O��̍��W
	};

public:	// �N�ł��A�N�Z�X�\

	CGimmickMultiDoor();		// �R���X�g���N�^(�I�[�o�[���[�h)
	~CGimmickMultiDoor();		// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CGimmickMultiDoor *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);
	void BindButton(CGimmickButton *pButton);
	void SetNumButton(const int nNum);
	
	// �����o�֐�(�擾)

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	bool CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, D3DXVECTOR3 &SetPos, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, int nAction, CGimmick **ppGimmick, bool* bLand = nullptr);
	void StateSet(void);
	void UpdateState(void);
	void ObjIner(void);

	// �����o�ϐ�
	SObj m_aObject[TYPE_MAX];
	int m_nNumSwitch;					// �K��l�̃X�C�b�`��
	int m_nNumLinkSwitch;				// �����N���Ă���X�C�b�`��
	CGimmickButton **m_ppButton;		// �A�N�Z�X���͑��u
	STATE m_state;					// ���
	int m_nStateCnt;					// ��ԊǗ��J�E���^�[
	float m_fInerMulti;				// �␳�{��
};

#endif


