//===============================================
//
// ゲーム画面の管理処理 [game.h]
// Author : Ibuki Okusada
//
//===============================================
#ifndef _GAME_H_		// このマクロが定義されていない場合
#define _GAME_H_		// 二重インクルード防止用マクロを定義

#include "manager.h"
#include <mutex>

// 前方宣言
class CScore;
class CTime;
class CPlayer;
class CMapCamera;
class CFileLoad;
class CClient;
class CMeshDome;

// マクロ定義
#define NUM_FILTER	(2)

//===============================================
// ゲームクラスの定義(派生クラス)
//===============================================
class CGame : public CScene
{
public:

	enum STATE
	{
		STATE_TIMEATTACK = 0,
		STATE_MULTI,
		STATE_END,
		STATE_MAX
	};

public:

	// メンバ関数
	CGame();	// コンストラクタ
	~CGame();	// デストラクタ

	// メンバ関数
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

	// メンバ関数(ポインタ)
	CPlayer *GetPlayer(void);
	CFileLoad *GetFileLoad(void);

private:

	// TCP通信用関数
	void Online(void);
	void ByteCheck(char *pRecvData, int nRecvByte);
	void OnlineEnd(void);
	void AddressLoad(char *pAddrss);

	CFileLoad *m_pFileLoad;		// ファイル読み込みのポインタ
	CPlayer *m_pPlayer;	// プレイヤーのポインタ
	CMeshDome *m_pMeshDome;		// メッシュドームのポインタ
	CClient *m_pClient;	// クライアントのポインタ
	char m_aAddress[30];	// 接続先サーバーのアドレス
	static STATE m_state;	// 状態
	int m_nSledCnt;		// 現在動作しているスレッド数
	WSADATA m_wsaData;
	std::mutex m_mutex;
	bool m_bEnd;
};

#endif