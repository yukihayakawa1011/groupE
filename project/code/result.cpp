//===============================================
//
// リザルト画面の管理処理 [result.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "result.h"
#include "object2D.h"
#include "texture.h"
#include "manager.h"
#include "main.h"
#include "input.h"
#include "objectX.h"
#include "fade.h"
#include "ranking.h"
#include "sound.h"
#include "result.h"
#include "fileload.h"
#include "meshdome.h"
#include "character.h"
#include "motion.h"
#include "camera.h"
#include "score.h"
#include "player.h"
#include "ranking.h"
#include "object_manager.h"

// マクロ定義
#define RANKING_FILE	"data\\FILE\\ranking.bin"	// ランキングファイル
#define MOVE_TIMER	(660)

// 無名名前空間
namespace {
	const D3DXVECTOR3 TOTALSCORE_POS = {SCREEN_WIDTH * 0.425f, SCREEN_HEIGHT * 0.8f, 0.0f};	// 合計スコアの設置座標
	const float SCORE_MOVESIZE = (100.0f);
	const float SCORE_SPACE = (100.0f);
	const D3DXVECTOR3 RANK_POS = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.4f, 0.0f };	// 合計スコアの設置座標
	const float X_RANKSPACE = (100.0f);
	const D3DXVECTOR2 RANK_SIZE = { 50.0f, 30.0f };
	const int PLAYER_MAXMOTION = (13);
}

// 静的メンバ変数
int *CResult::m_pScore = 0;
int CResult::m_nTopScore = 0;
CResult::TYPE CResult::m_type = CResult::TYPE_MAX;
int CResult::m_nNumPlayer = 0;
int CResult::m_nQuota = 0;
CPlayer **CResult::m_ppPlayer = nullptr;
CScore **CResult::m_apScore = nullptr;

//===============================================
// コンストラクタ
//===============================================
CResult::CResult()
{
	m_pMeshSky = NULL;
	m_nTimer = 0;
	m_pTime = NULL;
	m_pTotalScore = nullptr;
	m_pRank = nullptr;
	m_bClear = false;
}

//===============================================
// デストラクタ
//===============================================
CResult::~CResult()
{

}

//===============================================
// 初期化処理
//===============================================
HRESULT CResult::Init(void)
{
	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_RESULT);
	CTexture *pTexture = CManager::GetInstance()->GetTexture();
	CMeshDome::Create(D3DXVECTOR3(0.0f, -1000.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10000.0f, 10.0f, 3, 10, 10);

	if (m_pFileLoad == NULL)
	{// 使用していない場合
		m_pFileLoad = new CFileLoad;

		if (m_pFileLoad != NULL)
		{
			m_pFileLoad->Init();
			m_pFileLoad->OpenFile("data\\TXT\\result.txt");
		}
	}

	// 人数分ポインタ生成
	m_ppPlayer = new CPlayer*[m_nNumPlayer];

	for (int nCnt = 0; nCnt < m_nNumPlayer; nCnt++)
	{
		char aBodyPass[200] = "";		// 胴体パス
		char aLegPass[200] = "";		// 下半身パス

		sprintf(&aBodyPass[0], "data\\TXT\\Player%d\\motion_ninjabody.txt", nCnt);
		sprintf(&aLegPass[0], "data\\TXT\\Player%d\\motion_ninjaleg.txt", nCnt);

		m_ppPlayer[nCnt] = CPlayer::Create(D3DXVECTOR3(-((m_nNumPlayer - 1) * 100.0f) + nCnt * 200.0f, 0.0f, 60.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), &aBodyPass[0], &aLegPass[0]);
		m_ppPlayer[nCnt]->BindId(nCnt);
		m_ppPlayer[nCnt]->SetType(CPlayer::TYPE_NONE);
	}

	m_apScore = new CScore*[m_nNumPlayer];

	for (int nCount = 0; nCount < m_nNumPlayer; nCount++)
	{
		m_apScore[nCount] = CScore::Create(D3DXVECTOR3(-((m_nNumPlayer - 1) * SCORE_MOVESIZE) + nCount * SCORE_SPACE, 180.0f, 0.0f), 15.0f, 15.0f);
		m_apScore[nCount]->SetScore(m_pScore[nCount]);

	}

	SetTopScore(m_pScore);

	if (m_pRank == nullptr && m_nNumPlayer > 0) {
		m_pRank = new int[m_nNumPlayer];
	}

	// それぞれのランク付け
	SetRank(m_nNumPlayer);

	// ランクのポリゴン生成
	for (int nCnt = 0; nCnt < m_nNumPlayer; nCnt++) {
		CObject2D *pObj = CObject2D::Create(NUM_PRIORITY);
		pObj->BindTexture(CTexture::TYPE_RESULTRANK);
		pObj->SetPosition(D3DXVECTOR3(RANK_POS.x + nCnt * X_RANKSPACE, RANK_POS.y, RANK_POS.z));
		pObj->SetSize(RANK_SIZE.x, RANK_SIZE.y);
		pObj->SetVtx(m_pRank[nCnt], PLAYER_MAX, 1);
	}

	//カメラ初期化
	{
		CManager::GetInstance()->GetCamera()->SetPositionR(D3DXVECTOR3(0.0f, 137.77f, -381.94f));
		//CManager::GetInstance()->GetCamera()->SetPositionR(D3DXVECTOR3(205.0f, 92.42f, -89.13f));
		CManager::GetInstance()->GetCamera()->SetRotation(D3DXVECTOR3(1.0f, -D3DX_PI * 0.5f, 1.63f));
		CManager::GetInstance()->GetCamera()->SetLength(300.0f);

		D3DVIEWPORT9 viewport;
		//プレイヤー追従カメラの画面位置設定
		viewport.X = 0;
		viewport.Y = 0;
		viewport.Width = (DWORD)(SCREEN_WIDTH * 1.0f);
		viewport.Height = (DWORD)(SCREEN_HEIGHT * 1.0f);
		viewport.MinZ = 0.0f;
		viewport.MaxZ = 1.0f;
		CManager::GetInstance()->GetCamera()->SetViewPort(viewport);
	}

	// 合計スコアの取得
	int nTotalScore = SumScore();

	m_pTotalScore = CScore::Create(TOTALSCORE_POS, 15.0f, 15.0f);
	m_pTotalScore->SetScore(nTotalScore);
	CRanking::SetTotalScore(nTotalScore);

	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_RANKING);

	if (m_ppPlayer == nullptr) {
		return S_OK;
	}

	for (int nCnt = 0; nCnt < m_nNumPlayer; nCnt++)
	{
		if (m_ppPlayer[nCnt] == nullptr) {
			continue;
		}

		if (nTotalScore < m_nQuota) {	// ノルマを達成していない
			m_ppPlayer[nCnt]->SetMotion(PLAYER_MAXMOTION - 2);
		}
		else {
			m_ppPlayer[nCnt]->SetMotion(PLAYER_MAXMOTION - 1);
		}
	}

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CResult::Uninit(void)
{
	if (m_apScore != nullptr) {
		for (int nCnt = 0; nCnt < m_nNumPlayer; nCnt++) {
			if (m_apScore[nCnt] != nullptr) {// 使用されている場合

				// 終了処理
				m_apScore[nCnt]->Uninit();

				// 破棄
				delete m_apScore[nCnt];

				// 使用していない状態にする
				m_apScore[nCnt] = nullptr;
			}
		}
		delete[] m_apScore;	// ポインタの開放
		m_apScore = nullptr;	// 使用していない状態にする
	}

	if (m_ppPlayer != nullptr) { // 使用していた場合
		for (int nCnt = 0; nCnt < m_nNumPlayer; nCnt++)
		{
			// 終了処理
			m_ppPlayer[nCnt]->Uninit();
			m_ppPlayer[nCnt] = nullptr;	// 使用していない状態にする
		}

		delete[] m_ppPlayer;	// ポインタの開放
		m_ppPlayer = nullptr;	// 使用していない状態にする
	}

	m_type = TYPE_MAX;

	if (m_pScore != nullptr) {
		delete[] m_pScore;
		m_pScore = nullptr;
	}

	m_nNumPlayer = 0;
}

