//===============================================
//
// タイムの処理 [time.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "time.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "number.h"
#include "object2D.h"
#include "slow.h"
#include "debugproc.h"

// マクロ定義
#define X_SPACE		(50)	// 横の移動量
#define NUM_WIDTH		(20)
#define NUM_HEIGHT	(50)

//===============================================
// コンストラクタ
//===============================================
CTime::CTime()
{
	// 値をクリア
	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		m_apNumber[nCnt] = NULL;
	}

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNum = 0;
	m_fAnimTimer = 0.0f;
	m_nIdxTexture = -1;
	m_nMaxNum = 0;
	m_fDiff = 0.0f;
	m_nStartDeltaTime = 0;
	m_nPauseTimer = 0;
	m_mode = MODE_MAX;
	m_bActive = false;
}

//===============================================
// デストラクタ
//===============================================
CTime::~CTime()
{

}

//===============================================
// 初期化処理
//===============================================
HRESULT CTime::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();
	m_nStartDeltaTime = timeGetTime();
	m_mode = MODE_MINUS;

	// テクスチャの読み込み
	m_nIdxTexture = pTexture->Regist(CTexture::GetFileName(CTexture::TYPE_TIMER));
	CObject2D *pObj = CObject2D::Create(6);
	pObj->SetPosition(D3DXVECTOR3(m_pos.x + X_SPACE * 1.0f + NUM_WIDTH * 1.25f, m_pos.y, 0.0f));
	pObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f));
	pObj->SetSize(NUM_WIDTH * 5.0f, NUM_HEIGHT * 0.7f);
	pObj->BindTexture(pTexture->Regist("data\\TEXTURE\\map001.png"));

	pObj = CObject2D::Create(6);
	pObj->SetPosition(D3DXVECTOR3(m_pos.x + X_SPACE * 1.0f + NUM_WIDTH * 1.4f, m_pos.y, 0.0f));
	pObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	pObj->SetSize(NUM_WIDTH * 0.4f, NUM_HEIGHT * 0.45f);
	pObj->BindTexture(pTexture->Regist("data\\TEXTURE\\number002.png"));

	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		if (m_apNumber[nCnt] == NULL)
		{// 使用していない場合
			D3DXVECTOR3 pos = m_pos;	// 設定座標
			pos.x += nCnt * X_SPACE + 1.0f;	// 横移動
			m_apNumber[nCnt] = CNumber::Create(pos, NUM_WIDTH, NUM_HEIGHT);


			if (m_apNumber[nCnt] != NULL)
			{// 使用している場合
				m_apNumber[nCnt]->GetObject2D()->BindTexture(m_nIdxTexture);
				
			}
		}
	}

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CTime::Uninit(void)
{
	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{// 使用していない場合
			m_apNumber[nCnt]->Uninit();

			delete m_apNumber[nCnt];

			m_apNumber[nCnt] = NULL;
		}
	}
}

//===============================================
// 更新処理
//===============================================
void CTime::Update(void)
{
	if(!m_bActive)
	{
		return;
	}

	m_fAnimTimer += CManager::GetInstance()->GetSlow()->Get();
	if (m_fAnimTimer >= 60)
	{// 12フレーム立った
		m_fAnimTimer = 0;	// カウンターリセット
		Add(-1);
	}
}

//===============================================
// 生成
//===============================================
CTime *CTime::Create(const D3DXVECTOR3& pos)
{
	CTime *pTIme = NULL;

	// オブジェクト2Dの生成
	pTIme = new CTime;

	if (pTIme != NULL)
	{// 生成できた場合

		pTIme->m_pos = pos;

		// 初期化処理
		pTIme->Init();
	}
	else
	{// 生成に失敗した場合
		return NULL;
	}


	return pTIme;
}

//===============================================
// 加算
//===============================================
void CTime::Add(int nValue)
{
	// 代入
	m_nNum += nValue;

	// 数値設定
	SetValue();
}

//===============================================
// 設定
//===============================================
void CTime::Set(int nValue)
{
	// 代入
	m_nNum = nValue;
	m_nSetNum = nValue;

	// 数値設定
	SetValue();
}

//===============================================
// 設定値
//===============================================
void CTime::SetNum(int nValue)
{
	// 代入
	m_nNum = nValue;

	// 数値設定
	SetValue();
}

//===============================================
// 桁ごとの値設定
//===============================================
void CTime::SetValue(void)
{
	int aTexU[NUM_PLACE] = {};	// 計算格納用

	if (m_nNum < 0)
	{// 0以下の場合
		m_nNum = 0;
	}
	else if ((m_nNum - m_nNum % 100) * 0.01f >= 60 * 100)
	{
		m_nNum = 60 * 100 - 1;
	}

	int nNum = m_nNum;
	aTexU[0] = nNum / 60 / 10;
	aTexU[1] = nNum / 60 - aTexU[0] * 10;
	aTexU[2] = nNum % 60 / 10;
	aTexU[3] = nNum % 60 - aTexU[2] * 10;

	//スコアを各配列に格納
	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{// 使用されている場合
			// 値を設定
			m_apNumber[nCnt]->SetIdx(aTexU[nCnt]);
		}
	}
}

//===============================================
// 色設定
//===============================================
void CTime::SetColor(D3DXCOLOR col)
{
	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{// 使用していない場合
			m_apNumber[nCnt]->GetObject2D()->SetCol(col);
		}
	}
}