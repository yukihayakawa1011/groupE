//==========================================================
//
//�|���S���`�揈��
//Author ����ɐ�
//
//==========================================================
#include "main.h"
#include "object3D.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "debugproc.h"

//==========================================================
//�}�N����`
//==========================================================
#define TEXTUREFILE_DATA	"data\\TEXTURE\\bg0000.png"		//�e�N�X�`���f�[�^

//==========================================================
//�R���X�g���N�^
//==========================================================
CObject3D::CObject3D(int nPriority) : CObject(nPriority)
{
	m_nIdxTexture = -1;

	//�e��ϐ��̏�����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//==========================================================
//�f�X�g���N�^
//==========================================================
CObject3D::~CObject3D()
{

}

//==========================================================
//�|���S���̏���������
//==========================================================
HRESULT CObject3D::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		//�f�o�C�X�ւ̃|�C���^���擾
	CTexture *pTexture = CManager::GetInstance()->GetTexture();	// �e�N�X�`���ւ̃|�C���^

	// �e�N�X�`���̊��蓖��
	m_nIdxTexture = pTexture->Regist(TEXTUREFILE_DATA);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	D3DXVECTOR3 vecLine, vecline2, vec;	//����p�ϐ�
	D3DXVECTOR3 vecOldPos;	//�O��̍��W�x�N�g��

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-300.0f, 200.0f, +300.0f);
	pVtx[1].pos = D3DXVECTOR3(+300.0f, 100.0f, +300.0f);
	pVtx[2].pos = D3DXVECTOR3(-300.0f, 100.0f, -300.0f);
	pVtx[3].pos = D3DXVECTOR3(+300.0f, 0.0f, -300.0f);

	//Pos0����̃x�N�g�������߂�
	vecLine = pVtx[1].pos - pVtx[0].pos;
	vecline2 = pVtx[2].pos - pVtx[0].pos;

	D3DXVec3Cross(&vec, &vecLine, &vecline2);

	D3DXVec3Normalize(&vec, &vec);	// �x�N�g���𐳋K������

	//���݂̈ʒu�Ƃ̖ʐς����߂�
	pVtx[0].nor = vec;

	//�ǂ̃x�N�g�������߂�
	vecLine = pVtx[2].pos - pVtx[3].pos;
	vecline2 = pVtx[1].pos - pVtx[3].pos;

	//���݂̈ʒu�Ƃ̖ʐς����߂�
	D3DXVec3Cross(&vec, &vecLine, &vecline2);

	D3DXVec3Normalize(&vec, &vec);	// �x�N�g���𐳋K������

	pVtx[3].nor = vec;

	pVtx[1].nor = (pVtx[0].nor + pVtx[3].nor) / 2;
	pVtx[2].nor = (pVtx[0].nor + pVtx[3].nor) / 2;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//==========================================================
//�|���S���̏I������
//==========================================================
void CObject3D::Uninit(void)
{
	//���_�o�b�t�@�̔p��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �p��
	Release();

}

//==========================================================
//�|���S���̍X�V����
//==========================================================
void CObject3D::Update(void)
{

}

//==========================================================
//�|���S���̕`�揈��
//==========================================================
void CObject3D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		//�f�o�C�X�ւ̃|�C���^���擾
	CTexture *pTexture = CManager::GetInstance()->GetTexture();	// �e�N�X�`���ւ̃|�C���^

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

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

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->SetAddress(m_nIdxTexture));

	//�|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
		0,
		2	//���_���\���̂̃T�C�Y
		);
}

//==========================================================
//��������
//==========================================================
CObject3D *CObject3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CObject3D *pObject3D = NULL;

	// �I�u�W�F�N�g2D�̐���
	pObject3D = new CObject3D;

	if (pObject3D != NULL)
	{// �����ł����ꍇ
		// ����������
		pObject3D->Init();

		pObject3D->SetPosition(pos);

		// ��ސݒ�
		pObject3D->SetType(TYPE_NONE);
	}
	else
	{// �����Ɏ��s�����ꍇ
		return NULL;
	}

	return pObject3D;
}

//==========================================================
// ���_���ݒ�
//==========================================================
void CObject3D::SetpVtx(float fWidth, float fHeight)
{
	m_fWidth = fWidth;
	m_fHeight = fHeight;
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth, 0.0f, +m_fHeight);
	pVtx[1].pos = D3DXVECTOR3(+m_fWidth, 0.0f, +m_fHeight);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth, 0.0f, -m_fHeight);
	pVtx[3].pos = D3DXVECTOR3(+m_fWidth, 0.0f, -m_fHeight);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

void CObject3D::BindTexture(int nIdx)
{
	m_nIdxTexture = nIdx;
}

