//==========================================================
//
// ゲージ [gage.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _GAGE_H_		// このマクロが定義されていない場合
#define _GAGE_H_		// 二重インクルード防止用マクロを定義

#include "task.h"	// これでファイルインクルードできます

// 前方宣言
class CObjectBillboard;

//==========================================================
// サンプルのクラス定義
//==========================================================
class CGage : public CTask
{
private:

	// 種類列挙型
	enum TYPE
	{
		TYPE_FRAME = 0,	// 枠
		TYPE_CONTENT,		// 中身
		TYPE_MAX
	};

public:	// 誰でもアクセス可能

	CGage();	// コンストラクタ(オーバーロード)
	~CGage();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CGage *Create(void);

	// メンバ関数(取得)

	// メンバ関数(設定)

private:	// 自分だけがアクセス可能

	// メンバ関数

	// メンバ変数
};

#endif

