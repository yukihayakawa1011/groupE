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
#include "goal.h"
#include "minimap.h"
#include "ui.h"
#include "score.h"
#include "gimmick_multidoor.h"
#include "minimap.h"
#include "gimmick_pull.h"
#include "pause.h"
#include "quataui.h"
#include <assert.h>
#include "particle.h"

// �������O��Ԃ��`
namespace {
    const D3DXVECTOR3 STARTDOORPOS = { -1160.0f, 0.0f, 950.0f };	// �X�^�[�g�n�_�h�A��{���W
	const D3DXVECTOR3 PLAYERSTARTPOS = { -2500.0f, 0.0f, 950.0f };  // �v���C���[�̃X�^�[�g�ʒu
    const D3DXVECTOR3 LEVERPOS[4] =
    {
        D3DXVECTOR3(130.0f, 100.0f, -5130.0f),
        D3DXVECTOR3(-1000.0f, 100.0f, -4440.0f),
        D3DXVECTOR3(470.0f, 100.0f, -560.0f),
        D3DXVECTOR3(360.0f, 100.0f, -1900.0f),
    };

    const D3DXVECTOR3 LEVERROT[4] =
    {
        D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
        D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
        D3DXVECTOR3(0.0f, 0.0f, 0.0f),
        D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f),
    };

    const D3DXVECTOR2 QUATAUI_SIZE = { 100.0f, 50.0f };	// �m���}��UI�̃T�C�Y
    const D3DXVECTOR2 SCORE_SIZE = { 14.0f, 18.0f };	// �X�R�A�̃T�C�Y
    const float DOOR_SPACE = (-20.0f);			// �e�X�^�[�g�n�_�h�A�̊�
    const char* FILEPASS = "data\\TXT\\player";	// �t�@�C���̃p�X
    const char* FILEEXT = ".txt";				// �t�@�C���̊g���q
    const int FILEPASS_SIZE = (200);			// �t�@�C���̃p�X�T�C�Y
    const int START_TIMER = (180);				// �J�n��������
    const int START_WAITCNT = (430);            // �X�^�[�g���̑����Ă鎞��
	const int PLAYER_MOVESTART = (180);
	const int CAMERA_ROTATESTART = (240);
	const D3DXVECTOR3 START_CAMERAROT = {0.0f, D3DX_PI * 0.0f, D3DX_PI * 0.51f};
    const int SCORE = (5000);                   // �����̃X�R�A
    const int UNINITCOUNT = (120);              // �m���}��UI��������܂ł̎���
	const int PLAYER_SPWANSTART = (240);
}

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
#define WIDTH_NUM		(2)		// ���̕�����
#define HEIGHT_NUM	(2)		// �c�̕�����
#define STANDARDSCORE  (5000)   // �m���}�̊�_

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
    m_ppCamera = nullptr;
    m_ppPlayer = nullptr;
    m_pFileLoad = nullptr;
    m_pMeshDome = nullptr;
    m_pClient = nullptr;
    m_pTimer = nullptr;
    m_QuataScore = nullptr;
    m_QuataUI = nullptr;
    m_nSledCnt = 0;
    m_bEnd = false;
    m_nStartCnt = 0;
    m_nCntLostQuataUI = 0;
    m_bPause = false;
    m_pPause = nullptr;
    m_bQuota = false;
    m_bDispQuataUI = false;
	m_bSetOnceAngle = false;
}

//===============================================
// �R���X�g���N�^(�l���ݒ�)
//===============================================
CGame::CGame(int nNumPlayer)
{
    // �l�̃N���A
    m_ppCamera = nullptr;
    m_ppPlayer = nullptr;
    m_pFileLoad = nullptr;
    m_pMeshDome = nullptr;
    m_pClient = nullptr;
    m_pTimer = nullptr;
    m_QuataScore = nullptr;
    m_QuataUI = nullptr;
    m_nSledCnt = 0;
    m_bEnd = false;
    m_nStartCnt = 0;
    m_nCntLostQuataUI = 0;
    m_bPause = false;
    m_pPause = nullptr;
    m_bQuota = false;
    m_bDispQuataUI = false;
	m_bSetOnceAngle = false;

    // �l���ݒ�
    m_nNumPlayer = nNumPlayer;
}

