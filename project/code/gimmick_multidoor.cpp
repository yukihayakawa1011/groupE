//==========================================================
//
// ギミック生える槍 [gimmick_multidoor.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "gimmick_multidoor.h"
#include "model.h"
#include "manager.h"
#include "debugproc.h"
#include "player.h"
#include "Xfile.h"
#include "gimmick_button.h"
#include "input.h"
#include "manager.h"

// 無名名前空間
namespace {
	const char* FILENAME = "data\\MODEL\\multidoor.x";	// 使用するモデルファイル名
	const D3DXVECTOR3 SETPOS = { 150.0f, 0.0f, 0.0f };		// 初期設定座標
	const float INERMULTI[CGimmickMultiDoor::STATE_MAX] = {0.75f, 0.15f, 0.01f};	// 補正倍率
	const D3DXVECTOR3 OPENPOS = { 300.0f, 0.0f, 0.0f };
	const int CLOSECOUNTER = (300);
}

//==========================================================
// コンストラクタ
//==========================================================
CGimmickMultiDoor::CGimmickMultiDoor()
{
	// 値のクリア
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++) {
		m_aObject[nCnt].pModel = nullptr;
		m_aObject[nCnt].posDest = { 0.0f, 0.0f, 0.0f };
		m_aObject[nCnt].posOld = { 0.0f, 0.0f, 0.0f };
	}

	m_state = STATE_NEUTRAL;
	m_nStateCnt = 0;
	m_nNumSwitch = 0;
	m_nNumLinkSwitch = 0;
	m_fInerMulti = 0.0f;
	m_ppButton = nullptr;
}

//==========================================================
// デストラクタ
//==========================================================
CGimmickMultiDoor::~CGimmickMultiDoor()
{

}

//==========================================================
// 初期化処理
//==========================================================
HRESULT CGimmickMultiDoor::Init(void)
{
	// モデルの生成
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++) {
		m_aObject[nCnt].pModel = CModel::Create(FILENAME);
		m_aObject[nCnt].pModel->SetParent(GetMtxWorld());
		m_aObject[nCnt].pModel->SetPosition({ SETPOS.x - (SETPOS.x * nCnt * 2), SETPOS.y, SETPOS.z});
		m_aObject[nCnt].pModel->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI * nCnt, 0.0f));
	}

	StateSet();

	return S_OK;
}

//==========================================================
// 終了処理
//==========================================================
void CGimmickMultiDoor::Uninit(void)
{
	// リストから削除
	ListOut();

	// 使用オブジェクトの削除
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++) {
		if (m_aObject[nCnt].pModel != nullptr) {	// モデルを使用されている場合
			m_aObject[nCnt].pModel->Uninit();
			m_aObject[nCnt].pModel = nullptr;
		}
	}

	// リリース
	Release();
}

//==========================================================
// 更新処理
//==========================================================
void CGimmickMultiDoor::Update(void)
{
	// マトリックス設定
	SetMtxWorld();

	// 状態更新
	UpdateState();

	// 補正
	ObjIner();

	int nActive = 0;
	// 開ける状態か確認
	for (int nCnt = 0; nCnt < m_nNumSwitch; nCnt++) {
		if (m_ppButton[nCnt] != nullptr) {	// 使用されている
			if (m_ppButton[nCnt]->GetState() == CGimmickButton::STATE_PRESS) {
				nActive++;
				continue;
			}
			break;
		}
	}

	if (nActive >= m_nNumLinkSwitch) {	// スイッチが規定値押されている
		m_state = STATE_OPEN;
		StateSet();
	}
	else
	{
		if (m_state == STATE_OPEN) {
			m_state = STATE_CLOSE;
			StateSet();
		}
	}
}

//==========================================================
// 生成
//==========================================================
CGimmickMultiDoor *CGimmickMultiDoor::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	CGimmickMultiDoor *pGimmick = nullptr;

	pGimmick = new CGimmickMultiDoor;

	if (pGimmick != nullptr)
	{
		// 初期化処理
		pGimmick->Init();

		// 値の設定
		pGimmick->SetPosition(pos);
		pGimmick->SetRotation(rot);
		pGimmick->CGimmick::BindType(TYPE_SPEAR);
	}

	return pGimmick;
}

