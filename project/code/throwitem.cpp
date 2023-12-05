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
	if (m_nNowID > nThrowItemID || (nThrowItemID == TYPE_MAX && m_nNowID == 0))
	{
		m_apObject[m_nNextID]->SetDraw(false);
	}

	if (m_nNowID < nThrowItemID)
	{
		m_apObject[m_nBeforeID]->SetDraw(false);
	}

	// 現在選択している番号
	m_nNowID = nThrowItemID;

	// 選択している番号の前
	m_nBeforeID = (m_nNowID + TYPE_MAX - 1) % TYPE_MAX;;

	// 選択している番号の次
	m_nNextID = (m_nNowID + 1) % TYPE_MAX;

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++) {
		m_apObject[nCnt]->SetDraw(false);
	}

	// サイズを設定
	{
		if (m_apObject[m_nBeforeID] == nullptr || m_apObject[m_nNowID] == nullptr || m_apObject[m_nNextID] == nullptr) {
			return;
		}

		m_apObject[m_nBeforeID]->SetSize(m_fPolyWidth, m_fPolyHeight);
		m_apObject[m_nNowID]->SetSize(m_fPolyWidth, m_fPolyHeight);
		m_apObject[m_nNextID]->SetSize(m_fPolyWidth, m_fPolyHeight);

		m_apObject[m_nBeforeID]->SetDraw(true);
		m_apObject[m_nNowID]->SetDraw(true);
		m_apObject[m_nNextID]->SetDraw(true);
	}
}

//==========================================================
// 初期化処理
//==========================================================
HRESULT CThrowItem::Init(void)
{
	// オブジェクトの生成
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++) {
		m_apObject[nCnt] = CObjectBillboard::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), DEF_PRI + nCnt);
		m_apObject[nCnt]->SetDraw(false);
		m_apObject[nCnt]->SetAlphaText(false);
		m_apObject[nCnt]->SetLighting(true);
		m_apObject[nCnt]->SetZTest(false);
		m_apObject[nCnt]->SetFusion(CObjectBillboard::FUSION_NORMAL);
		m_apObject[nCnt]->BindTexture(CManager::GetInstance()->GetTexture()->Regist(FILENAME[nCnt]));
	}

	return S_OK;
}

//==========================================================
// 終了処理
//==========================================================
void CThrowItem::Uninit(void)
{
	// オブジェクトの終了処理
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++) {
		if (m_apObject[nCnt] != nullptr) {
			m_apObject[nCnt]->Uninit();
			m_apObject[nCnt] = nullptr;
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

	// オブジェクトに適応させる
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++) {
		if (m_apObject[nCnt] == nullptr) {	// 使用されていない
			continue;
		}

		// 座標設定
		m_apObject[nCnt]->SetSize(m_fPolyWidth, m_fPolyHeight);
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

	if (m_apObject[m_nBeforeID] == nullptr || m_apObject[m_nNowID] == nullptr || m_apObject[m_nNextID] == nullptr) {
		return;
	}

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++) {
		if (m_apObject[nCnt] == nullptr) {	// 使用されていない
			continue;
		}

		// 座標設定
		m_apObject[nCnt]->SetPosition(D3DXVECTOR3(pos));
	}

	// 座標設定
	m_apObject[m_nBeforeID]->SetPosition(D3DXVECTOR3(pos.x - 50.0f, pos.y, pos.z));
	m_apObject[m_nNowID]->SetPosition(D3DXVECTOR3(pos));
	m_apObject[m_nNextID]->SetPosition(D3DXVECTOR3(pos.x + 50.0f, pos.y, pos.z));
}