//==========================================================
//
// �`���[�g���A���̃G���g���[�̃A�C�R�� [entryicon.cpp]
// Author : Ryosuke Ohara
//
//==========================================================
#include "entryicon.h"
#include "object2D.h"
#include "texture.h"
#include "manager.h"

// �������O���
namespace
{
	const char* FILEPASS[2] = 
	{
		"data\\TEXTURE\\tutorial_icon0%d.png",
		"data\\TEXTURE\\tutorial_icon1%d.png",
	};
	const int FILEPASS_SIZE = (200);	// �t�@�C���̃p�X�T�C�Y
}

//==========================================================
// �R���X�g���N�^
//==========================================================
CEntryIcon::CEntryIcon()
{
	// �l���N���A
	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_Info.state = STATE_STANDBY;
	m_Info.fPolyWidth = 0.0f;
	m_Info.fPolyHeight = 0.0f;
	m_Info.bEntry = false;
	m_pObject = nullptr;
	m_nIdxPlayer = -1;
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CEntryIcon::~CEntryIcon()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CEntryIcon::Init(D3DXVECTOR3 pos)
{
	if (m_pObject == nullptr)
	{// �g�p���Ă����ꍇ

		m_pObject = CObject2D::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 7);
		m_pObject->SetDraw(true);
		char aTexPass[256] = "";
		sprintf(&aTexPass[0], FILEPASS[STATE_STANDBY], m_nIdxPlayer);
		m_pObject->BindTexture(CManager::GetInstance()->GetTexture()->Regist(aTexPass));
	}

	return S_OK;
}

//==========================================================
// ����������
//==========================================================
HRESULT CEntryIcon::Init(void)
{
	if (m_pObject == nullptr)
	{// �g�p���Ă����ꍇ

		m_pObject = CObject2D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 7);
		m_pObject->SetDraw(true);
		char aTexPass[256] = "";
		sprintf(&aTexPass[0], FILEPASS[STATE_STANDBY], m_nIdxPlayer);
		m_pObject->BindTexture(CManager::GetInstance()->GetTexture()->Regist(aTexPass));
	}
	
	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CEntryIcon::Uninit(void)
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
void CEntryIcon::Update(void)
{

}

//==========================================================
// ����
//==========================================================
CEntryIcon * CEntryIcon::Create(void)
{
	CEntryIcon *pEntryIcon = nullptr;

	pEntryIcon = new CEntryIcon;

	if (pEntryIcon != nullptr)
	{
		pEntryIcon->m_Info.state = STATE_STANDBY;
		pEntryIcon->m_nIdxPlayer = 0;
		pEntryIcon->Init();
	}

	return pEntryIcon;
}

//==========================================================
// ����
//==========================================================
CEntryIcon * CEntryIcon::Create(D3DXVECTOR3 Pos, const int nIdx, const float fPolyWidth, const float fPolyHeight)
{
	CEntryIcon *pEntryIcon = nullptr;

	pEntryIcon = new CEntryIcon;

	if (pEntryIcon != nullptr)
	{
		pEntryIcon->m_Info.state = STATE_STANDBY;
		pEntryIcon->m_nIdxPlayer = nIdx;
		pEntryIcon->Init(Pos);
		pEntryIcon->SetPolySize(fPolyWidth, fPolyHeight);
	}

	return pEntryIcon;
}

//==========================================================
// �T�C�Y�ݒ�
//==========================================================
void CEntryIcon::SetPolySize(const float fWidth, const float fHeight)
{
	// ���̐ݒ�
	{
		m_Info.fPolyWidth = fWidth;
		if (m_Info.fPolyWidth < 0.0f) {	// �l���}�C�i�X
			m_Info.fPolyWidth = 0.0f;
		}
	}

	// �����̐ݒ�
	{
		m_Info.fPolyHeight = fHeight;
		if (m_Info.fPolyWidth < 0.0f) {	// �l���}�C�i�X
			m_Info.fPolyWidth = 0.0f;
		}
	}

	if (m_pObject != nullptr)
	{// �g�p���Ă����ꍇ

	 // ���W�ݒ�
		m_pObject->SetSize(m_Info.fPolyWidth, m_Info.fPolyHeight);
	}
}
