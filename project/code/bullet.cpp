//==========================================================
//
// �e [bullet.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "bullet.h"
#include "model.h"

// �������O���
namespace {
	const char* FILENAME = "data\\MODEL\\bullet.x";	// �t�@�C����
	const int SETLIFE = (240);	// �e�̐ݒ����
}

//==========================================================
// �R���X�g���N�^
//==========================================================
CBullet::CBullet()
{
	// �l�̃N���A
	m_pObject = nullptr;
	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CBullet::~CBullet()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CBullet::Init(void)
{
	// �I�u�W�F�N�g�̐���
	m_pObject = CModel::Create(FILENAME);
	m_pObject->SetParent(&m_Info.mtxWorld);

	// �����̐ݒ�
	m_nLife = SETLIFE;

	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CBullet::Uninit(void)
{
	// �I�u�W�F�N�g�̏I��
	if (m_pObject != nullptr) {
		m_pObject->Uninit();
		m_pObject = nullptr;
	}

	// �J��
	Release();
}

//==========================================================
// �X�V����
//==========================================================
void CBullet::Update(void)
{
	// ����֘A
	Controller();

	// �}�g���b�N�X���f
	SetMatrix();

	// �����m�F
	if (m_nLife <= 0) {	// �������Ȃ��Ȃ���
		Uninit();	// �I��
	}
	else {
		m_nLife--;
	}
}

//==========================================================
// ����
//==========================================================
CBullet *CBullet::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot, const D3DXVECTOR3 &move)
{
	CBullet *pBullet = nullptr;

	pBullet = new CBullet;

	if (pBullet != nullptr)
	{
		// ����������
		pBullet->Init();

		// ���W���f
		pBullet->SetPosition(pos);

		// �������f
		pBullet->SetRotation(rot);

		// �ړ��ʔ��f
		pBullet->SetMove(move);
	}

	return pBullet;
}

//==========================================================
// �}�g���b�N�X�ݒ�
//==========================================================
void CBullet::SetMatrix(void)
{
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_Info.mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Info.rot.y, m_Info.rot.x, m_Info.rot.z);
	D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);
	D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxTrans);
}

//==========================================================
// ����֘A
//==========================================================
void CBullet::Controller(void)
{
	// �ړ�
	m_Info.pos += m_Info.move;
}