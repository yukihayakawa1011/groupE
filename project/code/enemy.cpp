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

//===============================================
// マクロ定義
//===============================================
#define MOVE	(2.0f)		// 移動量
#define PLAYER_GRAVITY	(-0.15f)		//敵重力
#define PLAYER_JUMP		(10.0f)		//敵ジャンプ力
#define ROT_MULTI	(0.1f)	// 向き補正倍率
#define WIDTH	(20.0f)		// 幅
#define HEIGHT	(80.0f)	// 高さ
#define INER	(0.3f)		// 慣性
#define START_LIFE	(4)	// 初期体力
#define DAMAGE_INTERVAL	(10)
#define DEFAULT_ROTATE	(0.1f)		//プレイヤー探索中の回転量
#define SEARCH_LENGTH	(200.0f)	//プレイヤー探索範囲
#define ATTACK_LENGTH	(50.0f)		//攻撃モードにする範囲
#define ATTACK_COOLTIME	(60)		//攻撃クールタイム

#define FIX_ROT(x)				(fmodf(x + (D3DX_PI * 3), D3DX_PI * 2) - D3DX_PI)	//角度を-PI~PIに修正

// 前方宣言
CEnemy *CEnemy::m_pTop = NULL;	// 先頭のオブジェクトへのポインタ
CEnemy *CEnemy::m_pCur = NULL;	// 最後尾のオブジェクトへのポインタ
int CEnemy::m_nNumCount = 0;

//===============================================
// コンストラクタ
//===============================================
//CEnemy::CEnemy()
//{
//	// 値をクリアする
//	m_nCounterAnim = 0;
//	m_nPatternAnim = 0;
//}

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

	// カメラ追従
	CCamera* pCamera = CManager::GetInstance()->GetCamera();

	// 追従処理
	pCamera->Pursue(GetPosition(), GetRotation());

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

	// 起伏との当たり判定
	D3DXVECTOR3 nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float fHeight = CMeshField::GetHeight(m_Info.pos);
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
		Search();	// 探索
	}

	pos = GetPosition();	// 座標を取得

	m_Info.move.x += (0.0f - m_Info.move.x) * INER;	//x座標
	m_Info.move.z += (0.0f - m_Info.move.z) * INER;	//x座標

	pos.x += m_Info.move.x * CManager::GetInstance()->GetSlow()->Get();
	pos.z += m_Info.move.z * CManager::GetInstance()->GetSlow()->Get();

	// 調整
	Adjust();

	m_Info.pos = pos;
}

//===============================================
// 移動
//===============================================
void CEnemy::Move(void)
{
	CCamera *pCamera = CManager::GetInstance()->GetCamera();		// カメラのポインタ
	D3DXVECTOR3 CamRot = pCamera->GetRotation();	// カメラの角度
	float fSpeed = MOVE;	// 移動量

	//敵の更新
	m_Info.move.x += -sinf(CamRot.y - m_fRotMove) * fSpeed;
	m_Info.move.z += cosf(CamRot.y - m_fRotMove) * fSpeed;
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
		else
		{//追跡範囲
			D3DXVECTOR3 posPlayer = pPlayerNear->GetPosition();
			m_fRotDest = atan2f(m_Info.pos.x - posPlayer.x, m_Info.pos.z - posPlayer.z);
		}
	}
	else
	{//適当にぐるぐる
		Rotation();	// 回転
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
		D3DXVECTOR3 posPlayer = pPlayer->GetPosition();
		float fLength = D3DXVec3Length(&(posPlayer - this->m_Info.pos));
		if (fLengthNear > fLength)
		{//一番近いやつ
			pPlayerNear = pPlayer;
			fLengthNear = fLength;
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
	m_nLife -= nDamage;

	if (m_nLife < 0)
	{
		m_nLife = 0;
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
	m_nLife = nLife;

	if (m_nLife < 0)
	{
		m_nLife = 0;
	}
}

//===============================================
// 体力設定
//===============================================
void CEnemy::SetType(TYPE type)
{
	m_type = type;
}
