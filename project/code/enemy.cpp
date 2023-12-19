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
#include "gimmick.h"
#include "model.h"
#include "object3DFan.h"
#include "waist.h"
#include "point.h"
#include "particle.h"

//�������O���
namespace
{
	const float MOVE = 1.3f;			// �ړ���
	const float GRAVITY = -0.9f;		// �G�d��
	const float JUMP = 20.0f;			// �G�W�����v��
	const float ROT_MULTI = 0.1f;		// �����␳�{��
	const float INER = 0.3f;			// ����
	const float BLOW_INER = 0.1f;		// ������΂�������
	const int START_LIFE = 4;			// �����̗�
	const int DAMAGE_INTERVAL = 80;		// �_���[�W�t�^�Ԋu
	const int APPEAR_INTERVAL = 120;	// �o�����ɂȂ��Ă���Ԋu
	const float DEFAULT_ROTATE = 0.1f;	// �v���C���[�T�����̉�]��
	const float SEARCH_LENGTH = 300.0f;	// �v���C���[�T���͈�
	const float SEARCH_RADIUS = 0.3f;	// �v���C���[�T���p�x
	const float CHACE_LENGTH = 500.0f;	// �ǐՔ͈�
	const float ATTACK_LENGTH = 50.0f;	// �U�����[�h�ɂ���͈�
	const int ATTACK_COOLTIME = 60;		// �U���N�[���^�C��
	const float NEXTPOINT_LENGTH = 100.0f;	//���̃|�C���g�ɐ؂�ւ��鋗��
	const D3DXVECTOR3 ENEMY_VTX_MIN = D3DXVECTOR3(-20.0f, 0.0f, -20.0f);	// �����蔻��Ȃǂ̃T�C�Y
	const D3DXVECTOR3 ENEMY_VTX_MAX = D3DXVECTOR3(20.0f, 0.0f, 20.0f);
	const float HIT_RANGE = 100.0f;		// �U����������͈�
	const int DROP_COIN = 3;			// �R�C���̃h���b�v��
	const char* BODY_FILENAME = "data\\TXT\\enemy\\motion_ninjabody.txt";	// �㔼�g�̃��[�V�����t�@�C���p�X
	const char* LEG_FILENAME = "data\\TXT\\enemy\\motion_ninjaleg.txt";		// �����g�̃��[�V�����t�@�C���p�X
	const int RETURN_TIME_LIMIT = 120;	//�A���ė���܂ł̐�������
	const int HEADPARTS_IDX = (1);
}

//===============================================
// �}�N����`
//===============================================
#define FIX_ROT(x)				(fmodf(x + (D3DX_PI * 3), D3DX_PI * 2) - D3DX_PI)	//�p�x��-PI~PI�ɏC��
#define MINUS_GUARD(x)			((x < 0) ? 0 : x)

// �O���錾
CEnemy *CEnemy::m_pTop = nullptr;	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
CEnemy *CEnemy::m_pCur = nullptr;	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^
int CEnemy::m_nNumCount = 0;

//===============================================
// �R���X�g���N�^
//===============================================
CEnemy::CEnemy()
{
	// �l���N���A����
	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fRotMove = 0.0f;
	m_fRotDiff = 0.0f;
	m_fRotDest = 0.0f;
	m_pBody = nullptr;
	m_nLife = 0;
	m_nCounterAttack = ATTACK_COOLTIME;
	m_bChace = false;
	m_bJump = false;
	m_type = TYPE_NONE;
	m_nId = m_nNumCount;
	m_pChase = nullptr;
	m_nPointID = -1;
	m_nPointNum = 0;

	// �������g�����X�g�ɒǉ�
	if (m_pTop != nullptr)
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
	if (nullptr == m_pBody)
	{
		m_pBody = CCharacter::Create(GetPosition(), GetRotation(), "data\\TXT\\motion_kidsboy.txt");
		m_pBody->SetShadow(true);
	}

	if (nullptr == m_pFov)
	{
		m_pFov = CObject3DFan::Create(m_Info.pos, m_Info.rot, SEARCH_LENGTH, SEARCH_RADIUS * D3DX_PI, 8);
		m_pFov->SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.4f));
	}

	m_Info.state = STATE_APPEAR;
	m_type = TYPE_NONE;
	m_nLife = START_LIFE;

	// ���̃p�[�e�B�N������
	CModel *pModel = m_pLeg->GetParts(0);
	CParticle::Create(D3DXVECTOR3(pModel->GetMtx()->_41, pModel->GetMtx()->_42, pModel->GetMtx()->_43), CEffect::TYPE_SMAKE);

	return S_OK;
}

