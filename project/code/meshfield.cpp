//==========================================================
//
// ���b�V���t�B�[���h�̏��� [meshfield.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "meshfield.h"
#include "texture.h"
#include "manager.h"
#include "debugproc.h"
#include "input.h"

CMeshField *CMeshField::m_pTop = NULL;	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
CMeshField *CMeshField::m_pCur = NULL;	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^

//==========================================================
// �R���X�g���N�^
//==========================================================
CMeshField::CMeshField()
{
	m_pNext = NULL;
	m_pPrev = NULL;

	// �������g�����X�g�ɒǉ�
	if (m_pTop != NULL)
	{// �擪�����݂��Ă���ꍇ
		m_pCur->m_pNext = this;	// ���ݍŌ���̃I�u�W�F�N�g�̃|�C���^�ɂȂ���
		m_pPrev = m_pCur;
		m_pCur = this;	// �������g���Ō���ɂȂ�
	}
	else
	{// ���݂��Ȃ��ꍇ
		m_pTop = this;	// �������g���擪�ɂȂ�
		m_pCur = this;	// �������g���Ō���ɂȂ�
	}

	m_bHot = false;
	m_tex = D3DXVECTOR2(0.0f, 0.0f);
	m_texmove = D3DXVECTOR2(0.0f, 0.0f);
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CMeshField::~CMeshField()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CMeshField::Init(void)
{
	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CMeshField::Uninit(void)
{
	//���_�o�b�t�@�̔p��
	CObjectMesh::Uninit();

	// ���X�g���玩�����g���폜����
	if (m_pTop == this)
	{// ���g���擪
		if (m_pNext != NULL)
		{// �������݂��Ă���
			m_pTop = m_pNext;	// ����擪�ɂ���
			m_pNext->m_pPrev = NULL;	// ���̑O�̃|�C���^���o���Ă��Ȃ��悤�ɂ���
		}
		else
		{// ���݂��Ă��Ȃ�
			m_pTop = NULL;	// �擪���Ȃ���Ԃɂ���
			m_pCur = NULL;	// �Ō�����Ȃ���Ԃɂ���
		}
	}
	else if (m_pCur == this)
	{// ���g���Ō��
		if (m_pPrev != NULL)
		{// �������݂��Ă���
			m_pCur = m_pPrev;			// �O���Ō���ɂ���
			m_pPrev->m_pNext = NULL;	// �O�̎��̃|�C���^���o���Ă��Ȃ��悤�ɂ���
		}
		else
		{// ���݂��Ă��Ȃ�
			m_pTop = NULL;	// �擪���Ȃ���Ԃɂ���
			m_pCur = NULL;	// �Ō�����Ȃ���Ԃɂ���
		}
	}
	else
	{
		if (m_pNext != NULL)
		{
			m_pNext->m_pPrev = m_pPrev;	// ���g�̎��ɑO�̃|�C���^���o��������
		}
		if (m_pPrev != NULL)
		{
			m_pPrev->m_pNext = m_pNext;	// ���g�̑O�Ɏ��̃|�C���^���o��������
		}
	}
}

//==========================================================
// �X�V����
//==========================================================
void CMeshField::Update(void)
{
	// �e�N�X�`���X�V
	m_tex += m_texmove;
	if (m_tex.x < 0.0f)
	{
		m_tex.x += 1.0f;
	}
	else if (m_tex.x > 1.0f)
	{
		m_tex.x -= 1.0f;
	}
	if (m_tex.y < 0.0f)
	{
		m_tex.y += 1.0f;
	}
	else if (m_tex.y > 1.0f)
	{
		m_tex.y -= 1.0f;
	}

	SetTex();
}

//==========================================================
// �`�揈��
//==========================================================
void CMeshField::Draw(void)
{
	// �`��
	CObjectMesh::Draw();
}

//==========================================================
// ���_���ݒ�
//==========================================================
void CMeshField::SetVtxInfo(void)
{
	int nVertex = GetVertex();			// ���_�����擾
	int nNumWidth = GetNumWidth();		// ���������擾
	int nNumHeight = GetNumHeight();	// �����������擾

	//���_���W�̐ݒ�(��������E��O�Ɍ������Ē��_����ݒ肷��
	for (int nCntpVtx = 0; nCntpVtx < nVertex; nCntpVtx++)
	{
		//���_���W
		m_pVtx[nCntpVtx].pos.x = -(m_fWidth * nNumWidth) + (nCntpVtx % (nNumWidth + 1) * (m_fWidth * 2));
		m_pVtx[nCntpVtx].pos.y = 0.0f;
		m_pVtx[nCntpVtx].pos.z = (m_fHeight * nNumHeight) + ((nCntpVtx / (nNumWidth + 1) * (-m_fHeight * 2)));

		//�F
		m_pVtx[nCntpVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		m_pVtx[nCntpVtx].tex = D3DXVECTOR2(m_tex.x + 1.0f * (nCntpVtx % (nNumWidth + 1)), m_tex.y + 1.0f * (nCntpVtx / (nNumWidth + 1)));
	}

	// �@���x�N�g���̐ݒ�
	D3DXVECTOR3 nor, vec1, vec2;
	VERTEX_3D *aVtx[4];

	for (int nCntHeight = 0; nCntHeight < GetNumHeight(); nCntHeight++)
	{
		for (int nCntWidth = 0; nCntWidth < GetNumWidth(); nCntWidth++)
		{

			aVtx[0] = &m_pVtx[nCntHeight * (GetNumWidth() + 1) + nCntWidth + 0];
			aVtx[1] = &m_pVtx[nCntHeight * (GetNumWidth() + 1) + nCntWidth + 1];
			aVtx[2] = &m_pVtx[nCntHeight * (GetNumWidth() + 1) + nCntWidth + GetNumWidth() + 1];
			aVtx[3] = &m_pVtx[nCntHeight * (GetNumWidth() + 1) + nCntWidth + GetNumWidth() + 2];

			//Pos0����̃x�N�g�������߂�
			vec1 = aVtx[1]->pos - aVtx[0]->pos;
			vec2 = aVtx[2]->pos - aVtx[0]->pos;

			D3DXVec3Cross(&aVtx[0]->nor, &vec1, &vec2);

			D3DXVec3Normalize(&aVtx[0]->nor, &aVtx[0]->nor);	// �x�N�g���𐳋K������

			//Pos3����̃x�N�g�������߂�
			vec1 = aVtx[2]->pos - aVtx[3]->pos;
			vec2 = aVtx[1]->pos - aVtx[3]->pos;

			D3DXVec3Cross(&aVtx[3]->nor, &vec1, &vec2);

			D3DXVec3Normalize(&aVtx[3]->nor, &aVtx[3]->nor);	// �x�N�g���𐳋K������

			aVtx[1]->nor = (aVtx[0]->nor + aVtx[3]->nor) / 2;
			aVtx[2]->nor = (aVtx[0]->nor + aVtx[3]->nor) / 2;
		}
	}

	//for (int nCntpVtx = 0; nCntpVtx < nVertex; nCntpVtx++)
	//{
	//	if (nCntpVtx > 0 && nCntpVtx < nVertex - 1)
	//	{// �ŏ��ƍŌ�ȊO
	//		if (nCntpVtx > GetNumWidth() + 1 && nCntpVtx < (GetNumWidth() + 1) * GetNumHeight() &&
	//			nCntpVtx % (GetNumWidth() + 1) > 0 && nCntpVtx % (GetNumWidth() + 1) < GetNumWidth())
	//		{// 6�̖ʂƊւ���Ă���
	//			D3DXVECTOR3 norAdd = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//			norAdd += m_pVtx[nCntpVtx - 1].nor;
	//			norAdd += m_pVtx[nCntpVtx + 1].nor;
	//			norAdd += m_pVtx[GetNumWidth() + 1].nor;
	//			norAdd += m_pVtx[GetNumWidth() + 2].nor;
	//			norAdd += m_pVtx[GetNumWidth() - 1].nor;
	//			norAdd += m_pVtx[GetNumWidth() - 2].nor;
	//			m_pVtx[nCntpVtx].nor = norAdd / 6;
	//		}
	//	}
	//}

	// ���_�ݒ�
	SetVtx();
}

//==========================================================
// �e�N�X�`�����ݒ�
//==========================================================
void CMeshField::SetTex(void)
{
	int nVertex = GetVertex();			// ���_�����擾
	int nNumWidth = GetNumWidth();		// ���������擾
	int nNumHeight = GetNumHeight();	// �����������擾

	// �e�N�X�`�����W(��������E��O�Ɍ������Ē��_����ݒ肷��
	for (int nCntpVtx = 0; nCntpVtx < nVertex; nCntpVtx++)
	{
		m_pVtx[nCntpVtx].tex = D3DXVECTOR2(m_tex.x + 1.0f * (nCntpVtx % (nNumWidth + 1)), m_tex.y + 1.0f * (nCntpVtx / (nNumWidth + 1)));
	}

	SetVtx();
}

//==========================================================
// ����
//==========================================================
CMeshField *CMeshField::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, 
	float fWidth, float fHeight, const char *pFileName, const int nWidth, const int nHeight, const int nPriority)
{
	CMeshField *pMeshField = NULL;	// ���b�V���t�B�[���h�̃|�C���^
	CTexture *pTexture = CManager::GetInstance()->GetTexture();	// �e�N�X�`���ւ̃|�C���^

	// �������̊m��
	pMeshField = new CMeshField;

	if (pMeshField != NULL)
	{// �m�ۂł����ꍇ

		// ������
		pMeshField->Init();

		// ���W�ݒ�
		pMeshField->SetPosition(pos);

		// �����ݒ�
		pMeshField->SetRotation(rot);

		// ���_����
		pMeshField->CObjectMesh::Create(nWidth, nHeight);

		// �T�C�Y�ݒ�
		pMeshField->SetSize(fWidth, fHeight);

		// �e�N�X�`���ݒ�
		pMeshField->BindTexture(pTexture->Regist(pFileName));
	}

	return pMeshField;
}


//==========================================================
// ���ݒ�
//==========================================================
void CMeshField::SetSize(float fWidth, float fHeight)
{
	// �T�C�Y�ݒ�
	m_fWidth = fWidth;
	m_fHeight = fHeight;

	// ���_���ݒ�
	SetVtxInfo();
}

//==========================================================
// �����蔻��
//==========================================================
float CMeshField::GetHeight(D3DXVECTOR3 pos, D3DXVECTOR3 &normal)
{
	float fHeight = 0.0f;	// ����
	D3DXVECTOR3 Pos0, Pos1, Pos2, Pos3;
	D3DXVECTOR3 vecToPos;	//����p�ϐ�
	D3DXVECTOR3 vec1, vec2;	//����p�ϐ�
	D3DXVECTOR3 nor0, nor3;
	float fRate, fRate2;	//����p�ϐ�
	float fMaxField;		//����p
	float fField, fField2;
	D3DXVECTOR3 nor;
	D3DXVECTOR3 MeshPos = GetPosition();
	int nNowWidth = -1;		// ����Ă��镝�ԍ�
	int nNowHeight = -1;	// ����Ă��鍂���ԍ�

	if (pos.x < MeshPos.x + m_pVtx[0].pos.x || pos.x > MeshPos.x + m_pVtx[GetVertex() - 1].pos.x ||
		pos.z > MeshPos.z + m_pVtx[0].pos.z || pos.z < MeshPos.z + m_pVtx[GetVertex() - 1].pos.z)
	{// �͈͊O
		return fHeight;
	}

	// �T�C�Y���擾
	vec1 = m_pVtx[GetVertex() - 1].pos - m_pVtx[0].pos;
	vec2 = pos - (GetPosition() + m_pVtx[0].pos);

	if (vec1.x == 0.0f || vec1.z == 0.0f)
	{// �����̏ꍇ
		return fHeight;
	}

	//x��z���W�̃��b�V�����̊��������߂�
	nor0 = D3DXVECTOR3(vec2.x / vec1.x, 0.0f, vec2.z / vec1.z);

	// ���̏ꏊ���擾
	nNowWidth = (int)((float)(GetNumWidth() * nor0.x));

	// �����̏ꏊ���擾
	nNowHeight = (int)((float)(GetNumHeight() * nor0.z));

	Pos0 = m_pVtx[nNowHeight * (GetNumWidth() + 1) + nNowWidth + GetNumWidth() + 1].pos;
	Pos1 = m_pVtx[nNowHeight * (GetNumWidth() + 1) + nNowWidth + 0].pos;
	Pos2 = m_pVtx[nNowHeight * (GetNumWidth() + 1) + nNowWidth + GetNumWidth() + 2].pos;
	Pos3 = m_pVtx[nNowHeight * (GetNumWidth() + 1) + nNowWidth + 1].pos;

	// Pos0����̃x�N�g�������߂�
	vec1 = Pos1 - Pos0;
	vec2 = Pos2 - Pos0;

	// ���݂̍��W�̃x�N�g�������߂�
	vecToPos = D3DXVECTOR3(pos.x - (MeshPos.x + Pos0.x),
		pos.y - (MeshPos.y + Pos0.y),
		pos.z - (MeshPos.z + Pos0.z));

	D3DXVec3Cross(&nor0, &vec1, &vec2);

	D3DXVec3Normalize(&nor0, &nor0);	// �x�N�g���𐳋K������

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
			fHeight = (-((pos.x - (MeshPos.x + Pos0.x)) * nor0.x) +
				-((pos.z - (MeshPos.z + Pos0.z)) * nor0.z)) / nor0.y + (MeshPos.y + Pos0.y);

			normal = nor0;

			return fHeight;
		}
	}

	// Pos3����̃x�N�g�������߂�
	vec1 = Pos2 - Pos3;
	vec2 = Pos1 - Pos3;

	D3DXVec3Cross(&nor3, &vec2, &vec1);

	D3DXVec3Normalize(&nor3, &nor3);	// �x�N�g���𐳋K������

	// ���݂̍��W�̃x�N�g�������߂�
	vecToPos = D3DXVECTOR3(pos.x - (MeshPos.x + Pos3.x),
		pos.y - (MeshPos.y + Pos3.y),
		pos.z - (MeshPos.z + Pos3.z));

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
			fHeight = (-((pos.x - (MeshPos.x + Pos3.x)) * nor3.x) +
				-((pos.z - (MeshPos.z + Pos3.z)) * nor3.z)) / nor3.y + (MeshPos.y + Pos3.y);

			normal = nor3;

			return fHeight;
		}
	}

	return pos.y;
}

