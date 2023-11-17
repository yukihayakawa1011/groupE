//===============================================
//
// 数字全般の処理 [score.h]
// Author : Ryosuke Ohhara
//
//===============================================
#ifndef _SCORE_H_		// このマクロが定義されていない場合
#define _SCORE_H_		// 二重インクルード防止用マクロを定義

#include "main.h"
#include "number.h"

//マクロ定義
#define NUM_SCORE   (8)  // スコアの桁数

//===============================================
// ナンバークラスの定義
//===============================================
class CScore : public CNumber
{
public:	// 誰でもアクセス可能

	CScore();	// コンストラクタ
	~CScore();	// デストラクタ

	// メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CScore *Create(void);
	static CScore *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
	CNumber *GetObject2D(void) { return m_apNumber[0]; }
	void PolygonDelete(void);

	// メンバ関数(設定)
	void SetIdx(const int nIdx);

	// メンバ関数(取得)
	int GetIdx(void) { return m_nIdx; }

private:	// 自分だけがアクセス可能

	// メンバ変数
	CNumber *m_apNumber[NUM_SCORE];	// 2Dオブジェクトのポインタ
	int m_nIdx;	// 数字の番号
};

#endif