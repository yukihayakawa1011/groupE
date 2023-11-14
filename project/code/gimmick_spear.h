//==========================================================
//
// ギミック生える槍 [gimmick_spear.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _GIMMICK_SPEAR_H_		// このマクロが定義されていない場合
#define _GIMMICK_SPEAR_H_		// 二重インクルード防止用マクロを定義

#include "gimmick.h"		// これでファイルインクルードできます

class CModel;

//==========================================================
// サンプルのクラス定義
//==========================================================
class CGimmickSpear : public CGimmick
{
private:

public:

	// 状態列挙型
	enum STATE
	{
		STATE_NONE = 0,	// 何もない
		STATE_ROTATE,		// 回転中
		STATE_MAX
	};

public:	// 誰でもアクセス可能

	CGimmickSpear();		// コンストラクタ(オーバーロード)
	~CGimmickSpear();		// デストラクタ

								// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CGimmickSpear *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);

	// メンバ関数(取得)
	STATE GetState(void) { return m_state; }
	CModel *GetModel(void) { return m_pObj; }

	// メンバ関数(設定)

private:	// 自分だけがアクセス可能

	// メンバ関数
	bool CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, D3DXVECTOR3 &SetPos, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, int nAction, CGimmick **ppGimmick);

	// メンバ変数
	CModel *m_pObj;			// オブジェクトのポインタ
	STATE m_state;			// 状態
	D3DXVECTOR3 m_RotDest;		// 目標の角度
	static char *m_pFileName;	// モデルファイルネーム

};

#endif

