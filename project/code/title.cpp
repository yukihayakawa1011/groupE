//===============================================
//
// �^�C�g����ʂ̊Ǘ����� [title.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "title.h"
#include "object2D.h"
#include "texture.h"
#include "manager.h"
#include "main.h"
#include "input.h"
#include "fade.h"
#include "fileload.h"
#include "meshcylinder.h"
#include "meshdome.h"
#include "light.h"
#include "sound.h"
#include "camera.h"

//===============================================
// �}�N����`
//===============================================
#define AUTOMOVE_RANKING	(1200)	// �����L���O�����J��
#define TITLE_CAMLENGTH		(1000.0f)
#define TITLE_CAMROTZ		(D3DX_PI * 0.35f)

//===============================================
// �R���X�g���N�^
//===============================================
CTitle::CTitle()
{
	m_nTimer = 0;
	m_pFileLoad = NULL;
	m_bClick = false;
	m_fMoveCol = 0.01f;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

//===============================================
// �f�X�g���N�^
//===============================================
CTitle::~CTitle()
{

}

//===============================================
// ����������
//===============================================
HRESULT CTitle::Init(void)
{
	//�O���t�@�C���ǂݍ��݂̐���
	if (m_pFileLoad == NULL)
	{// �g�p���Ă��Ȃ��ꍇ
		m_pFileLoad = new CFileLoad;

		if (m_pFileLoad != NULL)
		{
			m_pFileLoad->Init();
			m_pFileLoad->OpenFile("data\\TXT\\model.txt");
		}
	}

	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_TITLE);

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CTitle::Uninit(void)
{
	if (m_pFileLoad != NULL)
	{
		m_pFileLoad->Uninit();

		delete m_pFileLoad;		// �������̊J��
		m_pFileLoad = NULL;
	}
}

//===============================================
// �X�V����
//===============================================
void CTitle::Update(void)
{
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();
	CInputKeyboard *pInputKey = CManager::GetInstance()->GetInputKeyboard();

	// ���͑J��
	if (pInputKey->GetTrigger(DIK_RETURN) || pInputPad->GetTrigger(CInputPad::BUTTON_A, 0))
	{
		CManager::GetInstance()->GetFade()->Set(CScene::MODE_TUTORIAL);

		if (m_bClick == false)
		{
			m_col.a = 1.0f;
			m_bClick = true;
			CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_CLICK);
		}
	}

	if (CManager::GetInstance()->GetCamera() != NULL)
	{
		//CManager::GetInstance()->GetCamera()->TitleRotateCamera();
	}

	CScene::Update();
}

//===============================================
// �`�揈��
//===============================================
void CTitle::Draw(void)
{
	CScene::Draw();
}
