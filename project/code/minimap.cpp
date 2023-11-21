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

//�e�X�g�}�N��
#define TEST_WIDTH	(256)
#define TEST_HEIGHT	(144)

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CMiniMap::m_pTexture = nullptr;
LPDIRECT3DSURFACE9 CMiniMap::m_pZSurface = nullptr;

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

	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(
		0,
		m_pVtxBuff,
		0,
		sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

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
	D3DXMATRIX mtxView;			// �r���[�}�g���b�N�X
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
	D3DXMatrixIdentity(&mtxView);

	//�r���[�}�g���̍쐬
	D3DXMatrixLookAtLH(&mtxView,
		&posV,
		&posR,
		&vecU);

	//�r���[�}�g���̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &mtxView);

	//�e�N�X�`��
	//�쐬�e�N�X�`���p�C���^�[�t�F�[�X�擾
	m_pTexture->GetSurfaceLevel(0, &pTexSurface);

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
		CObjectManager::GetInstance()->DrawAll();

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
// �e�N�X�`����������
//===============================================
void CMiniMap::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�ւ̃|�C���^

	D3DXCreateTexture(pDevice, TEST_WIDTH, TEST_HEIGHT,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT, //�����̂��߃f�o�C�X���X�g���͔j�����K�v
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
// �e�N�X�`���J������
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
