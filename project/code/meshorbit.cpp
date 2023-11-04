//==========================================================
//
//���b�V���\���̋O�Տ��� [meshorbit.cpp]
//Author Ibuki Okusada
//
//==========================================================
#include "meshorbit.h"
#include "manager.h"
#include "debugproc.h"
#include "renderer.h"
#include "main.h"
#include "slow.h"

//==========================================================
//�}�N����`
//==========================================================
#define MAX_WIDTH	(16)// �O�Ղ̕����_��
#define MAX_HEIGHT	(2)	// �O�Ղ̍������_��

int CMeshOrbit::m_nNumAll = 0;

//==========================================================
// �R���X�g���N�^
//==========================================================
CMeshOrbit::CMeshOrbit() : CObjectMesh(5)
{
	m_pMtxParent = NULL;
	m_fTimer = 0;
	m_pPos = NULL;

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_aOffSet[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_aCol[nCnt] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	m_nNumAll++;
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CMeshOrbit::~CMeshOrbit()
{
	m_nNumAll--;
}

//==========================================================
// ����������
//==========================================================
HRESULT CMeshOrbit::Init(void)
{
	// �J�n�_�����Z�b�g
	m_rot.z = (float)(rand() % 629 - 314) * 0.01f;

	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CMeshOrbit::Uninit(void)
{
	if (m_type != TYPE_BULLET)
	{
		CObjectMesh::Uninit();

		if (m_pPos != NULL)
		{
			delete[] m_pPos;
			m_pPos = NULL;
		}

		if (m_pCol != NULL)
		{
			delete[] m_pCol;
			m_pCol = NULL;
		}
	}
	else
	{
		m_pMtxParent = NULL;
	}
}

//==========================================================
// �X�V����
//==========================================================
void CMeshOrbit::Update(void)
{
	m_fTimer += CManager::GetInstance()->GetSlow()->Get();

	if (m_fTimer >= 1)
	{
		// ���_�ݒ�
		SetVtxInfo();
		m_fTimer = 0;
	}
}

//==========================================================
// �`�揈��
//==========================================================
void CMeshOrbit::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		//�f�o�C�X�ւ̃|�C���^

	//���C�e�B���O���I�t�ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�J�����O�I���ɂ���
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//���b�V���\���̋O�Ղ�`��
	CObjectMesh::NotMtxDraw();

	//�J�����O�I�t�ɂ���
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//���C�e�B���O���I���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================================
// ����
//==========================================================
CMeshOrbit *CMeshOrbit::Create(D3DXMATRIX *pMtx, D3DXVECTOR3 UpSet, D3DXVECTOR3 DownSet, TYPE type)
{
	CMeshOrbit *pMeshOrbit = NULL;	// ���b�V���t�B�[���h�̃|�C���^
	CTexture *pTexture = CManager::GetInstance()->GetTexture();	// �e�N�X�`���ւ̃|�C���^

	// �������̊m��
	pMeshOrbit = new CMeshOrbit;

	if (pMeshOrbit != NULL)
	{// �m�ۂł����ꍇ

		// ������
		pMeshOrbit->Init();

		// ���W�ݒ�
		pMeshOrbit->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		// �e�ݒ�
		pMeshOrbit->SetParent(pMtx);

		// �I�t�Z�b�g�ݒ�
		pMeshOrbit->SetOffSet(UpSet, DownSet);

		// ���_����
		pMeshOrbit->CObjectMesh::Create(MAX_WIDTH - 1, MAX_HEIGHT - 1);

		// �e�N�X�`���ݒ�
		pMeshOrbit->BindTexture(-1);

		// �ێ��p���_����
		pMeshOrbit->m_pPos = new D3DXVECTOR3[pMeshOrbit->GetVertex()];

		// �ێ��p�J���[����
		pMeshOrbit->m_pCol= new D3DXCOLOR[pMeshOrbit->GetVertex()];

		// ���_��񏉊���
		pMeshOrbit->Reset();

		pMeshOrbit->m_type = type;

		pMeshOrbit->m_fRadius = UpSet.y + -DownSet.y * 0.5f;
	}

	return pMeshOrbit;
}

//==========================================================
// ���_�ݒ�
//==========================================================
void CMeshOrbit::SetVtxInfo(void)
{
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX *pMtxWorld = GetMtx();	//���[���h�}�g���b�N�X

	if (m_pMtxParent != NULL)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_aMtxWorldPoint[0]);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_aOffSet[0].x, m_aOffSet[0].y, m_aOffSet[0].z);
		D3DXMatrixMultiply(&m_aMtxWorldPoint[0], &m_aMtxWorldPoint[0], &mtxTrans);

		//�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���������킹��
		D3DXMatrixMultiply(&m_aMtxWorldPoint[0],
			&m_aMtxWorldPoint[0], m_pMtxParent);

		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_aMtxWorldPoint[1]);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_aOffSet[1].x, m_aOffSet[1].y, m_aOffSet[1].z);
		D3DXMatrixMultiply(&m_aMtxWorldPoint[1], &m_aMtxWorldPoint[1], &mtxTrans);

		//�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���������킹��
		D3DXMatrixMultiply(&m_aMtxWorldPoint[1],
			&m_aMtxWorldPoint[1], m_pMtxParent);
	}

	switch (m_type)
	{
	case TYPE_NONE:
		SetNone();
		break;

	case TYPE_PLAYER:
		SetPlayer();
		break;

	case TYPE_BULLET:
		SetBullet();
		break;
	}
}

