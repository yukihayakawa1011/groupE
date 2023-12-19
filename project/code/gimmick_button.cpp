//==========================================================
//
// �{�^�� [gimmick_button.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "gimmick_button.h"
#include "model.h"
#include "manager.h"
#include "debugproc.h"
#include "particle.h"
#include "Xfile.h"

// �ÓI�����o�ϐ��錾
char *CGimmickButton::m_apFileName[MODEL_MAX] = {
	"data\\MODEL\\trans_button.x",
	"data\\MODEL\\button_frame.x",
};

namespace
{
	const float COLLISION_RANGE = (50.0f);	// �����蔻�蔼�a
	const float PRESS_NOWHEIGHT = (-6.0f);	// ������Ă���ۂ̒��ޗ�
}

//==========================================================
// �R���X�g���N�^
//==========================================================
CGimmickButton::CGimmickButton()
{
	// �l�̃N���A
	for (int nCnt = 0; nCnt < MODEL_MAX; nCnt++)
	{
		m_apObj[nCnt] = nullptr;
	}

	m_state = STATE_NONE;
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CGimmickButton::~CGimmickButton()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CGimmickButton::Init(void)
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

	// �{�^���̕ύX��̐F��ݒ�
	if (m_apObj[MODEL_BUTTON] != nullptr) {
		D3DMATERIAL9 material = {};
		material.Ambient = D3DXCOLOR (0.1f, 0.1f, 1.0f, 1.0f);
		material.Diffuse = D3DXCOLOR (0.1f, 0.1f, 1.0f, 1.0f);
		material.Emissive = D3DXCOLOR(0.1f, 0.1f, 1.0f, 1.0f);
		m_apObj[MODEL_BUTTON]->SetMaterial(material);
	}

	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CGimmickButton::Uninit(void)
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
void CGimmickButton::Update(void)
{
	// �}�g���b�N�X�ݒ�
	SetMtxWorld();

	float fHeight = 0.0f;

	// ��Ԃɍ��킹�ă{�^���̐F��ύX
	switch (m_state)
	{
	case STATE_NONE:	// �����Ȃ�
		
		if (m_apObj[MODEL_BUTTON] != nullptr) {
			m_apObj[MODEL_BUTTON]->ChangeCol();
		}
		break;

	case STATE_PRESS:	// ������Ă���
		CParticle::Create(GetPosition(), CEffect::TYPE_BUTTON);
		fHeight = PRESS_NOWHEIGHT;
		if (m_apObj[MODEL_BUTTON] != nullptr) {
			m_apObj[MODEL_BUTTON]->ChangeCol(true);
		}
		break;
	}

	if (m_apObj[MODEL_BUTTON] == nullptr) {
		return;
	}

	D3DXVECTOR3 pos = m_apObj[MODEL_BUTTON]->GetCurrentPosition();
	float fDest = fHeight - pos.y;
	pos.y += fDest * 0.05f;
	m_apObj[MODEL_BUTTON]->SetCurrentPosition(pos);
}

//==========================================================
// ����
//==========================================================
CGimmickButton *CGimmickButton::Create(const D3DXVECTOR3 pos)
{
	CGimmickButton *pSample = nullptr;

	pSample = new CGimmickButton;

	if (pSample != nullptr)
	{
		// ����������
		pSample->Init();
		pSample->SetPosition(pos);
		pSample->BindType(TYPE_BUTTON);
	}

	return pSample;
}

//==========================================================
// ����m�F
//==========================================================
bool CGimmickButton::CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, D3DXVECTOR3 &SetPos, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, int nAction, CGimmick **ppGimmick, bool* bLand)
{
	bool bValue = false;
	D3DXVECTOR3 ObjPos = GetPosition();
	D3DXVECTOR3 ObjRot = GetRotation();

	// �͈͓��`�F�b�N
	float fLength =
		sqrtf((pos.x - ObjPos.x) * (pos.x - ObjPos.x)
			+ (pos.z - ObjPos.z) * (pos.z - ObjPos.z));

	if (fLength > COLLISION_RANGE){		// �͈͊O
		return bValue;
	}

	m_state = STATE_PRESS;		// �����ꂽ��Ԃɂ���
	CManager::GetInstance()->GetDebugProc()->Print("������Ă����[\n");

	return bValue;
}

//==========================================================
// �X�C�b�`�؂�ւ�
//==========================================================
void CGimmickButton::Switch(bool bUse)
{
	// ��Ԃɍ��킹�ă{�^���̐F��ύX
	switch (bUse)
	{
	case false:	// �����Ȃ�
		m_state = STATE_NONE;
		break;

	case true:	// ������Ă���
		m_state = STATE_PRESS;
		break;
	}
}

//==========================================================
// ��Ԃ��擾
//==========================================================
CGimmickButton::STATE CGimmickButton::GetState(void)
{
	return m_state;
}

//==========================================================
// �g���b�v�F�ɕύX
//==========================================================
void CGimmickButton::TrapMaterial(void)
{
	if (m_apObj[MODEL_BUTTON] != nullptr) {
		m_apObj[MODEL_BUTTON]->BindModelFile(
			CManager::GetInstance()->GetModelFile()->Regist("data\\MODEL\\trans_button_trap.x")
		);
	}
}

//==========================================================
// �F�ύX
//==========================================================
void CGimmickButton::SetPressMaterial(const D3DMATERIAL9& mat)
{
	if (m_apObj[MODEL_BUTTON] == nullptr) {
		return;
	}

	m_apObj[MODEL_BUTTON]->SetMaterial(mat);
}