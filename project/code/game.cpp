//===============================================
//
// �Q�[����ʂ̊Ǘ����� [game.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "game.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "camera.h"
#include "light.h"
#include "texture.h"
#include "objectX.h"
#include "Xfile.h"
#include "input.h"
#include "fade.h"
#include "result.h"
#include "sound.h"
#include "fileload.h"
#include "debugproc.h"
#include "time.h"
#include "meshdome.h"
#include "tcp_client.h"
#include <thread>
#include "protocol_online.h"
#include "object2D.h"
#include "player.h"
#include "enemy.h"
#include "enemymanager.h"
#include "item.h"
#include "spike.h"
#include "itembox.h"
#include "gimmick_button.h"
#include "gimmick_pitfall.h"
#include "gimmick_rotatedoor.h"
#include "gimmick_startdoor.h"
#include "gimmick_lever.h"
#include "gimmick_spear.h"

// �O���[�o��

//===============================================
// �}�N����`
//===============================================
#define START_TIME	(60 * 4)	// ��������
#define START_SCORE	(0)		// �J�n�X�R�A
#define MAP_SIZE	(100.0f)	// �}�b�v�T�C�Y
#define STARTSET_NUMENEMY	(3)	// �J�n���ɔz�u����G�̐�
#define MORNING_TIME	(60 * 6)	// �����I������
#define AM_COMRUSH	(60 * 9)	// �ʋ΃��b�V��
#define RELAX_TIME	(60 * 11)	// �����b�N�X�^�C��
#define NOON_TIME	(60 * 12.5)	// ���x��
#define EVENT_RUSH	(60 * 15.5)	// �C�x���g
#define PM_RELAX_TIME	(60 * 16)	// �A��J�n����
#define PM_GOHOME_RUSH	(60 * 19)	// �A��b�V��
#define MAX_TIME	(60 * 20 + 10)	// �ő厞��
#define SPEED_UP	(30.0f)
#define DEF_PORT	(22333)	// �|�[�g�ԍ�
#define MAX_STRING	(2048)
#define ADDRESSFILE	"data\\TXT\\address.txt"

//===============================================
// �ÓI�����o�ϐ�
//===============================================
CGame::STATE CGame::m_state = CGame::STATE_LOCAL;	// ���
int CGame::m_nNumPlayer = 0;

//===============================================
// �R���X�g���N�^
//===============================================
CGame::CGame()
{
	// �l�̃N���A
	m_ppPlayer = NULL;
	m_pFileLoad = NULL;
	m_pMeshDome = NULL;
	m_pClient = NULL;
	m_nSledCnt = 0;
	m_bEnd = false;
	
}

//===============================================
// �R���X�g���N�^(�l���ݒ�)
//===============================================
CGame::CGame(int nNumPlayer)
{
	// �l�̃N���A
	m_ppPlayer = NULL;
	m_pFileLoad = NULL;
	m_pMeshDome = NULL;
	m_pClient = NULL;
	m_nSledCnt = 0;
	m_bEnd = false;

	// �l���ݒ�
	m_nNumPlayer = nNumPlayer;
}

//===============================================
// �f�X�g���N�^
//===============================================
CGame::~CGame()
{

}

