//==========================================================
//
// �M�~�b�N�����鑄 [gimmick_spear.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "gimmick_spear.h"
#include "model.h"
#include "manager.h"
#include "debugproc.h"
#include "player.h"
#include "Xfile.h"

// �}�N����`
#define COLLISION_RANGE	(50.0f)	// �����蔻��T�C�Y
#define SET_POSY			(-180.0f)	// �n�ʂɖ��܂��Ă鎞�̍��W�ݒ�

// �ÓI�����o�ϐ��錾
char *CGimmickSpear::m_pFileName = {
	"data\\MODEL\\spear.x",
};

// �ÓI�����o�ϐ��錾
int CGimmickSpear::m_aStateSetCount[CGimmickSpear::STATE_MAX] = {
	30,
	30,
	60,
	70,
};

float CGimmickSpear::m_aStateDiffMulti[CGimmickSpear::STATE_MAX] = {
	0.03f,
	0.35f,
	0.03f,
	0.03f,
};

//==========================================================
// �R���X�g���N�^
//==========================================================
CGimmickSpear::CGimmickSpear()
{
	// �l�̃N���A
	m_pObj = nullptr;
	m_state = STATE_NONE;
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CGimmickSpear::~CGimmickSpear()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CGimmickSpear::Init(void)
{
	// ���f���̐���
	m_pObj = CModel::Create(m_pFileName);

	if (m_pObj != nullptr)
	{
		m_pObj->SetShadow(true);
		m_pObj->SetParent(GetMtxWorld());
		m_pObj->SetCurrentPosition(D3DXVECTOR3(0.0f, SET_POSY, 0.0f));
	}

	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CGimmickSpear::Uninit(void)
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
void CGimmickSpear::Update(void)
{
	// �}�g���b�N�X�ݒ�
	SetMtxWorld();

	// ��ԊǗ�
	StateSet();

	CManager::GetInstance()->GetDebugProc()->Print("���̏��[ %d ] : �J�E���g [ %d ]\n", m_state, m_nStateCounter);


	if (m_pObj != nullptr) {	// �I�u�W�F�N�g���g���Ă���
		D3DXVECTOR3 pos = m_pObj->GetCurrentPosition();
		D3DXVECTOR3 posDiff = m_PosDest - pos;

		pos += posDiff * m_fDiffMulti;
		m_pObj->SetCurrentPosition(pos);
	}
}

//==========================================================
// ����
//==========================================================
CGimmickSpear *CGimmickSpear::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CGimmickSpear *pSample = nullptr;

	pSample = new CGimmickSpear;

	if (pSample != nullptr)
	{
		// ����������
		pSample->Init();

		// �l�̐ݒ�
		pSample->SetPosition(pos);
		pSample->SetRotation(rot);
		pSample->BindType(TYPE_SPEAR);
	}

	return pSample;
}

//==========================================================
// ��ԊǗ�
//==========================================================
void CGimmickSpear::StateSet(void)
{
	m_nStateCounter--;

	if (m_nStateCounter > 0) {
		return;
	}
	// ��Ԃɍ��킹�ă{�^���̐F��ύX
	switch (m_state)
	{
	case STATE_NONE:
	{
		m_state = STATE_APPEAR;
		m_PosDest.y = 0.0f;
	}
	break;

	case STATE_APPEAR:
	{
		m_state = STATE_ATKNOW;
		m_PosDest.y = 0.0f;
	}
	break;

	case STATE_ATKNOW:
	{
		m_state = STATE_BACK;
		m_PosDest.y = SET_POSY;
	}
	break;

	case STATE_BACK:
	{
		m_state = STATE_NONE;
		m_PosDest.y = SET_POSY;
	}
	break;

	default:

		break;
	}

	// ���̃J�E���g�ݒ�
	m_nStateCounter = m_aStateSetCount[m_state];
	m_fDiffMulti = m_aStateDiffMulti[m_state];
}

//==========================================================
// ����m�F
//==========================================================
bool CGimmickSpear::CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, D3DXVECTOR3 &SetPos, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, int nAction, CGimmick **ppGimmick)
{
	if (m_state >= STATE_NONE) {	// �J����
		return false;
	}

	bool bValue = false;
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

	//// X
	//if (pos.y + vtxMax.y > ObjPos.y + vtxObjMin.y
	//	&& pos.y + vtxMin.y < ObjPos.y + vtxObjMax.y
	//	&& pos.z + vtxMax.z > ObjPos.z + vtxObjMin.z
	//	&& pos.z + vtxMin.z < ObjPos.z + vtxObjMax.z)
	//{//�͈͓��ɂ���
	//	if (posOld.x + vtxMin.x >= ObjPos.x + vtxObjMax.x
	//		&& pos.x + vtxMin.x < ObjPos.x + vtxObjMax.x)
	//	{//�E���獶�ɂ߂荞��
	//		move.x = 0.0f;
	//		pos.x = ObjPos.x + vtxObjMax.x - vtxMin.x + 0.1f + move.x;

	//		if ((D3DX_PI * 0.5f == GetRotation().y || -D3DX_PI * 0.5f == GetRotation().y) && nAction == CPlayer::ACTION_ATK && m_state == STATE_NONE) {	// �U������
	//			m_state = STATE_ROTATE;
	//			m_RotDest.y += D3DX_PI;

	//			if (m_RotDest.y > D3DX_PI) {
	//				m_RotDest.y += -D3DX_PI * 2;
	//			}

	//			if (ppGimmick != nullptr) {
	//				*ppGimmick = this;
	//				SetPos.z = SET_POSZ;
	//			}
	//		}
	//	}
	//	else if (posOld.x + vtxMax.x <= ObjPos.x + vtxObjMin.x
	//		&& pos.x + vtxMax.x > ObjPos.x + vtxObjMin.x)
	//	{//������E�ɂ߂荞��
	//	 //�ʒu��߂�
	//		move.x = 0.0f;
	//		pos.x = ObjPos.x + vtxObjMin.x - vtxMax.x - 0.1f + move.x;

	//		if ((D3DX_PI * 0.5f == GetRotation().y || -D3DX_PI * 0.5f == GetRotation().y) && nAction == CPlayer::ACTION_ATK && m_state == STATE_NONE) {	// �U������
	//			m_state = STATE_ROTATE;
	//			m_RotDest.y += D3DX_PI;

	//			if (m_RotDest.y > D3DX_PI) {
	//				m_RotDest.y += -D3DX_PI * 2;
	//			}

	//			if (ppGimmick != nullptr) {
	//				*ppGimmick = this;
	//				SetPos.z = -SET_POSZ;
	//			}
	//		}
	//	}
	//}

	////Z
	//if (pos.x + vtxMax.x > ObjPos.x + vtxObjMin.x
	//	&& pos.x + vtxMin.x < ObjPos.x + vtxObjMax.x
	//	&& pos.y + vtxMax.y > ObjPos.y + vtxObjMin.y
	//	&& pos.y + vtxMin.y < ObjPos.y + vtxObjMax.y)
	//{//�͈͓��ɂ���
	//	if (posOld.z + vtxMin.z >= ObjPos.z + vtxObjMax.z
	//		&& pos.z + vtxMin.z < ObjPos.z + vtxObjMax.z)
	//	{//�������O�ɂ߂荞��
	//	 //�ʒu��߂�
	//		move.z = 0.0f;
	//		pos.z = ObjPos.z + vtxObjMax.z - vtxMin.z + 0.1f + move.z;

	//		if ((D3DX_PI * 1.0f == GetRotation().y || -D3DX_PI * 1.0f == GetRotation().y || 0.0f == GetRotation().y) && nAction == CPlayer::ACTION_ATK && m_state == STATE_NONE) {	// �U������
	//			m_state = STATE_ROTATE;
	//			m_RotDest.y += D3DX_PI;

	//			if (m_RotDest.y > D3DX_PI) {
	//				m_RotDest.y += -D3DX_PI * 2;
	//			}

	//			if (ppGimmick != nullptr) {
	//				*ppGimmick = this;
	//				SetPos.z = SET_POSZ;
	//			}
	//		}
	//	}
	//	else if (posOld.z + vtxMax.z <= ObjPos.z + vtxObjMin.z
	//		&& pos.z + vtxMax.z > ObjPos.z + vtxObjMin.z)
	//	{//��O���牜�ɂ߂荞��
	//	 //�ʒu��߂�
	//		move.z = 0.0f;
	//		pos.z = ObjPos.z + vtxObjMin.z - vtxMax.z - 0.1f + move.z;

	//		if ((D3DX_PI * 1.0f == GetRotation().y || -D3DX_PI * 1.0f == GetRotation().y || 0.0f == GetRotation().y) && nAction == CPlayer::ACTION_ATK && m_state == STATE_NONE) {	// �U������
	//			m_state = STATE_ROTATE;
	//			m_RotDest.y += D3DX_PI;

	//			if (m_RotDest.y > D3DX_PI) {
	//				m_RotDest.y += -D3DX_PI * 2;
	//			}

	//			if (ppGimmick != nullptr) {
	//				*ppGimmick = this;
	//				SetPos.z = -SET_POSZ;
	//			}
	//		}
	//	}
	//}

	////Y
	//if (pos.x + vtxMax.x > ObjPos.x + vtxObjMin.x
	//	&& pos.x + vtxMin.x < ObjPos.x + vtxObjMax.x
	//	&& pos.z + vtxMax.z > ObjPos.z + vtxObjMin.z
	//	&& pos.z + vtxMin.z < ObjPos.z + vtxObjMax.z)
	//{//�͈͓��ɂ���
	// //�ォ��̔���
	//	if (posOld.y + vtxMin.y >= ObjPos.y + vtxObjMax.y
	//		&& pos.y + vtxMin.y < ObjPos.y + vtxObjMax.y)
	//	{//�ォ��߂荞��
	//	 //��ɂ̂���
	//		pos.y = ObjPos.y + vtxObjMax.y - vtxMin.y;
	//		move.y = 0.0f;
	//		bValue = true;
	//	}
	//}

	return bValue;
}