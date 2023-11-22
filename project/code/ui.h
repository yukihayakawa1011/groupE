//==========================================================
//
// サンプルタスク [sample_task.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _UI_H_		// このマクロが定義されていない場合
#define _UI_H_		// 二重インクルード防止用マクロを定義

//#include "../task.h"
#include "task.h"	// これでファイルインクルードできます

//前方宣言
class CObject2D;

//==========================================================
// UIのクラス定義
//==========================================================
class CUI : public CTask
{

public:	// 誰でもアクセス可能

	CUI();	// コンストラクタ(オーバーロード)
	~CUI();	// デストラクタ

					// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CUI *Create(void);

	// メンバ関数(取得)
	D3DXVECTOR3 GetPosition(void) { return m_pos; }

	// メンバ関数(設定)
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }

private:	// 自分だけがアクセス可能

			// メンバ関数

			// メンバ変数
	CObject2D *m_pObject;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;

};

#endif


