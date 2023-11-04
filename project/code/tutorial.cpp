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
		
	}

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
}

//===============================================
// 更新処理
//===============================================
void CTutorial::Update(void)
{
	if (CManager::GetInstance()->GetInputPad()->GetTrigger(CInputPad::BUTTON_START, 0) || CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{
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
	CScene::Draw();
}

//===================================================
// ファイル読み込みの取得
//===================================================
CFileLoad *CTutorial::GetFileLoad(void)
{
	return m_pFileLoad;
}
