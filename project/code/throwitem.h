//==========================================================
//
// 捨てるアイテム [throwitem.h]
// Author : Ryosuke Ohhra
//
//==========================================================
#ifndef _THROWITEM_H_		// このマクロが定義されていない場合
#define _THROWITEM_H_		// 二重インクルード防止用マクロを定義

#include "task.h"	// これでファイルインクルードできます

// 前方宣言
class CObjectBillboard;
class CPlayer;

//==========================================================
// サンプルのクラス定義
//==========================================================
class CThrowItem : public CTask
{
public:

	// 種類列挙型
	enum TYPE
	{
		TYPE_COIN = 0,		// ただのコイン
		TYPE_BRECETET,		// つけると被れるブレスレット
		TYPE_CUP,           // 聖杯
		TYPE_EMERALD,       // エメラルドスプラッシュ
		TYPE_DIAMOND,       // クレイジーダイアモンド
		TYPE_GOLD,          // 思ったより軽い金塊
		TYPE_JAR,           // 高そうな壺
		TYPE_KUNAI,         // 金色の高そうなクナイ
		TYPE_RING,          // いい感じの腕輪
		TYPE_SCROLL,        // 秘伝の術が記された巻物
		TYPE_SHURIKEN,      // 伝説の忍者が使っていた手裏剣
		TYPE_MAX
	};

public:	// 誰でもアクセス可能

	CThrowItem();		// コンストラクタ
	~CThrowItem();		// デストラクタ

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CThrowItem *Create(D3DXVECTOR3* pPos, const float fUpHeight, const float fPolyWidth, const float fPolyHeight);

	// メンバ関数(取得)
	void SetParent(D3DXVECTOR3 *pPos) { m_pPos = pPos; }
	void SetUpHeight(const float fHeight) { m_fUpHeight = fHeight; }
	void SetRate(const float fRate);

private:	// 自分だけがアクセス可能

	// メンバ関数
	void SetPolySize(const float fWidth, const float fHeight);
	void SetMixPosition(void);

	// メンバ変数
	D3DXVECTOR3 *m_pPos;	// 親の座標
	float m_fUpHeight;	    // 上げる高さ
	float m_fPolyWidth;	    // オブジェクトの幅
	float m_fPolyHeight;	// オブジェクトの高さ
	float m_fRate;		    // 割合
	CObjectBillboard *m_apObject[TYPE_MAX];	// オブジェクトの配列
	static CPlayer **m_ppPlayer;
};

#endif