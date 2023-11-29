//===============================================
//
// エフェクトの処理 [effect.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "effect.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
#include "texture.h"
#include "slow.h"
#include "game.h"
#include "meshfield.h"
#include "billboard.h"

//===============================================
// 無名名前空間
//===============================================
namespace {
	const float LIFE = (30.0f); // 寿命

	const D3DXCOLOR COLINFO[CEffect::TYPE_MAX] = {	// 種類別初期色の設定
		{1.0f, 1.0f, 1.0f, 1.0f,},
	};

	const float RADIUSINFO[CEffect::TYPE_MAX] = {	// 種類別半径の設定
		100.0f,
	};
}

//===============================================
// コンストラクタ
//===============================================
CEffect::CEffect()
{
	// 値のクリア
	m_Info.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_Info.fLife = 0;
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.fRadius = 0.0f;
	m_Info.Type = TYPE_NONE;
}

//===============================================
// デストラクタ
//===============================================
CEffect::~CEffect()
{

}

//===============================================
// 初期化処理
//===============================================
HRESULT CEffect::Init(void)
{
	// オブジェクトの初期化処理
	m_pObjectBilBoard = CObjectBillboard::Create(m_Info.pos, 6);
	m_pObjectBilBoard->BindTexture(CManager::GetInstance()->GetTexture()->Regist(CManager::GetInstance()->GetTexture()->GetFileName(CTexture::TYPE_EFFECT)));
	m_pObjectBilBoard->SetAlphaText(true);
	m_pObjectBilBoard->SetZTest(true);
	m_pObjectBilBoard->SetLighting(true);
	m_pObjectBilBoard->SetFusion(CObjectBillboard::FUSION_ADD);

	m_Info.fLife = LIFE;	// 体力の初期化
	m_Info.Type = TYPE_NONE;

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CEffect::Uninit(void)
{
	// オブジェクトの終了処理
	if (m_pObjectBilBoard != nullptr) {
		m_pObjectBilBoard->Uninit();
		m_pObjectBilBoard = nullptr;
	}

	Release();
}

//===============================================
// 更新処理
//===============================================
void CEffect::Update(void)
{
	m_Info.fLife -= CManager::GetInstance()->GetSlow()->Get();
	D3DXVECTOR3 nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float fHeight = CMeshField::GetHeight(m_Info.pos);

	if (m_Info.fLife < 0)
	{// 寿命がなくなった場合

		// 終了する
		Uninit();

		return;
	}

	D3DXVECTOR3 pos = GetPosition();	// 座標

	pos += m_Info.move * CManager::GetInstance()->GetSlow()->Get();

	// 座標
	SetPosition(pos);

	switch (m_Info.Type)
	{
	case TYPE_NONE:
		m_Info.col.a -= 0.05f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.fRadius += 0.1f * CManager::GetInstance()->GetSlow()->Get();
		break;

	case TYPE_SMAKE:	// 煙

		m_Info.col.a -= 0.035f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.move.y -= m_Info.move.y * 0.005f * CManager::GetInstance()->GetSlow()->Get();

		break;
	}

	if (m_Info.col.a < 0.0f || m_Info.fRadius < 0.0f)
	{// 値がひっくり返った
		Uninit();

		return;
	}

	InfoSet();
}

//===============================================
// 生成
//===============================================
CEffect *CEffect::Create(D3DXVECTOR3 pos, TYPE type)
{
	CEffect *pEffect = NULL;
	CTexture *pTexture = CManager::GetInstance()->GetTexture();	// テクスチャへのポインタ

	// エフェクトの生成
	pEffect = new CEffect;

	if (pEffect != NULL)
	{// 生成できた場合

		// 座標設定
		pEffect->SetPosition(pos);

		// 初期化処理
		pEffect->Init();

		// オブジェクトの種類の設定

		// 種類の設定
		pEffect->SetType(type);

		// 半径設定
		pEffect->RadiusSet();

		// 色の設定
		pEffect->ColorSet();

		pEffect->InfoSet();

		// テクスチャの割り当て
	}
	else
	{// 生成に失敗した場合
		return NULL;
	}

	return pEffect;
}

//===============================================
// 生成
//===============================================
CEffect *CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, float fLife, TYPE type)
{
	CEffect *pEffect = NULL;
	CTexture *pTexture = CManager::GetInstance()->GetTexture();	// テクスチャへのポインタ

	// エフェクトの生成
	pEffect = new CEffect();

	if (pEffect != NULL)
	{// 生成できた場合

		// 座標設定
		pEffect->SetPosition(pos);

		// 初期化処理
		pEffect->Init();

		// エフェクトの設定
		pEffect->SetType(type);

		// 半径設定
		pEffect->m_Info.fRadius = fRadius;

		// 寿命設定
		pEffect->m_Info.fLife = fLife;

		// 移動量設定
		pEffect->SetMove(move);

		// サイズの設定
		//pEffect->SetSize(pEffect->m_Info.fRadius, pEffect->m_Info.fRadius);

		// 色の設定
		pEffect->m_Info.col = col;

		pEffect->InfoSet();
	}
	else
	{// 生成に失敗した場合
		return NULL;
	}

	return pEffect;
}

//===============================================
// 色設定
//===============================================
void CEffect::ColorSet(void)
{
	// 種類ごとに色の設定
	m_Info.col = COLINFO[m_Info.Type];
	

	if (m_pObjectBilBoard == nullptr) {
		return;
	}

	m_pObjectBilBoard->SetCol(m_Info.col);
}

//===============================================
// サイズの設定
//===============================================
void CEffect::RadiusSet(void)
{
	// 半径の設定
	m_Info.fRadius = RADIUSINFO[m_Info.Type];

	if (m_pObjectBilBoard == nullptr) {
		return;
	}

	m_pObjectBilBoard->SetSize(m_Info.fRadius, m_Info.fRadius);
}

//===============================================
// 移動量の設定
//===============================================
void CEffect::SetMove(D3DXVECTOR3 move)
{
	m_Info.move = move;
}

//===============================================
// 情報基本設定
//===============================================
void CEffect::InfoSet(void)
{
	if (m_pObjectBilBoard == nullptr) {
		return;
	}

	m_pObjectBilBoard->SetPosition(m_Info.pos);
	m_pObjectBilBoard->SetCol(m_Info.col);
	m_pObjectBilBoard->SetSize(m_Info.fRadius, m_Info.fRadius);
}