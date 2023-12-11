//===============================================
//
// �~�j�}�b�v�̏��� [minimap.cpp]
// Author : Soma Ishihara
//
//===============================================
#include "minimap.h"
#include "texture.h"
#include "manager.h"
#include "renderer.h"
#include "object_manager.h"
#include "camera.h"
#include "player.h"
#include "object2D.h"
#include "object2DMap.h"
#include <assert.h>

//===================================================
// �R���X�g���N�^
//===================================================
CMiniMap::CMiniMap()
{
	m_pObjMap = nullptr;
	m_pTextureMap = nullptr;
	m_pTextureUnex = nullptr;
	m_pZSurface = nullptr;
	m_ppPlayerIcon = nullptr;
	m_ppExplored = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	m_nElaseWidth = 0;
	m_nElaseHeight = 0;
	m_nPlayerNum = 0;
}

//===================================================
// �f�X�g���N�^
//===================================================
CMiniMap::~CMiniMap()
{
}

//===============================================
// ����������
//===============================================
HRESULT CMiniMap::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		//�f�o�C�X�ւ̃|�C���^
	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	//�T���ς݃h�b�g�p�t���O����
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

	// �e�N�X�`���̐���
	Load();
	Reset();

	//�v���C���[�l�����A�C�R���p2D�I�u�W�F����
	if (m_nPlayerNum > 0)
	{//1�l�ȏア��
		m_ppPlayerIcon = new CObject2D*[m_nPlayerNum];
		for (int cnt = 0; cnt < m_nPlayerNum; cnt++)
		{
			char path[128];
			sprintf(&path[0], "data\\TEXTURE\\player_icon%d.png", cnt);

			m_ppPlayerIcon[cnt] = CObject2D::Create(4);
			m_ppPlayerIcon[cnt]->BindTexture(pTexture->Regist(&path[0]));
			m_ppPlayerIcon[cnt]->SetLength(12.0f, 12.0f);
			m_ppPlayerIcon[cnt]->SetVtx();
		}
	}
	else
	{//�s��
		assert(false);
	}

	//�}�b�v�I�u�W�F����
	CObject2D* pObjScroll = CObject2D::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pObjScroll->SetSize((m_fHeight * 0.8f) * 2.0f, (m_fHeight * 0.8f));
	pObjScroll->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\scroll_minimap.png"));
	if (m_pObjMap == nullptr)
	{
		m_pObjMap = CObject2DMap::Create(m_pos, D3DXVECTOR3(0.0f,0.0f,0.0f), m_fWidth * 0.5f, m_fHeight * 0.5f);
		m_pObjMap->SetTexture(m_pTextureMap, m_pTextureUnex);
	}

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CMiniMap::Uninit(void)
{
	//�A�C�R���I�u�W�F�j��
	if (m_ppPlayerIcon != nullptr)
	{
		for (int cnt = 0; cnt < m_nPlayerNum; cnt++)
		{
			m_ppPlayerIcon[cnt]->Uninit();
		}
		//���ꕨ�j��
		delete m_ppPlayerIcon;
	}

	//�T���ς݃h�b�g�p�t���O�j��
	if (m_ppExplored != nullptr)
	{
		int x = static_cast<int>(m_fWidth);
		int y = static_cast<int>(m_fHeight);

		for (int cntX = 0; cntX < x; cntX++)
		{//bool*�̕����j��
			delete[] m_ppExplored[cntX];
		}

		//2�����z��݂����ȃ|�C���^�j��
		delete[] m_ppExplored;
	}

	//�}�b�v�I�u�W�F�j��
	if (m_pObjMap != nullptr)
	{
		m_pObjMap->Uninit();
		m_pObjMap = nullptr;
	}

	// �e�N�X�`���j��
	UnLoad();

	//�^�X�N�j��
	Release();
}

