//===============================================
//
// �e�N�X�`���̊Ǘ��S�� [texture.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "texture.h"
#include "manager.h"
#include "renderer.h"
#include <string.h>

// �ÓI�����o�ϐ��錾
int CTexture::m_nNumAll = 0;	// �ǂݍ��ݑ���

// �t�@�C����
const char *CTexture::m_apDefFileName[TYPE_MAX] =
{
	"data\\TEXTURE\\effect000.jpg",
	"data\\TEXTURE\\money0.png",
	"data\\TEXTURE\\frame0.png",
	"data\\TEXTURE\\frame1.png",
	"data\\TEXTURE\\frame2.png",
	"data\\TEXTURE\\frame3.png",
	"data\\TEXTURE\\player_icon0.png",
	"data\\TEXTURE\\player_icon1.png",
	"data\\TEXTURE\\player_icon2.png",
	"data\\TEXTURE\\player_icon3.png",
	"data\\TEXTURE\\number001.png",
	"data\\TEXTURE\\heartL_0.png",
	"data\\TEXTURE\\heartR_0.png",
	"data\\TEXTURE\\smook.png",
	"data\\TEXTURE\\rank00.png",
};

//===============================================
// �R���X�g���N�^
//===============================================
CTexture::CTexture()
{
	for (int nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		m_aFile[nCntTex].pTexture = NULL;	// �g�p���Ă��Ȃ���Ԃɂ���
		memset(&m_aFile[nCntTex].aName[0], '\0', sizeof(File::aName));	// ���O�̃N���A
	}
}

//===============================================
// �f�X�g���N�^
//===============================================
CTexture::~CTexture()
{
	
}

//===============================================
// �ǂݍ���
//===============================================
HRESULT CTexture::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// �������ǂݍ���
	for (int nCntTex = 0; nCntTex < TYPE_MAX; nCntTex++)
	{
		if (m_aFile[nCntTex].pTexture == NULL)
		{// �g�p����Ă��Ȃ��ꍇ
			if (m_aFile[nCntTex].aName[0] == '\0')
			{// �t�@�C���������݂��Ă��Ȃ��ꍇ
				D3DXCreateTextureFromFile(pDevice,
					m_apDefFileName[nCntTex],
					&m_aFile[nCntTex].pTexture);

				strcpy(&m_aFile[nCntTex].aName[0], m_apDefFileName[nCntTex]);

				m_nNumAll++;
			}
		}
	}

	return S_OK;
}

//===============================================
// �p��
//===============================================
void CTexture::Unload(void)
{
	for (int nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		// �e�N�X�`���̔p��
		if (m_aFile[nCntTex].pTexture != NULL)
		{// �g�p����Ă���ꍇ
			m_aFile[nCntTex].pTexture->Release();
			m_aFile[nCntTex].pTexture = NULL;
			m_nNumAll--;
		}
	}
}

//===============================================
// �w��t�@�C���ǂݍ���
//===============================================
int CTexture::Regist(const char* pFileName)
{
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();		//�f�o�C�X�ւ̃|�C���^���擾
	int nIdx = -1;	// �e�N�X�`���ԍ�

	for (int nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		if (m_aFile[nCntTex].pTexture == NULL)
		{// �g�p����Ă��Ȃ��ꍇ
			// �t�@�C�������擾
			strcpy(&m_aFile[nCntTex].aName[0], pFileName);

			// �e�N�X�`���̓ǂݍ���
			if (SUCCEEDED(D3DXCreateTextureFromFile(pDevice,
				&m_aFile[nCntTex].aName[0],
				&m_aFile[nCntTex].pTexture)))
			{
				m_nNumAll++;	// �������J�E���g�A�b�v
				nIdx = nCntTex;	// �e�N�X�`���ԍ���ݒ�
			}

			break;
		}
		else
		{// �g�p����Ă���ꍇ
			if (strstr(&m_aFile[nCntTex].aName[0], pFileName) != NULL)
			{// �t�@�C��������v���Ă���ꍇ
				nIdx = nCntTex;	// �e�N�X�`���ԍ���ݒ�
				break;
			}
		}
	}

	return nIdx;	// �e�N�X�`���ԍ���Ԃ�
}

//===============================================
// �w��A�h���X�̃e�N�X�`�����擾
//===============================================
LPDIRECT3DTEXTURE9 CTexture::SetAddress(int nIdx)
{
	if (nIdx > m_nNumAll || nIdx < 0)
	{// �ǂݍ��ݔ͈͊O�̏ꍇ
		return NULL;
	}

	return m_aFile[nIdx].pTexture;
}

//===============================================
// �e�N�X�`�������擾
//===============================================
const char *CTexture::GetFileName(int nIdx)
{
	if (nIdx >= 0 && nIdx < TYPE_MAX)
	{// �͈͓�
		return m_apDefFileName[nIdx];
	}

	return NULL;
}