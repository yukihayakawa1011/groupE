//===============================================
//
// 数字全般の処理 [number.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "score.h"
#include "object2D.h"
#include "texture.h"
#include "manager.h"

// マクロ定義
#define MAX_WIDTHPATTERN	(10)	// パターン数

//===============================================
// コンストラクタ
//===============================================
CScore::CScore()
{
	// 値をクリアする
	m_nIdx = 0;

	for (int nCount = 0; nCount < NUM_SCORE; nCount++)
	{
		m_apNumber[nCount] = nullptr;
	}
}

//===============================================
// デストラクタ
//===============================================
CScore::~CScore()
{

}

//===============================================
// 初期化処理
//===============================================
HRESULT CScore::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	for (int nCount = 0; nCount < NUM_SCORE; nCount++)
	{
		if (m_apNumber[nCount] == nullptr)
		{// 使用されていない場合

			// 生成
			m_apNumber[nCount] = CNumber::Create(D3DXVECTOR3(pos.x + nCount * 50.0f, pos.y , pos.z), fWidth, fHeight);

			if (m_apNumber[nCount] != nullptr)
			{// 使用されている場合

				// 初期化処理
				m_apNumber[nCount]->Init(pos, fWidth, fHeight);
			}
		}
	}

	return S_OK;
}

//===============================================
// 初期化処理
//===============================================
HRESULT CScore::Init()
{
	for (int nCount = 0; nCount < NUM_SCORE; nCount++)
	{
		if (m_apNumber[nCount] == nullptr)
		{// 使用されていない場合

			// 生成
			m_apNumber[nCount] = CNumber::Create();

			if (m_apNumber[nCount] != nullptr)
			{// 使用されている場合

				// 初期化処理
				m_apNumber[nCount]->Init();
			}
		}
	}

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CScore::Uninit(void)
{
	for (int nCount = 0; nCount < NUM_SCORE; nCount++)
	{
		if (m_apNumber[nCount] != nullptr)
		{// 使用されていない場合

			// 終了処理
			m_apNumber[nCount]->Uninit();

			// 使用されていない状態にする
			m_apNumber[nCount] = nullptr;
		}
	}
}

//===============================================
// 更新処理
//===============================================
void CScore::Update(void)
{
	for (int nCount = 0; nCount < NUM_SCORE; nCount++)
	{
		if (m_apNumber[nCount] != nullptr)
		{// 使用されていない場合

			// 更新処理
			m_apNumber[nCount]->Update();
		}
	}
}

//===============================================
// 描画処理
//===============================================
void CScore::Draw(void)
{
	//if (m_pObject2D != NULL)
	//{// 使用されている場合
	//	// 描画処理
	//	m_pObject2D->Draw();
	//}
}

//===============================================
// 生成
//===============================================
CScore *CScore::Create(void)
{
	CScore *pNum = NULL;

	if (pNum != NULL)
	{// 使用されていない場合
		pNum = new CScore;

		if (pNum != NULL)
		{// 使用されている場合

			// 初期化処理
			pNum->Init();
		}
	}

	return pNum;
}

//===============================================
// 生成
//===============================================
CScore *CScore::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CScore *pNum = NULL;

	if (pNum == NULL)
	{// 使用されていない場合
		pNum = new CScore;

		if (pNum != NULL)
		{// 使用されている場合

			// 初期化処理
			pNum->Init(pos, fWidth, fHeight);
		}
	}

	return pNum;
}