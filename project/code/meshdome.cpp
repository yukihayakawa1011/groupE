//==========================================================
//
// ���b�V���h�[���̏��� [meshdome.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "meshdome.h"
#include "texture.h"
#include "manager.h"
#include "renderer.h"

// �}�N����`
#define TEXTUREFILE_DATA	"data\\TEXTURE\\sky000.jpg"		//�e�N�X�`���f�[�^

//==========================================================
// �R���X�g���N�^
//==========================================================
CMeshDome::CMeshDome()
{

}

//==========================================================
// �f�X�g���N�^
//==========================================================
CMeshDome::~CMeshDome()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CMeshDome::Init(void)
{
	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CMeshDome::Uninit(void)
{
	//���_�o�b�t�@�̔p��
	CObjectMesh::Uninit();
}

//==========================================================
// �X�V����
//==========================================================
void CMeshDome::Update(void)
{
	D3DXVECTOR3 rot = GetRotation();
	rot.y += 0.001f;

	SetRotation(rot);
}

//==========================================================
// �`�揈��
//==========================================================
void CMeshDome::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���C�e�B���O���I�t�ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �`��
	CObjectMesh::Draw();

	//���C�e�B���O���I���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//==========================================================
// ���_���ݒ�
//==========================================================
void CMeshDome::SetVtxInfo(void)
{
	int nVertex = GetVertex();			// ���_�����擾
	int nNumWidth = GetNumWidth();		// ���������擾
	int nNumHeight = GetNumHeight();	// �����������擾
	D3DXVECTOR3 pos = GetPosition();	// ���W
	D3DXVECTOR3 vecDir;					// �ݒ�ύX�p�x�N�g��

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

		m_pVtx[nCntVtx].tex = D3DXVECTOR2((1.0f / nNumWidth) * (nCntVtx % (nNumWidth + 1)), 1.0f -((1.0f / nNumHeight) * (nCntVtx / (nNumWidth + 1))));
	}

	// ���_�ݒ�
	SetVtx();
}

//==========================================================
// ����
//==========================================================
CMeshDome *CMeshDome::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot,
	float fLength, float fHeight, const int nPriority, const int nWidth, const int nHeight)
{
	CMeshDome *pMeshWall = NULL;	// ���b�V���t�B�[���h�̃|�C���^
	CTexture *pTexture = CManager::GetInstance()->GetTexture();	// �e�N�X�`���ւ̃|�C���^

													// �������̊m��
	pMeshWall = new CMeshDome;

	if (pMeshWall != NULL)
	{// �m�ۂł����ꍇ

		// ������
		pMeshWall->Init();

		// ���W�ݒ�
		pMeshWall->SetPosition(pos);

		// �����ݒ�
		pMeshWall->SetRotation(rot);

		// ���_����
		pMeshWall->CObjectMesh::Create(nWidth, nHeight);

		// �꒸�_�ӂ�̊p�x�����߂�
		pMeshWall->m_fRot = (D3DX_PI * 2) / nWidth;

		// �c�����̊p�x�����߂�
		pMeshWall->m_fHeightRot = (D3DX_PI * 0.5f) / (nHeight + 2);

		// �T�C�Y�ݒ�
		pMeshWall->SetSize(fLength, fHeight);

		// �e�N�X�`���ݒ�
		pMeshWall->BindTexture(pTexture->Regist(TEXTUREFILE_DATA));
	}

	return pMeshWall;
}

//==========================================================
// ���ݒ�
//==========================================================
void CMeshDome::SetSize(float fLength, float fHeight)
{
	// �T�C�Y�ݒ�
	m_fLength = fLength;
	m_fHeight = fHeight;

	// ���_���ݒ�
	SetVtxInfo();
}

//==========================================================
// �F�ݒ�
//==========================================================
void CMeshDome::SetColor(float fDiff)
{
	int nVertex = GetVertex();			// ���_�����擾
	int nNumWidth = GetNumWidth();		// ���������擾
	int nNumHeight = GetNumHeight();	// �����������擾
	D3DXVECTOR3 pos = GetPosition();	// ���W
	D3DXVECTOR3 vecDir;					// �ݒ�ύX�p�x�N�g��

	// ���_���W�̐ݒ�(��������E��O�Ɍ������Ē��_����ݒ肷��
	for (int nCntVtx = 0; nCntVtx < nVertex; nCntVtx++)
	{
		if (fDiff >= 0.0f && fDiff < 0.5f)
		{
			//�F
			m_pVtx[nCntVtx].col = D3DXCOLOR(0.1f + fDiff * 2, 0.1f + fDiff * 2, 0.1f + fDiff * 2, 1.0f);
		}
		else if (fDiff >= 0.75f && fDiff < 0.875f)
		{
			//�F
			m_pVtx[nCntVtx].col = D3DXCOLOR(1.0f - (fDiff - 0.75f) * 2.0f, 1.0f - (fDiff - 0.75f) * 4, 1.0f - (fDiff - 0.75f) * 4, 1.0f);
		}
		else if (fDiff >= 0.875f && fDiff < 1.0f)
		{
			//�F
			m_pVtx[nCntVtx].col = D3DXCOLOR(0.75f - (fDiff - 0.875f) * 7.0f, 1.0f - (fDiff - 0.75f) * 4, 1.0f - (fDiff - 0.75f) * 4, 1.0f);
		}
	}

	// ���_�ݒ�
	SetVtx();
}
