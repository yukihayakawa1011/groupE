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
	m_pObject = CObject2D::Create();

	m_pObject->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\frame0.png"));
	m_pObject->SetPosition(m_pos);
	m_pObject->SetRotation(m_rot);
	m_pObject->SetLength(300.0f, 150.0f);

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
	m_pObject->SetVtx();
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