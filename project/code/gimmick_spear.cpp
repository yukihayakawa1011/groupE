//==========================================================
//
// ギミック生える槍 [gimmick_spear.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "gimmick_spear.h"
#include "model.h"
#include "manager.h"
#include "debugproc.h"
#include "player.h"
#include "Xfile.h"

// マクロ定義
#define COLLISION_RANGE	(50.0f)	// 当たり判定サイズ
#define SET_POSY			(-180.0f)	// 地面に埋まってる時の座標設定

// 静的メンバ変数宣言
char *CGimmickSpear::m_pFileName = {
	"data\\MODEL\\spear.x",
};

// 静的メンバ変数宣言
int CGimmickSpear::m_aStateSetCount[CGimmickSpear::STATE_MAX] = {
	30,
	30,
	60,
	70,
};

float CGimmickSpear::m_aStateDiffMulti[CGimmickSpear::STATE_MAX] = {
	0.03f,
	0.35f,
	0.03f,
	0.03f,
};

//==========================================================
// コンストラクタ
//==========================================================
CGimmickSpear::CGimmickSpear()
{
	// 値のクリア
	m_pObj = nullptr;
	m_state = STATE_NONE;
}

//==========================================================
// デストラクタ
//==========================================================
CGimmickSpear::~CGimmickSpear()
{

}

//==========================================================
// 初期化処理
//==========================================================
HRESULT CGimmickSpear::Init(void)
{
	// モデルの生成
	m_pObj = CModel::Create(m_pFileName);

	if (m_pObj != nullptr)
	{
		m_pObj->SetShadow(true);
		m_pObj->SetParent(GetMtxWorld());
		m_pObj->SetCurrentPosition(D3DXVECTOR3(0.0f, SET_POSY, 0.0f));
	}

	return S_OK;
}

//==========================================================
// 終了処理
//==========================================================
void CGimmickSpear::Uninit(void)
{
	// 値のクリア
	if (m_pObj != nullptr)
	{
		m_pObj->Uninit();
		m_pObj = nullptr;
	}

	// リストから削除
	ListOut();

	// リリース
	Release();
}

//==========================================================
// 更新処理
//==========================================================
void CGimmickSpear::Update(void)
{
	// マトリックス設定
	SetMtxWorld();

	// 状態管理
	StateSet();

	CManager::GetInstance()->GetDebugProc()->Print("槍の状態[ %d ] : カウント [ %d ]\n", m_state, m_nStateCounter);


	if (m_pObj != nullptr) {	// オブジェクトが使われている
		D3DXVECTOR3 pos = m_pObj->GetCurrentPosition();
		D3DXVECTOR3 posDiff = m_PosDest - pos;

		pos += posDiff * m_fDiffMulti;
		m_pObj->SetCurrentPosition(pos);
	}
}

//==========================================================
// 生成
//==========================================================
CGimmickSpear *CGimmickSpear::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CGimmickSpear *pSample = nullptr;

	pSample = new CGimmickSpear;

	if (pSample != nullptr)
	{
		// 初期化処理
		pSample->Init();

		// 値の設定
		pSample->SetPosition(pos);
		pSample->SetRotation(rot);
		pSample->BindType(TYPE_SPEAR);
	}

	return pSample;
}

//==========================================================
// 状態管理
//==========================================================
void CGimmickSpear::StateSet(void)
{
	m_nStateCounter--;

	if (m_nStateCounter > 0) {
		return;
	}
	// 状態に合わせてボタンの色を変更
	switch (m_state)
	{
	case STATE_NONE:
	{
		m_state = STATE_APPEAR;
		m_PosDest.y = 0.0f;
	}
	break;

	case STATE_APPEAR:
	{
		m_state = STATE_ATKNOW;
		m_PosDest.y = 0.0f;
	}
	break;

	case STATE_ATKNOW:
	{
		m_state = STATE_BACK;
		m_PosDest.y = SET_POSY;
	}
	break;

	case STATE_BACK:
	{
		m_state = STATE_NONE;
		m_PosDest.y = SET_POSY;
	}
	break;

	default:

		break;
	}

	// 次のカウント設定
	m_nStateCounter = m_aStateSetCount[m_state];
	m_fDiffMulti = m_aStateDiffMulti[m_state];
}

