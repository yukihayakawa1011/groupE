//==========================================================
//
// 風の術 [air.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _SAMPLETASK_H_		// このマクロが定義されていない場合
#define _SAMPLETASK_H_		// 二重インクルード防止用マクロを定義

#include "task.h"	// これでファイルインクルードできます

//==========================================================
// サンプルのクラス定義
//==========================================================
class CAir : public CTask
{
private:

	// 情報構造体
	struct SInfo
	{
		D3DXVECTOR3 pos;	// 座標
		D3DXVECTOR3 rot;	// 向き
		D3DXMATRIX mtxWorld;	// ワールドマトリックス
		float fRange;		// 半径
	};

public:	// 誰でもアクセス可能

	CAir();	// コンストラクタ(オーバーロード)
	~CAir();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CAir *Create(const D3DXVECTOR3& pos, const int nId);

	// メンバ関数(取得)
	D3DXVECTOR3 GetPosition(void) { return m_Info.pos; }
	int GetId(void) { return m_nId; }

	// メンバ関数(設定)
	void SetPosition(const D3DXVECTOR3& pos) { m_Info.pos = pos; }
	void Collision(void);
	void BindId(int nId) { m_nId = nId; }

private:	// 自分だけがアクセス可能

	// メンバ関数

	// メンバ変数
	int m_nId;	// 使用者ID
	SInfo m_Info;	// 情報
};

#endif