//===============================================
// �f�X�g���N�^
//===============================================
CGame::~CGame()
{
    if (m_pFileLoad != nullptr) {
        assert(false);
    }
    if (m_ppPlayer != nullptr) {
        assert(false);
    }
    if (m_ppCamera != nullptr) {
        assert(false);
    }
    if (m_pMeshDome != nullptr) {
        assert(false);
    }
    if (m_pTimer != nullptr) {
        assert(false);
    }
    if (m_pMiniMap != nullptr) {
        assert(false);
    }
    if (m_pClient != nullptr) {
        assert(false);
    }
    if (m_QuataScore != nullptr) {
        assert(false);
    }
    if (m_QuataUI != nullptr) {
        assert(false);
    }
    if (m_pClient != nullptr) {
        assert(false);
    }
    if (m_pClient != nullptr) {
        assert(false);
    }
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
            m_pFileLoad->OpenFile("data\\TXT\\model.txt");			//���f����
            m_pFileLoad->OpenFile("data\\TXT\\enemy_point.txt");	//�G����|�C���g
			m_pFileLoad->OpenFile("data\\TXT\\setitem.txt");	    // �A�C�e���̔z�u
        }
    }

    switch (m_state)
    {
    case STATE_LOCAL:
    {// ���[�J���̏ꍇ
        if (m_nNumPlayer <= 0)
        {// �l�����w�肳��Ă��Ȃ�
            m_nNumPlayer = 1;
        }

        // �l�����|�C���^����
        m_ppPlayer = new CPlayer*[m_nNumPlayer];

        for (int nCnt = 0; nCnt < m_nNumPlayer; nCnt++)
        {
            m_ppPlayer[nCnt] = nullptr;

            char aBodyPass[FILEPASS_SIZE] = "";		// ���̃p�X
            char aLegPass[FILEPASS_SIZE] = "";		// �����g�p�X

            sprintf(&aBodyPass[0], "%s%d\\motion_ninjabody%s", FILEPASS, nCnt, FILEEXT);
            sprintf(&aLegPass[0], "%s%d\\motion_ninjaleg%s", FILEPASS, nCnt, FILEEXT);

            m_ppPlayer[nCnt] = CPlayer::Create(D3DXVECTOR3(PLAYERSTARTPOS.x, PLAYERSTARTPOS.y, PLAYERSTARTPOS.z - nCnt * 25.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),&aBodyPass[0], &aLegPass[0]);
            m_ppPlayer[nCnt]->BindId(nCnt);

            //�X�R�A��UI�̍����ƊԊu�̒����p
            float fData = 0.0f;
            float fData1 = 0.0f;
            float fData2 = 0.0f;

            if (nCnt == 1 || nCnt == 3)
            {
                fData = 1035.0f;
            }
            else
            {
                fData = 0.0f;
            }

            if (nCnt == 2 || nCnt == 3)
            {
                fData1 = 620.0f;
                fData2 = 50.0f;

            }
            else
            {
                fData1 = 0.0f;
                fData2 = 0.0f;
            }

            // UI�̐���
            CUI *pUI = CUI::Create(D3DXVECTOR3(130.0f + fData, 50.0f + fData1, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), nCnt, nCnt, CUI::TYPE_LEFTUP);
            m_ppPlayer[nCnt]->BindUI(pUI);
            
            // �X�R�A�̐���
            CScore * pScore = CScore::Create(D3DXVECTOR3(40.0f + fData, 23.0f + fData1 + fData2, 0.0f), 6, 0.9f, SCORE_SIZE.x, SCORE_SIZE.y);
            m_ppPlayer[nCnt]->BindScore(pScore);
			m_ppPlayer[nCnt]->SetDraw(false);
        }

		if (m_pFileLoad != NULL)
		{
			m_pFileLoad->OpenFile("data\\TXT\\gimmick.txt");	//�G����|�C���g
		}

        // �M�~�b�N�̐���

        // �J�n��(�l����)
        for (int nCnt = 0; nCnt < m_nNumPlayer; nCnt++) {
            CGimmickLever *l = CGimmickLever::Create(LEVERPOS[nCnt]);
            l->SetRotation(LEVERROT[nCnt]);
            CGimmickStartDoor *p = CGimmickStartDoor::Create(D3DXVECTOR3(STARTDOORPOS.x + nCnt * DOOR_SPACE, STARTDOORPOS.y, STARTDOORPOS.z));
            p->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
            p->SetLever(l);
        }

        // �S�[��
        CGoal::Create(D3DXVECTOR3(STARTDOORPOS.x + PLAYER_MAX * DOOR_SPACE, 2.0f, STARTDOORPOS.z), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), 100.0f);

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

    //��
    CItemBox::Create(D3DXVECTOR3(-800.0f, 0.0f, -4250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CItemBox::Create(D3DXVECTOR3(-1000.0f, 0.0f, -4250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CItemBox::Create(D3DXVECTOR3(-500.0f, 0.0f, -3400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CItemBox::Create(D3DXVECTOR3(-680.0f, 0.0f, 1775.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CItemBox::Create(D3DXVECTOR3(-880.0f, 0.0f, -2610.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	
    //�J����������
    {
        //CManager::GetInstance()->GetCamera()->Init();

        CManager::GetInstance()->GetCamera()->SetPositionV(D3DXVECTOR3(-874.3f, 1124.15f, 1717.2f));
        CManager::GetInstance()->GetCamera()->SetPositionR(D3DXVECTOR3(-320.3f, 1.0f, -91.6f));
        CManager::GetInstance()->GetCamera()->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, D3DX_PI * 0.1f));

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

    // �����J��������
    {
        // default�J�����I�t
        CManager::GetInstance()->GetCamera()->SetDraw(false);

        // �l�����|�C���^����
        m_ppCamera = new CMultiCamera*[m_nNumPlayer];

        for (int nCnt = 0; nCnt < m_nNumPlayer; nCnt++)
        {
            m_ppCamera[nCnt] = new CMultiCamera;
            m_ppCamera[nCnt]->Init();
            m_ppCamera[nCnt]->SetPositionV(D3DXVECTOR3(-874.3f, 1124.15f, 1717.2f));
            m_ppCamera[nCnt]->SetPositionR(D3DXVECTOR3(-320.3f, 1.0f, -91.6f));
            m_ppCamera[nCnt]->SetLength(400.0f);
            m_ppCamera[nCnt]->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI * 1.0f, D3DX_PI * 0.41f));

            D3DVIEWPORT9 viewport;
            //�v���C���[�Ǐ]�J�����̉�ʈʒu�ݒ�
            viewport.X = (DWORD)((SCREEN_WIDTH * 0.5f) * (nCnt % WIDTH_NUM));
            viewport.Y = (DWORD)((SCREEN_HEIGHT * 0.5f) * (nCnt / WIDTH_NUM));

            if (m_nNumPlayer < WIDTH_NUM) {
                viewport.Width = (DWORD)(SCREEN_WIDTH * 1.0f);
            }
            else
            {
                viewport.Width = (DWORD)(SCREEN_WIDTH * 0.5f);
            }

            if (m_nNumPlayer <= WIDTH_NUM) {
                viewport.Height = (DWORD)(SCREEN_HEIGHT * 1.0f);
            }
            else
            {
                viewport.Height = (DWORD)(SCREEN_HEIGHT * 0.5f);
            }
            
            viewport.MinZ = 0.0f;
            viewport.MaxZ = 1.0f;
            m_ppCamera[nCnt]->SetViewPort(viewport);

            CPlayer *pPlayer = CPlayer::GetTop();

            while (pPlayer != nullptr) {
                CPlayer *pPlayerNext = pPlayer->GetNext();

                if (pPlayer->GetId() == nCnt) {
                    pPlayer->SetCamera(m_ppCamera[nCnt]);
                    m_ppCamera[nCnt]->BindId(pPlayer->GetId());
                    break;
                }

                pPlayer = pPlayerNext;
            }
        }
    }

    // �^�C���̐���
    m_pTimer = CTime::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.4375f, SCREEN_HEIGHT * 0.05f, 0.0f));
    m_pTimer->Set(START_TIMER);
    m_pTimer->SetActive(true);

    // �X�|�b�g���C�g���I��
    CManager::GetInstance()->GetLight()->EnablePointLight(true);

    CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_GAME);

    //�~�j�}�b�v����
    if (m_pMiniMap == nullptr)
    {
        m_pMiniMap = CMiniMap::Create(m_nNumPlayer, 10, 10);	//����
        m_pMiniMap->DrawTexture();	//�~�j�}�b�v�e�N�X�`���̕`��
    }

	if (m_QuataUI == nullptr)
	{
		m_QuataUI = CQuataUI::Create(D3DXVECTOR3(SCREEN_WIDTH + 100.0f, SCREEN_HEIGHT * 0.5f, 0.0f), CQuataUI::TYPE_START, CQuataUI::STATE_MOVE, QUATAUI_SIZE.x, QUATAUI_SIZE.y);
		m_bDispQuataUI = true;
	}

	// �m���}�̐ݒ�
	int QuataScore = STANDARDSCORE + (m_nNumPlayer * SCORE);
	CResult::SetQuata(QuataScore);

	// �m���}�̓_��
	if (m_QuataScore == nullptr)
	{
		m_QuataScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH + 35.0f, SCREEN_HEIGHT * 0.5f, 0.0f), 6, 0.75f, 16.0f, 20.0f);
		m_QuataScore->SetScore(QuataScore);
	}

    // �|�[�Y�̐���
    m_pPause = CPause::Create();
    if (m_pPause != nullptr) {
        m_pPause->SetDraw(m_bPause);
    }

    CGimmick::SwitchOn();

    m_nCntLostQuataUI = UNINITCOUNT;

    return S_OK;
}

//===============================================
// �I������
//===============================================
void CGame::Uninit(void)
{
    m_bEnd = true;

    while (1)
    {
        OnlineEnd();
        if (m_nSledCnt <= 0)
        {
            break;
        }
    }

    if (m_QuataScore != nullptr)
    {
        m_QuataScore->Uninit();
        delete m_QuataScore;
        m_QuataScore = nullptr;
    }

    if (m_pPause != nullptr) {
        m_pPause->Uninit();
        delete m_pPause;
        m_pPause = nullptr;
    }

    if (m_pFileLoad != nullptr)
    {
        m_pFileLoad->Uninit();

        delete m_pFileLoad;		// �������̊J��
        m_pFileLoad = nullptr;
    }

    if (m_pClient != nullptr)
    {
        m_pClient->Uninit();
        delete m_pClient;
        m_pClient = nullptr;
    }

    if (m_QuataScore != nullptr) {
        m_QuataScore->Uninit();
        delete m_QuataScore;
        m_QuataScore = nullptr;
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

    if (m_ppCamera != nullptr) { // �g�p���Ă����ꍇ
        for (int nCnt = 0; nCnt < m_nNumPlayer; nCnt++)
        {
            // �I������
            m_ppCamera[nCnt]->Uninit();
            delete m_ppCamera[nCnt];
            m_ppCamera[nCnt] = nullptr;	// �g�p���Ă��Ȃ���Ԃɂ���
        }

        delete[] m_ppCamera;	// �|�C���^�̊J��
        m_ppCamera = nullptr;	// �g�p���Ă��Ȃ���Ԃɂ���
    }

    if (m_pTimer != nullptr) {
        m_pTimer->Uninit();
        delete m_pTimer;
        m_pTimer = nullptr;
    }

    // default�J�����I��
    CManager::GetInstance()->GetCamera()->SetDraw(true);

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

    if (pInputKey->GetTrigger(DIK_P) == true || pInputPad->GetTrigger(CInputPad::BUTTON_START, 0))
    {//�|�[�Y�L�[(P�L�[)�������ꂽ
        m_bPause = m_bPause ? false : true;

        if (m_pPause != nullptr) {
            m_pPause->SetDraw(m_bPause);
        }
    }

    if (m_bPause == true)
    {
        if (m_pPause != nullptr) {
            if (m_pPause->Update()) {
                m_bPause = false;
                m_pPause->SetDraw(m_bPause);
            }
        }
        return;
    }

	if (m_QuataScore != nullptr)
	{
		if (m_QuataUI != nullptr)
		{
			if (m_QuataUI->GetState() == CQuataUI::STATE_MOVE)
			{
				D3DXVECTOR3 pos = m_QuataScore->GetPosition();
				pos.x -= 8.0f;
				m_QuataScore->SetPosition(pos);
			}

			if (m_QuataUI->GetState() == CQuataUI::STATE_UP)
			{
				if (m_QuataUI->GetCounter() <= 0.0f) {
					D3DXVECTOR3 pos = m_QuataScore->GetPosition();
					pos.y -= 2.5f;
					m_QuataScore->SetPosition(pos);
				}
			}

			if (m_QuataUI->GetState() == CQuataUI::STATE_SET)
			{
				D3DXVECTOR3 pos = m_QuataScore->GetPosition();
				pos.y -= 2.5f * 0.13f;
				m_QuataScore->SetPosition(pos);
			}
		}
	}

    // �J�n�^�C�}�[
    if(!StartDirection())
    {	// ���Ԑ؂�
		//1�x�����v���C���[�̃J�����𒲐�
		if (m_bSetOnceAngle == false)
		{
			for (int cnt = 0; cnt < m_nNumPlayer; cnt++)
			{
				m_ppCamera[cnt]->SetRotation(m_ppCamera[cnt]->GetRotation() - D3DXVECTOR3(0.0f, 0.0f, 0.2f * D3DX_PI));
			}
			m_bSetOnceAngle = true;
		}
        if (m_state != STATE_END) {	// �I����ԈȊO
            if (EndCheck()) {	// �S���S�[�����Ă���
                CManager::GetInstance()->GetFade()->Set(CScene::MODE_RESULT);
                m_state = STATE_END;
            }
            else
            {
                if (m_pTimer != nullptr) {

                    if (m_QuataUI != nullptr) {
                        if (m_QuataUI->GetState() == CQuataUI::STATE_NONE) {
                            m_pTimer->Update();
                        }
                    }
                    else {
                        m_pTimer->Update();
                    }

                    if (m_pTimer->GetNum() <= 0) {	// �^�C���I�[�o�[
                        CManager::GetInstance()->GetFade()->Set(CScene::MODE_RESULT);
                        CResult::SetNumPlayer(m_nNumPlayer);
                        CResult::SetScore(m_ppPlayer);
                        m_state = STATE_END;
                    }
                }
            }
        }
    }

    if (CManager::GetInstance()->GetMode() == CScene::MODE_GAME)
    {
        CScene::Update();
    }

	CGimmick::Buttonoff();
}

//===============================================
// �`�揈��
//===============================================
void CGame::Draw(void)
{
    if (m_pMiniMap != nullptr) {
        m_pMiniMap->ExploredMap();
    }

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

        CResult::SetNumPlayer(m_nNumPlayer);
        CResult::SetScore(m_ppPlayer);

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

//===================================================
// �J�n���o
//===================================================
bool CGame::StartDirection(void)
{
	bool bDirection = false;

	if (m_nStartCnt < START_WAITCNT) {	// �K��l����
		m_nStartCnt++;
		bDirection = true;

		// �^�C�~���O���Ƃɓ�����
		if (m_nStartCnt == START_WAITCNT - PLAYER_SPWANSTART) {	// �v���C���[�ړ��J�n
			if (m_ppPlayer != nullptr) { // �g�p���Ă����ꍇ
				for (int nCnt = 0; nCnt < m_nNumPlayer; nCnt++) {
					if (m_ppPlayer[nCnt] != nullptr) {
						m_ppPlayer[nCnt]->SetDraw(true);
						// ���̃p�[�e�B�N������
						CParticle::Create(m_ppPlayer[nCnt]->GetPosition(), CEffect::TYPE_SMAKE);
					}
				}
			}
		}
		else if (m_nStartCnt == START_WAITCNT - PLAYER_MOVESTART) {	// �v���C���[�ړ��J�n
			if (m_ppPlayer != nullptr) { // �g�p���Ă����ꍇ
				for (int nCnt = 0; nCnt < m_nNumPlayer; nCnt++) {
					if (m_ppPlayer[nCnt] != nullptr) {
						m_ppPlayer[nCnt]->SetType(CPlayer::TYPE_AUTOMOVE);	// �����ړ���ԂɕύX
					}
				}
			}
		}
		else if (m_nStartCnt >= START_WAITCNT - PLAYER_MOVESTART) {	// �v���C���[���ړ����Ă���
			if (m_ppCamera != nullptr) { // �g�p���Ă����ꍇ
				for (int nCnt = 0; nCnt < m_nNumPlayer; nCnt++) {	// �S�ẴJ�����̋����𗣂��Ă���
					m_ppCamera[nCnt]->SetLength(m_ppCamera[nCnt]->GetLength() + 1.5f);

					// �J������ڕW�̌����܂ŉ�]������
					D3DXVECTOR3 rotDest = START_CAMERAROT - m_ppCamera[nCnt]->GetRotation();
					m_ppCamera[nCnt]->SetRotation(m_ppCamera[nCnt]->GetRotation() + rotDest * 0.1f);
				}
			}
		}

			if (m_nStartCnt == START_WAITCNT - 30) {	// �K��l
				CGimmick::SwitchOff();
			}
			else if (m_nStartCnt >= START_WAITCNT) {	// �K��l�ȏ�
				if (m_ppPlayer != nullptr) { // �g�p���Ă����ꍇ
					for (int nCnt = 0; nCnt < m_nNumPlayer; nCnt++)
					{
						if (m_ppPlayer[nCnt] != nullptr) {
							m_ppPlayer[nCnt]->SetType(CPlayer::TYPE_ACTIVE);
						}
					}
				}
			}
	}

	return bDirection;
}