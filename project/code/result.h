//===============================================
//
// ���U���g��ʂ̊Ǘ����� [result.h]
// Author : Ibuki Okusada
//
//===============================================
#ifndef _RESULT_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _RESULT_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "manager.h"

class CScore;
class CFileLoad;
class CMeshDome;
class CTime;
class CCharacter;
class CObject2D;

#define MAX_RANK	(4)		// �����L���O�̏��ʐ�

//===============================================
// ���U���g�N���X�̒�`(�h���N���X)
//===============================================
class CResult : public CScene
{
public:
	
	// ��ޗ񋓌^
	enum TYPE
	{
		TYPE_MULTI_WIN,		// �}���`����
		TYPE_MULTI_LOSE,	// �}���`�s�k
		TYPE_MAX			// �ʏ�
	};

public:

	// �����o�֐�
	CResult();	// �R���X�g���N�^
	~CResult();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetScore(CPlayer **ppPlayer);
	static void SetType(TYPE type) { m_type = type; }
	static TYPE GetType(void) { return m_type; }
	static void SetQuata(const int nValue) { m_nQuota = nValue; }
	static void SetNumPlayer(int nNum) { m_nNumPlayer = nNum; }

private:

	// �����o�֐�
	int SumScore(void);
	void Sort(int *pScore);
	void SetRank(int nNum);
	void SetTopScore(int *pScore);

	// �����o�ϐ�
	CFileLoad *m_pFileLoad;	// �t�@�C���ǂݍ��݂̃|�C���^
	CMeshDome *m_pMeshSky;		// ��p
	CTime *m_pTime;			// �^�C�}�[
	CScore *m_pTotalScore;		// ���v�X�R�A�I�u�W�F�N�g
	CObject2D **m_ppRank;
	static CScore **m_apScore;	// �X�R�A�̃|�C���^(���ʕ�)
	static CPlayer **m_ppPlayer;	// �v���C���[�̃|�C���^
	int m_nTimer;				// �J�ڃ^�C�}�[
	int m_nWorst;				// �ŉ��ʂ̏���
	int *m_pRank;				// �����N
	bool m_bClear;			// �B�����ǂ���
	static int *m_pScore;		// ����̃X�R�A
	static int m_nTopScore;   // ��ʂ̃X�R�A
	static TYPE m_type;		// ���
	static int m_nQuota;		// �m���}
	static int m_nNumPlayer;  // �S�[�������v���C���[�̐l��
};

#endif