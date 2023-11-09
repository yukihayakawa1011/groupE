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
			m_pFileLoad->OpenFile("data\\TXT\\model.txt");
		}
	}

	//P
	CItem::Create(D3DXVECTOR3(-200.0f, 100.0f, 500.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-200.0f, 100.0f, 475.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-200.0f, 100.0f, 450.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-225.0f, 100.0f, 425.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-225.0f, 100.0f, 500.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-250.0f, 100.0f, 500.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-250.0f, 100.0f, 475.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-250.0f, 100.0f, 450.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-275.0f, 100.0f, 500.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-300.0f, 100.0f, 500.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	
	//R
	CItem::Create(D3DXVECTOR3(-200.0f, 100.0f, 375.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-200.0f, 100.0f, 350.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-200.0f, 100.0f, 325.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-225.0f, 100.0f, 300.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-225.0f, 100.0f, 375.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-250.0f, 100.0f, 350.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-250.0f, 100.0f, 325.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-250.0f, 100.0f, 375.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-275.0f, 100.0f, 375.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-275.0f, 100.0f, 300.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-300.0f, 100.0f, 375.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-300.0f, 100.0f, 300.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	
	//E
	CItem::Create(D3DXVECTOR3(-200.0f, 100.0f, 250.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-200.0f, 100.0f, 225.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-200.0f, 100.0f, 200.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-200.0f, 100.0f, 175.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-225.0f, 100.0f, 250.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-250.0f, 100.0f, 250.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-250.0f, 100.0f, 225.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-250.0f, 100.0f, 200.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-275.0f, 100.0f, 250.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-300.0f, 100.0f, 250.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-300.0f, 100.0f, 225.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-300.0f, 100.0f, 200.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-300.0f, 100.0f, 175.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);

	//S
	CItem::Create(D3DXVECTOR3(-200.0f, 100.0f, 100.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-200.0f, 100.0f, 75.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-200.0f, 100.0f, 50.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-225.0f, 100.0f, 125.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-250.0f, 100.0f, 100.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-250.0f, 100.0f, 75.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-250.0f, 100.0f, 50.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-275.0f, 100.0f, 25.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-300.0f, 100.0f, 100.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-300.0f, 100.0f, 75.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-300.0f, 100.0f, 50.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);

	//S
	CItem::Create(D3DXVECTOR3(-200.0f, 100.0f, -50.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-200.0f, 100.0f, -75.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-200.0f, 100.0f, -100.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-225.0f, 100.0f, -25.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-250.0f, 100.0f, -50.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-250.0f, 100.0f, -75.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-250.0f, 100.0f, -100.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-275.0f, 100.0f, -125.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-300.0f, 100.0f, -50.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-300.0f, 100.0f, -75.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-300.0f, 100.0f, -100.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);

	//E
	CItem::Create(D3DXVECTOR3(-200.0f, 100.0f, -175.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-200.0f, 100.0f, -200.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-200.0f, 100.0f, -225.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-200.0f, 100.0f, -250.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-225.0f, 100.0f, -175.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-250.0f, 100.0f, -175.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-250.0f, 100.0f, -200.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-250.0f, 100.0f, -225.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-275.0f, 100.0f, -175.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-300.0f, 100.0f, -175.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-300.0f, 100.0f, -200.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-300.0f, 100.0f, -225.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-300.0f, 100.0f, -250.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);

	//N
	CItem::Create(D3DXVECTOR3(-200.0f, 100.0f, -300.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-200.0f, 100.0f, -400.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-225.0f, 100.0f, -300.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-225.0f, 100.0f, -325.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-225.0f, 100.0f, -400.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-250.0f, 100.0f, -300.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-250.0f, 100.0f, -350.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-250.0f, 100.0f, -400.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-275.0f, 100.0f, -300.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-275.0f, 100.0f, -375.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-275.0f, 100.0f, -400.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-300.0f, 100.0f, -300.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-300.0f, 100.0f, -400.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);

	//T
	CItem::Create(D3DXVECTOR3(-200.0f, 100.0f, -450.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-200.0f, 100.0f, -475.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-200.0f, 100.0f, -500.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-200.0f, 100.0f, -525.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-200.0f, 100.0f, -550.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-225.0f, 100.0f, -500.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-250.0f, 100.0f, -500.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-275.0f, 100.0f, -500.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-300.0f, 100.0f, -500.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);

	//E
	CItem::Create(D3DXVECTOR3(-200.0f, 100.0f, -600.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-200.0f, 100.0f, -625.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-200.0f, 100.0f, -650.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-200.0f, 100.0f, -675.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-225.0f, 100.0f, -600.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-250.0f, 100.0f, -600.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-250.0f, 100.0f, -625.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-250.0f, 100.0f, -650.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-275.0f, 100.0f, -600.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-300.0f, 100.0f, -600.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-300.0f, 100.0f, -625.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-300.0f, 100.0f, -650.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-300.0f, 100.0f, -675.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);

	//R
	CItem::Create(D3DXVECTOR3(-200.0f, 100.0f, -725.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-200.0f, 100.0f, -750.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-200.0f, 100.0f, -775.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-225.0f, 100.0f, -725.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-225.0f, 100.0f, -800.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-250.0f, 100.0f, -725.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-250.0f, 100.0f, -750.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-250.0f, 100.0f, -775.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-275.0f, 100.0f, -725.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-275.0f, 100.0f, -800.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-300.0f, 100.0f, -725.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-300.0f, 100.0f, -800.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);

	//O
	CItem::Create(D3DXVECTOR3(-350.0f, 100.0f, 0.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-350.0f, 100.0f, -25.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-375.0f, 100.0f, 25.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-375.0f, 100.0f, -50.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-400.0f, 100.0f, 25.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-400.0f, 100.0f, -50.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-425.0f, 100.0f, 25.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-425.0f, 100.0f, -50.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-450.0f, 100.0f, 0.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-450.0f, 100.0f, -25.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	
	//R
	CItem::Create(D3DXVECTOR3(-350.0f, 100.0f, -125.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-350.0f, 100.0f, -150.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-350.0f, 100.0f, -175.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-375.0f, 100.0f, -125.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-375.0f, 100.0f, -200.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-400.0f, 100.0f, -125.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-400.0f, 100.0f, -150.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-400.0f, 100.0f, -175.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-425.0f, 100.0f, -125.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-425.0f, 100.0f, -200.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-450.0f, 100.0f, -125.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-450.0f, 100.0f, -200.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);

	//S
	CItem::Create(D3DXVECTOR3(-500.0f, 100.0f, 625.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-500.0f, 100.0f, 600.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-500.0f, 100.0f, 575.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-525.0f, 100.0f, 650.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-550.0f, 100.0f, 625.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-550.0f, 100.0f, 600.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-550.0f, 100.0f, 575.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-575.0f, 100.0f, 550.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-600.0f, 100.0f, 625.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-600.0f, 100.0f, 600.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-600.0f, 100.0f, 575.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);

	//T
	CItem::Create(D3DXVECTOR3(-500.0f, 100.0f, 500.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-500.0f, 100.0f, 475.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-500.0f, 100.0f, 450.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-500.0f, 100.0f, 425.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-500.0f, 100.0f, 400.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-525.0f, 100.0f, 450.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-550.0f, 100.0f, 450.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-575.0f, 100.0f, 450.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-600.0f, 100.0f, 450.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);

	//A
	CItem::Create(D3DXVECTOR3(-500.0f, 100.0f, 325.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-525.0f, 100.0f, 350.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-525.0f, 100.0f, 300.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-550.0f, 100.0f, 350.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-550.0f, 100.0f, 325.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-550.0f, 100.0f, 300.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-575.0f, 100.0f, 375.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-575.0f, 100.0f, 275.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-600.0f, 100.0f, 375.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-600.0f, 100.0f, 275.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);

	//R
	CItem::Create(D3DXVECTOR3(-500.0f, 100.0f, 225.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-500.0f, 100.0f, 200.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-500.0f, 100.0f, 175.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-525.0f, 100.0f, 225.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-525.0f, 100.0f, 150.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-550.0f, 100.0f, 225.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-550.0f, 100.0f, 200.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-550.0f, 100.0f, 175.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-575.0f, 100.0f, 225.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-575.0f, 100.0f, 150.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-600.0f, 100.0f, 225.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-600.0f, 100.0f, 150.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);

	//T
	CItem::Create(D3DXVECTOR3(-500.0f, 100.0f, 100.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-500.0f, 100.0f, 75.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-500.0f, 100.0f, 50.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-500.0f, 100.0f, 25.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-500.0f, 100.0f, 0.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-525.0f, 100.0f, 50.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-550.0f, 100.0f, 50.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-575.0f, 100.0f, 50.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-600.0f, 100.0f, 50.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);

	//B
	CItem::Create(D3DXVECTOR3(-500.0f, 100.0f, -50.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-500.0f, 100.0f, -75.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-500.0f, 100.0f, -100.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-525.0f, 100.0f, -50.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-525.0f, 100.0f, -125.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-550.0f, 100.0f, -50.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-550.0f, 100.0f, -75.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-550.0f, 100.0f, -100.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-575.0f, 100.0f, -50.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-575.0f, 100.0f, -125.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-600.0f, 100.0f, -50.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-600.0f, 100.0f, -75.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-600.0f, 100.0f, -100.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);

	//U
	CItem::Create(D3DXVECTOR3(-500.0f, 100.0f, -175.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-500.0f, 100.0f, -250.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-525.0f, 100.0f, -175.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-525.0f, 100.0f, -250.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-550.0f, 100.0f, -175.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-550.0f, 100.0f, -250.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-575.0f, 100.0f, -175.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-575.0f, 100.0f, -250.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-600.0f, 100.0f, -200.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-600.0f, 100.0f, -225.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);

	//T
	CItem::Create(D3DXVECTOR3(-500.0f, 100.0f, -300.00f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-500.0f, 100.0f, -325.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-500.0f, 100.0f, -350.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-500.0f, 100.0f, -375.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-500.0f, 100.0f, -400.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-525.0f, 100.0f, -350.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-550.0f, 100.0f, -350.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-575.0f, 100.0f, -350.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-600.0f, 100.0f, -350.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);

	//T
	CItem::Create(D3DXVECTOR3(-500.0f, 100.0f, -450.00f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-500.0f, 100.0f, -475.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-500.0f, 100.0f, -500.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-500.0f, 100.0f, -525.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-500.0f, 100.0f, -550.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-525.0f, 100.0f, -500.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-550.0f, 100.0f, -500.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-575.0f, 100.0f, -500.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-600.0f, 100.0f, -500.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);

	//O
	CItem::Create(D3DXVECTOR3(-500.0f, 100.0f, -625.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-500.0f, 100.0f, -650.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-525.0f, 100.0f, -600.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-525.0f, 100.0f, -675.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-550.0f, 100.0f, -600.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-550.0f, 100.0f, -675.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-575.0f, 100.0f, -600.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-575.0f, 100.0f, -675.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-600.0f, 100.0f, -625.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-600.0f, 100.0f, -650.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);

	//N
	CItem::Create(D3DXVECTOR3(-500.0f, 100.0f, -725.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-500.0f, 100.0f, -825.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-525.0f, 100.0f, -725.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-525.0f, 100.0f, -750.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-525.0f, 100.0f, -825.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-550.0f, 100.0f, -725.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-550.0f, 100.0f, -775.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-550.0f, 100.0f, -825.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-575.0f, 100.0f, -725.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-575.0f, 100.0f, -800.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-575.0f, 100.0f, -825.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-600.0f, 100.0f, -725.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);
	CItem::Create(D3DXVECTOR3(-600.0f, 100.0f, -825.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), "data\\MODEL\\coin_mini.x", NULL);


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
