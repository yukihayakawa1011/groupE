//==========================================================
//
// �X�e�[�W�J�ڃ{�^�� [gimmick_transbutton.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "gimmick_transbutton.h"
#include "model.h"
#include "manager.h"
#include "debugproc.h"

// �}�N����`
#define COLLISION_RANGE	(50.0f)

// �ÓI�����o�ϐ��錾
char *CGimmickTransButton::m_apFileName[MODEL_MAX] = {
	"data\\MODEL\\trans_button.x",
	"data\\MODEL\\button_frame.x",
};

//==========================================================
// �R���X�g���N�^
//==========================================================
CGimmickTransButton::CGimmickTransButton()
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
CGimmickTransButton::~CGimmickTransButton()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CGimmickTransButton::Init(void)
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

	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CGimmickTransButton::Uninit(void)
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
void CGimmickTransButton::Update(void)
{
	// �}�g���b�N�X�ݒ�
	SetMtxWorld();

	// ��Ԃɍ��킹�ă{�^���̐F��ύX
	switch (m_state)
	{
	case STATE_NONE:	// �����Ȃ�
		
		break;

	case STATE_PRESS:	// ������Ă���

		break;
	}

	m_state = STATE_NONE;
}

//==========================================================
// ����
//==========================================================
CGimmickTransButton *CGimmickTransButton::Create(const D3DXVECTOR3 pos)
{
	CGimmickTransButton *pSample = nullptr;

	pSample = new CGimmickTransButton;

	if (pSample != nullptr)
	{
		// ����������
		pSample->Init();
		pSample->SetPosition(pos);
	}

	return pSample;
}

//==========================================================
// ����m�F
//==========================================================
bool CGimmickTransButton::CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax)
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

	bValue = true;			// �G�ꂽ���
	m_state = STATE_PRESS;		// �����ꂽ��Ԃɂ���
	CManager::GetInstance()->GetDebugProc()->Print("������Ă����[\n");

	return bValue;
}