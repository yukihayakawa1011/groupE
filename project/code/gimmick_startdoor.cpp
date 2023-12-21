//==========================================================
//
// �M�~�b�N�J�n�n�_�h�A [gimmick_startdoor.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "gimmick_startdoor.h"
#include "gimmick_lever.h"
#include "model.h"
#include "manager.h"
#include "debugproc.h"
#include "player.h"
#include "Xfile.h"
#include "sound.h"
#include "effect.h"

// �}�N����`
#define COLLISION_RANGE	(50.0f)
#define UPPOSITION		(150.0f)

// �ÓI�����o�ϐ��錾
char *CGimmickStartDoor::m_pFileName = {
	"data\\MODEL\\start_door.x",
};

//==========================================================
// �R���X�g���N�^
//==========================================================
CGimmickStartDoor::CGimmickStartDoor()
{
	// �l�̃N���A
	m_pObj = nullptr;
	m_state = STATE_NONE;
	m_nSoundUp = 0;
	m_nSoundDown = 0;

	for (int nCnt = 0; nCnt < DOOR_EFFECT::NUM_EFFECT; nCnt++) {
		m_apEffect[nCnt] = nullptr;
	}
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CGimmickStartDoor::~CGimmickStartDoor()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CGimmickStartDoor::Init(void)
{
	// ���f���̐���
	m_pObj = CModel::Create(m_pFileName);

	if (m_pObj != nullptr)
	{
		m_pObj->SetShadow(true);
		m_pObj->SetParent(GetMtxWorld());
	}

	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CGimmickStartDoor::Uninit(void)
{
	// �l�̃N���A
	if (m_pObj != nullptr)
	{
		m_pObj->Uninit();
		m_pObj = nullptr;
	}

	for (int nCnt = 0; nCnt < DOOR_EFFECT::NUM_EFFECT; nCnt++) {
		if (m_apEffect[nCnt] == nullptr) {
			continue;
		}
		m_apEffect[nCnt]->Uninit();
		m_apEffect[nCnt] = nullptr;
	}

	// ���X�g����폜
	ListOut();

	// �����[�X
	Release();
}

//==========================================================
// �X�V����
//==========================================================
void CGimmickStartDoor::Update(void)
{
	// �}�g���b�N�X�ݒ�
	SetMtxWorld();

	// ��Ԃɍ��킹�ă{�^���̐F��ύX
	switch (m_state)
	{
	case STATE_NONE:	// �����Ȃ�
		m_PosDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		m_nSoundDown++;

		if (m_nSoundDown == 1)
		{
			CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_OPEN02);
		}
		break;

	case STATE_OPEN:	// ������Ă���
		m_PosDest = D3DXVECTOR3(0.0f, UPPOSITION, 0.0f);
		m_nSoundUp++;

		if (m_nSoundUp == 1)
		{
			CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_OPEN02);
		}
	
		break;
	}

	if (m_pObj != nullptr) {	// �I�u�W�F�N�g���g���Ă���
		D3DXVECTOR3 pos = m_pObj->GetCurrentPosition();
		D3DXVECTOR3 posDiff = m_PosDest - pos;

		pos += posDiff * 0.1f;
		m_pObj->SetCurrentPosition(pos);

		if (m_PosDest.y == UPPOSITION && posDiff.y >= 0.1f && posDiff.y <= 5.0f)
		{
			// �G�t�F�N�g�𐶐�����
			for (int nCnt = 0; nCnt < DOOR_EFFECT::NUM_EFFECT; nCnt++) {
				if (m_apEffect[nCnt] != nullptr) {
					continue;
				}
				// ���W�̐ݒ�
				D3DXVECTOR3 pos = GetPosition();

				if (m_pObj != nullptr) {
					pos.x = m_pObj->GetMtx()->_41;
					pos.y = m_pObj->GetMtx()->_42;
					pos.z = m_pObj->GetMtx()->_43;
				}

				pos.x += sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 1.0f;
				pos.z += cosf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 1.0f;

				//�ړ��ʂ̐ݒ�
				D3DXVECTOR3 move = { 0.0f, 0.0f, 0.0f };
				move.x = sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.01f;
				move.y = ((float)(rand() % 10 + 1)) * 0.5f;
				move.z = cosf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.01f;

				float frand = rand() % 8 * 0.1f;

				//�F�̐ݒ�
				D3DXCOLOR col = D3DXCOLOR(frand, frand, frand, 1.0f);

				//���a�̐ݒ�
				float fRadius = 10.0f;

				//�����̐ݒ�
				float fLife = 200.0f;

				m_apEffect[nCnt] = CEffect::Create(pos + move, move, col, fRadius, fLife, CEffect::TYPE_DUST);
			}
		}
	}

	STATE stateOld = m_state;

	if (m_pLever != nullptr) {	// ���o�[���g���Ă���

		switch (m_pLever->GetState())
		{
		case CGimmickLever::STATE_NONE:
			m_state = STATE_NONE;
			break;

		case CGimmickLever::STATE_PRESS:
			m_state = STATE_OPEN;
			break;

		default:
			m_state = STATE_NONE;
			break;
		}
	}

	// �G�t�F�N�g�̍X�V����
	for (int nCnt = 0; nCnt < DOOR_EFFECT::NUM_EFFECT; nCnt++) {
		if (m_apEffect[nCnt] == nullptr) {
			continue;
		}

		// �X�V����
		m_apEffect[nCnt]->Update();

		if (m_apEffect[nCnt]->GetCol().a <= 0.0f || m_apEffect[nCnt]->GetRange() <= 0.0f || m_apEffect[nCnt]->GetLife() <= 0.0f) {	// �F���������������̓T�C�Y���������Ȃ���
			m_apEffect[nCnt]->Uninit();
			m_apEffect[nCnt] = nullptr;
		}
	}
}

