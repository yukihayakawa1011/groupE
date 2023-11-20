//==========================================================
//
// �A�C�e���{�b�N�X [itembox.cpp]
// Author : Soma Ishihara
//
//==========================================================
#include "itembox.h"
#include "spike.h"
#include "item.h"
#include "player.h"
#include "objectX.h"

//�ÓI�����o�ϐ�
CItemBox *CItemBox::m_pTop = nullptr;
CItemBox *CItemBox::m_pCur = nullptr;

// �}�N����`
#define COLLISION_RANGE	(70.0f)
#define EMISSION_CT		(90)

//==========================================================
// �R���X�g���N�^
//==========================================================
CItemBox::CItemBox()
{
	// �l�̃N���A
	m_pObj = nullptr;
	m_nCounter = 0;

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
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CItemBox::~CItemBox()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CItemBox::Init(void)
{
	m_pObj = CObjectX::Create(GetPosition(), GetRotation(), "data\\MODEL\\pot.x");
	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CItemBox::Uninit(void)
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

	ListOut();

	Release();
}

//==========================================================
// �X�V����
//==========================================================
void CItemBox::Update(void)
{
	m_nCounter--;
	if (m_nCounter < 0)
	{
		m_nCounter = 0;
	}
}

//==========================================================
// ����
//==========================================================
CItemBox *CItemBox::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CItemBox *pItemBox = nullptr;

	pItemBox = new CItemBox;

	if (pItemBox != nullptr)
	{
		// ����������
		pItemBox->SetPosition(pos);
		pItemBox->SetRotation(rot);
		pItemBox->Init();

		//�f�[�^�ݒ�
	}

	return pItemBox;
}

//==========================================================
// �r�o
//==========================================================
void CItemBox::Emission(void)
{
	int nRand = rand() % 2;

	if (nRand == 0)
	{
		CItem *pItem = CItem::Create(GetPosition(), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\coin.x", CItem::TYPE_COIN, CItem::STATE_DROP);

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
	else
	{
		CSpike::Create(GetPosition(), GetRotation(), 10.0f, 20.0f);
	}
}

//==========================================================
// �����蔻��
//==========================================================
bool CItemBox::CollisionCheck(D3DXVECTOR3 & pos, D3DXVECTOR3 & posOld, D3DXVECTOR3 & move, D3DXVECTOR3 & SetPos, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, int nAction, CGimmick ** ppGimmick)
{
	D3DXVECTOR3 ObjPos = GetPosition();

	// �͈͓��`�F�b�N
	float fLength = D3DXVec3Length(&(D3DXVECTOR3((pos.x - ObjPos.x), 0.0f, (pos.z - ObjPos.z))));

	if (fLength < COLLISION_RANGE && nAction == CPlayer::ACTION_ATK && m_nCounter <= 0)
	{// �͈͓�
		Emission();
		m_nCounter = EMISSION_CT;
	}

	return false;
}