//==========================================================
// �S�Ă̏��Ƃ̔���
//==========================================================
float CMeshField::GetHeight(D3DXVECTOR3 pos)
{
	CMeshField *pMesh = CMeshField::GetTop();	// �擪���擾
	float fHeight = 0.0f;	// ����
	bool bValue = false;
	D3DXVECTOR3 Pos0, Pos1, Pos2, Pos3;
	D3DXVECTOR3 vecToPos;	//����p�ϐ�
	D3DXVECTOR3 vec1, vec2;	//����p�ϐ�
	D3DXVECTOR3 nor0, nor3;
	float fRate, fRate2;	//����p�ϐ�
	float fMaxField;		//����p
	float fField, fField2;
	int nNowWidth = -1;		// ����Ă��镝�ԍ�
	int nNowHeight = -1;	// ����Ă��鍂���ԍ�

	while (pMesh != NULL)
	{// �g�p����Ă���ԌJ��Ԃ�
		CMeshField *pMeshNext = pMesh->GetNext();	// ����ێ�
		D3DXVECTOR3 MeshPos = pMesh->GetPosition();

		if (pos.x < MeshPos.x + pMesh->m_pVtx[0].pos.x || pos.x > MeshPos.x + pMesh->m_pVtx[pMesh->GetVertex() - 1].pos.x ||
			pos.z > MeshPos.z + pMesh->m_pVtx[0].pos.z || pos.z < MeshPos.z + pMesh->m_pVtx[pMesh->GetVertex() - 1].pos.z)
		{// �͈͊O
			pMesh = pMeshNext;	// ���Ɉړ�

			continue;
		}

		// �T�C�Y���擾
		vec1 = pMesh->m_pVtx[pMesh->GetVertex() - 1].pos - pMesh->m_pVtx[0].pos;
		vec2 = pos - (MeshPos + pMesh->m_pVtx[0].pos);

		if (vec1.x == 0.0f || vec1.z == 0.0f)
		{// �����̏ꍇ
			return fHeight;
		}

		//x��z���W�̃��b�V�����̊��������߂�
		nor0 = D3DXVECTOR3(vec2.x / vec1.x, 0.0f, vec2.z / vec1.z);

		// ���̏ꏊ���擾
		nNowWidth = (int)((float)(pMesh->GetNumWidth() * nor0.x));

		// �����̏ꏊ���擾
		nNowHeight = (int)((float)(pMesh->GetNumHeight() * nor0.z));

		if (nNowHeight * (pMesh->GetNumWidth() + 1) + nNowWidth + pMesh->GetNumWidth() + 2 >= pMesh->GetVertex())
		{
			pMesh = pMeshNext;	// ���Ɉړ�
			continue;
		}

		Pos0 = pMesh->m_pVtx[nNowHeight * (pMesh->GetNumWidth() + 1) + nNowWidth + pMesh->GetNumWidth() + 1].pos;
		Pos1 = pMesh->m_pVtx[nNowHeight * (pMesh->GetNumWidth() + 1) + nNowWidth + 0].pos;
		Pos2 = pMesh->m_pVtx[nNowHeight * (pMesh->GetNumWidth() + 1) + nNowWidth + pMesh->GetNumWidth() + 2].pos;
		Pos3 = pMesh->m_pVtx[nNowHeight * (pMesh->GetNumWidth() + 1) + nNowWidth + 1].pos;

		// Pos0����̃x�N�g�������߂�
		vec1 = Pos1 - Pos0;
		vec2 = Pos2 - Pos0;

		// ���݂̍��W�̃x�N�g�������߂�
		vecToPos = D3DXVECTOR3(pos.x - (MeshPos.x + Pos0.x),
			pos.y - (MeshPos.y + Pos0.y),
			pos.z - (MeshPos.z + Pos0.z));

		D3DXVec3Cross(&nor0, &vec1, &vec2);

		D3DXVec3Normalize(&nor0, &nor0);	// �x�N�g���𐳋K������

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
				float fValue = (-((pos.x - (MeshPos.x + Pos0.x)) * nor0.x) +
					-((pos.z - (MeshPos.z + Pos0.z)) * nor0.z)) / nor0.y + (MeshPos.y + Pos0.y);

				if (fValue > fHeight || bValue == false)
				{
					bValue = true;
					fHeight = fValue;
				}
			}
		}

		// Pos3����̃x�N�g�������߂�
		vec1 = Pos2 - Pos3;
		vec2 = Pos1 - Pos3;

		D3DXVec3Cross(&nor3, &vec2, &vec1);

		D3DXVec3Normalize(&nor3, &nor3);	// �x�N�g���𐳋K������

		// ���݂̍��W�̃x�N�g�������߂�
		vecToPos = D3DXVECTOR3(pos.x - (MeshPos.x + Pos3.x),
			pos.y - (MeshPos.y + Pos3.y),
			pos.z - (MeshPos.z + Pos3.z));

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

				float fValue = (-((pos.x - (MeshPos.x + Pos3.x)) * nor3.x) +
					-((pos.z - (MeshPos.z + Pos3.z)) * nor3.z)) / nor3.y + (MeshPos.y + Pos3.y);


				if (fValue > fHeight || bValue == false)
				{
					bValue = true;
					fHeight = fValue;
				}
			}
		}

		pMesh = pMeshNext;	// ���Ɉړ�
	}

	return fHeight;
}

