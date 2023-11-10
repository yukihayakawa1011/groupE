//===============================================
//
// 敵の処理 [enemy.cpp]
// Author : Soma Ishihara (Base:Ibuki Okusada)
//
//===============================================
#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
#include "camera.h"
#include "Xfile.h"
#include "slow.h"
#include "texture.h"
#include "meshfield.h"
#include "Xfile.h"
#include "meshorbit.h"
#include "game.h"
#include "filter.h"
#include "object2D.h"
#include "meshwall.h"
#include "objectX.h"
#include "sound.h"
#include <assert.h>
#include "billboard.h"
#include "character.h"
#include "motion.h"
#include "sound.h"
#include "player.h"
#include "item.h"

//===============================================
// マクロ定義
//===============================================
#define MOVE	(2.0f)		// 移動量
#define ENEMY_GRAVITY	(-0.9f)		//敵重力
#define ENEMY_JUMP		(25.0f)		//敵ジャンプ力
#define ROT_MULTI	(0.1f)	// 向き補正倍率
#define WIDTH	(20.0f)		// 幅
#define HEIGHT	(80.0f)	// 高さ
#define INER	(0.3f)		// 慣性
#define START_LIFE	(4)	// 初期体力
#define DAMAGE_INTERVAL	(10)
#define DEFAULT_ROTATE	(0.1f)		//プレイヤー探索中の回転量
#define SEARCH_LENGTH	(500.0f)	//プレイヤー探索範囲
#define CHACE_LENGTH	(800.0f)	//追跡範囲
#define ATTACK_LENGTH	(50.0f)		//攻撃モードにする範囲
#define ATTACK_COOLTIME	(60)		//攻撃クールタイム
#define ENEMY_VTX_MIN	D3DXVECTOR3(-20.0f,0.0f,-20.0f)
#define ENEMY_VTX_MAX	D3DXVECTOR3(20.0f,0.0f,20.0f)

#define FIX_ROT(x)				(fmodf(x + (D3DX_PI * 3), D3DX_PI * 2) - D3DX_PI)	//角度を-PI~PIに修正
#define MINUS_GUARD(x)			((x < 0) ? 0 : x)

// 前方宣言
CEnemy *CEnemy::m_pTop = NULL;	// 先頭のオブジェクトへのポインタ
CEnemy *CEnemy::m_pCur = NULL;	// 最後尾のオブジェクトへのポインタ
int CEnemy::m_nNumCount = 0;

//===============================================
// コンストラクタ(オーバーロード)
//===============================================
CEnemy::CEnemy(const D3DXVECTOR3 pos)
{
	// 値をクリアする
	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fRotMove = 0.0f;
	m_fRotDiff = 0.0f;
	m_fRotDest = 0.0f;
	m_pObject = NULL;
	m_nLife = 0;
	m_nCounterAttack = ATTACK_COOLTIME;
	m_bChace = false;
	m_bJump = false;
	m_type = TYPE_NONE;
	m_nId = m_nNumCount;

	// 自分自身をリストに追加
	if (m_pTop != NULL)
	{// 先頭が存在している場合
		m_pCur->m_pNext = this;	// 現在最後尾のオブジェクトのポインタにつなげる
		m_pPrev = m_pCur;
		m_pCur = this;	// 自分自身が最後尾になる
	}
	else
	{// 存在しない場合
		m_pTop = this;	// 自分自身が先頭になる
		m_pCur = this;	// 自分自身が最後尾になる
	}

	m_nNumCount++;
}

//===============================================
// コンストラクタ(オーバーロード)
//===============================================
CEnemy::CEnemy(int nPriOrity)
{
	// 値をクリアする
	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fRotMove = 0.0f;
	m_fRotDiff = 0.0f;
	m_fRotDest = 0.0f;
	m_pObject = NULL;
	m_nLife = 0;
	m_nCounterAttack = ATTACK_COOLTIME;
	m_bChace = false;
	m_bJump = false;
	m_type = TYPE_NONE;
	m_nId = m_nNumCount;

	// 自分自身をリストに追加
	if (m_pTop != NULL)
	{// 先頭が存在している場合
		m_pCur->m_pNext = this;	// 現在最後尾のオブジェクトのポインタにつなげる
		m_pPrev = m_pCur;
		m_pCur = this;	// 自分自身が最後尾になる
	}
	else
	{// 存在しない場合
		m_pTop = this;	// 自分自身が先頭になる
		m_pCur = this;	// 自分自身が最後尾になる
	}

	m_nNumCount++;
}

