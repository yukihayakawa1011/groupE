//==========================================================
//
// 捨てるアイテム [throwitem.cpp]
// Author : Ryosuke Ohhra
//
//==========================================================
#include "throwitem.h"
#include "billboard.h"
#include "manager.h"
#include "texture.h"
#include "number.h"

// 無名名前空間
namespace {
	const int DEF_PRI = (3);	// 優先順位
	const char* FILENAME[CThrowItem::TYPE_MAX] = {	// テクスチャファイル名
		"data\\TEXTURE\\item_icon1.png",
		"data\\TEXTURE\\item_icon0.png",
		"data\\TEXTURE\\item_icon2.png",
		"data\\TEXTURE\\item_icon3.png",
		"data\\TEXTURE\\item_icon4.png",
		"data\\TEXTURE\\item_icon5.png",
		"data\\TEXTURE\\item_icon6.png",
		"data\\TEXTURE\\item_icon8.png",
		"data\\TEXTURE\\item_icon10.png",
		"data\\TEXTURE\\item_icon7.png",
		"data\\TEXTURE\\item_icon9.png",
	};
}

//==========================================================
// コンストラクタ
//==========================================================
CThrowItem::CThrowItem()
{
	// 値のクリア
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++) {
		m_apObject[nCnt] = nullptr;
	}

	m_pObject = nullptr;

	for (int nCnt = 0; nCnt < MAX_ITEM; nCnt++) {
		m_pNumber[nCnt] = nullptr;
	} 

	m_nBeforeID = 0;
	m_nNowID = 0;
	m_nNextID = 0;
}

//==========================================================
// デストラクタ
//==========================================================
CThrowItem::~CThrowItem()
{

}

//==========================================================
// 生成
//==========================================================
CThrowItem * CThrowItem::Create(D3DXVECTOR3 * pPos, const float fUpHeight, const float fPolyWidth, const float fPolyHeight)
{
	CThrowItem *pThrowItem = nullptr;

	pThrowItem = new CThrowItem;

	if (pThrowItem != nullptr)
	{
		// 初期化処理
		pThrowItem->Init();

		// 親の設定
		pThrowItem->SetParent(pPos);

		// 相対座標の高さを設定
		pThrowItem->SetUpHeight(fUpHeight);

		// ポリゴンサイズを設定
		pThrowItem->SetPolySize(fPolyWidth, fPolyHeight);

		// 座標を設定
		pThrowItem->SetMixPosition();
	}

	return pThrowItem;
}

//==========================================================
// どのアイテムを選択しているか
//==========================================================
void CThrowItem::SetItem(int nThrowItemID)
{
	// 現在選択している番号
	m_nNowID = nThrowItemID;

	if (m_pObject != nullptr)
	{// 使用されていた場合

		// テクスチャ座標設定
		m_pObject->SetVtx(((float)(m_nNowID - 1) * 0.09f), 1.0f);
	}
}

//==========================================================
// 初期化処理
//==========================================================
HRESULT CThrowItem::Init(void)
{
	// ビルボード生成
	m_pObject = CObjectBillboard::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), DEF_PRI);
	m_pObject->SetDraw();
	m_pObject->SetAlphaText(false);
	m_pObject->SetLighting(true);
	m_pObject->SetZTest(false);
	m_pObject->SetFusion(CObjectBillboard::FUSION_NORMAL);
	m_pObject->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\item_icon.png"));

	// 数字生成
	/*for (int nCount = 0; nCount < MAX_ITEM; nCount++)
	{
		m_pNumber[nCount] = CNumber::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f, 20.0f);
	}*/
	
	return S_OK;
}

//==========================================================
// 終了処理
//==========================================================
void CThrowItem::Uninit(void)
{
	if (m_pObject != nullptr) { // 使用されていた場合

		// 終了処理
		m_pObject->Uninit();

		// 使用していない状態にする
		m_pObject = nullptr;
	}

	for (int nCount = 0; nCount < MAX_ITEM; nCount++)
	{
		if (m_pNumber[nCount] != nullptr)
		{// 使用されていた場合

			// 終了処理
			m_pNumber[nCount]->Uninit();

			// 使用していない状態にする
			m_pNumber[nCount] = nullptr;
		}
	}

	// 開放
	Release();
}

//==========================================================
// 更新処理
//==========================================================
void CThrowItem::Update(void)
{
	// 座標の更新
	SetMixPosition();
}

//==========================================================
// 幅と高さの適応
//==========================================================
void CThrowItem::SetPolySize(const float fWidth, const float fHeight)
{
	// 幅の設定
	{
		m_fPolyWidth = fWidth;
		if (m_fPolyWidth < 0.0f) {	// 値がマイナス
			m_fPolyWidth = 0.0f;
		}
	}

	// 高さの設定
	{
		m_fPolyHeight = fHeight;
		if (m_fPolyHeight < 0.0f) {	// 値がマイナス
			m_fPolyHeight = 0.0f;
		}
	}

	if (m_pObject != nullptr)
	{
		// 座標設定
		m_pObject->SetSize(m_fPolyWidth, m_fPolyHeight);
	}
}

//==========================================================
// 設定高さと混ぜた座標を設定
//==========================================================
void CThrowItem::SetMixPosition(void)
{
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 基準の座標
	if (m_pPos != nullptr) {	// 親が存在している
		pos = *m_pPos;
	}
	pos.y += m_fUpHeight;	// 設定された高さを上げる

	if (m_pObject != nullptr)
	{
		// 座標設定
		m_pObject->SetPosition(D3DXVECTOR3(pos));
	}
}