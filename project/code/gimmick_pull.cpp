//==========================================================
//
// �M�~�b�N������I�u�W�F�N�g [gimmick_pull.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "gimmick_pull.h"
#include "model.h"
#include "manager.h"
#include "debugproc.h"
#include "player.h"
#include "Xfile.h"
#include "particle.h"

// �������O���
namespace {
	const float COLLISION_RANGE = (50.0f);
	const float UPPOSITION = (150.0f);
	const float ROTATE_SPEED = (D3DX_PI * 0.045f);
	const float SET_POSZ = (75.0f);
	const float SET_POSX = (50.0f);
	const int PARTICLE_CT = (5);
}

// �ÓI�����o�ϐ��錾
char *CGimmickPull::m_pFileName = {
	"data\\MODEL\\jar.x",
};

//==========================================================
// �R���X�g���N�^
//==========================================================
CGimmickPull::CGimmickPull()
{
	// �l�̃N���A
	m_pObj = nullptr;
	m_pMtxParent = nullptr;
	m_state = STATE_NONE;
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CGimmickPull::~CGimmickPull()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CGimmickPull::Init(void)
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
void CGimmickPull::Uninit(void)
{
	// �l�̃N���A
	if (m_pObj != nullptr)
	{
		m_pObj->Uninit();
		m_pObj = nullptr;
	}

	// ���X�g����폜
	ListOut();

	// �����[�X
	Release();
}

//==========================================================
// �X�V����
//==========================================================
void CGimmickPull::Update(void)
{
	m_posOld = D3DXVECTOR3(GetMtxWorld()->_41, GetMtxWorld()->_42, GetMtxWorld()->_43);

	// ��Ԃɍ��킹�ă{�^���̐F��ύX
	switch (m_state)
	{
	case STATE_NONE:	// �����Ȃ�
		// �}�g���b�N�X�ݒ�
		SetMtxWorld();

		m_nParticleTimer--;
		if (m_nParticleTimer <= 0) {
			D3DXVECTOR3 pos = GetPosition();
			pos.y += 40.0f;
			CParticle::Create(pos, CEffect::TYPE_PULLSTAR);
			m_nParticleTimer = PARTICLE_CT;
		}

		break;

	case STATE_PULL:	// ������Ă���
	{
		// �}�g���b�N�X�ݒ�
		SetParentMatrix();

		m_nParticleTimer--;
		if (m_nParticleTimer <= 0) {
			D3DXVECTOR3 pos = GetPosition();
			pos.x = GetMtxWorld()->_41;
			pos.y = GetMtxWorld()->_42 + 50.0f;
			pos.z = GetMtxWorld()->_43;
			CParticle::Create(pos, CEffect::TYPE_PULLSMAKE);
			m_nParticleTimer = PARTICLE_CT - 2;
		}
	}
	break;
	}

	bool bLand = false;
	CGimmick *pGimmick = nullptr;
	CXFile *pFile = CManager::GetInstance()->GetModelFile();
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 SetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 pos = D3DXVECTOR3(GetMtxWorld()->_41, GetMtxWorld()->_42, GetMtxWorld()->_43);

	// �����𔽉f
	m_pObj->SetRotSize(vtxMax,
		vtxMin,
		pFile->GetMax(m_pObj->GetId()),
		pFile->GetMin(m_pObj->GetId()),
		0.0f);

	CGimmick::Collision(pos, m_posOld, m_move, SetPos, vtxMin, vtxMax, -1, &pGimmick, &bLand);
}

//==========================================================
// ����
//==========================================================
CGimmickPull *CGimmickPull::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CGimmickPull *pPull = nullptr;

	pPull = new CGimmickPull;

	if (pPull != nullptr)
	{
		// ����������
		pPull->Init();

		// �l�̐ݒ�
		pPull->SetPosition(pos);
		pPull->SetRotation(rot);
		pPull->BindType(TYPE_ROTATEDOOR);
	}

	return pPull;
}

//==========================================================
// ����m�F
//==========================================================
bool CGimmickPull::CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, D3DXVECTOR3 &SetPos, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, int nAction, CGimmick **ppGimmick, bool* bLand)
{
	bool bValue = false;

	if (m_pMtxParent != nullptr) {	// �N�ɂ��͂܂�Ă��Ȃ�
		return bValue;
	}

	if (ppGimmick == nullptr) {
		return bValue;
	}

	if (*ppGimmick != nullptr) {	// ���ɉ����̃M�~�b�N��G��Ă���
		return bValue;
	}

	D3DXVECTOR3 ObjPos = GetPosition();
	D3DXVECTOR3 ObjRot = GetRotation();

	CXFile *pFile = CManager::GetInstance()->GetModelFile();
	D3DXVECTOR3 vtxObjMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vtxObjMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �����𔽉f
	m_pObj->SetRotSize(vtxObjMax,
		vtxObjMin,
		pFile->GetMax(m_pObj->GetId()),
		pFile->GetMin(m_pObj->GetId()),
		ObjRot.y);

	if (pos.x + vtxMin.x <= ObjPos.x + vtxObjMax.x && pos.x + vtxMax.x >= ObjPos.x + vtxObjMin.x &&
		pos.z + vtxMin.z <= ObjPos.z + vtxObjMax.z && pos.z + vtxMax.z >= ObjPos.z + vtxObjMin.z) {
		
		if (nAction == CPlayer::ACTION_CATCH) {
			m_state = STATE_PULL;
			SetPosition(D3DXVECTOR3(0.0f, 0.0f, -100.0f));
			SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			*ppGimmick = this;
		}
	}

	return bValue;
}

//==========================================================
// �e�̃}�g���b�N�X�Ƒg�ݍ��킹��
//==========================================================
void CGimmickPull::SetParentMatrix(void)
{
	if (m_pMtxParent == NULL)
	{// �o���Ă���ꍇ
		SetPosition(D3DXVECTOR3(GetMtxWorld()->_41, GetMtxWorld()->_42, GetMtxWorld()->_43));
		m_state = STATE_NONE;
		return;
	}

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX *pMtxWorld = GetMtxWorld();	// �e�̃}�g���b�N�X���
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRotation();

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(pMtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(pMtxWorld, pMtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(pMtxWorld, pMtxWorld, &mtxTrans);

	// �p�[�c�̃}�g���b�N�X�Ɛe�̃}�g���b�N�X���������킹��
	D3DXMatrixMultiply(pMtxWorld,
		pMtxWorld, m_pMtxParent);
}