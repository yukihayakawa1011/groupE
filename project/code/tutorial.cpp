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
#include "goal.h"
#include "gimmick_rotatedoor.h"
#include "gimmick_startdoor.h"
#include "gimmick_lever.h"
#include "gimmick_multidoor.h"
#include "gimmick_button.h"
#include "gimmick_spear.h"
#include "gimmick_pull.h"
#include "object3D.h"
#include "enemy.h"
#include "item.h"
#include "particle.h"
#include "entryicon.h"

// �������O���
namespace
{
	const char* FILEPASS = "data\\TXT\\player";	// �t�@�C���̃p�X
	const char* FILEEXT = ".txt";				// �t�@�C���̊g���q
	const int FILEPASS_SIZE = (200);	// �t�@�C���̃p�X�T�C�Y
}

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

	for (int i = 0; i < NUM_PLAYER; i++)
	{
		m_apObject[i] = nullptr;
	}

	for (int i = 0; i < NUM_PORI; i++)
	{
		m_pObject3D[i] = nullptr;
	}

	for (int i = 0; i < NUM_ENEMY; i++)
	{
		m_apEnemy[i] = nullptr;
	}
	
	m_nCntRespawn = 0;
	m_nEnemyId = 0;
	m_bEnd = false;
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
		//CManager::GetInstance()->GetCamera()->Init();

		CManager::GetInstance()->GetCamera()->SetPositionV(D3DXVECTOR3(-874.3f, 1124.15f, 1717.2f));
		CManager::GetInstance()->GetCamera()->SetPositionR(D3DXVECTOR3(-320.3f, 1.0f, -91.6f));
		CManager::GetInstance()->GetCamera()->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, D3DX_PI * 0.1f));

		D3DVIEWPORT9 viewport;
		//�v���C���[�Ǐ]�J�����̉�ʈʒu�ݒ�
		viewport.X = 0;
		viewport.Y = 0;
		viewport.Width = (DWORD)(SCREEN_WIDTH * 1.0f);
		viewport.Height = (DWORD)(SCREEN_HEIGHT * 1.0f);
		viewport.MinZ = 0.0f;
		viewport.MaxZ = 1.0f;
		CManager::GetInstance()->GetCamera()->SetViewPort(viewport);
		CManager::GetInstance()->GetCamera()->SetActive(false);
	}

	// ��]��
	CGimmickRotateDoor::Create(D3DXVECTOR3(-700.0f, 0.0f, -50.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));

	// �S�[��
	CGoal::Create(D3DXVECTOR3(-1350.0f, 0.0f, -1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f);

	// ���͔�
	CGimmickButton *pButton = CGimmickButton::Create(D3DXVECTOR3(-1700.0f, 0.0f, -600.0f));
	CGimmickMultiDoor *pMultiDoor = CGimmickMultiDoor::Create(D3DXVECTOR3(-1350.0f, 0.0f, -1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pMultiDoor->SetNumButton(1);
	pMultiDoor->BindButton(pButton);

	// ��
	CGimmickPull::Create(D3DXVECTOR3(-400.0f, 0.0f, -800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CGimmickPull::Create(D3DXVECTOR3(-200.0f, 0.0f, -800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CGimmickPull::Create(D3DXVECTOR3(0.0f, 0.0f, -800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// �n�ʂ���̑�
	CGimmickSpear::Create(D3DXVECTOR3(-850.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CGimmickSpear::TYPE_AUTO);

	// �l�����|�C���^����
	m_ppPlayer = new CPlayer*[PLAYER_MAX];

	m_ppPlayer[0] = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		"data\\TXT\\player0\\motion_ninjabody.txt", "data\\TXT\\player0\\motion_ninjaleg.txt");
	m_ppPlayer[0]->BindId(0);
	m_ppPlayer[0]->SetType(CPlayer::TYPE_ACTIVE);

	for (int i = 0; i < NUM_ENEMY; i++)
	{
		if (m_apEnemy[i] == nullptr)
		{// �g�p����Ă��Ȃ��ꍇ

			m_apEnemy[i] = CEnemy::Create(D3DXVECTOR3(200.0f - i * 500.0f, 0.0f, 350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, NULL);
		}
	}

	// �G���g���[�A�C�R��
	{
		for (int i = 0; i < NUM_PLAYER; i++)
		{
			if (m_apObject[i] == nullptr)
			{// �g�p����Ă��Ȃ�������

				m_apObject[i] = CEntryIcon::Create(D3DXVECTOR3(190.0f + i * 300.0f, 625.0f, 0.0f), i, 125.0f, 75.0f);
			}
		}
	}
	
	// 0�Ԗڂ����G���g���[���Ă����Ԃɂ���
	if (m_apObject[0] != nullptr)
	{
		m_apObject[0]->SetbEntry(true);
		m_apObject[0]->Entryed();
	}

	CItem::Create(D3DXVECTOR3(-900.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItem::TYPE_BRECELET, NULL);
	CItem::Create(D3DXVECTOR3(-900.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItem::TYPE_CUP, NULL);
	CItem::Create(D3DXVECTOR3(-900.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItem::TYPE_GEM00, NULL);
	CItem::Create(D3DXVECTOR3(-900.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItem::TYPE_GEM01, NULL);
	CItem::Create(D3DXVECTOR3(-900.0f, 0.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItem::TYPE_GOLDBAR, NULL);
	CItem::Create(D3DXVECTOR3(-1300.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItem::TYPE_JAR, NULL);
	CItem::Create(D3DXVECTOR3(-1300.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItem::TYPE_KUNAI, NULL);
	CItem::Create(D3DXVECTOR3(-1300.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItem::TYPE_RING00, NULL);
	CItem::Create(D3DXVECTOR3(-1300.0f, 0.0f, 400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItem::TYPE_SCROLL, NULL);
	CItem::Create(D3DXVECTOR3(-1300.0f, 0.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItem::TYPE_SHURIKEN, NULL);

	// ��{����
	if (m_pObject3D[0] == nullptr)
	{
		m_pObject3D[0] = CObject3D::Create(D3DXVECTOR3(600.0f, 10.0f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_pObject3D[0]->SetRotation(D3DXVECTOR3(D3DX_PI * 0.5f, D3DX_PI, 0.0f));
		m_pObject3D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pObject3D[0]->SetSize(100.0f, 100.0f);
		m_pObject3D[0]->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\tutorial000.png"));
	}
	
	// �M�~�b�N
	if (m_pObject3D[1] == nullptr)
	{
		m_pObject3D[1] = CObject3D::Create(D3DXVECTOR3(-1300.0f, 10.0f, -550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_pObject3D[1]->SetRotation(D3DXVECTOR3(D3DX_PI * 0.5f, D3DX_PI, 0.0f));
		m_pObject3D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pObject3D[1]->SetSize(100.0f, 100.0f);
		m_pObject3D[1]->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\tutorial004.png"));
	}

	// �E�p�֘A
	if (m_pObject3D[2] == nullptr)
	{
		m_pObject3D[2] = CObject3D::Create(D3DXVECTOR3(600.0f, 10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_pObject3D[2]->SetRotation(D3DXVECTOR3(D3DX_PI * 0.5f, D3DX_PI, 0.0f));
		m_pObject3D[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pObject3D[2]->SetSize(100.0f, 100.0f);
		m_pObject3D[2]->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\tutorial003.png"));
	}

	// ����֘A
	if (m_pObject3D[3] == nullptr)
	{
		m_pObject3D[3] = CObject3D::Create(D3DXVECTOR3(-1300.0f, 10.0f, -50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_pObject3D[3]->SetRotation(D3DXVECTOR3(D3DX_PI * 0.5f, D3DX_PI, 0.0f));
		m_pObject3D[3]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pObject3D[3]->SetSize(100.0f, 100.0f);
		m_pObject3D[3]->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\tutorial001.png"));
	}

	//	��]��
	if (m_pObject3D[4] == nullptr)
	{
		m_pObject3D[4] = CObject3D::Create(D3DXVECTOR3(-500.0f, 10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_pObject3D[4]->SetRotation(D3DXVECTOR3(D3DX_PI * 0.5f, D3DX_PI, 0.0f));
		m_pObject3D[4]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pObject3D[4]->SetSize(100.0f, 100.0f);
		m_pObject3D[4]->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\tutorial002.png"));
	}

	////	��]��
	//if (m_pObject3D[5] == nullptr)
	//{
	//	m_pObject3D[5] = CObject3D::Create(D3DXVECTOR3(650.0f, 10.0f, 450.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//	m_pObject3D[5]->SetRotation(D3DXVECTOR3(D3DX_PI * 0.5f, D3DX_PI, 0.0f));
	//	m_pObject3D[5]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//	m_pObject3D[5]->SetSize(100.0f, 100.0f);
	//	m_pObject3D[5]->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\tutorial002.png"));
	//}

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

	for (int i = 0; i < NUM_PORI; i++)
	{
		if (m_pObject3D[i] != nullptr)
		{// �g�p����Ă���ꍇ

			// �g�p���Ă��Ȃ���Ԃɂ���
			m_pObject3D[i] = nullptr;
		}
	}

	for (int i = 0; i < NUM_ENEMY; i++)
	{
		if (m_apEnemy[i] != nullptr)
		{// �g�p����Ă���ꍇ

		 // �g�p���Ă��Ȃ���Ԃɂ���
			m_apEnemy[i] = nullptr;
		}
	}

	for (int i = 0; i < NUM_PLAYER; i++)
	{
		if (m_apObject[i] != nullptr)
		{
			m_apObject[i]->Uninit();
			m_apObject[i] = nullptr;
		}
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

	CManager::GetInstance()->GetCamera()->SetActive(true);
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
			char aBodyPass[FILEPASS_SIZE] = "";		// ���̃p�X
			char aLegPass[FILEPASS_SIZE] = "";		// �����g�p�X

			sprintf(&aBodyPass[0], "%s%d\\motion_ninjabody%s",FILEPASS, nId, FILEEXT);
			sprintf(&aLegPass[0], "%s%d\\motion_ninjaleg%s", FILEPASS, nId, FILEEXT);

			m_ppPlayer[nId] = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), &aBodyPass[0], &aLegPass[0]);
			m_ppPlayer[nId]->BindId(nId);
			m_ppPlayer[nId]->SetType(CPlayer::TYPE_ACTIVE);
			// ���̃p�[�e�B�N������
			CParticle::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEffect::TYPE_SMAKE);
			bCreate = true;
			m_apObject[nId]->SetbEntry(true);
			m_apObject[nId]->Entryed();
		}
	}

	if (CPlayer::GetNum() - 1 > 0 && !bCreate) { // �l�����ő�ł͂Ȃ��ꍇ
		if (CManager::GetInstance()->GetInputPad()->GetTrigger(CInputPad::BUTTON_START, CPlayer::GetNum() - 1)) {
			int nId = CPlayer::GetNum() - 1;
			m_ppPlayer[nId]->Uninit();
			m_ppPlayer[nId] = 0;
			m_apObject[nId]->SetbEntry(false);
			m_apObject[nId]->NoEntry();
		}
	}

	for (int i = 0; i < NUM_PORI; i++)
	{
		if (m_pObject3D[i] != nullptr)
		{// �g�p����Ă���ꍇ

			// �߂Â��Ƒ傫���Ȃ�
			m_pObject3D[i]->ZoomSize(m_ppPlayer, 100.0f);
		}
	}

	if (CEnemy::GetNum() <= 0)
	{// �G���S�����񂾂�Đ���

		for (int i = 0; i < NUM_ENEMY; i++)
		{
			// �g�p���Ă��Ȃ���Ԃɂ���
			m_apEnemy[i] = nullptr;

			if (m_apEnemy[i] == nullptr)
			{// �g�p���Ă��Ȃ�������
				
				m_apEnemy[i] = CEnemy::Create(D3DXVECTOR3(200.0f - i * 500.0f, 0.0f, 550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, NULL);
			}
		}
	}

	if (EndCheck()) 
	{// �S���S�[�����Ă���

		// �Q�[���ɑJ��
		CManager::GetInstance()->GetFade()->Set(CScene::MODE_GAME);
		CGame::SetNumPlayer(CPlayer::GetNum());
	}

	// �X�V����
	CScene::Update();
}

//===============================================
// �`�揈��
//===============================================
void CTutorial::Draw(void)
{
	// �`�揈��
	CScene::Draw();
}

//===================================================
// �t�@�C���ǂݍ��݂̎擾
//===================================================
CFileLoad *CTutorial::GetFileLoad(void)
{
	return m_pFileLoad;
}

//===================================================
// �t�@�C���ǂݍ��݂̎擾
//===================================================
bool CTutorial::EndCheck(void)
{
	CPlayer *pPl = CPlayer::GetTop();	// �v���C���[
	int nNumGoal = 0;

	// �S�[�����Ă���l���𔻒�
	while (pPl != nullptr) {

		CPlayer *pPlNext = pPl->GetNext();	// �����o����

		if (!pPl->GetGoal()) {	// �S�[�����Ă��Ȃ�
			break;
		}

		nNumGoal++;
		pPl = pPlNext;	// ���Ɉړ�
	}

	if (nNumGoal >= CPlayer::GetNum()) {	// �S���S�[��
		return true;
	}

	return false;
}
