//===============================================
//
// �Q�[����ʂ̊Ǘ����� [game.h]
// Author : Ibuki Okusada
//
//===============================================
#ifndef _GAME_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _GAME_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "manager.h"
#include <mutex>

// �O���錾
class CScore;
class CTime;
class CPlayer;
class CFileLoad;
class CClient;
class CMeshDome;
class CMiniMap;
class CPause;
class CQuataUI;
class CGimmickLever;
class CGimmickStartDoor;

// �}�N����`
#define NUM_FILTER	(2)

//===============================================
// �Q�[���N���X�̒�`(�h���N���X)
//===============================================
class CGame : public CScene
{
public:

	enum STATE
	{
		STATE_LOCAL = 0,	// ���[�J���ʐM
		STATE_ONLINE,		// TCP�I�����C��
		STATE_END,
		STATE_PAUSE,
		STATE_MAX
	};

public:

	// �����o�֐�
	CGame();	// �R���X�g���N�^
	CGame(int nNumPlayer);	// �R���X�g���N�^
	~CGame();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetState(STATE state) { m_state = state; }
	void SendPosition(D3DXVECTOR3& pos);
	void SendRotation(D3DXVECTOR3& rot);
	void SendDamage(int nDamage);
	void SendLife(int nLife);
	void SendSetUp(void);
	void SendGoal(void);
	static void SetNumPlayer(int nNum) { m_nNumPlayer = nNum; }
	static int GetNumPlayer(void) { return m_nNumPlayer; }
	CMiniMap* GetMiniMap(void) { return m_pMiniMap; }
	bool GetbopenDoor(void) { return m_bOpenStartDoor; }

	// �����o�֐�(�|�C���^)
	CPlayer *GetPlayer(void);
	CFileLoad *GetFileLoad(void);

private:

	// TCP�ʐM�p�֐�
	void Online(void);
	void ByteCheck(char *pRecvData, int nRecvByte);
	void OnlineEnd(void);
	void AddressLoad(char *pAddrss);
	bool EndCheck(void);
	bool StartDirection(void);

	CFileLoad *m_pFileLoad;		// �t�@�C���ǂݍ��݂̃|�C���^
	CPlayer **m_ppPlayer;		// �v���C���[�̃|�C���^
	CMultiCamera **m_ppCamera;	// �J�����̃|�C���^
	CMeshDome *m_pMeshDome;		// ���b�V���h�[���̃|�C���^
	CTime *m_pTimer;			// �^�C�}�[
	CMiniMap* m_pMiniMap;		// �~�j�}�b�v
	CClient *m_pClient;			// �N���C�A���g�̃|�C���^
	CScore *m_QuataScore;       // �m���}�̃X�R�A
	CQuataUI *m_QuataUI;        // �m���}��UI
	CGimmickLever **m_ppLever;  // ���o�[�̃|�C���^
	CGimmickStartDoor **m_ppMultiDoor;  // ���͔��̃|�C���^
	char m_aAddress[30];		// �ڑ���T�[�o�[�̃A�h���X
	static STATE m_state;		// ���
	int m_nSledCnt;				// ���ݓ��삵�Ă���X���b�h��
	static int m_nNumPlayer;	// �v���C�l��
	CPause *m_pPause;			// �|�[�Y���
	WSADATA m_wsaData;
	std::mutex m_mutex;
	bool m_bEnd;
	int m_nStartCnt;			// �J�n�^�C�}�[
	int m_nCntLostQuataUI;      // �m���}��UI��������܂ł̃J�E���g
	int m_nCntGoal;             // �S�[�������l��
	int m_nCntLookGoal;         //
	bool m_bPause;              // �|�[�Y
	bool m_bQuota;              // �m���}�B�����Ă���ǂ���
	bool m_bDispQuataUI;        // �m���}��UI���ł��邩�ǂ���
	bool m_bSetOnceAngle;		// 1�x�����̊p�x�ݒ��������
	bool m_bOpenStartDoor;      // �X�^�[�g�̃h�A�����ׂĊJ���Ă��邩�ǂ���
};

#endif