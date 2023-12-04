//==========================================================
//
//�t�@�C���A�f�[�^�ǂݍ��ݏ���
//Author Ibuki Okusada
//
//==========================================================
#include "fileload.h"
#include <string.h>
#include "texture.h"
#include "meshfield.h"
#include "meshwall.h"
#include "manager.h"
#include "texture.h"
#include "Xfile.h"
#include "objectX.h"
#include "game.h"
#include "item.h"
#include "title_enter.h"

//==========================================================
// �}�N����`
//==========================================================
//�m�F����
#define START_SCRIPTTXT	"SCRIPT"			// �X�N���v�g�J�n�m�F����
#define END_SCRIPTTXT	"END_SCRIPT"			// �X�N���v�g�I���m�F����
#define TEXTURENUM_TXT	"NUM_TEXTURE"			// �e�N�X�`���g�p�����m�F����
#define TEXTUREFILENAME_TXT	"TEXTURE_FILENAME"	// �e�N�X�`���t�@�C�����m�F����
#define MODELNUM_TXT	"NUM_MODEL"			// ���f���g�p�m�F����
#define MODELFILENAME_TXT	"MODEL_FILENAME"	// ���f���t�@�C�����m�F����
#define FIELDSET_TXT	"FIELDSET"			// ���b�V���t�B�[���h�ݒu�m�F����
#define ENDFIELDSET_TXT	"END_FIELDSET"	// ���ǂݍ��ݏI��
#define WALLSET_TXT		"WALLSET"		// ���b�V���E�H�[���ݒu�m�F����
#define ENDWALLSET_TXT	"END_WALLSET"			// �Ǔǂݍ��ݏI��
#define MODELSET_TXT	"MODELSET"			// ���f���z�u�m�F����
#define ENDMODELSET_TXT	"END_MODELSET"	// ���f���ǂݍ��ݏI��
#define ITEMSET_TXT		"ITEMSET"		// �A�C�e���z�u�m�F����
#define ENDITEMSET_TXT	"END_ITEMSET"			// �A�C�e���ǂݍ��ݏI��
#define LOAD_POS		"POS"				// ���W
#define LOAD_ROT		"ROT"				// ����
#define LOAD_TEXTYPE	"TEXTYPE"			// �e�N�X�`���ԍ�
#define LOAD_MODELTYPE	"TYPE"				// ���f���ԍ�
#define LOAD_BLOCK		"BLOCK"			// ����
#define LOAD_SIZE		"SIZE"				// �T�C�Y
#define LOAD_SHADOW		"SHADOW"			// �e
#define LOAD_UPDOWN		"UPDOWN"			// �N��
#define LOAD_VTXMAX		"VTXMAX"			// �����蔻��ő�
#define LOAD_VTXMIN		"VTXMIN"			// �����蔻��ŏ�

