//==========================================================
//
// ���b�V���̊Ǘ� [mesh.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "mesh.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "slow.h"
#include "debugproc.h"

//==========================================================
// �R���X�g���N�^
//==========================================================
CObjectMesh::CObjectMesh(int nPriority) : CObject(nPriority)
{
	// �l���N���A����
	m_nIndex = 0;
	m_nVertex = 0;
	m_nNumWidth = 0;
	m_nIdxTexture = -1;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pVtx = NULL;
	m_Type = TYPE_NONE;
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CObjectMesh::~CObjectMesh()
{

}

#if 0
//==========================================================
// ����������
//==========================================================
HRESULT CMesh::Init(void)
{
	return S_OK;
}
#endif

//==========================================================
// �I������
//==========================================================
void CObjectMesh::Uninit(void)
{
	//���_�o�b�t�@�̔p��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̔p��
	if (m_pIdexBuff != NULL)
	{
		m_pIdexBuff->Release();
		m_pIdexBuff = NULL;
	}

	// ���_���̔p��
	if (m_pVtx != NULL)
	{
		delete[] m_pVtx;
		m_pVtx = NULL;
	}

	// �p��
	Release();
}

#if 0
//==========================================================
// �X�V����
//==========================================================
void CMesh::Update(void)
{

}
#endif

//==========================================================
// �`�揈��
//==========================================================
void CObjectMesh::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		//�f�o�C�X�ւ̃|�C���^���擾
	CTexture *pTexture = CManager::GetInstance()->GetTexture();	// �e�N�X�`���ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	if (m_pVtxBuff != NULL)
	{
		// �F�ݒ�
		//SetSlowCol();

		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(
			0,
			m_pVtxBuff,
			0,
			sizeof(VERTEX_3D));

		//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetIndices(m_pIdexBuff);

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, pTexture->SetAddress(m_nIdxTexture));
		
		//�|���S���̕`��
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
			0,
			0,
			m_nVertex,		//�p�ӂ������_��
			0,
			m_nIndex - 2	//�`�悷��v���~�e�B�u��
		);
	}
}

//==========================================================
// ���_��񐶐�
//==========================================================
void CObjectMesh::CreateVertex(void)
{
	if (m_nVertex <= 0)
	{// �ݒ肳��Ă��Ȃ��ꍇ
		return;
	}

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * m_nVertex,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);
}

//==========================================================
// �C���f�b�N�X��񐶐�
//==========================================================
void CObjectMesh::CreateIndex(void)
{
	if (m_nIndex <= 0)
	{// �ݒ肳��Ă��Ȃ��ꍇ
		return;
	}

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		//�f�o�C�X�ւ̃|�C���^

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nIndex,		// �K�v�ȃC���f�b�N�X��
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdexBuff,
		NULL);
}

//==========================================================
// �C���f�b�N�X���̐ݒ�
//==========================================================
void CObjectMesh::SetIndex(void)
{
	WORD *pIdx;	//�C���f�b�N�X���̃|�C���^

	//�C���f�b�N�X�o�b�t�@�����b�N�����_�ԍ��f�[�^�ւ̃|�C���^���擾
	m_pIdexBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntIdx = 0; nCntIdx < m_nIndex / 2; nCntIdx++)
	{
		pIdx[nCntIdx * 2] = (nCntIdx + m_nNumWidth + 1)
			- (nCntIdx % (m_nNumWidth + 2) / (m_nNumWidth + 1) * (m_nNumWidth + 2))
			- (nCntIdx / (m_nNumWidth + 2));
		pIdx[nCntIdx * 2 + 1] = nCntIdx
			+ (nCntIdx % (m_nNumWidth + 2) / (m_nNumWidth + 1) * (m_nNumWidth + 1))
			- (nCntIdx / (m_nNumWidth + 2));

		pIdx[nCntIdx * 2] = (nCntIdx + m_nNumWidth + 1)
			- (nCntIdx % (m_nNumWidth + 2) / (m_nNumWidth + 1) * (m_nNumWidth + 2))
			- (nCntIdx / (m_nNumWidth + 2));
		pIdx[nCntIdx * 2 + 1] = nCntIdx
			+ (nCntIdx % (m_nNumWidth + 2) / (m_nNumWidth + 1) * (m_nNumWidth + 1))
			- (nCntIdx / (m_nNumWidth + 2));
	}

	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	m_pIdexBuff->Unlock();
}

