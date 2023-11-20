//==========================================================
//
// 敵の処理 [enemy.h]
// Author : Soma Ishihara (Base:Ibuki Okusada)
//
//==========================================================
#ifndef _ENEMY_H_		// このマクロが定義されていない場合
#define _ENEMY_H_		// 二重インクルード防止用マクロを定義

#include "main.h"
#include "object.h"
#include "objectX.h"
#include "task.h"

// 前方宣言
class CPlayer;
class CCharacter;

//==========================================================
// 敵のクラス定義(派生クラス)
//==========================================================
class CEnemy : public CTask
{
private:	// 自分だけがアクセス可能な定義

	// 状態列挙型
	enum STATE
	{
		STATE_APPEAR = 0,	// 出現状態
		STATE_NORMAL,		// 通常状態
		STATE_DAMAGE,		// ダメージ状態
		STATE_DEATH,		// 死亡状態
		STATE_SPAWN,		// 生成状態
		STATE_MAX
	};

	// モーション列挙型
	enum MOTION {
		MOTION_NEUTRAL = 0,	// 待機
		MOTION_MOVE,			// 移動
		MOTION_JUMP,			// ジャンプ状態
		MOTION_ATK,			// 攻撃
		MOTION_DAMAGE,		// ダメージ
		MOTION_DEATH,			// 死亡
		MOTION_MAX
	};

	// 情報構造体
	struct SInfo
	{
		D3DXVECTOR3 pos;		// 位置
		D3DXVECTOR3 rot;		// 向き
		D3DXVECTOR3 move;		// 移動量
		D3DXVECTOR3 posOld;	// 設定位置
		D3DXMATRIX mtxWorld;	// ワールドマトリックス
		D3DXVECTOR3 posDiff;	// 
		STATE state;			// 状態
		int nStateCounter;		// 状態管理カウンター
	};

public:	// 誰でもアクセス可能

	CEnemy(const D3DXVECTOR3 pos);	// コンストラクタ(オーバーロード)
	CEnemy(int nPriOrity = 1);
	~CEnemy();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);
	HRESULT Init(const char *pBodyName, const char *pLegName);	// オーバーロード
	void Uninit(void);
	void Update(void);
	static CEnemy *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 move,
		const char *pBodyName, const char *pLegName, const int nPriority = 4);
	void HitCheck(D3DXVECTOR3 pos, float fRange, int nDamage = 1);

	// メンバ関数(設定)
	void SetMove(const D3DXVECTOR3 move) { m_Info.move = move; }
	void SetPosition(const D3DXVECTOR3 pos) { m_Info.pos = pos; m_Info.posDiff = pos; }
	void SetDiffPosition(const D3DXVECTOR3 pos) { m_Info.posDiff = pos; }
	void SetRotation(const D3DXVECTOR3 rot) { m_Info.rot = rot; }
	void BindId(int nId) { m_nId = nId; }
	void SetType(TYPE type){ m_type = type; }

	// メンバ関数(取得)
	D3DXVECTOR3 GetMove(void) { return m_Info.move; }
	D3DXVECTOR3 GetPosition(void) { return m_Info.pos; }
	D3DXVECTOR3 GetRotation(void) { return m_Info.rot; }
	int GetId(void) { return m_nId; }
	static CEnemy *GetTop(void) { return m_pTop; }
	CEnemy *GetNext(void) { return m_pNext; }
	void Damage(int nDamage);
	void SetLife(int nLife);
	static int GetNum(void) { return m_nNumCount; }
	int GetLife(void) { return m_nLife; }

private:	// 自分だけがアクセス可能

	// メンバ関数
	void StateSet(void);
	void Controller(void);
	void Move(void);
	void Rotation(void);
	void Adjust(void);
	void Search(void);
	void Chace(void);
	void Death(void);
	void MotionSet(void);
	void Collision(void);
	void CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, const float fRefMulti = 0.5f);
	CPlayer* SearchNearPlayer(float fRadiusRest, float* pLength = nullptr);
	D3DXVECTOR3 CollisionAllEnemy(D3DXVECTOR3 pos);

	// メンバ変数
	static CEnemy *m_pTop;	// 先頭のオブジェクトへのポインタ
	static CEnemy *m_pCur;	// 最後尾のオブジェクトへのポインタ
	CEnemy *m_pPrev;		// 前のオブジェクトへのポインタ
	CEnemy *m_pNext;		// 次のオブジェクトへのポインタ
	SInfo m_Info;			// 自分自身の情報
	CCharacter *m_pObject;	// 描画オブジェクト
	float m_fRotMove;		// 現在の角度
	float m_fRotDiff;		// 目的の角度
	float m_fRotDest;		// 角度計算
	bool m_bJump;			// ジャンプ
	int m_nLife;	// 体力
	int m_nCounterAttack;	//攻撃カウンター
	bool m_bChace;	//追跡モードか否か
	int m_nId;	// ID
	TYPE m_type;	// 種類
	static int m_nNumCount;

};

#endif
