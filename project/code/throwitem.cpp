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
	const int DEF_PRI = (7);	// �D�揇��
	const char* FILENAME[CThrowItem::TYPE_MAX] = {	// �e�N�X�`���t�@�C����
		"data\\TEXTURE\\arrow00.png",
		"data\\TEXTURE\\item_icon.png",
		"data\\TEXTURE\\frame.png",
		
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
// ����������
//==========================================================
HRESULT CThrowItem::Init(void)
{
	// �r���{�[�h����
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		m_apObject[nCount] = CObjectBillboard::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), DEF_PRI);
		m_apObject[nCount]->SetDraw(false);
		m_apObject[nCount]->SetAlphaText(false);
		m_apObject[nCount]->SetLighting(true);
		m_apObject[nCount]->SetZTest(false);
		m_apObject[nCount]->SetFusion(CObjectBillboard::FUSION_NORMAL);
		m_apObject[nCount]->BindTexture(CManager::GetInstance()->GetTexture()->Regist(FILENAME[nCount]));
	}
	
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
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		if (m_apObject[nCount] != nullptr)
		{
			// �I������
			m_apObject[nCount]->Uninit();

			// �g�p���Ă��Ȃ���Ԃɂ���
			m_apObject[nCount] = nullptr;
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

	if (CManager::GetInstance()->GetMode() == CScene::MODE_TUTORIAL || CManager::GetInstance()->GetMode() == CScene::MODE_GAME)
	{// �V�[�����`���[�g���A���܂��̓Q�[���̂Ƃ�

		for (int nCount = 0; nCount < TYPE_MAX; nCount++)
		{
			// �`�悷��
			m_apObject[nCount]->SetDraw();
		}
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

	if (m_apObject[TYPE_ITEM] != nullptr)
	{
		// ���W�ݒ�
		m_apObject[TYPE_ITEM]->SetSize(m_fPolyWidth, m_fPolyHeight);
	}

	if (m_apObject[TYPE_FRAME] != nullptr)
	{
		// ���W�ݒ�
		m_apObject[TYPE_FRAME]->SetSize(m_fPolyWidth - 50.0f, m_fPolyHeight );
	}

	if (m_apObject[TYPE_ARROW] != nullptr)
	{
		// ���W�ݒ�
		m_apObject[TYPE_ARROW]->SetSize(m_fPolyWidth - 15.0f, m_fPolyHeight - 10.0f);
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

	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		if (m_apObject[nCount] != nullptr)
		{
			if (nCount == TYPE_ARROW)
			{
				// ���W�ݒ�
				m_apObject[nCount]->SetPosition(D3DXVECTOR3(pos.x, pos.y - 20.0f, pos.z));
			}
			else
			{
				// ���W�ݒ�
				m_apObject[nCount]->SetPosition(D3DXVECTOR3(pos));
			}
		}
	}
}

//==========================================================
// �ǂ̃A�C�e����I�����Ă��邩
//==========================================================
void CThrowItem::SetItem(int nThrowItemID)
{
	// ���ݑI�����Ă���ԍ�
	m_nNowID = nThrowItemID;

	if (m_apObject[TYPE_ITEM] != nullptr)
	{
		m_apObject[TYPE_ITEM]->SetVtx(((float)(m_nNowID - 1) * 0.09f), 1.0f);
	}

	//if (m_pObject != nullptr)
	//{// �g�p����Ă����ꍇ

	// // �e�N�X�`�����W�ݒ�
	//	m_pObject->SetVtx(((float)(m_nNowID - 1) * 0.09f), 1.0f);
	//}
}