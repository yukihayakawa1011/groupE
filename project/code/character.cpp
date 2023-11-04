//==========================================================
//
// �K�w�\���̏����S�� [character.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "character.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "texture.h"
#include "Xfile.h"
#include "model.h"
#include <string.h>
#include "motion.h"

//===================================================
// �R���X�g���N�^
//===================================================
CCharacter::CCharacter()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_ParentMtx = NULL;
	m_pMotion = NULL;
	m_ppParts = NULL;

	//���[���h�}�g���b�N�X�̏�����
	/*D3DXMatrixIdentity(&m_mtxWorld);*/
}

//===================================================
// �f�X�g���N�^
//===================================================
CCharacter::~CCharacter()
{

}

//===================================================
// ����������
//===================================================
HRESULT CCharacter::Init(void)
{
	// �t�@�C�����J��
	OpenFile("data\\TXT\\motion_sample.txt");

	return S_OK;
}

//===================================================
// ����������
//===================================================
HRESULT CCharacter::Init(const char* pFileName)
{
	// �t�@�C�����J��
	OpenFile(pFileName);

	return S_OK;
}

//===================================================
// �I������
//===================================================
void CCharacter::Uninit(void)
{
	// ���[�V�������̏I��
	if (m_pMotion != NULL)
	{
		m_pMotion->Uninit();
		delete m_pMotion;
		m_pMotion = NULL;
	}

	// �p�[�c�̏I��
	if (m_ppParts != NULL)
	{// �g�p���Ă����ꍇ
		for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
		{
			// �I������
			m_ppParts[nCnt]->Uninit();
			m_ppParts[nCnt] = NULL;	// �g�p���Ă��Ȃ���Ԃɂ���
		}

		delete[] m_ppParts;	// �|�C���^�̊J��
		m_ppParts = NULL;	// �g�p���Ă��Ȃ���Ԃɂ���
	}
}

//===================================================
// �X�V����
//===================================================
void CCharacter::Update(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�ւ̃|�C���^���擾
	CTexture *pTexture = CManager::GetInstance()->GetTexture();	// �e�N�X�`���ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	CXFile *pModelFile = CManager::GetInstance()->GetModelFile();	// X�t�@�C�����̃|�C���^
	D3DXMATRIX mtxParent;			// �e�̃}�g���b�N�X���

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_ParentMtx != NULL)
	{// �o���Ă���ꍇ
		mtxParent = *m_ParentMtx;

		//�p�[�c�̃}�g���b�N�X�Ɛe�̃}�g���b�N�X���������킹��
		D3DXMatrixMultiply(&m_mtxWorld,
			&m_mtxWorld, &mtxParent);
	}

	if (m_pMotion != NULL)
	{// ���[�V�������g�p���Ă���ꍇ
		m_pMotion->Update();
	}
}

//===================================================
// �`�揈��
//===================================================
void CCharacter::Draw(void)
{

}

