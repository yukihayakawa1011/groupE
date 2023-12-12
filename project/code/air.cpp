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
#include "meshcylinder.h"
#include "texture.h"
#include "item.h"

// �������O���
namespace {
	const float MAX_LENGTH = (500.0f);	// �ő�͈̔�
	const float RANGE_UPSPEED = (5.0f);	// 1�t���[���Ԃ͈̔͑�����
	const float FLYAWAY_SPEED = (100.0f);	// ������ԑ��x(���������ϐ���)
	const float ITEMAWAY_SPEED = (18.0f);	// �A�C�e���̐�����ԑ��x
	const float ITEMAWAY_JUMP = (15.0f);
	const float AIROBJ_HEIGHT = (40.0f);	// �I�u�W�F�N�g�̍���
	const int OBJ_NUMWIDTH = (10);		// ������
	const float FLYAWAY_JUMP = (20.0f);	// ������ԍ���
	const char* FILENAME[CAir::TYPE_MAX] = {	// �e�N�X�`���t�@�C����
		"data\\TEXTURE\\wind000.png",
		"data\\TEXTURE\\wind001.png"
	};
}

//==========================================================
// �R���X�g���N�^
//==========================================================
CAir::CAir()
{
	// �l�̃N���A
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++) {
		m_apObject[nCnt] = nullptr;
	}
	m_Info.fRange = 0.0f;
	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&m_Info.mtxWorld);
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
	// �I�u�W�F�N�g�̐���
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++) {
		m_apObject[nCnt] = CMeshCylinder::Create(m_Info.pos, m_Info.rot, m_Info.fRange, AIROBJ_HEIGHT, 5, OBJ_NUMWIDTH);
		m_apObject[nCnt]->BindTexture(CManager::GetInstance()->GetTexture()->Regist(FILENAME[nCnt]));
	}

	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CAir::Uninit(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++) {
		if (m_apObject[nCnt] != nullptr) {
			m_apObject[nCnt]->Uninit();
			m_apObject[nCnt] = nullptr;
		}
	}

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

		// �����蔻������
		Collision();
	}

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++) {
		if (m_apObject[nCnt] != nullptr) {
			m_apObject[nCnt]->SetLength(m_Info.fRange);
			m_apObject[nCnt]->SetPosition(m_Info.pos);

			// ���݂̊��������߂�
			float fRate = m_Info.fRange / MAX_LENGTH;
			float fAdd = 0.1f;
			float fMulti = 0.15f;

			if (nCnt == TYPE_ANOTHER) {
				fAdd *= -1.0f;
				fMulti *= -1.0f;
			}

			D3DXVECTOR3 rot = m_apObject[nCnt]->GetRotation();
			rot.y += fAdd + (fRate * fMulti);
			m_apObject[nCnt]->SetRotation(rot);
			m_apObject[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (fRate * 0.75f)));
		}
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
			if (move.y <= 0.0f)
			{
				move.y = FLYAWAY_JUMP;
			}
			move.z = cosf(fRot) * FLYAWAY_SPEED;

			// �ړ��ʂ𔽉f
			pPlayer->SetMove(move);
			pPlayer->Blow();

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
			if (move.y <= 0.0f)
			{
				move.y = FLYAWAY_JUMP;
			}
			move.z = cosf(fRot) * FLYAWAY_SPEED;

			// �ړ��ʂ𔽉f
			pEnemy->SetMove(move);
			pEnemy->Blow();

			pEnemy = pEnemyNext;	// ���Ɉړ�
		}
	}

	// �A�C�e���Ƃ̔���
	{
		CItem *pItem = CItem::GetTop();

		while (pItem != nullptr)
		{
			CItem *pItemNext = pItem->GetNext();	// ����ێ�

													// ���������
			D3DXVECTOR3 ObjPos = pItem->GetPosition();
			float fLength = sqrtf((m_Info.pos.x - ObjPos.x) * (m_Info.pos.x - ObjPos.x)
				+ (m_Info.pos.z - ObjPos.z) * (m_Info.pos.z - ObjPos.z));

			if (fLength > m_Info.fRange || m_Info.pos.y + AIROBJ_HEIGHT <= ObjPos.y) {	// ���͈͓̔��ł͂Ȃ��ꍇ
				pItem = pItemNext;
				continue;
			}

			D3DXVECTOR3 move = pItem->GetMove();
			float fRot = atan2f(ObjPos.x - m_Info.pos.x, ObjPos.z - m_Info.pos.z);	//�ڕW�܂ł̈ړ�����

			// �ړ�������ݒ�
			move.x = sinf(fRot) * ITEMAWAY_SPEED;
			if (move.y <= 0.0f)
			{
				move.y = ITEMAWAY_JUMP;
			}
			move.z = cosf(fRot) * ITEMAWAY_SPEED;

			// �ړ��ʂ𔽉f
			pItem->SetMove(move);
			pItem->SetState(CItem::STATE_DROP);

			pItem = pItemNext;	// ���Ɉړ�
		}
	}
}