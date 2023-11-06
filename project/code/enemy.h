//==========================================================
//
// �G�̏��� [enemy.h]
// Author : Soma Ishihara (Base:Ibuki Okusada)
//
//==========================================================
#ifndef _ENEMY_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _ENEMY_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"
#include "object.h"
#include "objectX.h"
#include "task.h"

// �O���錾
class CCharacter;

//==========================================================
// �G�̃N���X��`(�h���N���X)
//==========================================================
class CEnemy : public CTask
{
public:

	// �����ޗ񋓌^
	enum TYPE
	{
		TYPE_NONE,	// ����s�\
		TYPE_SEND,	// �f�[�^���M
		TYPE_ACTIVE,	// ����\
		TYPE_MAX
	};

private:	// �����������A�N�Z�X�\�Ȓ�`

	// ��ԗ񋓌^
	enum STATE
	{
		STATE_APPEAR = 0,	// �o�����
		STATE_NORMAL,		// �ʏ���
		STATE_DAMAGE,		// �_���[�W���
		STATE_DEATH,		// ���S���
		STATE_SPAWN,		// ���������
		STATE_MAX
	};

	// ���\����
	typedef struct
	{
		D3DXVECTOR3 pos;		// �ʒu
		D3DXVECTOR3 rot;		// ����
		D3DXVECTOR3 move;		// �ړ���
		D3DXVECTOR3 posOld;	// �ݒ�ʒu
		D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
		D3DXVECTOR3 posDiff;
		STATE state;			// ���
		float fStateCounter;	// ��ԊǗ��J�E���^�[
	}SInfo;

public:	// �N�ł��A�N�Z�X�\

	//CEnemy();	// �R���X�g���N�^
	CEnemy(const D3DXVECTOR3 pos);	// �R���X�g���N�^(�I�[�o�[���[�h)
	CEnemy(int nPriOrity = 1);
	~CEnemy();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	HRESULT Init(const char *pBodyName, const char *pLegName);	// �I�[�o�[���[�h
	void Uninit(void);
	void Update(void);
	static CEnemy *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 move,
		const char *pBodyName, const char *pLegName, const int nPriority = 4);

	// �����o�֐�(�ݒ�)
	void SetMove(const D3DXVECTOR3 move) { m_Info.move = move; }
	void SetPosition(const D3DXVECTOR3 pos) { m_Info.pos = pos; m_Info.posDiff = pos; }
	void SetDiffPosition(const D3DXVECTOR3 pos) { m_Info.posDiff = pos; }
	void SetRotation(const D3DXVECTOR3 rot) { m_Info.rot = rot; }
	void BindId(int nId) { m_nId = nId; }
	void SetType(TYPE type);

	// �����o�֐�(�擾)
	D3DXVECTOR3 GetMove(void) { return m_Info.move; }
	D3DXVECTOR3 GetPosition(void) { return m_Info.pos; }
	D3DXVECTOR3 GetRotation(void) { return m_Info.rot; }
	int GetId(void) { return m_nId; }
	static CEnemy *GetTop(void) { return m_pTop; }
	CEnemy *GetNext(void) { return m_pNext; }
	void Damage(int nDamage);
	void SetLife(int nLife);

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void StateSet(void);
	void Controller(void);
	void Move(void);
	void Rotation(void);
	void Adjust(void);
	void Search(void);

	// �����o�ϐ�
	static CEnemy *m_pTop;	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CEnemy *m_pCur;	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^
	CEnemy *m_pPrev;	// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CEnemy *m_pNext;	// ���̃I�u�W�F�N�g�ւ̃|�C���^
	SInfo m_Info;			// �������g�̏��
	CCharacter *m_pObject;	// �`��I�u�W�F�N�g
	float m_fRotMove;		// ���݂̊p�x
	float m_fRotDiff;		// �ړI�̊p�x
	float m_fRotDest;		// �p�x�v�Z
	bool m_bMove;
	int m_nLife;	// �̗�
	int m_nId;	// ID
	TYPE m_type;	// ���
	static int m_nNumCount;

};

#endif