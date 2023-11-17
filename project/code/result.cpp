//===============================================
//
// ���U���g��ʂ̊Ǘ����� [result.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "result.h"
#include "object2D.h"
#include "texture.h"
#include "manager.h"
#include "main.h"
#include "input.h"
#include "objectX.h"
#include "fade.h"
#include "ranking.h"
#include "sound.h"
#include "result.h"
#include "fileload.h"
#include "meshdome.h"
#include "character.h"
#include "motion.h"
#include "camera.h"

// �}�N����`
#define RANKING_FILE	"data\\FILE\\ranking.bin"	// �����L���O�t�@�C��
#define MOVE_TIMER	(660)

int CResult::m_nScore = 0;
CResult::TYPE CResult::m_type = CResult::TYPE_MAX;

//===============================================
// �R���X�g���N�^
//===============================================
CResult::CResult()
{
	m_pMeshSky = NULL;
	m_nTimer = 0;
	m_pTime = NULL;

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_apCharacter[nCnt] = NULL;
	}
}

//===============================================
// �f�X�g���N�^
//===============================================
CResult::~CResult()
{

}

//===============================================
// ����������
//===============================================
HRESULT CResult::Init(void)
{
	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_RESULT);
	CTexture *pTexture = CManager::GetInstance()->GetTexture();
	CMeshDome::Create(D3DXVECTOR3(0.0f, -1000.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10000.0f, 10.0f, 3, 10, 10);

	if (m_pFileLoad == NULL)
	{// �g�p���Ă��Ȃ��ꍇ
		m_pFileLoad = new CFileLoad;

		if (m_pFileLoad != NULL)
		{
			m_pFileLoad->Init();
			m_pFileLoad->OpenFile("data\\TXT\\result.txt");
		}
	}

	// ��ނ��Ƃɕ`��
	switch (m_type)
	{

	case TYPE_MULTI_WIN:
	{
		m_apCharacter[TYPE_MULTI_WIN] = CCharacter::Create("data\\TXT\\motion_kidsboy.txt");
		m_apCharacter[TYPE_MULTI_WIN]->GetMotion()->InitSet(4);
		m_apCharacter[TYPE_MULTI_WIN]->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 100.0f));
		m_apCharacter[TYPE_MULTI_WIN]->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
		m_apCharacter[TYPE_MULTI_LOSE] = CCharacter::Create("data\\TXT\\motion_kidsgirl.txt");
		m_apCharacter[TYPE_MULTI_LOSE]->GetMotion()->InitSet(5);
		m_apCharacter[TYPE_MULTI_LOSE]->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -100.0f));
		m_apCharacter[TYPE_MULTI_LOSE]->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));

		CManager::GetInstance()->GetCamera()->SetRotation(D3DXVECTOR3(0.0f, -D3DX_PI * 1.0f, 1.51f));
		CManager::GetInstance()->GetCamera()->SetPositionR(D3DXVECTOR3(1000.0f, 0.0f, 100.0f));

		CObject2D *pObj = CObject2D::Create();
		pObj->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.8f, 0.0f));
		pObj->SetSize(SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.2f);
		pObj->BindTexture(pTexture->Regist("data\\TEXTURE\\result_win.png"));
	}
		break;

	case TYPE_MULTI_LOSE:
	{
		m_apCharacter[TYPE_MULTI_WIN] = CCharacter::Create("data\\TXT\\motion_kidsgirl.txt");
		m_apCharacter[TYPE_MULTI_WIN]->GetMotion()->InitSet(4);
		m_apCharacter[TYPE_MULTI_WIN]->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 100.0f));
		m_apCharacter[TYPE_MULTI_WIN]->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
		m_apCharacter[TYPE_MULTI_LOSE] = CCharacter::Create("data\\TXT\\motion_kidsboy.txt");
		m_apCharacter[TYPE_MULTI_LOSE]->GetMotion()->InitSet(5);
		m_apCharacter[TYPE_MULTI_LOSE]->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -100.0f));
		m_apCharacter[TYPE_MULTI_LOSE]->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));

		CManager::GetInstance()->GetCamera()->SetRotation(D3DXVECTOR3(0.0f, -D3DX_PI * 1.0f, 1.51f));
		CManager::GetInstance()->GetCamera()->SetPositionR(D3DXVECTOR3(1000.0f, 0.0f, -100.0f));

		CObject2D *pObj = CObject2D::Create();
		pObj->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.8f, 0.0f));
		pObj->SetSize(SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.2f);
		pObj->BindTexture(pTexture->Regist("data\\TEXTURE\\result_lose.png"));
	}
		break;

	case TYPE_MAX:
	{
		m_apCharacter[TYPE_MULTI_WIN] = CCharacter::Create("data\\TXT\\motion_kidsboy.txt");
		if (m_nScore != 0)
		{
			m_apCharacter[TYPE_MULTI_WIN]->GetMotion()->InitSet(4);
		}
		else
		{
			m_apCharacter[TYPE_MULTI_WIN]->GetMotion()->InitSet(5);
		}

		m_apCharacter[TYPE_MULTI_WIN]->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 100.0f));
		m_apCharacter[TYPE_MULTI_WIN]->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));

		CManager::GetInstance()->GetCamera()->SetRotation(D3DXVECTOR3(0.0f, -D3DX_PI * 1.0f, 1.51f));
		CManager::GetInstance()->GetCamera()->SetPositionR(D3DXVECTOR3(1000.0f, 0.0f, 0.0f));

		int aScore[NUM_RANK] = {};	// �X�R�A�i�[�p
		m_nRank = -1;	//�����N�C�����ĂȂ����

		// �f�[�^�̓ǂݍ���
		Load(&aScore[0]);

		// �f�[�^�̃\�[�g
		Sort(&aScore[0]);

		// �����N�C���m�F
		RankIn(&aScore[0], m_nScore);
	}
		break;
	}

	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_RANKING);

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CResult::Uninit(void)
{

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apCharacter[nCnt] != NULL)
		{
			m_apCharacter[nCnt]->Uninit();
			delete m_apCharacter[nCnt];
			m_apCharacter[nCnt] = NULL;
		}
	}

	m_type = TYPE_MAX;
	m_nScore = 0;
}

