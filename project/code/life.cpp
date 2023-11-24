//==========================================================
//
// �T���v���^�X�N [sample_task.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "life.h"
#include "object2D.h"
#include "manager.h"
#include "texture.h"

// �}�N����`

//==========================================================
// �R���X�g���N�^
//==========================================================
CLife::CLife()
{
	// �l�̃N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_life = 6;
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CLife::~CLife()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CLife::Init(void)
{
	for (int nCnt = 0; nCnt < m_life; nCnt++)
	{
		if (m_pObject[nCnt] == NULL)
		{
			m_pObject[nCnt] = CObject2D::Create(7);

			if (nCnt % 2 == 0)
			{
				m_pObject[nCnt]->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\heartL_0.png"));
				m_pObject[nCnt]->SetPosition(D3DXVECTOR3(m_pos.x + (20.0f * nCnt), m_pos.y, m_pos.z));
				m_pObject[nCnt]->SetLength(25.0f, 50.0f);
			}
			else if (nCnt % 2 != 0)
			{
				m_pObject[nCnt]->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\heartR_0.png"));
				m_pObject[nCnt]->SetPosition(D3DXVECTOR3(m_pos.x + (20.0f * nCnt), m_pos.y, m_pos.z));
				m_pObject[nCnt]->SetLength(25.0f, 50.0f);
			}
		}
	}

	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CLife::Uninit(void)
{
	for (int nCnt = 0; nCnt < NUM_LIFE; nCnt++)
	{
		if (nullptr != m_pObject[nCnt]) {
			m_pObject[nCnt]->Uninit();
			m_pObject[nCnt] = NULL;
		}
	}

	Release();
}

//==========================================================
// �X�V����
//==========================================================
void CLife::Update(void)
{

}

//==========================================================
// ����
//==========================================================
CLife *CLife::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CLife *pLife = nullptr;

	pLife = new CLife;

	if (pLife != nullptr)
	{
		pLife->SetPosition(pos);

		pLife->SetRotation(rot);

		// ����������
		pLife->Init();
	}

	return pLife;
}