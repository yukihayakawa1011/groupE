//==========================================================
//
// ゲージ [gage.h]
// Author : Ibuki Okusada
//
//==========================================================
#include "gage.h"

// マクロ定義

//==========================================================
// コンストラクタ
//==========================================================
CGage::CGage()
{
	// 値のクリア
}

//==========================================================
// デストラクタ
//==========================================================
CGage::~CGage()
{

}

//==========================================================
// 初期化処理
//==========================================================
HRESULT CGage::Init(void)
{
	return S_OK;
}

//==========================================================
// 終了処理
//==========================================================
void CGage::Uninit(void)
{
	Release();
}

//==========================================================
// 更新処理
//==========================================================
void CGage::Update(void)
{

}

//==========================================================
// 生成
//==========================================================
CGage *CGage::Create(void)
{
	CGage *pSample = nullptr;

	pSample = new CGage;

	if (pSample != nullptr)
	{
		// 初期化処理
		pSample->Init();
	}

	return pSample;
}
