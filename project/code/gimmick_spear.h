//==========================================================
//
// �M�~�b�N�����鑄 [gimmick_spear.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _GIMMICK_SPEAR_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _GIMMICK_SPEAR_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "gimmick.h"		// ����Ńt�@�C���C���N���[�h�ł��܂�

class CModel;
class CGimmickButton;
class CMeshCylinder;

//==========================================================
// �����鑄�̃N���X��`
//==========================================================
class CGimmickSpear : public CGimmick
{
private:

public:

	// ���
	enum TYPE
	{
		TYPE_AUTO = 0,	// �����쓮
		TYPE_PRESS,		// �쓮��
		TYPE_NOTPRESS,	// �����Ă��Ȃ��Ƃ��쓮
		TYPE_PRESSAUTO,	// �쓮�����㎩����
		TYPE_SENSOR,		// �Z���T�[��
		TYPE_MAX
	};

	// ��ԗ񋓌^
	enum STATE
	{
		STATE_NONE = 0,	// �����Ȃ�
		STATE_APPEAR,		// �o��
		STATE_ATKNOW,		// �U����
		STATE_BACK,		// �߂�
		STATE_MAX
	};

public:	// �N�ł��A�N�Z�X�\

	CGimmickSpear();		// �R���X�g���N�^(�I�[�o�[���[�h)
	~CGimmickSpear();		// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CGimmickSpear *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, TYPE type);
	virtual void IdSetButton(void) override;

	// �����o�֐�(�擾)
	STATE GetState(void) { return m_state; }
	CModel *GetModel(void) { return m_pObj; }
	TYPE GetType(void) { return m_type; }

	// �����o�֐�(�ݒ�)
	void BindType(TYPE type) { m_type = type; }
	void BindButton(CGimmickButton *pGimmick) { m_pInObj = pGimmick; }

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	bool CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, D3DXVECTOR3 &SetPos, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, int nAction, CGimmick **ppGimmick, bool* bLand = nullptr);
	void StateSet(void);
	void UpdateType(void);

	// �����o�ϐ�
	CModel *m_pObj;			// �I�u�W�F�N�g�̃|�C���^
	STATE m_state;			// ���
	TYPE m_type;				// ���
	D3DXVECTOR3 m_PosDest;		// �ڕW�̍��W
	CGimmickButton *m_pInObj;	// ���̓I�u�W�F�N�g
	bool m_bActive;			// ����\���ǂ���
	int m_nStateCounter;		// ��ԊǗ��J�E���^�[
	float m_fDiffMulti;		// �����␳�̔{��
	static char *m_pFileName;	// ���f���t�@�C���l�[��
	static int m_aStateSetCount[STATE_MAX];	// �J�ڃJ�E���g
	static float m_aStateDiffMulti[STATE_MAX];	// �J�ڃJ�E���g
};

#endif
