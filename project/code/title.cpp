//===============================================
//
// タイトル画面の管理処理 [title.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "title.h"
#include "object2D.h"
#include "texture.h"
#include "manager.h"
#include "main.h"
#include "input.h"
#include "fade.h"
#include "fileload.h"
#include "meshcylinder.h"
#include "meshdome.h"
#include "light.h"
#include "sound.h"
#include "camera.h"
#include "item.h"
#include "objectX.h"

//===============================================
// マクロ定義
//===============================================
#define AUTOMOVE_RANKING	(640)	// ランキング自動遷移
#define TITLE_CAMLENGTH		(1000.0f)
#define TITLE_CAMROTZ		(D3DX_PI * 0.35f)
#define MOVE_TUTORIAL		(110)	//チュートリアルに遷移するまで

//===============================================
// コンストラクタ
//===============================================
CTitle::CTitle()
{
	m_nTimer = 0;
	m_pFileLoad = NULL;
	m_bClick = false;
	m_fMoveCol = 0.01f;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nCounter = 0;
	m_bPush = false;
}

//===============================================
// デストラクタ
//===============================================
CTitle::~CTitle()
{

}

//===============================================
// 初期化処理
//===============================================
HRESULT CTitle::Init(void)
{
	//外部ファイル読み込みの生成
	if (m_pFileLoad == NULL)
	{// 使用していない場合
		m_pFileLoad = new CFileLoad;

		if (m_pFileLoad != NULL)
		{
			m_pFileLoad->Init();
			m_pFileLoad->OpenFile("data\\TXT\\title_model.txt");
		}
	}

	//家モデルの設置
	CObjectX::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\house.x", NULL);

	//カメラ初期化
	{
		/*CManager::GetInstance()->GetCamera()->Init();*/

		CManager::GetInstance()->GetCamera()->SetPositionV(D3DXVECTOR3(-0.0f, 0.0f, 0.0f));
		CManager::GetInstance()->GetCamera()->SetPositionR(D3DXVECTOR3(75.0f, 300.0f, -0.0f));
		CManager::GetInstance()->GetCamera()->SetRotation(D3DXVECTOR3(1.0f, -1.6f, 1.35f));

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

	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_TITLE);

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CTitle::Uninit(void)
{
	if (m_pFileLoad != NULL)
	{
		m_pFileLoad->Uninit();

		delete m_pFileLoad;		// メモリの開放
		m_pFileLoad = NULL;
	}
}

//===============================================
// 更新処理
//===============================================
void CTitle::Update(void)
{
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();
	CInputKeyboard *pInputKey = CManager::GetInstance()->GetInputKeyboard();

	// 入力遷移
	if (pInputKey->GetTrigger(DIK_RETURN) || pInputPad->GetTrigger(CInputPad::BUTTON_START, 0))
	{
		CItem *pItem = CItem::GetTop();

		while (pItem != NULL)
		{// 使用されていない状態まで

			CItem *pItemNext = pItem->GetNext();	// 次のオブジェクトへのポインタを取得

			D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//移動量の設定
			move.x = sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.6f;
			move.z = cosf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.6f;
			pItem->SetMove(move);

			//タイプの変更											
			pItem->SetState(CItem::STATE_CRASH);

			pItem = pItemNext;	// 次のオブジェクトに移動
		}

		m_bPush = true;		//ボタンを押した

		if (m_bClick == false)
		{
			m_col.a = 1.0f;
			m_bClick = true;
			CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_CLICK);
		}
	}

	if (m_bPush == true)
	{
		m_nCounter++;

		if (m_nCounter >= MOVE_TUTORIAL)
		{
			CManager::GetInstance()->GetFade()->Set(CScene::MODE_TUTORIAL);
		}
	}

	if (CManager::GetInstance()->GetCamera() != NULL)
	{
		//CManager::GetInstance()->GetCamera()->TitleRotateCamera();
	}

	//ランキング画面自動遷移
	if (m_bClick == false && m_bPush == false)
	{
		m_nTimer++;

		if (m_nTimer >= AUTOMOVE_RANKING)
		{
			CManager::GetInstance()->GetFade()->Set(CScene::MODE_RANKING);
		}
	}

	CScene::Update();
}

//===============================================
// 描画処理
//===============================================
void CTitle::Draw(void)
{
	CScene::Draw();
}
