//==========================================================
//
// サンプルタスク [sample_task.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "life.h"
#include "object2D.h"
#include "manager.h"
#include "texture.h"

// マクロ定義

//==========================================================
// コンストラクタ
//==========================================================
CLife::CLife()
{
	// 値のクリア
}

//==========================================================
// デストラクタ
//==========================================================
CLife::~CLife()
{

}

//==========================================================
// 初期化処理
//==========================================================
HRESULT CLife::Init(void)
{
	for (int nCnt = 0; nCnt < NUM_LIFE; nCnt++)
	{
		m_pObject[nCnt] = CObject2D::Create(7);
	}

	m_pObject[0]->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\heartL_0.png"));
	m_pObject[0]->SetPosition(D3DXVECTOR3(m_pos.x - 10.0f,m_pos.y,m_pos.z));
	m_pObject[0]->SetLength(25.0f, 50.0f);
	m_pObject[1]->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\heartR_0.png"));
	m_pObject[1]->SetPosition(D3DXVECTOR3(m_pos.x + 10.0f, m_pos.y, m_pos.z));
	m_pObject[1]->SetLength(25.0f, 50.0f);

	return S_OK;
}

//==========================================================
// 終了処理
//==========================================================
void CLife::Uninit(void)
{
	Release();
}

//==========================================================
// 更新処理
//==========================================================
void CLife::Update(void)
{

}

//==========================================================
// 生成
//==========================================================
CLife *CLife::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CLife *pLife = nullptr;

	pLife = new CLife;

	if (pLife != nullptr)
	{
		pLife->SetPosition(pos);

		pLife->SetRotation(rot);

		// 初期化処理
		pLife->Init();
	}

	return pLife;
}