//===============================================
// ����������(�I�[�o�[���[�h)
//===============================================
HRESULT CEnemy::Init(const char *pBodyName, const char *pLegName)
{
	// ���̐���
	if (m_pWaist == NULL)
	{
		m_pWaist = new CWaist;
		m_pWaist->SetParent(&m_Info.mtxWorld);
		m_pWaist->SetMatrix();
	}

	// ���̂̐ݒ�
	//if (pBodyName != NULL)
	{// �t�@�C���������݂��Ă���
		m_pBody = CCharacter::Create(BODY_FILENAME);
		m_pBody->SetParent(m_pWaist->GetMtxWorld());
		m_pBody->SetShadow(true);
		m_pBody->SetDraw();

		if (m_pBody->GetMotion() != NULL)
		{
			// �������[�V�����̐ݒ�
			m_pBody->GetMotion()->InitSet(MOTION_NEUTRAL);
		}
	}

	// �����g�̐ݒ�
	//if (pLegName != NULL)
	{// �t�@�C���������݂��Ă���
		m_pLeg = CCharacter::Create(LEG_FILENAME);
		m_pLeg->SetParent(m_pWaist->GetMtxWorld());
		m_pLeg->SetShadow(true);
		m_pLeg->SetDraw();

		if (m_pLeg->GetMotion() != NULL)
		{
			// �������[�V�����̐ݒ�
			m_pLeg->GetMotion()->InitSet(MOTION_NEUTRAL);
		}
	}

	// ���̍��������킹��
	if (m_pLeg != NULL)
	{// �r���g�p����Ă���ꍇ
		CModel *pModel = m_pLeg->GetParts(0);	// ���p�[�c���擾

		if (pModel != NULL)
		{// �p�[�c�����݂���ꍇ
			D3DXVECTOR3 pos = pModel->GetPosition();	// ���f���̑��Έʒu���擾

			// ������ݒ�
			m_pWaist->SetHeight(pos);

			// ���̃��f���̈ʒu��ύX
			pModel->SetPosition(pos);
		}
	}

	if (nullptr == m_pFov && CManager::GetInstance()->GetMode() != CScene::MODE_TITLE)
	{
		m_pFov = CObject3DFan::Create(m_Info.pos, m_Info.rot, SEARCH_LENGTH, SEARCH_RADIUS * D3DX_PI, 8);
		m_pFov->SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.6f));
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
		if (m_pNext != nullptr)
		{// �������݂��Ă���
			m_pTop = m_pNext;	// ����擪�ɂ���
			m_pNext->m_pPrev = nullptr;	// ���̑O�̃|�C���^���o���Ă��Ȃ��悤�ɂ���
		}
		else
		{// ���݂��Ă��Ȃ�
			m_pTop = nullptr;	// �擪���Ȃ���Ԃɂ���
			m_pCur = nullptr;	// �Ō�����Ȃ���Ԃɂ���
		}
	}
	else if (m_pCur == this)
	{// ���g���Ō��
		if (m_pPrev != nullptr)
		{// �������݂��Ă���
			m_pCur = m_pPrev;			// �O���Ō���ɂ���
			m_pPrev->m_pNext = nullptr;	// �O�̎��̃|�C���^���o���Ă��Ȃ��悤�ɂ���
		}
		else
		{// ���݂��Ă��Ȃ�
			m_pTop = nullptr;	// �擪���Ȃ���Ԃɂ���
			m_pCur = nullptr;	// �Ō�����Ȃ���Ԃɂ���
		}
	}
	else
	{
		if (m_pNext != nullptr)
		{
			m_pNext->m_pPrev = m_pPrev;	// ���g�̎��ɑO�̃|�C���^���o��������
		}
		if (m_pPrev != nullptr)
		{
			m_pPrev->m_pNext = m_pNext;	// ���g�̑O�Ɏ��̃|�C���^���o��������
		}
	}

	// ���̂̏I��
	if (m_pBody != nullptr) {
		m_pBody->Uninit();
		delete m_pBody;
		m_pBody = nullptr;
	}

	// �����g�̏I��
	if (m_pLeg != nullptr) {
		m_pLeg->Uninit();
		delete m_pLeg;
		m_pLeg = nullptr;
	}

	// ���̔p��
	if (m_pWaist != nullptr) {
		delete m_pWaist;
		m_pWaist = nullptr;
	}

	if (nullptr != m_pFov)
	{
		m_pFov->Uninit();
		m_pFov = nullptr;
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

	m_nCounterAttack--;

	if (m_Info.state < STATE_DAMAGE || m_Info.state >= STATE_BLOW)
	{
		// �G����
		Controller();
	}

	// ���[�V�����ݒ�
	MotionSet();

	// �}�g���b�N�X�ݒ�
	SetMatrix();

	CManager::GetInstance()->GetDebugProc()->Print("�̗� [ %d ]\n", m_nLife);

	// �g�p�I�u�W�F�N�g�X�V
	if (nullptr != m_pFov)
	{
		m_pFov->SetPosition(m_Info.pos);
		m_pFov->SetRotation(m_Info.rot + D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	}

	// �K�w�\���ݒ�
	BodySet();

	// ��ԑJ��
	StateSet();

	if (m_pLeg != nullptr)
	{// �g�p����Ă���ꍇ
		CModel *pModel = m_pLeg->GetParts(0);

		pModel->SetCurrentPosition(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	}
}

//===============================================
// ����
//===============================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, const char *pBodyName, const char *pLegName, const int nPointID)
{
	CEnemy *pEnemy = nullptr;

	// �G�̐���
	pEnemy = new CEnemy();

	if (nullptr != pEnemy)
	{// �����ł����ꍇ
		// ����������
		pEnemy->Init(pBodyName, pLegName);
		pEnemy->m_nPointID = nPointID;

		// ���W�ݒ�
		pEnemy->SetPosition(pos);

		// �����ݒ�
		pEnemy->SetRotation(rot);

		pEnemy->m_fRotDest = rot.y;

		// �ړ��ʐݒ�
		pEnemy->SetMove(move);

		//���o��
		CParticle::Create(pos, CEffect::TYPE_SMAKE);
	}
	else
	{// �����Ɏ��s�����ꍇ
		return nullptr;
	}

	return pEnemy;
}

//===============================================
// ���쏈��
//===============================================
void CEnemy::Controller(void)
{
	D3DXVECTOR3 pos = GetPosition();	// ���W���擾
	D3DXVECTOR3 rot = GetRotation();	// �������擾
	m_fRotMove = rot.y;	//���݂̌������擾
	float fIner = INER;

	// ���쏈��
	{
		if (m_Info.state != STATE_BLOW) {	// ������΂��ȊO
			Move();		// �ړ�
		}
		else {
			fIner = BLOW_INER;
		}

		if (m_bChace == false)
		{
			Search();	// �T��
		}
		else
		{
			Chace();	// �ǐ�
		}
	}

	if (CManager::GetInstance()->GetMode() != CScene::MODE_TUTORIAL && CManager::GetInstance()->GetMode() != CScene::MODE_TITLE)
	{// �`���[�g���A���ȊO

		pos = GetPosition();	// ���W���擾

		float fGravity = GRAVITY * CManager::GetInstance()->GetSlow()->Get();
		m_Info.move.y += fGravity;
		pos.y += m_Info.move.y * CManager::GetInstance()->GetSlow()->Get();

		m_Info.move.x += (0.0f - m_Info.move.x) * fIner;	//x���W
		m_Info.move.z += (0.0f - m_Info.move.z) * fIner;	//x���W

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

		D3DXVECTOR3 vtxMax = D3DXVECTOR3(50.0f, 120.0f, 50.0f);
		D3DXVECTOR3 vtxMin = D3DXVECTOR3(-50.0f, -10.0f, -50.0f);
		if (CObjectX::Collision(m_Info.pos, m_Info.posOld, m_Info.move, vtxMin, vtxMax, 0.3f))
		{
			m_bJump = false;
		}

		CGimmick::Collision(m_Info.pos, m_Info.posOld, m_Info.move, D3DXVECTOR3(0.0f, 0.0f, 0.0f), vtxMin, vtxMax, 0);

		//�ǐՃ��[�h�ł���xz�ǂ��炩�����O����ω����Ă���
		if (m_bChace == true && m_bJump == false && (m_Info.pos.x != pos.x || m_Info.pos.z != pos.z))
		{
			//�W�����v����K�v�����邩�m�F
			CPlayer* pPlayerNear = SearchNearPlayer(FLT_MAX);

			if (pPlayerNear != nullptr && CObjectX::CollisionCloss(pPlayerNear->GetPosition(), m_Info.pos))
			{
				m_Info.move.y = JUMP;
				m_bJump = true;
			}
		}

		//�G���m�����蔻��
		this->Collision();
	}
	else if (CManager::GetInstance()->GetMode() == CScene::MODE_TITLE && m_nPointID == ExPattern::POINTID_TITLE)
	{
		pos.z += 10.0f * CManager::GetInstance()->GetSlow()->Get();

		m_Info.pos = pos;
		m_fRotDest = D3DX_PI;

		Adjust();

		// �N���Ƃ̓����蔻��
		float fHeight = CMeshField::GetHeight(m_Info.pos);
		if (m_Info.pos.y <= fHeight)
		{
			m_Info.pos.y = fHeight;
			m_bJump = false;
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
// �|�C���g�ړ�
//===============================================
void CEnemy::Trace(void)
{
	CPoint* pPoint = CPoint::GetTop();
	D3DXVECTOR3 posPoint;

	//�|�C���g�ʒu�擾
	for (int cnt = 0; cnt < m_nPointID; cnt++)
	{
		pPoint = pPoint->GetNext();
	}
	if (pPoint != nullptr)
	{
		posPoint = pPoint->GetPoint(m_nPointNum);

		//�p�x����
		m_fRotDest = FIX_ROT(atan2f(posPoint.x - m_Info.pos.x, posPoint.z - m_Info.pos.z) + D3DX_PI);

		//�߂��Ȃ����玟�̃|�C���g
		if (D3DXVec3Length(&(posPoint - m_Info.pos)) < NEXTPOINT_LENGTH)
		{
			m_nPointNum = (m_nPointNum + 1) % pPoint->GetRegistPointNum();

			//���[�v���ԃJ�E���g���Ȃ�J�E���g��~
			if (m_nLimitReturn > 0)
			{
				m_nLimitReturn = -1;
			}
		}

		//�J�E���g���Ȃ�J�E���g���炷
		if (m_nLimitReturn > 0)
		{
			m_nLimitReturn--;
			if (m_nLimitReturn == 0)
			{//�h����
				Warp();
			}
		}
	}
	else
	{//�ꉞ�ʂ�ۂ̎��͂��邮�邷��悤�ɂ���
		m_nPointID = ExPattern::POINTID_FREE;
	}
}

//===============================================
// �T��
//===============================================
void CEnemy::Search(void)
{
	float fLengthNear = FLT_MAX;
	CPlayer* pPlayerNear = SearchNearPlayer(SEARCH_RADIUS, &fLengthNear);

	if (pPlayerNear != nullptr && fLengthNear <= SEARCH_LENGTH && pPlayerNear->GetAction() != CPlayer::ACTION_HENGE)
	{//�v���C���[�����Ă����肪�B��g�̏p
		m_bChace = true;
		if (nullptr != m_pFov)
		{
			m_pFov->SetLength(CHACE_LENGTH);
			m_pFov->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.4f));

			CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_SEEK);
		}
	}
	else
	{
		if (m_nPointID != ExPattern::POINTID_FREE && m_nPointID != ExPattern::POINTID_TITLE)
		{//�ړ��p�^�[������
			Trace();
		}
		else if (m_nPointID == ExPattern::POINTID_FREE)
		{//�K���ɂ��邮��
			Rotation();	// ��]
		}
	}
}

//===============================================
// �ǐ�
//===============================================
void CEnemy::Chace(void)
{
	CPoint* pPoint = CPoint::GetTop();
	int nPointNear = -1;
	float fLengthNear = FLT_MAX;
	CPlayer* pPlayerNear = SearchNearPlayer(SEARCH_RADIUS, &fLengthNear);

	if (pPlayerNear != nullptr && fLengthNear <= ATTACK_LENGTH)
	{//�U���͈�
		m_Info.move.x = 0.0f;
		m_Info.move.z = 0.0f;
		if (m_nCounterAttack <= 0)
		{//�N�[���^�C���I��
			if (m_Info.state == STATE_NORMAL) {	// �ʏ��Ԃ̂Ƃ��̂�
				pPlayerNear->Damage(1);				
			}

			m_nCounterAttack = ATTACK_COOLTIME;
		}
	}
	else if (pPlayerNear != nullptr && fLengthNear <= CHACE_LENGTH)
	{//�ǐՔ͈�
		D3DXVECTOR3 posPlayer = pPlayerNear->GetPosition();
		m_fRotDest = FIX_ROT(atan2f(posPlayer.x - m_Info.pos.x, posPlayer.z - m_Info.pos.z) + D3DX_PI);
	}
	else
	{
		//�T����Ԃɂ���
		m_bChace = false;
		m_pFov->SetLength(SEARCH_LENGTH);
		m_pFov->SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.4f));

		//��ԋ߂��|�C���g�Ɉړ�����悤�ɂ���
		//�|�C���g�擾
		for (int cnt = 0; cnt < m_nPointID; cnt++)
		{
			pPoint = pPoint->GetNext();
		}
		if (pPoint != nullptr)
		{
			//�߂��̒T��
			fLengthNear = FLT_MAX;
			for (int cnt = 0; cnt < pPoint->GetRegistPointNum(); cnt++)
			{
				D3DXVECTOR3 posPoint = pPoint->GetPoint(cnt);
				float fLength = D3DXVec3Length(&(posPoint - m_Info.pos));
				if (fLengthNear > fLength)
				{
					fLengthNear = fLength;
					nPointNear = cnt;
				}
			}
			//���̈ړ����ݒ�
			m_nPointNum = nPointNear;

			//���̋O���ɖ߂�܂ł̐������Ԑݒ�
			m_nLimitReturn = RETURN_TIME_LIMIT;
		}
		else
		{//�ꉞ�ʂ�ۂ̎��͂��邮�邷��悤�ɂ���
			m_nPointID = ExPattern::POINTID_FREE;
		}
	}
}

