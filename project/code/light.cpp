//==========================================================
//
// ���C�g�̏����S�� [light.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "light.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"

//==========================================================
// �R���X�g���N�^
//==========================================================
CLight::CLight()
{
	
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CLight::~CLight()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CLight::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		// �f�o�C�X�ւ̃|�C���^���擾
	D3DXVECTOR3 vecDir;		// �ݒ�ύX�p�x�N�g��

	for (int nCntLight = 0; nCntLight < NUM_LIGHT - 1; nCntLight++)
	{
		// ���C�g�̏����N���A����
		ZeroMemory(&m_aLight[nCntLight], sizeof(D3DLIGHT9));

		// ���C�g�̎�ނ�ݒ�
		m_aLight[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		// ���C�g�̊g�U����ݒ�
		switch (nCntLight)
		{
		case 0:
			m_aLight[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			break;
		case 1:
			m_aLight[nCntLight].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);
			break;
		case 2:
			m_aLight[nCntLight].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);
			break;
		case 3:
			m_aLight[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			break;
		}
		// ���C�g�̕�����ݒ�
		switch (nCntLight)
		{
		case 0:
			//vecDir = D3DXVECTOR3(0.1f, -0.11f, 0.44f);
			//vecDir = D3DXVECTOR3(0.8f, 0.23f, -0.55f);
			vecDir = D3DXVECTOR3(-0.05f, -0.87f, 0.05f);

			break;
		case 1:
			vecDir = D3DXVECTOR3(0.46f, 0.88f, -0.44f);
			break;
		case 2:
			vecDir = D3DXVECTOR3(-0.60f, -0.82f, 0.42f);
			break;
		case 3:
			vecDir = D3DXVECTOR3(0.22f, -0.87f, -0.44f);
			break;
		}

		D3DXVec3Normalize(&vecDir, &vecDir);	// �x�N�g���𐳋K������
		m_aLight[nCntLight].Direction = vecDir;

		// ���C�g��ݒ肷��
		pDevice->SetLight(nCntLight, &m_aLight[nCntLight]);

		// ���C�g��L��������
		pDevice->LightEnable(nCntLight, TRUE);
	}

	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CLight::Uninit(void)
{

}

//==========================================================
// �X�V����
//==========================================================
void CLight::Update(void)
{

}

//==========================================================
// �F�ݒ�
//==========================================================
void CLight::SetLight(float fDiff)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		// �f�o�C�X�ւ̃|�C���^���擾

	for (int nCntLight = 0; nCntLight < NUM_LIGHT - 1; nCntLight++)
	{
		// ���C�g�̎�ނ�ݒ�
		m_aLight[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		if (fDiff >= 0.0f && fDiff < 0.5f)
		{
			// ���C�g�̊g�U����ݒ�
			switch (nCntLight)
			{
			case 0:
				m_aLight[nCntLight].Diffuse = D3DXCOLOR(0.1f + fDiff * 2, 0.1f + fDiff * 2, 0.1f + fDiff * 2, 1.0f);
				break;
			case 1:
				m_aLight[nCntLight].Diffuse = D3DXCOLOR(0.065f + fDiff * 2 * 0.65f, 0.065f + fDiff * 2 * 0.65f, 0.065f + fDiff * 2 * 0.65f, 1.0f);
				break;
			case 2:
				m_aLight[nCntLight].Diffuse = D3DXCOLOR(0.065f + fDiff * 2 * 0.65f, 0.065f + fDiff * 2 * 0.65f, 0.065f + fDiff * 2 * 0.65f, 1.0f);
				break;
			}
		}
		else if (fDiff >= 0.75f && fDiff < 0.875f)
		{
			// ���C�g�̊g�U����ݒ�
			switch (nCntLight)
			{
			case 0:
				m_aLight[nCntLight].Diffuse = D3DXCOLOR(1.0f - (fDiff - 0.75f) * 2.0f, 1.0f - (fDiff - 0.75f) * 3.0f, 1.0f - (fDiff - 0.75f) * 3.0f, 1.0f);
				break;
			case 1:
				m_aLight[nCntLight].Diffuse = D3DXCOLOR(0.65f - (fDiff - 0.75f) * 2.0f, 0.65f - (fDiff - 0.75f) * 3 * 0.65f, 0.65f - (fDiff - 0.75f) * 3 * 0.65f, 1.0f);
				break;
			case 2:
				m_aLight[nCntLight].Diffuse = D3DXCOLOR(0.65f - (fDiff - 0.75f) * 2.0f, 0.65f - (fDiff - 0.75f) * 3 * 0.65f, 0.65f - (fDiff - 0.75f) * 3 * 0.65f, 1.0f);
				break;
			}
		}
		else if (fDiff >= 0.875f && fDiff < 1.0f)
		{
			// ���C�g�̊g�U����ݒ�
			switch (nCntLight)
			{
			case 0:
				m_aLight[nCntLight].Diffuse = D3DXCOLOR(0.75f - (fDiff - 0.875f) * 7.0f, 1.0f - (fDiff - 0.75f) * 3.0f, 1.0f - (fDiff - 0.75f) * 3.0f, 1.0f);
				break;
			case 1:
				m_aLight[nCntLight].Diffuse = D3DXCOLOR(0.4f - (fDiff - 0.875f) * 4.0f * 0.4f, 0.65f - (fDiff - 0.75f) * 3 * 0.65f, 0.65f - (fDiff - 0.75f) * 3 * 0.65f, 1.0f);
				break;
			case 2:
				m_aLight[nCntLight].Diffuse = D3DXCOLOR(0.4f - (fDiff - 0.875f) * 4.0f * 0.4f, 0.65f - (fDiff - 0.75f) * 3 * 0.65f, 0.65f - (fDiff - 0.75f) * 3 * 0.65f, 1.0f);
				break;
			}
		}

		// ���C�g��ݒ肷��
		pDevice->SetLight(nCntLight, &m_aLight[nCntLight]);
	}
}

//==========================================================
// �|�C���g���C�g�̃I�t
//==========================================================
void CLight::EnablePointLight(bool bEnable)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		// �f�o�C�X�ւ̃|�C���^���擾

	// ���C�g���w�肳�ꂽ��Ԃɂ���
	pDevice->LightEnable(NUM_LIGHT - 1, bEnable);
}

//==========================================================
// �|�C���g���C�g�̍��W�ݒ�
//==========================================================
void CLight::SetPositonPointLight(D3DXVECTOR3 pos)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		// �f�o�C�X�ւ̃|�C���^���擾

	// ���C�g�̎�ނ�ݒ�
	m_aLight[NUM_LIGHT - 1].Type = D3DLIGHT_POINT;

	//���C�g�̈ʒu�ݒ�
	m_aLight[NUM_LIGHT - 1].Position = D3DXVECTOR3(pos.x, pos.y + 200.0f, pos.z);

	//���C�g�̐F�ݒ�
	m_aLight[NUM_LIGHT - 1].Diffuse = D3DXCOLOR(0.4f, 0.4f, 0.4f, 0.7f);

	//���C�g�͈̔͐ݒ�
	m_aLight[NUM_LIGHT - 1].Range = 2000.0f;

	//���C�g�̌���0�̐ݒ�
	m_aLight[NUM_LIGHT - 1].Attenuation0 = 0.94f;

	//���C�g�̌���1�̐ݒ�
	m_aLight[NUM_LIGHT - 1].Attenuation1 = 0.0f;

	//���C�g�̌���2�̐ݒ�
	m_aLight[NUM_LIGHT - 1].Attenuation2 = 0.0f;

	// ���C�g��ݒ肷��
	pDevice->SetLight(NUM_LIGHT - 1, &m_aLight[NUM_LIGHT - 1]);
}