//===============================================
// デストラクタ
//===============================================
CEnemy::~CEnemy()
{
	
}

//===============================================
// 初期化処理
//===============================================
HRESULT CEnemy::Init(void)
{
	if (nullptr == m_pObject)
	{
		m_pObject = CCharacter::Create(GetPosition(), GetRotation(), "data\\TXT\\motion_kidsboy.txt");
		m_pObject->SetShadow(true);
	}

	m_Info.state = STATE_APPEAR;
	m_type = TYPE_NONE;
	m_nLife = START_LIFE;

	return S_OK;
}

//===============================================
// 初期化処理(オーバーロード)
//===============================================
HRESULT CEnemy::Init(const char *pBodyName, const char *pLegName)
{
	if (nullptr == m_pObject)
	{
		m_pObject = CCharacter::Create("data\\TXT\\motion_kidsboy.txt");
		m_pObject->GetMotion()->InitSet(0);
		m_pObject->SetShadow(true);
		m_pObject->SetDraw();
	}

	m_nLife = START_LIFE;
	m_type = TYPE_NONE;

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CEnemy::Uninit(void)
{
	// リストから自分自身を削除する
	if (m_pTop == this)
	{// 自身が先頭
		if (m_pNext != NULL)
		{// 次が存在している
			m_pTop = m_pNext;	// 次を先頭にする
			m_pNext->m_pPrev = NULL;	// 次の前のポインタを覚えていないようにする
		}
		else
		{// 存在していない
			m_pTop = NULL;	// 先頭がない状態にする
			m_pCur = NULL;	// 最後尾がない状態にする
		}
	}
	else if (m_pCur == this)
	{// 自身が最後尾
		if (m_pPrev != NULL)
		{// 次が存在している
			m_pCur = m_pPrev;			// 前を最後尾にする
			m_pPrev->m_pNext = NULL;	// 前の次のポインタを覚えていないようにする
		}
		else
		{// 存在していない
			m_pTop = NULL;	// 先頭がない状態にする
			m_pCur = NULL;	// 最後尾がない状態にする
		}
	}
	else
	{
		if (m_pNext != NULL)
		{
			m_pNext->m_pPrev = m_pPrev;	// 自身の次に前のポインタを覚えさせる
		}
		if (m_pPrev != NULL)
		{
			m_pPrev->m_pNext = m_pNext;	// 自身の前に次のポインタを覚えさせる
		}
	}

	if (nullptr != m_pObject){
		m_pObject->Uninit();
		m_pObject = NULL;
	}

	if (m_pObject != NULL)
	{
		m_pObject->Uninit();
		delete m_pObject;
		m_pObject = NULL;
	}

	m_nNumCount--;

	// 廃棄
	Release();
}

//===============================================
// 更新処理
//===============================================
void CEnemy::Update(void)
{
	// 前回の座標を取得
	m_Info.posOld = GetPosition();

	StateSet();

	m_nCounterAttack--;

	if (m_Info.state != STATE_SPAWN)
	{
		// 敵操作
		Controller();
	}

	//// カメラ追従
	//CCamera* pCamera = CManager::GetInstance()->GetCamera();

	//// 追従処理
	//pCamera->Pursue(GetPosition(), GetRotation());

#ifdef _DEBUG	//デバッグモードのみ表示

	CManager::GetInstance()->GetDebugProc()->Print("向き [%f, %f, %f] : ID [ %d]\n", GetRotation().x, GetRotation().y, GetRotation().z, m_nId);
	CManager::GetInstance()->GetDebugProc()->Print("位置 [%f, %f, %f]", GetPosition().x, GetPosition().y, GetPosition().z);
	CManager::GetInstance()->GetDebugProc()->Print("体力 [ %d ]\n", m_nLife);

#endif // _DEBUG

	// 使用オブジェクト更新
	if (nullptr != m_pObject) {
		m_pObject->SetPosition(m_Info.pos);
		m_pObject->SetRotation(m_Info.rot);
		m_pObject->Update();
	}
}

//===============================================
// 生成
//===============================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, const char *pBodyName, const char *pLegName, const int nPriority)
{
	CEnemy *pPlayer = NULL;
	CXFile *pModelFile = CManager::GetInstance()->GetModelFile();

	// 敵の生成
	pPlayer = new CEnemy(nPriority);

	if (nullptr != pPlayer)
	{// 生成できた場合
		// 初期化処理
		pPlayer->Init(pBodyName, pLegName);

		// 座標設定
		pPlayer->SetPosition(pos);

		// 向き設定
		pPlayer->SetRotation(rot);

		pPlayer->m_fRotDest = rot.y;

		// 移動量設定
		pPlayer->SetMove(move);
	}
	else
	{// 生成に失敗した場合
		return NULL;
	}

	return pPlayer;
}

//===============================================
// 操作処理
//===============================================
void CEnemy::Controller(void)
{
	D3DXVECTOR3 pos = GetPosition();	// 座標を取得
	D3DXVECTOR3 rot = GetRotation();	// 向きを取得
	m_fRotMove = rot.y;	//現在の向きを取得

	// 操作処理
	{
		Move();		// 移動

		if (m_bChace == false)
		{
			Search();	// 探索
		}
		else
		{
			Chace();	// 追跡
		}
	}

	pos = GetPosition();	// 座標を取得

	float fGravity = ENEMY_GRAVITY * CManager::GetInstance()->GetSlow()->Get();
	m_Info.move.y += fGravity;
	pos.y += m_Info.move.y * CManager::GetInstance()->GetSlow()->Get();

	m_Info.move.x += (0.0f - m_Info.move.x) * INER;	//x座標
	m_Info.move.z += (0.0f - m_Info.move.z) * INER;	//x座標

	pos.x += m_Info.move.x * CManager::GetInstance()->GetSlow()->Get();
	pos.z += m_Info.move.z * CManager::GetInstance()->GetSlow()->Get();

	// 調整
	Adjust();

	m_Info.pos = pos;
	m_bJump = true;

	// 起伏との当たり判定
	float fHeight = CMeshField::GetHeight(m_Info.pos);
	if (m_Info.pos.y <= fHeight)
	{
		m_Info.pos.y = fHeight;
		m_bJump = false;
	}

	//当たり判定処理前の位置記憶
	pos = m_Info.pos;

	D3DXVECTOR3 vtxMax = D3DXVECTOR3(50.0f, 0.0f, 50.0f);
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);
	if (CObjectX::Collision(m_Info.pos, m_Info.posOld, m_Info.move, vtxMin, vtxMax, 0.3f))
	{
		m_bJump = false;
	}
	this->Collision();

	//追跡モードでかつxzどちらか処理前から変化している
	if (m_bChace == true && (m_Info.pos.x != pos.x || m_Info.pos.z != pos.z))
	{
		//ジャンプする必要があるか確認
		CPlayer* pPlayerNear = SearchNearPlayer();

		if (CObjectX::CollisionCloss(pPlayerNear->GetPosition(), m_Info.pos))
		{
			m_Info.move.y = ENEMY_JUMP;
			m_bJump = true;
		}
	}
}

