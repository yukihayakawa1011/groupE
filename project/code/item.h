//==========================================================
//
// アイテムの処理 [item.h]
// Author : Yuuka Sakuma
//
//==========================================================
#ifndef _ITEM_H_	// このマクロが定義されていない場合
#define _ITEM_H_	// 二重インクルード防止用マクロを定義

#include "task.h"

// 前方宣言
class CObjectX;

//==========================================================
// アイテムクラスの定義(派生クラス)
//==========================================================
class CItem : public CTask
{
public:

	enum TYPE
	{
		TYPE_NORMAL = 0,	// 通常
		TYPE_DROP,		// ドロップしたもの
		TYPE_MAX
	};

public:	// 誰でもアクセス可能

	CItem();		// コンストラクタ
	~CItem();		// デストラクタ

	// メンバ関数
	HRESULT Init(void);
	HRESULT Init(const char *pFileName);
	void Uninit(void);
	void Update(void);

	static CItem *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *pFileName, int nType = TYPE_NORMAL);
	static CItem *Collision(D3DXVECTOR3 &pos);

	// メンバ関数(設定)
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	void SetOldPos(D3DXVECTOR3 posOld) { m_posOld = posOld; }
	void SetPosition(const D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRotation(const D3DXVECTOR3 rot) { m_rot = rot; }
	void SetType(TYPE type) { m_nType = type; }
	CItem *GetNext(void) { return m_pNext; }
	CItem *GetPrev(void) { return m_pPrev; }

	// メンバ関数(取得)
	D3DXVECTOR3 GetMove(void) { return m_move; }
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	D3DXVECTOR3 GetOldPos(void) { return m_posOld; }
	int GetType(void) { return m_nType; }
	void SetNext(CItem *pNext) { m_pNext = pNext; }
	void SetPrev(CItem *pPrev) { m_pPrev = pPrev; }

private:	// 自分だけがアクセス可能

	// メンバ関数
	bool CollisionCheck(D3DXVECTOR3 &pos);

	// メンバ変数
	static CItem *m_pTop;	// 先頭のオブジェクトへのポインタ
	static CItem *m_pCur;	// 最後尾のオブジェクトへのポインタ
	CItem *m_pPrev;	// 前のオブジェクトへのポインタ
	CItem *m_pNext;	// 次のオブジェクトへのポインタ
	CObjectX *m_pObject;
	D3DXVECTOR3 m_move;	// 移動量
	D3DXVECTOR3 m_posOld;	// 前回の座標
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	int m_nBound;		// bound回数
	float m_fCurve;
	int m_nType;
};

#endif