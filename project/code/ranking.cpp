//===============================================
//
// ランキング画面の管理処理 [ranking.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "ranking.h"
#include "object2D.h"
#include "texture.h"
#include "manager.h"
#include "main.h"
#include "input.h"
#include "fade.h"
#include "light.h"
#include "sound.h"
#include "camera.h"
#include "number.h"
#include "score.h"
#include "objectX.h"
#include "item.h"
#include "object2D.h"

//===============================================
// マクロ定義
//===============================================
#define RANKING_FILE	"data\\FILE\\ranking.bin"	// ランキングファイル
#define AUTOMOVE_TITLE	(600)						// タイトル自動遷移タイマー

//===============================================
// 静的メンバ変数
//===============================================
CScore *CRanking::m_apScore[NUM_RANKING][NUM_RANK] = {};	// ランキングのポインタ
int CRanking::m_nScore = 0;					// スコア

//===============================================
// コンストラクタ
//===============================================
CRanking::CRanking()
{
	// 値をクリアする
	m_nTimer = 0;
	m_nRank = 0;
	m_nCounter = 0;
}

//===============================================
// デストラクタ
//===============================================
CRanking::~CRanking()
{

}

//===============================================
// 初期化処理
//===============================================
HRESULT CRanking::Init(void)
{
	int aScore[NUM_RANK] = {};	// スコア格納用
	m_nRank = -1;	//ランクインしてない状態

	CObjectX::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\coin_tower00.x", NULL);

	for (int nCnt = 0; nCnt < NUM_RANK; nCnt++)
	{
		m_pObjectRank[nCnt] = CObject2D::Create(D3DXVECTOR3(100.0f, 200.0f + (100.0f* nCnt), 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_pObjectRank[nCnt]->SetPosition(D3DXVECTOR3(500.0f, -100.0f, 0.0f));
		m_pObjectRank[nCnt]->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\rank00.png"));

		// 頂点情報の設定
		m_pObjectRank[nCnt]->SetVtx(nCnt, NUM_RANK, 1);
	}
	
	
	


	// データの読み込み
	Load(&aScore[0]);

	// データのソート
	Sort(&aScore[0]);

	// ランクイン確認
	RankIn(&aScore[0], m_nScore);

	for (int nCntRanking = 0; nCntRanking < NUM_RANKING; nCntRanking++)
	{
		for (int nCntRank = 0; nCntRank < NUM_RANK; nCntRank++)
		{
			m_apScore[nCntRanking][nCntRank] = CScore::Create(D3DXVECTOR3(200.0f + nCntRanking * 800.0f, 200.0f + nCntRank * 100.0f, 0.0f), 15.0f, 25.0f);
		}
	}

	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_RANKING);

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CRanking::Uninit(void)
{
	m_nScore = 0;

	for (int nCntRanking = 0; nCntRanking < NUM_RANKING; nCntRanking++)
	{
		for (int nCntRank = 0; nCntRank < NUM_RANK; nCntRank++)
		{
			m_apScore[nCntRanking][nCntRank]->Uninit();
		}
	}
}

//===============================================
// 更新処理
//===============================================
void CRanking::Update(void)
{
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();

	//m_nCounter++;
	
	if (m_nCounter % 5 == 0)
	{
		D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 pos1 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		
		pos.x = ((float)(rand() % 8000 - 4000) * 0.01f)* ((float)(rand() % 100)) * 0.6f;
		pos1.x = ((float)(rand() % 8000 - 4000) * 0.01f)* ((float)(rand() % 100)) * 0.6f;

		pos.z = ((float)(rand() % 2000 - 1000) * 0.01f)* ((float)(rand() % 100)) * 0.6f;
		pos1.z = ((float)(rand() % 2000 - 1000) * 0.01f)* ((float)(rand() % 100)) * 0.6f;

		CItem::Create(D3DXVECTOR3(pos.x , 1500.0f, pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\coin.x", CItem::TYPE_COIN, CItem::STATE_DOWN);
		CItem::Create(D3DXVECTOR3(pos1.x, 1500.0f, pos1.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\coin.x", CItem::TYPE_COIN, CItem::STATE_DOWN);
	}

	if (CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_RETURN) || pInputPad->GetTrigger(CInputPad::BUTTON_START, 0))
	{
		CManager::GetInstance()->GetFade()->Set(CScene::MODE_TITLE);
	}

	if (CManager::GetInstance()->GetFade()->GetState() == CFade::STATE_NONE)
	{
		m_nTimer++;

		if (m_nTimer >= AUTOMOVE_TITLE)
		{// タイトル自動遷移規定値
			CManager::GetInstance()->GetFade()->Set(CScene::MODE_TITLE);
		}
	}

	CScene::Update();
}

//===============================================
// 描画処理
//===============================================
void CRanking::Draw(void)
{
	CScene::Draw();
}

//===============================================
// ランキングデータ保存
//===============================================
void CRanking::Save(int *pScore)
{
	FILE *pFile;

	pFile = fopen(RANKING_FILE, "wb");

	if (pFile != NULL)
	{//ファイルが開けた場合

		//データを読み込む
		fwrite(pScore, sizeof(int), NUM_RANK, pFile);

		//ファイルを閉じる
		fclose(pFile);
	}
}

//===============================================
// ランキングデータ読み込み
//===============================================
void CRanking::Load(int *pScore)
{
	FILE *pFile;

	pFile = fopen(RANKING_FILE, "rb");

	if (pFile != NULL)
	{//ファイルが開けた場合

		//データを読み込む
		fread(pScore, sizeof(int), NUM_RANK, pFile);

		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開けなかった場合
		//要素を入れておく
		for (int nCntRanking = 0; nCntRanking < NUM_RANK; nCntRanking++)
		{
			pScore[nCntRanking] = 40000 - (nCntRanking * 5000);
		}
	}
}

//===============================================
// ランキングデータソート
//===============================================
void CRanking::Sort(int *pScore)
{
	// 降順ソート
	for (int nCntFst = 0; nCntFst < NUM_RANK - 1; nCntFst++)
	{
		int nTempNum = nCntFst;	// 仮の一番大きい番号

		for (int nCntSec = nCntFst + 1; nCntSec < NUM_RANK; nCntSec++)
		{
			if (pScore[nCntSec] > pScore[nTempNum])
			{// 値が大きい場合
				nTempNum = nCntSec;	// 大きい番号を変更
			}
		}

		if (nTempNum != nCntFst)
		{// 変更する場合
			int nTemp = pScore[nCntFst];
			pScore[nCntFst] = pScore[nTempNum];
			pScore[nTempNum] = nTemp;
		}
	}
}

//===============================================
// ランキングイン確認
//===============================================
void CRanking::RankIn(int *pScore, int nResult)
{
	if (nResult > pScore[NUM_RANK - 1])
	{
		pScore[NUM_RANK - 1] = nResult;

		// ソート処理
		Sort(pScore);

		// 保存処理
		Save(pScore);

		//ランクインした順位を確認する
		for (int nCntRank = 0; nCntRank < NUM_RANK; nCntRank++)
		{
			if (pScore[nCntRank] == nResult)
			{
				m_nRank = nCntRank;	// ランクインした順位を保存			
				break;
			}
		}
	}
}