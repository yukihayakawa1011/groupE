//===============================================
//
// �G�̏��� [enemy.cpp]
// Author : Soma Ishihara (Base:Ibuki Okusada)
//
//===============================================
#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
#include "camera.h"
#include "Xfile.h"
#include "slow.h"
#include "texture.h"
#include "meshfield.h"
#include "Xfile.h"
#include "meshorbit.h"
#include "game.h"
#include "filter.h"
#include "object2D.h"
#include "meshwall.h"
#include "objectX.h"
#include "sound.h"
#include <assert.h>
#include "billboard.h"
#include "character.h"
#include "motion.h"
#include "sound.h"
#include "player.h"
#include "item.h"

//===============================================
// �}�N����`
//===============================================
#define MOVE	(2.0f)		// �ړ���
#define ENEMY_GRAVITY	(-0.9f)		//�G�d��
#define ENEMY_JUMP		(25.0f)		//�G�W�����v��
#define ROT_MULTI	(0.1f)	// �����␳�{��
#define WIDTH	(20.0f)		// ��
#define HEIGHT	(80.0f)	// ����
#define INER	(0.3f)		// ����
#define START_LIFE	(4)	// �����̗�
#define DAMAGE_INTERVAL	(10)
#define DEFAULT_ROTATE	(0.1f)		//�v���C���[�T�����̉�]��
#define SEARCH_LENGTH	(500.0f)	//�v���C���[�T���͈�
#define CHACE_LENGTH	(800.0f)	//�ǐՔ͈�
#define ATTACK_LENGTH	(50.0f)		//�U�����[�h�ɂ���͈�
#define ATTACK_COOLTIME	(60)		//�U���N�[���^�C��
#define ENEMY_VTX_MIN	D3DXVECTOR3(-20.0f,0.0f,-20.0f)
#define ENEMY_VTX_MAX	D3DXVECTOR3(20.0f,0.0f,20.0f)

#define FIX_ROT(x)				(fmodf(x + (D3DX_PI * 3), D3DX_PI * 2) - D3DX_PI)	//�p�x��-PI~PI�ɏC��
#define MINUS_GUARD(x)			((x < 0) ? 0 : x)

// �O���錾
CEnemy *CEnemy::m_pTop = NULL;	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
CEnemy *CEnemy::m_pCur = NULL;	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^
int CEnemy::m_nNumCount = 0;

//===============================================
// �R���X�g���N�^(�I�[�o�[���[�h)
//===============================================
CEnemy::CEnemy(const D3DXVECTOR3 pos)
{
	// �l���N���A����
	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fRotMove = 0.0f;
	m_fRotDiff = 0.0f;
	m_fRotDest = 0.0f;
	m_pObject = NULL;
	m_nLife = 0;
	m_nCounterAttack = ATTACK_COOLTIME;
	m_bChace = false;
	m_bJump = false;
	m_type = TYPE_NONE;
	m_nId = m_nNumCount;

	// �������g�����X�g�ɒǉ�
	if (m_pTop != NULL)
	{// �擪�����݂��Ă���ꍇ
		m_pCur->m_pNext = this;	// ���ݍŌ���̃I�u�W�F�N�g�̃|�C���^�ɂȂ���
		m_pPrev = m_pCur;
		m_pCur = this;	// �������g���Ō���ɂȂ�
	}
	else
	{// ���݂��Ȃ��ꍇ
		m_pTop = this;	// �������g���擪�ɂȂ�
		m_pCur = this;	// �������g���Ō���ɂȂ�
	}

	m_nNumCount++;
}

//===============================================
// �R���X�g���N�^(�I�[�o�[���[�h)
//===============================================
CEnemy::CEnemy(int nPriOrity)
{
	// �l���N���A����
	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fRotMove = 0.0f;
	m_fRotDiff = 0.0f;
	m_fRotDest = 0.0f;
	m_pObject = NULL;
	m_nLife = 0;
	m_nCounterAttack = ATTACK_COOLTIME;
	m_bChace = false;
	m_bJump = false;
	m_type = TYPE_NONE;
	m_nId = m_nNumCount;

	// �������g�����X�g�ɒǉ�
	if (m_pTop != NULL)
	{// �擪�����݂��Ă���ꍇ
		m_pCur->m_pNext = this;	// ���ݍŌ���̃I�u�W�F�N�g�̃|�C���^�ɂȂ���
		m_pPrev = m_pCur;
		m_pCur = this;	// �������g���Ō���ɂȂ�
	}
	else
	{// ���݂��Ȃ��ꍇ
		m_pTop = this;	// �������g���擪�ɂȂ�
		m_pCur = this;	// �������g���Ō���ɂȂ�
	}

	m_nNumCount++;
}