//===============================================
// 更新処理
//===============================================
void CResult::Update(void)
{
	m_nTimer++;

	if (/*CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_RETURN) || m_nTimer > MOVE_TIMER 
		||*/ CManager::GetInstance()->GetInputPad()->GetTrigger(CInputPad::BUTTON_A, 0) || CManager::GetInstance()->GetInputPad()->GetTrigger(CInputPad::BUTTON_START, 0))
	{
		CManager::GetInstance()->GetFade()->Set(CScene::MODE_RANKING);
	}

	CScene::Update();
}

//===============================================
// 描画処理
//===============================================
void CResult::Draw(void)
{
	CScene::Draw();
}

//===============================================
// スコア設定処理
//===============================================
void CResult::SetScore(CPlayer **ppPlayer)
{
	CPlayer *pPlayer = CPlayer::GetTop();
	int nNumGoal = 0;

	m_pScore = new int [m_nNumPlayer];

	for (int i = 0; i < m_nNumPlayer; i++)
	{
		if (ppPlayer[i]->GetGoal())
		{
			m_pScore[i] = ppPlayer[i]->GetScore()->GetScore();
		}
		else
		{
			m_pScore[i] = 0;
		}
	}
}

//===============================================
// ランキングデータソート
//===============================================
void CResult::Sort(int *pScore)
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
// 全員のスコア足す
//===============================================
int CResult::SumScore(void)
{
	int nSumScore = 0;

	for (int i = 0; i < m_nNumPlayer; i++)
	{
		nSumScore += m_pScore[i];
	}

	return nSumScore;
}

//===============================================
// 誰が一位なのか決める
//===============================================
void CResult::SetTopScore(int * pScore)
{
	int nTopScore = 0;

	for (int nCount = 0; nCount < m_nNumPlayer; nCount++)
	{
		if(nTopScore < pScore[nCount])
		{
			nTopScore = pScore[nCount];
		}
	}

	CRanking::SetScore(nTopScore);
}

//===============================================
// それぞれのランク付け
//===============================================
void CResult::SetRank(int nNum)
{
	if (m_apScore == nullptr) {	// スコア存在していない
		return;
	}

	int *pScore = new int[nNum];

	for (int nCount = 0; nCount < m_nNumPlayer; nCount++)
	{
		pScore[nCount] = m_pScore[nCount];
	}

	// 降順ソート
	for (int nCntFst = 0; nCntFst < m_nNumPlayer - 1; nCntFst++)
	{
		int nTempNum = nCntFst;	// 仮の一番大きい番号

		for (int nCntSec = nCntFst + 1; nCntSec < m_nNumPlayer; nCntSec++)
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

	// ランク付け
	for (int nCntFst = 0; nCntFst < m_nNumPlayer; nCntFst++)
	{
		for (int nCntSec = 0; nCntSec < m_nNumPlayer; nCntSec++)
		{
			if (m_pScore[nCntFst] == pScore[nCntSec])
			{// 値が大きい場合
				m_pRank[nCntFst] = nCntSec;
				break;
			}
		}
	}

	if (pScore != nullptr) {
		delete[] pScore;
		pScore = nullptr;
	}

}
