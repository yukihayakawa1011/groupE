//===============================================
//
// プレイヤーの処理 [player.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "player.h"
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
#include "waist.h"
#include "model.h"
#include "item.h"
#include "gimmick.h"
#include "gimmick_rotatedoor.h"
#include "enemy.h"
#include "goal.h"
#include "score.h"

//===============================================
// マクロ定義
//===============================================
#define MOVE	(4.0f)		// 移動量
#define GRAVITY	(-1.0f)		//プレイヤー重力
#define ROT_MULTI	(0.1f)	// 向き補正倍率
#define WIDTH	(20.0f)		// 幅
#define HEIGHT	(80.0f)	// 高さ
#define INER	(0.3f)		// 慣性
#define STEP_SPEED	(50.0f)
#define STEP_COOLTIME	(90.0f)
#define START_LIFE	(6)	// 初期体力
#define DAMAGE_INTERVAL	(10.0f)
#define DAMAGE_APPEAR	(110.0f)
#define DEATH_INTERVAL	(120.0f)
#define DASH_INTERVAL	(60.0f)
#define SPAWN_INTERVAL	(60.0f)
#define PARTICLE_TIMER	 (5.0f)
#define SHADOW_ALPHA	(0.4f)
#define JUMP	(25.0f)
#define ATK_RANGE	(50.0f)
#define CATCH_RANGE	(100.0f)
#define DROP_CNT	(4)
#define START_COIN	(10)
#define CATCH_LIMIT	(90)
#define CATCH_MOVE	(2.0f)
#define SPEED_DECAY (0.1f)  // 持っているアイテムの数に応じてスピードが下がる
#define HAND_PARTS	(4)	 // 手のモデル番号(後ろから

// 前方宣言
CPlayer *CPlayer::m_pTop = nullptr;	// 先頭のオブジェクトへのポインタ
CPlayer *CPlayer::m_pCur = nullptr;	// 最後尾のオブジェクトへのポインタ
int CPlayer::m_nNumCount = 0;

//===============================================
// コンストラクタ
//===============================================
//CPlayer::CPlayer()
//{
//	// 値をクリアする
//	m_nCounterAnim = 0;
//	m_nPatternAnim = 0;
//}

