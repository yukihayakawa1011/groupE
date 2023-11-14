//==========================================================
//
// ボタン [gimmick_button.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "gimmick_button.h"
#include "model.h"
#include "manager.h"
#include "debugproc.h"

// マクロ定義
#define COLLISION_RANGE	(50.0f)

// 静的メンバ変数宣言
char *CGimmickButton::m_apFileName[MODEL_MAX] = {
	"data\\MODEL\\trans_button.x",
	"data\\MODEL\\button_frame.x",
};

//==========================================================
// コンストラクタ
//==========================================================
CGimmickButton::CGimmickButton()
{
	// 値のクリア
	for (int nCnt = 0; nCnt < MODEL_MAX; nCnt++)
	{
		m_apObj[nCnt] = nullptr;
	}

	m_state = STATE_NONE;
}

//==========================================================
// デストラクタ
//==========================================================
CGimmickButton::~CGimmickButton()
{

}

//==========================================================
// 初期化処理
//==========================================================
HRESULT CGimmickButton::Init(void)
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

	return S_OK;
}

//==========================================================
// 終了処理
//==========================================================
void CGimmickButton::Uninit(void)
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
void CGimmickButton::Update(void)
{
	// マトリックス設定
	SetMtxWorld();

	// 状態に合わせてボタンの色を変更
	switch (m_state)
	{
	case STATE_NONE:	// 何もない
		
		break;

	case STATE_PRESS:	// 押されている

		break;
	}

	m_state = STATE_NONE;
}

//==========================================================
// 生成
//==========================================================
CGimmickButton *CGimmickButton::Create(const D3DXVECTOR3 pos)
{
	CGimmickButton *pSample = nullptr;

	pSample = new CGimmickButton;

	if (pSample != nullptr)
	{
		// 初期化処理
		pSample->Init();
		pSample->SetPosition(pos);
		pSample->BindType(TYPE_BUTTON);
	}

	return pSample;
}

//==========================================================
// 判定確認
//==========================================================
bool CGimmickButton::CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, D3DXVECTOR3 &SetPos, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, int nAction, CGimmick **ppGimmick)
{
	bool bValue = false;
	D3DXVECTOR3 ObjPos = GetPosition();
	D3DXVECTOR3 ObjRot = GetRotation();

	// 範囲内チェック
	float fLength =
		sqrtf((pos.x - ObjPos.x) * (pos.x - ObjPos.x)
			+ (pos.z - ObjPos.z) * (pos.z - ObjPos.z));

	if (fLength > COLLISION_RANGE){		// 範囲外
		return bValue;
	}

	bValue = true;			// 触れた状態
	m_state = STATE_PRESS;		// 押された状態にする
	CManager::GetInstance()->GetDebugProc()->Print("押されているよー\n");

	return bValue;
}