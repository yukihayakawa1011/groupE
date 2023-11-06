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
#define STEP_SPEED	(50.0f)
#define STEP_COOLTIME	(90.0f)
#define START_LIFE	(4)	// 初期体力
#define DAMAGE_INTERVAL	(10.0f)
#define DAMAGE_APPEAR	(110.0f)
#define DEATH_INTERVAL	(120.0f)
#define DASH_INTERVAL	(60.0f)
#define SPAWN_INTERVAL	(60.0f)
#define PARTICLE_TIMER	 (5.0f)
#define SHADOW_ALPHA	(0.4f)
#define DEFAULT_ROTATE	(0.1f)		//プレイヤー探索中の回転量
#define SEARCH_LENGTH	(200.0f)	//プレイヤー探索範囲

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

	if (m_type == TYPE_SEND)
	{
		CManager::GetInstance()->GetCamera()->Setting(m_Info.pos, m_Info.rot);
		CManager::GetInstance()->GetScene()->SendPosition(m_Info.pos);
		CManager::GetInstance()->GetScene()->SendRotation(m_Info.rot);
		CManager::GetInstance()->GetScene()->SendLife(m_nLife);
	}

	if (m_type == TYPE_ACTIVE)
	{

		if (m_Info.state != STATE_SPAWN)
		{
			// 敵操作
			Controller();
		}

		// カメラ追従
		CCamera *pCamera = CManager::GetInstance()->GetCamera();

		// 追従処理
		pCamera->Pursue(GetPosition(), GetRotation());

		// オンライン送信
		CManager::GetInstance()->GetScene()->SendPosition(m_Info.pos);
		CManager::GetInstance()->GetScene()->SendRotation(m_Info.rot);
		CManager::GetInstance()->GetScene()->SendLife(m_nLife);
	}
	else
	{// 操作キャラではない
		D3DXVECTOR3 posDest = m_Info.posDiff - m_Info.pos;
		m_Info.pos += posDest * 0.95f;
	}

	CManager::GetInstance()->GetDebugProc()->Print("向き [%f, %f, %f] : ID [ %d]\n", GetRotation().x, GetRotation().y, GetRotation().z, m_nId);
	CManager::GetInstance()->GetDebugProc()->Print("位置 [%f, %f, %f]", GetPosition().x, GetPosition().y, GetPosition().z);
	CManager::GetInstance()->GetDebugProc()->Print("体力 [ %d ]\n", m_nLife);

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
		Search();	// 探索
		Move();		// 移動
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
	m_Info.move.x += cosf(CamRot.y + (-m_fRotMove)) * fSpeed;
	m_Info.move.z += sinf(CamRot.y + (-m_fRotMove)) * fSpeed;
}

//===============================================
// 回転
//===============================================
void CEnemy::Rotation(void)
{
	CCamera *pCamera = CManager::GetInstance()->GetCamera();		// カメラのポインタ
	D3DXVECTOR3 CamRot = pCamera->GetRotation();	// カメラの角度

	m_fRotDest = m_fRotMove + DEFAULT_ROTATE;
}

//===============================================
// 探索
//===============================================
void CEnemy::Search(void)
{
	CPlayer* pPlayer = CPlayer::GetTop();
	CPlayer* pPlayerNear = nullptr;
	float fLengthNear = FLT_MAX;

	while (pPlayer != nullptr)
	{
		D3DXVECTOR3 posPlayer = pPlayer->GetPosition();
		float fLength = D3DXVec3Length(&(posPlayer - this->m_Info.pos));
		if (fLength <= SEARCH_LENGTH && fLengthNear > fLength)
		{//一番近いやつ
			pPlayerNear = pPlayer;
			fLengthNear = fLength;
		}

		pPlayer = pPlayer->GetNext();
	}

	if (pPlayerNear != nullptr)
	{//プレイヤー見つけた
		D3DXVECTOR3 posPlayer = pPlayerNear->GetPosition();
		m_fRotDest = atan2f(m_Info.pos.x - posPlayer.x, m_Info.pos.z - posPlayer.z);
	}
	else
	{//適当にぐるぐる
		Rotation();	// 回転
	}
}

//===============================================
// 調整
//===============================================
void CEnemy::Adjust(void)
{
	while (1)
	{
		if (m_fRotDest > D3DX_PI || m_fRotDest < -D3DX_PI)
		{//-3.14～3.14の範囲外の場合
			if (m_fRotDest > D3DX_PI)
			{
				m_fRotDest += (-D3DX_PI * 2);
			}
			else if (m_fRotDest < -D3DX_PI)
			{
				m_fRotDest += (D3DX_PI * 2);
			}
		}
		else
		{
			break;
		}
	}

	m_fRotDiff = m_fRotDest - m_fRotMove;	//目標までの移動方向の差分

	while (1)
	{
		if (m_fRotDiff > D3DX_PI || m_fRotDiff < -D3DX_PI)
		{//-3.14～3.14の範囲外の場合
			if (m_fRotDiff > D3DX_PI)
			{
				m_fRotDiff += (-D3DX_PI * 2);
			}
			else if (m_fRotDiff < -D3DX_PI)
			{
				m_fRotDiff += (D3DX_PI * 2);
			}
		}
		else
		{
			break;
		}
	}

	m_Info.rot.y += m_fRotDiff * ROT_MULTI;

	while (1)
	{
		if (m_Info.rot.y > D3DX_PI || m_Info.rot.y < -D3DX_PI)
		{//-3.14～3.14の範囲外の場合
			if (m_Info.rot.y > D3DX_PI)
			{
				m_Info.rot.y += (-D3DX_PI * 2);
			}
			else if (m_Info.rot.y < -D3DX_PI)
			{
				m_Info.rot.y += (D3DX_PI * 2);
			}
		}
		else
		{
			break;
		}
	}
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
		m_Info.fStateCounter = DAMAGE_INTERVAL;
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