//===============================================
// 移動
//===============================================
void CEnemy::Move(void)
{
	//敵の更新
	m_Info.move.x += sinf(m_fRotDest - D3DX_PI) * MOVE;
	m_Info.move.z += cosf(m_fRotDest - D3DX_PI) * MOVE;
}

//===============================================
// 回転
//===============================================
void CEnemy::Rotation(void)
{
	m_fRotDest = m_fRotMove - DEFAULT_ROTATE;
}

//===============================================
// 探索
//===============================================
void CEnemy::Search(void)
{
	float fLengthNear = FLT_MAX;
	CPlayer* pPlayerNear = SearchNearPlayer(&fLengthNear);

	if (pPlayerNear != nullptr && fLengthNear <= SEARCH_LENGTH)
	{//プレイヤー見つけた
		m_bChace = true;
	}
	else
	{//適当にぐるぐる
		Rotation();	// 回転
	}
}

//===============================================
// 追跡
//===============================================
void CEnemy::Chace(void)
{
	float fLengthNear = FLT_MAX;
	CPlayer* pPlayerNear = SearchNearPlayer(&fLengthNear);

	if (pPlayerNear != nullptr && fLengthNear <= ATTACK_LENGTH)
	{//攻撃範囲
		m_Info.move.x = 0.0f;
		m_Info.move.z = 0.0f;
		if (m_nCounterAttack <= 0)
		{//クールタイム終了
			pPlayerNear->Damage(1);
			m_nCounterAttack = ATTACK_COOLTIME;
		}
	}
	else if (pPlayerNear != nullptr && fLengthNear <= CHACE_LENGTH)
	{//追跡範囲
		D3DXVECTOR3 posPlayer = pPlayerNear->GetPosition();
		float aaa = atan2f(posPlayer.x - m_Info.pos.x, posPlayer.z - m_Info.pos.z);
		m_fRotDest = FIX_ROT(atan2f(posPlayer.x - m_Info.pos.x, posPlayer.z - m_Info.pos.z) + D3DX_PI);
	}
	else
	{
		m_bChace = false;
	}
}

