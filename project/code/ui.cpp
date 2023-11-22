//==========================================================
//
// サンプルタスク [sample_task.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "ui.h"
#include "object2D.h"
#include "manager.h"
#include "texture.h"

// マクロ定義
#define TEXTURE_MONEY	("data\\TEXTURE\\money0.png")	//お金の単位のテクスチャ

//==========================================================
// コンストラクタ
//==========================================================
CUI::CUI()
{
	// 値のクリア
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);;
	m_type = TYPE_NORMAL;

}

//==========================================================
// デストラクタ
//==========================================================
CUI::~CUI()
{

}

//==========================================================
// 初期化処理
//==========================================================
HRESULT CUI::Init(void)
{
	for (int nCnt = 0; nCnt < NUM_OBJ; nCnt++)
	{
		m_pObject[nCnt] = CObject2D::Create();
	}

	m_pObject[0]->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\frame0.png"));
	m_pObject[0]->SetPosition(m_pos);
	m_pObject[0]->SetRotation(m_rot);
	m_pObject[0]->SetLength(300.0f, 125.0f);

	m_pObject[1]->BindTexture(CManager::GetInstance()->GetTexture()->Regist(TEXTURE_MONEY));
	m_pObject[1]->SetPosition(D3DXVECTOR3(m_pos.x + 50.0f, m_pos.y + 38.0f, m_pos.z));
	m_pObject[1]->SetRotation(m_rot);
	m_pObject[1]->SetLength(50.0f, 25.0f);

	m_pObject[2]->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\player_icon0.png"));
	m_pObject[2]->SetPosition(D3DXVECTOR3(m_pos.x - 110.0f, m_pos.y - 20.0f, m_pos.z));
	m_pObject[2]->SetRotation(m_rot);
	m_pObject[2]->SetLength(70.0f, 70.0f);

	return S_OK;
}

//==========================================================
// 初期化処理
//==========================================================
HRESULT CUI::Init(const char *pFileFrameName, const char *pFilePIconName)
{
	for (int nCnt = 0; nCnt < NUM_OBJ; nCnt++)
	{
		m_pObject[nCnt] = CObject2D::Create(7);
	}

	//フレーム
	m_pObject[0]->BindTexture(CManager::GetInstance()->GetTexture()->Regist(pFileFrameName));
	m_pObject[0]->SetPosition(m_pos);
	m_pObject[0]->SetLength(350.0f, 125.0f);

	//お金の単位
	m_pObject[1]->BindTexture(CManager::GetInstance()->GetTexture()->Regist(TEXTURE_MONEY));
	m_pObject[1]->SetLength(50.0f, 25.0f);

	//顔
	m_pObject[2]->BindTexture(CManager::GetInstance()->GetTexture()->Regist(pFilePIconName));
	m_pObject[2]->SetLength(70.0f, 70.0f);

	//タイプごとの位置設定
	if (m_type == TYPE_LEFTUP)
	{
		m_pObject[1]->SetPosition(D3DXVECTOR3(m_pos.x + 125.0f, m_pos.y - 38.0f, m_pos.z));	//単位
		m_pObject[2]->SetPosition(D3DXVECTOR3(m_pos.x - 135.0f, m_pos.y + 15.0f, m_pos.z));	//顔
	}
	else if (m_type == TYPE_RIGHTUP)
	{
		m_pObject[1]->SetPosition(D3DXVECTOR3(m_pos.x + 130.0f, m_pos.y - 38.0f, m_pos.z)); //単位
		m_pObject[2]->SetPosition(D3DXVECTOR3(m_pos.x + 130.0f, m_pos.y + 15.0f, m_pos.z));	//顔
	}
	else if (m_type == TYPE_LEFTDOWN)
	{
		m_pObject[1]->SetPosition(D3DXVECTOR3(m_pos.x + 125.0f, m_pos.y + 38.0f, m_pos.z)); //単位
		m_pObject[2]->SetPosition(D3DXVECTOR3(m_pos.x - 130.0f, m_pos.y - 20.0f, m_pos.z));	//顔
	}
	else if (m_type == TYPE_RIGHTDOWN)
	{	
		m_pObject[1]->SetPosition(D3DXVECTOR3(m_pos.x + 130.0f, m_pos.y + 38.0f, m_pos.z)); //単位
		m_pObject[2]->SetPosition(D3DXVECTOR3(m_pos.x + 130.0f, m_pos.y - 20.0f, m_pos.z));	//顔
	}

	return S_OK;
}

//==========================================================
// 終了処理
//==========================================================
void CUI::Uninit(void)
{
	Release();

	for (int nCnt = 0; nCnt < NUM_OBJ; nCnt++)
	{
		if (nullptr != m_pObject[nCnt]) {
			m_pObject[nCnt]->Uninit();
			m_pObject[nCnt] = NULL;
		}
	}

	
}

//==========================================================
// 更新処理
//==========================================================
void CUI::Update(void)
{
	//サイズの設定
	for (int nCnt = 0; nCnt < NUM_OBJ; nCnt++)
	{
		m_pObject[nCnt]->SetVtx();
	}
}

//==========================================================
// 生成
//==========================================================
CUI *CUI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *pFileFrameName, const char *pFilePIconName, TYPE type)
{
	CUI *pUI = nullptr;

	pUI = new CUI;

	if (pUI != nullptr)
	{
		pUI->SetPosition(pos);
		pUI->SetRotation(rot);
		pUI->SetType(type);
		// 初期化処理
		pUI->Init(pFileFrameName,pFilePIconName);
	}	

	return pUI;
}