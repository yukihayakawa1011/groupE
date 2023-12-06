//===============================================
//
// �����L���O��ʂ̊Ǘ����� [ranking.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "ranking.h"
#include "object2D.h"
#include "texture.h"
#include "manager.h"
#include "main.h"
#include "input.h"
#include "fade.h"
#include "light.h"
#include "sound.h"
#include "camera.h"
#include "number.h"
#include "score.h"
#include "objectX.h"
#include "item.h"
#include "object2D.h"
#include "meshdome.h"
#include "camera.h"

//===============================================
// �}�N����`
//===============================================
#define RANKING_FILE_ONE	"data\\FILE\\rankingone.bin"	// �����L���O�t�@�C��
#define RANKING_FILE_TEAM	"data\\FILE\\rankingteam.bin"	// �����L���O�t�@�C��
#define AUTOMOVE_TITLE	(600)						// �^�C�g�������J�ڃ^�C�}�[

//===============================================
// �ÓI�����o�ϐ�
//===============================================
CScore *CRanking::m_apScore[NUM_RANKING][NUM_RANK] = {};	// �����L���O��
CScore *CRanking::m_apNowScore[NUM_NOWSCORE] = {};	// �����L���O�̃|�C���^
int CRanking::m_nScore = 0;					// �X�R�A
int CRanking::m_nTotalScore = 0;			// �X�R�A

//===============================================
// �R���X�g���N�^
//===============================================
CRanking::CRanking()
{
	// �l���N���A����
	m_nTimer = 0;
	m_nRank = 0;
	m_nCounter = 0;
	m_bOne = false;
	m_bTotal = false;
	m_nOne = -1;
	m_nTotal = -1;
}

//===============================================
// �f�X�g���N�^
//===============================================
CRanking::~CRanking()
{

}

