//==========================================================
//
// 風の術 [air.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "air.h"
#include "player.h"
#include "enemy.h"
#include "manager.h"
#include "debugproc.h"

// 無名名前空間
namespace {
	const float MAX_LENGTH = (500.0f);	// 最大の範囲
	const float RANGE_UPSPEED = (5.0f);	// 1フレーム間の範囲増加量
	const float FLYAWAY_SPEED = (300.0f);	// 吹っ飛ぶ速度(かっけえ変数名)
}

//==========================================================
// コンストラクタ
//==========================================================
CAir::CAir()
{
	// 値のクリア
}

//==========================================================
// デストラクタ
//==========================================================
CAir::~CAir()
{

}

//==========================================================
// 初期化処理
//==========================================================
HRESULT CAir::Init(void)
{
	return S_OK;
}

//==========================================================
// 終了処理
//==========================================================
void CAir::Uninit(void)
{
	Release();
}

//==========================================================
// 更新処理
//==========================================================
void CAir::Update(void)
{
	m_Info.fRange += RANGE_UPSPEED;

	if (m_Info.fRange > MAX_LENGTH) {	// 最大範囲を超えた
		Uninit();
	}
	else
	{
		CManager::GetInstance()->GetDebugProc()->Print("範囲[%f]\n", m_Info.fRange);
		// 当たり判定を取る
		Collision();
	}
}

//==========================================================
// 生成
//==========================================================
CAir *CAir::Create(const D3DXVECTOR3& pos, const int nId)
{
	CAir *pAir = nullptr;

	pAir = new CAir;

	if (pAir != nullptr)
	{
		// 初期化処理
		pAir->Init();

		// 座標の設定
		pAir->SetPosition(pos);

		// IDの設定
		pAir->BindId(nId);
	}

	return pAir;
}

//==========================================================
// 当たり判定
//==========================================================
void CAir::Collision(void)
{
	// プレイヤーとの判定
	{
		CPlayer *pPlayer = CPlayer::GetTop();

		while (pPlayer != nullptr) 
		{
			CPlayer *pPlayerNext = pPlayer->GetNext();	// 次を保持

			if (pPlayer->GetId() == m_nId) {	// 出した本人
				pPlayer = pPlayerNext;
				continue;
			}

			// 距離を取る
			D3DXVECTOR3 ObjPos = pPlayer->GetPosition();
			float fLength = sqrtf((m_Info.pos.x - ObjPos.x) * (m_Info.pos.x - ObjPos.x)
				+ (m_Info.pos.z - ObjPos.z) * (m_Info.pos.z - ObjPos.z));

			if (fLength > m_Info.fRange) {	// 風の範囲内ではない場合
				pPlayer = pPlayerNext;
				continue;
			}

			D3DXVECTOR3 move = pPlayer->GetMove();
			float fRot = atan2f(ObjPos.x - m_Info.pos.x, ObjPos.z - m_Info.pos.z);	//目標までの移動差分

			// 移動方向を設定
			move.x = sinf(fRot) * FLYAWAY_SPEED;
			move.z = cosf(fRot) * FLYAWAY_SPEED;

			// 移動量を反映
			pPlayer->SetMove(move);

			pPlayer = pPlayerNext;	// 次に移動
		}
	}

	// 敵との判定
	{
		CEnemy *pEnemy = CEnemy::GetTop();

		while (pEnemy != nullptr)
		{
			CEnemy *pEnemyNext = pEnemy->GetNext();	// 次を保持

			// 距離を取る
			D3DXVECTOR3 ObjPos = pEnemy->GetPosition();
			float fLength = sqrtf((m_Info.pos.x - ObjPos.x) * (m_Info.pos.x - ObjPos.x)
				+ (m_Info.pos.z - ObjPos.z) * (m_Info.pos.z - ObjPos.z));

			if (fLength > m_Info.fRange) {	// 風の範囲内ではない場合
				pEnemy = pEnemyNext;
				continue;
			}

			D3DXVECTOR3 move = pEnemy->GetMove();
			float fRot = atan2f(ObjPos.x - m_Info.pos.x, ObjPos.z - m_Info.pos.z);	//目標までの移動差分

			// 移動方向を設定
			move.x = sinf(fRot) * FLYAWAY_SPEED;
			move.z = cosf(fRot) * FLYAWAY_SPEED;

			// 移動量を反映
			pEnemy->SetMove(move);

			pEnemy = pEnemyNext;	// 次に移動
		}
	}
}