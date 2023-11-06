//==========================================================
//
// プレイヤーの処理 [player.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _PLAYER_H_		// このマクロが定義されていない場合
#define _PLAYER_H_		// 二重インクルード防止用マクロを定義

#include "main.h"
#include "object.h"
#include "objectX.h"
#include "task.h"

// 前方宣言
class CCharacter;

//==========================================================
// プレイヤーのクラス定義(派生クラス)
//==========================================================
class CPlayer : public CTask
{
public:

	// 操作種類列挙型
	enum TYPE
	{
		TYPE_NONE,	// 操作不可能
		TYPE_SEND,	// データ送信
		TYPE_ACTIVE,	// 操作可能
		TYPE_MAX
	};

private:	// 自分だけがアクセス可能な定義

	// 状態列挙型
	enum STATE
	{
		STATE_APPEAR = 0,	// 出現状態
		STATE_NORMAL,		// 通常状態
		STATE_DAMAGE,		// ダメージ状態
		STATE_DEATH,		// 死亡状態
		STATE_SPAWN,		// 復活中状態
		STATE_MAX
	};

	// アクション列挙型
	enum ACTION
	{
		ACTION_NEUTRAL = 0,	// 待機状
		ACTION_WALK,			// 歩行
		ACTION_JUMP,			// ジャンプ
		ACTION_ATK,			// 攻撃
		ACTION_MAX
	};

	// 情報構造体
	typedef struct
	{
		D3DXVECTOR3 pos;		// 位置
		D3DXVECTOR3 rot;		// 向き
		D3DXVECTOR3 move;		// 移動量
		D3DXVECTOR3 posOld;	// 設定位置
		D3DXMATRIX mtxWorld;	// ワールドマトリックス
		D3DXVECTOR3 posDiff;
		STATE state;			// 状態
		float fStateCounter;	// 状態管理カウンター
	}SInfo;

public:	// 誰でもアクセス可能

	//CPlayer();	// コンストラクタ
	CPlayer(const D3DXVECTOR3 pos);	// コンストラクタ(オーバーロード)
	CPlayer(int nPriOrity = 1);
	~CPlayer();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);
	HRESULT Init(const char *pBodyName, const char *pLegName);	// オーバーロード
	void Uninit(void);
	void Update(void);
	static CPlayer *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 move,
		const char *pBodyName, const char *pLegName, const int nPriority = 4);

	// メンバ関数(設定)
	void SetMove(const D3DXVECTOR3 move) { m_Info.move = move; }
	void SetPosition(const D3DXVECTOR3 pos) { m_Info.pos = pos; m_Info.posDiff = pos; }
	void SetDiffPosition(const D3DXVECTOR3 pos) { m_Info.posDiff = pos; }
	void SetRotation(const D3DXVECTOR3 rot) { m_Info.rot = rot; }
	void BindId(int nId) { m_nId = nId; }
	void SetType(TYPE type);

	// メンバ関数(取得)
	D3DXVECTOR3 GetMove(void) { return m_Info.move; }
	D3DXVECTOR3 GetPosition(void) { return m_Info.pos; }
	D3DXVECTOR3 GetRotation(void) { return m_Info.rot; }
	int GetId(void) { return m_nId; }
	static CPlayer *GetTop(void) { return m_pTop; }
	CPlayer *GetNext(void) { return m_pNext; }
	void Damage(int nDamage);
	void SetLife(int nLife);

private:	// 自分だけがアクセス可能

	// メンバ関数
	void StateSet(void);
	void Controller(void);
	void Move(void);
	void Rotation(void);
	void Adjust(void);
	void KeyBoardRotation(void);
	void MoveController(void);

	// メンバ変数
	static CPlayer *m_pTop;	// 先頭のオブジェクトへのポインタ
	static CPlayer *m_pCur;	// 最後尾のオブジェクトへのポインタ
	CPlayer *m_pPrev;	// 前のオブジェクトへのポインタ
	CPlayer *m_pNext;	// 次のオブジェクトへのポインタ
	SInfo m_Info;			// 自分自身の情報
	CCharacter *m_pObject;	// 描画オブジェクト
	float m_fRotMove;		// 現在の角度
	float m_fRotDiff;		// 目的の角度
	float m_fRotDest;		// 角度計算
	bool m_bMove;
	int m_nLife;	// 体力
	int m_nId;	// ID
	TYPE m_type;	// 種類
	ACTION m_action;	// アクション
	static int m_nNumCount;
	
};

#endif
