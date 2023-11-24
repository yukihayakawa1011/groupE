//===============================================
//
// ミニマップの処理 [minimap.h]
// Author : Soma Ishihara
//
//===============================================
#ifndef _MINIMAP_H_
#define _MINIMAP_H_

#define TEST_WIDTH		(256)
#define TEST_HEIGHT		(144)

//前方宣言
class CMultiCamera;

//ミニマップクラス（結構特殊のためいったん継承なし）
class CMiniMap
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
	void DrawMap(void);
	void DrawTexture(void);
	static void Load(void);		//デバイスロスト対策：ロスト解消したら呼び出してね。初期化にも使える。
	static void UnLoad(void);	//デバイスロスト対策：ロストしたら呼び出してね
	static void Reset(void);	//まっくろくろすけにして探索してないことにする。初期化にどうぞ

	//マップポリゴンの設定・取得処理
	void SetPosition(const D3DXVECTOR3 pos);
	void SetRotation(const D3DXVECTOR3 rot);
	void SetSize(float fWidth, float fHeight);

	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	float GetWidth(void) { return m_fWidth; }
	float GetHeight(void) { return m_fHeight; }

	void SetpVtx(const int nChangeVtx);

private:
	//メンバ関数
	void CulcDiagonal(void);

	// メンバ変数
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// 頂点バッファへのポインタ
	static LPDIRECT3DTEXTURE9 m_pTextureMap;	// テクスチャ
	static LPDIRECT3DTEXTURE9 m_pTextureUnex;	// 未探索場所を黒くしたテクスチャ
	static LPDIRECT3DSURFACE9 m_pZSurface;		// テクスチャの深度バッファ
	static bool m_bExplored[TEST_WIDTH][TEST_HEIGHT];
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_rot;	// 向き
	float m_fLength;	// 対角線の長さ
	float m_fAngle;		// 対角線の角度
	float m_fWidth;		// 幅
	float m_fHeight;	// 高さ
};

#endif // !_MINIMAP_H_
