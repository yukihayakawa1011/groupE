//===============================================
//
// �~�j�}�b�v�̏��� [minimap.cpp]
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

//�e�X�g�}�N��
#define ELASE_WIDTH		(10)
#define ELASE_HEIGHT	(10)

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CMiniMap::m_pTextureMap = nullptr;
LPDIRECT3DTEXTURE9 CMiniMap::m_pTextureUnex = nullptr;
LPDIRECT3DSURFACE9 CMiniMap::m_pZSurface = nullptr;
bool CMiniMap::m_bExplored[TEST_WIDTH][TEST_HEIGHT] = {};

//===================================================
// �R���X�g���N�^
//===================================================
CMiniMap::CMiniMap()
{
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
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	Load();
	Reset();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		nullptr);

	if (m_pVtxBuff == nullptr)
	{// �����Ɏ��s�����ꍇ
		return E_FAIL;
	}

	//�p�x�v�Z
	CulcDiagonal();

	// ���_���ݒ�
	SetpVtx(CHANGE_ALL);

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CMiniMap::Uninit(void)
{
	// ���_�o�b�t�@�̔p��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	// �e�N�X�`���j��
	UnLoad();
}

//===============================================
// �|���S���`�揈��
//===============================================
void CMiniMap::DrawMap(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		//�f�o�C�X�ւ̃|�C���^
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(
		0,
		m_pVtxBuff,
		0,
		sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �}�b�v�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTextureMap);

	// �`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
		0,
		2	//���_���\���̂̃T�C�Y
	);

	// �܂����낭�낷���e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTextureUnex);

	// �`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
		0,
		2	//���_���\���̂̃T�C�Y
	);
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
	CCamera* pOrgCamera = pManager->GetCamera();

	//�o�b�N�o�b�t�@�p
	LPDIRECT3DSURFACE9 pOrgSurface;
	LPDIRECT3DSURFACE9 pOrgZBuffer;

	LPDIRECT3DSURFACE9 pTexSurface;

	//��p�J����
	D3DXMATRIX mtxViewCamera;	// �r���[�}�g���b�N�X
	D3DXMATRIX mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXVECTOR3 posR = D3DXVECTOR3(-2500.0f, 1.0f, 1000.0f);
	D3DXVECTOR3 posV = D3DXVECTOR3(-2500.0f, 6000.0f, 1100.0f);
	D3DXVECTOR3 vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//�v���W�F�N�V�����}�g���̏�����
	D3DXMatrixIdentity(&mtxProjection);

	D3DXMatrixPerspectiveFovLH(&mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		40000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);

	//�r���[�}�g���̏�����
	D3DXMatrixIdentity(&mtxViewCamera);

	//�r���[�}�g���̍쐬
	D3DXMatrixLookAtLH(&mtxViewCamera,
		&posV,
		&posR,
		&vecU);

	//�r���[�}�g���̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &mtxViewCamera);

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
		CObjectManager::GetInstance()->DrawAll(CObjectManager::TYPE_3DONLY);

		// �`��I��
		pDevice->EndScene();
	}

	//�߂�
	pDevice->SetRenderTarget(0, pOrgSurface);
	pDevice->SetDepthStencilSurface(pOrgZBuffer);

	//�T���ς݃G���A�̓������i�e�N�X�`�����j
	//�K�v�ȕϐ�
	D3DXMATRIX mtxViewPort, mtxProj, mtxView, mtx;

	//�K�v�ȃ}�g���v�Z
	{
		//�r���[�}�g���擾
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//�v���W�F�N�V�����}�g���擾
		pDevice->GetTransform(D3DTS_PROJECTION, &mtxProj);

		//�r���[�|�[�g�}�g���ݒ�
		D3DXMatrixIdentity(&mtxViewPort);
		mtxViewPort._11 = TEST_WIDTH * 0.5;
		mtxViewPort._22 = -TEST_HEIGHT * 0.5;
		mtxViewPort._41 = TEST_WIDTH * 0.5;
		mtxViewPort._42 = TEST_HEIGHT * 0.5;

		//�S���|����
		mtx = mtxView * mtxProj * mtxViewPort;	//������D3DXMatrixMultiply����Ă�݂���
	}
	
	//�v���C���[���ׂČ���
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
		int posElaseMinX = ((posX - ELASE_WIDTH) > 0) ? posX - ELASE_WIDTH : 0;
		int posElaseMaxX = ((posX + ELASE_WIDTH) < TEST_WIDTH) ? posX + ELASE_WIDTH : TEST_WIDTH;
		int posElaseMinY = ((posY - ELASE_HEIGHT) > 0) ? posY - ELASE_HEIGHT : 0;
		int posElaseMaxY = ((posY + ELASE_HEIGHT) < TEST_HEIGHT) ? posY + ELASE_HEIGHT : TEST_HEIGHT;

		//���͈͏���
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
// �e�N�X�`����������
//===============================================
void CMiniMap::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�ւ̃|�C���^

	//�e�e�N�X�`������
	D3DXCreateTexture(pDevice, TEST_WIDTH, TEST_HEIGHT,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT, //�����̂��߃f�o�C�X���X�g���͔j�����K�v
		&m_pTextureMap);

	D3DXCreateTexture(pDevice, TEST_WIDTH, TEST_HEIGHT,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT, //�����̂��߃f�o�C�X���X�g���͔j�����K�v
		&m_pTextureUnex);

	//���炩���ߍ����h��Ԃ�
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

	//����Z�o�b�t�@����
	pDevice->CreateDepthStencilSurface(
		TEST_WIDTH, TEST_HEIGHT,
		D3DFMT_D16,
		D3DMULTISAMPLE_NONE,
		0, false ,
		&m_pZSurface,
		nullptr);
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
		//���炩���ߍ����h��Ԃ�
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
// �|���S���ʒu�ݒ菈��
//===============================================
void CMiniMap::SetPosition(const D3DXVECTOR3 pos)
{
	m_pos = pos;

	//���_�Đݒ�
	SetpVtx(CHANGE_POS);
}

