//===============================================
//
// �����L���O��ʂ̊Ǘ����� [ranking.h]
// Author : Ibuki Okusada
//
//===============================================
#ifndef _RANKING_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _RANKING_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "manager.h"

//===============================================
// �}�N����`
//===============================================
#define NUM_RANK	(3)		// �����L���O�̏��ʐ�
#define NUM_RANKING (2)     // �\�����郉���L���O�̐�
#define MAX_RANKING (4)
#define NUM_NOWSCORE (2)	//�X�R�A

// �O���錾
class CScore;
class CFileLoad;
class CCarManager;
class CNumber;
class CObject2D;

//===============================================
// �����L���O�N���X�̒�`(�h���N���X)
//===============================================
class CRanking : public CScene
{
public:

	enum TYPE
	{
		TYPE_ONE = 0,	// ����
		TYPE_TEAM,		// �V�L�^
		TYPE_MAX
	};

	// �����o�֐�
	CRanking();		// �R���X�g���N�^
	~CRanking();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void SetScore(int nValue) { m_nScore = nValue; }
	static void SetTotalScore(int nValue) { m_nTotalScore = nValue; }

private:

	// �����o�֐�
	void Save(int *pScore, const char *pFileName);
	void Load(int *pScore, const char *pFileName);
	void Sort(int *pScore);
	void RankIn(int *pScore, int nResult, const char *pFileName, int nNew);

	// �����o�ϐ�
	CFileLoad *m_pFileLoad;	// �t�@�C���ǂݍ��݂̃|�C���^
	static CScore *m_apScore[NUM_RANKING][NUM_RANK];	// �X�R�A�̃|�C���^(���ʕ�)
	static CScore *m_apNowScore[NUM_NOWSCORE];			// �X�R�A�̃|�C���^(�l�A�`�[��)
	static int m_nScore;		// ����̃X�R�A
	static int m_nTotalScore;	// ����̃X�R�A
	int m_nTimer;				// �����J�ڃ^�C�}�[
	int m_nRank;
	CCarManager *m_pCarManager;		// �J�[�}�l�[�W���[�̃|�C���^
	int m_nCounter;
	CObject2D *m_pObjectRank[NUM_RANKING][NUM_RANK];
	CObject2D *m_pObject[MAX_RANKING];
	const static char *m_apFileName[TYPE_MAX];	// �����ǂݍ��݃t�@�C����

	bool m_bOne;	//�g�b�v�ɂȂ�����
	bool m_bTotal;	//�g�b�v�ɂȂ�����
	int m_nOne;	//�g�b�v�ɂȂ�����
	int m_nTotal;	//�g�b�v�ɂȂ�����
};

#endif