//===============================================
// ����������
//===============================================
HRESULT CRanking::Init(void)
{
	int aScore[NUM_RANK] = {};	// �X�R�A�i�[�p
	int aTotalScore[NUM_RANK] = {};	// �X�R�A�i�[�p
	m_nRank = -1;	//�����N�C�����ĂȂ����


	CObjectX::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\coin_tower00.x", NULL);

	for (int nCntRanking = 0; nCntRanking < NUM_RANKING; nCntRanking++)
	{
		for (int nCnt = 0; nCnt < NUM_RANK; nCnt++)
		{
			m_pObjectRank[nCntRanking][nCnt] = CObject2D::Create(7);
			m_pObjectRank[nCntRanking][nCnt]->SetPosition(D3DXVECTOR3(200.0f + nCntRanking * 600.0f, 400.0f + (nCnt* 100.0f), 0.0f));
			m_pObjectRank[nCntRanking][nCnt]->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\rank00.png"));
		}
	}

	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		m_pObject[nCnt] = CObject2D::Create(7);
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_pObject[nCnt]->SetPosition(D3DXVECTOR3(450.0f + nCnt * 600.0f, 300.0f, 0.0f));
		m_pObject[nCnt]->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\new_record00.png"));
		m_pObject[nCnt]->SetLength(200.0f, 75.0f);
		m_pObject[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}

	m_pObject[2]->SetPosition(D3DXVECTOR3(300.0f, 100.0f, 0.0f));
	m_pObject[2]->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\ranking_one00.png"));
	m_pObject[2]->SetLength(250.0f, 100.0f);

	m_pObject[3]->SetPosition(D3DXVECTOR3(1000.0f, 100.0f, 0.0f));
	m_pObject[3]->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\ranking_team00.png"));
	m_pObject[3]->SetLength(250.0f, 100.0f);

	//�l
	// �f�[�^�̓ǂݍ���
	Load(&aScore[0], RANKING_FILE_ONE);

	// �f�[�^�̃\�[�g
	Sort(&aScore[0]);

	// �����N�C���m�F
	RankIn(&aScore[0], m_nScore, RANKING_FILE_ONE, 0);

	if (m_bOne == true)
	{
		m_pObject[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	//���v
	// �f�[�^�̓ǂݍ���
	Load(&aTotalScore[0], RANKING_FILE_TEAM);

	// �f�[�^�̃\�[�g
	Sort(&aTotalScore[0]);

	// �����N�C���m�F
	RankIn(&aTotalScore[0], m_nTotalScore, RANKING_FILE_TEAM, 1);
	
	if (m_bTotal == true)
	{
		m_pObject[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	//����̃X�R�A
	for (int nCnt = 0; nCnt < NUM_NOWSCORE; nCnt++)
	{
		m_apNowScore[nCnt] = CScore::Create(D3DXVECTOR3(300.0f + nCnt * 600.0f, 200.0f, 0.0f), 15.0f, 25.0f);
	}

	m_apNowScore[0]->SetScore(m_nScore);
	m_apNowScore[1]->SetScore(m_nTotalScore);

	for (int nCntRanking = 0; nCntRanking < NUM_RANKING; nCntRanking++)
	{
		for (int nCntRank = 0; nCntRank < NUM_RANK; nCntRank++)
		{
			m_apScore[nCntRanking][nCntRank] = CScore::Create(D3DXVECTOR3(300.0f + nCntRanking * 600.0f, 400.0f + nCntRank * 100.0f, 0.0f), 15.0f, 25.0f);
		}
	}

	for (int nCntRank = 0; nCntRank < NUM_RANK; nCntRank++)
	{
		m_apScore[0][nCntRank]->SetScore(aScore[nCntRank]);
		m_apScore[1][nCntRank]->SetScore(aTotalScore[nCntRank]);
	}

	if (m_nRank != -1)
	{
		m_apScore[0][m_nOne]->SetClo(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		m_apScore[1][m_nTotal]->SetClo(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}

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
	CMeshDome::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 6000.0f, 6000.0f, 3, 8, 8);

	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_RANKING);

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CRanking::Uninit(void)
{
	m_nScore = 0;
	m_nTotalScore = 0;

	for (int nCntRanking = 0; nCntRanking < NUM_RANKING; nCntRanking++)
	{
		for (int nCntRank = 0; nCntRank < NUM_RANK; nCntRank++)
		{
			m_apScore[nCntRanking][nCntRank]->Uninit();
		}
	}

	for (int nCntRanking = 0; nCntRanking < NUM_RANKING; nCntRanking++)
	{
		for (int nCnt = 0; nCnt < NUM_RANK; nCnt++)
		{
			m_pObjectRank[nCntRanking][nCnt]->Uninit();
		}
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_apNowScore[nCnt]->Uninit();
	}

	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		m_pObject[nCnt]->Uninit();
	}

}

//===============================================
// �X�V����
//===============================================
void CRanking::Update(void)
{
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();

	//�T�C�Y�̐ݒ�
	for (int nCntRanking = 0; nCntRanking < NUM_RANKING; nCntRanking++)
	{
		for (int nCnt = 0; nCnt < NUM_RANK; nCnt++)
		{
			// ���_���̐ݒ�
			m_pObjectRank[nCntRanking][nCnt]->SetVtx();
			m_pObjectRank[nCntRanking][nCnt]->SetVtx(nCnt, NUM_RANK, 1);
		}
	}

	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		// ���_���̐ݒ�
		m_pObject[nCnt]->SetVtx();	

		if (nCnt >= 4)
		{
			m_pObject[nCnt]->SetVtx(0, NUM_RANK, 1);
		}
	}

		D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 pos1 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		
		pos.x = ((float)(rand() % 8000 - 4000) * 0.01f)* ((float)(rand() % 100)) * 0.6f;
		pos1.x = ((float)(rand() % 8000 - 4000) * 0.01f)* ((float)(rand() % 100)) * 0.6f;

		pos.z = ((float)(rand() % 2000 - 1000) * 0.01f)* ((float)(rand() % 100)) * 0.6f;
		pos1.z = ((float)(rand() % 2000 - 1000) * 0.01f)* ((float)(rand() % 100)) * 0.6f;

		CItem::Create(D3DXVECTOR3(pos.x , 1500.0f, pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\coin.x", CItem::TYPE_COIN, CItem::STATE_DOWN);
		CItem::Create(D3DXVECTOR3(pos1.x, 1500.0f, pos1.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\coin.x", CItem::TYPE_COIN, CItem::STATE_DOWN);

	if (CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_RETURN) || pInputPad->GetTrigger(CInputPad::BUTTON_START, 0))
	{
		CManager::GetInstance()->GetFade()->Set(CScene::MODE_TITLE);
	}

	if (CManager::GetInstance()->GetFade()->GetState() == CFade::STATE_NONE)
	{
		m_nTimer++;

		if (m_nTimer >= AUTOMOVE_TITLE)
		{// �^�C�g�������J�ڋK��l
			CManager::GetInstance()->GetFade()->Set(CScene::MODE_TITLE);
		}
	}

	CScene::Update();
}

//===============================================
// �`�揈��
//===============================================
void CRanking::Draw(void)
{
	CScene::Draw();
}

//===============================================
// �����L���O�f�[�^�ۑ�
//===============================================
void CRanking::Save(int *pScore, const char *pFileName)
{
	FILE *pFile;

	pFile = fopen(pFileName, "wb");

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
void CRanking::Load(int *pScore, const char *pFileName)
{
	FILE *pFile;

	pFile = fopen(pFileName, "rb");

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
			pScore[nCntRanking] = 5 - (nCntRanking * 5);
		}
	}
}

//===============================================
// �����L���O�f�[�^�\�[�g
//===============================================
void CRanking::Sort(int *pScore)
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
void CRanking::RankIn(int *pScore, int nResult, const char *pFileName, int nNew)
{
	if (nResult > pScore[NUM_RANK - 1])
	{
		pScore[NUM_RANK - 1] = nResult;

		// �\�[�g����
		Sort(pScore);

		// �ۑ�����
		Save(pScore, pFileName);

		//�����N�C���������ʂ��m�F����
		for (int nCntRank = 0; nCntRank < NUM_RANK; nCntRank++)
		{
			if (pScore[nCntRank] == nResult)
			{
				m_nRank = nCntRank;	// �����N�C���������ʂ�ۑ�		

				if (nNew == 0)
				{
					if (m_nRank == 0)
					{
						m_bOne = true;
					}
					if (m_nRank != -1)
					{
						m_nOne = m_nRank;
					}
				}
				else if (nNew == 1)
				{
					if (m_nRank == 0)
					{
						m_bTotal = true;
					}
					if (m_nRank != -1)
					{
						m_nTotal = m_nRank;
					}

				}

				break;
			}
		}
	}
}