//===============================================
// �|���S���p�x�ݒ菈��
//===============================================
void CMiniMap::SetRotation(const D3DXVECTOR3 rot)
{
	m_rot = rot;

	//���_�Đݒ�
	SetpVtx(CHANGE_POS);
}

//===============================================
// �|���S���T�C�Y�ݒ菈��
//===============================================
void CMiniMap::SetSize(float fWidth, float fHeight)
{
	m_fWidth = fWidth;
	m_fHeight = fHeight;

	//�p�x�v�Z
	CulcDiagonal();

	//���_�Đݒ�
	SetpVtx(CHANGE_POS);
}

//===============================================
// �|���S�����_�ݒ菈��
//===============================================
void CMiniMap::SetpVtx(const int nChangeVtx)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	//���_���W�̐ݒ�
	if ((nChangeVtx & CHANGE_POS) == CHANGE_POS)
	{
		//�����
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

	//�@���x�N�g���̐ݒ�
	if ((nChangeVtx & CHANGE_RHW) == CHANGE_RHW)
	{
		//�����
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
	}

	//���_�J���[�̐ݒ�
	if ((nChangeVtx & CHANGE_COL) == CHANGE_COL)
	{
		//�����
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//�e�N�X�`�����W�̐ݒ�
	if ((nChangeVtx & CHANGE_TEX) == CHANGE_TEX)
	{
		//�����
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===============================================
// �|���S���p�x�v�Z����
//===============================================
void CMiniMap::CulcDiagonal(void)
{
	//�Ίp���̒������Z�o����
	m_fLength = sqrtf(m_fWidth * m_fWidth + m_fHeight * m_fHeight) * 0.5f;

	//�Ίp���̊p�x���Z�o����
	m_fAngle = atan2f(m_fWidth, m_fHeight);
}
