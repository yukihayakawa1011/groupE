//==========================================================
//
// �M�~�b�N�J�n�n�_�h�A [gimmick_startdoor.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "gimmick_rotatedoor.h"
#include "model.h"
#include "manager.h"
#include "debugproc.h"
#include "player.h"
#include "Xfile.h"

// �������O���
namespace {
	const float COLLISION_RANGE = (50.0f);
	const float UPPOSITION = (150.0f);
	const float ROTATE_SPEED = (D3DX_PI * 0.045f);
	const float SET_POSZ = (75.0f);
	const float SET_POSX = (50.0f);
}

// �ÓI�����o�ϐ��錾
char *CGimmickRotateDoor::m_pFileName = {
	"data\\MODEL\\rotate_door000.x",
};

//==========================================================
// �R���X�g���N�^
//==========================================================
CGimmickRotateDoor::CGimmickRotateDoor()
{
	// �l�̃N���A
	m_pObj = nullptr;
	m_state = STATE_NONE;
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CGimmickRotateDoor::~CGimmickRotateDoor()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CGimmickRotateDoor::Init(void)
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
void CGimmickRotateDoor::Uninit(void)
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
void CGimmickRotateDoor::Update(void)
{
	// �}�g���b�N�X�ݒ�
	SetMtxWorld();

	// ��Ԃɍ��킹�ă{�^���̐F��ύX
	switch (m_state)
	{
	case STATE_NONE:	// �����Ȃ�
		
		break;

	case STATE_ROTATE:	// ������Ă���
	{
		if (m_pObj == nullptr) {
			return;
		}

		D3DXVECTOR3 rot = m_pObj->GetCurrentRotation();

		rot.y += ROTATE_SPEED;

		m_pObj->SetCurrentRotation(rot);

		if (rot.y >= m_RotDest.y)
		{// ������
			m_state = STATE_NONE;
			m_RotDest.y = 0.0f;
			rot.y = 0.0f;
			m_pObj->SetCurrentRotation(rot);
		}
	}
		break;
	}
}

//==========================================================
// ����
//==========================================================
CGimmickRotateDoor *CGimmickRotateDoor::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CGimmickRotateDoor *pSample = nullptr;

	pSample = new CGimmickRotateDoor;

	if (pSample != nullptr)
	{
		// ����������
		pSample->Init();

		// �l�̐ݒ�
		pSample->SetPosition(pos);
		pSample->SetRotation(rot);
		pSample->BindType(TYPE_ROTATEDOOR);
	}

	return pSample;
}

//==========================================================
// ����m�F
//==========================================================
bool CGimmickRotateDoor::CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, D3DXVECTOR3 &SetPos, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, int nAction, CGimmick **ppGimmick, bool* bLand)
{
	if (m_state == STATE_ROTATE) {	// �J����
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

			if ((D3DX_PI * 0.5f == GetRotation().y || -D3DX_PI * 0.5f == GetRotation().y) && nAction == CPlayer::ACTION_ATK && m_state == STATE_NONE) {	// �U������
				m_state = STATE_ROTATE;
				m_RotDest.y += D3DX_PI;

				if (m_RotDest.y > D3DX_PI) {
					m_RotDest.y += -D3DX_PI * 2;
				}

				if (ppGimmick != nullptr) {
					*ppGimmick = this;
					SetPos.z = SET_POSZ;
					SetPos.x = SET_POSX;
				}
			}
		}
		else if (posOld.x + vtxMax.x <= ObjPos.x + vtxObjMin.x
			&& pos.x + vtxMax.x > ObjPos.x + vtxObjMin.x)
		{//������E�ɂ߂荞��
		 //�ʒu��߂�
			move.x = 0.0f;
			pos.x = ObjPos.x + vtxObjMin.x - vtxMax.x - 0.1f + move.x;

			if ((D3DX_PI * 0.5f == GetRotation().y || -D3DX_PI * 0.5f == GetRotation().y) && nAction == CPlayer::ACTION_ATK && m_state == STATE_NONE) {	// �U������
				m_state = STATE_ROTATE;
				m_RotDest.y += D3DX_PI;

				if (m_RotDest.y > D3DX_PI) {
					m_RotDest.y += -D3DX_PI * 2;
				}

				if (ppGimmick != nullptr) {
					*ppGimmick = this;
					SetPos.z = -SET_POSZ;
					SetPos.x = -SET_POSX;
				}
			}
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

			if ((D3DX_PI * 1.0f == GetRotation().y || -D3DX_PI * 1.0f == GetRotation().y || 0.0f == GetRotation().y) && nAction == CPlayer::ACTION_ATK && m_state == STATE_NONE) {	// �U������
				m_state = STATE_ROTATE;
				m_RotDest.y += D3DX_PI;

				if (m_RotDest.y > D3DX_PI) {
					m_RotDest.y += -D3DX_PI * 2;
				}

				if (ppGimmick != nullptr) {
					*ppGimmick = this;
					SetPos.z = SET_POSZ;
					SetPos.x = SET_POSX;
				}
			}
		}
		else if (posOld.z + vtxMax.z <= ObjPos.z + vtxObjMin.z
			&& pos.z + vtxMax.z > ObjPos.z + vtxObjMin.z)
		{//��O���牜�ɂ߂荞��
		 //�ʒu��߂�
			move.z = 0.0f;
			pos.z = ObjPos.z + vtxObjMin.z - vtxMax.z - 0.1f + move.z;

			if ((D3DX_PI * 1.0f == GetRotation().y || -D3DX_PI * 1.0f == GetRotation().y || 0.0f == GetRotation().y) && nAction == CPlayer::ACTION_ATK && m_state == STATE_NONE) {	// �U������
				m_state = STATE_ROTATE;
				m_RotDest.y += D3DX_PI;

				if (m_RotDest.y > D3DX_PI) {
					m_RotDest.y += -D3DX_PI * 2;
				}

				if (ppGimmick != nullptr) {
					*ppGimmick = this;
					SetPos.z = -SET_POSZ;
					SetPos.x = -SET_POSX;
				}
			}
		}
	}

	//Y
	if (pos.x + vtxMax.x > ObjPos.x + vtxObjMin.x
		&& pos.x + vtxMin.x < ObjPos.x + vtxObjMax.x
		&& pos.z + vtxMax.z > ObjPos.z + vtxObjMin.z
		&& pos.z + vtxMin.z < ObjPos.z + vtxObjMax.z)
	{//�͈͓��ɂ���
	 //�ォ��̔���
		if (posOld.y + vtxMin.y >= ObjPos.y + vtxObjMax.y
			&& pos.y + vtxMin.y < ObjPos.y + vtxObjMax.y)
		{//�ォ��߂荞��
		 //��ɂ̂���
			pos.y = ObjPos.y + vtxObjMax.y - vtxMin.y;
			move.y = 0.0f;
		}
	}

	return bValue;
}