//==========================================================
//
// チュートリアルのエントリーのアイコン [entryicon.h]
// Author : Ryosuke Ohara
//
//==========================================================
#ifndef _ENTRYICON_H_		// このマクロが定義されていない場合
#define _ENTRYICON_H_		// 二重インクルード防止用マクロを定義

#include "task.h"

// 前方宣言
class CObject2D;

// マクロ定義
#define NUM_PLAYER (4)  // プレイヤーの最大人数

//===============================================
// ナンバークラスの定義
//===============================================
class CEntryIcon : public CTask
{
public:	// 誰でもアクセス可能

	CEntryIcon();	// コンストラクタ
	~CEntryIcon();	// デストラクタ

	enum STATE
	{
		STATE_STANDBY = 0,          // エントリー受付中
		STATE_ENTRY,                // エントリー完了
		STATE_MAX
	};

	// 情報
	struct Info
	{
		D3DXVECTOR3 pos;            // 位置
		D3DXCOLOR col;              // 色
		STATE state;                // 状態
		float fPolyWidth;	        // オブジェクトの幅
		float fPolyHeight;	        // オブジェクトの高さ
		bool bEntry;                // エントリーしたかどうか
	};

	// メンバ関数
	//HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CEntryIcon *Create(void);
	static CEntryIcon *Create(D3DXVECTOR3 * pPos, D3DXMATRIX *Matrix, const float fUpHeight, const float fPolyWidth, const float fPolyHeight);
	CObject2D *GetObjectBill(void) { return m_apObject[0]; }

	// メンバ関数(設定)
	void SetIdx(const int nIdx);
	void SetMixPosition(void);

private:	// 自分だけがアクセス可能

	// メンバ関数
	void SetPolySize(const float fWidth, const float fHeight);

	// メンバ変数
	Info m_Info;                        // 情報
	CObject2D *m_apObject[NUM_PLAYER];	// オブジェクト2Dのポインタ
	int m_nIdx;                         // インデックス番号
};

#endif