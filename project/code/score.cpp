//===============================================
//
// 数字全般の処理 [score.cpp]
// Author : Ryosuke Ohhara
//
//===============================================
#include "score.h"
#include "object2D.h"
#include "number.h"

// 定数定義
namespace
{
	const int MAX_WIDTHPATTERN = 10;	// パターン数
	const float POLYSIZE = (25.0f);	// ポリゴンのサイズ
}

//===============================================
// コンストラクタ
//===============================================
CScore::CScore()
{
	// 値をクリアする
	m_nIdx = 0;
	m_nNumScore = 0;

	for (int nCount = 0; nCount < NUM_SCORE; nCount++)
	{
		m_apNumber[nCount] = nullptr;  // 使用していない状態にする
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
			m_apNumber[nCount] = CNumber::Create(D3DXVECTOR3(pos.x + nCount * POLYSIZE, pos.y, pos.z), fWidth, fHeight);

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
		{// 使用していない場合

			// 生成
			m_apNumber[nCount] = CNumber::Create();

			if (m_apNumber[nCount] != nullptr)
			{// 使用されていた場合

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
		{// 使用されていた場合

			// 終了処理
			m_apNumber[nCount]->Uninit();

			// 使用していない状態にする
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
		{// 使用されている場合

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

//===============================================
//スコア加算処理
//===============================================
void CScore::AddScore(int nScore)
{
	m_nNumScore += nScore;

	m_apNumber[0]->SetIdx(m_nNumScore % 100000000 / 10000000);
	m_apNumber[1]->SetIdx(m_nNumScore % 10000000 / 1000000);
	m_apNumber[2]->SetIdx(m_nNumScore % 1000000 / 100000);
	m_apNumber[3]->SetIdx(m_nNumScore % 100000 / 10000);
	m_apNumber[4]->SetIdx(m_nNumScore % 10000 / 1000);
	m_apNumber[5]->SetIdx(m_nNumScore % 1000 / 100);
	m_apNumber[6]->SetIdx(m_nNumScore % 100 / 10);
	m_apNumber[7]->SetIdx(m_nNumScore % 10 / 1);

	/*for (int nCount = 0; nCount < NUM_SCORE; nCount++)
	{
		m_apNumber[nCount]->SetIdx(m_nNumScore);
	}*/
}

//===============================================
//スコア減算処理
//===============================================
void CScore::LowerScore(int nScore)
{
	m_nNumScore -= nScore;

	m_apNumber[0]->SetIdx(m_nNumScore % 100000000 / 10000000);
	m_apNumber[1]->SetIdx(m_nNumScore % 10000000 / 1000000);
	m_apNumber[2]->SetIdx(m_nNumScore % 1000000 / 100000);
	m_apNumber[3]->SetIdx(m_nNumScore % 100000 / 10000);
	m_apNumber[4]->SetIdx(m_nNumScore % 10000 / 1000);
	m_apNumber[5]->SetIdx(m_nNumScore % 1000 / 100);
	m_apNumber[6]->SetIdx(m_nNumScore % 100 / 10);
	m_apNumber[7]->SetIdx(m_nNumScore % 10 / 1);
}

//===============================================
//スコア設定処理
//===============================================
void CScore::SetScore(int nScore)
{
	m_nNumScore = nScore;

	m_apNumber[0]->SetIdx(m_nNumScore % 100000000 / 10000000);
	m_apNumber[1]->SetIdx(m_nNumScore % 10000000 / 1000000);
	m_apNumber[2]->SetIdx(m_nNumScore % 1000000 / 100000);
	m_apNumber[3]->SetIdx(m_nNumScore % 100000 / 10000);
	m_apNumber[4]->SetIdx(m_nNumScore % 10000 / 1000);
	m_apNumber[5]->SetIdx(m_nNumScore % 1000 / 100);
	m_apNumber[6]->SetIdx(m_nNumScore % 100 / 10);
	m_apNumber[7]->SetIdx(m_nNumScore % 10 / 1);
}

//===============================================
// 色設定
//===============================================
void CScore::SetClo(D3DXCOLOR col)
{
	for (int nCnt = 0; nCnt < NUM_SCORE; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{// 使用していない場合
			m_apNumber[nCnt]->GetObject2D()->SetCol(col);
		}
	}
}

////===============================================
//// 頂点設定
////===============================================
//void CScore::SetIdx(const int nIdx)
//{
//	m_nIdx = nIdx;	// 値を設定
//
//	if (m_nIdx > 10)
//	{// 値が限界を超えた場合
//		m_nIdx = 9;
//	}
//	else if (m_nIdx < 0)
//	{// 値が最低値を超えた場合
//		m_nIdx = 0;
//	}
//
//	if (m_pObject2D != NULL)
//	{// 使用されている場合
//	 // 頂点情報の設定
//		m_pObject2D->SetVtx(m_nIdx, MAX_WIDTHPATTERN, 1);
//	}
//}
//
////===============================================
//// ポリゴン廃棄
////===============================================
//void CScore::PolygonDelete(void)
//{
//	if (m_pObject2D != NULL)
//	{// 使用されている場合
//		m_pObject2D->Uninit();
//		m_pObject2D = NULL;
//	}
//}