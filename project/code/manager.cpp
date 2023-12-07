//===============================================
//
// �}�l�[�W���[�̏��� [manager.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
#include "sound.h"
#include "camera.h"
#include "light.h"
#include "Xfile.h"
#include "texture.h"
#include "game.h"
#include "title.h"
#include "result.h"
#include "tutorial.h"
#include "fade.h"
#include "object.h"
#include "ranking.h"
#include "slow.h"
#include "task_manager.h"
#include "object_manager.h"

//===============================================
// �ÓI�����o�ϐ�
//===============================================
CManager *CManager::m_pManager = NULL;

//===================================================
// �R���X�g���N�^
//===================================================
CManager::CManager()
{
	m_pRenderer = NULL;			// �����_���[�̃|�C���^
	m_pInputKeyboard = NULL;	// ���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
	m_pInputMouse = NULL;		// ���̓f�o�C�X(�}�E�X)�̃|�C���^
	m_pInputPad = NULL;
	m_pDebugProc = NULL;			// �f�o�b�O�\���̃|�C���^
	m_pSound = NULL;					// �T�E���h�̃|�C���^
	m_pCamera = NULL;				// �J�����̃|�C���^
	m_pLight = NULL;					// ���C�g�̃|�C���^
	m_pTexture = NULL;				// �e�N�X�`���̃|�C���^
	m_pModelFile = NULL;				// X�t�@�C�����̃|�C���^
	m_pSlow = NULL;					// �X���[��Ԃւ̃|�C���^
	m_pScene = NULL;					// �V�[���̃|�C���^
	m_pFade = NULL;					// �t�F�[�h�ւ̃|�C���^
}

//===================================================
// �f�X�g���N�^
//===================================================
CManager::~CManager()
{

}

//===================================================
// ����������
//===================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{

	// �����_���[�̐���
	if (m_pRenderer == NULL)
	{// �g�p���Ă��Ȃ��ꍇ
		m_pRenderer = new CRenderer;
	}

	//����������
	if (m_pRenderer != NULL)
	{// �g�p���Ă���ꍇ
		if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
		{//�����������s�����ꍇ
			return E_FAIL;
		}
	}

	// ���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (m_pInputKeyboard == NULL)
	{// �g�p���Ă��Ȃ��ꍇ
		m_pInputKeyboard = new CInputKeyboard;

		//����������
		if (m_pInputKeyboard != NULL)
		{// �g�p���Ă���ꍇ
			if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
			{//�����������s�����ꍇ
				return E_FAIL;
			}
		}
	}

	// ���̓f�o�C�X(�}�E�X)�̐���
	if (m_pInputMouse == NULL)
	{// �g�p���Ă��Ȃ��ꍇ
		m_pInputMouse = new CInputMouse;

		//����������
		if (m_pInputMouse != NULL)
		{// �g�p���Ă���ꍇ
			if (FAILED(m_pInputMouse->Init(hInstance, hWnd)))
			{//�����������s�����ꍇ
				return E_FAIL;
			}
		}
	}

	// ���̓f�o�C�X(�p�b�h)�̐���
	if (m_pInputPad == NULL)
	{// �g�p���Ă��Ȃ��ꍇ
		m_pInputPad = new CInputPad;

		//����������
		if (m_pInputPad != NULL)
		{// �g�p���Ă���ꍇ
			if (FAILED(m_pInputPad->Init(hInstance, hWnd)))
			{//�����������s�����ꍇ
				return E_FAIL;
			}
		}
	}

	// �f�o�b�O�\���̐���
	if (m_pDebugProc == NULL)
	{// �g�p���Ă��Ȃ��ꍇ
		m_pDebugProc = new CDebugProc;
	}

	//����������
	if (m_pDebugProc != NULL)
	{// �g�p���Ă���ꍇ
		m_pDebugProc->Init();
	}

	// �T�E���h�̐���
	if (m_pSound == NULL)
	{// �g�p���Ă��Ȃ��ꍇ
		m_pSound = new CSound;

		// ������
		if (m_pSound != NULL)
		{
			m_pSound->Init(hWnd);
		}
	}

	// �J�����̐���
	if (m_pCamera == NULL)
	{// �g�p���Ă��Ȃ��ꍇ
		m_pCamera = new CMultiCamera;

		// ������
		if (m_pCamera != NULL)
		{
			m_pCamera->Init();

			D3DVIEWPORT9 viewport;

			//�v���C���[�Ǐ]�J�����̉�ʈʒu�ݒ�
			viewport.X = 0;
			viewport.Y = 0;
			viewport.Width = (DWORD)(SCREEN_WIDTH * 1.0f);
			viewport.Height = (DWORD)(SCREEN_HEIGHT * 1.0f);
			viewport.MinZ = 0.0f;
			viewport.MaxZ = 1.0f;

			m_pCamera->SetViewPort(viewport);
		}
	}

	// ���C�g�̐���
	if (m_pLight == NULL)
	{// �g�p���Ă��Ȃ��ꍇ
		m_pLight = new CLight;

		// ������
		if (m_pLight != NULL)
		{
			m_pLight->Init();
		}
	}

	//�e�N�X�`���̐���
	if (m_pTexture == NULL)
	{// �g�p���Ă��Ȃ��ꍇ
		m_pTexture = new CTexture;

		// �����ǂݍ���
		if (m_pTexture != NULL)
		{
			m_pTexture->Load();
		}
	}

	// X�t�@�C�����̐���
	if (m_pModelFile == NULL)
	{// �g�p���Ă��Ȃ��ꍇ
		m_pModelFile = new CXFile;
	}

	// �X���[���̐���
	if (m_pSlow == NULL)
	{
		m_pSlow = new CSlow;
		m_pSlow->Init();
	}

	// ���[�h�̐���
	SetMode(CScene::MODE_GAME);

	return S_OK;
}