//===============================================
// �X�V����
//===============================================
void CResult::Update(void)
{
	m_nTimer++;

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apCharacter[nCnt] != nullptr)
		{
			m_apCharacter[nCnt]->Update();
		}
	}

	if (CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_RETURN) || m_nTimer > MOVE_TIMER 
		|| CManager::GetInstance()->GetInputPad()->GetTrigger(CInputPad::BUTTON_A, 0) || CManager::GetInstance()->GetInputPad()->GetTrigger(CInputPad::BUTTON_START, 0))
	{
		CManager::GetInstance()->GetFade()->Set(CScene::MODE_RANKING);
	}

	CScene::Update();
}

//===============================================
// �`�揈��
//===============================================
void CResult::Draw(void)
{
	CScene::Draw();
}

//===============================================
// �����L���O�f�[�^�ۑ�
//===============================================
void CResult::Save(int *pScore)
{
	FILE *pFile;

	pFile = fopen(RANKING_FILE, "wb");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

	 //�f�[�^��ǂݍ���
		fwrite(pScore, sizeof(int), NUM_RANK, pFile);

		//�t�@�C�������
		fclose(pFile);
	}
}

//===============================================
// �����L���O�f�[�^�ǂݍ���
//===============================================
void CResult::Load(int *pScore)
{
	FILE *pFile;

	pFile = fopen(RANKING_FILE, "rb");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

	 //�f�[�^��ǂݍ���
		fread(pScore, sizeof(int), NUM_RANK, pFile);

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
	 //�v�f�����Ă���
		for (int nCntRanking = 0; nCntRanking < NUM_RANK; nCntRanking++)
		{
			pScore[nCntRanking] = 500 + (nCntRanking * 100);
		}
	}
}

//===============================================
// �����L���O�f�[�^�\�[�g
//===============================================
void CResult::Sort(int *pScore)
{
	// �~���\�[�g
	for (int nCntFst = 0; nCntFst < NUM_RANK - 1; nCntFst++)
	{
		int nTempNum = nCntFst;	// ���̈�ԑ傫���ԍ�

		for (int nCntSec = nCntFst + 1; nCntSec < NUM_RANK; nCntSec++)
		{
			if (pScore[nCntSec] > pScore[nTempNum])
			{// �l���傫���ꍇ
				nTempNum = nCntSec;	// �傫���ԍ���ύX
			}
		}

		if (nTempNum != nCntFst)
		{// �ύX����ꍇ
			int nTemp = pScore[nCntFst];
			pScore[nCntFst] = pScore[nTempNum];
			pScore[nTempNum] = nTemp;
		}
	}
}

//===============================================
// �����L���O�C���m�F
//===============================================
void CResult::RankIn(int *pScore, int nResult)
{
	if (nResult > pScore[NUM_RANK - 1])
	{
		pScore[NUM_RANK - 1] = nResult;

		// �\�[�g����
		Sort(pScore);

		// �ۑ�����
		Save(pScore);

		//�����N�C���������ʂ��m�F����
		for (int nCntRank = 0; nCntRank < NUM_RANK; nCntRank++)
		{
			if (pScore[nCntRank] == nResult)
			{
				m_nRank = nCntRank;	// �����N�C���������ʂ�ۑ�			
				break;
			}
		}
	}
}