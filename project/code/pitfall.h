//==========================================================
//
// 落とし穴 [pitfall.h]
// Author : Soma Ishihara
//
//==========================================================
#ifndef _PITFALL_H_		// このマクロが定義されていない場合
#define _PITFALL_H_		// 二重インクルード防止用マクロを定義

#include "task.h"

//前方宣言
class CObjectX;

//==========================================================
// サンプルのクラス定義
//==========================================================
class CPitFall : public CTask
{

public:	// 誰でもアクセス可能

	CPitFall();	// コンストラクタ(オーバーロード)
	~CPitFall();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CPitFall *Create(const D3DXVECTOR3 pos);

	// メンバ関数(取得)

	// メンバ関数(設定)
	void IsOpen(const bool bOpen) { m_bOpen = bOpen; }

private:	// 自分だけがアクセス可能

	// メンバ関数

	// メンバ変数
	CObjectX* m_pObjFloor[2];	//穴の床
	float m_fAngle;				//床の開き具合
	bool m_bOpen;				//穴を開いているか
};

#endif

