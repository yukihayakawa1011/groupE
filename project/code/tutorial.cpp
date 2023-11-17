//===============================================
//
// �`���[�g���A����ʂ̊Ǘ����� [tutorial.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "tutorial.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "time.h"
#include "camera.h"
#include "light.h"
#include "texture.h"
#include "fileload.h"
#include "Xfile.h"
#include "input.h"
#include "fade.h"
#include "result.h"
#include "sound.h"
#include "debugproc.h"
#include "player.h"
#include "game.h"

//===============================================
// �}�N����`
//===============================================

//===============================================
// �ÓI�����o�ϐ�
//===============================================

//===============================================
// �R���X�g���N�^
//===============================================
CTutorial::CTutorial()
{
	// �l�̃N���A
	m_pFileLoad = NULL;
}

//===============================================
// �f�X�g���N�^
//===============================================
CTutorial::~CTutorial()
{

}

//===============================================
// ����������
//===============================================
HRESULT CTutorial::Init(void)
{
	// �O���t�@�C���ǂݍ��݂̐���
	if (m_pFileLoad == NULL)
	{// �g�p���Ă��Ȃ��ꍇ
		m_pFileLoad = new CFileLoad;

		if (m_pFileLoad != NULL)
		{
			m_pFileLoad->Init();
			m_pFileLoad->OpenFile("data\\TXT\\tutorial.txt");
		}
	}

	//�J����������
	{
		CManager::GetInstance()->GetCamera()->Init();
		D3DVIEWPORT9 viewport;
		//�v���C���[�Ǐ]�J�����̉�ʈʒu�ݒ�
		viewport.X = 0;
		viewport.Y = 0;
		viewport.Width = (DWORD)(SCREEN_WIDTH * 1.0f);
		viewport.Height = (DWORD)(SCREEN_HEIGHT * 1.0f);
		viewport.MinZ = 0.0f;
		viewport.MaxZ = 1.0f;
		CManager::GetInstance()->GetCamera()->SetViewPort(viewport);
	}

	// �l�����|�C���^����
	m_ppPlayer = new CPlayer*[PLAYER_MAX];

	m_ppPlayer[0] = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		"data\\TXT\\motion_ninjabody.txt", "data\\TXT\\motion_ninjaleg.txt");
	m_ppPlayer[0]->BindId(0);
	m_ppPlayer[0]->SetType(CPlayer::TYPE_ACTIVE);

	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_TUTORIAL);

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CTutorial::Uninit(void)
{
	if (m_pFileLoad != NULL)
	{
		m_pFileLoad->Uninit();

		delete m_pFileLoad;		// �������̊J��
		m_pFileLoad = NULL;
	}

	if (m_ppPlayer != NULL)
	{// �g�p���Ă����ꍇ
		int nNum = CPlayer::GetNum();
		for (int nCnt = 0; nCnt < nNum; nCnt++)
		{
			// �I������
			m_ppPlayer[nCnt]->Uninit();
			m_ppPlayer[nCnt] = NULL;	// �g�p���Ă��Ȃ���Ԃɂ���
		}

		delete[] m_ppPlayer;	// �|�C���^�̊J��
		m_ppPlayer = NULL;	// �g�p���Ă��Ȃ���Ԃɂ���
	}
}

//===============================================
// �X�V����
//===============================================
void CTutorial::Update(void)
{
	if (CManager::GetInstance()->GetInputPad()->GetTrigger(CInputPad::BUTTON_START, 0) || CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{
		CManager::GetInstance()->GetFade()->Set(CScene::MODE_GAME);
		CGame::SetNumPlayer(CPlayer::GetNum());
	}

	bool bCreate = false;

	if (CPlayer::GetNum() < PLAYER_MAX){ // �l�����ő�ł͂Ȃ��ꍇ
		if (CManager::GetInstance()->GetInputPad()->GetTrigger(CInputPad::BUTTON_START, CPlayer::GetNum())) {
			int nId = CPlayer::GetNum();
			m_ppPlayer[nId] = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\TXT\\motion_ninjabody.txt", "data\\TXT\\motion_ninjaleg.txt");
			m_ppPlayer[nId]->BindId(nId);
			m_ppPlayer[nId]->SetType(CPlayer::TYPE_ACTIVE);
			bCreate = true;
		}
	}

	if (CPlayer::GetNum() - 1 > 0 && !bCreate) { // �l�����ő�ł͂Ȃ��ꍇ
		if (CManager::GetInstance()->GetInputPad()->GetTrigger(CInputPad::BUTTON_START, CPlayer::GetNum() - 1)) {
			int nId = CPlayer::GetNum() - 1;
			m_ppPlayer[nId]->Uninit();
			m_ppPlayer[nId] = 0;
		}
	}

	// �X�V����
	CScene::Update();
}

//===============================================
// �`�揈��
//===============================================
void CTutorial::Draw(void)
{
	CScene::Draw();
}

//===================================================
// �t�@�C���ǂݍ��݂̎擾
//===================================================
CFileLoad *CTutorial::GetFileLoad(void)
{
	return m_pFileLoad;
}
