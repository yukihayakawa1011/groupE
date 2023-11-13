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

//===============================================
// マクロ定義
//===============================================
#define AUTOMOVE_RANKING	(1200)	// ランキング自動遷移
#define TITLE_CAMLENGTH		(1000.0f)
#define TITLE_CAMROTZ		(D3DX_PI * 0.35f)

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
	if (pInputKey->GetTrigger(DIK_RETURN) || pInputPad->GetTrigger(CInputPad::BUTTON_A, 0))
	{
		CManager::GetInstance()->GetFade()->Set(CScene::MODE_TUTORIAL);

		if (m_bClick == false)
		{
			m_col.a = 1.0f;
			m_bClick = true;
			CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_CLICK);
		}
	}

	if (pInputKey->GetTrigger(DIK_C))
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
			pItem->SetType(CItem::TYPE_CRASH);

			pItem = pItemNext;	// 次のオブジェクトに移動
		}
	}

	if (CManager::GetInstance()->GetCamera() != NULL)
	{
		//CManager::GetInstance()->GetCamera()->TitleRotateCamera();
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
