//==========================================================
//
// ���z�̍������S�� [waist.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "waist.h"
#include "manager.h"
#include "renderer.h"

//==========================================================
// �R���X�g���N�^
//==========================================================
CWaist::CWaist()
{
	// �l�̃N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����
	m_pParentMtx = NULL;						// �e�̃��[���h�}�g���b�N�X
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CWaist::~CWaist()
{

}

//==========================================================
// �}�g���b�N�X�̐ݒ�
//==========================================================
void CWaist::SetMatrix(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�ւ̃|�C���^���擾
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxParent;			// �e�̃}�g���b�N�X���

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_pParentMtx != NULL)
	{// �o���Ă���ꍇ

		mtxParent = *m_pParentMtx;

		//�p�[�c�̃}�g���b�N�X�Ɛe�̃}�g���b�N�X���������킹��
		D3DXMatrixMultiply(&m_mtxWorld,
			&m_mtxWorld, &mtxParent);
	}

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
}

//==========================================================
// ����
//==========================================================
CWaist *CWaist::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CWaist *pWaist = NULL;	// ���̃|�C���^

	// ���I�m��
	pWaist = new CWaist;

	if (pWaist != NULL)
	{// �m�ۂ��ꂽ�ꍇ
		pWaist->SetPosition(pos);
		pWaist->SetRotation(rot);
	}

	return pWaist;
}

//==========================================================
// ���̍�����ݒ�
//==========================================================
void CWaist::SetHeight(D3DXVECTOR3& pPos)
{
	// ���W��ݒ�
	m_SetPos = pPos;

	pPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
