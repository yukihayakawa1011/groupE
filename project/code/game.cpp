//===============================================
//
// ゲーム画面の管理処理 [game.cpp]
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

// グローバル

//===============================================
// マクロ定義
//===============================================
#define START_TIME	(60 * 4)	// 制限時間
#define START_SCORE	(0)		// 開始スコア
#define MAP_SIZE	(100.0f)	// マップサイズ
#define STARTSET_NUMENEMY	(3)	// 開始時に配置する敵の数
#define MORNING_TIME	(60 * 6)	// 早朝終了時刻
#define AM_COMRUSH	(60 * 9)	// 通勤ラッシュ
#define RELAX_TIME	(60 * 11)	// リラックスタイム
#define NOON_TIME	(60 * 12.5)	// 昼休み
#define EVENT_RUSH	(60 * 15.5)	// イベント
#define PM_RELAX_TIME	(60 * 16)	// 帰宅開始時間
#define PM_GOHOME_RUSH	(60 * 19)	// 帰宅ラッシュ
#define MAX_TIME	(60 * 20 + 10)	// 最大時間
#define SPEED_UP	(30.0f)
#define DEF_PORT	(22333)	// ポート番号
#define MAX_STRING	(2048)
#define ADDRESSFILE	"data\\TXT\\address.txt"

//===============================================
// 静的メンバ変数
//===============================================
CGame::STATE CGame::m_state = CGame::STATE_LOCAL;	// 状態
int CGame::m_nNumPlayer = 0;

//===============================================
// コンストラクタ
//===============================================
CGame::CGame()
{
	// 値のクリア
	m_ppPlayer = NULL;
	m_pFileLoad = NULL;
	m_pMeshDome = NULL;
	m_pClient = NULL;
	m_nSledCnt = 0;
	m_bEnd = false;
	
}

//===============================================
// コンストラクタ(人数設定)
//===============================================
CGame::CGame(int nNumPlayer)
{
	// 値のクリア
	m_ppPlayer = NULL;
	m_pFileLoad = NULL;
	m_pMeshDome = NULL;
	m_pClient = NULL;
	m_nSledCnt = 0;
	m_bEnd = false;

	// 人数設定
	m_nNumPlayer = nNumPlayer;
}

//===============================================
// デストラクタ
//===============================================
CGame::~CGame()
{

}

