//==========================================================
//
// �A�C�e���̏��� [item.cpp]
// Author : Yuuka Sakuma
//
//==========================================================
#include "item.h"
#include "Xfile.h"
#include "manager.h"
#include "debugproc.h"
#include "texture.h"
#include "objectX.h"

//==========================================================
// �R���X�g���N�^
//==========================================================
CItem::CItem()
{
	// �l�̃N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CItem::~CItem()
{

}

//==========================================================
// ����
//==========================================================
CItem *CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *pFileName, int nType, const int nPriority)
{
	CItem *pObjectX = NULL;
	CXFile *pModelFile = CManager::GetInstance()->GetModelFile();

	// �I�u�W�F�N�gX�̐���
	pObjectX = new CItem;

	if (pObjectX != NULL)
	{// �����ł����ꍇ
	
		// ���W
		pObjectX->SetPosition(pos);
		//pObjectX->SetOldPos(pos);

		// ����
		pObjectX->SetRotation(rot);
		

		//// ��ސݒ�
		//pObjectX->SetType(nType);

		// ���
		pObjectX->m_nType = nType;
		// ����������
		pObjectX->Init(pFileName);

	}
	else
	{// �����Ɏ��s�����ꍇ
		return NULL;
	}

	return pObjectX;
}


//==========================================================
// ����������
//==========================================================
HRESULT CItem::Init(void)
{
	m_pObject = CObjectX::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, NULL);

	return S_OK;
}

//==========================================================
// ����������
//==========================================================
HRESULT CItem::Init(const char *pFileName)
{
	m_pObject = CObjectX::Create(m_pos, m_rot, pFileName, NULL);

	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CItem::Uninit(void)
{
	if (nullptr != m_pObject) {
		m_pObject->Uninit();
		m_pObject = NULL;
	}

	if (m_pObject != NULL)
	{
		m_pObject->Uninit();
		delete m_pObject;
		m_pObject = NULL;
	}

	Release();
}

//==========================================================
// �X�V����
//==========================================================
void CItem::Update(void)
{
	m_posOld = m_pObject->GetPosition();
	m_pos = m_pObject->GetPosition();

	m_rot = m_pObject->GetRotation();

	//�p�x�����߂�
	m_fCurve += (D3DX_PI * 0.02f);

	//�ʒu��������
	m_pos.y = m_posOld.y + sinf(m_fCurve) * 1.5f;

	m_rot.y += sinf(D3DX_PI * 0.02f);

	// �g�p�I�u�W�F�N�g�X�V
	if (nullptr != m_pObject) {
		m_pObject->SetPosition(m_pos);
		m_pObject->SetRotation(m_rot);
		m_pObject->Update();
	}
}

////==========================================================
//// �`�揈��
////==========================================================
//void CItem::Draw(void)
//{
//	m_pObject->
//}
//