//===============================================
// �f�X�g���N�^
//===============================================
CEnemy::~CEnemy()
{
	
}

//===============================================
// ����������
//===============================================
HRESULT CEnemy::Init(void)
{
	if (nullptr == m_pObject)
	{
		m_pObject = CCharacter::Create(GetPosition(), GetRotation(), "data\\TXT\\motion_kidsboy.txt");
		m_pObject->SetShadow(true);
	}

	m_Info.state = STATE_APPEAR;
	m_type = TYPE_NONE;
	m_nLife = START_LIFE;

	return S_OK;
}

//===============================================
// ����������(�I�[�o�[���[�h)
//===============================================
HRESULT CEnemy::Init(const char *pBodyName, const char *pLegName)
{
	if (nullptr == m_pObject)
	{
		m_pObject = CCharacter::Create("data\\TXT\\motion_kidsboy.txt");
		m_pObject->GetMotion()->InitSet(0);
		m_pObject->SetShadow(true);
		m_pObject->SetDraw();
	}

	m_nLife = START_LIFE;
	m_type = TYPE_NONE;

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CEnemy::Uninit(void)
{
	// ���X�g���玩�����g���폜����
	if (m_pTop == this)
	{// ���g���擪
		if (m_pNext != NULL)
		{// �������݂��Ă���
			m_pTop = m_pNext;	// ����擪�ɂ���
			m_pNext->m_pPrev = NULL;	// ���̑O�̃|�C���^���o���Ă��Ȃ��悤�ɂ���
		}
		else
		{// ���݂��Ă��Ȃ�
			m_pTop = NULL;	// �擪���Ȃ���Ԃɂ���
			m_pCur = NULL;	// �Ō�����Ȃ���Ԃɂ���
		}
	}
	else if (m_pCur == this)
	{// ���g���Ō��
		if (m_pPrev != NULL)
		{// �������݂��Ă���
			m_pCur = m_pPrev;			// �O���Ō���ɂ���
			m_pPrev->m_pNext = NULL;	// �O�̎��̃|�C���^���o���Ă��Ȃ��悤�ɂ���
		}
		else
		{// ���݂��Ă��Ȃ�
			m_pTop = NULL;	// �擪���Ȃ���Ԃɂ���
			m_pCur = NULL;	// �Ō�����Ȃ���Ԃɂ���
		}
	}
	else
	{
		if (m_pNext != NULL)
		{
			m_pNext->m_pPrev = m_pPrev;	// ���g�̎��ɑO�̃|�C���^���o��������
		}
		if (m_pPrev != NULL)
		{
			m_pPrev->m_pNext = m_pNext;	// ���g�̑O�Ɏ��̃|�C���^���o��������
		}
	}

	if (nullptr != m_pObject){
		m_pObject->Uninit();
		m_pObject = NULL;
	}

	if (m_pObject != NULL)
	{
		m_pObject->Uninit();
		delete m_pObject;
		m_pObject = NULL;
	}

	m_nNumCount--;

	// �p��
	Release();
}

//===============================================
// �X�V����
//===============================================
void CEnemy::Update(void)
{
	// �O��̍��W���擾
	m_Info.posOld = GetPosition();

	StateSet();

	m_nCounterAttack--;

	if (m_Info.state != STATE_SPAWN)
	{
		// �G����
		Controller();
	}

	//// �J�����Ǐ]
	//CCamera* pCamera = CManager::GetInstance()->GetCamera();

	//// �Ǐ]����
	//pCamera->Pursue(GetPosition(), GetRotation());

#ifdef _DEBUG	//�f�o�b�O���[�h�̂ݕ\��

	CManager::GetInstance()->GetDebugProc()->Print("���� [%f, %f, %f] : ID [ %d]\n", GetRotation().x, GetRotation().y, GetRotation().z, m_nId);
	CManager::GetInstance()->GetDebugProc()->Print("�ʒu [%f, %f, %f]", GetPosition().x, GetPosition().y, GetPosition().z);
	CManager::GetInstance()->GetDebugProc()->Print("�̗� [ %d ]\n", m_nLife);

#endif // _DEBUG

	// �g�p�I�u�W�F�N�g�X�V
	if (nullptr != m_pObject) {
		m_pObject->SetPosition(m_Info.pos);
		m_pObject->SetRotation(m_Info.rot);
		m_pObject->Update();
	}
}

//===============================================
// ����
//===============================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, const char *pBodyName, const char *pLegName, const int nPriority)
{
	CEnemy *pPlayer = NULL;
	CXFile *pModelFile = CManager::GetInstance()->GetModelFile();

	// �G�̐���
	pPlayer = new CEnemy(nPriority);

	if (nullptr != pPlayer)
	{// �����ł����ꍇ
		// ����������
		pPlayer->Init(pBodyName, pLegName);

		// ���W�ݒ�
		pPlayer->SetPosition(pos);

		// �����ݒ�
		pPlayer->SetRotation(rot);

		pPlayer->m_fRotDest = rot.y;

		// �ړ��ʐݒ�
		pPlayer->SetMove(move);
	}
	else
	{// �����Ɏ��s�����ꍇ
		return NULL;
	}

	return pPlayer;
}

//===============================================
// ���쏈��
//===============================================
void CEnemy::Controller(void)
{
	D3DXVECTOR3 pos = GetPosition();	// ���W���擾
	D3DXVECTOR3 rot = GetRotation();	// �������擾
	m_fRotMove = rot.y;	//���݂̌������擾

	// ���쏈��
	{
		Move();		// �ړ�

		if (m_bChace == false)
		{
			Search();	// �T��
		}
		else
		{
			Chace();	// �ǐ�
		}
	}

	pos = GetPosition();	// ���W���擾

	float fGravity = ENEMY_GRAVITY * CManager::GetInstance()->GetSlow()->Get();
	m_Info.move.y += fGravity;
	pos.y += m_Info.move.y * CManager::GetInstance()->GetSlow()->Get();

	m_Info.move.x += (0.0f - m_Info.move.x) * INER;	//x���W
	m_Info.move.z += (0.0f - m_Info.move.z) * INER;	//x���W

	pos.x += m_Info.move.x * CManager::GetInstance()->GetSlow()->Get();
	pos.z += m_Info.move.z * CManager::GetInstance()->GetSlow()->Get();

	// ����
	Adjust();

	m_Info.pos = pos;
	m_bJump = true;

	// �N���Ƃ̓����蔻��
	float fHeight = CMeshField::GetHeight(m_Info.pos);
	if (m_Info.pos.y <= fHeight)
	{
		m_Info.pos.y = fHeight;
		m_bJump = false;
	}

	//�����蔻�菈���O�̈ʒu�L��
	pos = m_Info.pos;

	D3DXVECTOR3 vtxMax = D3DXVECTOR3(50.0f, 0.0f, 50.0f);
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);
	if (CObjectX::Collision(m_Info.pos, m_Info.posOld, m_Info.move, vtxMin, vtxMax, 0.3f))
	{
		m_bJump = false;
	}
	this->Collision();

	//�ǐՃ��[�h�ł���xz�ǂ��炩�����O����ω����Ă���
	if (m_bChace == true && (m_Info.pos.x != pos.x || m_Info.pos.z != pos.z))
	{
		//�W�����v����K�v�����邩�m�F
		CPlayer* pPlayerNear = SearchNearPlayer();

		if (CObjectX::CollisionCloss(pPlayerNear->GetPosition(), m_Info.pos))
		{
			m_Info.move.y = ENEMY_JUMP;
			m_bJump = true;
		}
	}
}