//==========================================================
// 判定確認
//==========================================================
bool CGimmickSpear::CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, D3DXVECTOR3 &SetPos, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, int nAction, CGimmick **ppGimmick)
{
	if (m_state >= STATE_NONE) {	// 開く扉
		return false;
	}

	bool bValue = false;
	D3DXVECTOR3 ObjPos = GetPosition();
	D3DXVECTOR3 ObjRot = GetRotation();

	CXFile *pFile = CManager::GetInstance()->GetModelFile();
	D3DXVECTOR3 vtxObjMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vtxObjMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 向きを反映
	m_pObj->SetRotSize(vtxObjMax,
		vtxObjMin,
		pFile->GetMax(m_pObj->GetId()),
		pFile->GetMin(m_pObj->GetId()),
		ObjRot.y);

	//// X
	//if (pos.y + vtxMax.y > ObjPos.y + vtxObjMin.y
	//	&& pos.y + vtxMin.y < ObjPos.y + vtxObjMax.y
	//	&& pos.z + vtxMax.z > ObjPos.z + vtxObjMin.z
	//	&& pos.z + vtxMin.z < ObjPos.z + vtxObjMax.z)
	//{//範囲内にある
	//	if (posOld.x + vtxMin.x >= ObjPos.x + vtxObjMax.x
	//		&& pos.x + vtxMin.x < ObjPos.x + vtxObjMax.x)
	//	{//右から左にめり込んだ
	//		move.x = 0.0f;
	//		pos.x = ObjPos.x + vtxObjMax.x - vtxMin.x + 0.1f + move.x;

	//		if ((D3DX_PI * 0.5f == GetRotation().y || -D3DX_PI * 0.5f == GetRotation().y) && nAction == CPlayer::ACTION_ATK && m_state == STATE_NONE) {	// 攻撃した
	//			m_state = STATE_ROTATE;
	//			m_RotDest.y += D3DX_PI;

	//			if (m_RotDest.y > D3DX_PI) {
	//				m_RotDest.y += -D3DX_PI * 2;
	//			}

	//			if (ppGimmick != nullptr) {
	//				*ppGimmick = this;
	//				SetPos.z = SET_POSZ;
	//			}
	//		}
	//	}
	//	else if (posOld.x + vtxMax.x <= ObjPos.x + vtxObjMin.x
	//		&& pos.x + vtxMax.x > ObjPos.x + vtxObjMin.x)
	//	{//左から右にめり込んだ
	//	 //位置を戻す
	//		move.x = 0.0f;
	//		pos.x = ObjPos.x + vtxObjMin.x - vtxMax.x - 0.1f + move.x;

	//		if ((D3DX_PI * 0.5f == GetRotation().y || -D3DX_PI * 0.5f == GetRotation().y) && nAction == CPlayer::ACTION_ATK && m_state == STATE_NONE) {	// 攻撃した
	//			m_state = STATE_ROTATE;
	//			m_RotDest.y += D3DX_PI;

	//			if (m_RotDest.y > D3DX_PI) {
	//				m_RotDest.y += -D3DX_PI * 2;
	//			}

	//			if (ppGimmick != nullptr) {
	//				*ppGimmick = this;
	//				SetPos.z = -SET_POSZ;
	//			}
	//		}
	//	}
	//}

	////Z
	//if (pos.x + vtxMax.x > ObjPos.x + vtxObjMin.x
	//	&& pos.x + vtxMin.x < ObjPos.x + vtxObjMax.x
	//	&& pos.y + vtxMax.y > ObjPos.y + vtxObjMin.y
	//	&& pos.y + vtxMin.y < ObjPos.y + vtxObjMax.y)
	//{//範囲内にある
	//	if (posOld.z + vtxMin.z >= ObjPos.z + vtxObjMax.z
	//		&& pos.z + vtxMin.z < ObjPos.z + vtxObjMax.z)
	//	{//奥から手前にめり込んだ
	//	 //位置を戻す
	//		move.z = 0.0f;
	//		pos.z = ObjPos.z + vtxObjMax.z - vtxMin.z + 0.1f + move.z;

	//		if ((D3DX_PI * 1.0f == GetRotation().y || -D3DX_PI * 1.0f == GetRotation().y || 0.0f == GetRotation().y) && nAction == CPlayer::ACTION_ATK && m_state == STATE_NONE) {	// 攻撃した
	//			m_state = STATE_ROTATE;
	//			m_RotDest.y += D3DX_PI;

	//			if (m_RotDest.y > D3DX_PI) {
	//				m_RotDest.y += -D3DX_PI * 2;
	//			}

	//			if (ppGimmick != nullptr) {
	//				*ppGimmick = this;
	//				SetPos.z = SET_POSZ;
	//			}
	//		}
	//	}
	//	else if (posOld.z + vtxMax.z <= ObjPos.z + vtxObjMin.z
	//		&& pos.z + vtxMax.z > ObjPos.z + vtxObjMin.z)
	//	{//手前から奥にめり込んだ
	//	 //位置を戻す
	//		move.z = 0.0f;
	//		pos.z = ObjPos.z + vtxObjMin.z - vtxMax.z - 0.1f + move.z;

	//		if ((D3DX_PI * 1.0f == GetRotation().y || -D3DX_PI * 1.0f == GetRotation().y || 0.0f == GetRotation().y) && nAction == CPlayer::ACTION_ATK && m_state == STATE_NONE) {	// 攻撃した
	//			m_state = STATE_ROTATE;
	//			m_RotDest.y += D3DX_PI;

	//			if (m_RotDest.y > D3DX_PI) {
	//				m_RotDest.y += -D3DX_PI * 2;
	//			}

	//			if (ppGimmick != nullptr) {
	//				*ppGimmick = this;
	//				SetPos.z = -SET_POSZ;
	//			}
	//		}
	//	}
	//}

	////Y
	//if (pos.x + vtxMax.x > ObjPos.x + vtxObjMin.x
	//	&& pos.x + vtxMin.x < ObjPos.x + vtxObjMax.x
	//	&& pos.z + vtxMax.z > ObjPos.z + vtxObjMin.z
	//	&& pos.z + vtxMin.z < ObjPos.z + vtxObjMax.z)
	//{//範囲内にある
	// //上からの判定
	//	if (posOld.y + vtxMin.y >= ObjPos.y + vtxObjMax.y
	//		&& pos.y + vtxMin.y < ObjPos.y + vtxObjMax.y)
	//	{//上からめり込んだ
	//	 //上にのせる
	//		pos.y = ObjPos.y + vtxObjMax.y - vtxMin.y;
	//		move.y = 0.0f;
	//		bValue = true;
	//	}
	//}

	return bValue;
}