//==========================================================
// ����
//==========================================================
CGimmickStartDoor *CGimmickStartDoor::Create(const D3DXVECTOR3 pos)
{
	CGimmickStartDoor *pSample = nullptr;

	pSample = new CGimmickStartDoor;

	if (pSample != nullptr)
	{
		// ����������
		pSample->Init();

		pSample->SetPosition(pos);
		pSample->BindType(TYPE_STARTDOOR);
	}

	return pSample;
}

//==========================================================
// ����m�F
//==========================================================
bool CGimmickStartDoor::CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, D3DXVECTOR3 &SetPos, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, int nAction, CGimmick **ppGimmick, bool* bLand)
{
	if (m_state == STATE_OPEN) {	// �J����
		return false;
	}

	bool bValue = false;
	D3DXVECTOR3 ObjPos = GetPosition();
	D3DXVECTOR3 ObjRot = GetRotation();

	CXFile *pFile = CManager::GetInstance()->GetModelFile();
	D3DXVECTOR3 vtxObjMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vtxObjMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �����𔽉f
	int nID = m_pObj->GetId();
	m_pObj->SetRotSize(vtxObjMax,
		vtxObjMin,
		pFile->GetMax(nID),
		pFile->GetMin(nID),
		GetRotation().y);

	// X
	if (pos.y + vtxMax.y > ObjPos.y + vtxObjMin.y
		&& pos.y + vtxMin.y < ObjPos.y + vtxObjMax.y
		&& pos.z + vtxMax.z > ObjPos.z + vtxObjMin.z
		&& pos.z + vtxMin.z < ObjPos.z + vtxObjMax.z)
	{//�͈͓��ɂ���
		if (posOld.x + vtxMin.x >= ObjPos.x + vtxObjMax.x
			&& pos.x + vtxMin.x < ObjPos.x + vtxObjMax.x)
		{//�E���獶�ɂ߂荞��
			move.x = 0.0f;
			pos.x = ObjPos.x + vtxObjMax.x - vtxMin.x + 0.1f + move.x;
		}
		else if (posOld.x + vtxMax.x <= ObjPos.x + vtxObjMin.x
			&& pos.x + vtxMax.x > ObjPos.x + vtxObjMin.x)
		{//������E�ɂ߂荞��
		 //�ʒu��߂�
			move.x = 0.0f;
			pos.x = ObjPos.x + vtxObjMin.x - vtxMax.x - 0.1f + move.x;
		}
	}

	//Z
	if (pos.x + vtxMax.x > ObjPos.x + vtxObjMin.x
		&& pos.x + vtxMin.x < ObjPos.x + vtxObjMax.x
		&& pos.y + vtxMax.y > ObjPos.y + vtxObjMin.y
		&& pos.y + vtxMin.y < ObjPos.y + vtxObjMax.y)
	{//�͈͓��ɂ���
		if (posOld.z + vtxMin.z >= ObjPos.z + vtxObjMax.z
			&& pos.z + vtxMin.z < ObjPos.z + vtxObjMax.z)
		{//�������O�ɂ߂荞��
		 //�ʒu��߂�
			move.z = 0.0f;
			pos.z = ObjPos.z + vtxObjMax.z - vtxMin.z + 0.1f + move.z;
		}
		else if (posOld.z + vtxMax.z <= ObjPos.z + vtxObjMin.z
			&& pos.z + vtxMax.z > ObjPos.z + vtxObjMin.z)
		{//��O���牜�ɂ߂荞��
		 //�ʒu��߂�
			move.z = 0.0f;
			pos.z = ObjPos.z + vtxObjMin.z - vtxMax.z - 0.1f + move.z;
		}
	}

	//Y
	if (pos.x + vtxMax.x > ObjPos.x + vtxObjMin.x
		&& pos.x + vtxMin.x < ObjPos.x + vtxObjMax.x
		&& pos.z + vtxMax.z > ObjPos.z + vtxObjMin.z
		&& pos.z + vtxMin.z < ObjPos.z + vtxObjMax.z)
	{// �͈͓��ɂ���
	 // �ォ��̔���
		if (posOld.y + vtxMin.y >= ObjPos.y + vtxObjMax.y
			&& pos.y + vtxMin.y < ObjPos.y + vtxObjMax.y)
		{//�ォ��߂荞��
			// ��ɂ̂���
			pos.y = ObjPos.y + vtxObjMax.y - vtxMin.y;
			move.y = 0.0f;
		}
	}

	return bValue;
}