//===============================================
// コンストラクタ(オーバーロード)
//===============================================
CPlayer::CPlayer()
{
	// 値をクリアする
	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fRotMove = 0.0f;
	m_fRotDiff = 0.0f;
	m_fRotDest = 0.0f;
	m_pBody = nullptr;
	m_pLeg = nullptr;
	m_pWaist = nullptr;
	m_Catch.pPlayer = nullptr;
	m_Catch.pGimmick = nullptr;
	m_pScore = nullptr;
	m_Catch.SetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Catch.nMoveCnt = 0;
	m_nLife = 0;
	m_type = TYPE_NONE;
	m_nId = m_nNumCount;
	m_nNumItemCoin = 0;
	m_nNumItemBrecetet = 0;
	m_nNumItemCup = 0;
	m_nNumItemEmerald = 0;
	m_nNumItemDiamond = 0;
	m_nNumItemGold = 0;
	m_nNumItemJar = 0;
	m_nNumItemKunai = 0;
	m_nNumItemRing = 0;
	m_nNumItemScroll = 0;
	m_nNumItemShuriken = 0;
	m_nItemId = CItem::TYPE_COIN;
	m_action = ACTION_NEUTRAL;
	m_bJump = false;
	m_bGoal = false;
	m_nItemCnt = 0;
	m_pMyCamera = nullptr;

	for (int i = 0; i < MAX_ITEM; i++)
	{
		m_aSaveType[i] = 0;
	}
	
	// 自分自身をリストに追加
	if (m_pTop != nullptr)
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
CPlayer::~CPlayer()
{
	
}

//===============================================
// 初期化処理
//===============================================
HRESULT CPlayer::Init(void)
{
	// 腰の生成
	if (m_pWaist == nullptr)
	{
		m_pWaist = new CWaist;
		m_pWaist->SetParent(&m_Info.mtxWorld);
	}

	// 胴体の設定
	m_pBody = CCharacter::Create("data\\TXT\\motion_ninjabody.txt");
	m_pBody->SetParent(m_pWaist->GetMtxWorld());

	if (m_pBody->GetMotion() != nullptr)
	{
		// 初期モーションの設定
		m_pBody->GetMotion()->InitSet(m_action);
	}

	// 下半身の設定
	m_pLeg = CCharacter::Create("data\\TXT\\motion_ninjaleg.txt");
	m_pLeg->SetParent(m_pWaist->GetMtxWorld());

	if (m_pLeg->GetMotion() != nullptr)
	{
		// 初期モーションの設定
		m_pLeg->GetMotion()->InitSet(m_action);
	}

	// 腰の高さを合わせる
	if (m_pLeg != nullptr)
	{// 脚が使用されている場合
		CModel *pModel = m_pLeg->GetParts(0);	// 腰パーツを取得

		if (pModel != nullptr)
		{// パーツが存在する場合
			D3DXVECTOR3 pos = pModel->GetPosition();	// モデルの相対位置を取得

			// 高さを設定
			m_pWaist->SetHeight(pos);

			// 腰のモデルの位置を変更
			pModel->SetPosition(pos);
		}
	}

	if (m_pScore == nullptr)
	{
		m_pScore = CScore::Create(D3DXVECTOR3(100.0f, 100.0f, 0.0f), 30.0f, 30.0f);
	}
	
	if (m_pScore != nullptr)
	{
		m_pScore->Init();
	}

	m_Info.state = STATE_APPEAR;
	m_action = ACTION_NEUTRAL;
	m_type = TYPE_NONE;
	m_nLife = START_LIFE;
	m_bJump = false;
	m_nItemCnt = 0;

	//m_pScore->AddScore(500 * m_nItemCnt);

	return S_OK;
}

//===============================================
// 初期化処理(オーバーロード)
//===============================================
HRESULT CPlayer::Init(const char *pBodyName, const char *pLegName)
{
	SetMatrix();

	// 腰の生成
	if (m_pWaist == nullptr)
	{
		m_pWaist = new CWaist;
		m_pWaist->SetParent(&m_Info.mtxWorld);
		m_pWaist->SetMatrix();
	}

	// 胴体の設定
	if (pBodyName != nullptr)
	{// ファイル名が存在している
		m_pBody = CCharacter::Create(pBodyName);
		m_pBody->SetParent(m_pWaist->GetMtxWorld());
		m_pBody->SetShadow(true);
		m_pBody->SetDraw();

		if (m_pBody->GetMotion() != nullptr)
		{
			// 初期モーションの設定
			m_pBody->GetMotion()->InitSet(m_action);
		}
	}

	// 下半身の設定
	if (pLegName != nullptr)
	{// ファイル名が存在している
		m_pLeg = CCharacter::Create(pLegName);
		m_pLeg->SetParent(m_pWaist->GetMtxWorld());
		m_pLeg->SetShadow(true);
		m_pLeg->SetDraw();

		if (m_pLeg->GetMotion() != nullptr)
		{
			// 初期モーションの設定
			m_pLeg->GetMotion()->InitSet(m_action);
		}
	}

	// 腰の高さを合わせる
	if (m_pLeg != nullptr)
	{// 脚が使用されている場合
		CModel *pModel = m_pLeg->GetParts(0);	// 腰パーツを取得

		if (pModel != nullptr)
		{// パーツが存在する場合
			D3DXVECTOR3 pos = pModel->GetPosition();	// モデルの相対位置を取得

			// 高さを設定
			m_pWaist->SetHeight(pos);

			// 腰のモデルの位置を変更
			pModel->SetPosition(pos);
		}
	}

	/*if (m_pScore == nullptr)
	{
		m_pScore = CScore::Create(D3DXVECTOR3(50.0f + (m_nNumCount - 1) * 500.0f, 50.0f, 0.0f), 30.0f, 30.0f);
	}*/

	if (m_pScore != nullptr)
	{
		m_pScore->Init();
	}

	m_nLife = START_LIFE;
	m_type = TYPE_NONE;
	m_action = ACTION_NEUTRAL;
	m_bJump = false;
	m_nItemCnt = 0;

	//m_pScore->AddScore(500 * m_nItemCnt);

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CPlayer::Uninit(void)
{
	// リストから自分自身を削除する
	if (m_pTop == this) {// 自身が先頭
		if (m_pNext != nullptr)
		{// 次が存在している
			m_pTop = m_pNext;	// 次を先頭にする
			m_pNext->m_pPrev = nullptr;	// 次の前のポインタを覚えていないようにする
		}
		else
		{// 存在していない
			m_pTop = nullptr;	// 先頭がない状態にする
			m_pCur = nullptr;	// 最後尾がない状態にする
		}
	}
	else if (m_pCur == this) {// 自身が最後尾
		if (m_pPrev != nullptr)
		{// 次が存在している
			m_pCur = m_pPrev;			// 前を最後尾にする
			m_pPrev->m_pNext = nullptr;	// 前の次のポインタを覚えていないようにする
		}
		else
		{// 存在していない
			m_pTop = nullptr;	// 先頭がない状態にする
			m_pCur = nullptr;	// 最後尾がない状態にする
		}
	}
	else {
		if (m_pNext != nullptr)
		{
			m_pNext->m_pPrev = m_pPrev;	// 自身の次に前のポインタを覚えさせる
		}
		if (m_pPrev != nullptr)
		{
			m_pPrev->m_pNext = m_pNext;	// 自身の前に次のポインタを覚えさせる
		}
	}

	// 胴体の終了
	if (m_pBody != nullptr) {
		m_pBody->Uninit();
		delete m_pBody;
		m_pBody = nullptr;
	}

	// 下半身の終了
	if (m_pLeg != nullptr) {
		m_pLeg->Uninit();
		delete m_pLeg;
		m_pLeg = nullptr;
	}

	// 腰の廃棄
	if (m_pWaist != nullptr){
		delete m_pWaist;
		m_pWaist = nullptr;
	}

	// スコアの終了
	if (m_pScore != nullptr) {// 使用されている場合

		// 終了処理
		m_pScore->Uninit();

		// 開放
		delete m_pScore;

		// 使用されていない状態にする
		m_pScore = nullptr;
	}

	// 人数を減らす
	m_nNumCount--;

	// 廃棄
	Release();
}

//===============================================
// 更新処理
//===============================================
void CPlayer::Update(void)
{	
	// 前回の座標を取得
	m_Info.posOld = GetPosition();

	StateSet();

	if (m_type == TYPE_ACTIVE)
	{

		if (m_Info.state != STATE_SPAWN)
		{
			// プレイヤー操作
			Controller();
		}

		// カメラ追従
		if (m_pMyCamera != nullptr) {
			// 追従処理
			m_pMyCamera->Update();
			m_pMyCamera->Pursue(GetPosition(), GetRotation());
		}

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
	CManager::GetInstance()->GetDebugProc()->Print("体力 [ %d ] : 状態 [ %d ] : アイテム所持数 [ %d ] : 選択中のアイテム [ %d ]\n", m_nLife, m_Info.state, m_nItemCnt, m_nItemId);

	// マトリックス設定
	if (m_Info.state == STATE_CATCH) {	// キャッチされている場合!!!!
		SetCatchMatrix();
	}
	else {	// それ以外!!!!!!
		SetMatrix();
	}

	BodySet();

	if (m_nLife <= 0) {	// 体力が0
		m_Info.state = STATE_DEATH;
	}

	if (m_pLeg != nullptr)
	{// 使用されている場合
		CModel *pModel = m_pLeg->GetParts(0);

		pModel->SetCurrentPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
}

//===============================================
// 生成
//===============================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, const char *pBodyName, const char *pLegName)
{
	CPlayer *pPlayer = nullptr;

	// オブジェクト2Dの生成
	pPlayer = new CPlayer();

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
		return nullptr;
	}

	return pPlayer;
}

//===============================================
// 操作処理
//===============================================
void CPlayer::Controller(void)
{
	D3DXVECTOR3 pos = GetPosition();	// 座標を取得
	D3DXVECTOR3 rot = GetRotation();	// 向きを取得
	m_fRotMove = rot.y;	//現在の向きを取得

	// 操作処理
	if(m_action != ACTION_DAMAGE){	// ダメージリアクションをしていない
		if (m_Info.state != STATE_DEATH) {	// 死亡していない
			Move();		// 移動
			Rotation();	// 回転
			Jump();		// ジャンプ
			Attack();	// 攻撃
			Catch();		// 掴む
			Throw();		// 投げる
			SelectItem();   // 捨てるアイテム選択
		}
	}

	MotionSet();	// モーション設定

	pos = GetPosition();	// 座標を取得

	float fGravity = GRAVITY * CManager::GetInstance()->GetSlow()->Get();
	m_Info.move.y += fGravity;
	pos.y += m_Info.move.y * CManager::GetInstance()->GetSlow()->Get();

	m_Info.move.x += (0.0f - m_Info.move.x) * INER;	//x座標
	m_Info.move.z += (0.0f - m_Info.move.z) * INER;	//x座標

	pos.x += m_Info.move.x * CManager::GetInstance()->GetSlow()->Get();
	pos.z += m_Info.move.z * CManager::GetInstance()->GetSlow()->Get();

	// 調整
	Adjust();

	m_Info.pos = pos;
	m_bJump = true;	// ジャンプ状態リセット

	// 起伏との当たり判定
	float fHeight = CMeshField::GetHeight(m_Info.pos);
	if (m_Info.pos.y <= fHeight)
	{
		m_Info.pos.y = fHeight;
		m_bJump = false;
	}

	// オブジェクトとの当たり判定
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(50.0f, 0.0f, 50.0f);
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);
	if (CObjectX::Collision(m_Info.pos, m_Info.posOld, m_Info.move, vtxMin, vtxMax, 0.3f))
	{
		m_bJump = false;
	}

	// アイテムとの当たり判定
	CItem *pItem = CItem::Collision(m_Info.pos);

	if (pItem != nullptr) {
		m_nItemCnt++;
		if (m_pScore != nullptr)
		{
			m_pScore->AddScore(pItem->GetEachScore());
		}

		for (int i = 0; i < MAX_ITEM; i++)
		{
			if (m_aSaveType[i] == 0)
			{
				m_aSaveType[i] = pItem->GetType();

				break;
			}
		}

		AddItemCount(pItem->GetType());

		pItem->Uninit();
	}

	// ギミックとの判定
	if (CGimmick::Collision(m_Info.pos, m_Info.posOld, m_Info.move, m_Catch.SetPos, vtxMin, vtxMax, m_action, &m_Catch.pGimmick)) {
		Damage(1);
	}

	// ゴールとの判定
	if (!m_bGoal) {	// まだゴールしていない
		if (CGoal::Collision(m_Info.pos, m_Info.posOld)) {	// ゴールを跨いだ
			m_bGoal = true;
		}
	}

	if (m_Catch.pGimmick != nullptr && m_Info.state != STATE_DEATH) {
		m_Info.state = STATE_CATCH;
	}
}

//===============================================
// 移動
//===============================================
void CPlayer::Move(void)
{
	CInputKeyboard *pInputKey = CManager::GetInstance()->GetInputKeyboard();	// キーボードのポインタ
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();

	// 入力装置確認
	if (nullptr == pInputKey){
		return;
	}

	// 入力装置確認
	if (nullptr == pInputPad){
		return;
	}

	//プレイヤーの更新
	MoveController();
}

//===============================================
// 回転
//===============================================
void CPlayer::Rotation(void)
{
	CCamera *pCamera = m_pMyCamera;		// カメラのポインタ

	if (m_pMyCamera == nullptr) {
		pCamera = CManager::GetInstance()->GetCamera();
	}

	D3DXVECTOR3 CamRot = pCamera->GetRotation();	// カメラの角度
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();

	// 入力装置確認
	if (nullptr == pInputPad){
		return;
	}

	if (m_nId < 0 || m_nId >= PLAYER_MAX)
	{// コントローラー数オーバー
		return;
	}

	if (!pInputPad->GetStickPress(m_nId, CInputPad::BUTTON_LEFT_X, 0.1f, CInputPad::STICK_PLUS) && 
		!pInputPad->GetStickPress(m_nId, CInputPad::BUTTON_LEFT_X, 0.1f, CInputPad::STICK_MINUS) &&
		!pInputPad->GetStickPress(m_nId, CInputPad::BUTTON_LEFT_Y, 0.1f, CInputPad::STICK_PLUS) &&
		!pInputPad->GetStickPress(m_nId, CInputPad::BUTTON_LEFT_Y, 0.1f, CInputPad::STICK_MINUS))
	{// コントローラー入力無し
		KeyBoardRotation();
		return;
	}

	// コントローラーの入力方向取得
	/*D3DXVECTOR2 vec;
	vec.y = pInputPad->GetStickAdd(m_nId, CInputPad::BUTTON_LEFT_X, 0.1f, CInputPad::STICK_PLUS);
	vec.x = pInputPad->GetStickAdd(m_nId, CInputPad::BUTTON_LEFT_Y, 0.1f, CInputPad::STICK_PLUS);
	D3DXVec2Normalize(&vec, &vec);
	m_fRotDest = atan2f(vec.y, vec.x);*/
}

//===============================================
// 回転
//===============================================
void CPlayer::KeyBoardRotation(void)
{
	CInputKeyboard *pInputKey = CManager::GetInstance()->GetInputKeyboard();	// キーボードのポインタ

	if (nullptr == pInputKey){
		return;
	}

	if (pInputKey->GetPress(DIK_W))
	{
		if (pInputKey->GetPress(DIK_A))
		{
			m_fRotDest = -D3DX_PI * 0.25f;
		}
		else if (pInputKey->GetPress(DIK_D))
		{
			m_fRotDest = D3DX_PI * 0.25f;
		}
		else
		{
			m_fRotDest = D3DX_PI * 0.0f;
		}
	}
	else if (pInputKey->GetPress(DIK_S))
	{
		if (pInputKey->GetPress(DIK_A))
		{
			m_fRotDest = -D3DX_PI * 0.75f;
		}
		else if (pInputKey->GetPress(DIK_D))
		{
			m_fRotDest = D3DX_PI * 0.75f;
		}
		else
		{
			m_fRotDest = D3DX_PI * 1.0f;
		}
	}
	else if (pInputKey->GetPress(DIK_A))
	{
		m_fRotDest = -D3DX_PI * 0.5f;
	}
	else if (pInputKey->GetPress(DIK_D))
	{
		m_fRotDest = D3DX_PI * 0.5f;
	}
}

//===============================================
// 調整
//===============================================
void CPlayer::MoveController(void)
{
	if (m_nId < 0 || m_nId >= PLAYER_MAX)
	{// コントローラー数おーばー
		return;
	}

	CCamera *pCamera = m_pMyCamera;		// カメラのポインタ

	if (m_pMyCamera == nullptr) {
		pCamera = CManager::GetInstance()->GetCamera();
	}

	D3DXVECTOR3 CamRot = pCamera->GetRotation();	// カメラの角度
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();
	float fSpeed = MOVE;	// 移動量

	if (m_Catch.pPlayer != nullptr) {
		fSpeed = CATCH_MOVE;
	}

	m_bMove = false;

	if (pInputPad->GetStickPress(m_nId, CInputPad::BUTTON_LEFT_X, 0.5f, CInputPad::STICK_MINUS) == true)
	{
		if (pInputPad->GetStickPress(m_nId, CInputPad::BUTTON_LEFT_Y, 0.5f, CInputPad::STICK_PLUS))
		{
			m_Info.move.x += cosf(CamRot.y + (-D3DX_PI * 0.75f)) * fSpeed - (m_nItemCnt * SPEED_DECAY);
			m_Info.move.z += sinf(CamRot.y + (-D3DX_PI * 0.75f)) * fSpeed + (m_nItemCnt * SPEED_DECAY);
			m_fRotDest = (-CamRot.y + D3DX_PI * 0.25f);
		}
		else if (pInputPad->GetStickPress(m_nId, CInputPad::BUTTON_LEFT_Y, 0.5f, CInputPad::STICK_MINUS))
		{
			m_Info.move.x += cosf(CamRot.y + (-D3DX_PI * 0.25f)) * fSpeed - (m_nItemCnt * SPEED_DECAY);
			m_Info.move.z += sinf(CamRot.y + (-D3DX_PI * 0.25f)) * fSpeed - (m_nItemCnt * SPEED_DECAY);
			m_fRotDest = (-CamRot.y + -D3DX_PI * 0.25f);
		}
		else
		{
			m_Info.move.x += cosf(CamRot.y + (-D3DX_PI * 0.5f)) * fSpeed - (m_nItemCnt * SPEED_DECAY);
			m_Info.move.z += sinf(CamRot.y + (-D3DX_PI * 0.5f)) * fSpeed;
			m_fRotDest = -CamRot.y;
		}

		// 移動した状態にする
		m_bMove = true;
	}
	else if (pInputPad->GetStickPress(m_nId, CInputPad::BUTTON_LEFT_X, 0.5f, CInputPad::STICK_PLUS) == true)
	{
		if (pInputPad->GetStickPress(m_nId, CInputPad::BUTTON_LEFT_Y, 0.5f, CInputPad::STICK_PLUS))
		{
			m_Info.move.x += cosf(CamRot.y + (D3DX_PI * 0.75f)) * fSpeed + (m_nItemCnt * SPEED_DECAY);
			m_Info.move.z += sinf(CamRot.y + (D3DX_PI * 0.75f)) * fSpeed + (m_nItemCnt * SPEED_DECAY);

			m_fRotDest = (-CamRot.y + D3DX_PI * 0.75f);
		}
		else if (pInputPad->GetStickPress(m_nId, CInputPad::BUTTON_LEFT_Y, 0.5f, CInputPad::STICK_MINUS))
		{
			m_Info.move.x += cosf(CamRot.y + (D3DX_PI * 0.25f)) * fSpeed + (m_nItemCnt * SPEED_DECAY);
			m_Info.move.z += sinf(CamRot.y + (D3DX_PI * 0.25f)) * fSpeed - (m_nItemCnt * SPEED_DECAY);

			m_fRotDest = (-CamRot.y + -D3DX_PI * 0.75f);
		}
		else
		{
			m_Info.move.x += cosf(CamRot.y + (D3DX_PI * 0.5f)) * fSpeed + (m_nItemCnt * SPEED_DECAY);
			m_Info.move.z += sinf(CamRot.y + (D3DX_PI * 0.5f)) * fSpeed;
			m_fRotDest = (-CamRot.y + D3DX_PI * 1.0f);
		}

		// 移動した状態にする
		m_bMove = true;
	}
	else if (pInputPad->GetStickPress(m_nId, CInputPad::BUTTON_LEFT_Y, 0.5f, CInputPad::STICK_PLUS))
	{
		m_Info.move.x += -cosf(CamRot.y) * fSpeed;
		m_Info.move.z += -sinf(CamRot.y) * fSpeed + (m_nItemCnt * SPEED_DECAY);
		m_fRotDest = (-CamRot.y + D3DX_PI * 0.5f);

		// 移動した状態にする
		m_bMove = true;

	}
	else if (pInputPad->GetStickPress(m_nId, CInputPad::BUTTON_LEFT_Y, 0.5f, CInputPad::STICK_MINUS))
	{
		m_Info.move.x += cosf(CamRot.y) * fSpeed;
		m_Info.move.z += sinf(CamRot.y) * fSpeed - (m_nItemCnt * SPEED_DECAY);
		m_fRotDest = (-CamRot.y + -D3DX_PI * 0.5f);

		// 移動した状態にする
		m_bMove = true;
	}
}

//===============================================
// ジャンプ
//===============================================
void CPlayer::Jump(void)
{
	if (m_nId < 0 || m_nId >= PLAYER_MAX)
	{// コントローラー数オーバー
		return;
	}

	if (m_Catch.pPlayer != nullptr && m_Info.state != STATE_CATCH)
	{
		return;
	}

	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();

	// 入力
	if (pInputPad->GetTrigger(CInputPad::BUTTON_B, m_nId))
	{
		if (m_bJump == false)
		{// ジャンプしていない場合
			m_bJump = true;

			if(m_Catch.pPlayer != nullptr)
			{
				m_Info.move.y = JUMP * 0.5f;
			}
			else
			{
				m_Info.move.y = JUMP;
			}

		}
	}
}

//===============================================
// 調整
//===============================================
void CPlayer::Adjust(void)
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
void CPlayer::StateSet(void)
{
	float fSlawMul = CManager::GetInstance()->GetSlow()->Get();
	switch (m_Info.state)
	{
	case STATE_APPEAR:
	{
		m_Info.fStateCounter -= fSlawMul;

		if (m_Info.fStateCounter <= 0.0f)
		{
			m_Info.fStateCounter = 0.0f;
			m_Info.state = STATE_NORMAL;
		}
	}
		break;

	case STATE_NORMAL:
	{

	}
		break;

	case STATE_DAMAGE:
	{
		m_Info.fStateCounter -= fSlawMul;

		if (m_Info.fStateCounter <= 0.0f)
		{
			m_Info.fStateCounter = DAMAGE_APPEAR;
			m_Info.state = STATE_APPEAR;
		}
	}
		break;

	case STATE_DEATH:
	{
		m_Info.fStateCounter -= fSlawMul;

		if (m_Info.fStateCounter <= 0.0f)
		{
			m_Info.fStateCounter = DAMAGE_APPEAR;
			m_Info.state = STATE_SPAWN;
			m_nLife = START_LIFE;

			if (m_pBody != nullptr) {
				m_pBody->SetDraw();
			}

			if (m_pLeg != nullptr) {
				m_pLeg->SetDraw();
			}
		}
	}
		break;

	case STATE_SPAWN:
	{
		m_Info.fStateCounter -= fSlawMul;

		if (m_Info.fStateCounter <= 0.0f)
		{
			m_Info.fStateCounter = SPAWN_INTERVAL;
			m_Info.state = STATE_APPEAR;
		}
	}
		break;

	case STATE_CATCH:
	{

	}
		break;
	}
}

//===============================================
// ダメージ処理
//===============================================
void CPlayer::Damage(int nDamage) 
{ 
	if (m_Info.state != STATE_NORMAL)
	{// ダメージを食らわない
		if (m_Info.state != STATE_CATCH)
		{
			return;
		}
	}

	int nOldLife = m_nLife;
	m_nLife -= nDamage;

	if (m_nLife < 0)
	{
		m_nLife = 0;
	}

	Drop(DROP_CNT * (nOldLife - m_nLife));

	if (m_nLife != nOldLife)
	{
		m_Info.fStateCounter = DAMAGE_INTERVAL;
		m_Info.state = STATE_DAMAGE;

		if (m_nLife <= 0)
		{
			m_nLife = 0;
			m_Info.state = STATE_DEATH;
			m_Info.fStateCounter = DAMAGE_APPEAR;

			if (m_pBody != nullptr){
				m_pBody->SetDraw(false);
			}

			if (m_pLeg != nullptr){
				m_pLeg->SetDraw(false);
			}

			DropAll();
		}
	}

	if (m_Catch.pPlayer != nullptr) {	// 他のプレイヤーを持っている
		m_Catch.pPlayer->m_Info.state = STATE_NORMAL;
		m_Catch.pPlayer->m_Catch.pPlayer = nullptr;
		m_Catch.pPlayer = nullptr;
	}
}

//===============================================
// 体力設定
//===============================================
void CPlayer::SetLife(int nLife)
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
void CPlayer::SetType(TYPE type)
{
	m_type = type;
}

//===============================================
// モーション設定
//===============================================
void CPlayer::MotionSet(void)
{
	if (nullptr == m_pBody)
	{// オブジェクト無し
		return;
	}

	if (nullptr == m_pBody->GetMotion())
	{// モーション無し
		return;
	}

	if (m_Info.state == STATE_DAMAGE)
	{// ダメージ状態
		m_action = ACTION_DAMAGE;
		m_pBody->GetMotion()->Set(m_action);
		m_pLeg->GetMotion()->Set(m_action);

		if (m_pBody->GetMotion()->GetEnd())
		{// モーション終了
			m_action = ACTION_NEUTRAL;	// 保持状態に変更
		}
		else
		{
			return;
		}
	}

	if (m_Info.state == STATE_CATCH && m_Catch.pPlayer != nullptr) {
		m_pBody->GetMotion()->Set(ACTION_FLUTTERING);
		m_pLeg->GetMotion()->Set(ACTION_FLUTTERING);

		return;
	}

	if (!m_bJump && !m_bMove && 
		m_action >= ACTION_NEUTRAL && m_action <= ACTION_JUMP)
	{// 何もしていない
		m_action = ACTION_NEUTRAL;
		m_pBody->GetMotion()->BlendSet(m_action);
	}
	else if(m_bJump && 
		m_action >= ACTION_NEUTRAL && m_action <= ACTION_JUMP)
	{// ジャンプした
		m_action = ACTION_JUMP;
		m_pBody->GetMotion()->BlendSet(m_action);
	}
	else if (m_bMove &&
		m_action >= ACTION_NEUTRAL && m_action <= ACTION_JUMP)
	{// 移動した
		m_action = ACTION_WALK;
		m_pBody->GetMotion()->BlendSet(m_action);
	}
	else if (m_action == ACTION_ATK)
	{// 攻撃した
		m_pBody->GetMotion()->Set(m_action);
		if (m_pBody->GetMotion()->GetEnd())
		{// モーション終了
			m_action = ACTION_NEUTRAL;
		}
	}
	else if (m_action == ACTION_CATCH)
	{// 持った
		m_pBody->GetMotion()->BlendSet(m_action);

		if (m_pBody->GetMotion()->GetEnd())
		{// モーション終了
			if (m_Catch.pPlayer == nullptr)
			{
				//m_action = ACTION_HOLD;	// 保持状態に変更
				m_action = ACTION_NEUTRAL;
			}
		}
		else
		{
			if (m_Catch.pPlayer == nullptr){	// プレイヤーを掴んでいない
				CModel *pModel = m_pBody->GetParts(m_pBody->GetNumParts() - HAND_PARTS);
				D3DXVECTOR3 pos = D3DXVECTOR3(pModel->GetMtx()->_41, pModel->GetMtx()->_42, pModel->GetMtx()->_43);
				PlayerCatch(pos);
			}
		}
	}
	else if (m_action == ACTION_HOLD)
	{// 保持している
		m_pBody->GetMotion()->BlendSet(m_action);
		if (m_pBody->GetMotion()->GetEnd())
		{// モーション終了
		
		}
	}
	else if (m_action == ACTION_THROW)
	{// 投げる
		m_pBody->GetMotion()->BlendSet(m_action);
		if (m_pBody->GetMotion()->GetEnd())
		{// モーション終了
			m_action = ACTION_NEUTRAL;
		}
	}
	else if (m_action == ACTION_DAMAGE)
	{// 投げる
		m_pBody->GetMotion()->BlendSet(m_action);
		if (m_pBody->GetMotion()->GetEnd())
		{// モーション終了
			m_action = ACTION_NEUTRAL;
		}

		return;
	}
	else
	{

	}

	if (nullptr == m_pLeg){	// 脚がない
		return;
	}

	if (nullptr == m_pLeg->GetMotion()) {	// モーションがない
		return;
	}

	if (m_bJump)
	{
		m_pLeg->GetMotion()->BlendSet(ACTION_JUMP);
	}
	else if (m_bMove)
	{
		m_pLeg->GetMotion()->BlendSet(ACTION_WALK);
	}
	else
	{
		m_pLeg->GetMotion()->BlendSet(ACTION_NEUTRAL);
	}
}

//===============================================
// 攻撃
//===============================================
void CPlayer::Attack(void)
{
	if (m_action < ACTION_NEUTRAL || m_action > ACTION_JUMP || m_Info.state == STATE_CATCH)
	{// 攻撃不可能
		if (m_action != ACTION_ATK)
		{// 攻撃中ではない
			return;
		}
	}

	// パッド入力
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();

	// 入力
	if (pInputPad->GetTrigger(CInputPad::BUTTON_A, m_nId))
	{
		if (m_action != ACTION_ATK)
		{// 攻撃中ではない
			m_action = ACTION_ATK;
		}
	}

	// 攻撃判定
	if (m_pBody == nullptr){	// 胴体がない
		return;
	}

	if (m_pBody->GetMotion() == nullptr){	// モーションがない
		return;
	}

	if (m_pBody->GetMotion()->GetNowMotion() == ACTION_ATK && 
		m_pBody->GetMotion()->GetNowKey() == m_pBody->GetMotion()->GetNowNumKey() - 2)
	{// 攻撃判定中
		CModel *pModel = m_pBody->GetParts(m_pBody->GetNumParts() - HAND_PARTS);	// パーツ
		D3DXVECTOR3 pos = D3DXVECTOR3(pModel->GetMtx()->_41, pModel->GetMtx()->_42, pModel->GetMtx()->_43);
		DamageCollision(pos);

		// 当たり判定確認
		AttackCheck();
	}
}

//===============================================
// 物を持つ
//===============================================
void CPlayer::Catch(void)
{
	if (m_action < ACTION_NEUTRAL || m_action > ACTION_WALK || m_Info.state == STATE_CATCH)
	{// 待機か移動中
		if (m_action != ACTION_CATCH && (m_Catch.pPlayer == nullptr && m_Catch.pGimmick == nullptr))
		{
			return;
		}
	}

	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();

	// 入力
	if (pInputPad->GetTrigger(CInputPad::BUTTON_X, m_nId))
	{
		if (m_action != ACTION_CATCH)
		{
			m_action = ACTION_CATCH;
		}
	}

	if (pInputPad->GetTrigger(CInputPad::BUTTON_Y, m_nId))
	{
		int n = 0;
	}

	// 持った対象の判定
	if (m_Catch.pPlayer != nullptr && m_Info.state != STATE_CATCH) {	// 他のプレイヤーを持っている
		if (m_Catch.pPlayer->m_Info.state != STATE_CATCH) {	// 相手の状態が変わった場合
			m_Catch.pPlayer->m_Catch.pPlayer = nullptr;
			m_Catch.pPlayer = nullptr;
		}
		else
		{
			m_fRotDest = m_fRotMove;
			if (m_Catch.pPlayer->m_bMove) {	// 相手が移動
				m_Catch.nMoveCnt++;	// カウントアップ
				if (m_Catch.pPlayer->m_bJump)
				{
					m_Info.pos.x += m_Catch.pPlayer->m_Info.move.x * 1.5f;	// 相手の移動量に引っ張られる
					m_Info.pos.z += m_Catch.pPlayer->m_Info.move.z * 1.5f;	// 相手の移動量に引っ張られる
				}
				else
				{
					m_Info.pos.x += m_Catch.pPlayer->m_Info.move.x * 0.75f;	// 相手の移動量に引っ張られる
					m_Info.pos.z += m_Catch.pPlayer->m_Info.move.z * 0.75f;	// 相手の移動量に引っ張られる
				}

				m_Catch.pPlayer->m_Info.pos.y += m_Catch.pPlayer->m_Info.move.y;

				if (m_Catch.pPlayer->m_Info.pos.y < m_Info.pos.y)
				{
					m_Catch.pPlayer->m_Info.pos.y = m_Info.pos.y;
					m_Catch.pPlayer->m_Info.move.y = 0.0f;
				}
			}

			if (m_Catch.nMoveCnt >= CATCH_LIMIT							// カウント限界値
				|| pInputPad->GetTrigger(CInputPad::BUTTON_X, m_nId)) {	// キー入力
				m_Catch.pPlayer->m_Info.state = STATE_NORMAL;
				m_Catch.pPlayer->m_Catch.pPlayer = nullptr;
				m_Catch.pPlayer = nullptr;
			}
		}
	}
	else if(m_Catch.pGimmick != nullptr) {	// ギミックを持っている
		CGimmickRotateDoor *pDoor = m_Catch.pGimmick->GetRotateDoor();

		if (pDoor != nullptr) {	// ドアを持っている

			if (pDoor->GetModel() == nullptr) {	// ドアのモデルが使用されていない
				GimmickRelease();	// ギミックを離す
			}

			if (pDoor->GetModel()->GetCurrentRotation().y == 0.0f) {	// 回転が止まっている
				GimmickRelease();	// ギミックを離す
			}
		}
	}
}

//===============================================
// 所持しているギミックを外す
//===============================================
void CPlayer::GimmickRelease(void)
{
	m_Info.state = STATE_NORMAL;
	m_Catch.pGimmick = nullptr;
}

//===============================================
// アイテムのファイル設定
//===============================================
const char *CPlayer::ItemFileName(int type)
{
	char m_aString[64] = "\n";

	switch (type)
	{
	case CItem::TYPE_NORMAL:
	{
		return "\0";
	}

	break;

	case CItem::TYPE_COIN:
	{
		return  "data\\MODEL\\coin.x";
	}

	break;

	case CItem::TYPE_BRECELET:
	{
		return   "data\\MODEL\\bracelet00.x";
	}

	break;

	case CItem::TYPE_CUP:
	{
		return  "data\\MODEL\\cup00.x";
	}

	break;

	case CItem::TYPE_GEM00:
	{
		return  "data\\MODEL\\gem00.x";
	}

	break;

	case CItem::TYPE_GEM01:
	{
		return  "data\\MODEL\\gem01.x";
	}

	break;

	case CItem::TYPE_GOLDBAR:
	{
		return  "data\\MODEL\\goldbar00.x";
	}

	break;

	case CItem::TYPE_JAR:
	{
		return  "data\\MODEL\\jar.x";
	}

	break;

	case CItem::TYPE_KUNAI:
	{
		return  "data\\MODEL\\kunai.x";
	}

	break;

	case CItem::TYPE_RING00:
	{
		return  "data\\MODEL\\ring00.x";
	}

	break;

	case CItem::TYPE_SCROLL:
	{
		return  "data\\MODEL\\scroll00.x";
	}

	break;

	case CItem::TYPE_SHURIKEN:
	{
		return  "data\\MODEL\\shuriken.x";
	}

	break;

	case CItem::TYPE_MAX:
	{
		return  "";
	}

	break;

	}

	return  "";
}

//===============================================
// アイテムのソート
//===============================================
void CPlayer::ItemSort(void)
{
	for (int nCount = 0; nCount < MAX_ITEM - 1; nCount++)
	{
		for (int nCntRank = 1 + nCount; nCntRank < MAX_ITEM; nCntRank++)
		{
			//大きかったら入れ替え
			if (m_aSaveType[nCount] == 0)
			{//入れ替え
				m_aSaveType[nCount] = 0;
				int nTmp = m_aSaveType[nCntRank];
				m_aSaveType[nCntRank] = m_aSaveType[nCount];
				m_aSaveType[nCount] = nTmp;
			}
		}
	}
}

//===============================================
// それぞれのアイテム加算
//===============================================
void CPlayer::AddItemCount(int type)
{
	switch (type)
	{
	case CItem::TYPE_NORMAL:  // なんもない
	{
		
	}

	break;

	case CItem::TYPE_COIN:  // コイン
	{
		m_nNumItemCoin++;
	}

	break;

	case CItem::TYPE_BRECELET:  // ブレスレット
	{
		m_nNumItemBrecetet++;
	}

	break;

	case CItem::TYPE_CUP:       // 盃
	{
		m_nNumItemCup++;
	}

	break;

	case CItem::TYPE_GEM00:     // エメラルド
	{
		m_nNumItemEmerald++;
	}

	break;

	case CItem::TYPE_GEM01:     // ダイヤモンド
	{
		m_nNumItemDiamond++;
	}

	break;

	case CItem::TYPE_GOLDBAR:   // 金塊
	{
		m_nNumItemGold++;
	}

	break;

	case CItem::TYPE_JAR:       // 瓶
	{
		m_nNumItemJar++;
	}

	break;

	case CItem::TYPE_KUNAI:     // クナイ
	{
		m_nNumItemKunai++;
	}

	break;

	case CItem::TYPE_RING00:    // リング
	{
		m_nNumItemRing++;
	}

	break;

	case CItem::TYPE_SCROLL:    // 巻物
	{
		m_nNumItemScroll++;
	}

	break;

	case CItem::TYPE_SHURIKEN:  // 手裏剣
	{
		m_nNumItemShuriken++;
	}

	break;

	case CItem::TYPE_MAX:
	{
		
	}

	break;

	}
}

//===============================================
// それぞれのアイテム減算
//===============================================
void CPlayer::SubItemCount(int type)
{
	switch (type)
	{
	case CItem::TYPE_NORMAL:  // なんもない
	{

	}

	break;

	case CItem::TYPE_COIN:  // コイン
	{
		m_nNumItemCoin--;
	}

	break;

	case CItem::TYPE_BRECELET:  // ブレスレット
	{
		m_nNumItemBrecetet--;
	}

	break;

	case CItem::TYPE_CUP:       // 盃
	{
		m_nNumItemCup--;
	}

	break;

	case CItem::TYPE_GEM00:     // エメラルド
	{
		m_nNumItemEmerald--;
	}

	break;

	case CItem::TYPE_GEM01:     // ダイヤモンド
	{
		m_nNumItemDiamond--;
	}

	break;

	case CItem::TYPE_GOLDBAR:   // 金塊
	{
		m_nNumItemGold--;
	}

	break;

	case CItem::TYPE_JAR:       // 瓶
	{
		m_nNumItemJar--;
	}

	break;

	case CItem::TYPE_KUNAI:     // クナイ
	{
		m_nNumItemKunai--;
	}

	break;

	case CItem::TYPE_RING00:    // リング
	{
		m_nNumItemRing--;
	}

	break;

	case CItem::TYPE_SCROLL:    // 巻物
	{
		m_nNumItemScroll--;
	}

	break;

	case CItem::TYPE_SHURIKEN:  // 手裏剣
	{
		m_nNumItemShuriken--;
	}

	break;

	case CItem::TYPE_MAX:
	{
		
	}

	break;

	}
}

//===============================================
// 捨てるアイテム選択
//===============================================
void CPlayer::SelectItem(void)
{
	// ゲームパッドの情報を取得
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();

	if (pInputPad->GetTrigger(CInputPad::BUTTON_RIGHTBUTTON, m_nId))
	{
		m_nItemId++;
	}

	if (pInputPad->GetTrigger(CInputPad::BUTTON_LEFTBUTTON, m_nId))
	{
		m_nItemId--;
	}

	if (m_nItemId >= 12)
	{
		m_nItemId = 1;
	}
	else if(m_nItemId <= 0)
	{
		m_nItemId = 11;
	}

	if (pInputPad->GetTrigger(CInputPad::BUTTON_Y, m_nId))
	{
		if (m_nItemCnt > 0 && GetSelectItem(m_nItemId) > 0)
		{
			CItem *pItem = CItem::Create(m_Info.pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), ItemFileName(m_nItemId), m_nItemId, CItem::STATE_DROP);

			if (m_pScore != nullptr)
			{
				// スコアへらすう
				m_pScore->LowerScore(pItem->GetEachScore());
			}

			m_aSaveType[m_nItemId] = 0;

			if (nullptr != pItem)
			{
				D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				//移動量の設定
				move.x = sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.08f;
				move.y = 18.0f;
				move.z = cosf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.08f;
				pItem->SetMove(move);
			}

			m_nItemCnt--;

			SubItemCount(m_nItemId);

			ItemSort();
		}
	}
}

//===============================================
// それぞれのアイテムの総数取得
//===============================================
int CPlayer::GetSelectItem(int type)
{
	switch (type)
	{
	case CItem::TYPE_NORMAL:  // なんもない
	{

	}

	break;

	case CItem::TYPE_COIN:  // コイン
	{
		return m_nNumItemCoin;
	}

	break;

	case CItem::TYPE_BRECELET:  // ブレスレット
	{
		return m_nNumItemBrecetet;
	}

	break;

	case CItem::TYPE_CUP:       // 盃
	{
		return m_nNumItemCup;
	}

	break;

	case CItem::TYPE_GEM00:     // エメラルド
	{
		return m_nNumItemEmerald;
	}

	break;

	case CItem::TYPE_GEM01:     // ダイヤモンド
	{
		return m_nNumItemDiamond;
	}

	break;

	case CItem::TYPE_GOLDBAR:   // 金塊
	{
		return m_nNumItemGold;
	}

	break;

	case CItem::TYPE_JAR:       // 瓶
	{
		return m_nNumItemJar;
	}

	break;

	case CItem::TYPE_KUNAI:     // クナイ
	{
		return m_nNumItemKunai;
	}

	break;

	case CItem::TYPE_RING00:    // リング
	{
		return m_nNumItemRing;
	}

	break;

	case CItem::TYPE_SCROLL:    // 巻物
	{
		return m_nNumItemScroll;
	}

	break;

	case CItem::TYPE_SHURIKEN:  // 手裏剣
	{
		return m_nNumItemShuriken;
	}

	break;

	case CItem::TYPE_MAX:
	{
		return 0;
	}

	break;

	}

	return 0;
}

//===============================================
// 物を投げる
//===============================================
void CPlayer::Throw(void)
{
	if (m_action != ACTION_HOLD)
	{// 持っていない
		return;
	}

	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();

	// 入力
	if (pInputPad->GetTrigger(CInputPad::BUTTON_X, m_nId))
	{
		m_action = ACTION_THROW;
	}
}

//===============================================
// マトリックス設定
//===============================================
void CPlayer::SetMatrix(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスへのポインタを取得
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_Info.mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Info.rot.y, m_Info.rot.x, m_Info.rot.z);
	D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);
	D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_Info.mtxWorld);
}