//==========================================================
// 状態管理
//==========================================================
void CGimmickMultiDoor::StateSet(void)
{
	// 状態ごとに設定
	switch (m_state) 
	{
	case STATE_NEUTRAL:

		for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++) {
			if (m_aObject[nCnt].pModel != nullptr) {	// モデルを使用されている場合
				m_aObject[nCnt].posDest = m_aObject[nCnt].pModel->GetPosition();	// 閉じた状態を目標に
			}
		}

		break;

	case STATE_OPEN:

		for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++) {
			if (m_aObject[nCnt].pModel != nullptr) {	// モデルを使用されている場合
				m_aObject[nCnt].posDest = { OPENPOS.x - (OPENPOS.x * nCnt * 2), OPENPOS.y, OPENPOS.z };	// 開いた状態を目標に
			}
		}

		break;

	case STATE_CLOSE:
		
		for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++) {
			if (m_aObject[nCnt].pModel != nullptr) {	// モデルを使用されている場合
				m_aObject[nCnt].posDest = m_aObject[nCnt].pModel->GetPosition();	// 閉じた状態を目標に
			}
		}

		m_nStateCnt = CLOSECOUNTER;

		break;
	}

	// 補正倍率を設定
	m_fInerMulti = INERMULTI[m_state];
}

//==========================================================
// 判定確認
//==========================================================
bool CGimmickMultiDoor::CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, D3DXVECTOR3 &SetPos, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, int nAction, CGimmick **ppGimmick)
{
	bool bValue = false;
	CXFile *pFile = CManager::GetInstance()->GetModelFile();

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++) {
		if (m_aObject[nCnt].pModel != nullptr) {	// モデルを使用されている場合
			D3DXVECTOR3 vtxObjMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 vtxObjMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 ObjPos = D3DXVECTOR3(m_aObject[nCnt].pModel->GetMtx()->_41, m_aObject[nCnt].pModel->GetMtx()->_42, m_aObject[nCnt].pModel->GetMtx()->_43);
			D3DXVECTOR3 ObjRot = GetRotation();

			// 向きを反映
			m_aObject[nCnt].pModel->SetRotSize(vtxObjMax,
				vtxObjMin,
				pFile->GetMax(m_aObject[nCnt].pModel->GetId()),
				pFile->GetMin(m_aObject[nCnt].pModel->GetId()),
				m_aObject[nCnt].pModel->GetRotation().y);

			if (pos.y + vtxMax.y > ObjPos.y + vtxObjMin.y
				&& pos.y + vtxMin.y <= ObjPos.y + vtxObjMax.y)
			{//プレイヤーとモデルが同じ高さにある
				if (posOld.x + vtxMin.x >= m_aObject[nCnt].posOld.x + vtxObjMax.x
					&& pos.x + vtxMin.x < ObjPos.x + vtxObjMax.x
					&& pos.z + vtxMax.z > ObjPos.z + vtxObjMin.z
					&& pos.z + vtxMin.z < ObjPos.z + vtxObjMax.z)
				{//右から左にめり込んだ
					//位置を戻す
					pos.x = ObjPos.x + vtxObjMax.x - vtxMin.x + 0.1f;
				}
				else if (posOld.x + vtxMax.x <= m_aObject[nCnt].posOld.x + vtxObjMin.x
					&& pos.x + vtxMax.x > ObjPos.x + vtxObjMin.x
					&& pos.z + vtxMax.z > ObjPos.z + vtxObjMin.z
					&& pos.z + vtxMin.z < ObjPos.z + vtxObjMax.z)
				{//左から右にめり込んだ
					//位置を戻す
					pos.x = ObjPos.x + vtxObjMin.x - vtxMax.x - 0.1f;
				}
				else if (posOld.z + vtxMin.z >= m_aObject[nCnt].posOld.z + vtxObjMax.z
					&& pos.z + vtxMin.z < ObjPos.z + vtxObjMax.z
					&& pos.x + vtxMax.x > ObjPos.x + vtxObjMin.x
					&& pos.x + vtxMin.x < ObjPos.x + vtxObjMax.x)
				{//奥から手前にめり込んだ
					//位置を戻す
					pos.z = ObjPos.z + vtxObjMax.z - vtxMin.z + 0.1f;
				}
				else if (posOld.z + vtxMax.z <= m_aObject[nCnt].posOld.z + vtxObjMin.z
					&& pos.z + vtxMax.z > ObjPos.z + vtxObjMin.z
					&& pos.x + vtxMax.x > ObjPos.x + vtxObjMin.x
					&& pos.x + vtxMin.x < ObjPos.x + vtxObjMax.x)
				{//手前から奥にめり込んだt
				 //位置を戻す
					pos.z = ObjPos.z + vtxObjMin.z - vtxMax.z - 0.1f;
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
				}
			}
		}
	}

	return bValue;
}

