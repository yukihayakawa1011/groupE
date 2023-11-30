//==========================================================
//
// ギミックレバー [gimmick_lever.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "gimmick_lever.h"
#include "model.h"
#include "manager.h"
#include "debugproc.h"
#include "player.h"

// マクロ定義
#define COLLISION_RANGE	(50.0f)
#define INTERVAL			(90)

// 静的メンバ変数宣言
char *CGimmickLever::m_apFileName[MODEL_MAX] = {
	"data\\MODEL\\lever_frame.x",
	"data\\MODEL\\lever.x",
};

//==========================================================
// コンストラクタ
//==========================================================
CGimmickLever::CGimmickLever()
{
	// 値のクリア
	for (int nCnt = 0; nCnt < MODEL_MAX; nCnt++)
	{
		m_apObj[nCnt] = nullptr;
	}

	m_nInterval = 0;
	m_state = STATE_NONE;
}

//==========================================================
// デストラクタ
//==========================================================
CGimmickLever::~CGimmickLever()
{

}

//==========================================================
// 初期化処理
//==========================================================
HRESULT CGimmickLever::Init(void)
{
	// モデルの生成
	for (int nCnt = 0; nCnt < MODEL_MAX; nCnt++)
	{
		m_apObj[nCnt] = CModel::Create(m_apFileName[nCnt]);

		if (m_apObj[nCnt] != nullptr)
		{
			m_apObj[nCnt]->SetShadow(false);
			m_apObj[nCnt]->SetParent(GetMtxWorld());
		}
	}

	m_apObj[MODEL_BUTTON]->SetCurrentRotation(D3DXVECTOR3(D3DX_PI * 0.15f, 0.0f, 0.0f));

	return S_OK;
}

//==========================================================
// 終了処理
//==========================================================
void CGimmickLever::Uninit(void)
{
	// 値のクリア
	for (int nCnt = 0; nCnt < MODEL_MAX; nCnt++)
	{
		if (m_apObj[nCnt] != nullptr)
		{
			m_apObj[nCnt]->Uninit();
			m_apObj[nCnt] = nullptr;
		}
	}

	// リストから削除
	ListOut();

	// リリース
	Release();
}

//==========================================================
// 更新処理
//==========================================================
void CGimmickLever::Update(void)
{
	if (m_nInterval > 0){
		m_nInterval--;
	}

	// マトリックス設定
	SetMtxWorld();

	// 状態に合わせてボタンの色を変更
	switch (m_state)
	{
	case STATE_NONE:	// 何もない
		m_RotDest = D3DXVECTOR3(D3DX_PI * 0.15f, 0.0f, 0.0f);
		break;

	case STATE_PRESS:	// 押されている
		m_RotDest = D3DXVECTOR3(-D3DX_PI * 0.15f, 0.0f, 0.0f);
		break;
	}

	if (m_apObj[MODEL_BUTTON] != nullptr) {
		D3DXVECTOR3 rot = m_apObj[MODEL_BUTTON]->GetCurrentRotation();
		D3DXVECTOR3 rotDiff = m_RotDest - rot;

		rot += rotDiff * 0.1f;
		m_apObj[MODEL_BUTTON]->SetCurrentRotation(rot);
	}
}

//==========================================================
// 生成
//==========================================================
CGimmickLever *CGimmickLever::Create(const D3DXVECTOR3 pos)
{
	CGimmickLever *pSample = nullptr;

	pSample = new CGimmickLever;

	if (pSample != nullptr)
	{
		// 初期化処理
		pSample->Init();
	
		pSample->SetPosition(pos);
		pSample->BindType(TYPE_LEVER);
	}

	return pSample;
}

//==========================================================
// 判定確認
//==========================================================
bool CGimmickLever::CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, D3DXVECTOR3 &SetPos, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, int nAction, CGimmick **ppGimmick, bool* bLand)
{
	bool bValue = false;
	D3DXVECTOR3 ObjPos = GetPosition();
	D3DXVECTOR3 ObjRot = GetRotation();

	// 範囲内チェック
	float fLength =
		sqrtf((pos.x - ObjPos.x) * (pos.x - ObjPos.x)
			+ (pos.z - ObjPos.z) * (pos.z - ObjPos.z));

	if (fLength > COLLISION_RANGE) {		// 範囲外
		return bValue;
	}

	if (nAction != CPlayer::ACTION_ATK) {
		return bValue;
	}

	if(m_nInterval > 0)
	{
		return bValue;
	}
	
	m_state = (STATE)(m_state ^ 1);	// 押された状態にする
	m_nInterval = INTERVAL;			// インターバル

	return bValue;
}