//==========================================================
// �p�[�c�̏��e�L�X�g�ǂݍ���
//==========================================================
void CCharacter::OpenFile(const char *pFileData)
{
	FILE *pFile;

	pFile = fopen(pFileData, "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		char aStr[256];

		//�J�n�����܂œǂݍ���
		while (1)
		{
			//�e�L�X�g�ǂݍ���
			int nResult = fscanf(pFile, "%s", &aStr[0]);

			if (strcmp(&aStr[0], "SCRIPT") == 0)
			{//�X�N���v�g�J�n�̕������m�F�ł����ꍇ

				// �ǂݍ��݊J�n
				LoadFile(pFile);
				break;
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
}

//==========================================================
// �p�[�c�e�L�X�g���ǂݍ���
//==========================================================
void CCharacter::LoadFile(FILE *pFile)
{
	char aStr[256] = "";
	char aStrOld[256];
	int nMotion = 0;	//�ǂݍ��݃��[�V�����ԍ�

	//���ǂݍ��݊J�n
	while (1)
	{
		strcpy(&aStrOld[0], &aStr[0]);
		int nResult = fscanf(pFile, "%s", &aStr[0]);

		if (strcmp(&aStr[0], "NUM_MODEL") == 0)
		{//�g�p���郂�f�����̏ꍇ
			fscanf(pFile, "%s", &aStr[0]); //=
			fscanf(pFile, "%d", &m_nNumParts); //�p�[�c���擾

			m_ppParts = new CModel*[m_nNumParts];	// �p�[�c�����m��

			for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
			{
				m_ppParts[nCnt] = NULL;
			}

			//�t�@�C�����擾
			LoadXFile(pFile);
		}
		else if (strcmp(&aStr[0], "CHARACTERSET") == 0)
		{//�L�����N�^�[���̏ꍇ
			LoadSetData(pFile);
		}
		else if (strcmp(&aStr[0], "MOTIONSET") == 0)
		{//���[�V�������̏ꍇ

			if (m_pMotion == NULL)
			{// ���[�V�������m�ۂ���Ă��Ȃ��ꍇ
				m_pMotion = new CMotion;
				m_pMotion->SetModel(m_ppParts, m_nNumParts);
			}

			if (m_pMotion != NULL)
			{// �g�p����Ă���ꍇ
				m_pMotion->LoadMotionData(pFile);
			}
		}
		else if (strcmp(&aStr[0], "END_SCRIPT") == 0)
		{//�X�N���v�g�I���̕������m�F�ł����ꍇ
			break;
		}
		else if (nResult == EOF)
		{//�t�@�C���̍Ō�܂œǂݍ���ł��܂����ꍇ
			break;
		}
	}
}

//==========================================================
// �p�[�c���f���t�@�C�����ǂݍ���
//==========================================================
void CCharacter::LoadXFile(FILE *pFile)
{
	int nParts = 0;		//���݂̃p�[�c�ԍ�
	char aStr[128] = {};	//�z�u�������i�[�p
	CXFile *pModelFile = CManager::GetInstance()->GetModelFile();

	while (1)
	{
		if (nParts >= m_nNumParts)
		{//�p�[�c�����܂œ��B�����ꍇ
			break;
		}
		else
		{//���B���Ă��Ȃ��ꍇ
			//�e�L�X�g�ǂݍ���
			int nResult = fscanf(pFile, "%s", &aStr[0]);

			if (strcmp(&aStr[0], "MODEL_FILENAME") == 0)
			{//���f�����ǂݍ���
				fscanf(pFile, "%s", &aStr[0]); //=
				fscanf(pFile, "%s", &aStr[0]); //�t�@�C����

				// ���f���̃C���X�^���X�𐶐����ăt�@�C����ǂݍ���
				m_ppParts[nParts] = CModel::Create(&aStr[0]);

				nParts++;
			}
			if (strcmp(&aStr[0], "END_SCRIPT") == 0)
			{//�X�N���v�g�I���̕������m�F�ł����ꍇ
				break;
			}
			else if (nResult == EOF)
			{//�t�@�C���̍Ō�܂œǂݍ���ł��܂����ꍇ
				break;
			}
		}
	}
}

//==========================================================
// �p�[�c�̏����ݒu���ǂݍ���
//==========================================================
void CCharacter::LoadSetData(FILE *pFile)
{
	char aStr[128] = {};	//�z�u�������i�[�p
	int nCntParts = 0;
	while (1)
	{
		//�e�L�X�g�ǂݍ���
		int nResult = fscanf(pFile, "%s", &aStr[0]);

		if (strcmp(&aStr[0], "PARTSSET") == 0)
		{//�p�[�c���m�F�����������ꍇ

			CMotion::KEY Key = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };	// ���

			while (1)
			{
				//�ǂݍ���
				fscanf(pFile, "%s", &aStr[0]);

				if (nCntParts >= m_nNumParts)
				{//�p�[�c�����ɓ��B�����ꍇ
					break;
				}
				if (strcmp(&aStr[0], "POS") == 0)
				{//���W
					fscanf(pFile, "%s", &aStr[0]);	//(=)�ǂݍ���
					fscanf(pFile, "%f", &Key.fPosX);	//x���W�ǂݍ���
					fscanf(pFile, "%f", &Key.fPosY);	//y���W�ǂݍ���
					fscanf(pFile, "%f", &Key.fPosZ);	//z���W�ǂݍ���

					// ��������ݒ�
					if (m_ppParts[nCntParts] != NULL)
					{// �g�p����Ă���ꍇ
						m_ppParts[nCntParts]->SetPosition(D3DXVECTOR3(Key.fPosX, Key.fPosY, Key.fPosZ));
					}
				}
				else if (strcmp(&aStr[0], "ROT") == 0)
				{//����
					fscanf(pFile, "%s", &aStr[0]);	//(=)�ǂݍ���
					fscanf(pFile, "%f", &Key.fRotX);	//x���W�ǂݍ���
					fscanf(pFile, "%f", &Key.fRotY);	//y���W�ǂݍ���
					fscanf(pFile, "%f", &Key.fRotZ);	//z���W�ǂݍ���

					// ��������ݒ�
					if (m_ppParts[nCntParts] != NULL)
					{// �g�p����Ă���ꍇ
						m_ppParts[nCntParts]->SetRotation(D3DXVECTOR3(Key.fRotX, Key.fRotY, Key.fRotZ));
					}
				}
				else if (strcmp(&aStr[0], "INDEX") == 0)
				{//�p�[�c�ԍ�
					int nIdx = 0;
					fscanf(pFile, "%s", &aStr[0]);	//(=)�ǂݍ���
					fscanf(pFile, "%d", &nIdx);	//�ǂݍ���
				}
				else if (strcmp(&aStr[0], "PARENT") == 0)
				{//�e�ԍ�
					int nIdxParent = 0;
					fscanf(pFile, "%s", &aStr[0]);		//(=)�ǂݍ���
					fscanf(pFile, "%d", &nIdxParent);	//�ǂݍ���

					if (nIdxParent >= 0 && nIdxParent <= m_nNumParts)
					{// �p�[�c�����͈͓̔��̏ꍇ
						if (m_ppParts[nIdxParent] != NULL && m_ppParts[nCntParts] != NULL)
						{// �e���������g���g�p���Ă���ꍇ
							m_ppParts[nCntParts]->SetParent(m_ppParts[nIdxParent]->GetMtxWorld());
						}
					}
					else
					{
						m_ppParts[nCntParts]->SetParent(&m_mtxWorld);
					}
				}
				else if (strcmp(&aStr[0], "END_PARTSSET") == 0)
				{//�p�[�c���I�������m�F�ł����ꍇ
					nCntParts++;
				}
			}


		}

		if (strcmp(&aStr[0], "END_CHARACTERSET") == 0)
		{//�L�����N�^�[���I�������m�F�ł����ꍇ
			return;	//�Ȃɂ������Ԃ�
		}
	}
}

//==========================================================
// ����
//==========================================================
CCharacter *CCharacter::Create(const char* pFileName)
{
	CCharacter *pCharacter = NULL;

	// �L�����N�^�[�̐���
	pCharacter = new CCharacter;

	if (pCharacter != NULL)
	{// �����ł����ꍇ
		// ����������
		pCharacter->Init(pFileName);
	}
	else
	{// �����Ɏ��s�����ꍇ
		return NULL;
	}

	return pCharacter;
}

//==========================================================
// ����(���W�����w��)
//==========================================================
CCharacter *CCharacter::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pFileName)
{
	CCharacter *pCharacter = NULL;

	// �I�u�W�F�N�g2D�̐���
	pCharacter = new CCharacter;

	if (pCharacter != NULL)
	{// �����ł����ꍇ
		// ����������
		pCharacter->Init(pFileName);

		// ���W�ݒ�
		pCharacter->SetPosition(pos);

		// �����ݒ�
		pCharacter->SetRotation(rot);
	}
	else
	{// �����Ɏ��s�����ꍇ
		return NULL;
	}

	return pCharacter;
}

//==========================================================
// �����ݒ�
//==========================================================
void CCharacter::SetRotation(const D3DXVECTOR3 rot)
{
	m_rot = rot;

	if (m_rot.z < -D3DX_PI)
	{// z���W�p�x���E
		m_rot.z += D3DX_PI * 2;
	}
	else if (m_rot.z > D3DX_PI)
	{// z���W�p�x���E
		m_rot.z += -D3DX_PI * 2;
	}

	if (m_rot.x < -D3DX_PI)
	{// x���W�p�x���E
		m_rot.x += D3DX_PI * 2;
	}
	else if (m_rot.x > D3DX_PI)
	{// x���W�p�x���E
		m_rot.x += -D3DX_PI * 2;
	}

	if (m_rot.y < -D3DX_PI)
	{// x���W�p�x���E
		m_rot.y += D3DX_PI * 2;
	}
	else if (m_rot.y > D3DX_PI)
	{// x���W�p�x���E
		m_rot.y += -D3DX_PI * 2;
	}
}

//==========================================================
// �p�[�c���擾
//==========================================================
CModel *CCharacter::GetParts(int nIdx)
{
	if (nIdx >= 0 && nIdx < m_nNumParts)
	{// �͈͓�
		return m_ppParts[nIdx];
	}
	return NULL;
}

//==========================================================
// �`��ݒ�
//==========================================================
void CCharacter::SetDraw(bool bDraw)
{
	if (m_ppParts != NULL)
	{// �g�p���Ă����ꍇ
		for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
		{
			// �I������
			m_ppParts[nCnt]->SetDraw(bDraw);
		}
	}
}

//==========================================================
// �e�ݒ�
//==========================================================
void CCharacter::SetShadow(bool bShadow)
{
	if (m_ppParts != NULL)
	{// �g�p���Ă����ꍇ
		for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
		{
			// �I������
			m_ppParts[nCnt]->SetShadow(bShadow);
			m_ppParts[nCnt]->SetCharaParent(&m_mtxWorld);
		}
	}
}

void CCharacter::SetCharaMtx(void)
{
	if (m_ppParts != NULL)
	{// �g�p���Ă����ꍇ
		for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
		{
			// �I������
			m_ppParts[nCnt]->SetCharaParent(&m_mtxWorld);
		}
	}
}