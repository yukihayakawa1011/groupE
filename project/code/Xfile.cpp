//==========================================================
//
// X�t�@�C���Ǘ� [modelfile.h]
// Author : Ibuki Okusada
//
//==========================================================
#include "Xfile.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include <string.h>

// �ÓI�����o�ϐ��錾
int CXFile::m_nNumAll = 0;	// �ǂݍ��ݑ���

//==========================================================
// �R���X�g���N�^
//==========================================================
CXFile::CXFile()
{
	for(int nCnt = 0; nCnt < MAX_FILE; nCnt++)
	{
		m_apModelFileData[nCnt] = NULL;
	}
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CXFile::~CXFile()
{

}

//==========================================================
// �ǂݍ��݊m�F
//==========================================================
int CXFile::Regist(const char *pFileName)
{
	int nIdx = -1;
	// �ǂݍ��܂�Ă��邩�m�F
	for (int nCnt = 0; nCnt < MAX_FILE; nCnt++)
	{
		if (m_apModelFileData[nCnt] == NULL)
		{// �g���Ă��Ȃ��ꍇ
			continue;
		}

		// �����t�@�C�����m�F
		if (strstr(pFileName, &m_apModelFileData[nCnt]->aFileName[0]) != NULL)
		{// �������̂����݂��Ă���ꍇ
			nIdx = nCnt;
			return nIdx;	// �t�@�C������Ԃ�
		}
	}

	// �Ō�܂ő��݂��Ă��Ȃ��ꍇ
	for (int nCnt = 0; nCnt < MAX_FILE; nCnt++)
	{
		if (m_apModelFileData[nCnt] == NULL)
		{// �g���Ă��Ȃ��ꍇ
			m_apModelFileData[nCnt] = new FileInfo;	// �������̊m��

			if (m_apModelFileData[nCnt] != NULL)
			{// ���������m�ۂł����ꍇ

				// �������̃N���A
				memset(m_apModelFileData[nCnt], NULL, sizeof(FileInfo));

				// �T�C�Y�̍Œ�l����
				m_apModelFileData[nCnt]->filedata.vtxMax = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);
				m_apModelFileData[nCnt]->filedata.vtxMin = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);

				// �t�@�C�����̎擾
				strcpy(&m_apModelFileData[nCnt]->aFileName[0], pFileName);

				// X�t�@�C���̓ǂݍ���
				if (SUCCEEDED(FileLoad(nCnt)))
				{// ���������ꍇ

					m_nNumAll++;	// �ǂݍ��ݐ��J�E���g�A�b�v
					nIdx = nCnt;
					return nIdx;	// �t�@�C������Ԃ�
				}
				break;
			}
		}
	}

	return NULL;
}