//===============================================
// ����������
//===============================================
HRESULT CGame::Init(void)
{
	memset(&m_aAddress[0], '\0', sizeof(m_aAddress));
	int nErr = WSAStartup(WINSOCK_VERSION, &m_wsaData);	// winsock�̏������֐�

	if (nErr != 0)
	{// �������Ɏ��s�����ꍇ
		
	}

	// �O���t�@�C���ǂݍ��݂̐���
	if (nullptr == m_pFileLoad)
	{// �g�p���Ă��Ȃ��ꍇ
		m_pFileLoad = new CFileLoad;

		if (m_pFileLoad != NULL)
		{
			m_pFileLoad->Init();
			m_pFileLoad->OpenFile("data\\TXT\\model.txt");
		}
	}

	switch (m_state)
	{
	case STATE_LOCAL:
	{// ���[�J���̏ꍇ
		if (m_nNumPlayer == 0)
		{// �l�����w�肳��Ă��Ȃ�
			m_nNumPlayer = PLAYER_MAX;
		}

		// �l�����|�C���^����
		m_ppPlayer = new CPlayer*[m_nNumPlayer];

		for (int nCnt = 0; nCnt < m_nNumPlayer; nCnt++)
		{
			m_ppPlayer[nCnt] = CPlayer::Create(D3DXVECTOR3(nCnt * 60.0f, 0.0f, nCnt * 60.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				"data\\TXT\\motion_body.txt", "data\\TXT\\motion_leg.txt");
			m_ppPlayer[nCnt]->BindId(nCnt);
			m_ppPlayer[nCnt]->SetType(CPlayer::TYPE_ACTIVE);
		}

		CEnemy::Create(D3DXVECTOR3(-1500.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, NULL);

		// �M�~�b�N�̐���

		// �J�n��
		CGimmickLever *l = CGimmickLever::Create(D3DXVECTOR3(-100.0f, 0.0f, 0.0f));
		CGimmickStartDoor *p = CGimmickStartDoor::Create(D3DXVECTOR3(-200.0f, 0.0f, 0.0f));
		p->SetLever(l);

		// ��(�{�^����)
		CGimmickSpear *pSpear = CGimmickSpear::Create(D3DXVECTOR3(-300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CGimmickSpear::TYPE_AUTO);
		CGimmickButton *pButton = CGimmickButton::Create(D3DXVECTOR3(100.0f, 0.0f, 0.0f));		
		pSpear->BindButton(pButton);
		pSpear->BindType(CGimmickSpear::TYPE_PRESS);

		// ��(�{�^���������玩��)
		pSpear = CGimmickSpear::Create(D3DXVECTOR3(-300.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CGimmickSpear::TYPE_AUTO);
		pButton = CGimmickButton::Create(D3DXVECTOR3(100.0f, 0.0f, 400.0f));
		pSpear->BindButton(pButton);
		pSpear->BindType(CGimmickSpear::TYPE_PRESSAUTO);

		// ��(�Z���T�[��)
		pSpear = CGimmickSpear::Create(D3DXVECTOR3(-700.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CGimmickSpear::TYPE_SENSOR);

		// �n�ʂ���̑�
		CGimmickSpear::Create(D3DXVECTOR3(-900.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CGimmickSpear::TYPE_AUTO);

		// ��]��
		CGimmickRotateDoor::Create(D3DXVECTOR3(300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		CGimmickRotateDoor::Create(D3DXVECTOR3(300.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		// ���Ƃ���
		CGimmickPitFall::Create(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	}
		break;

	case STATE_ONLINE:
	{// �I�����C���ʐM�̏ꍇ
		m_pClient = new CClient;
		AddressLoad(&m_aAddress[0]);

		if (m_pClient->Init(&m_aAddress[0], DEF_PORT))
		{// �����ڑ�����
			// �I�����C���֐����}���`�X���b�h
			std::thread th(&CGame::Online, this);
			th.detach();
		}
	}
		break;

	default:

		break;
	}

	//�G�}�l�[�W�������i�������ρj
	CEnemyManager::Create();

	for (int nCnt = 0; nCnt < 10; nCnt++)
	{
		CItem::Create(D3DXVECTOR3(400.0f + nCnt * -100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\coin.x", CItem::TYPE_NORMAL);
	}

	//��
	CItemBox::Create(D3DXVECTOR3(0.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�J����������
	{
		/*CManager::GetInstance()->GetCamera()->Init();*/

		CManager::GetInstance()->GetCamera()->SetPositionV(D3DXVECTOR3(-874.3f, 1124.15f, 1717.2f));
		CManager::GetInstance()->GetCamera()->SetPositionR(D3DXVECTOR3(-320.3f, 1.0f, -91.6f));
		CManager::GetInstance()->GetCamera()->SetRotation(D3DXVECTOR3(0.0f, 1.9f, 1.0f));

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

	// �X�|�b�g���C�g���I��
	CManager::GetInstance()->GetLight()->EnablePointLight(true);

	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_GAME);

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CGame::Uninit(void)
{
	m_ppPlayer = nullptr;
	m_bEnd = true;

	while (1)
	{
		OnlineEnd();
		if (m_nSledCnt <= 0)
		{
			break;
		}
	}

	if (m_pFileLoad != NULL)
	{
		m_pFileLoad->Uninit();

		delete m_pFileLoad;		// �������̊J��
		m_pFileLoad = NULL;
	}

	if (m_pClient != NULL)
	{
		m_pClient->Uninit();
		delete m_pClient;
		m_pClient = NULL;
	}

	if (m_ppPlayer != NULL)
	{// �g�p���Ă����ꍇ
		for (int nCnt = 0; nCnt < m_nNumPlayer; nCnt++)
		{
			// �I������
			m_ppPlayer[nCnt]->Uninit();
			m_ppPlayer[nCnt] = NULL;	// �g�p���Ă��Ȃ���Ԃɂ���
		}

		delete[] m_ppPlayer;	// �|�C���^�̊J��
		m_ppPlayer = NULL;	// �g�p���Ă��Ȃ���Ԃɂ���
	}

	//Winsock�I������
	WSACleanup();	// WSACleanup�֐� : winsock�̏I������

	m_state = STATE_LOCAL;
}

//===============================================
// �X�V����
//===============================================
void CGame::Update(void)
{
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();
	CInputKeyboard *pInputKey = CManager::GetInstance()->GetInputKeyboard();

	if (m_state != STATE_END) {	// �I����ԈȊO
		if (EndCheck()) {	// �S���S�[�����Ă���
			CManager::GetInstance()->GetFade()->Set(CScene::MODE_RESULT);
			m_state = STATE_END;
		}
	}

	if (CManager::GetInstance()->GetMode() == CScene::MODE_GAME)
	{
		CScene::Update();
	}
}

//===============================================
// �`�揈��
//===============================================
void CGame::Draw(void)
{
	CScene::Draw();
}

//===================================================
// �v���C���[�̎擾
//===================================================
CPlayer *CGame::GetPlayer(void)
{
	return *m_ppPlayer;
}

//===================================================
// �t�@�C���ǂݍ��݂̎擾
//===================================================
CFileLoad *CGame::GetFileLoad(void)
{
	return m_pFileLoad;
}

//===================================================
// �I����Ԃ��m�F���Ď擾
//===================================================
bool CGame::EndCheck(void)
{
	CPlayer *pPl = CPlayer::GetTop();	// �v���C���[
	int nNumGoal = 0;

	// �S�[�����Ă���l���𔻒�
	while (pPl != nullptr) {

		CPlayer *pPlNext = pPl->GetNext();	// �����o����

		if (!pPl->GetGoal()) {	// �S�[�����Ă��Ȃ�
			break;
		}

		nNumGoal++;
		pPl = pPlNext;	// ���Ɉړ�
	}

	if (nNumGoal >= CPlayer::GetNum()) {	// �S���S�[��
		return true;
	}

	return false;
}

//===================================================
// �I�����C���ʐM
//===================================================
void CGame::Online(void)
{
	m_nSledCnt = 1;

	while (1)
	{
		if (m_ppPlayer == NULL || m_bEnd == true)
		{
			break;
		}

		char aRecvData[MAX_STRING] = {};	// ��M�p

		// ��M
		int nRecvByte = m_pClient->Recv(&aRecvData[0], MAX_STRING);

		// �}���`�X���b�h
		std::thread th(&CGame::ByteCheck, this, &aRecvData[0], nRecvByte);
		th.detach();
	}

	m_nSledCnt--;
}

//===================================================
// ��M�m�F
//===================================================
void CGame::ByteCheck(char *pRecvData, int nRecvByte)
{
	m_mutex.lock();

	m_nSledCnt++;
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	int nType = COMMAND_TYPE_NONE;	// �R�}���h�ԍ�
	int nId = -1;		// ID
	int nByte = 0;	// �o�C�g��
	int nDamage = 0;	// �_���[�W��
	CPlayer *pPlayer = NULL;		// �擪���擾
	CPlayer *pPlayerNext = NULL;	// ����ێ�

	if (nRecvByte <= 0)
	{
		m_nSledCnt--;
		m_mutex.unlock();
		return;
	}

	pPlayer = CPlayer::GetTop();	// �擪���擾

	// �I�[�����܂Ŋm�F����
	while (nByte < nRecvByte)
	{
		bool bIn = false;	// ���ɂ��邩�ǂ���
		memcpy(&nId, &pRecvData[nByte], sizeof(int));
		nByte += sizeof(int);

		// �R�}���h�擾
		memcpy(&nType, &pRecvData[nByte], sizeof(int));
		nByte += sizeof(int);

		if (nId != -1)
		{
			// �R�}���h���Ƃɕ�����
			switch (nType)
			{

			case COMMAND_TYPE_SETPOSITION:

				memcpy(&pos, &pRecvData[nByte], sizeof(D3DXVECTOR3));
				nByte += sizeof(D3DXVECTOR3);
				break;

			case COMMAND_TYPE_SETROTATION:

				memcpy(&pos, &pRecvData[nByte], sizeof(D3DXVECTOR3));
				nByte += sizeof(D3DXVECTOR3);
				break;

			case COMMAND_TYPE_SETLIFE:

				memcpy(&nDamage, &pRecvData[nByte], sizeof(int));
				nByte += sizeof(int);
				break;

			case COMMAND_TYPE_START_OK:

				break;

			case COMMAND_TYPE_CREATE:
				break;

			case COMMAND_TYPE_DAMAGE:

				memcpy(&nDamage, &pRecvData[nByte], sizeof(int));
				nByte += sizeof(int);
				break;

			case COMMAND_TYPE_DELETE:
				break;

			case COMMAND_TYPE_GETID:
				break;
			}
		}

		if (m_ppPlayer == NULL)
		{
			m_nSledCnt--;
			m_mutex.unlock();
			return;
		}

		if (nId != -1 && (*m_ppPlayer)->GetId() != -1)
		{// ID����M�ł���

			pPlayer = CPlayer::GetTop();	// �擪���擾

			while (pPlayer != NULL)
			{// �g�p����Ă���ԌJ��Ԃ�
				pPlayerNext = pPlayer->GetNext();	// ����ێ�

				if (nId == pPlayer->GetId() && (*m_ppPlayer)->GetId() != nId)
				{// �����ȊO�����삵�Ă��Ȃ�

				 // �R�}���h���Ƃɕ�����
					switch (nType)
					{
					case COMMAND_TYPE_SETPOSITION:

						pPlayer->SetDiffPosition(pos);
						break;

					case COMMAND_TYPE_SETROTATION:

						pPlayer->SetRotation(pos);
						break;

					case COMMAND_TYPE_SETLIFE:

						pPlayer->SetLife(nDamage);
						break;

					case COMMAND_TYPE_START_OK:

						break;

					case COMMAND_TYPE_CREATE:

						break;

					case COMMAND_TYPE_DAMAGE:

						pPlayer->Damage(nDamage);
						break;

					case COMMAND_TYPE_GOAL:

						break;

					case COMMAND_TYPE_DELETE:

						pPlayer->Uninit();
						break;

					case COMMAND_TYPE_GETID:

						break;
					}

					bIn = true;	// �����Ԃɂ���
					break;
				}
				else if (nId == pPlayer->GetId() && (*m_ppPlayer)->GetId() == nId)
				{// �����ȊO������L����

					bIn = true;	// �����Ԃɂ���
					break;
				}

				pPlayer = pPlayerNext;	// ���Ɉړ�
			}

			if (bIn == false && (*m_ppPlayer)->GetId() != -1 && nType > COMMAND_TYPE_NONE && nType < COMMAND_TYPE_MAX)
			{// �܂����݂��Ă��Ȃ��ꍇ
				pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, NULL);
				pPlayer->BindId(nId);
				pPlayer->SetType(CPlayer::TYPE_NONE);
			}
		}
		else if (nId == -1 && (*m_ppPlayer)->GetId() == -1)
		{// ID����M�ł��Ă��Ȃ����������g��ID�����݂��Ă��Ȃ�
			nId = nType;

			// ������ID��ݒ�
			(*m_ppPlayer)->BindId(nId);

			break;
		}
	}

	m_nSledCnt--;
	m_mutex.unlock();
}

//===================================================
// ���W���M
//===================================================
void CGame::SendPosition(D3DXVECTOR3& pos)
{
	if (m_pClient != nullptr)
	{
		char aSendData[MAX_STRING] = {};	// ���M�p
		int nProt = COMMAND_TYPE_SETPOSITION;

		// protocol��}��
		memcpy(&aSendData[0], &nProt, sizeof(int));

		// ���W��}��
		memcpy(&aSendData[sizeof(int)], &pos, sizeof(D3DXVECTOR3));

		// ���M
		m_pClient->Send(&aSendData[0], sizeof(int) + sizeof(D3DXVECTOR3));
	}
}

//===================================================
// �������M
//===================================================
void CGame::SendRotation(D3DXVECTOR3& rot)
{
	if (m_pClient != nullptr)
	{
		char aSendData[MAX_STRING] = {};	// ���M�p
		int nProt = COMMAND_TYPE_SETROTATION;

		// protocol��}��
		memcpy(&aSendData[0], &nProt, sizeof(int));

		// ���W��}��
		memcpy(&aSendData[sizeof(int)], &rot, sizeof(D3DXVECTOR3));

		// ���M
		m_pClient->Send(&aSendData[0], sizeof(int) + sizeof(D3DXVECTOR3));
	}
}

//===================================================
// �_���[�W���M
//===================================================
void CGame::SendDamage(int nDamage)
{
	if (m_pClient != nullptr)
	{
		char aSendData[MAX_STRING] = {};	// ���M�p
		int nProt = COMMAND_TYPE_DAMAGE;

		// protocol��}��
		memcpy(&aSendData[0], &nProt, sizeof(int));

		// �_���[�W��}��
		memcpy(&aSendData[sizeof(int)], &nDamage, sizeof(int));

		// ���M
		m_pClient->Send(&aSendData[0], sizeof(int) + sizeof(int));
	}
}

//===================================================
// �̗͑��M
//===================================================
void CGame::SendLife(int nLife)
{
	if (m_pClient != nullptr)
	{
		char aSendData[MAX_STRING] = {};	// ���M�p
		int nProt = COMMAND_TYPE_SETLIFE;

		// protocol��}��
		memcpy(&aSendData[0], &nProt, sizeof(int));

		// �_���[�W��}��
		memcpy(&aSendData[sizeof(int)], &nLife, sizeof(int));

		// ���M
		m_pClient->Send(&aSendData[0], sizeof(int) + sizeof(int));
	}
}

//===================================================
// �I�����M
//===================================================
void CGame::OnlineEnd(void)
{
	if (m_pClient != nullptr)
	{
		char aSendData[MAX_STRING] = {};	// ���M�p
		int nProt = COMMAND_TYPE_DELETE;

		// protocol��}��
		memcpy(&aSendData[0], &nProt, sizeof(int));

		// ���M
		m_pClient->Send(&aSendData[0], sizeof(int));
	}
}

//===============================================
// �̗͐ݒ�
//===============================================
void CGame::SendSetUp(void)
{
	if (m_pClient != nullptr)
	{
		char aSendData[MAX_STRING] = {};	// ���M�p
		int nProt = COMMAND_TYPE_START_OK;

		// protocol��}��
		memcpy(&aSendData[0], &nProt, sizeof(int));

		// ���M
		m_pClient->Send(&aSendData[0], sizeof(int));
	}
}

//===============================================
// �S�[�����M
//===============================================
void CGame::SendGoal(void)
{
	if (m_pClient != nullptr)
	{
		char aSendData[MAX_STRING] = {};	// ���M�p
		int nProt = COMMAND_TYPE_GOAL;

		// protocol��}��
		memcpy(&aSendData[0], &nProt, sizeof(int));

		// ���M
		m_pClient->Send(&aSendData[0], sizeof(int));
	}
}

//===================================================
// �A�h���X�ǂݍ���
//===================================================
void CGame::AddressLoad(char *pAddrss)
{
	FILE *pFile;	// �t�@�C���ւ̃|�C���^

	pFile = fopen(ADDRESSFILE, "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		
		//�e�L�X�g�ǂݍ���
		fscanf(pFile, "%s", pAddrss);

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		return;
	}
}
