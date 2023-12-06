//==========================================================
//
// ���Ƃ��� [gimmick_pitfall.cpp]
// Author : Soma Ishihara
//
//==========================================================
#include "gimmick_pitfall.h"
#include "Xfile.h"
#include "model.h"
#include "input.h"
#include "manager.h"
#include "gimmick_button.h"

// �}�N����`
#define ROTATE_ANGLE	(0.05f * D3DX_PI)	//���̊J���p�x

//==========================================================
// �R���X�g���N�^
//==========================================================
CGimmickPitFall::CGimmickPitFall()
{
	// �l�̃N���A
	m_bOpen = false;
	m_fAngle = 0.0f;
	m_pButton = nullptr;
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CGimmickPitFall::~CGimmickPitFall()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CGimmickPitFall::Init(void)
{
	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CGimmickPitFall::Uninit(void)
{
	ListOut();
	Release();
}

//==========================================================
// �X�V����
//==========================================================
void CGimmickPitFall::Update(void)
{
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetInputKeyboard();

	if (m_pButton != nullptr) {	// �{�^�����g�p����Ă���
		if (m_pButton->GetState() == CGimmickButton::STATE_PRESS) {	// �{�^����������Ă���
			m_bOpen = true;
		}
		else {	// ������Ă��Ȃ�
			m_bOpen = false;
		}
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
	D3DXVECTOR3 rot = m_apModel[0]->GetRotation();
	m_apModel[0]->SetRotation(D3DXVECTOR3(0.0f, rot.y, -m_fAngle));

	rot = m_apModel[1]->GetRotation();
	m_apModel[1]->SetRotation(D3DXVECTOR3(0.0f, rot.y, -m_fAngle));
}

//==========================================================
// ����
//==========================================================
CGimmickPitFall *CGimmickPitFall::Create(const D3DXVECTOR3 pos)
{
	CGimmickPitFall *pPitFall = nullptr;

	pPitFall = new CGimmickPitFall;

	if (pPitFall != nullptr)
	{
		// ����������
		pPitFall->Init();
		pPitFall->SetPosition(pos);
		pPitFall->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		pPitFall->BindType(TYPE_PITFALL);

		//�I�u�W�F�N�g����
		//����
		pPitFall->m_apModel[FLOOR_LEFT] = CModel::Create("data\\MODEL\\pitfall_floor.x");
		pPitFall->m_apModel[FLOOR_LEFT]->SetPosition(pos - D3DXVECTOR3(100.0f, 0.0f, 0.0f));
		pPitFall->m_apModel[FLOOR_LEFT]->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		pPitFall->m_apModel[FLOOR_LEFT]->SetShadow();

		//�E��
		pPitFall->m_apModel[FLOOR_RIGHT] = CModel::Create("data\\MODEL\\pitfall_floor.x");
		pPitFall->m_apModel[FLOOR_RIGHT]->SetPosition(pos + D3DXVECTOR3(100.0f, 0.0f, 0.0f));
		pPitFall->m_apModel[FLOOR_RIGHT]->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
		pPitFall->m_apModel[FLOOR_RIGHT]->SetShadow();
	}

	return pPitFall;
}

//==========================================================
// �����蔻��
//==========================================================
bool CGimmickPitFall::CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, D3DXVECTOR3 &SetPos, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, int nAction, CGimmick **ppGimmick, bool* bLand)
{
	CXFile *pFile = CManager::GetInstance()->GetModelFile();
	D3DXVECTOR3 vtxObjMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vtxObjMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (bLand != nullptr)
	{
		*bLand = false;
	}

	//Y
	if (m_bOpen == false)
	{//�J���ĂȂ��Ƃ��̂ݓ����蔻����s��
		for (int cnt = 0; cnt < FLOOR_MAX; cnt++)
		{
			// �����𔽉f
			m_apModel[cnt]->SetRotSize(vtxObjMax,
				vtxObjMin,
				pFile->GetMax(m_apModel[cnt]->GetId()),
				pFile->GetMin(m_apModel[cnt]->GetId()),
				m_apModel[cnt]->GetRotation().y);

			D3DXVECTOR3 posObj = m_apModel[cnt]->GetPosition();

			if (pos.x + vtxMax.x >= posObj.x + vtxObjMin.x
				&& pos.x + vtxMin.x <= posObj.x + vtxObjMax.x
				&& pos.z + vtxMax.z >= posObj.z + vtxObjMin.z
				&& pos.z + vtxMin.z <= posObj.z + vtxObjMax.z)
			{//�͈͓��ɂ���
			 //�ォ��̔���
				if (posOld.y >= posObj.y + vtxObjMax.y
					&& pos.y < posObj.y + vtxObjMax.y)
				{//�ォ��߂荞��
				 //��ɂ̂���
					pos.y = posObj.y + vtxObjMax.y;
					move.y = 0.0f;
					if (bLand != nullptr)
					{
						*bLand = true;
					}
				}
			}
		}
	}

	return false;
}