//==========================================================
// ���Z�b�g
//==========================================================
void CMeshOrbit::Reset(void)
{
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX *pMtxWorld = GetMtx();	//���[���h�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_aMtxWorldPoint[0]);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_aOffSet[0].x, m_aOffSet[0].y, m_aOffSet[0].z);
	D3DXMatrixMultiply(&m_aMtxWorldPoint[0], &m_aMtxWorldPoint[0], &mtxTrans);

	//�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���������킹��
	D3DXMatrixMultiply(&m_aMtxWorldPoint[0],
		&m_aMtxWorldPoint[0], m_pMtxParent);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_aMtxWorldPoint[1]);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_aOffSet[1].x, m_aOffSet[1].y, m_aOffSet[1].z);
	D3DXMatrixMultiply(&m_aMtxWorldPoint[1], &m_aMtxWorldPoint[1], &mtxTrans);

	//�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���������킹��
	D3DXMatrixMultiply(&m_aMtxWorldPoint[1],
		&m_aMtxWorldPoint[1], m_pMtxParent);

	// ��ނ��Ƃɂ��炷

	//�ۑ����Ă���������炷
	for (int nCntHeight = 0; nCntHeight < MAX_HEIGHT; nCntHeight++)
	{
		for (int nCntWidth = 0; nCntWidth < MAX_WIDTH; nCntWidth++)
		{
			m_pPos[nCntHeight * MAX_WIDTH + nCntWidth].x = m_aMtxWorldPoint[nCntHeight]._41;
			m_pPos[nCntHeight * MAX_WIDTH + nCntWidth].y = m_aMtxWorldPoint[nCntHeight]._42;
			m_pPos[nCntHeight * MAX_WIDTH + nCntWidth].z = m_aMtxWorldPoint[nCntHeight]._43;
			m_pVtx[nCntHeight * MAX_WIDTH + nCntWidth].pos = m_aOffSet[nCntHeight];
			m_pVtx[nCntHeight * MAX_WIDTH + nCntWidth].tex = D3DXVECTOR2(nCntWidth * 1.0f, nCntHeight * 1.0f);
			m_pCol[nCntHeight * MAX_WIDTH + nCntWidth] = m_aCol[nCntHeight];
			m_pVtx[nCntHeight * MAX_WIDTH + nCntWidth].col = m_pCol[nCntHeight * MAX_WIDTH + nCntWidth];
		}
	}

	// ���_���ݒ�
	SetVtx();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(pMtxWorld);

	//�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���������킹��
	D3DXMatrixMultiply(pMtxWorld,
		pMtxWorld, m_pMtxParent);

	pMtxWorld->_11 = 1.0f;
	pMtxWorld->_13 = 0.0f;
	pMtxWorld->_31 = 0.0f;
	pMtxWorld->_33 = 1.0f;

	//�ʒu�𔽉f
	SetMtx(*pMtxWorld);
}

//==========================================================
// �v���C���[�ݒ�
//==========================================================
void CMeshOrbit::SetPlayer(void)
{

}

