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
#include "item.h"
#include "objectX.h"

//===============================================
// �}�N����`
//===============================================
#define AUTOMOVE_RANKING	(640)	// �����L���O�����J��
#define TITLE_CAMLENGTH		(1000.0f)
#define TITLE_CAMROTZ		(D3DX_PI * 0.35f)
#define MOVE_TUTORIAL		(110)	//�`���[�g���A���ɑJ�ڂ���܂�

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
	m_nCounter = 0;
	m_bPush = false;
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
			m_pFileLoad->OpenFile("data\\TXT\\title_model.txt");
		}
	}

	//�ƃ��f���̐ݒu
	CObjectX::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\house.x", NULL);

	//�J����������
	{
		/*CManager::GetInstance()->GetCamera()->Init();*/

		CManager::GetInstance()->GetCamera()->SetPositionV(D3DXVECTOR3(-0.0f, 0.0f, 0.0f));
		CManager::GetInstance()->GetCamera()->SetPositionR(D3DXVECTOR3(75.0f, 300.0f, -0.0f));
		CManager::GetInstance()->GetCamera()->SetRotation(D3DXVECTOR3(1.0f, -1.6f, 1.35f));

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
	if (pInputKey->GetTrigger(DIK_RETURN) || pInputPad->GetTrigger(CInputPad::BUTTON_START, 0))
	{
		CItem *pItem = CItem::GetTop();

		while (pItem != NULL)
		{// �g�p����Ă��Ȃ���Ԃ܂�

			CItem *pItemNext = pItem->GetNext();	// ���̃I�u�W�F�N�g�ւ̃|�C���^���擾

			D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.6f;
			move.z = cosf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.6f;
			pItem->SetMove(move);

			//�^�C�v�̕ύX											
			pItem->SetState(CItem::STATE_CRASH);

			pItem = pItemNext;	// ���̃I�u�W�F�N�g�Ɉړ�
		}

		m_bPush = true;		//�{�^����������

		if (m_bClick == false)
		{
			m_col.a = 1.0f;
			m_bClick = true;
			CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_CLICK);
		}
	}

	if (m_bPush == true)
	{
		m_nCounter++;

		if (m_nCounter >= MOVE_TUTORIAL)
		{
			CManager::GetInstance()->GetFade()->Set(CScene::MODE_TUTORIAL);
		}
	}

	if (CManager::GetInstance()->GetCamera() != NULL)
	{
		//CManager::GetInstance()->GetCamera()->TitleRotateCamera();
	}

	//�����L���O��ʎ����J��
	if (m_bClick == false && m_bPush == false)
	{
		m_nTimer++;

		if (m_nTimer >= AUTOMOVE_RANKING)
		{
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
