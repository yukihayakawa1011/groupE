//==========================================================
//
// ���b�V���t�B�[���h�̏��� [meshfield.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "meshwall.h"
#include "texture.h"
#include "manager.h"

// �}�N����`
#define TEXTUREFILE_DATA	"data\\TEXTURE\\welltile.png"		//�e�N�X�`���f�[�^

// �ÓI�����o�ϐ��錾
CMeshWall *CMeshWall::m_pTop = NULL;	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
CMeshWall *CMeshWall::m_pCur = NULL;	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^

//==========================================================
// �R���X�g���N�^
//==========================================================
CMeshWall::CMeshWall()
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
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CMeshWall::~CMeshWall()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CMeshWall::Init(void)
{
	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CMeshWall::Uninit(void)
{
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

	//���_�o�b�t�@�̔p��
	CObjectMesh::Uninit();
}

//==========================================================
// �X�V����
//==========================================================
void CMeshWall::Update(void)
{

}

//==========================================================
// �`�揈��
//==========================================================
void CMeshWall::Draw(void)
{
	// �`��
	CObjectMesh::Draw();
}

//==========================================================
// ���_���ݒ�
//==========================================================
void CMeshWall::SetVtxInfo(void)
{
	int nVertex = GetVertex();			// ���_�����擾
	int nNumWidth = GetNumWidth();		// ���������擾
	int nNumHeight = GetNumHeight();	// �����������擾

	//���_���W�̐ݒ�(��������E��O�Ɍ������Ē��_����ݒ肷��
	for (int nCntpVtx = 0; nCntpVtx < nVertex; nCntpVtx++)
	{
		//���_���W
		m_pVtx[nCntpVtx].pos.x = -(m_fWidth * nNumWidth) + (nCntpVtx % (nNumWidth + 1) * (m_fWidth * 2));
		m_pVtx[nCntpVtx].pos.y = ((m_fHeight * 2) * nNumHeight) + ((nCntpVtx / (nNumWidth + 1) * (-m_fHeight * 2)));
		m_pVtx[nCntpVtx].pos.z = 0.0f;

		//�@��
		m_pVtx[nCntpVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//�F
		m_pVtx[nCntpVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		m_pVtx[nCntpVtx].tex = D3DXVECTOR2(1.0f * (nCntpVtx % (nNumWidth + 1)), 1.0f * (nCntpVtx / (nNumWidth + 1)));
	}

	// ���_�ݒ�
	SetVtx();
}

//==========================================================
// ����
//==========================================================
CMeshWall *CMeshWall::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, float fWidth, float fHeight,
	const char *pFileName, const int nWidth, const int nHeight, const int nPriority )
{
	CMeshWall *pMeshWall = NULL;	// ���b�V���t�B�[���h�̃|�C���^
	CTexture *pTexture = CManager::GetInstance()->GetTexture();	// �e�N�X�`���ւ̃|�C���^

	// �������̊m��
	pMeshWall = new CMeshWall;

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

		// �T�C�Y�ݒ�
		pMeshWall->SetSize(fWidth, fHeight);

		// �e�N�X�`���ݒ�
		pMeshWall->BindTexture(pTexture->Regist(pFileName));
	}

	return pMeshWall;
}

//==========================================================
// ���ݒ�
//==========================================================
void CMeshWall::SetSize(float fWidth, float fHeight)
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
void CMeshWall::Collision(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld)
{
	CMeshWall *pObj = m_pTop;

	while (pObj != NULL)
	{
		CMeshWall *pObjNext = pObj->m_pNext;

		if (pObj->GetHeight() <= 30.0f && pObj->GetNumHeight() == 1)
		{
			pObj = pObjNext;
			continue;
		}

		if (pObj->GetRotation().y == 0.0f * D3DX_PI || pObj->GetRotation().y == 0.0f * -D3DX_PI)
		{//�ǂ����ʂ������Ă���ꍇ(Z�����}�C�i�X�̕������Ă���)
			if (
				pos.y <= pObj->GetPosition().y + pObj->GetHeight() * 2 * pObj->GetNumHeight() &&
				pos.x >= pObj->GetPosition().x - pObj->GetWidth() * pObj->GetNumWidth() &&
				pos.x <= pObj->GetPosition().x + pObj->GetWidth() * pObj->GetNumWidth() &&
				posOld.z <= pObj->GetPosition().z &&
				pos.z > pObj->GetPosition().z)
			{//�������Ă���ꍇ
				pos.z = pObj->GetPosition().z;
			}
		}
		if (pObj->GetRotation().y == 0.5f * D3DX_PI)
		{//�ǂ��E�������Ă���ꍇ(X�����v���X�̕������Ă���)

			if (
				pos.y < pObj->GetPosition().y + pObj->GetHeight() * 2 * pObj->GetNumHeight() &&
				pos.z >= pObj->GetPosition().z - pObj->GetWidth() * pObj->GetNumWidth() &&
				pos.z <= pObj->GetPosition().z + pObj->GetWidth() * pObj->GetNumWidth() &&
				posOld.x <= pObj->GetPosition().x &&
				pos.x > pObj->GetPosition().x)
			{//�������Ă���ꍇ
				pos.x = pObj->GetPosition().x;
			}
		}
		if (pObj->GetRotation().y == -0.5f * D3DX_PI)
		{//�ǂ����������Ă���ꍇ(X�����}�C�i�X�̕������Ă���)
			if (
				pos.y < pObj->GetPosition().y + pObj->GetHeight() * 2 * pObj->GetNumHeight() &&
				pos.z >= pObj->GetPosition().z - pObj->GetWidth() * pObj->GetNumWidth() &&
				pos.z <= pObj->GetPosition().z + pObj->GetWidth() * pObj->GetNumWidth() &&
				posOld.x >= pObj->GetPosition().x &&
				pos.x < pObj->GetPosition().x)
			{//�������Ă���ꍇ
				pos.x = pObj->GetPosition().x;
			}

		}
		if (pObj->GetRotation().y == 1.0f * D3DX_PI || pObj->GetRotation().y == 1.0f * -D3DX_PI)
		{//�ǂ����������Ă���ꍇ(Z�����v���X�̕������Ă���)
			if (
				pos.y < pObj->GetPosition().y + pObj->GetHeight() * 2 * pObj->GetNumHeight()  &&
				pos.x >= pObj->GetPosition().x - pObj->GetWidth() * pObj->GetNumWidth() &&
				pos.x <= pObj->GetPosition().x + pObj->GetWidth() * pObj->GetNumWidth() &&
				posOld.z >= pObj->GetPosition().z &&
				pos.z < pObj->GetPosition().z)
			{//�������Ă���ꍇ
				pos.z = pObj->GetPosition().z;
			}
		}

		pObj = pObjNext;
	}
}