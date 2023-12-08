//==========================================================
//
// ノルマのUI [quataui.cpp]
// Author : Ryosuke Ohara
//
//==========================================================
#include "quataui.h"
#include "object2D.h"
#include "manager.h"
#include "texture.h"
#include "life.h"

// 無名名前空間
namespace {
	const int DEF_PRI = (7);	// 優先順位
	const char* FILENAME[CQuataUI::TYPE_MAX] = {	// テクスチャファイル名
		"data\\TEXTURE\\quata000.png",
		"data\\TEXTURE\\quata001.png",
		"data\\TEXTURE\\quata002.png",

	};
}

//==========================================================
// コンストラクタ
//==========================================================
CQuataUI::CQuataUI()
{
	// 値のクリア
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_nNumPlayer = 0;
}

//==========================================================
// デストラクタ
//==========================================================
CQuataUI::~CQuataUI()
{

}

//==========================================================
// 初期化処理
//==========================================================
HRESULT CQuataUI::Init(void)
{
	if (m_pObject == nullptr)
	{// 使用されていない場合


	}

	return S_OK;
}

//==========================================================
// 初期化処理
//==========================================================
HRESULT CQuataUI::Init(float fWidth, float fHeight)
{
	if (m_pObject == nullptr)
	{// 使用されていない場合

		m_pObject = CObject2D::Create(7);
		m_pObject->BindTexture(CManager::GetInstance()->GetTexture()->Regist(FILENAME[m_type]));
		m_pObject->SetPosition(m_pos);
		m_pObject->SetSize(fWidth, fHeight);
	}

	return S_OK;
}

//==========================================================
// 終了処理
//==========================================================
void CQuataUI::Uninit(void)
{
	if (m_pObject != nullptr)
	{
		m_pObject->Uninit();
		m_pObject = nullptr;
	}

	Release();
}

//==========================================================
// 更新処理
//==========================================================
void CQuataUI::Update(void)
{
	
}

//==========================================================
// 生成
//==========================================================
CQuataUI *CQuataUI::Create(D3DXVECTOR3 pos, QUATATYPE type, float fWidth, float fHeight)
{
	CQuataUI *pUI = nullptr;

	pUI = new CQuataUI;

	if (pUI != nullptr)
	{
		pUI->SetPosition(pos);
		pUI->SetType(type);
		// 初期化処理
		pUI->Init(fWidth, fHeight);
	}

	return pUI;
}