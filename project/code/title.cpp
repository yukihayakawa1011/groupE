//===============================================
//
// �^�C�g����ʂ̊Ǘ����� [title.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "title.h"
#include "manager.h"
#include "input.h"
#include "fade.h"
#include "fileload.h"
#include "sound.h"
#include "camera.h"
#include "item.h"
#include "objectX.h"
#include "title_enter.h"
#include "meshdome.h"

//===============================================
// �������O���
//===============================================
namespace {
	const D3DXVECTOR3 ENTERPOS = { 0.0f, 0.0f, 0.0f };	// ENTER ���W
	const D3DXVECTOR3 ENTERROT = { 0.0f, 0.0f, 0.0f };	// ENTER ����
	const int AUTOMOVE_RANKING = 640;	// �����L���O�����J�ڎ���
	const int MOVE_TUTORIAL = 110;		// �`���[�g���A���ɑJ�ڂ���܂ł̎���
}

//===============================================
// �R���X�g���N�^
//===============================================
CTitle::CTitle()
{
	m_nCounterRanking = 0;
	m_nCounterTutorial = 0;
	m_nCounterRanking = 0;
	m_bPush = false;
	m_pFileLoad = nullptr;
	m_pEnter = nullptr;
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
	// enter�C���X�^���X�𐶐�
	m_pEnter = new CTitleEnter;
	m_pEnter->SetPosition(D3DXVECTOR3(0.0f, 700.0f, -700.0f));
	m_pEnter->SetRotation(D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, D3DX_PI * 0.4f));

	//�O���t�@�C���ǂݍ��݂̐���
	if (m_pFileLoad == nullptr)
	{// �g�p���Ă��Ȃ��ꍇ
		m_pFileLoad = new CFileLoad;

		if (m_pFileLoad != nullptr)
		{
			m_pFileLoad->Init();
			m_pFileLoad->SetTitleEnter(m_pEnter);
			m_pFileLoad->OpenFile("data\\TXT\\title_model.txt");
		}
	}

	//�ƃ��f���̐ݒu
	CObjectX::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\house.x", NULL);

	//�J����������
	{
		CManager::GetInstance()->GetCamera()->SetPositionV(D3DXVECTOR3(387.0f, 793.0f, -2328.0f));
		CManager::GetInstance()->GetCamera()->SetPositionR(D3DXVECTOR3(-400.0f, 441.0f, -304.0f));
		CManager::GetInstance()->GetCamera()->SetRotation(D3DXVECTOR3(1.0f, -1.20f, 1.41f));

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

	//�h�[���ǉ�
	CMeshDome::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3000.0f, 3000.0f,3,8,8);

	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_TITLE);

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CTitle::Uninit(void)
{
	if (m_pFileLoad != nullptr)
	{
		m_pFileLoad->Uninit();

		delete m_pFileLoad;		// �������̊J��
		m_pFileLoad = nullptr;
	}

	if (m_pEnter != nullptr) 
	{
		m_pEnter->Uninit();
		delete m_pEnter;
		m_pEnter = nullptr;
	}
}

//===============================================
// �X�V����
//===============================================
void CTitle::Update(void)
{
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();
	CInputKeyboard *pInputKey = CManager::GetInstance()->GetInputKeyboard();

	if (m_pEnter != nullptr) {
		m_pEnter->Update();
	}

	// ���͑J��
	if (pInputKey->GetTrigger(DIK_RETURN) || pInputPad->GetTrigger(CInputPad::BUTTON_START, 0))
	{
		CItem *pItem = CItem::GetTop();

		while (pItem != nullptr)
		{// �g�p����Ă��Ȃ���Ԃ܂�

			CItem *pItemNext = pItem->GetNext();	// ���̃I�u�W�F�N�g�ւ̃|�C���^���擾

			D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.6f;
			move.y = sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.3f;
			move.z = cosf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.6f;
			pItem->SetMove(move);

			//�^�C�v�̕ύX											
			pItem->SetState(CItem::STATE_CRASH);

			pItem = pItemNext;	// ���̃I�u�W�F�N�g�Ɉړ�
		}

		if (m_bPush == false)
		{//1�񂾂����炷
			CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_CLICK);
		}

		m_bPush = true;		//�{�^����������
	}

	if (m_bPush == true)
	{//�X�^�[�g�ɑΉ�����{�^���������ꂽ�i�`���[�g���A����ʑJ�ڏ����j
		m_nCounterTutorial++;		//�`���[�g���A���J�ڃJ�E���^�[���Z

		if (m_nCounterTutorial >= MOVE_TUTORIAL)
		{//�`���[�g���A����ʑJ��
			CManager::GetInstance()->GetFade()->Set(CScene::MODE_TUTORIAL);
		}
	}
	else
	{//�X�^�[�g�ɑΉ�����{�^����������ĂȂ��i�����L���O�J�ڏ����j
		m_nCounterRanking++;		//�����L���O�J�ڃJ�E���^�[���Z

		//�����L���O��ʎ����J��
		if (m_nCounterRanking >= AUTOMOVE_RANKING)
		{//�����L���O�J��
			CManager::GetInstance()->GetFade()->Set(CScene::MODE_RANKING);
		}
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