//===============================================
// �ړ�
//===============================================
void CEnemy::Move(void)
{
	//�G�̍X�V
	m_Info.move.x += sinf(m_fRotDest - D3DX_PI) * MOVE;
	m_Info.move.z += cosf(m_fRotDest - D3DX_PI) * MOVE;
}

//===============================================
// ��]
//===============================================
void CEnemy::Rotation(void)
{
	m_fRotDest = m_fRotMove - DEFAULT_ROTATE;
}

//===============================================
// �T��
//===============================================
void CEnemy::Search(void)
{
	float fLengthNear = FLT_MAX;
	CPlayer* pPlayerNear = SearchNearPlayer(&fLengthNear);

	if (pPlayerNear != nullptr && fLengthNear <= SEARCH_LENGTH)
	{//�v���C���[������
		m_bChace = true;
	}
	else
	{//�K���ɂ��邮��
		Rotation();	// ��]
	}
}

//===============================================
// �ǐ�
//===============================================
void CEnemy::Chace(void)
{
	float fLengthNear = FLT_MAX;
	CPlayer* pPlayerNear = SearchNearPlayer(&fLengthNear);

	if (pPlayerNear != nullptr && fLengthNear <= ATTACK_LENGTH)
	{//�U���͈�
		m_Info.move.x = 0.0f;
		m_Info.move.z = 0.0f;
		if (m_nCounterAttack <= 0)
		{//�N�[���^�C���I��
			pPlayerNear->Damage(1);
			m_nCounterAttack = ATTACK_COOLTIME;
		}
	}
	else if (pPlayerNear != nullptr && fLengthNear <= CHACE_LENGTH)
	{//�ǐՔ͈�
		D3DXVECTOR3 posPlayer = pPlayerNear->GetPosition();
		float aaa = atan2f(posPlayer.x - m_Info.pos.x, posPlayer.z - m_Info.pos.z);
		m_fRotDest = FIX_ROT(atan2f(posPlayer.x - m_Info.pos.x, posPlayer.z - m_Info.pos.z) + D3DX_PI);
	}
	else
	{
		m_bChace = false;
	}
}

