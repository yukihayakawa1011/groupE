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


// ファイル名
const char *CRanking::m_apFileName[TYPE_MAX] =
{
	"data\\TEXTURE\\rank00.png",
	"data\\TEXTURE\\new_record00.png",
	"data\\TEXTURE\\ranking_one00.png",
	"data\\TEXTURE\\ranking_team00.png",
};

//===============================================
// 静的メンバ変数
//===============================================
CScore *CRanking::m_apScore[NUM_RANKING][NUM_RANK] = {};	// ランキングの
CScore *CRanking::m_apNowScore[NUM_NOWSCORE] = {};	// ランキングのポインタ
int CRanking::m_nScore = 0;					// スコア
int CRanking::m_nTotalScore = 0;					// スコア

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
	int aTotalScore[NUM_RANK] = {};	// スコア格納用
	m_nRank = -1;	//ランクインしてない状態

	CObjectX::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\coin_tower00.x", NULL);

	for (int nCntRanking = 0; nCntRanking < NUM_RANKING; nCntRanking++)
	{
		for (int nCnt = 0; nCnt < NUM_RANK; nCnt++)
		{
			m_pObjectRank[nCntRanking][nCnt] = CObject2D::Create();
			m_pObjectRank[nCntRanking][nCnt]->SetPosition(D3DXVECTOR3(200.0f + nCntRanking * 600.0f, 400.0f + (nCnt* 100.0f), 0.0f));
			m_pObjectRank[nCntRanking][nCnt]->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\rank00.png"));
		}
	}

	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		m_pObject[nCnt] = CObject2D::Create();
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_pObject[nCnt]->SetPosition(D3DXVECTOR3(400.0f + nCnt * 600.0f, 300.0f, 0.0f));
		m_pObject[nCnt]->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\new_record00.png"));
		m_pObject[nCnt]->SetLength(250.0f, 100.0f);
	}

	m_pObject[2]->SetPosition(D3DXVECTOR3(300.0f, 100.0f, 0.0f));
	m_pObject[2]->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\ranking_one00.png"));
	m_pObject[2]->SetLength(250.0f, 100.0f);

	m_pObject[3]->SetPosition(D3DXVECTOR3(1000.0f, 100.0f, 0.0f));
	m_pObject[3]->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\ranking_team00.png"));
	m_pObject[3]->SetLength(200.0f, 75.0f);

	//個人
	// データの読み込み
	Load(&aScore[0]);

	// データのソート
	Sort(&aScore[0]);

	// ランクイン確認
	RankIn(&aScore[0], m_nScore);

	//合計
	// データの読み込み
	Load(&aTotalScore[0]);

	// データのソート
	Sort(&aTotalScore[0]);

	// ランクイン確認
	RankIn(&aTotalScore[0], m_nTotalScore);

	for (int nCnt = 0; nCnt < NUM_NOWSCORE; nCnt++)
	{
		m_apNowScore[nCnt] = CScore::Create(D3DXVECTOR3(300.0f + nCnt * 600.0f, 200.0f, 0.0f), 15.0f, 25.0f);
	}

	m_apNowScore[0]->SetScore(m_nScore);
	m_apNowScore[1]->SetScore(m_nTotalScore);

	for (int nCntRanking = 0; nCntRanking < NUM_RANKING; nCntRanking++)
	{
		for (int nCntRank = 0; nCntRank < NUM_RANK; nCntRank++)
		{
			m_apScore[nCntRanking][nCntRank] = CScore::Create(D3DXVECTOR3(300.0f + nCntRanking * 600.0f, 400.0f + nCntRank * 100.0f, 0.0f), 15.0f, 25.0f);
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
	m_nTotalScore = 0;

	for (int nCntRanking = 0; nCntRanking < NUM_RANKING; nCntRanking++)
	{
		for (int nCntRank = 0; nCntRank < NUM_RANK; nCntRank++)
		{
			m_apScore[nCntRanking][nCntRank]->Uninit();
		}
	}

	for (int nCntRanking = 0; nCntRanking < NUM_RANKING; nCntRanking++)
	{
		for (int nCnt = 0; nCnt < NUM_RANK; nCnt++)
		{
			m_pObjectRank[nCntRanking][nCnt]->Uninit();
		}
	}
}

//===============================================
// 更新処理
//===============================================
void CRanking::Update(void)
{
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();

	//サイズの設定
	for (int nCntRanking = 0; nCntRanking < NUM_RANKING; nCntRanking++)
	{
		for (int nCnt = 0; nCnt < NUM_RANK; nCnt++)
		{
			// 頂点情報の設定
			m_pObjectRank[nCntRanking][nCnt]->SetVtx();
			m_pObjectRank[nCntRanking][nCnt]->SetVtx(nCnt, NUM_RANK, 1);
		}
	}

	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		// 頂点情報の設定
		m_pObject[nCnt]->SetVtx();	

		if (nCnt >= 4)
		{
			m_pObject[nCnt]->SetVtx(0, NUM_RANK, 1);
		}
	}

		D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 pos1 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		
		pos.x = ((float)(rand() % 8000 - 4000) * 0.01f)* ((float)(rand() % 100)) * 0.6f;
		pos1.x = ((float)(rand() % 8000 - 4000) * 0.01f)* ((float)(rand() % 100)) * 0.6f;

		pos.z = ((float)(rand() % 2000 - 1000) * 0.01f)* ((float)(rand() % 100)) * 0.6f;
		pos1.z = ((float)(rand() % 2000 - 1000) * 0.01f)* ((float)(rand() % 100)) * 0.6f;

		CItem::Create(D3DXVECTOR3(pos.x , 1500.0f, pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\coin.x", CItem::TYPE_COIN, CItem::STATE_DOWN);
		CItem::Create(D3DXVECTOR3(pos1.x, 1500.0f, pos1.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\coin.x", CItem::TYPE_COIN, CItem::STATE_DOWN);

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