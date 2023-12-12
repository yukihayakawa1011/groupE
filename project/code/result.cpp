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
	const float PLAYER_MOVESIZE = (100.0f);	// �v���C���[�̉��ړ��T�C�Y
	const float PLAYER_SPACE = (200.0f);	// �v���C���[���m�̊Ԃ̋���
	const float PLAYER_POSY = (2000.0f);	// �v���C���[�z�u��{Y���W
	const float PLAYER_RANK_POSY = (-350.0f);	// �v���C���[�̏��ʂ��Ƃɏグ��Y���W
	const float PLAYER_UPPOSY = (300.0f);	// �ő�l���ɂ���ĕς��v���C���[�̐ݒuY���W
	const float PLAYER_RANKMOVEPOS_Y = (900.0f);	// �����N�ƃX�R�A�����Ă���m�FY���W
	const float CAMERA_MOVESTARTPOSY = (1400.0f);	// �J���������n��Y���W
	const float PLAYER_GRAVITY = (-15.0f);	// �v���C���[�̗������x
	const float RANK_DOWNSPEED = (20.0f);	// �����N�ƃX�R�A�̗������x
	const D3DXVECTOR3 TOTALSCORE_POS = {SCREEN_WIDTH * 0.375f, SCREEN_HEIGHT * 0.9f, 0.0f};	// ���v�X�R�A�̐ݒu���W
	const D3DXVECTOR3 SCORE_POS = {SCREEN_WIDTH * 0.425f, -SCREEN_HEIGHT * 1.4f, 0.0f};		// ���v�X�R�A�̐ݒu���W
	const float SCORE_MOVESIZE = (130.0f);	// �X�R�A�̔z�u�ړ��T�C�Y
	const float SCORE_SPACE = (270.0f);		// �X�R�A�Ԃ̋��
	const D3DXVECTOR3 RANK_POS = { SCREEN_WIDTH * 0.5f, -SCREEN_HEIGHT * 1.3f, 0.0f };		// ���v�X�R�A�̐ݒu���W
	const float RANK_MOVESIZE = (135.0f);	// �����N�̔z�u�ړ��T�C�Y
	const float RANK_SPACE = (270.0f);		// �����N�Ԃ̋��
	const D3DXVECTOR2 RANK_SIZE = { 50.0f, 30.0f };	// �����N�|���S���T�C�Y
	const D3DXVECTOR3 CLEAR_SETPOS = { -SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.9f, 0.0f};	// clear�̔z�u���W
	const D3DXVECTOR2 CLEAR_SIZE = {500.0f, 100.0f };	// �N���A�̃T�C�Y
	const D3DXVECTOR3 CLEAR_POS = { SCREEN_WIDTH * 0.35f, SCREEN_HEIGHT * 0.9f, 0.0f };	// clear�̔z�u���W
	const float SCORE_MOVEX = (SCREEN_WIDTH * 0.2f);
	const float FAILED_ROTATE = (D3DX_PI * 0.125f);
	const float CLEAR_MOVE = (20.0f);
	const float CLEAR_ROTMOVEZ = (D3DX_PI * 0.015f);
	const float FAILED_UPY = (-2.5f);
	const float FAILED_NOBINOBISPEED = (0.025f);
	const float FAILED_NOBINOBISIZE = (10.0f);
	const float CLEAR_NOBINOBISPEED = (0.075f);	// �N���A�����ۂ̐L�яk�݂��鑬�x
	const float CLEAR_NOBINOBISIZE = (50.0f);	// �L�т�{��
	const int PLAYER_MAXMOTION = (13);			// �v���C���[�̍ő僂�[�V������
	const int SCORE_MINTORURURURU = (60);		// �Ƃ���Ƃ���̍����Œ�l
	const int SCORE_TORURURUSPEED = (13);		// �Ƃ���Ƃ���̍����␳���x
	const D3DXCOLOR CLEAR_COL = { 0.0f, 0.0f, 1.0f, 1.0f };
	const D3DXCOLOR FAILED_COL = { 1.0f, 0.0f, 0.0f, 1.0f };
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
	m_ppRank = nullptr;
	m_nWorst = 0;
	m_nNowScore = 0;
	m_nTotalScore = 0;
	m_pObjClear = nullptr;
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

	m_apScore = new CScore*[m_nNumPlayer];

	for (int nCount = 0; nCount < m_nNumPlayer; nCount++)
	{
		m_apScore[nCount] = CScore::Create(D3DXVECTOR3(SCORE_POS.x + (-((m_nNumPlayer - 1) * SCORE_MOVESIZE) + nCount * SCORE_SPACE), SCORE_POS.y, 0.0f), 6, 0.75f, 15.0f, 20.0f);
		m_apScore[nCount]->SetScore(m_pScore[nCount]);
	}

	SetTopScore(m_pScore);

	if (m_pRank == nullptr && m_nNumPlayer > 0) {
		m_pRank = new int[m_nNumPlayer];
	}

	// ���ꂼ��̃����N�t��
	SetRank(m_nNumPlayer);

	// �l�����|�C���^����
	m_ppRank = new CObject2D*[m_nNumPlayer];

	// �����N�̃|���S������
	for (int nCnt = 0; nCnt < m_nNumPlayer; nCnt++) {
		m_ppRank[nCnt] = CObject2D::Create(NUM_PRIORITY);
		m_ppRank[nCnt]->BindTexture(CTexture::TYPE_RESULTRANK);
		m_ppRank[nCnt]->SetPosition(D3DXVECTOR3(RANK_POS.x + (-((m_nNumPlayer - 1) * RANK_MOVESIZE) + nCnt * RANK_SPACE), RANK_POS.y, 0.0f));
		m_ppRank[nCnt]->SetSize(RANK_SIZE.x, RANK_SIZE.y);
		m_ppRank[nCnt]->SetVtx(m_pRank[nCnt], PLAYER_MAX, 1);

		if (m_pRank[nCnt] > m_nWorst)
		{
			m_nWorst = m_pRank[nCnt];
		}
	}

	//�J����������
	{
		CManager::GetInstance()->GetCamera()->SetPositionR(D3DXVECTOR3(0.0f, 137.77f, -301.94f));
		CManager::GetInstance()->GetCamera()->SetRotation(D3DXVECTOR3(1.0f, -D3DX_PI * 0.5f, 2.63f));
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

	// �l�����|�C���^����
	m_ppPlayer = new CPlayer*[m_nNumPlayer];

	for (int nCnt = 0; nCnt < m_nNumPlayer; nCnt++)
	{
		char aBodyPass[200] = "";		// ���̃p�X
		char aLegPass[200] = "";		// �����g�p�X

		sprintf(&aBodyPass[0], "data\\TXT\\Player%d\\motion_ninjabody.txt", nCnt);
		sprintf(&aLegPass[0], "data\\TXT\\Player%d\\motion_ninjaleg.txt", nCnt);

		m_ppPlayer[nCnt] = CPlayer::Create(D3DXVECTOR3(-((m_nNumPlayer - 1) * PLAYER_MOVESIZE) + nCnt * PLAYER_SPACE, PLAYER_POSY + m_pRank[nCnt] * PLAYER_RANK_POSY + PLAYER_UPPOSY * m_nNumPlayer, 60.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), &aBodyPass[0], &aLegPass[0]);
		m_ppPlayer[nCnt]->BindId(nCnt);
		m_ppPlayer[nCnt]->SetType(CPlayer::TYPE_NONE);
	}


	// ���v�X�R�A�̎擾
	m_nTotalScore = SumScore();

	m_pTotalScore = CScore::Create(TOTALSCORE_POS, 8, 0.75f, 25.0f, 45.0f);
	m_pTotalScore->SetScore(m_nNowScore);
	CRanking::SetTotalScore(m_nTotalScore);

	// 
	CManager::GetInstance()->GetCamera()->Update();
	CManager::GetInstance()->GetCamera()->SetActive(false);
	//CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_RANKING);

	if (m_ppPlayer == nullptr) {
		return S_OK;
	}

	for (int nCnt = 0; nCnt < m_nNumPlayer; nCnt++)
	{
		if (m_ppPlayer[nCnt] == nullptr) {
			continue;
		}

		if (m_nTotalScore < m_nQuota || m_pScore[nCnt] <= 0) {	// �m���}��B�����Ă��Ȃ�
			m_ppPlayer[nCnt]->SetMotion(PLAYER_MAXMOTION);
		}
		else {
			m_ppPlayer[nCnt]->SetMotion(PLAYER_MAXMOTION - 1);
		}
	}

	// �B���������m�F����
	if (m_nTotalScore >= m_nQuota) {	// �m���}�B��
		m_bClear = true;
	}

	// �m���}�B���̃|���S���ݒ�
	m_pObjClear = CObject2D::Create(NUM_PRIORITY - 1);

	// clear���ƂɃe�N�X�`���ύX
	if (m_pObjClear != nullptr) {
		switch (m_bClear) {
		case false:
			CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_RESULT_FAILED);
			m_pObjClear->BindTexture(CTexture::TYPE_RESULTFAILED);

			break;
		case true:
			CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_RESULT_CLEAR);
			m_pObjClear->BindTexture(CTexture::TYPE_RESULTCLEAR);
			break;
		}
	}

	// ���W�ƃT�C�Y�ݒ�
	if (m_pObjClear != nullptr) {
		m_pObjClear->SetPosition(CLEAR_SETPOS);
		m_pObjClear->SetLength(CLEAR_SIZE.x, CLEAR_SIZE.y);
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

	if (m_ppRank != nullptr) { // �g�p���Ă����ꍇ
		for (int nCnt = 0; nCnt < m_nNumPlayer; nCnt++)
		{
			// �I������
			m_ppRank[nCnt]->Uninit();
			m_ppRank[nCnt] = nullptr;	// �g�p���Ă��Ȃ���Ԃɂ���
		}

		delete[] m_ppRank;	// �|�C���^�̊J��
		m_ppRank = nullptr;	// �g�p���Ă��Ȃ���Ԃɂ���
	}
	
	if (m_pRank != nullptr)
	{
		delete[] m_pRank;
		m_pRank = nullptr;
	}

	if (m_pTotalScore != nullptr) {
		m_pTotalScore->Uninit();
		delete m_pTotalScore;
		m_pTotalScore = nullptr;
	}

	m_type = TYPE_MAX;

	if (m_pScore != nullptr) {
		delete[] m_pScore;
		m_pScore = nullptr;
	}

	if (m_pFileLoad != nullptr)
	{
		m_pFileLoad->Uninit();

		delete m_pFileLoad;		// �������̊J��
		m_pFileLoad = nullptr;
	}

	CManager::GetInstance()->GetCamera()->SetActive(true);
	m_nNumPlayer = 0;
}