//===============================================
// ���S����
//===============================================
void CEnemy::Death(void)
{
	// ���Ƃ����������iplayer����q�؁j
	for (int nCnt = 0; nCnt < 5; nCnt++)	//�񐔉�
	{
		CItem *pItem = CItem::Create(m_Info.pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\coin.x", CItem::TYPE_DROP);

		if (nullptr != pItem)
		{
			D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.04f;
			move.y = 18.0f;
			move.z = cosf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.04f;
			pItem->SetMove(move);
		}
	}

	//����
	Uninit();
}

//===============================================
// �G���m�����蔻��
//===============================================
void CEnemy::Collision(void)
{
	CEnemy *pObj = m_pTop;	// �擪�擾
	CXFile *pFile = CManager::GetInstance()->GetModelFile();
	bool bLand = false;	// ���n�������ۂ�

	//���u��
	D3DXVECTOR3 posTemp = m_Info.posOld;

	//X
	posTemp.x = m_Info.pos.x;
	pObj = m_pTop;
	while (pObj != NULL)
	{
		CEnemy *pObjNext = pObj->m_pNext;
		if (pObj != this)
		{
			pObj->CollisionCheck(posTemp, m_Info.posOld, m_Info.move, ENEMY_VTX_MIN, ENEMY_VTX_MAX);
		}

		pObj = pObjNext;
	}

	//Y
	posTemp.y = m_Info.pos.y;
	pObj = m_pTop;
	while (pObj != NULL)
	{
		CEnemy* pObjNext = pObj->m_pNext;
		if (pObj != this)
		{
			pObj->CollisionCheck(posTemp, m_Info.posOld, m_Info.move, ENEMY_VTX_MIN, ENEMY_VTX_MAX);
		}

		pObj = pObjNext;
	}

	//Z
	posTemp.z = m_Info.pos.z;
	pObj = m_pTop;
	while (pObj != NULL)
	{
		CEnemy* pObjNext = pObj->m_pNext;
		if (pObj != this)
		{
			pObj->CollisionCheck(posTemp, m_Info.posOld, m_Info.move, ENEMY_VTX_MIN, ENEMY_VTX_MAX);
		}

		pObj = pObjNext;
	}

	m_Info.pos = posTemp;
}

//===============================================
// �G�P�̓����蔻��
//===============================================
void CEnemy::CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, const float fRefMulti)
{
	//X
	if (pos.z + vtxMax.z > m_Info.pos.z + vtxMin.z
		&& pos.z + vtxMin.z < m_Info.pos.z + vtxMax.z)
	{//�͈͓��ɂ���
		if (posOld.x + vtxMin.x >= m_Info.pos.x + vtxMax.x
			&& pos.x + vtxMin.x < m_Info.pos.x + vtxMax.x)
		{//�E���獶�ɂ߂荞��
			move.x *= -1.0f;
			move.x *= fRefMulti;
			pos.x = m_Info.pos.x + vtxMax.x - vtxMin.x + 0.1f + move.x;
		}
		else if (posOld.x + vtxMax.x <= m_Info.pos.x + vtxMin.x
			&& pos.x + vtxMax.x > m_Info.pos.x + vtxMin.x)
		{//������E�ɂ߂荞��
		 //�ʒu��߂�
			move.x *= -1.0f;
			move.x *= fRefMulti;
			pos.x = m_Info.pos.x + vtxMin.x - vtxMax.x - 0.1f + move.x;
		}
	}

	//Z
	if (pos.x + vtxMax.x > m_Info.pos.x + vtxMin.x
		&& pos.x + vtxMin.x < m_Info.pos.x + vtxMax.x)
	{//�͈͓��ɂ���
		if (posOld.z + vtxMin.z >= m_Info.pos.z + vtxMax.z
			&& pos.z + vtxMin.z < m_Info.pos.z + vtxMax.z)
		{//�������O�ɂ߂荞��
		 //�ʒu��߂�
			move.z *= -1.0f;
			move.z *= fRefMulti;
			pos.z = m_Info.pos.z + vtxMax.z - vtxMin.z + 0.1f + move.z;
		}
		else if (posOld.z + vtxMax.z <= m_Info.pos.z + vtxMin.z
			&& pos.z + vtxMax.z > m_Info.pos.z + vtxMin.z)
		{//��O���牜�ɂ߂荞��
		 //�ʒu��߂�
			move.z *= -1.0f;
			move.z *= fRefMulti;
			pos.z = m_Info.pos.z + vtxMin.z - vtxMax.z - 0.1f + move.z;
		}
	}
}