//==========================================================
// �e�ݒ�
//==========================================================
void CMeshOrbit::SetBullet(void)
{
	D3DXMATRIX *pMtxWorld = GetMtx();	//���[���h�}�g���b�N�X

	//�ۑ����Ă���������炷
	for (int nCntHeight = 0; nCntHeight < MAX_HEIGHT; nCntHeight++)
	{
		for (int nCntWidth = MAX_WIDTH; nCntWidth > 1; nCntWidth--)
		{
			m_pPos[nCntHeight * MAX_WIDTH + nCntWidth - 1] = m_pPos[nCntHeight * MAX_WIDTH + nCntWidth - 2];
			m_pCol[nCntHeight * MAX_WIDTH + nCntWidth - 1] = m_pCol[nCntHeight * MAX_WIDTH + nCntWidth - 2];

			m_pCol[nCntHeight * MAX_WIDTH + nCntWidth - 1].a -= (float)(1.0f / MAX_WIDTH);
			m_pVtx[nCntHeight * MAX_WIDTH + nCntWidth - 1].pos.x =
				m_pPos[nCntHeight * MAX_WIDTH + nCntWidth - 1].x - m_aMtxWorldPoint[nCntHeight]._41 + m_aOffSet[nCntHeight].x + m_aOffSet[nCntHeight].z + (float)((rand() % 10 - 5) % 100);
			m_pVtx[nCntHeight * MAX_WIDTH + nCntWidth - 1].pos.y =
				m_pPos[nCntHeight * MAX_WIDTH + nCntWidth - 1].y - m_aMtxWorldPoint[nCntHeight]._42 + m_aOffSet[nCntHeight].y + 10.0f * (1.0f / nCntWidth);
			m_pVtx[nCntHeight * MAX_WIDTH + nCntWidth - 1].pos.z =
				m_pPos[nCntHeight * MAX_WIDTH + nCntWidth - 2].z - m_aMtxWorldPoint[nCntHeight]._43 + m_aOffSet[nCntHeight].z + m_aOffSet[nCntHeight].x + (float)((rand() % 10 - 5) % 100);
			m_pVtx[nCntHeight * MAX_WIDTH + nCntWidth - 1].col = m_pCol[nCntHeight * MAX_WIDTH + nCntWidth - 1];

			/*if (nCntWidth <= MAX_HEIGHT - 6)
			{
				CParticle::Create(m_pPos[nCntHeight * MAX_WIDTH + nCntWidth - 1], m_nor, CEffect::TYPE_BULLET);
			}*/
		}
	}

	m_rot.z += 1.0f;

	if (m_rot.z > D3DX_PI)
	{
		m_rot.z += -D3DX_PI * 2;
	}

	if (m_pMtxParent != NULL)
	{// �e������
	//�ŐV�̏�����
		m_pPos[0].x = m_pMtxParent->_41 + cosf((m_rot.z + D3DX_PI * 1.0f) * sinf(m_nor.z)) * m_fRadius;
		m_pPos[0].y = m_pMtxParent->_42 + sinf(m_rot.z + D3DX_PI * 1.0f + (m_nor.y * D3DX_PI)) * m_fRadius;
		m_pPos[0].z = m_pMtxParent->_43 + cosf((m_rot.z + D3DX_PI * 1.0f) * cosf(m_nor.x)) * m_fRadius;

		//m_pPos[0].x = m_aMtxWorldPoint[0]._41;
		//m_pPos[0].y = m_aMtxWorldPoint[0]._42;
		//m_pPos[0].z = m_aMtxWorldPoint[0]._43;
		m_pCol[0] = m_aCol[0];
		m_pVtx[0].pos.x = m_pPos[0].x - m_aMtxWorldPoint[0]._41 + m_aOffSet[0].x;
		m_pVtx[0].pos.y = m_pPos[0].y - m_aMtxWorldPoint[0]._42 + m_aOffSet[0].y;
		m_pVtx[0].pos.z = m_pPos[0].z - m_aMtxWorldPoint[0]._43 + m_aOffSet[0].z;

		m_pPos[MAX_WIDTH].x = m_pMtxParent->_41 + cosf((m_rot.z + D3DX_PI * 0.0f) * sinf(m_nor.z)) * m_fRadius;
		m_pPos[MAX_WIDTH].y = m_pMtxParent->_42 + sinf(m_rot.z + D3DX_PI * 0.0f + (m_nor.y * D3DX_PI)) * m_fRadius;
		m_pPos[MAX_WIDTH].z = m_pMtxParent->_43 + cosf((m_rot.z + D3DX_PI * 0.0f) * cosf(m_nor.x)) * m_fRadius;
		/*m_pPos[MAX_WIDTH].x = m_aMtxWorldPoint[1]._41;
		m_pPos[MAX_WIDTH].y = m_aMtxWorldPoint[1]._42;
		m_pPos[MAX_WIDTH].z = m_aMtxWorldPoint[1]._43;*/
		m_pVtx[MAX_WIDTH].pos.y = m_aOffSet[1].y;
		m_pCol[MAX_WIDTH] = m_aCol[1];
	}

	m_pVtx[MAX_WIDTH].pos.x = m_pPos[MAX_WIDTH].x - m_aMtxWorldPoint[1]._41 + m_aOffSet[1].x;
	m_pVtx[MAX_WIDTH].pos.y = m_pPos[MAX_WIDTH].y - m_aMtxWorldPoint[1]._42 + m_aOffSet[1].y;
	m_pVtx[MAX_WIDTH].pos.z = m_pPos[MAX_WIDTH].z - m_aMtxWorldPoint[1]._43 + m_aOffSet[1].z;

	SetVtx();

	if (m_pMtxParent != NULL)
	{// �e������
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(pMtxWorld);

		//�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���������킹��
		D3DXMatrixMultiply(pMtxWorld,
			pMtxWorld, m_pMtxParent);
	}
	else
	{// ������
		if (m_pPos[0].x + 1.0f >= m_pPos[MAX_WIDTH - 1].x && m_pPos[0].x - 1.0f <= m_pPos[MAX_WIDTH - 1].x &&
			m_pPos[0].y + 1.0f >= m_pPos[MAX_WIDTH - 1].y && m_pPos[0].y - 1.0f <= m_pPos[MAX_WIDTH - 1].y &&
			m_pPos[0].z + 1.0f >= m_pPos[MAX_WIDTH - 1].z && m_pPos[0].z - 1.0f <= m_pPos[MAX_WIDTH - 1].z)
		{
			CObjectMesh::Uninit();

			if (m_pPos != NULL)
			{
				delete[] m_pPos;
				m_pPos = NULL;
			}

			if (m_pCol != NULL)
			{
				delete[] m_pCol;
				m_pCol = NULL;
			}
		}
	}

	pMtxWorld->_11 = 1.0f;
	pMtxWorld->_13 = 0.0f;
	pMtxWorld->_31 = 0.0f;
	pMtxWorld->_33 = 1.0f;

	//�ʒu�𔽉f

	SetMtx(*pMtxWorld);
}

