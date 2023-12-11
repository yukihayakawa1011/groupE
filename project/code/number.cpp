//===============================================
//
// �����S�ʂ̏��� [number.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "number.h"
#include "object2D.h"
#include "texture.h"
#include "manager.h"

// �}�N����`
#define MAX_WIDTHPATTERN	(10)	// �p�^�[����

//===============================================
// �R���X�g���N�^
//===============================================
CNumber::CNumber()
{
	// �l���N���A����
	m_nIdx = 0;
	m_nIdxTexture = -1;
	m_pObject2D = NULL;
	m_pTexture = NULL;
}

//===============================================
// �f�X�g���N�^
//===============================================
CNumber::~CNumber()
{

}

//===============================================
// ����������
//===============================================
HRESULT CNumber::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	if (m_pObject2D == NULL)
	{// �g�p����Ă��Ȃ��ꍇ
		m_pObject2D = CObject2D::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 6);

		if (m_pObject2D != NULL)
		{// �g�p����Ă���ꍇ

			// ������
			m_pObject2D->Init();

			// �T�C�Y�ݒ�
			m_pObject2D->SetSize(fWidth, fHeight);

			// �e�N�X�`���̏����擾
			CTexture *pTexture = CManager::GetInstance()->GetTexture();

			// �e�N�X�`�����o�C���h
			m_pObject2D->BindTexture(pTexture->Regist("data\\TEXTURE\\number005.png"));

			// �e�N�X�`���ݒ�
			SetIdx(m_nIdx);
		}

	}
	return S_OK;
}

//===============================================
// ����������
//===============================================
HRESULT CNumber::Init()
{
	if (m_pObject2D == NULL)
	{// �g�p����Ă��Ȃ��ꍇ
		m_pObject2D = CObject2D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 7);

		if (m_pObject2D != NULL)
		{// �g�p����Ă���ꍇ

			// ������
			m_pObject2D->Init();

			// �e�N�X�`���ݒ�
			SetIdx(m_nIdx);
		}

	}
	return S_OK;
}

//===============================================
// �I������
//===============================================
void CNumber::Uninit(void)
{
	if (m_pObject2D != NULL)
	{// �g�p����Ă���ꍇ
		m_pObject2D = NULL;
	}
}

//===============================================
// �X�V����
//===============================================
void CNumber::Update(void)
{
	if (m_pObject2D != NULL)
	{// �g�p����Ă���ꍇ
		m_pObject2D->Update();
	}
}

//===============================================
// �`�揈��
//===============================================
void CNumber::Draw(void)
{
	//if (m_pObject2D != NULL)
	//{// �g�p����Ă���ꍇ
	//	// �`�揈��
	//	m_pObject2D->Draw();
	//}
}

//===============================================
// ����
//===============================================
CNumber *CNumber::Create(void)
{
	CNumber *pNum = NULL;

	if (pNum != NULL)
	{// �g�p����Ă��Ȃ��ꍇ
		pNum = new CNumber;

		if (pNum != NULL)
		{// �g�p����Ă���ꍇ

			// ����������
			pNum->Init();
		}
	}

	return pNum;
}

//===============================================
// ����
//===============================================
CNumber *CNumber::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CNumber *pNum = NULL;

	if (pNum == NULL)
	{// �g�p����Ă��Ȃ��ꍇ
		pNum = new CNumber;

		if(pNum != NULL)
		{// �g�p����Ă���ꍇ

			// ����������
			pNum->Init(pos, fWidth, fHeight);
		}
	}

	return pNum;
}

//===============================================
// ���_�ݒ�
//===============================================
void CNumber::SetIdx(const int nIdx)
{
	m_nIdx = nIdx;	// �l��ݒ�

	if (m_nIdx > 10)
	{// �l�����E�𒴂����ꍇ

		m_nIdx = 9;
	}
	else if (m_nIdx < 0)
	{// �l���Œ�l�𒴂����ꍇ

		m_nIdx = 0;
	}

	if (m_pObject2D != NULL)
	{// �g�p����Ă���ꍇ

		// ���_���̐ݒ�
		m_pObject2D->SetVtx(m_nIdx, MAX_WIDTHPATTERN, 1);
	}
}

//===============================================
// �|���S���p��
//===============================================
void CNumber::PolygonDelete(void)
{
	if (m_pObject2D != NULL)
	{// �g�p����Ă���ꍇ
		m_pObject2D->Uninit();
		m_pObject2D = NULL;
	}
}

//================================================================
//�e�N�X�`���擾
//================================================================
void CNumber::BindTexture(LPDIRECT3DTEXTURE9 m_Texture)
{
	m_pTexture = m_Texture;
}

void CNumber::SetPosition(const D3DXVECTOR3& pos)
{
	if (m_pObject2D == nullptr) {
		return;
	}

	// ���W�ݒ�
	m_pObject2D->SetPosition(pos);

	// �T�C�Y�ݒ�
	m_pObject2D->SetSize(m_pObject2D->GetWidth(), m_pObject2D->GetHeight());
}