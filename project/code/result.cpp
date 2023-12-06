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
#include "score.h"
#include "player.h"
#include "ranking.h"
#include "object_manager.h"

// �}�N����`
#define RANKING_FILE	"data\\FILE\\ranking.bin"	// �����L���O�t�@�C��
#define MOVE_TIMER	(660)

// �������O���
namespace {
	const D3DXVECTOR3 TOTALSCORE_POS = {SCREEN_WIDTH * 0.425f, SCREEN_HEIGHT * 0.8f, 0.0f};	// ���v�X�R�A�̐ݒu���W
	const float SCORE_MOVESIZE = (100.0f);
	const float SCORE_SPACE = (100.0f);
	const D3DXVECTOR3 RANK_POS = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.4f, 0.0f };	// ���v�X�R�A�̐ݒu���W
	const float X_RANKSPACE = (100.0f);
	const D3DXVECTOR2 RANK_SIZE = { 50.0f, 30.0f };
	const int PLAYER_MAXMOTION = (13);
}

// �ÓI�����o�ϐ�
int *CResult::m_pScore = 0;
int CResult::m_nTopScore = 0;
CResult::TYPE CResult::m_type = CResult::TYPE_MAX;
int CResult::m_nNumPlayer = 0;
int CResult::m_nQuota = 0;
CPlayer **CResult::m_ppPlayer = nullptr;
CScore **CResult::m_apScore = nullptr;

