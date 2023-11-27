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
	static void SetNumPlayer(int nNum) { m_nNumPlayer = nNum; }

private:

	// �����o�֐�
	void Save(int *pScore);
	void Load(int *pScore);
	void Sort(int *pScore);
	void RankIn(int *pScore, int nResult);

	// �����o�ϐ�
	CFileLoad *m_pFileLoad;	// �t�@�C���ǂݍ��݂̃|�C���^
	CMeshDome *m_pMeshSky;		// ��p
	CTime *m_pTime;			// �^�C�}�[
	static CScore **m_apScore;	// �X�R�A�̃|�C���^(���ʕ�)
	CCharacter *m_apCharacter[TYPE_MAX];
	static CPlayer **m_ppPlayer;		// �v���C���[�̃|�C���^
	int m_nRank;				// ����̃����N
	int m_nTimer;				// �J�ڃ^�C�}�[
	static int *m_nScore;			// ����̃X�R�A
	static TYPE m_type;		    // ���
	static int m_nNumPlayer;    // �S�[�������v���C���[�̐l��
};

#endif