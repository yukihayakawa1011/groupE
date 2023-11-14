//==========================================================
//
// �M�~�b�N��� [gimmick.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _GIMMICK_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _GIMMICK_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "task.h"	// ����Ńt�@�C���C���N���[�h�ł��܂�

//==========================================================
// �T���v���̃N���X��`
//==========================================================
class CGimmick : public CTask
{
public:

	// ��ޗ񋓌^
	enum TYPE
	{
		TYPE_NONE = 0,	// �����Ȃ�
		TYPE_TRAN_SWITCH,	// �X�e�[�W�J�ڃX�C�b�`
		TYPE_MAX
	};

public:	// �N�ł��A�N�Z�X�\

	CGimmick();	// �R���X�g���N�^(�I�[�o�[���[�h)
	~CGimmick();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void) = 0;
	void Uninit(void) = 0;
	void Update(void) = 0;

	// �����o�֐�(�擾)
	static bool Collision(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, int nAction);
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	D3DXMATRIX *GetMtxWorld(void) { return &m_mtxWorld; }

	// �����o�֐�(�ݒ�)
	void SetPosition(const D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRotation(const D3DXVECTOR3 rot) { m_rot = rot; }
	void SetActionId(const int nId) { m_nActionId = nId; }

protected:

	// ��ސݒ�
	void BindType(TYPE type) { m_type = type; }
	void ListOut(void);
	void SetMtxWorld(void);

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	virtual bool CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, int nAction) = 0;

	// �����o�ϐ�
	static CGimmick *m_pTop;	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CGimmick *m_pCur;	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^
	CGimmick *m_pPrev;		// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CGimmick *m_pNext;		// ���̃I�u�W�F�N�g�ւ̃|�C���^
	TYPE m_type;				// ���
	D3DXVECTOR3 m_pos;		// �ʒu
	D3DXVECTOR3 m_rot;		// ����
	int m_nActionId;			// �����̃A�N�V������
	D3DXMATRIX m_mtxWorld;	//���[���h�}�g���b�N�X
};

#endif

