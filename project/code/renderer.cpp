//===================================================
//
// DirectX�̃����_���[���� [renderer.cpp]
// Author : Ibuki Okusada
//
//===================================================
#include "renderer.h"
#include "debugproc.h"
#include "manager.h"
#include "input.h"
#include "task_manager.h"
#include "object_manager.h"
#include "object.h"

//===================================================
// �R���X�g���N�^
//===================================================
CRenderer::CRenderer()
{
	// �l�̃N���A
	m_pD3D = NULL;			//Direct3D�I�u�W�F�N�g�̃|�C���^
	m_pD3DDevice = NULL;	//Direct3D�f�o�C�X�ւ̃|�C���^
	pTexture = NULL;
	pTexture = NULL;
	m_pRenderTextureSurface = NULL;
	m_pZSurface = NULL;
}

//===================================================
// �f�X�g���N�^
//===================================================
CRenderer::~CRenderer()
{

}

//===================================================
// ����������
//===================================================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;	// �f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;	// �v���[���e�[�V�����p�����[�^

	// DirectX3D�I�u�W�F�N�g�̍쐬
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.BackBufferWidth = SCREEN_WIDTH;						// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;						// �o�b�N�o�b�t�@�[�̌`��
	d3dpp.BackBufferCount = 1;									// �o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// �_�u���o�b�t�@�̐؂�ւ�
	d3dpp.EnableAutoDepthStencil = TRUE;						// �f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;					// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;									// �E�C���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// ���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// �f�v�X�o�b�t�@�Ƃ���16bit���g��	

	// Direct3D�f�o�C�X�̍쐬
	if (FAILED(m_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{
		if (FAILED(m_pD3D->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			if (FAILED(m_pD3D->CreateDevice(
				D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//�����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�e�N�X�`���X�e�[�W�X�e�[�g
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//
	D3DXCreateTexture(m_pD3DDevice, SCREEN_WIDTH, SCREEN_HEIGHT, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &pTexture);
	pTexture->GetSurfaceLevel(0, &(m_pRenderTextureSurface));
	m_pD3DDevice->CreateDepthStencilSurface(SCREEN_WIDTH, SCREEN_HEIGHT, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, false, &m_pZSurface, nullptr);
	m_pD3DDevice->GetRenderTarget(0, &m_pOrgSurface);
	m_pD3DDevice->GetDepthStencilSurface(&m_pOrgZBuffer);

	return S_OK;
}

//===================================================
// �I������
//===================================================
void CRenderer::Uninit(void)
{
	// �^�X�N�̔p��
	CTaskManager::GetInstance()->Uninit();

	// �I�u�W�F�N�g�̔p��
	CObjectManager::GetInstance()->Uninit();

	// Direct3D�f�o�C�X�̔p��
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	// Direct3D�I�u�W�F�N�g�̔p��
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}

	if (pTexture != NULL)
	{
		pTexture->Release();
		pTexture = NULL;
	}

	if (m_pRenderTextureSurface != NULL)
	{
		m_pRenderTextureSurface->Release();
		m_pRenderTextureSurface = NULL;
	}

	if (m_pZSurface != NULL)
	{
		m_pZSurface->Release();
		m_pZSurface = NULL;
	}
}

//===================================================
// �X�V����
//===================================================
void CRenderer::Update(void)
{
	// �^�X�N�̑S�X�V
	CTaskManager::GetInstance()->Update();

#if _DEBUG	// �f�o�b�O��
	CInputKeyboard *pKey = CManager::GetInstance()->GetInputKeyboard();

	if (pKey->GetTrigger(DIK_F2) == true)
	{
		// ���C���[�t���[���ݒ�
		SetWire(m_bWire ? false : true);
	}
#endif
}

//===================================================
// �`�揈��
//===================================================
void CRenderer::Draw(void)
{
	CDebugProc *pDebugProc = CManager::GetInstance()->GetDebugProc();

	// ��ʃN���A
	m_pD3DDevice->Clear(
		0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0),
		1.0f,
		0);

	// �`��J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{// �`�悪���������ꍇ

	 // �I�u�W�F�N�g�̕`��
	 CObjectManager::GetInstance()->Draw();

#if _DEBUG	// �f�o�b�O��

	 // �G�f�B�^�[�̕`��
#endif

		// �f�o�b�O�\��
		if (pDebugProc != NULL)
		{
			pDebugProc->Draw();
		}

		// �`��I��
		m_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//===================================================
// �f�o�C�X�̎擾
//===================================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_pD3DDevice;
}

//===================================================
// ���C���[�t���[���ݒ�
//===================================================
void CRenderer::SetWire(bool bWire)
{
	m_bWire = bWire;
	//�`�惂�[�h�̕ύX
	switch (m_bWire)
	{
	case true:
		// ���C���[�t���[���`��ɕύX
		m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		break;
	case false:
		// �\���b�h�`��ɕύX
		m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		break;
	}
}