//==========================================================
// ���̂ق��ݒ�
//==========================================================
void CMeshOrbit::SetNone(void)
{
	D3DXMATRIX *pMtxWorld = GetMtx();	//���[���h�}�g���b�N�X

	//�ۑ����Ă���������炷
	for (int nCntHeight = 0; nCntHeight < MAX_HEIGHT; nCntHeight++)
	{
		for (int nCntWidth = MAX_WIDTH; nCntWidth > 1; nCntWidth--)
		{
			m_pPos[nCntHeight * MAX_WIDTH + nCntWidth - 1] = m_pPos[nCntHeight * MAX_WIDTH + nCntWidth - 2];
			m_pCol[nCntHeight * MAX_WIDTH + nCntWidth - 1] = m_pCol[nCntHeight * MAX_WIDTH + nCntWidth - 2];
			m_pCol[nCntHeight * MAX_WIDTH + nCntWidth - 1].a -= (float)(1.0f / MAX_WIDTH);
			m_pVtx[nCntHeight * MAX_WIDTH + nCntWidth - 1].pos.x =
				m_pPos[nCntHeight * MAX_WIDTH + nCntWidth - 1].x - m_aMtxWorldPoint[nCntHeight]._41 + m_aOffSet[nCntHeight].x;
			m_pVtx[nCntHeight * MAX_WIDTH + nCntWidth - 1].pos.y =
				m_pPos[nCntHeight * MAX_WIDTH + nCntWidth - 1].y - m_aMtxWorldPoint[nCntHeight]._42 + m_aOffSet[nCntHeight].y;
			m_pVtx[nCntHeight * MAX_WIDTH + nCntWidth - 1].pos.z = m_pPos[nCntHeight * MAX_WIDTH + nCntWidth - 2].z - m_aMtxWorldPoint[nCntHeight]._43 + m_aOffSet[nCntHeight].z;
			m_pVtx[nCntHeight * MAX_WIDTH + nCntWidth - 1].col = m_pCol[nCntHeight * MAX_WIDTH + nCntWidth - 1];
		}
	}

	//�ŐV�̏�����
	m_pPos[0].x = m_aMtxWorldPoint[0]._41;
	m_pPos[0].y = m_aMtxWorldPoint[0]._42;
	m_pPos[0].z = m_aMtxWorldPoint[0]._43;
	m_pVtx[0].pos.y = m_aOffSet[0].y;

	m_pPos[MAX_WIDTH].x = m_aMtxWorldPoint[1]._41;
	m_pPos[MAX_WIDTH].y = m_aMtxWorldPoint[1]._42;
	m_pPos[MAX_WIDTH].z = m_aMtxWorldPoint[1]._43;
	m_pVtx[MAX_WIDTH].pos.y = m_aOffSet[1].y;

	SetVtx();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(pMtxWorld);

	//�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���������킹��
	D3DXMatrixMultiply(pMtxWorld,
		pMtxWorld, m_pMtxParent);

	pMtxWorld->_11 = 1.0f;
	pMtxWorld->_13 = 0.0f;
	pMtxWorld->_21 = 0.0f;
	pMtxWorld->_23 = 0.0f;
	pMtxWorld->_31 = 0.0f;
	pMtxWorld->_33 = 1.0f;

	//�ʒu�𔽉f
	SetMtx(*pMtxWorld);
}

//==========================================================
// �F�̐ݒ�
//==========================================================
void CMeshOrbit::SetCol(D3DXCOLOR col)
{
	for (int nCnt = 0; nCnt < ORBIT_EDGE; nCnt++)
	{
		m_aCol[nCnt] = col;
	}
}