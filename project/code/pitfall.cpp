//==========================================================
//
// 落とし穴 [pitfall.cpp]
// Author : Soma Ishihara
//
//==========================================================
#include "pitfall.h"
#include "objectX.h"
#include "input.h"
#include "manager.h"

// マクロ定義
#define ROTATE_ANGLE	(0.05f * D3DX_PI)	//床の開く角度

//==========================================================
// コンストラクタ
//==========================================================
CPitFall::CPitFall()
{
	// 値のクリア
	m_bOpen = false;
	m_fAngle = 0.0f;
}

//==========================================================
// デストラクタ
//==========================================================
CPitFall::~CPitFall()
{

}

//==========================================================
// 初期化処理
//==========================================================
HRESULT CPitFall::Init(void)
{
	return S_OK;
}

//==========================================================
// 終了処理
//==========================================================
void CPitFall::Uninit(void)
{
	Release();
}

//==========================================================
// 更新処理
//==========================================================
void CPitFall::Update(void)
{
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetInputKeyboard();
	if (pKeyboard->GetPress(DIK_F) == true)
	{
		m_bOpen = true;
	}
	else
	{
		m_bOpen = false;
	}

	//開閉による角度設定
	if (m_bOpen == true)
	{//開いてる
		m_fAngle += ROTATE_ANGLE;
		if (m_fAngle > 0.5f * D3DX_PI)
		{
			m_fAngle = 0.5f * D3DX_PI;
		}
	}
	else
	{//閉じてる
		m_fAngle -= ROTATE_ANGLE;
		if (m_fAngle < 0.0f * D3DX_PI)
		{
			m_fAngle = 0.0f * D3DX_PI;
		}
	}

	//モデルに設定
	D3DXVECTOR3 rot = m_pObjFloor[0]->GetRotation();
	m_pObjFloor[0]->SetRotation(D3DXVECTOR3(0.0f, rot.y, -m_fAngle));
	m_pObjFloor[0]->SetEnableCollision(!m_bOpen);

	rot = m_pObjFloor[1]->GetRotation();
	m_pObjFloor[1]->SetRotation(D3DXVECTOR3(0.0f, rot.y, -m_fAngle));
	m_pObjFloor[1]->SetEnableCollision(!m_bOpen);
}

//==========================================================
// 生成
//==========================================================
CPitFall *CPitFall::Create(const D3DXVECTOR3 pos)
{
	CPitFall *pSample = nullptr;

	pSample = new CPitFall;

	if (pSample != nullptr)
	{
		// 初期化処理
		pSample->Init();

		//オブジェクト生成
		pSample->m_pObjFloor[0] = CObjectX::Create(pos - D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\pitfall_floor.x");	//左側
		pSample->m_pObjFloor[1] = CObjectX::Create(pos + D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), "data\\MODEL\\pitfall_floor.x");	//右側
	}

	return pSample;
}