//===============================================
// 死亡処理
//===============================================
void CEnemy::Death(void)
{
	// 落とした分生成（playerから拝借）
	for (int nCnt = 0; nCnt < 5; nCnt++)	//回数仮
	{
		CItem *pItem = CItem::Create(m_Info.pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\coin.x", CItem::TYPE_DROP);

		if (nullptr != pItem)
		{
			D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//移動量の設定
			move.x = sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.04f;
			move.y = 18.0f;
			move.z = cosf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.04f;
			pItem->SetMove(move);
		}
	}

	//自滅
	Uninit();
}

//===============================================
// 敵同士当たり判定
//===============================================
void CEnemy::Collision(void)
{
	CEnemy *pObj = m_pTop;	// 先頭取得
	CXFile *pFile = CManager::GetInstance()->GetModelFile();
	bool bLand = false;	// 着地したか否か

	//仮置き
	D3DXVECTOR3 posTemp = m_Info.posOld;

	//X
	posTemp.x = m_Info.pos.x;
	pObj = m_pTop;
	while (pObj != NULL)
	{
		CEnemy *pObjNext = pObj->m_pNext;
		if (pObj != this)
		{
			pObj->CollisionCheck(posTemp, m_Info.posOld, m_Info.move, ENEMY_VTX_MIN, ENEMY_VTX_MAX);
		}

		pObj = pObjNext;
	}

	//Y
	posTemp.y = m_Info.pos.y;
	pObj = m_pTop;
	while (pObj != NULL)
	{
		CEnemy* pObjNext = pObj->m_pNext;
		if (pObj != this)
		{
			pObj->CollisionCheck(posTemp, m_Info.posOld, m_Info.move, ENEMY_VTX_MIN, ENEMY_VTX_MAX);
		}

		pObj = pObjNext;
	}

	//Z
	posTemp.z = m_Info.pos.z;
	pObj = m_pTop;
	while (pObj != NULL)
	{
		CEnemy* pObjNext = pObj->m_pNext;
		if (pObj != this)
		{
			pObj->CollisionCheck(posTemp, m_Info.posOld, m_Info.move, ENEMY_VTX_MIN, ENEMY_VTX_MAX);
		}

		pObj = pObjNext;
	}

	m_Info.pos = posTemp;
}

//===============================================
// 敵単体当たり判定
//===============================================
void CEnemy::CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, const float fRefMulti)
{
	//X
	if (pos.z + vtxMax.z > m_Info.pos.z + vtxMin.z
		&& pos.z + vtxMin.z < m_Info.pos.z + vtxMax.z)
	{//範囲内にある
		if (posOld.x + vtxMin.x >= m_Info.pos.x + vtxMax.x
			&& pos.x + vtxMin.x < m_Info.pos.x + vtxMax.x)
		{//右から左にめり込んだ
			move.x *= -1.0f;
			move.x *= fRefMulti;
			pos.x = m_Info.pos.x + vtxMax.x - vtxMin.x + 0.1f + move.x;
		}
		else if (posOld.x + vtxMax.x <= m_Info.pos.x + vtxMin.x
			&& pos.x + vtxMax.x > m_Info.pos.x + vtxMin.x)
		{//左から右にめり込んだ
		 //位置を戻す
			move.x *= -1.0f;
			move.x *= fRefMulti;
			pos.x = m_Info.pos.x + vtxMin.x - vtxMax.x - 0.1f + move.x;
		}
	}

	//Z
	if (pos.x + vtxMax.x > m_Info.pos.x + vtxMin.x
		&& pos.x + vtxMin.x < m_Info.pos.x + vtxMax.x)
	{//範囲内にある
		if (posOld.z + vtxMin.z >= m_Info.pos.z + vtxMax.z
			&& pos.z + vtxMin.z < m_Info.pos.z + vtxMax.z)
		{//奥から手前にめり込んだ
		 //位置を戻す
			move.z *= -1.0f;
			move.z *= fRefMulti;
			pos.z = m_Info.pos.z + vtxMax.z - vtxMin.z + 0.1f + move.z;
		}
		else if (posOld.z + vtxMax.z <= m_Info.pos.z + vtxMin.z
			&& pos.z + vtxMax.z > m_Info.pos.z + vtxMin.z)
		{//手前から奥にめり込んだ
		 //位置を戻す
			move.z *= -1.0f;
			move.z *= fRefMulti;
			pos.z = m_Info.pos.z + vtxMin.z - vtxMax.z - 0.1f + move.z;
		}
	}
}