//===================================================
// �I������
//===================================================
void CManager::Uninit(void)
{
	// �T�E���h�̒�~
	m_pSound->Stop();

	if (m_pFade != NULL)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = NULL;
	}

	if (m_pScene != NULL)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = NULL;
	}

	if (m_pSlow != NULL)
	{
		m_pSlow->Uninit();
		delete m_pSlow;
		m_pSlow = NULL;
	}

	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}

	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	if (m_pSound != nullptr)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}

	if (m_pInputKeyboard != NULL)
	{// �g�p���Ă���ꍇ
		// �I������
		m_pInputKeyboard->Uninit();

		delete m_pInputKeyboard;	// �������̊J��

		m_pInputKeyboard = NULL;	// �g�p���Ă��Ȃ���Ԃɂ���
	}

	if (m_pInputMouse != NULL)
	{// �g�p���Ă���ꍇ
		// �I������
		m_pInputMouse->Uninit();

		delete m_pInputMouse;	// �������̊J��

		m_pInputMouse = NULL;	// �g�p���Ă��Ȃ���Ԃɂ���
	}

	if (m_pInputPad != NULL)
	{// �g�p���Ă���ꍇ
		// �I������
		m_pInputPad->Uninit();

		delete m_pInputPad;	// �������̊J��

		m_pInputPad = NULL;	// �g�p���Ă��Ȃ���Ԃɂ���
	}

	if (m_pDebugProc != NULL)
	{// �g�p���Ă���ꍇ
		// �I������
		m_pDebugProc->Uninit();

		delete m_pDebugProc;	// �������̊J��

		m_pDebugProc = NULL;	// �g�p���Ă��Ȃ���Ԃɂ���
	}

	if (m_pRenderer != NULL)
	{// �g�p���Ă���ꍇ
		// �I������
		m_pRenderer->Uninit();

		delete m_pRenderer;	// �������̊J��

		m_pRenderer = NULL;	// �g�p���Ă��Ȃ���Ԃɂ���
	}

	if (m_pSound != NULL)
	{// �g�p���Ă���ꍇ
		// �I������
		m_pSound->Uninit();

		delete m_pSound;	// �������̊J��

		m_pSound = NULL;	// �g�p���Ă��Ȃ���Ԃɂ���
	}

	// �e�N�X�`���̔p��
	if (m_pTexture != NULL)
	{// �g�p���Ă���ꍇ
		// �I������
		m_pTexture->Unload();

		delete m_pTexture;	// �������̊J��

		m_pTexture = NULL;	// �g�p���Ă��Ȃ���Ԃɂ���
	}

	// X�t�@�C�����̔p��
	if (m_pModelFile != NULL)
	{// �g�p���Ă���ꍇ
		// �I������
		m_pModelFile->Unload();

		delete m_pModelFile;	// �������̊J��

		m_pModelFile = NULL;	// �g�p���Ă��Ȃ���Ԃɂ���
	}
	//�e��}�l�[�W���̔j��
	CTaskManager::Release();
	CObjectManager::Release();
}

