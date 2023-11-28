//==========================================================
//
// �^�C�g���G���^�[ [title_enter.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "title_enter.h"
#include "manager.h"
#include "item.h"
#include "model.h"

// �ÓI�����o�ϐ��錾

//==========================================================
// �R���X�g���N�^
//==========================================================
CTitleEnter::CTitleEnter()
{
	// �l�̃N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CTitleEnter::~CTitleEnter()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CTitleEnter::Init(void)
{
	
	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CTitleEnter::Uninit(void)
{
	
}

//==========================================================
// �X�V����
//==========================================================
void CTitleEnter::Update(void)
{
	// �}�g���b�N�X�ݒ�
	SetMatrix();
}

//==========================================================
// �}�g���b�N�X�X�V
//==========================================================
void CTitleEnter::SetMatrix(void)
{
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
}

//==========================================================
// �A�C�e���̐e�ݒ�
//==========================================================
void CTitleEnter::SetItemParent(CItem *pItem)
{
	if (pItem == nullptr) {	// �I�u�W�F�N�g����
		return;
	}

	if (pItem->GetModel() == nullptr) {	// �������f������
		return;
	}

	// ���g�̃}�g���b�N�X��n��
	pItem->GetModel()->SetParent(&m_mtxWorld);
}