//===============================================
// プレイヤー同士の攻撃判定
//===============================================
void CPlayer::DamageCollision(D3DXVECTOR3 pos)
{
	CPlayer *pPlayer = GetTop();	// 先頭を受け取る
	CXFile *pFile = CManager::GetInstance()->GetModelFile();

	while (pPlayer != nullptr)
	{
		CPlayer *pPlayerNext = pPlayer->GetNext();	// 次を保持

		if (pPlayer == this)
		{// 自分自身か相手が通常状態以外
			pPlayer = pPlayerNext;
			continue;
		}

		D3DXVECTOR3 ObjPos = pPlayer->GetPosition();	// 座標
		D3DXVECTOR3 HeadPos = pPlayer->m_pBody->GetParts(1)->GetPosition();
		D3DXVECTOR3 HeadMax = pFile->GetMax(pPlayer->m_pBody->GetParts(1)->GetId());
		D3DXVECTOR3 vtxMax = pFile->GetMax(pPlayer->m_pBody->GetParts(0)->GetId());
		D3DXVECTOR3 vtxMin = pFile->GetMin(pPlayer->m_pBody->GetParts(0)->GetId());

		if (pos.x + -ATK_RANGE <= ObjPos.x + vtxMax.x && pos.x + ATK_RANGE >= ObjPos.x + vtxMin.x
			&& pos.z + -ATK_RANGE <= ObjPos.z + vtxMax.z && pos.z + ATK_RANGE >= ObjPos.z + vtxMin.z)
		{// 左右判定内
			if (pos.y >= ObjPos.y && pos.y <= ObjPos.y + HeadPos.y + HeadMax.y)
			{// 高さ判定内
				pPlayer->Damage(1);
			}
		}

		pPlayer = pPlayerNext;
	}
}

