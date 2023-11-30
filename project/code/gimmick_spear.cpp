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
#include "gimmick_button.h"

// �}�N����`
#define COLLISION_RANGE	(300.0f)		// �����蔻��T�C�Y
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
	m_pInObj = nullptr;
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

	if (m_bActive) {
		StateSet();	// ��ԊǗ�
	}

	// ��ލX�V
	UpdateType();

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
CGimmickSpear *CGimmickSpear::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, TYPE type)
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
		pSample->BindType(type);
		pSample->CGimmick::BindType(TYPE_SPEAR);
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
bool CGimmickSpear::CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, D3DXVECTOR3 &SetPos, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, int nAction, CGimmick **ppGimmick, bool* bLand)
{
	D3DXVECTOR3 ObjPos = GetPosition();
	D3DXVECTOR3 ObjRot = GetRotation();

	if (m_type == TYPE_SENSOR) {

		// �͈͓��`�F�b�N
		{
			float fLength =
				sqrtf((pos.x - ObjPos.x) * (pos.x - ObjPos.x)
					+ (pos.z - ObjPos.z) * (pos.z - ObjPos.z));

			if (fLength < COLLISION_RANGE)
			{
				m_bActive = true;
			}
		}
	}

	if (m_state < STATE_APPEAR || m_state > STATE_ATKNOW) {	// �J����
		return false;
	}

	bool bValue = false;
	CXFile *pFile = CManager::GetInstance()->GetModelFile();
	D3DXVECTOR3 vtxObjMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vtxObjMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �����𔽉f
	m_pObj->SetRotSize(vtxObjMax,
		vtxObjMin,
		pFile->GetMax(m_pObj->GetId()),
		pFile->GetMin(m_pObj->GetId()),
		ObjRot.y);

	if (pos.x + vtxMax.x > ObjPos.x + vtxObjMin.x
		&& pos.x + vtxMin.x < ObjPos.x + vtxObjMax.x
		&& pos.z + vtxMax.z > ObjPos.z + vtxObjMin.z
		&& pos.z + vtxMin.z < ObjPos.z + vtxObjMax.z) {	// �͈͓�

		if (pos.y + vtxMin.y >= ObjPos.y + vtxObjMin.y + vtxMin.y && pos.y <= ObjPos.y + vtxObjMax.y) {	// �������͈͓�
			bValue = true;
		}
	}

	return bValue;
}

//==========================================================
// ��ނ��Ƃ̍X�V
//==========================================================
void CGimmickSpear::UpdateType(void)
{
	// ��Ԃɍ��킹�ă{�^���̐F��ύX
	switch (m_type)
	{
	case TYPE_AUTO:	// ����
	{	 
		m_bActive = true;
	}
	break;

	case TYPE_PRESS:
	{
		if (m_pInObj == nullptr) {
			return;
		}

		if (m_pInObj->GetState() == CGimmickButton::STATE_PRESS) {	// ������Ă���
			m_bActive = true;
		}
		else
		{
			if (m_state == STATE_NONE) {
				m_bActive = false;
				m_nStateCounter = 0;
			}
		}
	}
	break;

	case TYPE_PRESSAUTO:
	{
		if (m_pInObj == nullptr) {
			return;
		}

		if (m_pInObj->GetState() == CGimmickButton::STATE_PRESS) {	// ������Ă���
			m_bActive = true;
			m_type = TYPE_AUTO;
		}
		else
		{
			m_bActive = false;
		}
	}
	break;

	case TYPE_SENSOR: 
	{
		if (m_state == STATE_NONE) {
			m_bActive = false;
			m_nStateCounter = 0;
		}
	}
	break;

	default:

		break;
	}
}