//===============================================
// �R���X�g���N�^
//===============================================
CResult::CResult()
{
	m_pMeshSky = NULL;
	m_nTimer = 0;
	m_pTime = NULL;
	m_pTotalScore = nullptr;
	m_pRank = nullptr;
	m_bClear = false;
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

	// �l�����|�C���^����
	m_ppPlayer = new CPlayer*[m_nNumPlayer];

	for (int nCnt = 0; nCnt < m_nNumPlayer; nCnt++)
	{
		char aBodyPass[200] = "";		// ���̃p�X
		char aLegPass[200] = "";		// �����g�p�X

		sprintf(&aBodyPass[0], "data\\TXT\\Player%d\\motion_ninjabody.txt", nCnt);
		sprintf(&aLegPass[0], "data\\TXT\\Player%d\\motion_ninjaleg.txt", nCnt);

		m_ppPlayer[nCnt] = CPlayer::Create(D3DXVECTOR3(-((m_nNumPlayer - 1) * 100.0f) + nCnt * 200.0f, 0.0f, 60.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), &aBodyPass[0], &aLegPass[0]);
		m_ppPlayer[nCnt]->BindId(nCnt);
		m_ppPlayer[nCnt]->SetType(CPlayer::TYPE_NONE);
	}

	m_apScore = new CScore*[m_nNumPlayer];

	for (int nCount = 0; nCount < m_nNumPlayer; nCount++)
	{
		m_apScore[nCount] = CScore::Create(D3DXVECTOR3(-((m_nNumPlayer - 1) * SCORE_MOVESIZE) + nCount * SCORE_SPACE, 180.0f, 0.0f), 15.0f, 15.0f);
		m_apScore[nCount]->SetScore(m_pScore[nCount]);

	}

	SetTopScore(m_pScore);

	if (m_pRank == nullptr && m_nNumPlayer > 0) {
		m_pRank = new int[m_nNumPlayer];
	}

	// ���ꂼ��̃����N�t��
	SetRank(m_nNumPlayer);

	// �����N�̃|���S������
	for (int nCnt = 0; nCnt < m_nNumPlayer; nCnt++) {
		CObject2D *pObj = CObject2D::Create(NUM_PRIORITY);
		pObj->BindTexture(CTexture::TYPE_RESULTRANK);
		pObj->SetPosition(D3DXVECTOR3(RANK_POS.x + nCnt * X_RANKSPACE, RANK_POS.y, RANK_POS.z));
		pObj->SetSize(RANK_SIZE.x, RANK_SIZE.y);
		pObj->SetVtx(m_pRank[nCnt], PLAYER_MAX, 1);
	}

	//�J����������
	{
		CManager::GetInstance()->GetCamera()->SetPositionR(D3DXVECTOR3(0.0f, 137.77f, -381.94f));
		//CManager::GetInstance()->GetCamera()->SetPositionR(D3DXVECTOR3(205.0f, 92.42f, -89.13f));
		CManager::GetInstance()->GetCamera()->SetRotation(D3DXVECTOR3(1.0f, -D3DX_PI * 0.5f, 1.63f));
		CManager::GetInstance()->GetCamera()->SetLength(300.0f);

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

	// ���v�X�R�A�̎擾
	int nTotalScore = SumScore();

	m_pTotalScore = CScore::Create(TOTALSCORE_POS, 15.0f, 15.0f);
	m_pTotalScore->SetScore(nTotalScore);
	CRanking::SetTotalScore(nTotalScore);

	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_RANKING);

	if (m_ppPlayer == nullptr) {
		return S_OK;
	}

	for (int nCnt = 0; nCnt < m_nNumPlayer; nCnt++)
	{
		if (m_ppPlayer[nCnt] == nullptr) {
			continue;
		}

		if (nTotalScore < m_nQuota) {	// �m���}��B�����Ă��Ȃ�
			m_ppPlayer[nCnt]->SetMotion(PLAYER_MAXMOTION - 2);
		}
		else {
			m_ppPlayer[nCnt]->SetMotion(PLAYER_MAXMOTION - 1);
		}
	}

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CResult::Uninit(void)
{
	if (m_apScore != nullptr) {
		for (int nCnt = 0; nCnt < m_nNumPlayer; nCnt++) {
			if (m_apScore[nCnt] != nullptr) {// �g�p����Ă���ꍇ

				// �I������
				m_apScore[nCnt]->Uninit();

				// �j��
				delete m_apScore[nCnt];

				// �g�p���Ă��Ȃ���Ԃɂ���
				m_apScore[nCnt] = nullptr;
			}
		}
		delete[] m_apScore;	// �|�C���^�̊J��
		m_apScore = nullptr;	// �g�p���Ă��Ȃ���Ԃɂ���
	}

	if (m_ppPlayer != nullptr) { // �g�p���Ă����ꍇ
		for (int nCnt = 0; nCnt < m_nNumPlayer; nCnt++)
		{
			// �I������
			m_ppPlayer[nCnt]->Uninit();
			m_ppPlayer[nCnt] = nullptr;	// �g�p���Ă��Ȃ���Ԃɂ���
		}

		delete[] m_ppPlayer;	// �|�C���^�̊J��
		m_ppPlayer = nullptr;	// �g�p���Ă��Ȃ���Ԃɂ���
	}

	m_type = TYPE_MAX;

	if (m_pScore != nullptr) {
		delete[] m_pScore;
		m_pScore = nullptr;
	}

	m_nNumPlayer = 0;
}

//===============================================
// �X�V����
//===============================================
void CResult::Update(void)
{
	m_nTimer++;

	if (/*CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_RETURN) || m_nTimer > MOVE_TIMER 
		||*/ CManager::GetInstance()->GetInputPad()->GetTrigger(CInputPad::BUTTON_A, 0) || CManager::GetInstance()->GetInputPad()->GetTrigger(CInputPad::BUTTON_START, 0))
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
// �X�R�A�ݒ菈��
//===============================================
void CResult::SetScore(CPlayer **ppPlayer)
{
	CPlayer *pPlayer = CPlayer::GetTop();
	int nNumGoal = 0;

	m_pScore = new int [m_nNumPlayer];

	for (int i = 0; i < m_nNumPlayer; i++)
	{
		if (ppPlayer[i]->GetGoal())
		{
			m_pScore[i] = ppPlayer[i]->GetScore()->GetScore();
		}
		else
		{
			m_pScore[i] = 0;
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
// �S���̃X�R�A����
//===============================================
int CResult::SumScore(void)
{
	int nSumScore = 0;

	for (int i = 0; i < m_nNumPlayer; i++)
	{
		nSumScore += m_pScore[i];
	}

	return nSumScore;
}

//===============================================
// �N����ʂȂ̂����߂�
//===============================================
void CResult::SetTopScore(int * pScore)
{
	int nTopScore = 0;

	for (int nCount = 0; nCount < m_nNumPlayer; nCount++)
	{
		if(nTopScore < pScore[nCount])
		{
			nTopScore = pScore[nCount];
		}
	}

	CRanking::SetScore(nTopScore);
}

//===============================================
// ���ꂼ��̃����N�t��
//===============================================
void CResult::SetRank(int nNum)
{
	if (m_apScore == nullptr) {	// �X�R�A���݂��Ă��Ȃ�
		return;
	}

	int *pScore = new int[nNum];

	for (int nCount = 0; nCount < m_nNumPlayer; nCount++)
	{
		pScore[nCount] = m_pScore[nCount];
	}

	// �~���\�[�g
	for (int nCntFst = 0; nCntFst < m_nNumPlayer - 1; nCntFst++)
	{
		int nTempNum = nCntFst;	// ���̈�ԑ傫���ԍ�

		for (int nCntSec = nCntFst + 1; nCntSec < m_nNumPlayer; nCntSec++)
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

	// �����N�t��
	for (int nCntFst = 0; nCntFst < m_nNumPlayer; nCntFst++)
	{
		for (int nCntSec = 0; nCntSec < m_nNumPlayer; nCntSec++)
		{
			if (m_pScore[nCntFst] == pScore[nCntSec])
			{// �l���傫���ꍇ
				m_pRank[nCntFst] = nCntSec;
				break;
			}
		}
	}

	if (pScore != nullptr) {
		delete[] pScore;
		pScore = nullptr;
	}

}