//===============================================
// �e�N�X�`���`�揈��
//===============================================
void CMiniMap::DrawTexture(void)
{
	//�f�o�C�X
	CManager* pManager = CManager::GetInstance();
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();		//�f�o�C�X�ւ̃|�C���^
	CScene* pScene = pManager->GetScene();

	//�o�b�N�o�b�t�@�p
	LPDIRECT3DSURFACE9 pOrgSurface;
	LPDIRECT3DSURFACE9 pOrgZBuffer;

	LPDIRECT3DSURFACE9 pTexSurface;

	//int�^�T�C�Y
	int nWidth = static_cast<int>(m_fWidth);
	int nHeight = static_cast<int>(m_fHeight);

	//��p�J����
	D3DXVECTOR3 posR = D3DXVECTOR3(0.0f, 1.0f, -1700.0f);
	D3DXVECTOR3 posV = D3DXVECTOR3(-50.0f, 3500.0f, -1700.0f);
	D3DXVECTOR3 vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//�v���W�F�N�V�����}�g���̏�����
	D3DXMatrixIdentity(&m_mtxProj);

	D3DXMatrixPerspectiveFovLH(&m_mtxProj,
		D3DXToRadian(45.0f),
		(float)m_fWidth / (float)m_fHeight,
		10.0f,
		40000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProj);

	//�r���[�}�g���̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&posV,
		&posR,
		&vecU);

	//�r���[�}�g���̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//�e�N�X�`��
	//�쐬�e�N�X�`���p�C���^�[�t�F�[�X�擾
	m_pTextureMap->GetSurfaceLevel(0, &pTexSurface);

	//�o�b�N�o�b�t�@�C���^�[�t�F�[�X�擾
	pDevice->GetRenderTarget(0, &pOrgSurface);
	pDevice->GetDepthStencilSurface(&pOrgZBuffer);

	//�����_�����O�^�[�Q�b�g���e�N�X�`���ɕύX
	pDevice->SetRenderTarget(0, pTexSurface);
	pDevice->SetDepthStencilSurface(m_pZSurface);

	//�e�N�X�`���N���A
	pDevice->Clear(
		0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0),
		1.0f,
		0);

	//�e�N�X�`���ɕ`��
	if (SUCCEEDED(pDevice->BeginScene()))
	{// �`�悪���������ꍇ

		// �I�u�W�F�N�g�̕`��
		CObjectManager::GetInstance()->DrawAll3D();

		// �`��I��
		pDevice->EndScene();
	}

	//�߂�
	pDevice->SetRenderTarget(0, pOrgSurface);
	pDevice->SetDepthStencilSurface(pOrgZBuffer);

	

	pOrgSurface->Release();
	pOrgZBuffer->Release();
	pTexSurface->Release();
}