//===============================================
// ���S����
//===============================================
void CEnemy::Death(void)
{
	// ���Ƃ����������iplayer����q�؁j
	for (int nCnt = 0; nCnt < DROP_COIN; nCnt++)
	{
		CItem *pItem = CItem::Create(m_Info.pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItem::TYPE_COIN, CItem::STATE_DROP);

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

	CModel *pModel = m_pLeg->GetParts(0);  // ���̃p�[�c

	// ���̃p�[�e�B�N������
	CParticle::Create(D3DXVECTOR3(pModel->GetMtx()->_41, pModel->GetMtx()->_42, pModel->GetMtx()->_43), CEffect::TYPE_BLACKSMAKE);

	//����
	Uninit();
}

//===============================================
// �G���m�����蔻��
//===============================================
void CEnemy::Collision(void)
{
	CEnemy *pObj = m_pTop;	// �擪�擾

	//���u��
	D3DXVECTOR3 posTemp = m_Info.posOld;

	//X
	posTemp.x = m_Info.pos.x;
	CollisionAllEnemy(posTemp);

	//Y
	posTemp.y = m_Info.pos.y;
	CollisionAllEnemy(posTemp);

	//Z
	posTemp.z = m_Info.pos.z;
	CollisionAllEnemy(posTemp);

	m_Info.pos = posTemp;
}

//===============================================
// �G���ׂĂɓ����蔻��`�F�b�N
//===============================================
D3DXVECTOR3 CEnemy::CollisionAllEnemy(D3DXVECTOR3 pos)
{
	CEnemy *pObj = m_pTop;	// �擪�擾
	while (pObj != nullptr)
	{
		CEnemy *pObjNext = pObj->m_pNext;
		if (pObj != this)
		{
			pObj->CollisionCheck(pos, m_Info.posOld, m_Info.move, ENEMY_VTX_MIN, ENEMY_VTX_MAX);
		}

		pObj = pObjNext;
	}

	return pos;
}

//===============================================
// ���A�p���[�v�i�h�����j
//===============================================
void CEnemy::Warp(void)
{
	//�|�C���g�擾
	CPoint* pPoint = CPoint::GetTop();
	for (int cnt = 0; cnt < m_nPointID; cnt++)
	{
		pPoint = pPoint->GetNext();
	}

	//�ړ��i�������̂𐶐��j����
	CEnemy* pNewEnemy = Create(pPoint->GetPoint(m_nPointNum), this->m_Info.rot, this->m_Info.move, nullptr, nullptr, this->m_nPointID);
	pNewEnemy->m_nPointNum = m_nPointNum + 1;
	pNewEnemy->m_nLimitReturn = -1;

	//�h�����i���̓G��j���j����
	this->Uninit();
	CParticle::Create(this->m_Info.pos, CEffect::TYPE_SMAKE);


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
CPlayer* CEnemy::SearchNearPlayer(float fRadiusRest, float* pLength)
{
	CPlayer* pPlayer = CPlayer::GetTop();
	CPlayer* pPlayerNear = nullptr;
	float fLengthNear = FLT_MAX;

	while (pPlayer != nullptr)
	{
		if (pPlayer->GetLife() > 0)
		{//�����Ă���z���v��
			D3DXVECTOR3 posPlayer = pPlayer->GetPosition();
			D3DXVECTOR3 vecPos = posPlayer - this->m_Info.pos;
			float fLength = D3DXVec3Length(&vecPos);
			D3DXVec3Normalize(&vecPos, &vecPos);
			D3DXVECTOR3 vecGaze = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			vecGaze.x = cosf(this->m_Info.rot.y + 0.5f * D3DX_PI);
			vecGaze.z = -sinf(this->m_Info.rot.y + 0.5f * D3DX_PI);

			float fRadius = D3DXVec3Dot(&vecGaze, &vecPos) / (D3DXVec3Length(&vecGaze) * D3DXVec3Length(&vecPos));
			if (fLengthNear > fLength && fRadius >= 1.0f - fRadiusRest 
				&& CObjectX::CollisionCloss(posPlayer,this->m_Info.pos) == false && CGimmick::CollisionCloss(posPlayer, this->m_Info.pos) == false)
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
	m_Info.nStateCounter--;

	if (m_Info.nStateCounter > 0)
	{
		return;
	}

	switch (m_Info.state)
	{
	case STATE_APPEAR:
	{
		m_Info.state = STATE_NORMAL;
	}
		break;

	case STATE_NORMAL:
	{

	}
		break;

	case STATE_DAMAGE:
	{
		m_Info.state = STATE_NORMAL;
	}
		break;

	case STATE_DEATH:
	{
		if (m_pBody == nullptr) {
			return;
		}

		if (m_pBody->GetMotion() == nullptr) {
			return;
		}

		if (m_pLeg == nullptr) {
			return;
		}

		if (m_pLeg->GetMotion() == nullptr) {
			return;
		}

		if (m_pBody->GetMotion()->GetEnd() && m_pBody->GetMotion()->GetNowKey() == m_pBody->GetMotion()->GetNowNumKey() - 1
			&& m_pBody->GetMotion()->GetNowMotion() == MOTION_DEATH) {	// ���[�V�����I�������S���[�V����
			Death();
		}
		else if (m_pBody->GetMotion()->GetEnd() && m_pBody->GetMotion()->GetNowKey() == m_pBody->GetMotion()->GetNowNumKey() - 1
			&& m_pBody->GetMotion()->GetNowMotion() == MOTION_DOWN) {	// ���[�V�����I�������S���[�V����
			m_pBody->GetMotion()->BlendSet(MOTION_DEATH);
			m_pLeg->GetMotion()->BlendSet(MOTION_DEATH);
		}
	}

		break;

	case STATE_SPAWN:
	{
		m_Info.state = STATE_APPEAR;
		m_Info.nStateCounter = APPEAR_INTERVAL;
	}
		break;
		
	case STATE_BLOW:
	{
		m_Info.state = STATE_APPEAR;
		m_Info.nStateCounter = APPEAR_INTERVAL;
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

	// �G�t�F�N�g�̐���
	if (m_pBody != nullptr) {
		if (m_pBody->GetParts(HEADPARTS_IDX) != nullptr) {
			D3DXVECTOR3 pos = D3DXVECTOR3(m_pBody->GetParts(HEADPARTS_IDX)->GetMtx()->_41, 
				m_pBody->GetParts(HEADPARTS_IDX)->GetMtx()->_42, 
				m_pBody->GetParts(HEADPARTS_IDX)->GetMtx()->_43);
			CParticle::Create(pos, CEffect::TYPE_HIT);
		}
	}

	if (m_nLife <= 0)
	{//��
		m_Info.state = STATE_DEATH;
		CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_DEATH);

		if (m_pBody == nullptr)
		{
			return;
		}

		if (m_pBody->GetMotion() == nullptr) {
			return;
		}

		m_pBody->GetMotion()->Set(MOTION_DOWN);

		if (m_pLeg == nullptr) {
			return;
		}

		if(m_pLeg->GetMotion() == nullptr){
			return;
		}

		m_pLeg->GetMotion()->Set(MOTION_DOWN);

		return;
	}

	if (m_nLife != nOldLife)
	{
		CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_DAMAGE);
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

//===============================================
// �U���̃q�b�g�m�F
//===============================================
bool CEnemy::HitCheck(D3DXVECTOR3 pos, float fRange, int nDamage)
{
	bool m_bValue = false;
	if (m_Info.state != STATE_NORMAL) {
		return m_bValue;
	}

	if (m_pBody == nullptr) {
		return m_bValue;
	}

	CXFile *pFile = CManager::GetInstance()->GetModelFile();
	D3DXVECTOR3 ObjPos = GetPosition();
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(0.0f, 
		m_pBody->GetParts(1)->GetMtx()->_42 - ObjPos.y + pFile->GetMax(m_pBody->GetParts(1)->GetId()).y, 
		0.0f);
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(0.0f, -10.0f, 0.0f);

	if (pos.y >= ObjPos.y + vtxMax.y || pos.y <= ObjPos.y - vtxMin.y) {	// �����͈͊O
		return m_bValue;
	}

	// �͈͓��`�F�b�N
	float fLength =
		sqrtf((pos.x - ObjPos.x) * (pos.x - ObjPos.x)
			+ (pos.z - ObjPos.z) * (pos.z - ObjPos.z));

	if (fLength > HIT_RANGE + fRange) {		// �͈͊O
		return m_bValue;
	}

	m_bValue = true;
	Damage(nDamage);

	return m_bValue;
}

//===============================================
// ���[�V�����ݒ�
//===============================================
void CEnemy::MotionSet(void)
{
	if (m_Info.state == STATE_DEATH) {	// ���S���
		return;
	}

	if (m_pBody == nullptr) {	// ���̖���
		return;
	}

	if (m_pBody->GetMotion() == nullptr) {	// ���[�V��������
		return;
	}

	if (m_pLeg == nullptr) {	// �����g����
		return;
	}

	if(m_pLeg->GetMotion() == nullptr){	// ���[�V��������
		return;
	}

	if (m_Info.state == STATE_DAMAGE) {	// �_���[�W���
		m_pBody->GetMotion()->Set(MOTION_DAMAGE);
		m_pLeg->GetMotion()->Set(MOTION_DAMAGE);
	}
	else if (m_Info.state == STATE_BLOW) {	// �_���[�W���
		m_pBody->GetMotion()->Set(MOTION_DAMAGE);
		m_pLeg->GetMotion()->Set(MOTION_DAMAGE);
	}
	else if (m_nCounterAttack > 0) {	// �U����
		m_pBody->GetMotion()->Set(MOTION_ATK);
		m_pLeg->GetMotion()->Set(MOTION_ATK);
	}
	else if (m_bJump) {	// �W�����v���
		m_pBody->GetMotion()->BlendSet(MOTION_JUMP);
		m_pLeg->GetMotion()->BlendSet(MOTION_JUMP);
	}
	else if (m_bChace) {	// �`�F�C�X��
		m_pBody->GetMotion()->BlendSet(MOTION_CHASEMOVE);
		m_pLeg->GetMotion()->BlendSet(MOTION_CHASEMOVE);
	}
	else {	// �ҋ@���
		if (m_pBody->GetMotion()->GetEnd()) {	// ���[�V�������I�����Ă���
			m_pBody->GetMotion()->BlendSet(MOTION_MOVE);
		}

		if (m_pLeg->GetMotion()->GetEnd()) {	// ���[�V�������I�����Ă���
			m_pLeg->GetMotion()->BlendSet(MOTION_MOVE);
		}

		if (m_pLeg->GetMotion()->GetNowMotion() == MOTION_MOVE && 
			m_pLeg->GetMotion()->GetNowFrame() == 0 && 
			(m_pLeg->GetMotion()->GetNowKey() == 0 || m_pLeg->GetMotion()->GetNowKey() == 2))
		{
			CParticle::Create(m_Info.pos, CEffect::TYPE_WALK);
		}
	}
}

//===============================================
// �g�p�K�w�\���̐ݒ�
//===============================================
void CEnemy::BodySet(void)
{
	// �����g�X�V
	if (m_pLeg != nullptr)
	{// �g�p����Ă���ꍇ
		m_pLeg->Update();

		// ���̐ݒ�
		if (m_pWaist != nullptr)
		{
			CModel *pModel = m_pLeg->GetParts(0);

			// ���̍������U
			m_pWaist->SetPosition(m_pWaist->GetSetPosition() + pModel->GetCurrentPosition());
			m_pWaist->SetMatrix();
		}
	}

	// ���̍X�V
	if (m_pBody != nullptr)
	{// �g�p����Ă���ꍇ
		m_pBody->Update();
	}
}

//===============================================
// �}�g���b�N�X�ݒ�
//===============================================
void CEnemy::SetMatrix(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�ւ̃|�C���^���擾
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_Info.mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Info.rot.y, m_Info.rot.x, m_Info.rot.z);
	D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);
	D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_Info.mtxWorld);
}

//===============================================
// ������΂����
//===============================================
void CEnemy::Blow(void) {
	m_Info.nStateCounter = DAMAGE_INTERVAL;
	m_Info.state = STATE_BLOW;
}