//==========================================================
// ���b�V������
//==========================================================
void CMeshField::Edit(float *pLength, float *pSpeed)
{
	CPlayer *pPlayer = CManager::GetInstance()->GetScene()->GetPlayer();

	if (pPlayer == NULL)
	{
		return;
	}

	CInputKeyboard *pInputKey = CManager::GetInstance()->GetInputKeyboard();
	D3DXVECTOR3 pos =D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ���Z�b�g
	if (pInputKey->GetPress(DIK_F6) == true)
	{
		for (int nCntpVtx = 0; nCntpVtx < GetVertex(); nCntpVtx++)
		{
			m_pVtx[nCntpVtx].pos.y = 0.0f;
		}
	}

	// �͈͐ݒ�
	if (pInputKey->GetPress(DIK_5) == true)
	{
		*pLength += 1.0f;
	}
	else if (pInputKey->GetPress(DIK_6) == true)
	{
		*pLength -= 1.0f;
	}

	// ���x�ݒ�
	if (pInputKey->GetPress(DIK_Y) == true)
	{
		*pSpeed += 0.5f;
	}
	else if (pInputKey->GetPress(DIK_H) == true)
	{
		*pSpeed -= 0.5f;
	}

	// ���ݒ�
	if (pInputKey->GetPress(DIK_I) == true)
	{
		m_fWidth += 0.5f;
	}
	else if (pInputKey->GetPress(DIK_K) == true)
	{
		m_fWidth -= 0.5f;
	}

	// �����ݒ�
	if (pInputKey->GetPress(DIK_O) == true)
	{
		m_fHeight += 1.0f;
	}
	else if (pInputKey->GetPress(DIK_L) == true)
	{
		m_fHeight -= 1.0f;
	}

	// �͈͓����_����
	if (pInputKey->GetPress(DIK_U) == true)
	{
		for (int nCntpVtx = 0; nCntpVtx < GetVertex(); nCntpVtx++)
		{
			D3DXVECTOR3 VtxPos = m_pVtx[nCntpVtx].pos + GetPosition();

			float fLength =
				sqrtf((VtxPos.x - pos.x) * (VtxPos.x - pos.x)
					+ (VtxPos.z - pos.z) * (VtxPos.z - pos.z));

			if (fLength <= *pLength)
			{// �͈͓��̒��_
				m_pVtx[nCntpVtx].pos.y += *pSpeed;	// ���W���ړ�
			}
		}
	}
	else if (pInputKey->GetPress(DIK_J) == true)
	{
		for (int nCntpVtx = 0; nCntpVtx < GetVertex(); nCntpVtx++)
		{
			D3DXVECTOR3 VtxPos = m_pVtx[nCntpVtx].pos + GetPosition();

			float fLength =
				sqrtf((VtxPos.x - pos.x) * (VtxPos.x - pos.x)
					+ (VtxPos.z - pos.z) * (VtxPos.z - pos.z));

			if (fLength <= *pLength)
			{// �͈͓��̒��_
				m_pVtx[nCntpVtx].pos.y -= *pSpeed;	// ���W���ړ�
			}
		}
	}

	// ���_�ݒ�
	for (int nCntpVtx = 0; nCntpVtx < GetVertex(); nCntpVtx++)
	{
		//���_���W
		m_pVtx[nCntpVtx].pos.x = -(m_fWidth * GetNumWidth()) + (nCntpVtx % (GetNumWidth() + 1) * (m_fWidth * 2));
		m_pVtx[nCntpVtx].pos.z = (m_fHeight * GetNumHeight()) + ((nCntpVtx / (GetNumWidth() + 1) * (-m_fHeight * 2)));
	}

	// �@���x�N�g���̐ݒ�
	D3DXVECTOR3 nor, vec1, vec2;
	VERTEX_3D *aVtx[4];

	for (int nCntHeight = 0; nCntHeight < GetNumHeight(); nCntHeight++)
	{
		for (int nCntWidth = 0; nCntWidth < GetNumWidth(); nCntWidth++)
		{
			aVtx[0] = &m_pVtx[nCntHeight * (GetNumWidth() + 1) + nCntWidth + 0];
			aVtx[1] = &m_pVtx[nCntHeight * (GetNumWidth() + 1) + nCntWidth + 1];
			aVtx[2] = &m_pVtx[nCntHeight * (GetNumWidth() + 1) + nCntWidth + GetNumWidth() + 1];
			aVtx[3] = &m_pVtx[nCntHeight * (GetNumWidth() + 1) + nCntWidth + GetNumWidth() + 2];

			//Pos0����̃x�N�g�������߂�
			vec1 = aVtx[1]->pos - aVtx[0]->pos;
			vec2 = aVtx[2]->pos - aVtx[0]->pos;

			D3DXVec3Cross(&aVtx[0]->nor, &vec1, &vec2);

			D3DXVec3Normalize(&aVtx[0]->nor, &aVtx[0]->nor);	// �x�N�g���𐳋K������

			//Pos3����̃x�N�g�������߂�
			vec1 = aVtx[2]->pos - aVtx[3]->pos;
			vec2 = aVtx[1]->pos - aVtx[3]->pos;

			D3DXVec3Cross(&aVtx[3]->nor, &vec1, &vec2);

			D3DXVec3Normalize(&aVtx[3]->nor, &aVtx[3]->nor);	// �x�N�g���𐳋K������

			aVtx[1]->nor = (aVtx[0]->nor + aVtx[3]->nor) / 2;
			aVtx[2]->nor = (aVtx[0]->nor + aVtx[3]->nor) / 2;
		}
	}

	// �ۑ�
	if (pInputKey->GetPress(DIK_F7) == true)
	{
		FILE *pFile = fopen("data\\TXT\\mesh.txt", "w");
		D3DXVECTOR3 ROT;

		if (pFile == NULL)
		{//�t�@�C�����J���Ȃ������ꍇ
			return;
		}

		fprintf(pFile, "#==============================================================================\n"
			"# �N���f�[�^�t�@�C��[mesh.txt]\n"
			"# Author : IBUKI OKUSADA\n"
			"#==============================================================================\n\n");
		fprintf(pFile, "#----------------------------------------------\n"
			"# �������\n"
			"#----------------------------------------------\n\n");

		// ���_�̍����������o��
		for (int nCntpVtx = 0; nCntpVtx < GetVertex(); nCntpVtx++)
		{
			fprintf(pFile, "	HEIGHT = %f	[%d]\n", m_pVtx[nCntpVtx].pos.y, nCntpVtx);
		}

		//�t�@�C�������
		fclose(pFile);
	}

	// ���_���ݒ�
	SetVtx();

	// �f�o�b�O�\��
	CManager::GetInstance()->GetDebugProc()->Print("\n-------------------------------------------------------\n");
	CManager::GetInstance()->GetDebugProc()->Print("���b�V���t�B�[���h�N��������@ ---------------\n");
	CManager::GetInstance()->GetDebugProc()->Print("���Z�b�g�yF6�z: �ۑ��yF7�z: �I��͈́y %f �z: �͈͑���y 5, 6 �z\n", *pLength);
	CManager::GetInstance()->GetDebugProc()->Print(" ���_�㏸ �y U, J �z: ���x�ύX�y Y, H �z[ %f ] : ���_��-> �c[ %d ], ��[ %d ]\n", *pSpeed, GetNumHeight(), GetNumWidth());
	CManager::GetInstance()->GetDebugProc()->Print(" ��  �y I, K �z[ %f ]\n", m_fWidth);
	CManager::GetInstance()->GetDebugProc()->Print(" �����y T, H �z[ %f ]\n", m_fHeight);
}