//===============================================
// �X�V����
//===============================================
void CResult::Update(void)
{
	int nLandPlayer = 0;	// ���n�v���C���[��
	bool bCamera = false;

	if (m_nNowScore < m_nTotalScore) {	// �����X�R�A�ɕ\���X�R�A�����B���Ă��Ȃ�

		if (m_nTotalScore - m_nNowScore > SCORE_MINTORURURURU) {	// �␳���邽�߂ɕK�v�ȍ���������
			m_nNowScore += static_cast <int>(static_cast <float>(m_nTotalScore - m_nNowScore) * 0.015f) + SCORE_TORURURUSPEED;
		}
		else {	// ����
			m_nNowScore += SCORE_TORURURUSPEED;
		}

		// �\���̐��l��ύX
		if (m_nNowScore >= m_nTotalScore) {	// ���B����
			m_nNowScore = m_nTotalScore;

			if (m_pTotalScore != nullptr) {
				if (m_bClear) {
					m_pTotalScore->SetClo(CLEAR_COL);
				}
				else {
					m_pTotalScore->SetClo(FAILED_COL);
				}
			}
		}
		if (m_pTotalScore != nullptr) {	// �g�p���Ă���
			m_pTotalScore->SetScore(m_nNowScore);
		}

		CScene::Update();
		if (m_nNumPlayer > 0) {
			return;
		}
	}

	// �m���}�������s�X�V
	if (m_pObjClear != nullptr) {
		D3DXVECTOR3 pos = m_pObjClear->GetPosition();
		D3DXVECTOR2 size = CLEAR_SIZE;
		D3DXVECTOR3 rot = m_pObjClear->GetRotation();

		// �܂����W���K��l�ɒB���Ă��Ȃ�
		if (pos.x < CLEAR_POS.x) {
			pos.x += CLEAR_MOVE;

			if (m_pTotalScore != nullptr) {	// ���v�X�R�A���g�p����Ă���
				if (pos.x >= SCORE_MOVEX) {	// �X�R�A���ړ����n�߂�
					// �ړ�
					D3DXVECTOR3 ScorePos = m_pTotalScore->GetPosition();
					ScorePos.x += CLEAR_MOVE;
					m_pTotalScore->SetPosition(ScorePos);
				}
			}

			if (pos.x > CLEAR_POS.x) {	// ��������
				pos.x = CLEAR_POS.x;	// �␳
			}
		}
		else {

			// ��]
			if (!m_bClear) {	// ���s�����ꍇ
				if (rot.z < FAILED_ROTATE) {
					rot.z += CLEAR_ROTMOVEZ;
					pos.y += FAILED_UPY;
				}
				else {
					m_ClearHeight += FAILED_NOBINOBISPEED;
					float fSin = sinf(m_ClearHeight);
					size.x = CLEAR_SIZE.x - fSin * FAILED_NOBINOBISIZE;
					size.y = CLEAR_SIZE.y + fSin * FAILED_NOBINOBISIZE;
				}
			}
			else {	// ����
				m_ClearHeight += CLEAR_NOBINOBISPEED;
				float fSin = sinf(m_ClearHeight);
				if (fSin < 0.0f) {
					fSin = 0.0f;
				}
				pos.y = CLEAR_POS.y - fSin * CLEAR_NOBINOBISIZE;
				size.y = CLEAR_SIZE.y + fSin * CLEAR_NOBINOBISIZE;
			}
		}

		m_pObjClear->SetRotation(rot);
		m_pObjClear->SetPosition(pos);
		m_pObjClear->SetLength(size.x, size.y);
	}

	// �v���C���[�̍X�V
	for (int nCnt = 0; nCnt < m_nNumPlayer; nCnt++)
	{
		if (m_ppPlayer == nullptr) {
			break;
		}

		if (m_ppPlayer[nCnt] == nullptr) {
			continue;
		}

		D3DXVECTOR3 pos = m_ppPlayer[nCnt]->GetPosition();

		if (pos.y <= CAMERA_MOVESTARTPOSY && pos.y > PLAYER_RANKMOVEPOS_Y) {	// ���W��ݒ�

			if (m_pRank == nullptr) {
				continue;
			}

			if (m_pRank[nCnt] == m_nWorst) {

				if (!bCamera) {
					CCamera *pCamera = CManager::GetInstance()->GetCamera();
					D3DXVECTOR3 rot = pCamera->GetRotation();
					rot.z -= 0.03f;
					pCamera->SetRotation(rot);
					bCamera = true;
				}
			}
		}
		else if (pos.y <= PLAYER_RANKMOVEPOS_Y && pos.y > 0.0f) {	// ���W��ݒ�
			if (m_ppRank != nullptr) {
				if (m_ppRank[nCnt] != nullptr) {
					D3DXVECTOR3 RankPos = m_ppRank[nCnt]->GetPosition();
					RankPos.y += RANK_DOWNSPEED;
					m_ppRank[nCnt]->SetPosition(RankPos);
					m_ppRank[nCnt]->SetSize(RANK_SIZE.x, RANK_SIZE.y);
				}
			}

			if (m_apScore != nullptr) {
				if (m_apScore[nCnt] != nullptr) {
					D3DXVECTOR3 RankPos = m_apScore[nCnt]->GetPosition();
					RankPos.y += RANK_DOWNSPEED;
					m_apScore[nCnt]->SetPosition(RankPos);
				}
			}
		}
		else if (pos.y == 0.0f) {	// ���n�ς�
			nLandPlayer++;
			continue;
		}

		// �d�͂𔽉f
		pos.y += PLAYER_GRAVITY;

		if (pos.y <= 0.0f) {	// �n�ʂɖ��܂���
			pos.y = 0.0f;
			m_ppPlayer[nCnt]->SetMotion(m_ppPlayer[nCnt]->GetMotion() - 2);
		}

		m_ppPlayer[nCnt]->SetPosition(pos);
	}

	if (nLandPlayer >= m_nNumPlayer) {	// �S�����n����
		m_nTimer++;

		if (m_nTimer >= MOVE_TIMER ||
			CManager::GetInstance()->GetInputPad()->GetTrigger(CInputPad::BUTTON_A, 0) ||
			CManager::GetInstance()->GetInputPad()->GetTrigger(CInputPad::BUTTON_START, 0))
		{
			CManager::GetInstance()->GetFade()->Set(CScene::MODE_RANKING);
			m_nTimer = 0;
		}
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
	if (ppPlayer == nullptr) {
		return;
	}

	CPlayer *pPlayer = CPlayer::GetTop();
	int nNumGoal = 0;

	m_pScore = new int [m_nNumPlayer];

	for (int i = 0; i < m_nNumPlayer; i++)
	{
		if (ppPlayer[i] == nullptr) {
			continue;
		}
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
