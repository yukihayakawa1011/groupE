//===============================================
//
// ミニマップの処理 [minimap.cpp]
// Author : Soma Ishihara
//
//===============================================
#include "minimap.h"
#include "manager.h"
#include "renderer.h"
#include "object_manager.h"
#include "camera.h"

//テストマクロ
#define TEST_WIDTH	(256)
#define TEST_HEIGHT	(144)

//静的メンバ変数
LPDIRECT3DTEXTURE9 CMiniMap::m_pTexture = nullptr;
LPDIRECT3DSURFACE9 CMiniMap::m_pZSurface = nullptr;

//===================================================
// コンストラクタ
//===================================================
CMiniMap::CMiniMap()
{
}

//===================================================
// デストラクタ
//===================================================
CMiniMap::~CMiniMap()
{
}

//===============================================
// 初期化処理
//===============================================
HRESULT CMiniMap::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// テクスチャの生成
	Load();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		nullptr);

	if (m_pVtxBuff == nullptr)
	{// 生成に失敗した場合
		return E_FAIL;
	}

	//角度計算
	CulcDiagonal();

	// 頂点情報設定
	SetpVtx(CHANGE_ALL);

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CMiniMap::Uninit(void)
{
	// 頂点バッファの廃棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	// テクスチャ破棄
	UnLoad();
}

//===============================================
// ポリゴン描画処理
//===============================================
void CMiniMap::DrawMap(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		//デバイスへのポインタ
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	//デバイスの取得
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(
		0,
		m_pVtxBuff,
		0,
		sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// 描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	//プリミティブの種類
		0,
		2	//頂点情報構造体のサイズ
	);
}

//===============================================
// テクスチャ描画処理
//===============================================
void CMiniMap::DrawTexture(void)
{
	//デバイス
	CManager* pManager = CManager::GetInstance();
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();		//デバイスへのポインタ
	CScene* pScene = pManager->GetScene();
	CCamera* pOrgCamera = pManager->GetCamera();

	//バックバッファ用
	LPDIRECT3DSURFACE9 pOrgSurface;
	LPDIRECT3DSURFACE9 pOrgZBuffer;

	LPDIRECT3DSURFACE9 pTexSurface;

	//専用カメラ
	D3DXMATRIX mtxView;			// ビューマトリックス
	D3DXMATRIX mtxProjection;	// プロジェクションマトリックス
	D3DXVECTOR3 posR = D3DXVECTOR3(-2500.0f, 1.0f, 1000.0f);
	D3DXVECTOR3 posV = D3DXVECTOR3(-2500.0f, 6000.0f, 1100.0f);
	D3DXVECTOR3 vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//プロジェクションマトリの初期化
	D3DXMatrixIdentity(&mtxProjection);

	D3DXMatrixPerspectiveFovLH(&mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		40000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);

	//ビューマトリの初期化
	D3DXMatrixIdentity(&mtxView);

	//ビューマトリの作成
	D3DXMatrixLookAtLH(&mtxView,
		&posV,
		&posR,
		&vecU);

	//ビューマトリの設定
	pDevice->SetTransform(D3DTS_VIEW, &mtxView);

	//テクスチャ
	//作成テクスチャ用インターフェース取得
	m_pTexture->GetSurfaceLevel(0, &pTexSurface);

	//バックバッファインターフェース取得
	pDevice->GetRenderTarget(0, &pOrgSurface);
	pDevice->GetDepthStencilSurface(&pOrgZBuffer);

	//レンダリングターゲットをテクスチャに変更
	pDevice->SetRenderTarget(0, pTexSurface);
	pDevice->SetDepthStencilSurface(m_pZSurface);

	//テクスチャクリア
	pDevice->Clear(
		0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0),
		1.0f,
		0);

	//テクスチャに描画
	if (SUCCEEDED(pDevice->BeginScene()))
	{// 描画が成功した場合

		// オブジェクトの描画
		CObjectManager::GetInstance()->DrawAll();

		// 描画終了
		pDevice->EndScene();
	}

	//戻す
	pDevice->SetRenderTarget(0, pOrgSurface);
	pDevice->SetDepthStencilSurface(pOrgZBuffer);

	pOrgSurface->Release();
	pOrgZBuffer->Release();
	pTexSurface->Release();
}

//===============================================
// テクスチャ生成処理
//===============================================
void CMiniMap::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスへのポインタ

	D3DXCreateTexture(pDevice, TEST_WIDTH, TEST_HEIGHT,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT, //こいつのためデバイスロスト時は破棄が必要
		&m_pTexture);

	pDevice->CreateDepthStencilSurface(
		TEST_WIDTH, TEST_HEIGHT,
		D3DFMT_D16,
		D3DMULTISAMPLE_NONE,
		0, false ,
		&m_pZSurface,
		nullptr);
}

//===============================================
// テクスチャ開放処理
//===============================================
void CMiniMap::UnLoad(void)
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}

//===============================================
// ポリゴン位置設定処理
//===============================================
void CMiniMap::SetPosition(const D3DXVECTOR3 pos)
{
	m_pos = pos;

	//頂点再設定
	SetpVtx(CHANGE_POS);
}

//===============================================
// ポリゴン角度設定処理
//===============================================
void CMiniMap::SetRotation(const D3DXVECTOR3 rot)
{
	m_rot = rot;

	//頂点再設定
	SetpVtx(CHANGE_POS);
}

//===============================================
// ポリゴンサイズ設定処理
//===============================================
void CMiniMap::SetSize(float fWidth, float fHeight)
{
	m_fWidth = fWidth;
	m_fHeight = fHeight;

	//角度計算
	CulcDiagonal();

	//頂点再設定
	SetpVtx(CHANGE_POS);
}

//===============================================
// ポリゴン頂点設定処理
//===============================================
void CMiniMap::SetpVtx(const int nChangeVtx)
{
	VERTEX_2D *pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuff->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	//頂点座標の設定
	if ((nChangeVtx & CHANGE_POS) == CHANGE_POS)
	{
		//入れる
		pVtx[0].pos.x = m_pos.x + sinf(m_rot.z + (-D3DX_PI + m_fAngle)) * m_fLength;
		pVtx[0].pos.y = m_pos.y + cosf(m_rot.z + (-D3DX_PI + m_fAngle)) * m_fLength;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
		pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = m_pos.x + sinf(m_rot.z + -m_fAngle) * m_fLength;
		pVtx[2].pos.y = m_pos.y + cosf(m_rot.z + -m_fAngle) * m_fLength;
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength;
		pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength;
		pVtx[3].pos.z = 0.0f;
	}

	//法線ベクトルの設定
	if ((nChangeVtx & CHANGE_RHW) == CHANGE_RHW)
	{
		//入れる
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
	}

	//頂点カラーの設定
	if ((nChangeVtx & CHANGE_COL) == CHANGE_COL)
	{
		//入れる
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//テクスチャ座標の設定
	if ((nChangeVtx & CHANGE_TEX) == CHANGE_TEX)
	{
		//入れる
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//===============================================
// ポリゴン角度計算処理
//===============================================
void CMiniMap::CulcDiagonal(void)
{
	//対角線の長さを算出する
	m_fLength = sqrtf(m_fWidth * m_fWidth + m_fHeight * m_fHeight) * 0.5f;

	//対角線の角度を算出する
	m_fAngle = atan2f(m_fWidth, m_fHeight);
}
