//==========================================================
//
// �܂��т� [spike.cpp]
// Author : Soma Ishihara
//
//==========================================================
#include "spike.h"
#include "manager.h"
#include "objectX.h"
#include "slow.h"
#include "meshfield.h"
#include "player.h"

// �}�N����`
#define SPIKE_GRAVITY	(-0.9f)		//�G�d��
#define INER	(0.12f)		// ����
#define SPIKE_LIFE		(180)	//�̗́i���t��1�_���[�W�j

//�ÓI�����o�ϐ�
CSpike *CSpike::m_pTop = NULL;	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
CSpike *CSpike::m_pCur = NULL;	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^
int CSpike::m_nNumCount = 0;

//==========================================================
// �R���X�g���N�^
//==========================================================
CSpike::CSpike()
{
	m_info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_info.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_info.nLife = 0;

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

	//�����₷
	m_nNumCount++;
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CSpike::~CSpike()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CSpike::Init(void)
{
	m_pObj = CObjectX::Create(m_info.pos, m_info.rot, "data\\MODEL\\spike.x");
	m_pObj->SetEnableCollision(false);
	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CSpike::Uninit(void)
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

	if (nullptr != m_pObj) {
		m_pObj->Uninit();
		m_pObj = NULL;
	}

	//�����炷
	m_nNumCount--;

	//�j��
	Release();
}

//==========================================================
// �X�V����
//==========================================================
void CSpike::Update(void)
{
	D3DXVECTOR3 pos = m_info.pos;
	m_info.posOld = m_info.pos;

	//�ړ�
	float fGravity = SPIKE_GRAVITY * CManager::GetInstance()->GetSlow()->Get();
	m_info.move.y += fGravity;
	pos.y += m_info.move.y * CManager::GetInstance()->GetSlow()->Get();

	m_info.move.x += (0.0f - m_info.move.x) * INER;	//x���W
	m_info.move.z += (0.0f - m_info.move.z) * INER;	//x���W

	pos.x += m_info.move.x * CManager::GetInstance()->GetSlow()->Get();
	pos.z += m_info.move.z * CManager::GetInstance()->GetSlow()->Get();

	m_info.pos = pos;

	// �N���Ƃ̓����蔻��
	float fHeight = CMeshField::GetHeight(m_info.pos);
	if (m_info.pos.y <= fHeight)
	{
		m_info.pos.y = fHeight;
		this->Collision();
	}

	//�����蔻��
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(20.0f, 0.0f, 20.0f);
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-20.0f, 0.0f, -20.0f);

	CObjectX::Collision(m_info.pos, m_info.posOld, m_info.move, vtxMin, vtxMax, 0.3f);
	this->CollisionCloss();

	//�̗͐ݒ�
	m_info.nLife--;

	if (m_info.nLife <= 0)
	{//���S���Ȃ�
		Uninit();
	}

	// �g�p�I�u�W�F�N�g�X�V
	if (nullptr != m_pObj) {
		m_pObj->SetPosition(m_info.pos);
		m_pObj->SetRotation(m_info.rot);
		m_pObj->Update();
	}
}

//==========================================================
// ����
//==========================================================
CSpike *CSpike::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float move)
{
	CSpike *pSpike = nullptr;

	pSpike = new CSpike;

	if (pSpike != nullptr)
	{
		// ����������
		pSpike->Init();

		//�ʒu�ݒ�
		pSpike->SetPosition(pos);
		pSpike->SetRotation(rot);

		//�ړ��ʂ̐ݒ�
		D3DXVECTOR3 movev3 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		movev3.x = sinf(rot.y) * move + (rand() % 11 - 5);
		movev3.y = 10.0f + (rand() % 11 - 5);
		movev3.z = -cosf(rot.y) * move + (rand() % 11 - 5);
		pSpike->SetMove(movev3);

		//�̗͐ݒ�
		pSpike->SetLife(SPIKE_LIFE);
	}

	return pSpike;
}

