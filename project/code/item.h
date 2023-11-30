//==========================================================
//
// �A�C�e���̏��� [item.h]
// Author : Yuuka Sakuma
//
//==========================================================
#ifndef _ITEM_H_	// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _ITEM_H_	// ��d�C���N���[�h�h�~�p�}�N�����`

#include "task.h"

// �O���錾
class CModel;

//==========================================================
// �A�C�e���N���X�̒�`(�h���N���X)
//==========================================================
class CItem : public CTask
{
public:

	enum STATE
	{
		STATE_NORMAL = 0,	// �ʏ�
		STATE_DROP,		// �h���b�v��������
		STATE_CRASH,			//�����
		STATE_DOWN,			//����
		STATE_MAX
	};

	enum TYPE
	{
		TYPE_NORMAL = 0,   // �Ȃ���Ȃ�
		TYPE_COIN,         // �R�C��
		TYPE_BRECELET,     // �u���X���b�g
		TYPE_CUP,          // �u
		TYPE_GEM00,        // �G�������h
		TYPE_GEM01,        // �_�C�������h
		TYPE_GOLDBAR,      // ����
		TYPE_JAR,          // �r
		TYPE_KUNAI,        // �N�i�C
		TYPE_RING00,       // �r��
		TYPE_SCROLL,       // ����
		TYPE_SHURIKEN,     //�藠��
		TYPE_MAX
	};

public:	// �N�ł��A�N�Z�X�\

	CItem();		// �R���X�g���N�^
	~CItem();		// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	HRESULT Init(const char *pFileName, int type);
	void Uninit(void);
	void Update(void);

	static CItem *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *pFileName, int type, int nType = TYPE_NORMAL);
	static CItem *Collision(D3DXVECTOR3 &pos);

	// �����o�֐�(�ݒ�)
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	void SetOldPos(D3DXVECTOR3 posOld) { m_posOld = posOld; }
	void SetPosition(const D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRotation(const D3DXVECTOR3 rot) { m_rot = rot; }
	void SetState(STATE state) { m_nState = state; }
	void SetType(int type) { m_type = type; }
	void SetNext(CItem *pNext) { m_pNext = pNext; }
	void SetPrev(CItem *pPrev) { m_pPrev = pPrev; }

	// �����o�֐�(�擾)
	static CItem *GetTop(void) { return m_pTop; }
	D3DXVECTOR3 GetMove(void) { return m_move; }
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	D3DXVECTOR3 GetOldPos(void) { return m_posOld; }
	int GetState(void) { return m_nState; }
	int GetType(void) { return m_type; }
	int GetEachScore(void);
	CItem *GetNext(void) { return m_pNext; }
	CItem *GetPrev(void) { return m_pPrev; }
	CModel *GetModel(void) { return m_pObject; }

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	bool CollisionCheck(D3DXVECTOR3 &pos);

	// �����o�ϐ�
	static CItem *m_pTop;	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CItem *m_pCur;	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^
	CItem *m_pPrev;	// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CItem *m_pNext;	// ���̃I�u�W�F�N�g�ւ̃|�C���^
	CModel *m_pObject;
	D3DXVECTOR3 m_move;	// �ړ���
	D3DXVECTOR3 m_posOld;	// �O��̍��W
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	int m_type;
	int m_nBound;		// bound��
	float m_fCurve;
	int m_nState;
};

#endif