//===============================================
// �߂��v���C���[�T��
//===============================================
CPlayer* CEnemy::SearchNearPlayer(float* pLength)
{
	CPlayer* pPlayer = CPlayer::GetTop();
	CPlayer* pPlayerNear = nullptr;
	float fLengthNear = FLT_MAX;

	while (pPlayer != nullptr)
	{
		if (pPlayer->GetLife() > 0)
		{//�����Ă���z���v��
			D3DXVECTOR3 posPlayer = pPlayer->GetPosition();
			float fLength = D3DXVec3Length(&(posPlayer - this->m_Info.pos));
			if (fLengthNear > fLength)
			{//��ԋ߂����
				pPlayerNear = pPlayer;
				fLengthNear = fLength;
			}
		}

		pPlayer = pPlayer->GetNext();
	}

	if (pLength != nullptr)
	{//�������~����
		*pLength = fLengthNear;
	}

	return pPlayerNear;	//�߂��v���C���[�̃|�C���^��Ԃ�
}

//===============================================
// ����
//===============================================
void CEnemy::Adjust(void)
{
	m_fRotDest = FIX_ROT(m_fRotDest);

	m_fRotDiff = m_fRotDest - m_fRotMove;	//�ڕW�܂ł̈ړ������̍���
	m_fRotDiff = FIX_ROT(m_fRotDiff);

	m_Info.rot.y += m_fRotDiff * ROT_MULTI;
	m_Info.rot.y = FIX_ROT(m_Info.rot.y);
}

//===============================================
// ��ԊǗ�
//===============================================
void CEnemy::StateSet(void)
{
	switch (m_Info.state)
	{
	case STATE_APPEAR:
	{

	}
		break;

	case STATE_NORMAL:
	{

	}
		break;

	case STATE_DAMAGE:
	{

	}
		break;

	case STATE_DEATH:
	{

	}
		break;

	case STATE_SPAWN:
	{

	}
		break;
	}
}

//===============================================
// �_���[�W����
//===============================================
void CEnemy::Damage(int nDamage) 
{ 
	int nOldLife = m_nLife;
	m_nLife = MINUS_GUARD(m_nLife - nDamage);

	if (m_nLife <= 0)
	{//��
		Death();
	}

	if (m_nLife != nOldLife)
	{
		m_Info.nStateCounter = DAMAGE_INTERVAL;
		m_Info.state = STATE_DAMAGE;
	}
}

//===============================================
// �̗͐ݒ�
//===============================================
void CEnemy::SetLife(int nLife)
{
	m_nLife = MINUS_GUARD(nLife);
}