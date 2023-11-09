//==========================================================
//
// アイテムの処理 [item.cpp]
// Author : Yuuka Sakuma
//
//==========================================================
#include "item.h"
#include "Xfile.h"
#include "manager.h"
#include "debugproc.h"
#include "texture.h"
#include "objectX.h"

// マクロ定義
#define COLLISION_SIZE	(50.0f)
#define BOUND_COUNT	(4)
#define GRAVITY	(-1.0f)		//プレイヤー重力

// 静的メンバ変数
CItem *CItem::m_pTop = nullptr;	// 先頭のオブジェクトへのポインタ
CItem *CItem::m_pCur = nullptr;	// 最後尾のオブジェクトへのポインタ

//==========================================================
// コンストラクタ
//==========================================================
CItem::CItem()
{
	// 値のクリア
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pPrev = nullptr;
	m_pNext = nullptr;

	// 自分自身をリストに追加
	if (m_pTop != nullptr)
	{// 先頭が存在している場合
		m_pCur->m_pNext = this;	// 現在最後尾のオブジェクトのポインタにつなげる
		m_pPrev = m_pCur;
		m_pCur = this;	// 自分自身が最後尾になる
	}
	else
	{// 存在しない場合
		m_pTop = this;	// 自分自身が先頭になる
		m_pCur = this;	// 自分自身が最後尾になる
	}
}

//==========================================================
// デストラクタ
//==========================================================
CItem::~CItem()
{

}

//==========================================================
// 生成
//==========================================================
CItem *CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *pFileName, int nType)
{
	CItem *pObjectX = nullptr;

	// オブジェクトXの生成
	pObjectX = new CItem;

	if (pObjectX != nullptr)
	{// 生成できた場合
	
		// 座標
		pObjectX->SetPosition(pos);
		//pObjectX->SetOldPos(pos);

		// 向き
		pObjectX->SetRotation(rot);
		

		//// 種類設定
		//pObjectX->SetType(nType);

		// 種類
		pObjectX->m_nType = nType;
		// 初期化処理
		pObjectX->Init(pFileName);

	}
	else
	{// 生成に失敗した場合
		return NULL;
	}

	return pObjectX;
}


//==========================================================
// 初期化処理
//==========================================================
HRESULT CItem::Init(void)
{
	m_pObject = CObjectX::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, NULL);

	if (m_pObject != nullptr)
	{
		m_pObject->ListOut();
	}

	return S_OK;
}

//==========================================================
// 初期化処理
//==========================================================
HRESULT CItem::Init(const char *pFileName)
{
	m_pObject = CObjectX::Create(m_pos, m_rot, pFileName);

	if (m_pObject != nullptr)
	{
		m_pObject->ListOut();
	}

	return S_OK;
}

//==========================================================
// 終了処理
//==========================================================
void CItem::Uninit(void)
{
	// リストから自分自身を削除する
	if (m_pTop == this)
	{// 自身が先頭
		if (m_pNext != NULL)
		{// 次が存在している
			m_pTop = m_pNext;	// 次を先頭にする
			m_pNext->m_pPrev = NULL;	// 次の前のポインタを覚えていないようにする
		}
		else
		{// 存在していない
			m_pTop = NULL;	// 先頭がない状態にする
			m_pCur = NULL;	// 最後尾がない状態にする
		}
	}
	else if (m_pCur == this)
	{// 自身が最後尾
		if (m_pPrev != NULL)
		{// 次が存在している
			m_pCur = m_pPrev;			// 前を最後尾にする
			m_pPrev->m_pNext = NULL;	// 前の次のポインタを覚えていないようにする
		}
		else
		{// 存在していない
			m_pTop = NULL;	// 先頭がない状態にする
			m_pCur = NULL;	// 最後尾がない状態にする
		}
	}
	else
	{
		if (m_pNext != NULL)
		{
			m_pNext->m_pPrev = m_pPrev;	// 自身の次に前のポインタを覚えさせる
		}
		if (m_pPrev != NULL)
		{
			m_pPrev->m_pNext = m_pNext;	// 自身の前に次のポインタを覚えさせる
		}
	}

	if (nullptr != m_pObject) {
		m_pObject->Uninit();
		m_pObject = NULL;
	}

	if (m_pObject != NULL)
	{
		m_pObject->Uninit();
		delete m_pObject;
		m_pObject = NULL;
	}

	Release();
}