//==========================================================
// �R���X�g���N�^
//==========================================================
CFileLoad::CFileLoad()
{
	m_nModelNumAll = 0;
	m_nTexNumAll = 0;
	m_pTextureFile = NULL;
	m_pModelFile = NULL;
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CFileLoad::~CFileLoad()
{

}

//==========================================================
// ����������
//==========================================================
void CFileLoad::Init(void)
{

}

//==========================================================
// �I������
//==========================================================
void CFileLoad::Uninit(void)
{
	if (m_pTextureFile != nullptr)
	{
		delete m_pTextureFile;
		m_pTextureFile = nullptr;
	}

	if (m_pModelFile != nullptr)
	{
		delete m_pModelFile;
		m_pModelFile = nullptr;
	}
}

//==========================================================
// �t�@�C�����J��
//==========================================================
void CFileLoad::OpenFile(const char *pFileName)
{
	FILE *pFile;	// �t�@�C���ւ̃|�C���^

	pFile = fopen(pFileName, "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		char aStr[256];

		//�J�n�����܂œǂݍ���
		while (1)
		{
			//�e�L�X�g�ǂݍ���
			int nResult = fscanf(pFile, "%s", &aStr[0]);

			if (strcmp(&aStr[0], START_SCRIPTTXT) == 0)
			{//�X�N���v�g�J�n�̕������m�F�ł����ꍇ
				//�e�f�[�^�̓ǂݍ��݊J�n
				LoadFileData(pFile);

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
//�t�@�C�����e�ǂݍ��ݏ���
//==========================================================
void CFileLoad::LoadFileData(FILE *pFile)
{
	char aStr[256];	//�]���ȕ��͓ǂݍ��ݗp
	int nModelIdx = -1;	// �����蔻��m�F�ꏊ

	while (1)
	{
		int nResult = fscanf(pFile, "%s", &aStr[0]);

		//�ǂݍ��ݓ��e�m�F
		if (strcmp(&aStr[0], TEXTURENUM_TXT) == 0)
		{//�g�p����e�N�X�`�������̏ꍇ
			LoadTexNum(pFile);
		}
		else if (strcmp(&aStr[0], MODELNUM_TXT) == 0)
		{//�g�p���郂�f�����̏ꍇ
			LoadModelNum(pFile);
		}

		//�t�@�C�����m�F
		if (strcmp(&aStr[0], TEXTUREFILENAME_TXT) == 0)
		{//�e�N�X�`���t�@�C�����̏ꍇ
			LoadTexFile(pFile);
		}
		else if (strcmp(&aStr[0], MODELFILENAME_TXT) == 0)
		{//���f���t�@�C�����̏ꍇ
			LoadModelFile(pFile);
			nModelIdx++;
		}

		// �T�C�Y�m�F
		if (strcmp(&aStr[0], LOAD_VTXMAX) == 0)
		{//�e�N�X�`���t�@�C�����̏ꍇ
			LoadVtxMaxData(pFile, nModelIdx);
		}
		else if (strcmp(&aStr[0], LOAD_VTXMIN) == 0)
		{//���f���t�@�C�����̏ꍇ
			LoadVtxMinData(pFile, nModelIdx);
		}

		//�z�u���m�F
		if (strcmp(&aStr[0], WALLSET_TXT) == 0)
		{//�ǔz�u�̏ꍇ
			LoadMeshWallData(pFile);
		}
		else if (strcmp(&aStr[0], FIELDSET_TXT) == 0)
		{//���z�u�̏ꍇ
			LoadMeshFieldData(pFile);
		}
		else if (strcmp(&aStr[0], MODELSET_TXT) == 0)
		{//���f���z�u�̏ꍇ
			LoadModelData(pFile);
		}
		else if (strcmp(&aStr[0], ITEMSET_TXT) == 0)
		{//���f���z�u�̏ꍇ
			LoadItemData(pFile);
		}

		//�I���m�F
		if (strcmp(&aStr[0], END_SCRIPTTXT) == 0)
		{//�X�N���v�g�J�n�̕������m�F�ł����ꍇ
			break;
		}
		else if (nResult == EOF)
		{//�t�@�C���̍Ō�܂œǂݍ���ł��܂����ꍇ
			break;
		}
	}
}

//==========================================================
// �e�N�X�`�������ǂݍ���
//==========================================================
void CFileLoad::LoadTexNum(FILE *pFile)
{
	char aStr[4];	//�]���ȕ��͓ǂݍ��ݗp

	fscanf(pFile, "%s", &aStr[0]);	//(=)�ǂݍ���
	fscanf(pFile, "%d", &m_nTexNumAll);	//�g�p�����ǂݍ���

	if (m_nTexNumAll > 0)
	{// �ǂݍ��ޏꍇ
		if (nullptr == m_pTextureFile)
		{// �g�p���Ă��Ȃ��ꍇ
			m_pTextureFile = new File[m_nTexNumAll];
			memset(m_pTextureFile, NULL, sizeof(File) * m_nTexNumAll);
		}
	}
}

//==========================================================
// ���f�����ǂݍ���
//==========================================================
void CFileLoad::LoadModelNum(FILE *pFile)
{
	char aStr[4];	//�]���ȕ��͓ǂݍ��ݗp

	fscanf(pFile, "%s", &aStr[0]);	//(=)�ǂݍ���
	fscanf(pFile, "%d", &m_nModelNumAll);	//�g�p�����ǂݍ���

	if (m_nModelNumAll > 0)
	{// �ǂݍ��ޏꍇ
		if (nullptr == m_pModelFile)
		{// �g�p���Ă��Ȃ��ꍇ
			m_pModelFile = new File[m_nModelNumAll];
			memset(m_pModelFile, NULL, sizeof(File) * m_nModelNumAll);
		}
	}
}

//==========================================================
// �e�N�X�`���ǂݍ���
//==========================================================
void CFileLoad::LoadTexFile(FILE *pFile)
{
	char aStr[4];	//�]���ȕ��͓ǂݍ��ݗp
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	fscanf(pFile, "%s", &aStr[0]);	//(=)�ǂݍ���

	if (m_pTextureFile != NULL)
	{// �g�p����Ă���ꍇ
		for (int nCntTexture = 0; nCntTexture < m_nTexNumAll; nCntTexture++)
		{
			if (m_pTextureFile[nCntTexture].aFileName[0] == '\0')
			{//�t�@�C����������ꏊ���g���Ă��Ȃ��ꍇ
				fscanf(pFile, "%s", &m_pTextureFile[nCntTexture].aFileName[0]);	//(=)�ǂݍ���
																				// �t�@�C���ǂݍ��݊m�F
				m_pTextureFile[nCntTexture].nIdx = pTexture->Regist(&m_pTextureFile[nCntTexture].aFileName[0]);
				break;
			}
		}
	}
}

//==========================================================
// ���f���ǂݍ���
//==========================================================
void CFileLoad::LoadModelFile(FILE *pFile)
{
	char aStr[4];	//�]���ȕ��͓ǂݍ��ݗp
	CXFile *pModel = CManager::GetInstance()->GetModelFile();

	fscanf(pFile, "%s", &aStr[0]);	//(=)�ǂݍ���

	if (m_pModelFile != NULL)
	{// �g�p����Ă���ꍇ
		for (int nCntModel = 0; nCntModel < m_nModelNumAll; nCntModel++)
		{
			if (m_pModelFile[nCntModel].aFileName[0] == '\0')
			{//�t�@�C����������ꏊ���g���Ă��Ȃ��ꍇ
				fscanf(pFile, "%s", &m_pModelFile[nCntModel].aFileName[0]);	//(=)�ǂݍ���
				// �t�@�C���ǂݍ��݊m�F
				m_pModelFile[nCntModel].nIdx = pModel->Regist(&m_pModelFile[nCntModel].aFileName[0]);
				break;
			}
		}
	}
}

//==========================================================
// �e�N�X�`���̃t�@�C�����擾
//==========================================================
char *CFileLoad::GetTextureFileName(int nCntTexture)
{
	if (nCntTexture >= 0 && nCntTexture < m_nTexNumAll)
	{// �͈͓�
		if (m_pTextureFile != NULL)
		{// �g�p����Ă���ꍇ
			return &m_pTextureFile[nCntTexture].aFileName[0];
		}
	}

	return NULL;
}

//==========================================================
// ���f���̃t�@�C�����擾
//==========================================================
char *CFileLoad::GetModelFileName(int nCntModel)
{
	if (nCntModel >= 0 && nCntModel < m_nModelNumAll)
	{// �͈͓�
		if (m_pModelFile != NULL)
		{// �g�p����Ă���ꍇ
			return &m_pModelFile[nCntModel].aFileName[0];
		}
	}

	return NULL;
}

//==========================================================
// ���b�V���E�H�[���z�u���擾
//==========================================================
void CFileLoad::LoadMeshWallData(FILE *pFile)
{
	char aStr[256];	//�]���ȕ��͓ǂݍ��ݗp

	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int nWidth = 0;			// ������
	int nHeight = 0;		// ��������
	float fWidth = 0.0f;	// ��
	float fHeight = 0.0f;	// ����
	int nIdx = -1;

	//�I�������܂œǂݍ���
	while (1)
	{
		fscanf(pFile, "%s", &aStr[0]);

		//�z�u���m�F
		if (strcmp(&aStr[0], LOAD_TEXTYPE) == 0)
		{//�e�N�X�`��
			fscanf(pFile, "%s", &aStr[0]);	//(=)�ǂݍ���
			fscanf(pFile, "%d", &nIdx);	//�e�N�X�`�����ǂݍ���
		}
		else if (strcmp(&aStr[0], LOAD_POS) == 0)
		{//���W
			fscanf(pFile, "%s", &aStr[0]);	//(=)�ǂݍ���
			fscanf(pFile, "%f", &pos.x);	//x���W�ǂݍ���
			fscanf(pFile, "%f", &pos.y);	//y���W�ǂݍ���
			fscanf(pFile, "%f", &pos.z);	//z���W�ǂݍ���
		}
		else if (strcmp(&aStr[0], LOAD_ROT) == 0)
		{//����
			fscanf(pFile, "%s", &aStr[0]);	//(=)�ǂݍ���
			fscanf(pFile, "%f", &rot.x);	//x���W�ǂݍ���
			fscanf(pFile, "%f", &rot.y);	//y���W�ǂݍ���
			fscanf(pFile, "%f", &rot.z);	//z���W�ǂݍ���
		}
		else if (strcmp(&aStr[0], LOAD_BLOCK) == 0)
		{//����
			fscanf(pFile, "%s", &aStr[0]);	//(=)�ǂݍ���
			fscanf(pFile, "%d", &nHeight);	//�c���ǂݍ���
			fscanf(pFile, "%d", &nWidth);		//�����ǂݍ���

		}
		else if (strcmp(&aStr[0], LOAD_SIZE) == 0)
		{//�T�C�Y
			fscanf(pFile, "%s", &aStr[0]);	//(=)�ǂݍ���
			fscanf(pFile, "%f", &fHeight);//�c���ǂݍ���
			fscanf(pFile, "%f", &fWidth);	//�����ǂݍ���
		}

		//�I��
		if (strcmp(&aStr[0], ENDWALLSET_TXT) == 0)
		{//�I������
			break;
		}
	}

	//�t�B�[���h�̔z�u
	CMeshWall::Create(pos, D3DXToRadian(rot), fWidth, fHeight, GetTextureFileName(nIdx), nWidth, nHeight);
}

//==========================================================
// ���b�V���t�B�[���h�z�u���擾
//==========================================================
void CFileLoad::LoadMeshFieldData(FILE *pFile)
{
	char aStr[256];	//�]���ȕ��͓ǂݍ��ݗp
	char aUpDown[256] = {};

	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR2 move = D3DXVECTOR2(0.0f, 0.0f);
	int nWidth = 0;			// ������
	int nHeight = 0;		// ��������
	float fWidth = 0.0f;	// ��
	float fHeight = 0.0f;	// ����
	int nIdx = -1;

	//�I�������܂œǂݍ���
	while (1)
	{
		fscanf(pFile, "%s", &aStr[0]);

		//�z�u���m�F
		if (strcmp(&aStr[0], LOAD_TEXTYPE) == 0)
		{//�e�N�X�`��
			fscanf(pFile, "%s", &aStr[0]);	//(=)�ǂݍ���
			fscanf(pFile, "%d", &nIdx);	//�e�N�X�`�����ǂݍ���
		}
		else if (strcmp(&aStr[0], LOAD_POS) == 0)
		{//���W
			fscanf(pFile, "%s", &aStr[0]);	//(=)�ǂݍ���
			fscanf(pFile, "%f", &pos.x);	//x���W�ǂݍ���
			fscanf(pFile, "%f", &pos.y);	//y���W�ǂݍ���
			fscanf(pFile, "%f", &pos.z);	//z���W�ǂݍ���
		}
		else if (strcmp(&aStr[0], LOAD_ROT) == 0)
		{//����
			fscanf(pFile, "%s", &aStr[0]);	//(=)�ǂݍ���
			fscanf(pFile, "%f", &rot.x);	//x���W�ǂݍ���
			fscanf(pFile, "%f", &rot.y);	//y���W�ǂݍ���
			fscanf(pFile, "%f", &rot.z);	//z���W�ǂݍ���
		}
		else if (strcmp(&aStr[0], LOAD_BLOCK) == 0)
		{//����
			fscanf(pFile, "%s", &aStr[0]);	//(=)�ǂݍ���
			fscanf(pFile, "%d", &nHeight);	//�c���ǂݍ���
			fscanf(pFile, "%d", &nWidth);		//�����ǂݍ���

		}
		else if (strcmp(&aStr[0], LOAD_SIZE) == 0)
		{//�T�C�Y
			fscanf(pFile, "%s", &aStr[0]);	//(=)�ǂݍ���
			fscanf(pFile, "%f", &fHeight);  //�c���ǂݍ���
			fscanf(pFile, "%f", &fWidth);	//�����ǂݍ���
		}
		else if (strcmp(&aStr[0], LOAD_UPDOWN) == 0)
		{//�T�C�Y
			fscanf(pFile, "%s", &aStr[0]);	//(=)�ǂݍ���
			fscanf(pFile, "%s", &aUpDown[0]);  //�c���ǂݍ���
		}
		else if (strcmp(&aStr[0], "MOVE") == 0)
		{//�T�C�Y
			fscanf(pFile, "%s", &aStr[0]);	//(=)�ǂݍ���
			fscanf(pFile, "%f", &move.x);  //�c�ǂݍ���
			fscanf(pFile, "%f", &move.y);	//���ǂݍ���
		}

		//�I��
		if (strcmp(&aStr[0], ENDFIELDSET_TXT) == 0)
		{//�I������
			break;
		}
	}

	//�t�B�[���h�̔z�u
	CMeshField *pMesh = CMeshField::Create(pos, D3DXToRadian(rot), fWidth, fHeight, GetTextureFileName(nIdx), nWidth, nHeight);
	
	if (pMesh)
	{
		pMesh->SetTexMove(move);
	}

	if (aUpDown[0] != '\0')
	{
		pMesh->UpDownLoad(&aUpDown[0]);
	}
}

//==========================================================
// ���f���z�u���擾
//==========================================================
void CFileLoad::LoadModelData(FILE *pFile)
{
	char aStr[256];	//�]���ȕ��͓ǂݍ��ݗp

	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int nIdx = -1;

	//�I�������܂œǂݍ���
	while (1)
	{
		fscanf(pFile, "%s", &aStr[0]);

		//�z�u���m�F
		if (strcmp(&aStr[0], LOAD_MODELTYPE) == 0)
		{//�e�N�X�`��
			fscanf(pFile, "%s", &aStr[0]);	//(=)�ǂݍ���
			fscanf(pFile, "%d", &nIdx);	//�e�N�X�`�����ǂݍ���
		}
		else if (strcmp(&aStr[0], LOAD_POS) == 0)
		{//���W
			fscanf(pFile, "%s", &aStr[0]);	//(=)�ǂݍ���
			fscanf(pFile, "%f", &pos.x);	//x���W�ǂݍ���
			fscanf(pFile, "%f", &pos.y);	//y���W�ǂݍ���
			fscanf(pFile, "%f", &pos.z);	//z���W�ǂݍ���
		}
		else if (strcmp(&aStr[0], LOAD_ROT) == 0)
		{//����
			fscanf(pFile, "%s", &aStr[0]);	//(=)�ǂݍ���
			fscanf(pFile, "%f", &rot.x);	//x���W�ǂݍ���
			fscanf(pFile, "%f", &rot.y);	//y���W�ǂݍ���
			fscanf(pFile, "%f", &rot.z);	//z���W�ǂݍ���
		}

		//�I��
		if (strcmp(&aStr[0], ENDMODELSET_TXT) == 0)
		{//�I������
			break;
		}
	}

	//�t�B�[���h�̔z�u
	CObjectX::Create(pos, D3DXToRadian(rot), GetModelFileName(nIdx));
}

//==========================================================
// �A�C�e���z�u���擾
//==========================================================
void CFileLoad::LoadItemData(FILE *pFile)
{
	char aStr[256];	//�]���ȕ��͓ǂݍ��ݗp

	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int nIdx = -1;

	//�I�������܂œǂݍ���
	while (1)
	{
		fscanf(pFile, "%s", &aStr[0]);

		//�z�u���m�F
		if (strcmp(&aStr[0], LOAD_MODELTYPE) == 0)
		{//�e�N�X�`��
			fscanf(pFile, "%s", &aStr[0]);	//(=)�ǂݍ���
			fscanf(pFile, "%d", &nIdx);	//�e�N�X�`�����ǂݍ���
		}
		else if (strcmp(&aStr[0], LOAD_POS) == 0)
		{//���W
			fscanf(pFile, "%s", &aStr[0]);	//(=)�ǂݍ���
			fscanf(pFile, "%f", &pos.x);	//x���W�ǂݍ���
			fscanf(pFile, "%f", &pos.y);	//y���W�ǂݍ���
			fscanf(pFile, "%f", &pos.z);	//z���W�ǂݍ���
		}
		else if (strcmp(&aStr[0], LOAD_ROT) == 0)
		{//����
			fscanf(pFile, "%s", &aStr[0]);	//(=)�ǂݍ���
			fscanf(pFile, "%f", &rot.x);	//x���W�ǂݍ���
			fscanf(pFile, "%f", &rot.y);	//y���W�ǂݍ���
			fscanf(pFile, "%f", &rot.z);	//z���W�ǂݍ���
		}

		//�I��
		if (strcmp(&aStr[0], ENDITEMSET_TXT) == 0)
		{//�I������
			break;
		}
	}

	//�t�B�[���h�̔z�u
	CItem *pItem = CItem::Create(pos, D3DXToRadian(rot), GetModelFileName(nIdx), CItem::TYPE_COIN, CItem::STATE_NORMAL);

	if(m_pEnter != nullptr){
		m_pEnter->SetItemParent(pItem);
	}
}


//==========================================================
// ���b�V���h�[���z�u���擾
//==========================================================
void CFileLoad::LoadDomeData(FILE *pFile)
{

}

//==========================================================
// ���b�V���V�����_�[�z�u���擾
//==========================================================
void CFileLoad::LoadCylinderData(FILE *pFile)
{

}

//==========================================================
// �w�肳�ꂽ�t�@�C�����̇��擾
//==========================================================
int CFileLoad::GetTextureNum(const char *pFileName)
{
	int nIdx = -1;
	// �ǂݍ��܂�Ă��邩�m�F
	for (int nCnt = 0; nCnt < m_nTexNumAll; nCnt++)
	{
		if (nullptr == m_pTextureFile)
		{// �g���Ă��Ȃ��ꍇ
			continue;
		}

		// �����t�@�C�����m�F
		if (strstr(pFileName, &m_pTextureFile[nCnt].aFileName[0]) != NULL)
		{// �������̂����݂��Ă���ꍇ
			nIdx = nCnt;
			return nIdx;	// �t�@�C������Ԃ�
		}
	}

	return nIdx;
}

//==========================================================
// �w�肳�ꂽ�t�@�C�����̇��擾
//==========================================================
int CFileLoad::GetModelNum(const char *pFileName)
{
	int nIdx = -1;
	// �ǂݍ��܂�Ă��邩�m�F
	for (int nCnt = 0; nCnt < m_nModelNumAll; nCnt++)
	{
		if (nullptr == m_pModelFile)
		{// �g���Ă��Ȃ��ꍇ
			continue;
		}

		// �����t�@�C�����m�F
		if (strstr(pFileName, &m_pModelFile[nCnt].aFileName[0]) != NULL)
		{// �������̂����݂��Ă���ꍇ
			nIdx = nCnt;
			return nIdx;	// �t�@�C������Ԃ�
		}
	}

	return nIdx;
}

//==========================================================
// ����
//==========================================================
void CFileLoad::LoadVtxMaxData(FILE *pFile, int nIdx)
{
	char aStr[256];	//�]���ȕ��͓ǂݍ��ݗp
	D3DXVECTOR3 VtxMax = CManager::GetInstance()->GetModelFile()->GetMax(nIdx);

	fscanf(pFile, "%s", &aStr[0]);	//(=)�ǂݍ���
	fscanf(pFile, "%f", &VtxMax.x);	//x���W�ǂݍ���
	fscanf(pFile, "%f", &VtxMax.y);	//y���W�ǂݍ���
	fscanf(pFile, "%f", &VtxMax.z);	//z���W�ǂݍ���

	CManager::GetInstance()->GetModelFile()->SetSizeVtxMax(nIdx, VtxMax);
}

//==========================================================
// ����
//==========================================================
void CFileLoad::LoadVtxMinData(FILE *pFile, int nIdx)
{
	char aStr[256];	//�]���ȕ��͓ǂݍ��ݗp
	D3DXVECTOR3 VtxMin = CManager::GetInstance()->GetModelFile()->GetMin(nIdx);

	fscanf(pFile, "%s", &aStr[0]);	//(=)�ǂݍ���
	fscanf(pFile, "%f", &VtxMin.x);	//x���W�ǂݍ���
	fscanf(pFile, "%f", &VtxMin.y);	//y���W�ǂݍ���
	fscanf(pFile, "%f", &VtxMin.z);	//z���W�ǂݍ���

	CManager::GetInstance()->GetModelFile()->SetSizeVtxMin(nIdx, VtxMin);
}