//===============================================
// アイテムを落とす
//===============================================
void CPlayer::Drop(int nDropCnt)
{
	int nOldCnt = m_nItemCnt;

	m_nItemCnt -= nDropCnt;

	if (m_nItemCnt < 0) {	// 所持数が0を下回った
		m_nItemCnt = 0;
	}

	int nDiff = nOldCnt - m_nItemCnt;	// 減少量

	// 落とした分生成
	for (int nCnt = 0; nCnt < nDiff; nCnt++)
	{
		char aString[258] = "\n";

		strcpy(aString, ItemFileName(m_aSaveType[nCnt]));

		CItem *pItem = CItem::Create(m_Info.pos, D3DXVECTOR3(0.0f, 0.0f ,0.0f), aString, m_aSaveType[nCnt], CItem::STATE_DROP);

		if (m_pScore != nullptr)
		{
			// スコアへらすう
			m_pScore->LowerScore(pItem->GetEachScore());
		}

		m_aSaveType[nCnt] = 0;

		if (nullptr != pItem)
		{
			D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//移動量の設定
			move.x = sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.08f;
			move.y = 18.0f;
			move.z = cosf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.08f;
			pItem->SetMove(move);
		}
	}

	ItemSort();
}

//===============================================
// アイテム全部落とす
//===============================================
void CPlayer::DropAll(void)
{
	// 落とした分生成
	for (int nCnt = 0; nCnt < m_nItemCnt; nCnt++)
	{
		char aString[258] = "\n";

		strcpy(aString, ItemFileName(m_aSaveType[nCnt]));

		CItem *pItem = CItem::Create(m_Info.pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), aString, m_aSaveType[nCnt], CItem::STATE_DROP);

		if (m_pScore != nullptr)
		{
			// スコアへらすう
			m_pScore->LowerScore(pItem->GetEachScore());
		}

		m_aSaveType[nCnt] = 0;

		if (nullptr != pItem)
		{
			D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//移動量の設定
			move.x = sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.08f;
			move.y = 18.0f;
			move.z = cosf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.08f;
			pItem->SetMove(move);
		}
	}

	// 所持しているアイテムの総数をゼロにする
	m_nItemCnt = 0;
}

