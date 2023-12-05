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
#include "number.h"

// �������O���
namespace {
	const int DEF_PRI = (3);	// �D�揇��
	const char* FILENAME[CThrowItem::TYPE_MAX] = {	// �e�N�X�`���t�@�C����
		"data\\TEXTURE\\item_icon1.png",
		"data\\TEXTURE\\item_icon0.png",
		"data\\TEXTURE\\item_icon2.png",
		"data\\TEXTURE\\item_icon3.png",
		"data\\TEXTURE\\item_icon4.png",
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

	m_pObject = nullptr;

	for (int nCnt = 0; nCnt < MAX_ITEM; nCnt++) {
		m_pNumber[nCnt] = nullptr;
	} 

	m_nBeforeID = 0;
	m_nNowID = 0;
	m_nNextID = 0;
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
// �ǂ̃A�C�e����I�����Ă��邩
//==========================================================
void CThrowItem::SetItem(int nThrowItemID)
{
	// ���ݑI�����Ă���ԍ�
	m_nNowID = nThrowItemID;

	if (m_pObject != nullptr)
	{// �g�p����Ă����ꍇ

		// �e�N�X�`�����W�ݒ�
		m_pObject->SetVtx(((float)(m_nNowID - 1) * 0.09f), 1.0f);
	}
}

//==========================================================
// ����������
//==========================================================
HRESULT CThrowItem::Init(void)
{
	// �r���{�[�h����
	m_pObject = CObjectBillboard::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), DEF_PRI);
	m_pObject->SetDraw();
	m_pObject->SetAlphaText(false);
	m_pObject->SetLighting(true);
	m_pObject->SetZTest(false);
	m_pObject->SetFusion(CObjectBillboard::FUSION_NORMAL);
	m_pObject->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\item_icon.png"));

	// ��������
	/*for (int nCount = 0; nCount < MAX_ITEM; nCount++)
	{
		m_pNumber[nCount] = CNumber::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f, 20.0f);
	}*/
	
	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CThrowItem::Uninit(void)
{
	if (m_pObject != nullptr) { // �g�p����Ă����ꍇ

		// �I������
		m_pObject->Uninit();

		// �g�p���Ă��Ȃ���Ԃɂ���
		m_pObject = nullptr;
	}

	for (int nCount = 0; nCount < MAX_ITEM; nCount++)
	{
		if (m_pNumber[nCount] != nullptr)
		{// �g�p����Ă����ꍇ

			// �I������
			m_pNumber[nCount]->Uninit();

			// �g�p���Ă��Ȃ���Ԃɂ���
			m_pNumber[nCount] = nullptr;
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

	if (m_pObject != nullptr)
	{
		// ���W�ݒ�
		m_pObject->SetSize(m_fPolyWidth, m_fPolyHeight);
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

	if (m_pObject != nullptr)
	{
		// ���W�ݒ�
		m_pObject->SetPosition(D3DXVECTOR3(pos));
	}
}