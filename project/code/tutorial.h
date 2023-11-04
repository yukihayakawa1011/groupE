//===============================================
//
// ゲーム画面の管理処理 [game.h]
// Author : Ibuki Okusada
//
//===============================================
#ifndef _TUTORIAL_H_		// このマクロが定義されていない場合
#define _TUTORIAL_H_		// 二重インクルード防止用マクロを定義

#include "manager.h"

// 前方宣言
class CFileLoad;

//===============================================
// ゲームクラスの定義(派生クラス)
//===============================================
class CTutorial : public CScene
{
public:

	// メンバ関数
	CTutorial();	// コンストラクタ
	~CTutorial();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// メンバ関数(ポインタ)
	CFileLoad *GetFileLoad(void);

private:

	CFileLoad *m_pFileLoad;			// ファイル読み込みのポインタ
};

#endif