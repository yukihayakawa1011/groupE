//==========================================================
//
// アイテムボックス [itembox.h]
// Author : Soma Ishihara
//
//==========================================================
#ifndef _ITEMBOX_H_		// このマクロが定義されていない場合
#define _ITEMBOX_H_		// 二重インクルード防止用マクロを定義

#include "task.h"

//==========================================================
// サンプルのクラス定義
//==========================================================
class CItemBox : public CTask
{
public:	// 誰でもアクセス可能

	CItemBox();	// コンストラクタ(オーバーロード)
	~CItemBox();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CItemBox *Create(void);
	void Emission(void);

	// メンバ関数(取得)
	static CItemBox* GetTop(void) { return m_pTop; }
	CItemBox* GetNext(void) { return m_pNext; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }

	// メンバ関数(設定)

private:	// 自分だけがアクセス可能

	// メンバ関数

	// メンバ変数
	static CItemBox *m_pTop;	// 先頭のオブジェクトへのポインタ
	static CItemBox *m_pCur;	// 最後尾のオブジェクトへのポインタ
	CItemBox *m_pPrev;			// 前のオブジェクトへのポインタ
	CItemBox *m_pNext;			// 次のオブジェクトへのポインタ
	D3DXVECTOR3 m_pos;			// 位置
	D3DXVECTOR3 m_rot;			// 向き
};

#endif

