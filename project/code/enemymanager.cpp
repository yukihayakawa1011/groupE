//==========================================================
//
// 敵マネージャ [enemymanager.cpp]
// Author : Soma Ishihara
//
//==========================================================
#include "enemymanager.h"
#include "enemy.h"
#include "point.h"

// マクロ定義
#define TEMP_SPAWN_POS	D3DXVECTOR3(0.0f,0.0f,0.0f)	//仮のスポーン位置
#define SPAWN_PULSE		(600)	//スポーン間隔
#define MAX_SPAWN_ENEMY	(3)	//敵沸き上限

//==========================================================
// コンストラクタ
//==========================================================
CEnemyManager::CEnemyManager()
{
	// 値のクリア
	m_nCounterSpawn = 0;
}

//==========================================================
// デストラクタ
//==========================================================
CEnemyManager::~CEnemyManager()
{

}

//==========================================================
// 初期化処理
//==========================================================
HRESULT CEnemyManager::Init(void)
{
	return S_OK;
}

//==========================================================
// 終了処理
//==========================================================
void CEnemyManager::Uninit(void)
{
	Release();
}

//==========================================================
// 更新処理
//==========================================================
void CEnemyManager::Update(void)
{
	m_nCounterSpawn++;

	if (m_nCounterSpawn >= SPAWN_PULSE)
	{
		m_nCounterSpawn = 0;	//カウンターリセット

		if (CEnemy::GetNum() < MAX_SPAWN_ENEMY)
		{
			int nRand = rand() % CPoint::GetNumAll();
			CPoint* pPoint = CPoint::GetTop();
			for (int cnt = 0; cnt < nRand; cnt++)
			{
				pPoint = pPoint->GetNext();
			}
			CEnemy::Create(pPoint->GetPoint(0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, NULL, nRand);
		}
	}
}

//==========================================================
// 生成
//==========================================================
CEnemyManager *CEnemyManager::Create(void)
{
	CEnemyManager *pEnemyManager = nullptr;

	pEnemyManager = new CEnemyManager;

	if (pEnemyManager != nullptr)
	{
		// 初期化処理
		pEnemyManager->Init();
	}

	return pEnemyManager;
}