//==========================================================
// 更新処理
//==========================================================
void CItem::Update(void)
{
	if (m_pObject == nullptr)
	{
		return;
	}

	switch (m_nType)
	{
	case TYPE_NORMAL:
	{
		D3DXVECTOR3 pos = m_pos;
		m_posOld = m_pObject->GetPosition();
		m_pos = m_pObject->GetPosition();
		m_rot = m_pObject->GetRotation();

		//角度を求める
		m_fCurve += (D3DX_PI * 0.02f);

		//位置を代入する
		m_pos.y = m_posOld.y + sinf(m_fCurve) * 1.5f;
		m_rot.y += sinf(D3DX_PI * 0.02f);

		m_pos = pos;
	}
		break;

	case TYPE_DROP:

		m_posOld = m_pos;

		//位置を代入する
		m_move.y += GRAVITY;
		m_pos += m_move;
		m_rot.y += sinf(D3DX_PI * (0.02f + (BOUND_COUNT - m_nBound) * 0.01f));

		if (m_pos.y <= 0.0f)
		{
			m_pos.y = 0.0f;
			m_move *= 0.8f;
			m_move.y *= -1.0f;
			m_nBound++;

			if(m_nBound >= BOUND_COUNT)
			{
				m_nType = TYPE_NORMAL;
			}
		}

		break;
	}

	while (1)
	{
		if (m_rot.y > D3DX_PI || m_rot.y < -D3DX_PI)
		{//-3.14〜3.14の範囲外の場合
			if (m_rot.y > D3DX_PI)
			{
				m_rot.y += (-D3DX_PI * 2);
			}
			else if (m_rot.y < -D3DX_PI)
			{
				m_rot.y += (D3DX_PI * 2);
			}
		}
		else
		{
			break;
		}
	}

	// 使用オブジェクト更新
	if (nullptr != m_pObject) {
		m_pObject->SetPosition(m_pos);
		m_pObject->SetRotation(m_rot);
		m_pObject->Update();
	}
}

////==========================================================
//// 描画処理
////==========================================================
//void CItem::Draw(void)
//{
//	m_pObject->
//}
//

//==========================================================
// 当たり判定
//==========================================================
CItem *CItem::Collision(D3DXVECTOR3 &pos)
{
	CItem *pObj = m_pTop;	// 先頭取得
	CXFile *pFile = CManager::GetInstance()->GetModelFile();

	while (pObj != NULL)
	{
		CItem* pObjNext = pObj->m_pNext;
		D3DXVECTOR3 vtxObjMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 vtxObjMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		if (pObj->CollisionCheck(pos))
		{
			if (pObj->m_pObject != nullptr)
			{
				pObj->m_pObject->SetDraw(false);
				return pObj;
			}
		}

		pObj = pObjNext;
	}

	return nullptr;
}

//==========================================================
// 個別判定チェック
//==========================================================
bool CItem::CollisionCheck(D3DXVECTOR3 &pos)
{
	CXFile *pFile = CManager::GetInstance()->GetModelFile();
	D3DXVECTOR3 ObjPos = GetPosition();

	if (m_pObject == nullptr){	// オブジェクトがない
		return false;
	}

	if (!m_pObject->GetDraw()){	// 描画しない
		return false;
	}

	if (m_nType == TYPE_DROP)
	{
		return false;
	}

	// 範囲内チェック
	{
		float fLength =
			sqrtf((pos.x - ObjPos.x) * (pos.x - ObjPos.x)
				+ (pos.z - ObjPos.z) * (pos.z - ObjPos.z));
	}

	// 距離を取得
	float fLength = sqrtf((pos.x - ObjPos.x) * (pos.x - ObjPos.x)
		+ (pos.z - ObjPos.z) * (pos.z - ObjPos.z));

	float fSize = COLLISION_SIZE;

	if (fLength > fSize)
	{// 触れていない
		return false;
	}

	if (pos.y >= ObjPos.y && pos.y <= ObjPos.y + fSize)
	{// 高さも一緒
		return true;
	}
	return false;
}