//==========================================================
// ���_���̔��f
//==========================================================
void CObjectMesh::SetVtx(void)
{
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	for (int nCntVtx = 0; nCntVtx < m_nVertex; nCntVtx++)
	{
		pVtx[nCntVtx].pos = m_pVtx[nCntVtx].pos;
		pVtx[nCntVtx].col = m_pVtx[nCntVtx].col;
		pVtx[nCntVtx].nor = m_pVtx[nCntVtx].nor;
		pVtx[nCntVtx].tex = m_pVtx[nCntVtx].tex;
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//==========================================================
// ����
//==========================================================
void CObjectMesh::Create(int nWidth, int nHeight)
{
	// �c���̖����ݒ�
	m_nNumHeight = nHeight;
	m_nNumWidth = nWidth;

	// ���_���̐ݒ�
	m_nVertex = (m_nNumWidth + 1) * (m_nNumHeight + 1);

	// �C���f�b�N�X���̐ݒ�
	m_nIndex = (m_nNumWidth + 1) * (m_nNumHeight) * 2 + (m_nNumHeight - 1) * 2;

	// ���_�o�b�t�@�̐���
	CreateVertex();

	// �C���f�b�N�X�o�b�t�@�̐���
	CreateIndex();

	// �C���f�b�N�X�̐ݒ�
	SetIndex();

	// ���_���̐���
	m_pVtx = new VERTEX_3D[m_nVertex];
}

//==========================================================
// �e�N�X�`���ԍ��ݒ�
//==========================================================
void CObjectMesh::BindTexture(int nIdx)
{
	m_nIdxTexture = nIdx;
}

//===============================================
// ���W�ݒ�
//===============================================
void CObjectMesh::SetPosition(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//===============================================
// �����ݒ�
//===============================================
void CObjectMesh::SetRotation(const D3DXVECTOR3 rot)
{
	m_rot = rot;

	if (m_rot.x < -D3DX_PI)
	{// z���W�p�x���E
		m_rot.x += D3DX_PI * 2;
	}
	else if (m_rot.x > D3DX_PI)
	{// z���W�p�x���E
		m_rot.x += -D3DX_PI * 2;
	}

	if (m_rot.y < -D3DX_PI)
	{// z���W�p�x���E
		m_rot.y += D3DX_PI * 2;
	}
	else if (m_rot.y > D3DX_PI)
	{// z���W�p�x���E
		m_rot.y += -D3DX_PI * 2;
	}

	if (m_rot.z < -D3DX_PI)
	{// z���W�p�x���E
		m_rot.z += D3DX_PI * 2;
	}
	else if (m_rot.z > D3DX_PI)
	{// z���W�p�x���E
		m_rot.z += -D3DX_PI * 2;
	}
}

//==========================================================
// �}�g���b�N�X�ݒ薳���`��
//==========================================================
void CObjectMesh::NotMtxDraw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		//�f�o�C�X�ւ̃|�C���^���擾
	CTexture *pTexture = CManager::GetInstance()->GetTexture();	// �e�N�X�`���ւ̃|�C���^

	if (m_pVtxBuff != NULL)
	{
		// �F�ݒ�
		//SetSlowCol();

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(
			0,
			m_pVtxBuff,
			0,
			sizeof(VERTEX_3D));

		//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetIndices(m_pIdexBuff);

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, pTexture->SetAddress(m_nIdxTexture));

		//�|���S���̕`��
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
			0,
			0,
			m_nVertex,		//�p�ӂ������_��
			0,
			m_nIndex - 2	//�`�悷��v���~�e�B�u��
		);
	}
}

//==========================================================
// �X���[��ԐF�ݒ�
//==========================================================
void CObjectMesh::SetSlowCol(void)
{
	CSlow *pSlow = CManager::GetInstance()->GetSlow();

	if (pSlow == NULL)
	{
		return;
	}

	if (pSlow->Get() == pSlow->GetOld() || pSlow->Get() > 1.0f)
	{
		return;
	}

	float GetSlowMul = pSlow->Get();

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	for (int nCntVtx = 0; nCntVtx < m_nVertex; nCntVtx++)
	{
		D3DXCOLOR col = m_pVtx[nCntVtx].col;
		m_pVtx[nCntVtx].col = D3DXCOLOR(GetSlowMul, GetSlowMul, GetSlowMul, col.a);
		pVtx[nCntVtx].col = (D3DXCOLOR)m_pVtx[nCntVtx].col;
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}