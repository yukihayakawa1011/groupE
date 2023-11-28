//===============================================
//
// ミニマップの処理 [minimap.h]
// Author : Soma Ishihara
//
//===============================================
#ifndef _MINIMAP_H_
#define _MINIMAP_H_

#include "task.h"
#include "object2DMap.h"
#include "input.h"

//前方宣言
class CMultiCamera;
class CObject2D;
class CObject2DMap;

//ミニマップクラス
class CMiniMap : public CTask
{
public:
	//頂点変更種類列挙（複数使用時AND演算して入れて）
	enum CHANGE
	{
		CHANGE_POS = 0b0001,
		CHANGE_RHW = 0b0010,
		CHANGE_COL = 0b0100,
		CHANGE_TEX = 0b1000,
		CHANGE_ALL = 0b1111
	};

	//コンストラクタ・デストラクタ
	CMiniMap();
	~CMiniMap();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void){}
	void DrawTexture(void);
	void Load(void);		//デバイスロスト対策：ロスト解消したら呼び出してね。初期化にも使える。
	void UnLoad(void);	//デバイスロスト対策：ロストしたら呼び出してね。終了にも使える。
	void Reset(void);	//まっくろくろすけにして探索してないことにする。初期化にどうぞ

	static CMiniMap* Create(const D3DXVECTOR3 posMap, const D3DXVECTOR3 rotMap, const float width, const float height, const int playerNum, 
		const int elaseWidth,const int elaseHeight);

	//マップポリゴンの設定・取得処理
	void SetPosition(const D3DXVECTOR3 pos){ m_pos = pos; }

	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_pObjMap->GetRotation(); }
	float GetWidth(void) { return m_fWidth; }
	float GetHeight(void) { return m_fHeight; }

private:
	// メンバ変数
	LPDIRECT3DTEXTURE9 m_pTextureMap;	// テクスチャ
	LPDIRECT3DTEXTURE9 m_pTextureUnex;	// 未探索場所を黒くしたテクスチャ
	LPDIRECT3DSURFACE9 m_pZSurface;		// テクスチャの深度バッファ
	CObject2DMap* m_pObjMap;			//マップオブジェ
	CObject2D** m_ppPlayerIcon;
	bool** m_ppExplored;//探索済みドット
	D3DXVECTOR3 m_pos;	// 位置
	float m_fWidth;		// 幅
	float m_fHeight;	// 高さ
	int m_nElaseWidth;	//探索済みにする幅
	int m_nElaseHeight;	//探索済みにする高さ
	int m_nPlayerNum;	//プレイヤー人数分
};

#endif // !_MINIMAP_H_
