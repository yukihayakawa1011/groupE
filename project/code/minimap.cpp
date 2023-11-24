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
#include "player.h"
#include <assert.h>

//テストマクロ
#define ELASE_WIDTH		(10)
#define ELASE_HEIGHT	(10)

//静的メンバ変数
LPDIRECT3DTEXTURE9 CMiniMap::m_pTextureMap = nullptr;
LPDIRECT3DTEXTURE9 CMiniMap::m_pTextureUnex = nullptr;
LPDIRECT3DSURFACE9 CMiniMap::m_pZSurface = nullptr;
bool CMiniMap::m_bExplored[TEST_WIDTH][TEST_HEIGHT] = {};

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
	Reset();

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

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(
		0,
		m_pVtxBuff,
		0,
		sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// マップテクスチャの設定
	pDevice->SetTexture(0, m_pTextureMap);

	// 描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	//プリミティブの種類
		0,
		2	//頂点情報構造体のサイズ
	);

	// まっくろくろすけテクスチャの設定
	pDevice->SetTexture(0, m_pTextureUnex);

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
	D3DXMATRIX mtxViewCamera;	// ビューマトリックス
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
	D3DXMatrixIdentity(&mtxViewCamera);

	//ビューマトリの作成
	D3DXMatrixLookAtLH(&mtxViewCamera,
		&posV,
		&posR,
		&vecU);

	//ビューマトリの設定
	pDevice->SetTransform(D3DTS_VIEW, &mtxViewCamera);

	//テクスチャ
	//作成テクスチャ用インターフェース取得
	m_pTextureMap->GetSurfaceLevel(0, &pTexSurface);

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
		CObjectManager::GetInstance()->DrawAll(CObjectManager::TYPE_3DONLY);

		// 描画終了
		pDevice->EndScene();
	}

	//戻す
	pDevice->SetRenderTarget(0, pOrgSurface);
	pDevice->SetDepthStencilSurface(pOrgZBuffer);

	//探索済みエリアの透明化（テクスチャが）
	//必要な変数
	D3DXMATRIX mtxViewPort, mtxProj, mtxView, mtx;

	//必要なマトリ計算
	{
		//ビューマトリ取得
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//プロジェクションマトリ取得
		pDevice->GetTransform(D3DTS_PROJECTION, &mtxProj);

		//ビューポートマトリ設定
		D3DXMatrixIdentity(&mtxViewPort);
		mtxViewPort._11 = TEST_WIDTH * 0.5;
		mtxViewPort._22 = -TEST_HEIGHT * 0.5;
		mtxViewPort._41 = TEST_WIDTH * 0.5;
		mtxViewPort._42 = TEST_HEIGHT * 0.5;

		//全部掛ける
		mtx = mtxView * mtxProj * mtxViewPort;	//内部でD3DXMatrixMultiplyやってるみたい
	}
	
	//プレイヤーすべて見る
	CPlayer* pPlayer = CPlayer::GetTop();
	while (pPlayer != nullptr)
	{
		//プレイヤーごとに必要な変数
		D3DXVECTOR3 posPlayer = pPlayer->GetPosition();
		D3DXVECTOR3 posWorld;

		//これでスクリーン座標に変換できた
		D3DXVec3TransformCoord(&posWorld, &posPlayer, &mtx);
		int posX = (int)posWorld.x;
		int posY = (int)posWorld.y;
		int posElaseMinX = ((posX - ELASE_WIDTH) > 0) ? posX - ELASE_WIDTH : 0;
		int posElaseMaxX = ((posX + ELASE_WIDTH) < TEST_WIDTH) ? posX + ELASE_WIDTH : TEST_WIDTH;
		int posElaseMinY = ((posY - ELASE_HEIGHT) > 0) ? posY - ELASE_HEIGHT : 0;
		int posElaseMaxY = ((posY + ELASE_HEIGHT) < TEST_HEIGHT) ? posY + ELASE_HEIGHT : TEST_HEIGHT;

		//一定範囲消す
		for (int y = posElaseMinY; y < posElaseMaxY; y++)
		{
			for (int x = posElaseMinX; x < posElaseMaxX; x++)
			{
				m_bExplored[x][y] = true;
			}
		}

		pPlayer = pPlayer->GetNext();
	}

	D3DLOCKED_RECT lockrect;
	m_pTextureUnex->LockRect(0, &lockrect, nullptr, 0);
	BYTE* pBitByte = (BYTE*)lockrect.pBits;
	for (int y = 0; y < TEST_HEIGHT; y++)
	{
		DWORD* pBitColor = (DWORD*)(pBitByte + y * lockrect.Pitch);
		for (int x = 0; x < TEST_WIDTH; x++)
		{
			if (m_bExplored[x][y] == true)
			{
				pBitColor[x] = 0x00000000;
			}
			else
			{
				pBitColor[x] = 0xff000000;
			}
		}
	}
	m_pTextureUnex->UnlockRect(0);

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

	//各テクスチャ生成
	D3DXCreateTexture(pDevice, TEST_WIDTH, TEST_HEIGHT,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT, //こいつのためデバイスロスト時は破棄が必要
		&m_pTextureMap);

	D3DXCreateTexture(pDevice, TEST_WIDTH, TEST_HEIGHT,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT, //こいつのためデバイスロスト時は破棄が必要
		&m_pTextureUnex);

	//あらかじめ黒く塗りつぶす
	D3DLOCKED_RECT lockrect;
	m_pTextureUnex->LockRect(0, &lockrect, nullptr, 0);
	BYTE* pBitByte = (BYTE*)lockrect.pBits;
	for (int y = 0; y < TEST_HEIGHT; y++)
	{
		DWORD* pBitColor = (DWORD*)(pBitByte + y * lockrect.Pitch);
		for (int x = 0; x < TEST_WIDTH; x++)
		{
			pBitColor[x] = 0xff000000;
		}
	}

	m_pTextureUnex->UnlockRect(0);

	//共通Zバッファ生成
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
	if (m_pTextureMap != nullptr)
	{
		m_pTextureMap->Release();
		m_pTextureMap = nullptr;
	}
	if (m_pTextureUnex != nullptr)
	{
		m_pTextureUnex->Release();
		m_pTextureUnex = nullptr;
	}
	if (m_pZSurface != nullptr)
	{
		m_pZSurface->Release();
		m_pZSurface = nullptr;
	}
}

//===============================================
// テクスチャリセット処理
//===============================================
void CMiniMap::Reset(void)
{
	if (m_pTextureUnex != nullptr)
	{
		//あらかじめ黒く塗りつぶす
		D3DLOCKED_RECT lockrect;
		m_pTextureUnex->LockRect(0, &lockrect, nullptr, 0);
		BYTE* pBitByte = (BYTE*)lockrect.pBits;
		for (int y = 0; y < TEST_HEIGHT; y++)
		{
			DWORD* pBitColor = (DWORD*)(pBitByte + y * lockrect.Pitch);
			for (int x = 0; x < TEST_WIDTH; x++)
			{
				pBitColor[x] = 0xffffffff;
				m_bExplored[x][y] = false;
			}
		}

		m_pTextureUnex->UnlockRect(0);
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
