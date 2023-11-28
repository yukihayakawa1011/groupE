//==========================================================
//
// 弾 [bullet.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "bullet.h"
#include "model.h"

// 無名名前空間
namespace {
	const char* FILENAME = "data\\MODEL\\bullet.x";	// ファイル名
	const int SETLIFE = (240);	// 弾の設定寿命
}

//==========================================================
// コンストラクタ
//==========================================================
CBullet::CBullet()
{
	// 値のクリア
	m_pObject = nullptr;
	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
}

//==========================================================
// デストラクタ
//==========================================================
CBullet::~CBullet()
{

}

//==========================================================
// 初期化処理
//==========================================================
HRESULT CBullet::Init(void)
{
	// オブジェクトの生成
	m_pObject = CModel::Create(FILENAME);
	m_pObject->SetParent(&m_Info.mtxWorld);

	// 寿命の設定
	m_nLife = SETLIFE;

	return S_OK;
}

//==========================================================
// 終了処理
//==========================================================
void CBullet::Uninit(void)
{
	// オブジェクトの終了
	if (m_pObject != nullptr) {
		m_pObject->Uninit();
		m_pObject = nullptr;
	}

	// 開放
	Release();
}

//==========================================================
// 更新処理
//==========================================================
void CBullet::Update(void)
{
	// 操作関連
	Controller();

	// マトリックス反映
	SetMatrix();

	// 寿命確認
	if (m_nLife <= 0) {	// 寿命がなくなった
		Uninit();	// 終了
	}
	else {
		m_nLife--;
	}
}

//==========================================================
// 生成
//==========================================================
CBullet *CBullet::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot, const D3DXVECTOR3 &move)
{
	CBullet *pBullet = nullptr;

	pBullet = new CBullet;

	if (pBullet != nullptr)
	{
		// 初期化処理
		pBullet->Init();

		// 座標反映
		pBullet->SetPosition(pos);

		// 向き反映
		pBullet->SetRotation(rot);

		// 移動量反映
		pBullet->SetMove(move);
	}

	return pBullet;
}

//==========================================================
// マトリックス設定
//==========================================================
void CBullet::SetMatrix(void)
{
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_Info.mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Info.rot.y, m_Info.rot.x, m_Info.rot.z);
	D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);
	D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxTrans);
}

//==========================================================
// 操作関連
//==========================================================
void CBullet::Controller(void)
{
	// 移動
	m_Info.pos += m_Info.move;
}