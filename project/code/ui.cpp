//==========================================================
//
// �T���v���^�X�N [sample_task.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "ui.h"
#include "object2D.h"
#include "manager.h"
#include "texture.h"

// �}�N����`

//==========================================================
// �R���X�g���N�^
//==========================================================
CUI::CUI()
{
	// �l�̃N���A
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CUI::~CUI()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CUI::Init(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_pObject[nCnt] = CObject2D::Create();
	}

	m_pObject[0]->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\frame0.png"));
	m_pObject[0]->SetPosition(m_pos);
	m_pObject[0]->SetRotation(m_rot);
	m_pObject[0]->SetLength(300.0f, 150.0f);

	m_pObject[1]->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\money0.png"));
	m_pObject[1]->SetPosition(D3DXVECTOR3(m_pos.x + 50.0f,m_pos.y + 45.0f,m_pos.z));
	m_pObject[1]->SetRotation(m_rot);
	m_pObject[1]->SetLength(50.0f, 25.0f);

	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CUI::Uninit(void)
{
	Release();
}

//==========================================================
// �X�V����
//==========================================================
void CUI::Update(void)
{
	//�T�C�Y�̐ݒ�
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_pObject[nCnt]->SetVtx();
	}
}

//==========================================================
// ����
//==========================================================
CUI *CUI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CUI *pUI = nullptr;

	pUI = new CUI;

	if (pUI != nullptr)
	{
		pUI->SetPosition(pos);
		pUI->SetRotation(rot);

		// ����������
		pUI->Init();
	}	

	return pUI;
}