//==========================================================
// 状態ごとの更新
//==========================================================
void CGimmickMultiDoor::UpdateState(void)
{
	// 状態ごとに設定
	switch (m_state) 
	{
	case STATE_NEUTRAL:

		break;

	case STATE_OPEN:

		break;

	case STATE_CLOSE:

		m_nStateCnt--;

		if (m_nStateCnt < 0) {
			m_state = STATE_NEUTRAL;	// 待機状態に変更
			StateSet();
		}

		break;
	}
}

//==========================================================
// オブジェクトの補正倍率
//==========================================================
void CGimmickMultiDoor::ObjIner(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++) {
		if (m_aObject[nCnt].pModel != nullptr) {	// モデルを使用されている場合
			m_aObject[nCnt].posOld = { m_aObject[nCnt].pModel->GetMtx()->_41 , m_aObject[nCnt].pModel->GetMtx()->_42, m_aObject[nCnt].pModel->GetMtx()->_43};
			D3DXVECTOR3 pos = m_aObject[nCnt].pModel->GetCurrentPosition();
			D3DXVECTOR3 posDiff = m_aObject[nCnt].posDest - pos;
			pos += posDiff * m_fInerMulti;
			m_aObject[nCnt].pModel->SetCurrentPosition(pos);
		}
	}
}

//==========================================================
// ボタンをリンクさせる
//==========================================================
void CGimmickMultiDoor::BindButton(CGimmickButton *pButton)
{
	if(m_ppButton == nullptr){	// 使用先ボタンが生成されていない
		return;
	}

	m_nNumLinkSwitch = 0;

	for (int nCnt = 0; nCnt < m_nNumSwitch; nCnt++) {
		if (m_ppButton[nCnt] != nullptr) {	// 使用されている
			m_nNumLinkSwitch++;
			continue;
		}

		m_ppButton[nCnt] = pButton;
		m_nNumLinkSwitch++;
		break;
	}
}

//==========================================================
// ボタン使用数を設定
//==========================================================
void CGimmickMultiDoor::SetNumButton(const int nNum)
{
	CGimmickButton **ppButtonOld = m_ppButton;
	int nNumOld = m_nNumSwitch;

	if (m_ppButton != nullptr) {	// 既に使用されている
		m_ppButton = nullptr;
	}

	// ポインタを生成
	m_ppButton = new CGimmickButton*[nNum];
	m_nNumSwitch = nNum;

	for (int nCnt = 0; nCnt < m_nNumSwitch; nCnt++) {
		m_ppButton[nCnt] = nullptr;
	}

	if (ppButtonOld != nullptr) {	// 生成前に使用されていた
		// 前回の数繰り返し
		for (int nCnt = 0; nCnt < nNumOld; nCnt++){
			
			if (ppButtonOld[nCnt] != nullptr) {	// 使用されている
				BindButton(ppButtonOld[nCnt]);	// 使用されていたボタンを再設定
			}
		}
		delete[] ppButtonOld;	// ポインタの開放
		ppButtonOld = nullptr;	// 使用していない状態にする
	}
}