//===============================================
// 近いプレイヤー探索
//===============================================
CPlayer* CEnemy::SearchNearPlayer(float* pLength)
{
	CPlayer* pPlayer = CPlayer::GetTop();
	CPlayer* pPlayerNear = nullptr;
	float fLengthNear = FLT_MAX;

	while (pPlayer != nullptr)
	{
		if (pPlayer->GetLife() > 0)
		{//生きている奴を計測
			D3DXVECTOR3 posPlayer = pPlayer->GetPosition();
			float fLength = D3DXVec3Length(&(posPlayer - this->m_Info.pos));
			if (fLengthNear > fLength)
			{//一番近いやつ
				pPlayerNear = pPlayer;
				fLengthNear = fLength;
			}
		}

		pPlayer = pPlayer->GetNext();
	}

	if (pLength != nullptr)
	{//距離も欲しい
		*pLength = fLengthNear;
	}

	return pPlayerNear;	//近いプレイヤーのポインタを返す
}

//===============================================
// 調整
//===============================================
void CEnemy::Adjust(void)
{
	m_fRotDest = FIX_ROT(m_fRotDest);

	m_fRotDiff = m_fRotDest - m_fRotMove;	//目標までの移動方向の差分
	m_fRotDiff = FIX_ROT(m_fRotDiff);

	m_Info.rot.y += m_fRotDiff * ROT_MULTI;
	m_Info.rot.y = FIX_ROT(m_Info.rot.y);
}

//===============================================
// 状態管理
//===============================================
void CEnemy::StateSet(void)
{
	switch (m_Info.state)
	{
	case STATE_APPEAR:
	{

	}
		break;

	case STATE_NORMAL:
	{

	}
		break;

	case STATE_DAMAGE:
	{

	}
		break;

	case STATE_DEATH:
	{

	}
		break;

	case STATE_SPAWN:
	{

	}
		break;
	}
}

//===============================================
// ダメージ処理
//===============================================
void CEnemy::Damage(int nDamage) 
{ 
	int nOldLife = m_nLife;
	m_nLife = MINUS_GUARD(m_nLife - nDamage);

	if (m_nLife <= 0)
	{//死
		Death();
	}

	if (m_nLife != nOldLife)
	{
		m_Info.nStateCounter = DAMAGE_INTERVAL;
		m_Info.state = STATE_DAMAGE;
	}
}

//===============================================
// 体力設定
//===============================================
void CEnemy::SetLife(int nLife)
{
	m_nLife = MINUS_GUARD(nLife);
}