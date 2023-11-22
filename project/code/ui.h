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

	enum TYPE
	{
		TYPE_NORMAL = 0,	// なんもない
		TYPE_LEFTUP,		// 左上
		TYPE_RIGHTUP,		// 右上
		TYPE_LEFTDOWN,		// 左下
		TYPE_RIGHTDOWN,		// 右下
		TYPE_MAX
	};

	CUI();	// コンストラクタ(オーバーロード)
	~CUI();	// デストラクタ

					// メンバ関数
	HRESULT Init(void);
	HRESULT Init(const char *pFileFrameName, const char *pFilePIconName);
	void Uninit(void);
	void Update(void);
	static CUI *Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot, const char *pFileFrameName, const char *pFilePIconName,TYPE type);

	// メンバ関数(取得)
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	TYPE GetType(void) { return m_type; }

	// メンバ関数(設定)
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetType(TYPE type) { m_type = type; }

private:	// 自分だけがアクセス可能

	#define NUM_OBJ			(3)			//オブジェクトの数

			// メンバ関数

			// メンバ変数
	CObject2D *m_pObject[NUM_OBJ];
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	TYPE m_type;

};

#endif


