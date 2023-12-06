//===============================================
//
// �����S�ʂ̏��� [score.cpp]
// Author : Ryosuke Ohhara
//
//===============================================
#include "score.h"
#include "object2D.h"
#include "number.h"

// �萔��`
namespace
{
	const int MAX_WIDTHPATTERN = 10;	// �p�^�[����
	const float POLYSIZE = (25.0f);	// �|���S���̃T�C�Y
}

//===============================================
// �R���X�g���N�^
//===============================================
CScore::CScore()
{
	// �l���N���A����
	m_nIdx = 0;
	m_nNumScore = 0;

	for (int nCount = 0; nCount < NUM_SCORE; nCount++)
	{
		m_apNumber[nCount] = nullptr;  // �g�p���Ă��Ȃ���Ԃɂ���
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
			m_apNumber[nCount] = CNumber::Create(D3DXVECTOR3(pos.x + nCount * POLYSIZE, pos.y, pos.z), fWidth, fHeight);

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
		{// �g�p���Ă��Ȃ��ꍇ

			// ����
			m_apNumber[nCount] = CNumber::Create();

			if (m_apNumber[nCount] != nullptr)
			{// �g�p����Ă����ꍇ

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
		{// �g�p����Ă����ꍇ

			// �I������
			m_apNumber[nCount]->Uninit();

			// �g�p���Ă��Ȃ���Ԃɂ���
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
		{// �g�p����Ă���ꍇ

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

//===============================================
//�X�R�A���Z����
//===============================================
void CScore::AddScore(int nScore)
{
	m_nNumScore += nScore;

	m_apNumber[0]->SetIdx(m_nNumScore % 100000000 / 10000000);
	m_apNumber[1]->SetIdx(m_nNumScore % 10000000 / 1000000);
	m_apNumber[2]->SetIdx(m_nNumScore % 1000000 / 100000);
	m_apNumber[3]->SetIdx(m_nNumScore % 100000 / 10000);
	m_apNumber[4]->SetIdx(m_nNumScore % 10000 / 1000);
	m_apNumber[5]->SetIdx(m_nNumScore % 1000 / 100);
	m_apNumber[6]->SetIdx(m_nNumScore % 100 / 10);
	m_apNumber[7]->SetIdx(m_nNumScore % 10 / 1);

	/*for (int nCount = 0; nCount < NUM_SCORE; nCount++)
	{
		m_apNumber[nCount]->SetIdx(m_nNumScore);
	}*/
}

//===============================================
//�X�R�A���Z����
//===============================================
void CScore::LowerScore(int nScore)
{
	m_nNumScore -= nScore;

	m_apNumber[0]->SetIdx(m_nNumScore % 100000000 / 10000000);
	m_apNumber[1]->SetIdx(m_nNumScore % 10000000 / 1000000);
	m_apNumber[2]->SetIdx(m_nNumScore % 1000000 / 100000);
	m_apNumber[3]->SetIdx(m_nNumScore % 100000 / 10000);
	m_apNumber[4]->SetIdx(m_nNumScore % 10000 / 1000);
	m_apNumber[5]->SetIdx(m_nNumScore % 1000 / 100);
	m_apNumber[6]->SetIdx(m_nNumScore % 100 / 10);
	m_apNumber[7]->SetIdx(m_nNumScore % 10 / 1);
}

//===============================================
//�X�R�A�ݒ菈��
//===============================================
void CScore::SetScore(int nScore)
{
	m_nNumScore = nScore;

	m_apNumber[0]->SetIdx(m_nNumScore % 100000000 / 10000000);
	m_apNumber[1]->SetIdx(m_nNumScore % 10000000 / 1000000);
	m_apNumber[2]->SetIdx(m_nNumScore % 1000000 / 100000);
	m_apNumber[3]->SetIdx(m_nNumScore % 100000 / 10000);
	m_apNumber[4]->SetIdx(m_nNumScore % 10000 / 1000);
	m_apNumber[5]->SetIdx(m_nNumScore % 1000 / 100);
	m_apNumber[6]->SetIdx(m_nNumScore % 100 / 10);
	m_apNumber[7]->SetIdx(m_nNumScore % 10 / 1);
}

//===============================================
// �F�ݒ�
//===============================================
void CScore::SetClo(D3DXCOLOR col)
{
	for (int nCnt = 0; nCnt < NUM_SCORE; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{// �g�p���Ă��Ȃ��ꍇ
			m_apNumber[nCnt]->GetObject2D()->SetCol(col);
		}
	}
}

////===============================================
//// ���_�ݒ�
////===============================================
//void CScore::SetIdx(const int nIdx)
//{
//	m_nIdx = nIdx;	// �l��ݒ�
//
//	if (m_nIdx > 10)
//	{// �l�����E�𒴂����ꍇ
//		m_nIdx = 9;
//	}
//	else if (m_nIdx < 0)
//	{// �l���Œ�l�𒴂����ꍇ
//		m_nIdx = 0;
//	}
//
//	if (m_pObject2D != NULL)
//	{// �g�p����Ă���ꍇ
//	 // ���_���̐ݒ�
//		m_pObject2D->SetVtx(m_nIdx, MAX_WIDTHPATTERN, 1);
//	}
//}
//
////===============================================
//// �|���S���p��
////===============================================
//void CScore::PolygonDelete(void)
//{
//	if (m_pObject2D != NULL)
//	{// �g�p����Ă���ꍇ
//		m_pObject2D->Uninit();
//		m_pObject2D = NULL;
//	}
//}