//===============================================
//
// ���̏�ɏo��UI���� [overheadui.cpp]
// Author : Ryosuke Ohara
//
//===============================================
#include "headui.h"
#include "billboard.h"
#include "manager.h"
#include "texture.h"
#include "camera.h"
#include "debugproc.h"

// �}�N����`
#define MAX_WIDTHPATTERN	(10)	// �p�^�[����
#define LEN (10.0f)
#define TEXTURENAME  ("data\\TEXTURE\\number004.png") // ����

//===============================================
// �R���X�g���N�^
//===============================================
CHeadUI::CHeadUI()
{
	// �l���N���A����
	m_nIdx = 0;
	m_fPolyHeight = 0.0f;
	m_fPolyWidth = 0.0f;
	m_fUpHeight = 0.0f;
	m_pPos = nullptr;

	for (int nCount = 0; nCount < NUM_DIGIT; nCount++)
	{
		m_apObject[nCount] = nullptr;
	}
}

//===============================================
// �f�X�g���N�^
//===============================================
CHeadUI::~CHeadUI()
{

}

//===============================================
// ����������
//===============================================
//HRESULT CHeadUI::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
//{
//	for (int nCount = 0; nCount < NUM_DIGIT; nCount++)
//	{
//		if (m_pObject[nCount] == nullptr)
//		{// �g�p����Ă��Ȃ��ꍇ
//
//			m_pObject[nCount] = CObjectBillboard::Create()
//
//		}
//	}
//
//	return S_OK;
//}

//===============================================
// ����������
//===============================================
HRESULT CHeadUI::Init()
{
	for (int nCount = 0; nCount < NUM_DIGIT; nCount++)
	{
		if (m_apObject[nCount] == nullptr)
		{// �g�p���Ă����ꍇ

			m_apObject[nCount] = CObjectBillboard::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 7);
			m_apObject[nCount]->SetDraw(true);
			m_apObject[nCount]->SetAlphaText(false);
			m_apObject[nCount]->SetLighting(true);
			m_apObject[nCount]->SetZTest(false);
			m_apObject[nCount]->SetFusion(CObjectBillboard::FUSION_NORMAL);
			m_apObject[nCount]->BindTexture(CManager::GetInstance()->GetTexture()->Regist(TEXTURENAME));
		}
	}

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CHeadUI::Uninit(void)
{
	for (int nCount = 0; nCount < NUM_DIGIT; nCount++)
	{
		if (m_apObject[nCount] != nullptr)
		{// �g�p���Ă����ꍇ

		 // �I������
			m_apObject[nCount]->Uninit();

			// �g�p���Ă��Ȃ���Ԃɂ���
			m_apObject[nCount] = nullptr;
		}
	}

	// �J��
	Release();
}

//===============================================
// �X�V����
//===============================================
void CHeadUI::Update(void)
{
	SetMixPosition();
}

//===============================================
// ����
//===============================================
CHeadUI *CHeadUI::Create(void)
{
	CHeadUI *pNum = NULL;

	if (pNum != NULL)
	{// �g�p����Ă��Ȃ��ꍇ
		pNum = new CHeadUI;

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
CHeadUI *CHeadUI::Create(D3DXVECTOR3 * pPos, D3DXMATRIX *Matrix, const float fUpHeight, const float fPolyWidth, const float fPolyHeight)
{
	CHeadUI *pOverUI = NULL;

	pOverUI = new CHeadUI;

	if (pOverUI != NULL)
	{// �g�p����Ă��Ȃ��ꍇ

		// ����������
		pOverUI->Init();

		// �e�̐ݒ�
		pOverUI->SetParent(pPos);

		// ���΍��W�̍�����ݒ�
		pOverUI->SetUpHeight(fUpHeight);

		// �|���S���T�C�Y��ݒ�
		pOverUI->SetPolySize(fPolyWidth, fPolyHeight);

		// �e�̃}�g���b�N�X�ݒ�
		pOverUI->SetMtxParent(Matrix);

		// ���W��ݒ�
		pOverUI->SetMixPosition();
	}

	return pOverUI;
}

//===============================================
// ���_�ݒ�
//===============================================
void CHeadUI::SetIdx(const int nIdx)
{
	m_nIdx = nIdx;	// �l��ݒ�

	if (m_apObject[0] != nullptr && m_apObject[1] != nullptr)
	{// �g�p���Ă����ꍇ

		// ���_���̐ݒ�
		m_apObject[0]->SetVtx(m_nIdx % 100 / 10, MAX_WIDTHPATTERN, 1);
		m_apObject[1]->SetVtx(m_nIdx % 10 / 1, MAX_WIDTHPATTERN, 1);
	}
}

//==========================================================
// ���ƍ����̓K��
//==========================================================
void CHeadUI::SetPolySize(const float fWidth, const float fHeight)
{
	// ���̐ݒ�
	{
		m_fPolyWidth = fWidth;
		if (m_fPolyWidth < 0.0f) {	// �l���}�C�i�X
			m_fPolyWidth = 0.0f;
		}
	}

	// �����̐ݒ�
	{
		m_fPolyHeight = fHeight;
		if (m_fPolyHeight < 0.0f) {	// �l���}�C�i�X
			m_fPolyHeight = 0.0f;
		}
	}

	for (int nCount = 0; nCount < NUM_DIGIT; nCount++)
	{
		if (m_apObject[nCount] != nullptr)
		{// �g�p���Ă����ꍇ

		 // ���W�ݒ�
			m_apObject[nCount]->SetSize(m_fPolyWidth, m_fPolyHeight);
		}
	}
}

//==========================================================
// �}�g���b�N�X�ݒ�
//==========================================================
void CHeadUI::SetMtxParent(D3DXMATRIX *mtxParent)
{
	m_mtxParent = mtxParent;
}

//==========================================================
// �ݒ荂���ƍ��������W��ݒ�
//==========================================================
void CHeadUI::SetMixPosition(void)
{
	for (int nCount = 0; nCount < NUM_DIGIT; nCount++)
	{
		D3DXVECTOR3 pos = D3DXVECTOR3(5.0f + (nCount * 12.0f), 0.0f, -20.0f);	// ��̍��W

		pos.y += 2.0f;	      // �ݒ肳�ꂽ�������グ��

		if(m_apObject[nCount] != nullptr)
		{
			D3DXMATRIX mtxTrans;	// �v�Z�p�}�g���b�N�X
			D3DXMATRIX mtxParent;	// �e�̃}�g���b�N�X���

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&m_mtxWorld[nCount]);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
			D3DXMatrixMultiply(&m_mtxWorld[nCount], &m_mtxWorld[nCount], &mtxTrans);

			if (m_mtxParent != nullptr)
			{// �g�p����Ă����ꍇ

				mtxParent = *m_mtxParent;

				// �}�g���b�N�X�Ɛe�̃}�g���b�N�X���������킹��
				D3DXMatrixMultiply(&m_mtxWorld[nCount],
					&m_mtxWorld[nCount], &mtxParent);

				m_apObject[nCount]->SetPosition(pos);
				m_apObject[nCount]->SetCurrent(m_mtxParent);
			}
		}
	}
}