//===============================================
// 初期化処理
//===============================================
HRESULT CGame::Init(void)
{
	memset(&m_aAddress[0], '\0', sizeof(m_aAddress));
	int nErr = WSAStartup(WINSOCK_VERSION, &m_wsaData);	// winsockの初期化関数

	if (nErr != 0)
	{// 初期化に失敗した場合
		
	}

	// 外部ファイル読み込みの生成
	if (nullptr == m_pFileLoad)
	{// 使用していない場合
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
	{// ローカルの場合
		if (m_nNumPlayer == 0)
		{// 人数が指定されていない
			m_nNumPlayer = PLAYER_MAX;
		}

		// 人数分ポインタ生成
		m_ppPlayer = new CPlayer*[m_nNumPlayer];

		for (int nCnt = 0; nCnt < m_nNumPlayer; nCnt++)
		{
			m_ppPlayer[nCnt] = CPlayer::Create(D3DXVECTOR3(nCnt * 60.0f, 0.0f, nCnt * 60.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				"data\\TXT\\motion_body.txt", "data\\TXT\\motion_leg.txt");
			m_ppPlayer[nCnt]->BindId(nCnt);
			m_ppPlayer[nCnt]->SetType(CPlayer::TYPE_ACTIVE);
		}

		CEnemy::Create(D3DXVECTOR3(-1500.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, NULL);

		// ギミックの生成

		// 開始扉
		CGimmickLever *l = CGimmickLever::Create(D3DXVECTOR3(-100.0f, 0.0f, 0.0f));
		CGimmickStartDoor *p = CGimmickStartDoor::Create(D3DXVECTOR3(-200.0f, 0.0f, 0.0f));
		p->SetLever(l);

		// 槍(ボタン式)
		CGimmickSpear *pSpear = CGimmickSpear::Create(D3DXVECTOR3(-300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CGimmickSpear::TYPE_AUTO);
		CGimmickButton *pButton = CGimmickButton::Create(D3DXVECTOR3(100.0f, 0.0f, 0.0f));		
		pSpear->BindButton(pButton);
		pSpear->BindType(CGimmickSpear::TYPE_PRESS);

		// 槍(ボタン押したら自動)
		pSpear = CGimmickSpear::Create(D3DXVECTOR3(-300.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CGimmickSpear::TYPE_AUTO);
		pButton = CGimmickButton::Create(D3DXVECTOR3(100.0f, 0.0f, 400.0f));
		pSpear->BindButton(pButton);
		pSpear->BindType(CGimmickSpear::TYPE_PRESSAUTO);

		// 槍(センサー式)
		pSpear = CGimmickSpear::Create(D3DXVECTOR3(-700.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CGimmickSpear::TYPE_SENSOR);

		// 地面からの槍
		CGimmickSpear::Create(D3DXVECTOR3(-900.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CGimmickSpear::TYPE_AUTO);

		// 回転扉
		CGimmickRotateDoor::Create(D3DXVECTOR3(300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		CGimmickRotateDoor::Create(D3DXVECTOR3(300.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		// 落とし穴
		CGimmickPitFall::Create(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	}
		break;

	case STATE_ONLINE:
	{// オンライン通信の場合
		m_pClient = new CClient;
		AddressLoad(&m_aAddress[0]);

		if (m_pClient->Init(&m_aAddress[0], DEF_PORT))
		{// 初期接続成功
			// オンライン関数をマルチスレッド
			std::thread th(&CGame::Online, this);
			th.detach();
		}
	}
		break;

	default:

		break;
	}

	//敵マネージャ生成（投げっぱ）
	CEnemyManager::Create();

	for (int nCnt = 0; nCnt < 10; nCnt++)
	{
		CItem::Create(D3DXVECTOR3(400.0f + nCnt * -100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\coin.x", CItem::TYPE_NORMAL);
	}

	//壺
	CItemBox::Create(D3DXVECTOR3(0.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//カメラ初期化
	{
		/*CManager::GetInstance()->GetCamera()->Init();*/

		CManager::GetInstance()->GetCamera()->SetPositionV(D3DXVECTOR3(-874.3f, 1124.15f, 1717.2f));
		CManager::GetInstance()->GetCamera()->SetPositionR(D3DXVECTOR3(-320.3f, 1.0f, -91.6f));
		CManager::GetInstance()->GetCamera()->SetRotation(D3DXVECTOR3(0.0f, 1.9f, 1.0f));

		D3DVIEWPORT9 viewport;
		//プレイヤー追従カメラの画面位置設定
		viewport.X = 0;
		viewport.Y = 0;
		viewport.Width = (DWORD)(SCREEN_WIDTH * 1.0f);
		viewport.Height = (DWORD)(SCREEN_HEIGHT * 1.0f);
		viewport.MinZ = 0.0f;
		viewport.MaxZ = 1.0f;
		CManager::GetInstance()->GetCamera()->SetViewPort(viewport);
	}

	// スポットライトをオン
	CManager::GetInstance()->GetLight()->EnablePointLight(true);

	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_GAME);

	return S_OK;
}

//===============================================
// 終了処理
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

		delete m_pFileLoad;		// メモリの開放
		m_pFileLoad = NULL;
	}

	if (m_pClient != NULL)
	{
		m_pClient->Uninit();
		delete m_pClient;
		m_pClient = NULL;
	}

	if (m_ppPlayer != NULL)
	{// 使用していた場合
		for (int nCnt = 0; nCnt < m_nNumPlayer; nCnt++)
		{
			// 終了処理
			m_ppPlayer[nCnt]->Uninit();
			m_ppPlayer[nCnt] = NULL;	// 使用していない状態にする
		}

		delete[] m_ppPlayer;	// ポインタの開放
		m_ppPlayer = NULL;	// 使用していない状態にする
	}

	//Winsock終了処理
	WSACleanup();	// WSACleanup関数 : winsockの終了処理

	m_state = STATE_LOCAL;
}

//===============================================
// 更新処理
//===============================================
void CGame::Update(void)
{
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();
	CInputKeyboard *pInputKey = CManager::GetInstance()->GetInputKeyboard();

	if (m_state != STATE_END) {	// 終了状態以外
		if (EndCheck()) {	// 全員ゴールしている
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
// 描画処理
//===============================================
void CGame::Draw(void)
{
	CScene::Draw();
}

//===================================================
// プレイヤーの取得
//===================================================
CPlayer *CGame::GetPlayer(void)
{
	return *m_ppPlayer;
}

//===================================================
// ファイル読み込みの取得
//===================================================
CFileLoad *CGame::GetFileLoad(void)
{
	return m_pFileLoad;
}

//===================================================
// 終了状態を確認して取得
//===================================================
bool CGame::EndCheck(void)
{
	CPlayer *pPl = CPlayer::GetTop();	// プレイヤー
	int nNumGoal = 0;

	// ゴールしている人数を判定
	while (pPl != nullptr) {

		CPlayer *pPlNext = pPl->GetNext();	// 次を覚える

		if (!pPl->GetGoal()) {	// ゴールしていない
			break;
		}

		nNumGoal++;
		pPl = pPlNext;	// 次に移動
	}

	if (nNumGoal >= CPlayer::GetNum()) {	// 全員ゴール
		return true;
	}

	return false;
}

//===================================================
// オンライン通信
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

		char aRecvData[MAX_STRING] = {};	// 受信用

		// 受信
		int nRecvByte = m_pClient->Recv(&aRecvData[0], MAX_STRING);

		// マルチスレッド
		std::thread th(&CGame::ByteCheck, this, &aRecvData[0], nRecvByte);
		th.detach();
	}

	m_nSledCnt--;
}

//===================================================
// 受信確認
//===================================================
void CGame::ByteCheck(char *pRecvData, int nRecvByte)
{
	m_mutex.lock();

	m_nSledCnt++;
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	int nType = COMMAND_TYPE_NONE;	// コマンド番号
	int nId = -1;		// ID
	int nByte = 0;	// バイト数
	int nDamage = 0;	// ダメージ数
	CPlayer *pPlayer = NULL;		// 先頭を取得
	CPlayer *pPlayerNext = NULL;	// 次を保持

	if (nRecvByte <= 0)
	{
		m_nSledCnt--;
		m_mutex.unlock();
		return;
	}

	pPlayer = CPlayer::GetTop();	// 先頭を取得

	// 終端文字まで確認する
	while (nByte < nRecvByte)
	{
		bool bIn = false;	// 既にいるかどうか
		memcpy(&nId, &pRecvData[nByte], sizeof(int));
		nByte += sizeof(int);

		// コマンド取得
		memcpy(&nType, &pRecvData[nByte], sizeof(int));
		nByte += sizeof(int);

		if (nId != -1)
		{
			// コマンドごとに分ける
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
		{// IDを受信できた

			pPlayer = CPlayer::GetTop();	// 先頭を取得

			while (pPlayer != NULL)
			{// 使用されている間繰り返し
				pPlayerNext = pPlayer->GetNext();	// 次を保持

				if (nId == pPlayer->GetId() && (*m_ppPlayer)->GetId() != nId)
				{// 自分以外かつ操作していない

				 // コマンドごとに分ける
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

					bIn = true;	// いる状態にする
					break;
				}
				else if (nId == pPlayer->GetId() && (*m_ppPlayer)->GetId() == nId)
				{// 自分以外かつ操作キャラ

					bIn = true;	// いる状態にする
					break;
				}

				pPlayer = pPlayerNext;	// 次に移動
			}

			if (bIn == false && (*m_ppPlayer)->GetId() != -1 && nType > COMMAND_TYPE_NONE && nType < COMMAND_TYPE_MAX)
			{// まだ存在していない場合
				pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, NULL);
				pPlayer->BindId(nId);
				pPlayer->SetType(CPlayer::TYPE_NONE);
			}
		}
		else if (nId == -1 && (*m_ppPlayer)->GetId() == -1)
		{// IDが受信できていないかつ自分自身のIDも存在していない
			nId = nType;

			// 自分のIDを設定
			(*m_ppPlayer)->BindId(nId);

			break;
		}
	}

	m_nSledCnt--;
	m_mutex.unlock();
}

//===================================================
// 座標送信
//===================================================
void CGame::SendPosition(D3DXVECTOR3& pos)
{
	if (m_pClient != nullptr)
	{
		char aSendData[MAX_STRING] = {};	// 送信用
		int nProt = COMMAND_TYPE_SETPOSITION;

		// protocolを挿入
		memcpy(&aSendData[0], &nProt, sizeof(int));

		// 座標を挿入
		memcpy(&aSendData[sizeof(int)], &pos, sizeof(D3DXVECTOR3));

		// 送信
		m_pClient->Send(&aSendData[0], sizeof(int) + sizeof(D3DXVECTOR3));
	}
}

//===================================================
// 向き送信
//===================================================
void CGame::SendRotation(D3DXVECTOR3& rot)
{
	if (m_pClient != nullptr)
	{
		char aSendData[MAX_STRING] = {};	// 送信用
		int nProt = COMMAND_TYPE_SETROTATION;

		// protocolを挿入
		memcpy(&aSendData[0], &nProt, sizeof(int));

		// 座標を挿入
		memcpy(&aSendData[sizeof(int)], &rot, sizeof(D3DXVECTOR3));

		// 送信
		m_pClient->Send(&aSendData[0], sizeof(int) + sizeof(D3DXVECTOR3));
	}
}

//===================================================
// ダメージ送信
//===================================================
void CGame::SendDamage(int nDamage)
{
	if (m_pClient != nullptr)
	{
		char aSendData[MAX_STRING] = {};	// 送信用
		int nProt = COMMAND_TYPE_DAMAGE;

		// protocolを挿入
		memcpy(&aSendData[0], &nProt, sizeof(int));

		// ダメージを挿入
		memcpy(&aSendData[sizeof(int)], &nDamage, sizeof(int));

		// 送信
		m_pClient->Send(&aSendData[0], sizeof(int) + sizeof(int));
	}
}

//===================================================
// 体力送信
//===================================================
void CGame::SendLife(int nLife)
{
	if (m_pClient != nullptr)
	{
		char aSendData[MAX_STRING] = {};	// 送信用
		int nProt = COMMAND_TYPE_SETLIFE;

		// protocolを挿入
		memcpy(&aSendData[0], &nProt, sizeof(int));

		// ダメージを挿入
		memcpy(&aSendData[sizeof(int)], &nLife, sizeof(int));

		// 送信
		m_pClient->Send(&aSendData[0], sizeof(int) + sizeof(int));
	}
}

//===================================================
// 終了送信
//===================================================
void CGame::OnlineEnd(void)
{
	if (m_pClient != nullptr)
	{
		char aSendData[MAX_STRING] = {};	// 送信用
		int nProt = COMMAND_TYPE_DELETE;

		// protocolを挿入
		memcpy(&aSendData[0], &nProt, sizeof(int));

		// 送信
		m_pClient->Send(&aSendData[0], sizeof(int));
	}
}

//===============================================
// 体力設定
//===============================================
void CGame::SendSetUp(void)
{
	if (m_pClient != nullptr)
	{
		char aSendData[MAX_STRING] = {};	// 送信用
		int nProt = COMMAND_TYPE_START_OK;

		// protocolを挿入
		memcpy(&aSendData[0], &nProt, sizeof(int));

		// 送信
		m_pClient->Send(&aSendData[0], sizeof(int));
	}
}

//===============================================
// ゴール送信
//===============================================
void CGame::SendGoal(void)
{
	if (m_pClient != nullptr)
	{
		char aSendData[MAX_STRING] = {};	// 送信用
		int nProt = COMMAND_TYPE_GOAL;

		// protocolを挿入
		memcpy(&aSendData[0], &nProt, sizeof(int));

		// 送信
		m_pClient->Send(&aSendData[0], sizeof(int));
	}
}

//===================================================
// アドレス読み込み
//===================================================
void CGame::AddressLoad(char *pAddrss)
{
	FILE *pFile;	// ファイルへのポインタ

	pFile = fopen(ADDRESSFILE, "r");

	if (pFile != NULL)
	{//ファイルが開けた場合
		
		//テキスト読み込み
		fscanf(pFile, "%s", pAddrss);

		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開けなかった場合
		return;
	}
}