//===============================================
// プレイヤーを掴む
//===============================================
void CPlayer::PlayerCatch(D3DXVECTOR3 pos)
{
	CPlayer *pPlayer = GetTop();	// 先頭を受け取る
	CXFile *pFile = CManager::GetInstance()->GetModelFile();

	while (pPlayer != nullptr)
	{
		CPlayer *pPlayerNext = pPlayer->GetNext();	// 次を保持

		if (pPlayer == this)
		{// 自分自身か相手が通常状態以外
			pPlayer = pPlayerNext;
			continue;
		}

		D3DXVECTOR3 ObjPos = pPlayer->GetPosition();	// 座標
		D3DXVECTOR3 HeadPos = pPlayer->m_pBody->GetParts(1)->GetPosition();
		D3DXVECTOR3 HeadMax = pFile->GetMax(pPlayer->m_pBody->GetParts(1)->GetId());
		D3DXVECTOR3 vtxMax = pFile->GetMax(pPlayer->m_pBody->GetParts(0)->GetId());
		D3DXVECTOR3 vtxMin = pFile->GetMin(pPlayer->m_pBody->GetParts(0)->GetId());

		if (pos.x + -CATCH_RANGE <= ObjPos.x + vtxMax.x && pos.x + CATCH_RANGE >= ObjPos.x + vtxMin.x
			&& pos.z + -CATCH_RANGE <= ObjPos.z + vtxMax.z && pos.z + CATCH_RANGE >= ObjPos.z + vtxMin.z)
		{// 左右判定内
			if (pos.y >= ObjPos.y && pos.y <= ObjPos.y + HeadPos.y + HeadMax.y)
			{// 高さ判定内
				if (pPlayer->m_Info.state == STATE_NORMAL)
				{// 通常状態の場合
					pPlayer->m_Info.state = STATE_CATCH;	// 相手を掴まれている状態に
					pPlayer->m_Catch.pPlayer = this;		// 相手に自分を指定
					m_Catch.pPlayer = pPlayer;				// 自分のポインタに相手を指定
					m_Catch.nMoveCnt = 0;
				}
			}
		}

		pPlayer = pPlayerNext;
	}
}

