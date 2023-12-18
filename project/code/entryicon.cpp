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
		"data\\TEXTURE\\entry0%d.png"
		"data\\TEXTURE\\entry1%d.png"
	};
	const char* FILEEXT = ".txt";				// �t�@�C���̊g���q
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

	for (int i = 0; i < NUM_PLAYER; i++)
	{
		m_apObject[i] = nullptr;
	}
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
HRESULT CEntryIcon::Init(void)
{
	for (int nCount = 0; nCount < NUM_PLAYER; nCount++)
	{
		if (m_apObject[nCount] == nullptr)
		{// �g�p���Ă����ꍇ

			m_apObject[nCount] = CObject2D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 7);
			m_apObject[nCount]->SetDraw(true);
			char aTexPass[256] = "";
			sprintf(&aTexPass[0], FILEPASS[STATE_STANDBY], nCount);

			m_apObject[nCount]->BindTexture(CManager::GetInstance()->GetTexture()->Regist(aTexPass));
		}
	}

	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CEntryIcon::Uninit(void)
{

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
	return nullptr;
}

//==========================================================
// ����
//==========================================================
CEntryIcon * CEntryIcon::Create(D3DXVECTOR3 * pPos, D3DXMATRIX * Matrix, const float fUpHeight, const float fPolyWidth, const float fPolyHeight)
{
	return nullptr;
}

//==========================================================
// �T�C�Y�ݒ�
//==========================================================
void CEntryIcon::SetPolySize(const float fWidth, const float fHeight)
{

}