//==========================================================
// �����蔻��(�ʉߒ��i�O�ρj)
//==========================================================
void CSpike::CollisionCloss(void)
{
	CPlayer* pPlayer = CPlayer::GetTop();

	while (pPlayer != nullptr)
	{
		CPlayer* pPlayerNext = pPlayer->GetNext();
		D3DXVECTOR3 vtxPlayerMax = D3DXVECTOR3(50.0f, 50.0f, 50.0f);
		D3DXVECTOR3 vtxPlayerMin = D3DXVECTOR3(-50.0f, -50.0f, -50.0f);
		D3DXVECTOR3 pos = pPlayer->GetPosition();

		D3DXVECTOR3 posPoint[4] =
		{
			D3DXVECTOR3(pos.x + vtxPlayerMin.x,0.0f,pos.z + vtxPlayerMin.z),
			D3DXVECTOR3(pos.x + vtxPlayerMax.x,0.0f,pos.z + vtxPlayerMin.z),
			D3DXVECTOR3(pos.x + vtxPlayerMax.x,0.0f,pos.z + vtxPlayerMax.z),
			D3DXVECTOR3(pos.x + vtxPlayerMin.x,0.0f,pos.z + vtxPlayerMax.z)
		};

		D3DXVECTOR3 vecMove, vecLine;
		D3DXVECTOR3 vecToPos, vecToPosOld;
		float fAreaA = 1.0f, fAreaB = 1.1f;

		for (int cnt = 0; cnt < 4; cnt++)
		{
			vecMove = m_info.pos - m_info.posOld;
			vecLine = posPoint[(cnt + 1) % 4] - posPoint[cnt];	//���E���x�N�g��
			vecToPos = m_info.pos - posPoint[cnt];
			vecToPos.y = 0.0f;
			vecToPosOld = m_info.posOld - posPoint[cnt];
			vecToPosOld.y = 0.0f;

			//�ʐϋ��߂�
			fAreaA = (vecToPos.z * vecMove.x) - (vecToPos.x * vecMove.z);
			fAreaB = (vecLine.z * vecMove.x) - (vecLine.x * vecMove.z);

			if ((vecLine.z * vecToPosOld.x) - (vecLine.x * vecToPosOld.z) >= 0.0f && (vecLine.z * vecToPos.x) - (vecLine.x * vecToPos.z) < 0.0f)
			{
				if (fAreaA / fAreaB >= 0.0f && fAreaA / fAreaB <= 1.0f)
				{//������
					pPlayer->Damage(1);
					Uninit();
					return;	//���ł������ߏI��
				}
			}
		}

		pPlayer = pPlayerNext;
	}
}

//==========================================================
// �����蔻��(�����Ă�)
//==========================================================
void CSpike::Collision(void)
{
	CPlayer* pPlayer = CPlayer::GetTop();

	while (pPlayer != nullptr)
	{
		CPlayer* pPlayerNext = pPlayer->GetNext();

		D3DXVECTOR3 posPlayer = pPlayer->GetPosition();
		D3DXVECTOR3 vtxPlayerMax = D3DXVECTOR3(50.0f, 50.0f, 50.0f);
		D3DXVECTOR3 vtxPlayerMin = D3DXVECTOR3(-50.0f, -50.0f, -50.0f);
		D3DXVECTOR3 vtxObjMax = D3DXVECTOR3(20.0f, 20.0f, 20.0f);
		D3DXVECTOR3 vtxObjMin = D3DXVECTOR3(-20.0f, -20.0f, -20.0f);

		if (m_info.pos.x + vtxObjMax.x > posPlayer.x + vtxPlayerMin.x
			&& m_info.pos.x + vtxObjMin.x < posPlayer.x + vtxPlayerMax.x
			&& m_info.pos.y + vtxObjMax.y > posPlayer.y + vtxPlayerMin.y
			&& m_info.pos.y + vtxObjMin.y < posPlayer.y + vtxPlayerMax.y
			&& m_info.pos.z + vtxObjMax.z > posPlayer.z + vtxPlayerMin.z
			&& m_info.pos.z + vtxObjMin.z < posPlayer.z + vtxPlayerMax.z)
		{//�͈͓��ɂ���
			pPlayer->Damage(1);
			Uninit();
		}

		pPlayer = pPlayerNext;
	}
}