//==========================================================
// �N���ǂݍ���
//==========================================================
void CMeshField::UpDownLoad(const char *pFileName)
{
	FILE *pFile;	// �t�@�C���ւ̃|�C���^
	int nVertex = 0;

	pFile = fopen(pFileName, "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		char aStr[256];

		//�J�n�����܂œǂݍ���
		while (1)
		{
			//�e�L�X�g�ǂݍ���
			int nResult = fscanf(pFile, "%s", &aStr[0]);

			if (strcmp(&aStr[0], "HEIGHT") == 0)
			{//�X�N���v�g�J�n�̕������m�F�ł����ꍇ
				fscanf(pFile, "%s", &aStr[0]);	// (=)�ǂݍ���
				fscanf(pFile, "%f", &m_pVtx[nVertex].pos.y);	// �����ǂݍ���
				nVertex++;

				if (nVertex >= GetVertex())
				{
					break;
				}
			}
			else if (nResult == EOF)
			{//�t�@�C���̍Ō�܂œǂݍ���ł��܂����ꍇ
				break;
			}
		}
		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		return;
	}

	// �@���x�N�g���̐ݒ�
	D3DXVECTOR3 nor, vec1, vec2;
	VERTEX_3D *aVtx[4];

	for (int nCntHeight = 0; nCntHeight < GetNumHeight(); nCntHeight++)
	{
		for (int nCntWidth = 0; nCntWidth < GetNumWidth(); nCntWidth++)
		{

			aVtx[0] = &m_pVtx[nCntHeight * (GetNumWidth() + 1) + nCntWidth + 0];
			aVtx[1] = &m_pVtx[nCntHeight * (GetNumWidth() + 1) + nCntWidth + 1];
			aVtx[2] = &m_pVtx[nCntHeight * (GetNumWidth() + 1) + nCntWidth + GetNumWidth() + 1];
			aVtx[3] = &m_pVtx[nCntHeight * (GetNumWidth() + 1) + nCntWidth + GetNumWidth() + 2];

			//Pos0����̃x�N�g�������߂�
			vec1 = aVtx[1]->pos - aVtx[0]->pos;
			vec2 = aVtx[2]->pos - aVtx[0]->pos;

			D3DXVec3Cross(&aVtx[0]->nor, &vec1, &vec2);

			D3DXVec3Normalize(&aVtx[0]->nor, &aVtx[0]->nor);	// �x�N�g���𐳋K������

			//Pos3����̃x�N�g�������߂�
			vec1 = aVtx[2]->pos - aVtx[3]->pos;
			vec2 = aVtx[1]->pos - aVtx[3]->pos;

			D3DXVec3Cross(&aVtx[3]->nor, &vec1, &vec2);

			D3DXVec3Normalize(&aVtx[3]->nor, &aVtx[3]->nor);	// �x�N�g���𐳋K������

			aVtx[1]->nor = (aVtx[0]->nor + aVtx[3]->nor) / 2;
			aVtx[2]->nor = (aVtx[0]->nor + aVtx[3]->nor) / 2;
		}
	}

	// ���_���ݒ�
	SetVtx();
}

//==========================================================
// ���ݒn�̃G���A�m�F
//==========================================================
CMeshField *CMeshField::GetArea(D3DXVECTOR3 pos)
{
	int nCnt = 0;
	// ���̕`��
	CMeshField *pMesh = CMeshField::GetTop();	// �擪���擾

	while (pMesh != NULL)
	{// �g�p����Ă���ԌJ��Ԃ�
		CMeshField *pMeshNext = pMesh->GetNext();	// ����ێ�
		D3DXVECTOR3 MeshPos = pMesh->GetPosition();

		if (pos.x > MeshPos.x + pMesh->m_pVtx[0].pos.x && pos.x < MeshPos.x + pMesh->m_pVtx[pMesh->GetVertex() - 1].pos.x &&
			pos.z < MeshPos.z + pMesh->m_pVtx[0].pos.z && pos.z > MeshPos.z + pMesh->m_pVtx[pMesh->GetVertex() - 1].pos.z)
		{// �͈͓�
			return pMesh;
		}

		pMesh = pMeshNext;	// ���Ɉړ�

		nCnt++;
	}
	return NULL;
}