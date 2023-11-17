//===============================================
//
// �����S�ʂ̏��� [number.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "score.h"
#include "object2D.h"
#include "texture.h"
#include "manager.h"

// �}�N����`
#define MAX_WIDTHPATTERN	(10)	// �p�^�[����

//===============================================
// �R���X�g���N�^
//===============================================
CScore::CScore()
{
	// �l���N���A����
	m_nIdx = 0;

	for (int nCount = 0; nCount < NUM_SCORE; nCount++)
	{
		m_apNumber[nCount] = nullptr;
	}
}

//===============================================
// �f�X�g���N�^
//===============================================
CScore::~CScore()
{

}

//===============================================
// ����������
//===============================================
HRESULT CScore::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	for (int nCount = 0; nCount < NUM_SCORE; nCount++)
	{
		if (m_apNumber[nCount] == nullptr)
		{// �g�p����Ă��Ȃ��ꍇ

			// ����
			m_apNumber[nCount] = CNumber::Create(D3DXVECTOR3(pos.x + nCount * 50.0f, pos.y , pos.z), fWidth, fHeight);

			if (m_apNumber[nCount] != nullptr)
			{// �g�p����Ă���ꍇ

				// ����������
				m_apNumber[nCount]->Init(pos, fWidth, fHeight);
			}
		}
	}

	return S_OK;
}

//===============================================
// ����������
//===============================================
HRESULT CScore::Init()
{
	for (int nCount = 0; nCount < NUM_SCORE; nCount++)
	{
		if (m_apNumber[nCount] == nullptr)
		{// �g�p����Ă��Ȃ��ꍇ

			// ����
			m_apNumber[nCount] = CNumber::Create();

			if (m_apNumber[nCount] != nullptr)
			{// �g�p����Ă���ꍇ

				// ����������
				m_apNumber[nCount]->Init();
			}
		}
	}

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CScore::Uninit(void)
{
	for (int nCount = 0; nCount < NUM_SCORE; nCount++)
	{
		if (m_apNumber[nCount] != nullptr)
		{// �g�p����Ă��Ȃ��ꍇ

			// �I������
			m_apNumber[nCount]->Uninit();

			// �g�p����Ă��Ȃ���Ԃɂ���
			m_apNumber[nCount] = nullptr;
		}
	}
}

//===============================================
// �X�V����
//===============================================
void CScore::Update(void)
{
	for (int nCount = 0; nCount < NUM_SCORE; nCount++)
	{
		if (m_apNumber[nCount] != nullptr)
		{// �g�p����Ă��Ȃ��ꍇ

			// �X�V����
			m_apNumber[nCount]->Update();
		}
	}
}

//===============================================
// �`�揈��
//===============================================
void CScore::Draw(void)
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
CScore *CScore::Create(void)
{
	CScore *pNum = NULL;

	if (pNum != NULL)
	{// �g�p����Ă��Ȃ��ꍇ
		pNum = new CScore;

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
CScore *CScore::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CScore *pNum = NULL;

	if (pNum == NULL)
	{// �g�p����Ă��Ȃ��ꍇ
		pNum = new CScore;

		if (pNum != NULL)
		{// �g�p����Ă���ꍇ

			// ����������
			pNum->Init(pos, fWidth, fHeight);
		}
	}

	return pNum;
}