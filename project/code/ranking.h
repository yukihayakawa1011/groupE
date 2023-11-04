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
#define NUM_RANK	(5)		// �����L���O�̏��ʐ�

// �O���錾
class CScore;
class CFileLoad;
class CCarManager;

//===============================================
// �����L���O�N���X�̒�`(�h���N���X)
//===============================================
class CRanking : public CScene
{
public:

	// �����o�֐�
	CRanking();		// �R���X�g���N�^
	~CRanking();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void SetScore(int nValue) { m_nScore = nValue; }

private:

	// �����o�֐�
	void Save(int *pScore);
	void Load(int *pScore);
	void Sort(int *pScore);
	void RankIn(int *pScore, int nResult);

	// �����o�ϐ�
	CFileLoad *m_pFileLoad;	// �t�@�C���ǂݍ��݂̃|�C���^
	static CScore *m_apScore[NUM_RANK];	// �X�R�A�̃|�C���^(���ʕ�)
	static int m_nScore;	// ����̃X�R�A
	int m_nTimer;			// �����J�ڃ^�C�}�[
	int m_nRank;
	CCarManager *m_pCarManager;		// �J�[�}�l�[�W���[�̃|�C���^
};

#endif