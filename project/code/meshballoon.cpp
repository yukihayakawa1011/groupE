//==========================================================
//
// �T���v�� [sample.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "meshballoon.h"
#include "texture.h"
#include "manager.h"
#include "renderer.h"

// �}�N����`

//==========================================================
// �R���X�g���N�^
//==========================================================
CMeshBalloon::CMeshBalloon(int nPriOrity) : CObjectMesh(nPriOrity)
{

}

//==========================================================
// �f�X�g���N�^
//==========================================================
CMeshBalloon::~CMeshBalloon()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CMeshBalloon::Init(void)
{
	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CMeshBalloon::Uninit(void)
{
	CObjectMesh::Uninit();
}

//==========================================================
// �X�V����
//==========================================================
void CMeshBalloon::Update(void)
{

}

//==========================================================
// �`�揈��
//==========================================================
void CMeshBalloon::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	// �`��
	CObjectMesh::Draw();

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
}

//==========================================================
// ����
//==========================================================
CMeshBalloon *CMeshBalloon::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, float fLength, const int nPriority, const int nWidth, const int nHeight)
{
	CMeshBalloon *pMesh = nullptr;

	pMesh = new CMeshBalloon;

	if (pMesh != NULL)
	{
		// ����������
		pMesh->Init();

		// ���W�ݒ�
		pMesh->SetPosition(pos);

		// �����ݒ�
		pMesh->SetRotation(rot);

		// ���_����
		pMesh->CObjectMesh::Create(nWidth, nHeight);

		// �꒸�_�ӂ�̊p�x�����߂�
		pMesh->m_fRot = (D3DX_PI * 2) / nWidth;

		// �c�����̊p�x�����߂�
		pMesh->m_fHeightRot = (D3DX_PI * 0.5f) / (nHeight + 2);

		// �T�C�Y�ݒ�
		pMesh->SetSize(fLength);

		// �e�N�X�`���ݒ�
		pMesh->BindTexture(-1);
	}

	return pMesh;
}

//==========================================================
// ���_���ݒ�
//==========================================================
void CMeshBalloon::SetVtxInfo(void)
{
	int nVertex = GetVertex();			// ���_�����擾
	int nNumWidth = GetNumWidth();		// ���������擾
	int nNumHeight = GetNumHeight();	// �����������擾
	D3DXVECTOR3 pos = GetPosition();	// ���W
	D3DXVECTOR3 vecDir;				// �ݒ�ύX�p�x�N�g��

	// ���_���W�̐ݒ�(��������E��O�Ɍ������Ē��_����ݒ肷��
	for (int nCntVtx = 0; nCntVtx < nVertex; nCntVtx++)
	{
		float fRot = m_fRot * (nCntVtx % (nNumWidth + 1));

		if (fRot > D3DX_PI || fRot < -D3DX_PI)
		{//-3.14�`3.14�͈̔͊O�̏ꍇ
			if (fRot > D3DX_PI)
			{
				fRot += (-D3DX_PI * 2);
			}
			else if (fRot < -D3DX_PI)
			{
				fRot += (D3DX_PI * 2);
			}
		}

		float fHeightRot = m_fHeightRot * (nCntVtx / (nNumWidth + 1));

		if (fHeightRot > D3DX_PI || fHeightRot < -D3DX_PI)
		{//-3.14�`3.14�͈̔͊O�̏ꍇ
			if (fHeightRot > D3DX_PI)
			{
				fHeightRot += (-D3DX_PI * 2);
			}
			else if (fHeightRot < -D3DX_PI)
			{
				fHeightRot += (D3DX_PI * 2);
			}
		}

		//���_���W
		m_pVtx[nCntVtx].pos.x = (cosf(fHeightRot) * cosf(fRot)) * m_fLength;
		m_pVtx[nCntVtx].pos.y = sinf(fHeightRot) * m_fLength;
		m_pVtx[nCntVtx].pos.z = (cosf(fHeightRot) * sinf(fRot)) * m_fLength;

		// �x�N�g�������߂�
		vecDir = m_pVtx[nCntVtx].pos - pos;

		//�x�N�g���𐳋K������
		D3DXVec3Normalize(&vecDir, &vecDir);

		//�@��
		m_pVtx[nCntVtx].nor = vecDir;

		//�F
		m_pVtx[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		m_pVtx[nCntVtx].tex = D3DXVECTOR2((1.0f / nNumWidth) * (nCntVtx % (nNumWidth + 1)), 1.0f - ((1.0f / nNumHeight) * (nCntVtx / (nNumWidth + 1))));
	}

	// ���_�ݒ�
	SetVtx();
}

//==========================================================
// ���ݒ�
//==========================================================
void CMeshBalloon::SetSize(float fLength)
{
	// �T�C�Y�ݒ�
	m_fLength = fLength;

	// ���_���ݒ�
	SetVtxInfo();
}