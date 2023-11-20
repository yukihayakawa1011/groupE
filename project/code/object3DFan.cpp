//==========================================================
//
// 3D��̏��� [object3DFan.cpp]
// Author : Soma Ishihara
//
//==========================================================
#include "object3DFan.h"
#include "manager.h"
#include "renderer.h"

//==========================================================
//�R���X�g���N�^
//==========================================================
CObject3DFan::CObject3DFan(int nPriority) : CObject(nPriority)
{
	//�e��ϐ��̏�����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pVtxBuff = nullptr;
	m_fLength = 0.0f;
	m_nDivision = 3;
}

//==========================================================
//�f�X�g���N�^
//==========================================================
CObject3DFan::~CObject3DFan()
{

}

//==========================================================
//�|���S���̏���������
//==========================================================
HRESULT CObject3DFan::Init(void)
{
	//���_���ݒ�
	ResetpVtx();

	return S_OK;
}

//==========================================================
//�|���S���̏I������
//==========================================================
void CObject3DFan::Uninit(void)
{
	//���_�o�b�t�@�̔p��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	// �p��
	Release();
}

//==========================================================
//�|���S���̕`�揈��
//==========================================================
void CObject3DFan::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		//�f�o�C�X�ւ̃|�C���^���擾

	//���[���h�}�g���b�N�X�̐ݒ�
	SetMtx();
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(
		0,
		m_pVtxBuff,
		0,
		sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, nullptr);

	//�|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLEFAN,	//�v���~�e�B�u�̎��
		0,
		m_nDivision	//���_���\���̂̃T�C�Y
		);
}

//==========================================================
//��������
//==========================================================
CObject3DFan *CObject3DFan::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fLength, float fRadius, int nDivision)
{
	CObject3DFan *pObject3DFan = nullptr;

	// �I�u�W�F�N�g2D�̐���
	pObject3DFan = new CObject3DFan;

	if (pObject3DFan != nullptr)
	{// �����ł����ꍇ
		// ����������
		pObject3DFan->Init();
		pObject3DFan->SetPosition(pos);
		pObject3DFan->SetRotation(rot);
		pObject3DFan->SetLength(fLength);
		pObject3DFan->SetRadius(fRadius);
		pObject3DFan->SetDivision(nDivision);

		// ��ސݒ�
		pObject3DFan->SetType(TYPE_NONE);
	}
	else
	{// �����Ɏ��s�����ꍇ
		return nullptr;
	}

	return pObject3DFan;
}

//==========================================================
// ���_���ݒ�
//==========================================================
void CObject3DFan::SetpVtx(const int nChangeVtx)
{
	VERTEX_3D *pVtx;
	VERTEX_3D *pVtxStart;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(
		0,
		0,
		(void**)&pVtxStart,
		0);

	//���_���W�̐ݒ�
	if ((nChangeVtx & CHANGE_POS) == CHANGE_POS)
	{
		//�擪�����
		pVtx = pVtxStart;
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx++;

		//���̑������
		for (int cnt = 0; cnt < m_nDivision + 1; cnt++)
		{
			//�v�Z
			float fRadiusOne = ((float)cnt / m_nDivision) * m_fRadius;
			D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pos.x = sinf(fRadiusOne - (m_fRadius * 0.5f)) * m_fLength;
			pos.z = cosf(fRadiusOne - (m_fRadius * 0.5f)) * m_fLength;

			//�ݒ�
			pVtx[cnt].pos = pos;
		}
	}

	//�@���x�N�g���̐ݒ�
	if ((nChangeVtx & CHANGE_NOR) == CHANGE_NOR)
	{
		//�擪�����
		pVtx = pVtxStart;
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx++;

		//���̑������
		for (int cnt = 0; cnt < m_nDivision + 1; cnt++)
		{
			pVtx[cnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		}
	}

	//���_�J���[�̐ݒ�
	if ((nChangeVtx & CHANGE_COL) == CHANGE_COL)
	{
		//�擪�����
		pVtx = pVtxStart;
		pVtx[0].col = m_col;
		pVtx++;

		//���̑������
		for (int cnt = 0; cnt < m_nDivision + 1; cnt++)
		{
			pVtx[cnt].col = m_col;
		}
	}

	//�e�N�X�`�����W�̐ݒ�
	if ((nChangeVtx & CHANGE_TEX) == CHANGE_TEX)
	{
		//�擪�����
		pVtx = pVtxStart;
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx++;

		//���̑������
		for (int cnt = 0; cnt < m_nDivision + 1; cnt++)
		{
			pVtx[cnt].tex = D3DXVECTOR2(0.0f, 0.0f);
		}
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//==========================================================
// �����ݒ�
//==========================================================
void CObject3DFan::SetLength(const float fLength)
{
	m_fLength = fLength;

	//���_���ݒ�
	SetpVtx(CHANGE_POS);
}

//==========================================================
// �p�x�ݒ�
//==========================================================
void CObject3DFan::SetRadius(const float fRadius)
{
	m_fRadius = fRadius;

	//���_���ݒ�
	SetpVtx(CHANGE_POS);
}

//==========================================================
// �������ݒ�i�Œ�3�`�j
//==========================================================
void CObject3DFan::SetDivision(const int nDiv)
{
	m_nDivision = (nDiv > 3) ? nDiv : 3;	//�Œ�3���_�ȏ�ɂ��邱��

	//���_���Đ���
	ResetpVtx();
}

//==========================================================
// �F�ݒ�
//==========================================================
void CObject3DFan::SetColor(const D3DXCOLOR col)
{
	m_col = col;

	//���_���ݒ�
	SetpVtx(CHANGE_COL);
}

//==========================================================
// �}�g���b�N�X�ݒ�
//==========================================================
void CObject3DFan::SetMtx(void)
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
// ���_���o�b�t�@���݂ōĐݒ�
//==========================================================
HRESULT CObject3DFan::ResetpVtx(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		//�f�o�C�X�ւ̃|�C���^���擾

	//���_�o�b�t�@�̔p��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * (m_nDivision + 2),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		nullptr)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	SetpVtx(CHANGE_ALL);

	return S_OK;
}
