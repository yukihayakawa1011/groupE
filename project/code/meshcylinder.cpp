//==========================================================
//
// ���b�V���V�����_�[�̏��� [meshcylinder.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "meshcylinder.h"
#include "texture.h"
#include "manager.h"
#include "renderer.h"
#include "slow.h"

// �}�N����`
#define TEXTUREFILE_DATA	"data\\TEXTURE\\city000.png"		//�e�N�X�`���f�[�^

//==========================================================
// �R���X�g���N�^
//==========================================================
CMeshCylinder::CMeshCylinder(int nPriority) : CObjectMesh(nPriority)
{
	
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CMeshCylinder::~CMeshCylinder()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CMeshCylinder::Init(void)
{
	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CMeshCylinder::Uninit(void)
{
	// ���_�o�b�t�@�̔p��
	CObjectMesh::Uninit();
}

//==========================================================
// �X�V����
//==========================================================
void CMeshCylinder::Update(void)
{
	
}

//==========================================================
// �`�揈��
//==========================================================
void CMeshCylinder::Draw(void)
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
void CMeshCylinder::SetVtxInfo(void)
{
	int nVertex = GetVertex();			// ���_�����擾
	int nNumWidth = GetNumWidth();		// ���������擾
	int nNumHeight = GetNumHeight();	// �����������擾
	D3DXVECTOR3 pos = GetPosition();	// ���W
	D3DXVECTOR3 vecDir;	//�ݒ�ύX�p�x�N�g��

	//���_���W�̐ݒ�(��������E��O�Ɍ������Ē��_����ݒ肷��
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

		//���_���W
		m_pVtx[nCntVtx].pos.x = sinf(fRot) * m_fLength;
		m_pVtx[nCntVtx].pos.y = ((m_fHeight * 2) * nNumHeight) + ((nCntVtx / (nNumWidth + 1) * (-m_fHeight * 2)));
		m_pVtx[nCntVtx].pos.z = cosf(fRot) * m_fLength;

		vecDir = (m_pVtx[nCntVtx].pos - pos);

		//�x�N�g���𐳋K������
		D3DXVec3Normalize(&vecDir, &vecDir);

		//�@��
		m_pVtx[nCntVtx].nor = vecDir;

		//�F
		m_pVtx[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		m_pVtx[nCntVtx].tex = D3DXVECTOR2((5.0f / nNumWidth) * (nCntVtx % (nNumWidth + 1)), (1.0f / nNumHeight) * (nCntVtx / (nNumWidth + 1)));
	}

	// ���_�ݒ�
	SetVtx();
}

//==========================================================
// ����
//==========================================================
CMeshCylinder *CMeshCylinder::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot,
	float fLength, float fHeight, const int nPriority, const int nWidth, const int nHeight)
{
	CMeshCylinder *pMeshWall = NULL;	// ���b�V���t�B�[���h�̃|�C���^
	CTexture *pTexture = CManager::GetInstance()->GetTexture();	// �e�N�X�`���ւ̃|�C���^

	// �������̊m��
	pMeshWall = new CMeshCylinder(3);

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
void CMeshCylinder::SetSize(float fLength, float fHeight)
{
	// �T�C�Y�ݒ�
	m_fLength = fLength;
	m_fHeight = fHeight;

	// ���_���ݒ�
	SetVtxInfo();
}

//==========================================================
// �R���X�g���N�^
//==========================================================
CMeshSmake::CMeshSmake(int nPriority) : CMeshCylinder(nPriority)
{
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_tex = D3DXVECTOR2(0.0f, 0.0f);
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CMeshSmake::~CMeshSmake()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CMeshSmake::Init(void)
{
	CMeshCylinder::Init();

	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CMeshSmake::Uninit(void)
{
	// ���_�o�b�t�@�̔p��
	CMeshCylinder::Uninit();
}

//==========================================================
// �X�V����
//==========================================================
void CMeshSmake::Update(void)
{
	CMeshCylinder::Update();

	m_col.a -= 0.005f * CManager::GetInstance()->GetSlow()->Get();

	SetCol(m_col);
	SetHeight(m_fHeight + 0.07f);
	m_tex.x += 0.005f;

	if (m_tex.x > 1.0f)
	{
		m_tex.x -= 1.0f;
	}
	else if (m_tex.x < 0.0f)
	{
		m_tex.x += 1.0f;
	}

	if (m_col.a <= 0.0f)
	{
		Uninit();
	}
}

//==========================================================
// �`�揈��
//==========================================================
void CMeshSmake::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//�A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	// �`��
	CMeshCylinder::Draw();

	//�A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 255);

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
}

//==========================================================
// ����
//==========================================================
CMeshSmake *CMeshSmake::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot,
	float fLength, float fHeight, const int nPriority, const int nWidth, const int nHeight)
{
	CMeshSmake *pMeshWall = NULL;	// ���b�V���t�B�[���h�̃|�C���^
	CTexture *pTexture = CManager::GetInstance()->GetTexture();	// �e�N�X�`���ւ̃|�C���^

	// �������̊m��
	pMeshWall = new CMeshSmake(6);

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
void CMeshSmake::SetSize(float fLength, float fHeight)
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
void CMeshSmake::SetCol(D3DXCOLOR col)
{
	int nVertex = GetVertex();			// ���_�����擾
	int nNumWidth = GetNumWidth();		// ���������擾
	int nNumHeight = GetNumHeight();	// �����������擾
	D3DXVECTOR3 pos = GetPosition();	// ���W
	D3DXVECTOR3 vecDir;	//�ݒ�ύX�p�x�N�g��

	//���_���W�̐ݒ�(��������E��O�Ɍ������Ē��_����ݒ肷��
	for (int nCntVtx = 0; nCntVtx < nVertex; nCntVtx++)
	{
		//�F
		m_pVtx[nCntVtx].col = col;
	}

	// ���_�ݒ�
	SetVtx();
}

//==========================================================
// �����ݒ�
//==========================================================
void CMeshSmake::SetHeight(float fHeight)
{
	int nVertex = GetVertex();			// ���_�����擾
	int nNumWidth = GetNumWidth();		// ���������擾
	int nNumHeight = GetNumHeight();	// �����������擾
	D3DXVECTOR3 pos = GetPosition();	// ���W
	D3DXVECTOR3 vecDir;	//�ݒ�ύX�p�x�N�g��

	m_fHeight = fHeight;

	//���_���W�̐ݒ�(��������E��O�Ɍ������Ē��_����ݒ肷��
	for (int nCntVtx = 0; nCntVtx < nVertex; nCntVtx++)
	{
		//���_���W
		m_pVtx[nCntVtx].pos.y = ((m_fHeight * 2) * nNumHeight) + ((nCntVtx / (nNumWidth + 1) * (-m_fHeight * 2)));
		m_pVtx[nCntVtx].tex = D3DXVECTOR2((5.0f / nNumWidth) * (nCntVtx % (nNumWidth + 1)) + m_tex.x, (1.0f / nNumHeight) * (nCntVtx / (nNumWidth + 1)));
	}

	// ���_�ݒ�
	SetVtx();
}
