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
#include "player.h"

// 静的メンバ変数宣言
CPlayer **CThrowItem::m_ppPlayer = nullptr;

// 無名名前空間
namespace {
	const int DEF_PRI = (3);	// 優先順位
	const char* FILENAME[CThrowItem::TYPE_MAX] = {	// テクスチャファイル名
		"data\\TEXTURE\\item_icon1.png",
		"data\\TEXTURE\\item_icon0.png",
		"data\\TEXTURE\\item_icon2.png",
		"data\\TEXTURE\\item_icon4.png",
		"data\\TEXTURE\\item_icon3.png",
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
// 初期化処理
//==========================================================
HRESULT CThrowItem::Init(void)
{
	// オブジェクトの生成
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++) {
		m_apObject[nCnt] = CObjectBillboard::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), DEF_PRI + nCnt);
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

	CPlayer *pPlayer = CPlayer::GetTop();

	while (pPlayer != nullptr)
	{
		CPlayer *pPlayerNext = pPlayer->GetNext();	// 次を保持

		int nOldId, nId, nNextId;

		// 現在選択している番号
		nId = pPlayer->GetThrowItemId();

		// 選択している番号の一個前
		nOldId = nId - 1;

		// 選択している番号の次
		nNextId = nId + 1;

		if (nOldId < 0)
		{
			nOldId = 10;
		}

		if (nNextId > 10)
		{
			nNextId = 0;
		}

		// サイズを設定
		{
			if (m_apObject[nOldId] == nullptr || m_apObject[nId] == nullptr || m_apObject[nNextId] == nullptr) {
				return;
			}

			m_apObject[nOldId]->SetSize(m_fPolyWidth, m_fPolyHeight);

			m_apObject[nId]->SetSize(m_fPolyWidth, m_fPolyHeight);

			m_apObject[nNextId]->SetSize(m_fPolyWidth, m_fPolyHeight);
		}

		pPlayer = pPlayerNext;
	}
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

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++) {
		if (m_apObject[nCnt] == nullptr) {	// 使用されていない
			continue;
		}

		// 座標設定
		m_apObject[nCnt]->SetPosition(D3DXVECTOR3(pos));
	}
}