//===============================================
// �T���ς݂̏ꏊ�̂܂����낭�낷���������ăv���C���[��\��
//===============================================
void CMiniMap::ExploredMap(void)
{
	//�f�o�C�X
	CManager* pManager = CManager::GetInstance();
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();		//�f�o�C�X�ւ̃|�C���^
	CScene* pScene = pManager->GetScene();
	D3DXMATRIX mtxViewPort, mtx;

	//int�^�T�C�Y
	int nWidth = static_cast<int>(m_fWidth);
	int nHeight = static_cast<int>(m_fHeight);

	//�v���W�F�N�V�����}�g���̏�����
	D3DXMatrixIdentity(&m_mtxProj);

	D3DXMatrixPerspectiveFovLH(&m_mtxProj,
		D3DXToRadian(45.0f),
		(float)m_fWidth / (float)m_fHeight,
		10.0f,
		40000.0f);

	//�T���ς݃G���A�̓������i�e�N�X�`�����j
	//�K�v�ȃ}�g���v�Z
	{
		//�r���[�|�[�g�}�g���ݒ�
		D3DXMatrixIdentity(&mtxViewPort);
		mtxViewPort._11 = m_fWidth * 0.5f;
		mtxViewPort._22 = -m_fHeight * 0.5f;
		mtxViewPort._41 = m_fWidth * 0.5f;
		mtxViewPort._42 = m_fHeight * 0.5f;

		//�S���|����
		mtx = m_mtxView * m_mtxProj * mtxViewPort;	//������D3DXMatrixMultiply����Ă�݂���
	}

	//�v���C���[���ׂČ���
	int nPlaceIcon = 0;
	CPlayer* pPlayer = CPlayer::GetTop();
	while (pPlayer != nullptr)
	{
		//�v���C���[���ƂɕK�v�ȕϐ�
		D3DXVECTOR3 posPlayer = pPlayer->GetPosition();
		D3DXVECTOR3 posWorld;

		//����ŃX�N���[�����W�ɕϊ��ł���
		D3DXVec3TransformCoord(&posWorld, &posPlayer, &mtx);
		int posX = (int)posWorld.x;
		int posY = (int)posWorld.y;
		int posElaseMinX = ((posX - m_nElaseWidth) > 0) ? posX - m_nElaseWidth : 0;
		int posElaseMaxX = ((posX + m_nElaseWidth) < nWidth) ? posX + m_nElaseWidth : nWidth;
		int posElaseMinY = ((posY - m_nElaseHeight) > 0) ? posY - m_nElaseHeight : 0;
		int posElaseMaxY = ((posY + m_nElaseHeight) < nHeight) ? posY + m_nElaseHeight : nHeight;

		//���͈͏���
		for (int y = posElaseMinY; y < posElaseMaxY; y++)
		{
			for (int x = posElaseMinX; x < posElaseMaxX; x++)
			{
				m_ppExplored[x][y] = true;
			}
		}

		//�A�C�R���u��
		if (nPlaceIcon < m_nPlayerNum)
		{
			D3DXVECTOR3 posIcon = m_pos;
			posIcon.x += -m_fWidth * 0.5f + static_cast<float>(posX);
			posIcon.y += -m_fHeight * 0.5f + static_cast<float>(posY);
			m_ppPlayerIcon[nPlaceIcon]->SetPosition(posIcon);
			m_ppPlayerIcon[nPlaceIcon]->SetVtx();
			nPlaceIcon++;
		}

		//��
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
}

//===============================================
// �e�N�X�`����������
//===============================================
void CMiniMap::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�ւ̃|�C���^

	//int�^�T�C�Y
	int nWidth = static_cast<int>(m_fWidth);
	int nHeight = static_cast<int>(m_fHeight);

	//�e�e�N�X�`������
	if (m_pTextureMap == nullptr)
	{
		D3DXCreateTexture(pDevice, nWidth, nHeight,
			1,
			D3DUSAGE_RENDERTARGET,
			D3DFMT_A8R8G8B8,
			D3DPOOL_DEFAULT, //�����̂��߃f�o�C�X���X�g���͔j�����K�v
			&m_pTextureMap);
	}
	
	if (m_pTextureUnex == nullptr)
	{
		D3DXCreateTexture(pDevice, nWidth, nHeight,
			1,
			D3DUSAGE_DYNAMIC,
			D3DFMT_A8R8G8B8,
			D3DPOOL_DEFAULT, //�����̂��߃f�o�C�X���X�g���͔j�����K�v
			&m_pTextureUnex);

		//���炩���ߍ����h��Ԃ�
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
		//����Z�o�b�t�@����
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
// �e�N�X�`���J������
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
// �e�N�X�`�����Z�b�g����
//===============================================
void CMiniMap::Reset(void)
{
	if (m_pTextureUnex != nullptr)
	{
		//int�^�T�C�Y
		int nWidth = static_cast<int>(m_fWidth);
		int nHeight = static_cast<int>(m_fHeight);

		//���炩���ߍ����h��Ԃ�
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
// ��������
//===============================================
CMiniMap* CMiniMap::Create(const int playerNum, const int elaseWidth, const int elaseHeight)
{
	CMiniMap* pMiniMap = nullptr;

	if (pMiniMap == nullptr)
	{//�����Ƃʂ�ۂ����琶��
		pMiniMap = new CMiniMap;
		pMiniMap->m_nPlayerNum = playerNum;
		pMiniMap->m_fWidth = PlacePos::NUM_PLACE_DATA[playerNum - 1].fWidth;
		pMiniMap->m_fHeight = PlacePos::NUM_PLACE_DATA[playerNum - 1].fHeight;
		pMiniMap->m_nElaseWidth = elaseWidth;
		pMiniMap->m_nElaseHeight = elaseHeight;
		pMiniMap->m_pos = PlacePos::NUM_PLACE_DATA[playerNum - 1].pos;
		pMiniMap->Init();
	}

	return pMiniMap;
}