//==========================================================
//
// �m���}��UI [quataui.cpp]
// Author : Ryosuke Ohara
//
//==========================================================
#include "quataui.h"
#include "object2D.h"
#include "manager.h"
#include "texture.h"
#include "life.h"

// �������O���
namespace {
	const int DEF_PRI = (7);	// �D�揇��
	const char* FILENAME[CQuataUI::TYPE_MAX] = {	// �e�N�X�`���t�@�C����
		"data\\TEXTURE\\quata000.png",
		"data\\TEXTURE\\quata001.png",
		"data\\TEXTURE\\quata002.png",

	};
}

//==========================================================
// �R���X�g���N�^
//==========================================================
CQuataUI::CQuataUI()
{
	// �l�̃N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_nNumPlayer = 0;
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CQuataUI::~CQuataUI()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CQuataUI::Init(void)
{
	if (m_pObject == nullptr)
	{// �g�p����Ă��Ȃ��ꍇ


	}

	return S_OK;
}

//==========================================================
// ����������
//==========================================================
HRESULT CQuataUI::Init(float fWidth, float fHeight)
{
	if (m_pObject == nullptr)
	{// �g�p����Ă��Ȃ��ꍇ

		m_pObject = CObject2D::Create(7);
		m_pObject->BindTexture(CManager::GetInstance()->GetTexture()->Regist(FILENAME[m_type]));
		m_pObject->SetPosition(m_pos);
		m_pObject->SetSize(fWidth, fHeight);
	}

	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CQuataUI::Uninit(void)
{
	if (m_pObject != nullptr)
	{
		m_pObject->Uninit();
		m_pObject = nullptr;
	}

	Release();
}

//==========================================================
// �X�V����
//==========================================================
void CQuataUI::Update(void)
{
	
}

//==========================================================
// ����
//==========================================================
CQuataUI *CQuataUI::Create(D3DXVECTOR3 pos, QUATATYPE type, float fWidth, float fHeight)
{
	CQuataUI *pUI = nullptr;

	pUI = new CQuataUI;

	if (pUI != nullptr)
	{
		pUI->SetPosition(pos);
		pUI->SetType(type);
		// ����������
		pUI->Init(fWidth, fHeight);
	}

	return pUI;
}