//===============================================
// プレイヤーのマトリックス
//===============================================
void CPlayer::SetCatchMatrix(void)
{
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_Info.mtxWorld);

	if (m_Catch.pPlayer != nullptr) {	// プレイヤー
		D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, m_Info.pos.y - m_Catch.pPlayer->m_Info.mtxWorld._42, -50.0f);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxTrans);

		// パーツのマトリックスと親のマトリックスをかけ合わせる
		D3DXMatrixMultiply(&m_Info.mtxWorld,
			&m_Info.mtxWorld, &m_Catch.pPlayer->m_Info.mtxWorld);

		m_Info.pos = D3DXVECTOR3(m_Info.mtxWorld._41, m_Info.mtxWorld._42, m_Info.mtxWorld._43);

		return;
	}
	else if (m_Catch.pGimmick != nullptr) { // ギミック

		D3DXVECTOR3 pos = m_Catch.SetPos;
		D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		CGimmickRotateDoor *pDoor = m_Catch.pGimmick->GetRotateDoor();
		
		if (pDoor != nullptr) {

			if (pDoor->GetModel() != nullptr) {

				// 位置を反映
				D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
				D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxTrans);

				// 向きを反映
				D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
				D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxRot);

				// パーツのマトリックスと親のマトリックスをかけ合わせる
				D3DXMatrixMultiply(&m_Info.mtxWorld,
					&m_Info.mtxWorld, pDoor->GetModel()->GetMtx());

				m_Info.pos = D3DXVECTOR3(m_Info.mtxWorld._41, m_Info.mtxWorld._42, m_Info.mtxWorld._43);
			}
		}

		return;
	}

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Info.rot.y, m_Info.rot.x, m_Info.rot.z);
	D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);
	D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxTrans);
}

