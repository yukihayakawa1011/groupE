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
#include "object2D.h"
#include <assert.h>

//===================================================
// コンストラクタ
//===================================================
CMiniMap::CMiniMap()
{
	m_pVtxBuff = nullptr;
	m_pTextureMap = nullptr;
	m_pTextureUnex = nullptr;
	m_pZSurface = nullptr;
	m_ppPlayerIcon = nullptr;
	m_ppExplored = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fLength = 0.0f;
	m_fAngle = 0.0f;
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	m_nElaseWidth = 0;
	m_nElaseHeight = 0;
	m_nPlayerNum = 0;
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

	//探索済みドット用フラグ生成
	if (m_ppExplored == nullptr)
	{
		int x = static_cast<int>(m_fWidth);
		int y = static_cast<int>(m_fHeight);

		m_ppExplored = new bool*[x];
		for (int cntX = 0; cntX < x; cntX++)
		{
			m_ppExplored[cntX] = new bool[y];
			for (int cntY = 0; cntY < y; cntY++)
			{
				m_ppExplored[cntX][cntY] = false;
			}
		}
	}

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

	//プレイヤー人数分アイコン用2Dオブジェ生成
	if (m_nPlayerNum > 0)
	{//1人以上いる
		m_ppPlayerIcon = new CObject2D*[m_nPlayerNum];
		for (int cnt = 0; cnt < m_nPlayerNum; cnt++)
		{
			m_ppPlayerIcon[cnt] = CObject2D::Create();
		}
	}
	else
	{//不正
		assert(false);
	}

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

	//アイコンオブジェ破棄
	if (m_ppPlayerIcon != nullptr)
	{
		for (int cnt = 0; cnt < m_nPlayerNum; cnt++)
		{
			m_ppPlayerIcon[cnt]->Uninit();
		}
		//入れ物破棄
		delete m_ppPlayerIcon;
	}

	//探索済みドット用フラグ破棄
	if (m_ppExplored != nullptr)
	{
		int x = static_cast<int>(m_fWidth);
		int y = static_cast<int>(m_fHeight);

		for (int cntX = 0; cntX < x; cntX++)
		{//bool*の部分破棄
			delete[] m_ppExplored[cntX];
		}

		//2次元配列みたいなポインタ破棄
		delete[] m_ppExplored;
	}

	// テクスチャ破棄
	UnLoad();

	//タスク破棄
	Release();
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

	//int型サイズ
	int nWidth = static_cast<int>(m_fWidth);
	int nHeight = static_cast<int>(m_fHeight);

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
		mtxViewPort._11 = m_fWidth * 0.5f;
		mtxViewPort._22 = -m_fHeight * 0.5f;
		mtxViewPort._41 = m_fWidth * 0.5f;
		mtxViewPort._42 = m_fHeight * 0.5f;

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
		int posElaseMinX = ((posX - m_nElaseWidth) > 0) ? posX - m_nElaseWidth : 0;
		int posElaseMaxX = ((posX + m_nElaseWidth) < nWidth) ? posX + m_nElaseWidth : nWidth;
		int posElaseMinY = ((posY - m_nElaseHeight) > 0) ? posY - m_nElaseHeight : 0;
		int posElaseMaxY = ((posY + m_nElaseHeight) < nHeight) ? posY + m_nElaseHeight : nHeight;

		//一定範囲消す
		for (int y = posElaseMinY; y < posElaseMaxY; y++)
		{
			for (int x = posElaseMinX; x < posElaseMaxX; x++)
			{
				m_ppExplored[x][y] = true;
			}
		}

		pPlayer = pPlayer->GetNext();
	}

	D3DLOCKED_RECT lockrect;
	m_pTextureUnex->LockRect(0, &lockrect, nullptr, 0);
	BYTE* pBitByte = (BYTE*)lockrect.pBits;
	for (int y = 0; y < nHeight; y++)
	{
		DWORD* pBitColor = (DWORD*)(pBitByte + y * lockrect.Pitch);
		for (int x = 0; x < nWidth; x++)
		{
			if (m_ppExplored[x][y] == true)
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

	//int型サイズ
	int nWidth = static_cast<int>(m_fWidth);
	int nHeight = static_cast<int>(m_fHeight);

	//各テクスチャ生成
	if (m_pTextureMap == nullptr)
	{
		D3DXCreateTexture(pDevice, nWidth, nHeight,
			1,
			D3DUSAGE_RENDERTARGET,
			D3DFMT_A8R8G8B8,
			D3DPOOL_DEFAULT, //こいつのためデバイスロスト時は破棄が必要
			&m_pTextureMap);
	}
	
	if (m_pTextureUnex == nullptr)
	{
		D3DXCreateTexture(pDevice, nWidth, nHeight,
			1,
			D3DUSAGE_DYNAMIC,
			D3DFMT_A8R8G8B8,
			D3DPOOL_DEFAULT, //こいつのためデバイスロスト時は破棄が必要
			&m_pTextureUnex);

		//あらかじめ黒く塗りつぶす
		D3DLOCKED_RECT lockrect;
		m_pTextureUnex->LockRect(0, &lockrect, nullptr, 0);
		BYTE* pBitByte = (BYTE*)lockrect.pBits;
		for (int y = 0; y < nHeight; y++)
		{
			DWORD* pBitColor = (DWORD*)(pBitByte + y * lockrect.Pitch);
			for (int x = 0; x < nWidth; x++)
			{
				pBitColor[x] = 0xff000000;
			}
		}

		m_pTextureUnex->UnlockRect(0);
	}

	if (m_pZSurface == nullptr)
	{
		//共通Zバッファ生成
		pDevice->CreateDepthStencilSurface(
			nWidth, nHeight,
			D3DFMT_D16,
			D3DMULTISAMPLE_NONE,
			0, false,
			&m_pZSurface,
			nullptr);
	}
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
		//int型サイズ
		int nWidth = static_cast<int>(m_fWidth);
		int nHeight = static_cast<int>(m_fHeight);

		//あらかじめ黒く塗りつぶす
		D3DLOCKED_RECT lockrect;
		m_pTextureUnex->LockRect(0, &lockrect, nullptr, 0);
		BYTE* pBitByte = (BYTE*)lockrect.pBits;
		for (int y = 0; y < nHeight; y++)
		{
			DWORD* pBitColor = (DWORD*)(pBitByte + y * lockrect.Pitch);
			for (int x = 0; x < nWidth; x++)
			{
				pBitColor[x] = 0xffffffff;
				m_ppExplored[x][y] = false;
			}
		}

		m_pTextureUnex->UnlockRect(0);
	}
}

//===============================================
// 生成処理
//===============================================
CMiniMap* CMiniMap::Create(const D3DXVECTOR3 posMap, const D3DXVECTOR3 rotMap, const float width, const float height, const int playerNum,
	const int elaseWidth, const int elaseHeight)
{
	CMiniMap* pMiniMap = nullptr;

	if (pMiniMap == nullptr)
	{//ちゃんとぬるぽだから生成
		pMiniMap = new CMiniMap;
		pMiniMap->m_nPlayerNum = playerNum;
		pMiniMap->m_fWidth = width;
		pMiniMap->m_fHeight = height;
		pMiniMap->m_nElaseWidth = elaseWidth;
		pMiniMap->m_nElaseHeight = elaseHeight;
		pMiniMap->Init();
		pMiniMap->SetPosition(posMap);
		pMiniMap->SetRotation(rotMap);
	}

	return pMiniMap;
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
