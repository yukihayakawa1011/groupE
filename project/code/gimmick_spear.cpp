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
#define COLLISION_RANGE	(50.0f)
#define UPPOSITION		(150.0f)
#define ROTATE_SPEED		(D3DX_PI * 0.05f)
#define SET_POSZ			(75.0f)

// 静的メンバ変数宣言
char *CGimmickSpear::m_pFileName = {
	"data\\MODEL\\start_door.x",
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

	// 状態に合わせてボタンの色を変更
	switch (m_state)
	{
	case STATE_NONE:	// 何もない

		break;

	case STATE_ROTATE:	// 押されている
	{
		if (m_pObj == nullptr) {
			return;
		}

		D3DXVECTOR3 rot = m_pObj->GetCurrentRotation();

		rot.y += ROTATE_SPEED;

		m_pObj->SetCurrentRotation(rot);

		if (rot.y >= m_RotDest.y)
		{// 超えた
			m_state = STATE_NONE;
			m_RotDest.y = 0.0f;
			rot.y = 0.0f;
			m_pObj->SetCurrentRotation(rot);
		}
	}
	break;
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
		pSample->BindType(TYPE_ROTATEDOOR);
	}

	return pSample;
}

//==========================================================
// 判定確認
//==========================================================
bool CGimmickSpear::CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, D3DXVECTOR3 &SetPos, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, int nAction, CGimmick **ppGimmick)
{
	if (m_state == STATE_ROTATE) {	// 開く扉
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

	// X
	if (pos.y + vtxMax.y > ObjPos.y + vtxObjMin.y
		&& pos.y + vtxMin.y < ObjPos.y + vtxObjMax.y
		&& pos.z + vtxMax.z > ObjPos.z + vtxObjMin.z
		&& pos.z + vtxMin.z < ObjPos.z + vtxObjMax.z)
	{//範囲内にある
		if (posOld.x + vtxMin.x >= ObjPos.x + vtxObjMax.x
			&& pos.x + vtxMin.x < ObjPos.x + vtxObjMax.x)
		{//右から左にめり込んだ
			move.x = 0.0f;
			pos.x = ObjPos.x + vtxObjMax.x - vtxMin.x + 0.1f + move.x;

			if ((D3DX_PI * 0.5f == GetRotation().y || -D3DX_PI * 0.5f == GetRotation().y) && nAction == CPlayer::ACTION_ATK && m_state == STATE_NONE) {	// 攻撃した
				m_state = STATE_ROTATE;
				m_RotDest.y += D3DX_PI;

				if (m_RotDest.y > D3DX_PI) {
					m_RotDest.y += -D3DX_PI * 2;
				}

				if (ppGimmick != nullptr) {
					*ppGimmick = this;
					SetPos.z = SET_POSZ;
				}
			}
		}
		else if (posOld.x + vtxMax.x <= ObjPos.x + vtxObjMin.x
			&& pos.x + vtxMax.x > ObjPos.x + vtxObjMin.x)
		{//左から右にめり込んだ
		 //位置を戻す
			move.x = 0.0f;
			pos.x = ObjPos.x + vtxObjMin.x - vtxMax.x - 0.1f + move.x;

			if ((D3DX_PI * 0.5f == GetRotation().y || -D3DX_PI * 0.5f == GetRotation().y) && nAction == CPlayer::ACTION_ATK && m_state == STATE_NONE) {	// 攻撃した
				m_state = STATE_ROTATE;
				m_RotDest.y += D3DX_PI;

				if (m_RotDest.y > D3DX_PI) {
					m_RotDest.y += -D3DX_PI * 2;
				}

				if (ppGimmick != nullptr) {
					*ppGimmick = this;
					SetPos.z = -SET_POSZ;
				}
			}
		}
	}

	//Z
	if (pos.x + vtxMax.x > ObjPos.x + vtxObjMin.x
		&& pos.x + vtxMin.x < ObjPos.x + vtxObjMax.x
		&& pos.y + vtxMax.y > ObjPos.y + vtxObjMin.y
		&& pos.y + vtxMin.y < ObjPos.y + vtxObjMax.y)
	{//範囲内にある
		if (posOld.z + vtxMin.z >= ObjPos.z + vtxObjMax.z
			&& pos.z + vtxMin.z < ObjPos.z + vtxObjMax.z)
		{//奥から手前にめり込んだ
		 //位置を戻す
			move.z = 0.0f;
			pos.z = ObjPos.z + vtxObjMax.z - vtxMin.z + 0.1f + move.z;

			if ((D3DX_PI * 1.0f == GetRotation().y || -D3DX_PI * 1.0f == GetRotation().y || 0.0f == GetRotation().y) && nAction == CPlayer::ACTION_ATK && m_state == STATE_NONE) {	// 攻撃した
				m_state = STATE_ROTATE;
				m_RotDest.y += D3DX_PI;

				if (m_RotDest.y > D3DX_PI) {
					m_RotDest.y += -D3DX_PI * 2;
				}

				if (ppGimmick != nullptr) {
					*ppGimmick = this;
					SetPos.z = SET_POSZ;
				}
			}
		}
		else if (posOld.z + vtxMax.z <= ObjPos.z + vtxObjMin.z
			&& pos.z + vtxMax.z > ObjPos.z + vtxObjMin.z)
		{//手前から奥にめり込んだ
		 //位置を戻す
			move.z = 0.0f;
			pos.z = ObjPos.z + vtxObjMin.z - vtxMax.z - 0.1f + move.z;

			if ((D3DX_PI * 1.0f == GetRotation().y || -D3DX_PI * 1.0f == GetRotation().y || 0.0f == GetRotation().y) && nAction == CPlayer::ACTION_ATK && m_state == STATE_NONE) {	// 攻撃した
				m_state = STATE_ROTATE;
				m_RotDest.y += D3DX_PI;

				if (m_RotDest.y > D3DX_PI) {
					m_RotDest.y += -D3DX_PI * 2;
				}

				if (ppGimmick != nullptr) {
					*ppGimmick = this;
					SetPos.z = -SET_POSZ;
				}
			}
		}
	}

	//Y
	if (pos.x + vtxMax.x > ObjPos.x + vtxObjMin.x
		&& pos.x + vtxMin.x < ObjPos.x + vtxObjMax.x
		&& pos.z + vtxMax.z > ObjPos.z + vtxObjMin.z
		&& pos.z + vtxMin.z < ObjPos.z + vtxObjMax.z)
	{//範囲内にある
	 //上からの判定
		if (posOld.y + vtxMin.y >= ObjPos.y + vtxObjMax.y
			&& pos.y + vtxMin.y < ObjPos.y + vtxObjMax.y)
		{//上からめり込んだ
		 //上にのせる
			pos.y = ObjPos.y + vtxObjMax.y - vtxMin.y;
			move.y = 0.0f;
			bValue = true;
		}
	}

	return bValue;
}