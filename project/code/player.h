//==========================================================
//
// �v���C���[�̏��� [player.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _PLAYER_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _PLAYER_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"
#include "object.h"
#include "objectX.h"
#include "task.h"

// �O���錾
class CWaist;
class CCharacter;
class CGimmick;
class CScore;
class CCamera;
class CItem;
class CLife;
class CUI;
class CGage;
class CThrowItem;
class CHeadUI;

// �}�N����`
#define MAX_ITEM  (1280)  // �����ł���A�C�e���̍ő吔

//==========================================================
// �v���C���[�̃N���X��`(�h���N���X)
//==========================================================
class CPlayer : public CTask
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


	// �A�N�V�����񋓌^
	enum ACTION
	{
		ACTION_NEUTRAL = 0,	// �ҋ@
		ACTION_WALK,			// ���s
		ACTION_JUMP,			// �W�����v
		ACTION_ATK,			// �U��
		ACTION_CATCH,			// ����
		ACTION_HOLD,			// �ێ�
		ACTION_THROW,			// ������
		ACTION_DAMAGE,		// �U�����󂯂�
		ACTION_FLUTTERING,	// �����΂�
		ACTION_HENGE,			// �ω��̏p
		ACTION_KUNAI,			// �N�i�C�̏p
		ACTION_AIR,			// ���_�̏p
		ACTION_MAX
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
		STATE_CATCH,		// �͂܂�Ă�����
		STATE_BLOW,		// ������΂�����
		STATE_MAX
	};

	// ���\����
	struct SInfo
	{
		D3DXVECTOR3 pos;		// �ʒu
		D3DXVECTOR3 rot;		// ����
		D3DXVECTOR3 move;		// �ړ���
		D3DXVECTOR3 posOld;	// �ݒ�ʒu
		D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
		D3DXVECTOR3 posDiff;	// �ڕW�̍��W
		STATE state;			// ���
		float fStateCounter;	// ��ԊǗ��J�E���^�[
	};

	// �͂ݏ��\����
	struct SCatch
	{
		CGimmick *pGimmick;	// �M�~�b�N
		CPlayer *pPlayer;		// �v���C���[
		int nMoveCnt;			// �ړ�������
		D3DXVECTOR3 SetPos;	// �ݒ���W
	};

public:	// �N�ł��A�N�Z�X�\

	CPlayer();	// �R���X�g���N�^
	~CPlayer();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	HRESULT Init(const char *pBodyName, const char *pLegName);	// �I�[�o�[���[�h
	void Uninit(void);
	void Update(void);
	static CPlayer *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 move,
		const char *pBodyName, const char *pLegName);
	bool HitCheck(D3DXVECTOR3 pos, float fRange, int nDamage = 1);

	// �����o�֐�(�ݒ�)
	void SetMove(const D3DXVECTOR3 move) { m_Info.move = move; }
	void SetPosition(const D3DXVECTOR3 pos) { m_Info.pos = pos; m_Info.posDiff = pos; }
	void SetDiffPosition(const D3DXVECTOR3 pos) { m_Info.posDiff = pos; }
	void SetRotation(const D3DXVECTOR3 rot) { m_Info.rot = rot; }
	void BindId(int nId) { m_nId = nId; }
	void SetType(TYPE type);
	void SetCamera(CCamera *pCamera) { m_pMyCamera = pCamera; }
	void BindScore(CScore *pScore) { m_pScore = pScore; }
	void BindUI(CUI *pUI);
	void Ninjutsu(void);
	void Blow(void);
	void SetMotion(int nMotion);

	// �����o�֐�(�擾)
	D3DXVECTOR3 GetMove(void) { return m_Info.move; }
	D3DXVECTOR3 GetPosition(void) { return m_Info.pos; }
	D3DXVECTOR3 GetRotation(void) { return m_Info.rot; }
	int GetId(void) { return m_nId; }
	static CPlayer *GetTop(void) { return m_pTop; }
	static int GetNum(void) { return m_nNumCount; }
	CPlayer *GetNext(void) { return m_pNext; }
	void Damage(int nDamage);
	void SetLife(int nLife);
	int GetLife(void) { return m_nLife; }
	STATE GetState(void) { return m_Info.state; }
	bool GetGoal(void) { return m_bGoal; }
	CScore *GetScore(void) { return m_pScore; }
	ACTION GetAction(void) const { return m_action; }
	int GetThrowItemId(void) { return m_nItemId; }
	int GetMotion(void);

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void SetMatrix(void);
	void StateSet(void);
	void Controller(void);
	void Move(void);
	void Rotation(void);
	void Adjust(void);
	void KeyBoardRotation(void);
	void MoveController(void);
	void Jump(void);
	void MotionSet(void);
	void Attack(void);
	void Catch(void);
	void PlayerCatch(D3DXVECTOR3 pos);
	void SetCatchMatrix(void);
	void Throw(void);
	void Drop(int nDropCnt);
	void DropAll(void);
	void DamageCollision(D3DXVECTOR3 pos);
	void AttackCheck(void);
	void GimmickRelease(void);
	const char *ItemFileName(int type);
	void ItemSort(void);
	void AddItemCount(int type);
	void SubItemCount(int type);
	void SelectItem(void);
	int GetSelectItem(int type);
	void BodySet(void);
	void ChangeBody(void);
	void BulletSet(void);

	// �����o�ϐ�
	static CPlayer *m_pTop;	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CPlayer *m_pCur;	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^
	CPlayer *m_pPrev;		// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CPlayer *m_pNext;		// ���̃I�u�W�F�N�g�ւ̃|�C���^
	SInfo m_Info;			// �������g�̏��
	SCatch m_Catch;		// �݂͂Ɋւ�����
	CWaist *m_pWaist;		// ��
	CCharacter *m_pBody;	// �㔼�g
	CCharacter *m_pLeg;		// �����g
	CScore *m_pScore;       // �X�R�A�ւ̃|�C���^
	int m_aSaveType[MAX_ITEM];
	float m_fRotMove;		// ���݂̊p�x
	float m_fRotDiff;		// �ړI�̊p�x
	float m_fRotDest;		// �p�x�v�Z
	float m_fGage;	// �E�p�Q�[�W
	bool m_bMove;			// �ړ��������ǂ���
	bool m_bJump;			// �W�����v
	bool m_bGoal;			// �S�[���t���O
	int m_nLife;			// �̗�
	int m_nId;				// ID
	int m_nNumItemCoin;
	int m_nNumItemBrecetet;
	int m_nNumItemCup;
	int m_nNumItemEmerald;
	int m_nNumItemDiamond;
	int m_nNumItemGold;
	int m_nNumItemJar;
	int m_nNumItemKunai;
	int m_nNumItemRing;
	int m_nNumItemScroll;
	int m_nNumItemShuriken;
	int m_nItemId;
	TYPE m_type;			// ���
	ACTION m_action;		// �A�N�V����
	int m_nItemCnt;		// 
	static int m_nNumCount;
	CCamera *m_pMyCamera;	// �����p�̃J����
	CUI *m_pUI;
	CGage *m_pGage;		// �E�p�Q�[�W
	CThrowItem *m_pThrowItem; // ���̏�ɏo��A�C�e���̃A�C�R��
	CHeadUI *m_pHeadUI;
};

#endif