//===================================================
// �X�V����
//===================================================
void CManager::Update(void)
{
	if (m_pFade != NULL)
	{
		m_pFade->Update();
	}
	// �f�o�b�O�\���̍X�V����
	if (m_pDebugProc != NULL)
	{// �g�p���Ă���ꍇ
		m_pDebugProc->Update();
	}

	// �L�[�{�[�h�̍X�V����
	if (m_pInputKeyboard != NULL)
	{// �g�p���Ă���ꍇ
		m_pInputKeyboard->Update();
	}

	// �}�E�X�̍X�V����
	if (m_pInputMouse != NULL)
	{// �g�p���Ă���ꍇ
		m_pInputMouse->Update();
	}

	// �}�E�X�̍X�V����
	if (m_pInputPad != NULL)
	{// �g�p���Ă���ꍇ
		m_pInputPad->Update();
	}

	if (m_pScene != NULL)
	{
		m_pScene->Update();
	}
}

//===================================================
// �`�揈��
//===================================================
void CManager::Draw(void)
{
	if (m_pScene != NULL)
	{
		m_pScene->Draw();
	}
}

//===================================================
// �����_���[�̎擾
//===================================================
CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//===================================================
// ���̓f�o�C�X�̎擾(�L�[�{�[�h)
//===================================================
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//===================================================
// ���̓f�o�C�X�̎擾(�p�b�h)
//===================================================
CInputPad *CManager::GetInputPad(void)
{
	return m_pInputPad;
}

//===================================================
// ���̓f�o�C�X�̎擾(�}�E�X)
//===================================================
CInputMouse *CManager::GetInputMouse(void)
{
	return m_pInputMouse;
}

//===================================================
// �f�o�b�O�\���̎擾
//===================================================
CDebugProc *CManager::GetDebugProc(void)
{
	return m_pDebugProc;
}

//===================================================
// �T�E���h�̎擾
//===================================================
CSound *CManager::GetSound(void)
{
	return m_pSound;
}

//===================================================
// �J�����̎擾
//===================================================
CMultiCamera *CManager::GetCamera(void)
{
	return m_pCamera;
}

//===================================================
// ���C�g�̎擾
//===================================================
CLight *CManager::GetLight(void)
{
	return m_pLight;
}

//===================================================
// �e�N�X�`���̎擾
//===================================================
CTexture *CManager::GetTexture(void)
{
	return m_pTexture;
}

//===================================================
// X�t�@�C�����̎擾
//===================================================
CXFile *CManager::GetModelFile(void)
{
	return m_pModelFile;
}

//===================================================
// �X���[���̎擾
//===================================================
CSlow *CManager::GetSlow(void)
{
	return m_pSlow;
}

//===================================================
// �t�F�[�h���̎擾
//===================================================
CFade *CManager::GetFade(void)
{
	return m_pFade;
}

//===================================================
// �f�[�^�S������
//===================================================
CManager *CManager::GetInstance(void)
{
	if (m_pManager == NULL)
	{
		m_pManager = new CManager;
	}

	return m_pManager;
}

void CManager::Release(void)
{
	if (m_pManager != NULL)
	{
		m_pManager->Uninit();
		delete m_pManager;
		m_pManager = NULL;
	}
}

