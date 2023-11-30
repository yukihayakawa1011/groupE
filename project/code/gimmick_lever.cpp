//==========================================================
//
// �M�~�b�N���o�[ [gimmick_lever.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "gimmick_lever.h"
#include "model.h"
#include "manager.h"
#include "debugproc.h"
#include "player.h"

// �}�N����`
#define COLLISION_RANGE	(50.0f)
#define INTERVAL			(90)

// �ÓI�����o�ϐ��錾
char *CGimmickLever::m_apFileName[MODEL_MAX] = {
	"data\\MODEL\\lever_frame.x",
	"data\\MODEL\\lever.x",
};

//==========================================================
// �R���X�g���N�^
//==========================================================
CGimmickLever::CGimmickLever()
{
	// �l�̃N���A
	for (int nCnt = 0; nCnt < MODEL_MAX; nCnt++)
	{
		m_apObj[nCnt] = nullptr;
	}

	m_nInterval = 0;
	m_state = STATE_NONE;
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CGimmickLever::~CGimmickLever()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CGimmickLever::Init(void)
{
	// ���f���̐���
	for (int nCnt = 0; nCnt < MODEL_MAX; nCnt++)
	{
		m_apObj[nCnt] = CModel::Create(m_apFileName[nCnt]);

		if (m_apObj[nCnt] != nullptr)
		{
			m_apObj[nCnt]->SetShadow(false);
			m_apObj[nCnt]->SetParent(GetMtxWorld());
		}
	}

	m_apObj[MODEL_BUTTON]->SetCurrentRotation(D3DXVECTOR3(D3DX_PI * 0.15f, 0.0f, 0.0f));

	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CGimmickLever::Uninit(void)
{
	// �l�̃N���A
	for (int nCnt = 0; nCnt < MODEL_MAX; nCnt++)
	{
		if (m_apObj[nCnt] != nullptr)
		{
			m_apObj[nCnt]->Uninit();
			m_apObj[nCnt] = nullptr;
		}
	}

	// ���X�g����폜
	ListOut();

	// �����[�X
	Release();
}

//==========================================================
// �X�V����
//==========================================================
void CGimmickLever::Update(void)
{
	if (m_nInterval > 0){
		m_nInterval--;
	}

	// �}�g���b�N�X�ݒ�
	SetMtxWorld();

	// ��Ԃɍ��킹�ă{�^���̐F��ύX
	switch (m_state)
	{
	case STATE_NONE:	// �����Ȃ�
		m_RotDest = D3DXVECTOR3(D3DX_PI * 0.15f, 0.0f, 0.0f);
		break;

	case STATE_PRESS:	// ������Ă���
		m_RotDest = D3DXVECTOR3(-D3DX_PI * 0.15f, 0.0f, 0.0f);
		break;
	}

	if (m_apObj[MODEL_BUTTON] != nullptr) {
		D3DXVECTOR3 rot = m_apObj[MODEL_BUTTON]->GetCurrentRotation();
		D3DXVECTOR3 rotDiff = m_RotDest - rot;

		rot += rotDiff * 0.1f;
		m_apObj[MODEL_BUTTON]->SetCurrentRotation(rot);
	}
}

//==========================================================
// ����
//==========================================================
CGimmickLever *CGimmickLever::Create(const D3DXVECTOR3 pos)
{
	CGimmickLever *pSample = nullptr;

	pSample = new CGimmickLever;

	if (pSample != nullptr)
	{
		// ����������
		pSample->Init();
	
		pSample->SetPosition(pos);
		pSample->BindType(TYPE_LEVER);
	}

	return pSample;
}

//==========================================================
// ����m�F
//==========================================================
bool CGimmickLever::CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, D3DXVECTOR3 &SetPos, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, int nAction, CGimmick **ppGimmick, bool* bLand)
{
	bool bValue = false;
	D3DXVECTOR3 ObjPos = GetPosition();
	D3DXVECTOR3 ObjRot = GetRotation();

	// �͈͓��`�F�b�N
	float fLength =
		sqrtf((pos.x - ObjPos.x) * (pos.x - ObjPos.x)
			+ (pos.z - ObjPos.z) * (pos.z - ObjPos.z));

	if (fLength > COLLISION_RANGE) {		// �͈͊O
		return bValue;
	}

	if (nAction != CPlayer::ACTION_ATK) {
		return bValue;
	}

	if(m_nInterval > 0)
	{
		return bValue;
	}
	
	m_state = (STATE)(m_state ^ 1);	// �����ꂽ��Ԃɂ���
	m_nInterval = INTERVAL;			// �C���^�[�o��

	return bValue;
}