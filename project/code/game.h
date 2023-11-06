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
class CMapCamera;
class CFileLoad;
class CClient;
class CMeshDome;

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
	void SendPosition(D3DXVECTOR3 pos);
	void SendRotation(D3DXVECTOR3 rot);
	void SendDamage(int nDamage);
	void SendLife(int nLife);
	void SendSetUp(void);
	void SendGoal(void);
	void SetNumPlayer(int nNum) { m_nNumPlayer = nNum; }
	int GetNumPlayer(void) { return m_nNumPlayer; }

	// �����o�֐�(�|�C���^)
	CPlayer *GetPlayer(void);
	CFileLoad *GetFileLoad(void);

private:

	// TCP�ʐM�p�֐�
	void Online(void);
	void ByteCheck(char *pRecvData, int nRecvByte);
	void OnlineEnd(void);
	void AddressLoad(char *pAddrss);

	CFileLoad *m_pFileLoad;		// �t�@�C���ǂݍ��݂̃|�C���^
	CPlayer **m_ppPlayer;			// �v���C���[�̃|�C���^
	CMeshDome *m_pMeshDome;		// ���b�V���h�[���̃|�C���^
	CClient *m_pClient;	// �N���C�A���g�̃|�C���^
	char m_aAddress[30];	// �ڑ���T�[�o�[�̃A�h���X
	static STATE m_state;	// ���
	int m_nSledCnt;		// ���ݓ��삵�Ă���X���b�h��
	int m_nNumPlayer;		// �v���C�l��
	WSADATA m_wsaData;
	std::mutex m_mutex;
	bool m_bEnd;
};

#endif