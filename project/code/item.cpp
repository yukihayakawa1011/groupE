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
CItem *CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *pFileName, int nType, const int nPriority)
{
	CItem *pObjectX = NULL;
	CXFile *pModelFile = CManager::GetInstance()->GetModelFile();

	// オブジェクトXの生成
	pObjectX = new CItem;

	if (pObjectX != NULL)
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

	return S_OK;
}

//==========================================================
// 初期化処理
//==========================================================
HRESULT CItem::Init(const char *pFileName)
{
	m_pObject = CObjectX::Create(m_pos, m_rot, pFileName, NULL);

	return S_OK;
}

//==========================================================
// 終了処理
//==========================================================
void CItem::Uninit(void)
{
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
	m_posOld = m_pObject->GetPosition();
	m_pos = m_pObject->GetPosition();

	m_rot = m_pObject->GetRotation();

	//角度を求める
	m_fCurve += (D3DX_PI * 0.02f);

	//位置を代入する
	m_pos.y = m_posOld.y + sinf(m_fCurve) * 1.5f;

	m_rot.y += sinf(D3DX_PI * 0.02f);

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
