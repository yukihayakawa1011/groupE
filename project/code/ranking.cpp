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

//===============================================
// �}�N����`
//===============================================
#define RANKING_FILE	"data\\FILE\\ranking.bin"	// �����L���O�t�@�C��
#define AUTOMOVE_TITLE	(600)						// �^�C�g�������J�ڃ^�C�}�[

//===============================================
// �ÓI�����o�ϐ�
//===============================================
CScore *CRanking::m_apScore[NUM_RANK] = {};	// �����L���O�̃|�C���^
CNumber *CRanking::m_apNumber[NUM_RANK][NUM_SCORE] = {}; // �\�����錅��
int CRanking::m_nScore = 0;					// �X�R�A

//===============================================
// �R���X�g���N�^
//===============================================
CRanking::CRanking()
{
	// �l���N���A����
	m_nTimer = 0;
	m_nRank = 0;
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
	m_nRank = -1;	//�����N�C�����ĂȂ����

	// �f�[�^�̓ǂݍ���
	Load(&aScore[0]);

	// �f�[�^�̃\�[�g
	Sort(&aScore[0]);

	// �����N�C���m�F
	RankIn(&aScore[0], m_nScore);

	for (int nCntRank = 0; nCntRank < NUM_RANK; nCntRank++)
	{
		for (int nCntScore = 0; nCntScore < NUM_SCORE; nCntScore++)
		{
			m_apNumber[nCntRank][nCntScore] = CNumber::Create(D3DXVECTOR3(500.0f + nCntScore * 50.0f, 180.0f + nCntRank * 70.0f, 0.0f), 30.0f, 30.0f);
		}
	}

	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_RANKING);

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CRanking::Uninit(void)
{
	m_nScore = 0;

	for (int nCntRank = 0; nCntRank < NUM_RANK; nCntRank++)
	{
		for (int nCntScore = 0; nCntScore < NUM_SCORE; nCntScore++)
		{
			m_apNumber[nCntRank][nCntScore]->Uninit();

			m_apNumber[nCntRank][nCntScore] = nullptr;
		}
	}
}

//===============================================
// �X�V����
//===============================================
void CRanking::Update(void)
{
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();

	if (CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_RETURN) || pInputPad->GetTrigger(CInputPad::BUTTON_A, 0))
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
void CRanking::Save(int *pScore)
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
void CRanking::Load(int *pScore)
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
			pScore[nCntRanking] = 40000 - (nCntRanking * 5000);
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
void CRanking::RankIn(int *pScore, int nResult)
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