//==========================================================
// ���_���ݒ�
//==========================================================
float CObject3D::GetHeight(D3DXVECTOR3 pos, D3DXVECTOR3 &normal)
{
	float fHeight = 0.0f;	// ����
	D3DXVECTOR3 Pos0, Pos1, Pos2, Pos3;
	D3DXVECTOR3 vecToPos;	//����p�ϐ�
	D3DXVECTOR3 vec1, vec2;	//����p�ϐ�
	D3DXVECTOR3 nor0, nor3;
	float fRate, fRate2;	//����p�ϐ�
	float fMaxField;		//����p
	float fField, fField2;
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	Pos0 = pVtx[0].pos;
	nor0 = pVtx[0].nor;
	Pos1 = pVtx[1].pos;
	Pos2 = pVtx[2].pos;
	Pos3 = pVtx[3].pos;
	nor3 = pVtx[3].nor;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	// Pos0����̃x�N�g�������߂�
	vec1 = Pos1 - Pos0;
	vec2 = Pos2 - Pos0;

	// ���݂̍��W�̃x�N�g�������߂�
	vecToPos = D3DXVECTOR3(pos.x - (m_pos.x + Pos0.x),
		pos.y - (m_pos.y + Pos0.y),
		pos.z - (m_pos.z + Pos0.z));

	// �ʐς����߂�
	fMaxField = (vec1.x * vec2.z) - (vec1.z * vec2.x);

	// ���݂̈ʒu�Ƃ̖ʐς����߂�
	fField = (vecToPos.x * vec2.z) - (vecToPos.z * vec2.x);
	fField2 = (vecToPos.z * vec1.x) - (vecToPos.x * vec1.z);

	// ��_�̊��������߂�
	fRate = fField / fMaxField;
	fRate2 = fField2 / fMaxField;

	// �͈͓�����
	if (nor0.y != 0.0f)
	{
		if (fRate >= 0.0f && fRate <= 1.0f && fRate2 >= 0.0f && fRate2 <= 1.0f && (fRate + fRate2) <= 1.0f)
		{// �O�p�|���S���̒��ɂ���

			fHeight = -((pos.x - (m_pos.x + Pos0.x)) * nor0.x / nor0.y) +
				-((pos.z - (m_pos.z + Pos0.z)) * nor0.z / nor0.y) + (m_pos.y + Pos0.y);

			normal = nor0;

			return fHeight;
		}
	}

	// Pos3����̃x�N�g�������߂�
	vec1 = Pos1 - Pos3;  
	vec2 = Pos2 - Pos3;

	// ���݂̍��W�̃x�N�g�������߂�
	vecToPos = D3DXVECTOR3(pos.x - (m_pos.x + Pos3.x),
		pos.y - (m_pos.y + Pos3.y),
		pos.z - (m_pos.z + Pos3.z));

	// �ʐς����߂�
	fMaxField = (vec1.x * vec2.z) - (vec1.z * vec2.x);

	// ���݂̈ʒu�Ƃ̖ʐς����߂�
	fField = (vecToPos.x * vec2.z) - (vecToPos.z * vec2.x);
	fField2 = (vecToPos.z * vec1.x) - (vecToPos.x * vec1.z);

	// ��_�̊��������߂�
	fRate = fField / fMaxField;
	fRate2 = fField2 / fMaxField;

	// �͈͓�����
	if (nor3.y != 0.0f)
	{
		if (fRate >= 0.0f && fRate <= 1.0f && fRate2 >= 0.0f && fRate2 <= 1.0f && (fRate + fRate2) <= 1.0f)
		{// �O�p�|���S���̒��ɂ���
			fHeight = -((pos.x - (m_pos.x + Pos3.x)) * nor3.x / nor3.y) +
				-((pos.z - (m_pos.z + Pos3.z)) * nor3.z / nor3.y) + (m_pos.y + Pos3.y);

			normal = nor3;

			return fHeight;
		}
	}

	return pos.y;
}

//==========================================================
//�T�C�Y�ݒ�
//==========================================================
void CObject3D::SetSize(float fWidth, float fHeight)
{
	VERTEX_3D *pVtx;

	m_fWidth = fWidth;
	m_fHeight = fHeight;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth, +m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+m_fWidth, +m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth, -m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+m_fWidth, -m_fHeight, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//==========================================================
// �F�ݒ�
//==========================================================
void CObject3D::SetCol(D3DXCOLOR col)
{
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//==========================================================
// �F�ݒ�
//==========================================================
void CObject3D::SetTextureVtx(float fWidth, float fHeight)
{
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(fWidth, fHeight);
	pVtx[1].tex = D3DXVECTOR2(fWidth + 1.0f, fHeight);
	pVtx[2].tex = D3DXVECTOR2(fWidth, fHeight + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(fWidth + 1.0f, fHeight + 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//==========================================================
// �}�g���b�N�X�ݒ�
//==========================================================
void CObject3D::SetMtx(void)
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