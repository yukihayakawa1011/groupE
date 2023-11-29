//==========================================================
//
// ���̏p [air.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "air.h"
#include "player.h"
#include "enemy.h"
#include "manager.h"
#include "debugproc.h"

// �������O���
namespace {
	const float MAX_LENGTH = (500.0f);	// �ő�͈̔�
	const float RANGE_UPSPEED = (5.0f);	// 1�t���[���Ԃ͈̔͑�����
	const float FLYAWAY_SPEED = (300.0f);	// ������ԑ��x(���������ϐ���)
}

//==========================================================
// �R���X�g���N�^
//==========================================================
CAir::CAir()
{
	// �l�̃N���A
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CAir::~CAir()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CAir::Init(void)
{
	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CAir::Uninit(void)
{
	Release();
}

//==========================================================
// �X�V����
//==========================================================
void CAir::Update(void)
{
	m_Info.fRange += RANGE_UPSPEED;

	if (m_Info.fRange > MAX_LENGTH) {	// �ő�͈͂𒴂���
		Uninit();
	}
	else
	{
		CManager::GetInstance()->GetDebugProc()->Print("�͈�[%f]\n", m_Info.fRange);
		// �����蔻������
		Collision();
	}
}

//==========================================================
// ����
//==========================================================
CAir *CAir::Create(const D3DXVECTOR3& pos, const int nId)
{
	CAir *pAir = nullptr;

	pAir = new CAir;

	if (pAir != nullptr)
	{
		// ����������
		pAir->Init();

		// ���W�̐ݒ�
		pAir->SetPosition(pos);

		// ID�̐ݒ�
		pAir->BindId(nId);
	}

	return pAir;
}

//==========================================================
// �����蔻��
//==========================================================
void CAir::Collision(void)
{
	// �v���C���[�Ƃ̔���
	{
		CPlayer *pPlayer = CPlayer::GetTop();

		while (pPlayer != nullptr) 
		{
			CPlayer *pPlayerNext = pPlayer->GetNext();	// ����ێ�

			if (pPlayer->GetId() == m_nId) {	// �o�����{�l
				pPlayer = pPlayerNext;
				continue;
			}

			// ���������
			D3DXVECTOR3 ObjPos = pPlayer->GetPosition();
			float fLength = sqrtf((m_Info.pos.x - ObjPos.x) * (m_Info.pos.x - ObjPos.x)
				+ (m_Info.pos.z - ObjPos.z) * (m_Info.pos.z - ObjPos.z));

			if (fLength > m_Info.fRange) {	// ���͈͓̔��ł͂Ȃ��ꍇ
				pPlayer = pPlayerNext;
				continue;
			}

			D3DXVECTOR3 move = pPlayer->GetMove();
			float fRot = atan2f(ObjPos.x - m_Info.pos.x, ObjPos.z - m_Info.pos.z);	//�ڕW�܂ł̈ړ�����

			// �ړ�������ݒ�
			move.x = sinf(fRot) * FLYAWAY_SPEED;
			move.z = cosf(fRot) * FLYAWAY_SPEED;

			// �ړ��ʂ𔽉f
			pPlayer->SetMove(move);

			pPlayer = pPlayerNext;	// ���Ɉړ�
		}
	}

	// �G�Ƃ̔���
	{
		CEnemy *pEnemy = CEnemy::GetTop();

		while (pEnemy != nullptr)
		{
			CEnemy *pEnemyNext = pEnemy->GetNext();	// ����ێ�

			// ���������
			D3DXVECTOR3 ObjPos = pEnemy->GetPosition();
			float fLength = sqrtf((m_Info.pos.x - ObjPos.x) * (m_Info.pos.x - ObjPos.x)
				+ (m_Info.pos.z - ObjPos.z) * (m_Info.pos.z - ObjPos.z));

			if (fLength > m_Info.fRange) {	// ���͈͓̔��ł͂Ȃ��ꍇ
				pEnemy = pEnemyNext;
				continue;
			}

			D3DXVECTOR3 move = pEnemy->GetMove();
			float fRot = atan2f(ObjPos.x - m_Info.pos.x, ObjPos.z - m_Info.pos.z);	//�ڕW�܂ł̈ړ�����

			// �ړ�������ݒ�
			move.x = sinf(fRot) * FLYAWAY_SPEED;
			move.z = cosf(fRot) * FLYAWAY_SPEED;

			// �ړ��ʂ𔽉f
			pEnemy->SetMove(move);

			pEnemy = pEnemyNext;	// ���Ɉړ�
		}
	}
}