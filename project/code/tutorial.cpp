//===============================================
//
// チュートリアル画面の管理処理 [tutorial.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "tutorial.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "time.h"
#include "camera.h"
#include "light.h"
#include "texture.h"
#include "fileload.h"
#include "Xfile.h"
#include "input.h"
#include "fade.h"
#include "result.h"
#include "sound.h"
#include "debugproc.h"
#include "player.h"
#include "game.h"
#include "goal.h"
#include "gimmick_rotatedoor.h"
#include "gimmick_startdoor.h"
#include "gimmick_lever.h"

// 無名名前空間
namespace
{
	const char* FILEPASS = "data\\TXT\\player";	// ファイルのパス
	const char* FILEEXT = ".txt";				// ファイルの拡張子
	const int FILEPASS_SIZE = (200);	// ファイルのパスサイズ
}

//===============================================
// マクロ定義
//===============================================

//===============================================
// 静的メンバ変数
//===============================================

//===============================================
// コンストラクタ
//===============================================
CTutorial::CTutorial()
{
	// 値のクリア
	m_pFileLoad = NULL;
	m_bEnd = false;
}

//===============================================
// デストラクタ
//===============================================
CTutorial::~CTutorial()
{

}

//===============================================
// 初期化処理
//===============================================
HRESULT CTutorial::Init(void)
{
	// 外部ファイル読み込みの生成
	if (m_pFileLoad == NULL)
	{// 使用していない場合
		m_pFileLoad = new CFileLoad;

		if (m_pFileLoad != NULL)
		{
			m_pFileLoad->Init();
			m_pFileLoad->OpenFile("data\\TXT\\tutorial.txt");
		}
	}

	//カメラ初期化
	{
		//CManager::GetInstance()->GetCamera()->Init();

		CManager::GetInstance()->GetCamera()->SetPositionV(D3DXVECTOR3(-874.3f, 1124.15f, 1717.2f));
		CManager::GetInstance()->GetCamera()->SetPositionR(D3DXVECTOR3(-320.3f, 1.0f, -91.6f));
		CManager::GetInstance()->GetCamera()->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, D3DX_PI * 0.1f)); 

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

	// 開始扉
	CGimmickLever *l = CGimmickLever::Create(D3DXVECTOR3(-1350.0f, 100.0f, -560.0f + 10.0f));
	l->SetRotation(D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f));
	CGimmickStartDoor *p = CGimmickStartDoor::Create(D3DXVECTOR3(950.0f, 0.0f, -550.0f));
	p->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	p->SetLever(l);
	
	// 回転扉
	CGimmickRotateDoor::Create(D3DXVECTOR3(-700.0f, 0.0f, -50.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));

	// ゴール
	CGoal::Create(D3DXVECTOR3(1025.0f, 0.0f, -550.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), 100.0f);

	// 人数分ポインタ生成
	m_ppPlayer = new CPlayer*[PLAYER_MAX];

	m_ppPlayer[0] = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		"data\\TXT\\player0\\motion_ninjabody.txt", "data\\TXT\\player0\\motion_ninjaleg.txt");
	m_ppPlayer[0]->BindId(0);
	m_ppPlayer[0]->SetType(CPlayer::TYPE_ACTIVE);

	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_TUTORIAL);

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CTutorial::Uninit(void)
{
	if (m_pFileLoad != NULL)
	{
		m_pFileLoad->Uninit();

		delete m_pFileLoad;		// メモリの開放
		m_pFileLoad = NULL;
	}

	if (m_ppPlayer != NULL)
	{// 使用していた場合
		int nNum = CPlayer::GetNum();
		for (int nCnt = 0; nCnt < nNum; nCnt++)
		{
			// 終了処理
			m_ppPlayer[nCnt]->Uninit();
			m_ppPlayer[nCnt] = NULL;	// 使用していない状態にする
		}

		delete[] m_ppPlayer;	// ポインタの開放
		m_ppPlayer = NULL;	// 使用していない状態にする
	}
}

//===============================================
// 更新処理
//===============================================
void CTutorial::Update(void)
{
	if (CManager::GetInstance()->GetInputPad()->GetTrigger(CInputPad::BUTTON_START, 0) || CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{
		CManager::GetInstance()->GetFade()->Set(CScene::MODE_GAME);
		CGame::SetNumPlayer(CPlayer::GetNum());
	}

	bool bCreate = false;

	if (CPlayer::GetNum() < PLAYER_MAX){ // 人数が最大ではない場合
		if (CManager::GetInstance()->GetInputPad()->GetTrigger(CInputPad::BUTTON_START, CPlayer::GetNum())) {
			int nId = CPlayer::GetNum();
			char aBodyPass[FILEPASS_SIZE] = "";		// 胴体パス
			char aLegPass[FILEPASS_SIZE] = "";		// 下半身パス

			sprintf(&aBodyPass[0], "%s%d\\motion_ninjabody%s",FILEPASS, nId, FILEEXT);
			sprintf(&aLegPass[0], "%s%d\\motion_ninjaleg%s", FILEPASS, nId, FILEEXT);

			m_ppPlayer[nId] = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), &aBodyPass[0], &aLegPass[0]);
			m_ppPlayer[nId]->BindId(nId);
			m_ppPlayer[nId]->SetType(CPlayer::TYPE_ACTIVE);
			bCreate = true;
		}
	}

	if (CPlayer::GetNum() - 1 > 0 && !bCreate) { // 人数が最大ではない場合
		if (CManager::GetInstance()->GetInputPad()->GetTrigger(CInputPad::BUTTON_START, CPlayer::GetNum() - 1)) {
			int nId = CPlayer::GetNum() - 1;
			m_ppPlayer[nId]->Uninit();
			m_ppPlayer[nId] = 0;
		}
	}

	if (EndCheck()) 
	{// 全員ゴールしている

		// ゲームに遷移
		CManager::GetInstance()->GetFade()->Set(CScene::MODE_GAME);
	}

	// 更新処理
	CScene::Update();
}

//===============================================
// 描画処理
//===============================================
void CTutorial::Draw(void)
{
	// 描画処理
	CScene::Draw();
}

//===================================================
// ファイル読み込みの取得
//===================================================
CFileLoad *CTutorial::GetFileLoad(void)
{
	return m_pFileLoad;
}

//===================================================
// ファイル読み込みの取得
//===================================================
bool CTutorial::EndCheck(void)
{
	CPlayer *pPl = CPlayer::GetTop();	// プレイヤー
	int nNumGoal = 0;

	// ゴールしている人数を判定
	while (pPl != nullptr) {

		CPlayer *pPlNext = pPl->GetNext();	// 次を覚える

		if (!pPl->GetGoal()) {	// ゴールしていない
			break;
		}

		nNumGoal++;
		pPl = pPlNext;	// 次に移動
	}

	if (nNumGoal >= CPlayer::GetNum()) {	// 全員ゴール
		return true;
	}

	return false;
}
