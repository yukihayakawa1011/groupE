//==========================================================
//
// �̂Ă�A�C�e�� [throwitem.cpp]
// Author : Ryosuke Ohhra
//
//==========================================================
#include "throwitem.h"
#include "billboard.h"
#include "manager.h"
#include "texture.h"
#include "player.h"

// �ÓI�����o�ϐ��錾
CPlayer **CThrowItem::m_ppPlayer = nullptr;

// �������O���
namespace {
	const int DEF_PRI = (3);	// �D�揇��
	const char* FILENAME[CThrowItem::TYPE_MAX] = {	// �e�N�X�`���t�@�C����
		"data\\TEXTURE\\item_icon1.png",
		"data\\TEXTURE\\item_icon0.png",
		"data\\TEXTURE\\item_icon2.png",
		"data\\TEXTURE\\item_icon4.png",
		"data\\TEXTURE\\item_icon3.png",
		"data\\TEXTURE\\item_icon5.png",
		"data\\TEXTURE\\item_icon6.png",
		"data\\TEXTURE\\item_icon8.png",
		"data\\TEXTURE\\item_icon10.png",
		"data\\TEXTURE\\item_icon7.png",
		"data\\TEXTURE\\item_icon9.png",
	};
}

//==========================================================
// �R���X�g���N�^
//==========================================================
CThrowItem::CThrowItem()
{
	// �l�̃N���A
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++) {
		m_apObject[nCnt] = nullptr;
	}
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CThrowItem::~CThrowItem()
{

}

//==========================================================
// ����
//==========================================================
CThrowItem * CThrowItem::Create(D3DXVECTOR3 * pPos, const float fUpHeight, const float fPolyWidth, const float fPolyHeight)
{
	CThrowItem *pThrowItem = nullptr;

	pThrowItem = new CThrowItem;

	if (pThrowItem != nullptr)
	{
		// ����������
		pThrowItem->Init();

		// �e�̐ݒ�
		pThrowItem->SetParent(pPos);

		// ���΍��W�̍�����ݒ�
		pThrowItem->SetUpHeight(fUpHeight);

		// �|���S���T�C�Y��ݒ�
		pThrowItem->SetPolySize(fPolyWidth, fPolyHeight);

		// ���W��ݒ�
		pThrowItem->SetMixPosition();
	}

	return pThrowItem;
}

//==========================================================
// ����������
//==========================================================
HRESULT CThrowItem::Init(void)
{
	// �I�u�W�F�N�g�̐���
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++) {
		m_apObject[nCnt] = CObjectBillboard::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), DEF_PRI + nCnt);
		m_apObject[nCnt]->SetAlphaText(false);
		m_apObject[nCnt]->SetLighting(true);
		m_apObject[nCnt]->SetZTest(false);
		m_apObject[nCnt]->SetFusion(CObjectBillboard::FUSION_NORMAL);
		m_apObject[nCnt]->BindTexture(CManager::GetInstance()->GetTexture()->Regist(FILENAME[nCnt]));
	}

	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CThrowItem::Uninit(void)
{
	// �I�u�W�F�N�g�̏I������
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++) {
		if (m_apObject[nCnt] != nullptr) {
			m_apObject[nCnt]->Uninit();
			m_apObject[nCnt] = nullptr;
		}
	}

	// �J��
	Release();
}

//==========================================================
// �X�V����
//==========================================================
void CThrowItem::Update(void)
{
	// ���W�̍X�V
	SetMixPosition();

	CPlayer *pPlayer = CPlayer::GetTop();

	while (pPlayer != nullptr)
	{
		CPlayer *pPlayerNext = pPlayer->GetNext();	// ����ێ�

		int nOldId, nId, nNextId;

		// ���ݑI�����Ă���ԍ�
		nId = pPlayer->GetThrowItemId();

		// �I�����Ă���ԍ��̈�O
		nOldId = nId - 1;

		// �I�����Ă���ԍ��̎�
		nNextId = nId + 1;

		if (nOldId < 0)
		{
			nOldId = 10;
		}

		if (nNextId > 10)
		{
			nNextId = 0;
		}

		// �T�C�Y��ݒ�
		{
			if (m_apObject[nOldId] == nullptr || m_apObject[nId] == nullptr || m_apObject[nNextId] == nullptr) {
				return;
			}

			m_apObject[nOldId]->SetSize(m_fPolyWidth, m_fPolyHeight);

			m_apObject[nId]->SetSize(m_fPolyWidth, m_fPolyHeight);

			m_apObject[nNextId]->SetSize(m_fPolyWidth, m_fPolyHeight);
		}

		pPlayer = pPlayerNext;
	}
}

//==========================================================
// ���ƍ����̓K��
//==========================================================
void CThrowItem::SetPolySize(const float fWidth, const float fHeight)
{
	// ���̐ݒ�
	{
		m_fPolyWidth = fWidth;
		if (m_fPolyWidth < 0.0f) {	// �l���}�C�i�X
			m_fPolyWidth = 0.0f;
		}
	}

	// �����̐ݒ�
	{
		m_fPolyHeight = fHeight;
		if (m_fPolyHeight < 0.0f) {	// �l���}�C�i�X
			m_fPolyHeight = 0.0f;
		}
	}

	// �I�u�W�F�N�g�ɓK��������
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++) {
		if (m_apObject[nCnt] == nullptr) {	// �g�p����Ă��Ȃ�
			continue;
		}

		// ���W�ݒ�
		m_apObject[nCnt]->SetSize(m_fPolyWidth, m_fPolyHeight);
	}
}

//==========================================================
// �ݒ荂���ƍ��������W��ݒ�
//==========================================================
void CThrowItem::SetMixPosition(void)
{
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��̍��W
	if (m_pPos != nullptr) {	// �e�����݂��Ă���
		pos = *m_pPos;
	}
	pos.y += m_fUpHeight;	// �ݒ肳�ꂽ�������グ��

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++) {
		if (m_apObject[nCnt] == nullptr) {	// �g�p����Ă��Ȃ�
			continue;
		}

		// ���W�ݒ�
		m_apObject[nCnt]->SetPosition(D3DXVECTOR3(pos));
	}
}