//===================================================
// �f�[�^�S������
//===================================================
void CManager::DataReset(void)
{
	// �^�X�N�}�l�[�W���[�̏I��
	CTaskManager::GetInstance()->Uninit();

	// �I�u�W�F�N�g�}�l�[�W���[�̏I��
	CObjectManager::GetInstance()->Uninit();

	// �e�N�X�`���̔p��
	if (m_pTexture != NULL)
	{// �g�p���Ă���ꍇ
	 // �I������
		m_pTexture->Unload();

		delete m_pTexture;	// �������̊J��

		m_pTexture = NULL;	// �g�p���Ă��Ȃ���Ԃɂ���
	}

	// X�t�@�C�����̔p��
	if (m_pModelFile != NULL)
	{// �g�p���Ă���ꍇ
		// �I������
		m_pModelFile->Unload();

		delete m_pModelFile;	// �������̊J��

		m_pModelFile = NULL;	// �g�p���Ă��Ȃ���Ԃɂ���
	}

	// �|�C���g���C�g�𖳌��ɂ���
	m_pLight->EnablePointLight(false);

	//�t�F�[�h�̍폜
	m_pFade = NULL;

	//�e�N�X�`���̐���
	if (m_pTexture == NULL)
	{// �g�p���Ă��Ȃ��ꍇ
		m_pTexture = new CTexture;

		// �����ǂݍ���
		if (m_pTexture != NULL)
		{
			m_pTexture->Load();
		}
	}

	// X�t�@�C�����̐���
	if (m_pModelFile == NULL)
	{// �g�p���Ă��Ȃ��ꍇ
		m_pModelFile = new CXFile;
	}

	// �^�X�N�}�l�[�W���[�̏�����
	CTaskManager::GetInstance()->Init();

	// �I�u�W�F�N�g�}�l�[�W���[�̏�����
	CObjectManager::GetInstance()->Init();
}

//===================================================
// ���[�h�ݒ�
//===================================================
void CManager::SetMode(CScene::MODE mode)
{
	// �T�E���h�̒�~
	if (m_pSound != NULL)
	{
		m_pSound->Stop();
	}

	// ���݂̃��[�h�̒�~
	if (m_pScene != NULL)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = NULL;
	}

	if (m_pFade != NULL)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = NULL;
	}

	// �f�[�^���Z�b�g
	DataReset();

	// �V�������[�h�̐���
	m_pScene = CScene::Create(mode);
	m_pScene->SetMode(mode);

	if (m_pScene != NULL)
	{
		m_pScene->Init();
	}

	// �t�F�[�h�̐���
	if (m_pFade == NULL)
	{
		m_pFade = CFade::Create(mode);
	}
}

//===================================================
//
// �V�[���N���X
//
//===================================================
// �R���X�g���N�^
//===================================================
CScene::CScene()
{

}

//===================================================
// �f�X�g���N�^
//===================================================
CScene::~CScene()
{

}

//===================================================
// ����
//===================================================
CScene *CScene::Create(MODE mode)
{
	CScene *pScene = NULL;

	// ���[�h�ʂɐ���
	switch (mode)
	{
	case MODE_TITLE:
		pScene = new CTitle;
		break;

	case MODE_TUTORIAL:
		pScene = new CTutorial;
		break;

	case MODE_GAME:
		pScene = new CGame;
		break;

	case MODE_RESULT:
		pScene = new CResult;
		break;

	case MODE_RANKING:
		pScene = new CRanking;
		break;
	}

	return pScene;
}

//===================================================
// ������
//===================================================
HRESULT CScene::Init(void)
{
	return S_OK;
}

//===================================================
// �I��
//===================================================
void CScene::Uninit(void)
{

}

//===================================================
// �X�V
//===================================================
void CScene::Update(void)
{
	// �J�����̍X�V����
	if (CManager::GetInstance()->GetCamera() != NULL)
	{
		CManager::GetInstance()->GetCamera()->Update();
	}

	// �X���[�̍X�V����
	if (CManager::GetInstance()->GetSlow() != NULL)
	{
		CManager::GetInstance()->GetSlow()->Update();
	}

	// �����_���[�̍X�V����
	if (CManager::GetInstance()->GetRenderer() != NULL)
	{// �g�p���Ă���ꍇ
		CManager::GetInstance()->GetRenderer()->Update();
	}
}

//===================================================
// �`��
//===================================================
void CScene::Draw(void)
{
	// �`�揈��
	if (CManager::GetInstance()->GetRenderer() != NULL)
	{// �g�p���Ă���ꍇ
		CManager::GetInstance()->GetRenderer()->Draw();
	}
}