//==========================================================
// X�t�@�C���ǂݍ���
//==========================================================
HRESULT CXFile::FileLoad(int nIdx)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();;		//�f�o�C�X�ւ̃|�C���^
	CTexture *pTexture = CManager::GetInstance()->GetTexture();	// �e�N�X�`���ւ̃|�C���^
	D3DXMATERIAL *pMat;	//�}�e���A���f�[�^�ւ̃|�C���^
	int nNumVtx;		//���_��
	DWORD dwSizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		//���_�o�b�t�@�̃|�C���^

	//X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(&m_apModelFileData[nIdx]->aFileName[0],
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_apModelFileData[nIdx]->filedata.pBuffMat,
		NULL,
		&m_apModelFileData[nIdx]->filedata.dwNumMat,
		&m_apModelFileData[nIdx]->filedata.pMesh)))
	{// �ǂݍ��݂Ɏ��s�����ꍇ
		return E_FAIL;	// ���s��Ԃ�
	}

	// �e�N�X�`���|�C���^�̊m��
	if ((int)m_apModelFileData[nIdx]->filedata.dwNumMat > 0)
	{// �}�e���A�����g�p���Ă���ꍇ
		if (m_apModelFileData[nIdx]->filedata.pIdexTexture == NULL)
		{// �e�N�X�`�����g�p����Ă��Ȃ��ꍇ
			// �}�e���A�������m��
			m_apModelFileData[nIdx]->filedata.pIdexTexture = new int[(int)m_apModelFileData[nIdx]->filedata.dwNumMat];
		}
	}

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_apModelFileData[nIdx]->filedata.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_apModelFileData[nIdx]->filedata.dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//�e�N�X�`���t�@�C�������݂��Ă���
			//�e�N�X�`���̓ǂݍ���
			m_apModelFileData[nIdx]->filedata.pIdexTexture[nCntMat] = pTexture->Regist(pMat[nCntMat].pTextureFilename);
		}
		else
		{
			m_apModelFileData[nIdx]->filedata.pIdexTexture[nCntMat] = -1;
		}
	}

	//���_�����擾
	nNumVtx = m_apModelFileData[nIdx]->filedata.pMesh->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	dwSizeFVF = D3DXGetFVFVertexSize(m_apModelFileData[nIdx]->filedata.pMesh->GetFVF());

	//���_�o�b�t�@�����b�N
	m_apModelFileData[nIdx]->filedata.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W�̑��

		// X���W
		if (vtx.x < m_apModelFileData[nIdx]->filedata.vtxMin.x)
		{//�ŏ��l�����l���������ꍇ
			m_apModelFileData[nIdx]->filedata.vtxMin.x = vtx.x;
		}
		else if (vtx.x > m_apModelFileData[nIdx]->filedata.vtxMax.x)
		{//�ő�l�����l���傫���ꍇ
			m_apModelFileData[nIdx]->filedata.vtxMax.x = vtx.x;
		}

		// Z���W
		if (vtx.z < m_apModelFileData[nIdx]->filedata.vtxMin.z)
		{//�ŏ��l�����l���������ꍇ
			m_apModelFileData[nIdx]->filedata.vtxMin.z = vtx.z;
		}
		else if (vtx.z > m_apModelFileData[nIdx]->filedata.vtxMax.z)
		{//�ő�l�����l���傫���ꍇ
			m_apModelFileData[nIdx]->filedata.vtxMax.z = vtx.z;
		}

		// Y���W
		if (vtx.y < m_apModelFileData[nIdx]->filedata.vtxMin.y)
		{//�ŏ��l�����l���������ꍇ
			m_apModelFileData[nIdx]->filedata.vtxMin.y = vtx.y;
		}
		else if (vtx.y > m_apModelFileData[nIdx]->filedata.vtxMax.y)
		{//�ő�l�����l���傫���ꍇ
			m_apModelFileData[nIdx]->filedata.vtxMax.y = vtx.y;
		}

		pVtxBuff += dwSizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	m_apModelFileData[nIdx]->filedata.pMesh->UnlockVertexBuffer();

	return S_OK;	// ������Ԃ�
}

//==========================================================
// X�t�@�C�����p��
//==========================================================
void CXFile::Unload(void)
{
	// �ǂݍ��܂�Ă��邩�m�F
	for (int nCnt = 0; nCnt < MAX_FILE; nCnt++)
	{
		if (m_apModelFileData[nCnt] == NULL)
		{// �g�p����Ă��Ȃ��ꍇ
			continue;	// ��蒼��
		}
		
		// �l���N���A����
		memset(m_apModelFileData[nCnt]->aFileName, '\0', sizeof(m_apModelFileData[nCnt]->aFileName));

		//���b�V���̔p��
		if (m_apModelFileData[nCnt]->filedata.pMesh != NULL)
		{
			m_apModelFileData[nCnt]->filedata.pMesh->Release();
			m_apModelFileData[nCnt]->filedata.pMesh = NULL;
		}

		//�}�e���A���̔p��
		if (m_apModelFileData[nCnt]->filedata.pBuffMat != NULL)
		{
			m_apModelFileData[nCnt]->filedata.pBuffMat->Release();
			m_apModelFileData[nCnt]->filedata.pBuffMat = NULL;
		}

		// �e�N�X�`���ԍ��̔p��
		delete[] m_apModelFileData[nCnt]->filedata.pIdexTexture;	// �e�N�X�`���|�C���^�̊J��

		delete m_apModelFileData[nCnt];	// �������̊J��
		m_apModelFileData[nCnt] = NULL;	// �g�p���Ă��Ȃ���Ԃɂ���
		m_nNumAll--;	// �ǂݍ��ݐ��J�E���g�_�E��
	}
}

//==========================================================
// X�t�@�C�����p��
//==========================================================
CXFile::FileData *CXFile::SetAddress(int nIdx)
{
	if (nIdx > m_nNumAll || nIdx < 0)
	{// �ǂݍ��ݔ͈͊O�̏ꍇ
		return NULL;
	}

	return &m_apModelFileData[nIdx]->filedata;
}