//===============================================
// 攻撃中の当たり判定確認
//===============================================
void CPlayer::AttackCheck(void)
{
	if (m_pBody == nullptr) {	// 体がない
		return;
	}

	CModel *pModel = m_pBody->GetParts(m_pBody->GetNumParts() - HAND_PARTS);	// 手を取得する

	if (pModel == nullptr) {	// モデルがない
		return;
	}

	D3DXVECTOR3 AtkPos = D3DXVECTOR3(pModel->GetMtx()->_41, pModel->GetMtx()->_42, pModel->GetMtx()->_43);	// 攻撃座標
	CEnemy *pEnem = CEnemy::GetTop()->GetTop();	// 敵の先頭を取得
	
	// 敵数分確認
	while (pEnem != nullptr) {
		CEnemy *pEnemNext = pEnem->GetNext();
		pEnem->HitCheck(AtkPos, ATK_RANGE);	// 触れているかチェック
		pEnem = pEnemNext;
	}
}

//===============================================
// 使用階層構造の設定
//===============================================
void CPlayer::BodySet(void)
{
	// 下半身更新
	if (m_pLeg != nullptr)
	{// 使用されている場合
		m_pLeg->Update();

		// 腰の設定
		if (m_pWaist != nullptr)
		{
			CModel *pModel = m_pLeg->GetParts(0);

			// 腰の高さを補填
			m_pWaist->SetPosition(m_pWaist->GetSetPosition() + pModel->GetCurrentPosition());
			m_pWaist->SetMatrix();
		}
	}

	// 胴体更新
	if (m_pBody != nullptr)
	{// 使用されている場合
		m_pBody->Update();
	}
}