//==========================================================
//
// ���Ƃ��� [pitfall.cpp]
// Author : Soma Ishihara
//
//==========================================================
#include "pitfall.h"
#include "objectX.h"
#include "input.h"
#include "manager.h"

// �}�N����`
#define ROTATE_ANGLE	(0.05f * D3DX_PI)	//���̊J���p�x

//==========================================================
// �R���X�g���N�^
//==========================================================
CPitFall::CPitFall()
{
	// �l�̃N���A
	m_bOpen = false;
	m_fAngle = 0.0f;
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CPitFall::~CPitFall()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CPitFall::Init(void)
{
	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CPitFall::Uninit(void)
{
	Release();
}

//==========================================================
// �X�V����
//==========================================================
void CPitFall::Update(void)
{
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetInputKeyboard();
	if (pKeyboard->GetPress(DIK_F) == true)
	{
		m_bOpen = true;
	}
	else
	{
		m_bOpen = false;
	}

	//�J�ɂ��p�x�ݒ�
	if (m_bOpen == true)
	{//�J���Ă�
		m_fAngle += ROTATE_ANGLE;
		if (m_fAngle > 0.5f * D3DX_PI)
		{
			m_fAngle = 0.5f * D3DX_PI;
		}
	}
	else
	{//���Ă�
		m_fAngle -= ROTATE_ANGLE;
		if (m_fAngle < 0.0f * D3DX_PI)
		{
			m_fAngle = 0.0f * D3DX_PI;
		}
	}

	//���f���ɐݒ�
	D3DXVECTOR3 rot = m_pObjFloor[0]->GetRotation();
	m_pObjFloor[0]->SetRotation(D3DXVECTOR3(0.0f, rot.y, -m_fAngle));
	m_pObjFloor[0]->SetEnableCollision(!m_bOpen);

	rot = m_pObjFloor[1]->GetRotation();
	m_pObjFloor[1]->SetRotation(D3DXVECTOR3(0.0f, rot.y, -m_fAngle));
	m_pObjFloor[1]->SetEnableCollision(!m_bOpen);
}

//==========================================================
// ����
//==========================================================
CPitFall *CPitFall::Create(const D3DXVECTOR3 pos)
{
	CPitFall *pSample = nullptr;

	pSample = new CPitFall;

	if (pSample != nullptr)
	{
		// ����������
		pSample->Init();

		//�I�u�W�F�N�g����
		pSample->m_pObjFloor[0] = CObjectX::Create(pos - D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\pitfall_floor.x");	//����
		pSample->m_pObjFloor[1] = CObjectX::Create(pos + D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), "data\\MODEL\\pitfall_floor.x");	//�E��
	}

	return pSample;
}