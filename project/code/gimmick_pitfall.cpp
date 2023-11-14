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
	Release();
}

//==========================================================
// �X�V����
//==========================================================
void CGimmickPitFall::Update(void)
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
bool CGimmickPitFall::CollisionCheck(D3DXVECTOR3 & pos, D3DXVECTOR3 & posOld, D3DXVECTOR3 & move, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, int nAction)
{
	CXFile *pFile = CManager::GetInstance()->GetModelFile();
	bool bLand = false;	// ���n�������ۂ�
	D3DXVECTOR3 vtxObjMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vtxObjMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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

			if (pos.x + vtxMax.x > posObj.x + vtxObjMin.x
				&& pos.x + vtxMin.x < posObj.x + vtxObjMax.x
				&& pos.z + vtxMax.z > posObj.z + vtxObjMin.z
				&& pos.z + vtxMin.z < posObj.z + vtxObjMax.z)
			{//�͈͓��ɂ���
			 //�ォ��̔���
				if (posOld.y + vtxMin.y >= posObj.y + vtxObjMax.y
					&& pos.y + vtxMin.y < posObj.y + vtxObjMax.y)
				{//�ォ��߂荞��
				 //��ɂ̂���
					pos.y = posObj.y + vtxObjMax.y - vtxMin.y;
					move.y = 0.0f;
					bLand = true;
				}
			}
		}
	}

	//X
	for (int cnt = 0; cnt < FLOOR_MAX; cnt++)
	{
		// �����𔽉f
		m_apModel[cnt]->SetRotSize(vtxObjMax,
			vtxObjMin,
			pFile->GetMax(m_apModel[cnt]->GetId()),
			pFile->GetMin(m_apModel[cnt]->GetId()),
			m_apModel[cnt]->GetRotation().y);

		D3DXVECTOR3 posObj = m_apModel[cnt]->GetPosition();

		if (pos.y + vtxMax.y > posObj.y + vtxObjMin.y
			&& pos.y + vtxMin.y < posObj.y + vtxObjMax.y
			&& pos.z + vtxMax.z > posObj.z + vtxObjMin.z
			&& pos.z + vtxMin.z < posObj.z + vtxObjMax.z)
		{//�͈͓��ɂ���
			if (posOld.x + vtxMin.x >= posObj.x + vtxObjMax.x
				&& pos.x + vtxMin.x < posObj.x + vtxObjMax.x)
			{//�E���獶�ɂ߂荞��
				move.x = 0.0f;
				pos.x = posObj.x + vtxObjMax.x - vtxMin.x + 0.1f + move.x;
			}
			else if (posOld.x + vtxMax.x <= posObj.x + vtxObjMin.x
				&& pos.x + vtxMax.x > posObj.x + vtxObjMin.x)
			{//������E�ɂ߂荞��
			 //�ʒu��߂�
				move.x = 0.0f;
				pos.x = posObj.x + vtxObjMin.x - vtxMax.x - 0.1f + move.x;
			}
		}
	}

	//Z
	for (int cnt = 0; cnt < FLOOR_MAX; cnt++)
	{
		// �����𔽉f
		m_apModel[cnt]->SetRotSize(vtxObjMax,
			vtxObjMin,
			pFile->GetMax(m_apModel[cnt]->GetId()),
			pFile->GetMin(m_apModel[cnt]->GetId()),
			m_apModel[cnt]->GetRotation().y);

		D3DXVECTOR3 posObj = m_apModel[cnt]->GetPosition();

		if (pos.x + vtxMax.x > posObj.x + vtxObjMin.x
			&& pos.x + vtxMin.x < posObj.x + vtxObjMax.x
			&& pos.y + vtxMax.y > posObj.y + vtxObjMin.y
			&& pos.y + vtxMin.y < posObj.y + vtxObjMax.y)
		{//�͈͓��ɂ���
			if (posOld.z + vtxMin.z >= posObj.z + vtxObjMax.z
				&& pos.z + vtxMin.z < posObj.z + vtxObjMax.z)
			{//�������O�ɂ߂荞��
			 //�ʒu��߂�
				move.z = 0.0f;
				pos.z = posObj.z + vtxObjMax.z - vtxMin.z + 0.1f + move.z;
			}
			else if (posOld.z + vtxMax.z <= posObj.z + vtxObjMin.z
				&& pos.z + vtxMax.z > posObj.z + vtxObjMin.z)
			{//��O���牜�ɂ߂荞��
			 //�ʒu��߂�
				move.z = 0.0f;
				pos.z = posObj.z + vtxObjMin.z - vtxMax.z - 0.1f + move.z;
			}
		}
	}

	return bLand;
}
