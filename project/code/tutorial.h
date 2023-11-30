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
class CPlayer;
class CObject3D;

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

	bool EndCheck(void);

	CPlayer **m_ppPlayer;			// プレイヤーのポインタ
	CFileLoad *m_pFileLoad;			// ファイル読み込みのポインタ
	CObject3D *m_pObject3D;         // オブジェクト3Dのポインタ
	bool m_bEnd;
};

#endif