//==========================================================
//
// ノルマのUI [quataui.h]
// Author : Ryosuke Ohara
//
//==========================================================
#ifndef _QUATAUI_H_		// このマクロが定義されていない場合
#define _QUATAUI_H_		// 二重インクルード防止用マクロを定義

//#include "../task.h"
#include "task.h"	// これでファイルインクルードできます

//前方宣言
class CObject2D;
class CLife;

//==========================================================
// UIのクラス定義
//==========================================================
class CQuataUI : public CTask
{

public:	// 誰でもアクセス可能

	// UIの種類
	enum QUATATYPE
	{
		TYPE_START = 0,	// 〇〇点盗め
		TYPE_CLEAR,		// ノルマ達成
		TYPE_FIAL,			// ノルマ失敗
		TYPE_MAX
	};

	CQuataUI();	// コンストラクタ(オーバーロード)
	~CQuataUI();	// デストラクタ

			// メンバ関数
	HRESULT Init(void);
	HRESULT Init(float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	static CQuataUI *Create(D3DXVECTOR3 pos, QUATATYPE type, float fWidth, float fHeight);
	void LostCount(void);

	// メンバ関数(取得)
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	QUATATYPE GetType(void) { return m_type; }
	int GetLife(void) { return m_nLife; }

	// メンバ関数(設定)
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetType(QUATATYPE type) { m_type = type; }

private:	// 自分だけがアクセス可能

	// メンバ関数

	// メンバ変数
	CObject2D *m_pObject;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	QUATATYPE m_type;
	const static char *m_apQuataFileName[TYPE_MAX];	// 初期読み込みファイル名
	int m_nLife;
	int m_nNumPlayer;
};

#endif