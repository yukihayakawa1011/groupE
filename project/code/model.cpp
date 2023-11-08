//==========================================================
//
// �K�w�\���̃��f������ [model.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "model.h"
#include "Xfile.h"
#include "manager.h"
#include "texture.h"
#include "renderer.h"
#include "slow.h"
#include "meshfield.h"
#include "objectX.h"

//==========================================================
// �R���X�g���N�^
//==========================================================
CModel::CModel() : CObject(1)
{
	// �l�̃N���A
	m_nIdxModel = -1;
	m_bChangeCol = false;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_ChangeMat.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_ChangeMat.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_ChangeMat.Emissive = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pParentMtx = NULL;
	m_bDraw = true;
	m_bShadow = true;
	m_pCharacterMtx = nullptr;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CModel::~CModel()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CModel::Init(void)
{
	return S_OK;
}

//==========================================================
// ����������
//==========================================================
HRESULT CModel::Init(const char *pFileName)
{
	CXFile *pModelFile = CManager::GetInstance()->GetModelFile();	// ���f���t�@�C�����̃|�C���^

	//X�t�@�C������ǂݍ���
	m_nIdxModel = pModelFile->Regist(pFileName);

	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CModel::Uninit(void)
{
	// �|�C���^���g�p���Ă��Ȃ���Ԃɂ���
	m_pParentMtx = NULL;

	Release();
}

//==========================================================
// �X�V����
//==========================================================
void CModel::Update(void)
{

}

//==========================================================
// �`�揈��
//==========================================================
void CModel::Draw(void)
{
	if (m_bDraw == false)
	{
		return;
	}

	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	// �f�o�C�X�ւ̃|�C���^���擾
	CTexture *pTexture = CManager::GetInstance()->GetTexture();	// �e�N�X�`���ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	CXFile *pModelFile = CManager::GetInstance()->GetModelFile();	// X�t�@�C�����̃|�C���^
	D3DMATERIAL9 matDef;	// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;	// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATRIX mtxParent;	// �e�̃}�g���b�N�X���
	CSlow *pSlow = CManager::GetInstance()->GetSlow();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_CurRot.y, m_CurRot.x, m_CurRot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_CurPos.x, m_CurPos.y, m_CurPos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if(m_pParentMtx != NULL)
	{// �o���Ă���ꍇ
		mtxParent = *m_pParentMtx;

		// �p�[�c�̃}�g���b�N�X�Ɛe�̃}�g���b�N�X���������킹��
		D3DXMatrixMultiply(&m_mtxWorld,
			&m_mtxWorld, &mtxParent);
	}

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// ���f�������擾
	CXFile::FileData *pFileData = pModelFile->SetAddress(m_nIdxModel);

	if (pFileData != NULL)
	{// �g�p����Ă���ꍇ
		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)pFileData->pBuffMat->GetBufferPointer();
		for (int nCntMat = 0; nCntMat < (int)pFileData->dwNumMat; nCntMat++)
		{
			int nIdxTex = pFileData->pIdexTexture[nCntMat];	// �e�N�X�`���ԍ�

			if (m_bChangeCol == false)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			}
			else
			{
				// �}�e���A���̐ݒ�
				if (pSlow->Get() != 1.0f)
				{
					m_ChangeMat.Emissive.r -= 0.3f;
					m_ChangeMat.Emissive.g -= 0.3f;
					m_ChangeMat.Emissive.b -= 0.3f;
					m_ChangeMat.Emissive.a -= 0.3f;
				}
				else
				{
					m_ChangeMat.Emissive = pMat[nCntMat].MatD3D.Emissive;
					m_ChangeMat.Emissive.r += 0.1f;
					m_ChangeMat.Emissive.g += 0.1f;
					m_ChangeMat.Emissive.b += 0.1f;
					m_ChangeMat.Emissive.a += 0.1f;
				}
				pDevice->SetMaterial(&m_ChangeMat);
			}

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, pTexture->SetAddress(nIdxTex));

			// ���f��(�p�[�c)�̕`��
			pFileData->pMesh->DrawSubset(nCntMat);
		}
	}

	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);

	if(m_bShadow == true)
	{
		D3DXMATRIX mtxShadow;
		D3DLIGHT9 light;
		D3DXVECTOR4 posLight;
		D3DXVECTOR3 pos, normal;
		D3DXPLANE plane;

		// ���C�g�̈ʒu��ݒ�
		pDevice->GetLight(0, &light);
		posLight = D3DXVECTOR4(-light.Direction.x, -light.Direction.y, -light.Direction.z, 0.0f);

		// ���ʏ���ݒ�
		if (m_mtxWorld._42 >= -296.0f)
		{
			pos = D3DXVECTOR3(m_mtxWorld._41, -296.0f, m_mtxWorld._43);
			pos.y = CMeshField::GetHeight(D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43)) + 4.0f;
			CObjectX::CollisionLand(pos);
			normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			D3DXPlaneFromPointNormal(&plane, &pos, &normal);

			// �V���h�E�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&mtxShadow);

			// �V���h�E�}�g���b�N�X�̍쐬
			D3DXMatrixShadow(&mtxShadow, &posLight, &plane);
			D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

			//���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// ���f�������擾
			pFileData = pModelFile->SetAddress(m_nIdxModel);

			if (pFileData != NULL)
			{// �g�p����Ă���ꍇ
				//�}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)pFileData->pBuffMat->GetBufferPointer();
				for (int nCntMat = 0; nCntMat < (int)pFileData->dwNumMat; nCntMat++)
				{
					int nIdxTex = pFileData->pIdexTexture[nCntMat];	// �e�N�X�`���ԍ�

					if (m_bChangeCol == false)
					{
						m_ChangeMat.Emissive.r = 0.0f;
						m_ChangeMat.Emissive.g = 0.0f;
						m_ChangeMat.Emissive.b = 0.0f;
						m_ChangeMat.Emissive.a = 0.7f;
						m_ChangeMat.Diffuse.r = 0.0f;
						m_ChangeMat.Diffuse.g = 0.0f;
						m_ChangeMat.Diffuse.b = 0.0f;
						m_ChangeMat.Diffuse.a = 0.7f;

						//�}�e���A���̐ݒ�
						pDevice->SetMaterial(&m_ChangeMat);
					}
					else
					{
						pDevice->SetMaterial(&m_ChangeMat);
					}

					//�e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, nullptr);

					//���f��(�p�[�c)�̕`��
					pFileData->pMesh->DrawSubset(nCntMat);
				}
			}

			//�ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//==========================================================
// ����
//==========================================================
CModel *CModel::Create(const char *pFileName)
{
	CModel *pModel = NULL;
	CXFile *pModelFile = CManager::GetInstance()->GetModelFile();

	// �I�u�W�F�N�gX�̐���
	pModel = new CModel;

	if (pModel != NULL)
	{// �����ł����ꍇ

		// ����������
		pModel->Init(pFileName);

	}
	else
	{// �����Ɏ��s�����ꍇ
		return NULL;
	}

	return pModel;
}

//==========================================================
// �e���f����ݒ�
//==========================================================
void CModel::SetParent(D3DXMATRIX *pMtx)
{
	m_pParentMtx = pMtx;
}

//==========================================================
// �����ʒu��ݒ�
//==========================================================
void CModel::SetPosition(const D3DXVECTOR3 pos)
{
	m_pos = pos;

	SetCurrentPosition(m_pos);
}

//==========================================================
// ����������ݒ�
//==========================================================
void CModel::SetRotation(const D3DXVECTOR3 rot)
{
	m_rot = rot;

	SetCurrentRotation(m_rot);
}

//==========================================================
// ���݂̈ʒu��ݒ�
//==========================================================
void CModel::SetCurrentPosition(const D3DXVECTOR3 pos)
{
	m_CurPos = pos;
}

//==========================================================
// ���݂̌�����ݒ�
//==========================================================
void CModel::SetCurrentRotation(const D3DXVECTOR3 rot)
{
	m_CurRot = rot;
}

//==========================================================
// ���f���ԍ��̐ݒ�
//==========================================================
void CModel::BindModelFile(int nIdx)
{
	m_nIdxModel = nIdx;
}

//==========================================================
// �����蔻��
//==========================================================
void CModel::SetRotSize(D3DXVECTOR3 &SetMax, D3DXVECTOR3 &SetMin, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin, float fRot)
{
	//�����ɂ���ĕύX����
	if (fRot == 0.0f || fRot == -0.0f)
	{//������
	 //�ő�l���f
		SetMax.x = vtxMax.x;	//x���W
		SetMax.y = vtxMax.y;	//y���W
		SetMax.z = vtxMax.z;	//z���W

								//�ŏ��l���f
		SetMin.x = vtxMin.x;	//x���W
		SetMin.y = vtxMin.y;	//y���W
		SetMin.z = vtxMin.z;	//z���W
	}
	if (fRot == D3DX_PI * 0.5f)
	{//������
	 //�ő�l���f
		SetMax.x = vtxMax.z;	//x���W
		SetMax.y = vtxMax.y;	//y���W
		SetMax.z = -vtxMin.x;	//z���W

								//�ŏ��l���f
		SetMin.x = vtxMin.z;	//x���W
		SetMin.y = vtxMin.y;	//y���W
		SetMin.z = -vtxMax.x;	//z���W
	}
	else if (fRot == -D3DX_PI * 0.5f)
	{//�E����
	 //�ő�l���f
		SetMax.x = -vtxMin.z;	//x���W
		SetMax.y = vtxMax.y;	//y���W
		SetMax.z = vtxMax.x;	//z���W

								//�ŏ��l���f
		SetMin.x = -vtxMax.z;	//x���W
		SetMin.y = vtxMin.y;	//y���W
		SetMin.z = vtxMin.x;	//z���W
	}
	else if (fRot == -D3DX_PI || fRot == D3DX_PI)
	{//���]���Ă���ꍇ
	 //�����ȊO�̍ő�l���ŏ��l�ɂ���
		SetMax.x = -vtxMin.x;	//x���W
		SetMax.y = vtxMax.y;	//y���W
		SetMax.z = -vtxMin.z;	//z���W

								//�����ȊO�̍ŏ��l���ő�l�ɂ���
		SetMin.x = -vtxMax.x;	//x���W
		SetMin.y = vtxMin.y;	//y���W
		SetMin.z = -vtxMax.z;	//z���W
	}
	else
	{//����ȊO�̏ꍇ
	 //�ő�l���f
		SetMax.x = vtxMax.x;	//x���W
		SetMax.y = vtxMax.y;	//y���W
		SetMax.z = vtxMax.z;	//z���W

								//�ŏ��l���f
		SetMin.x = vtxMin.x;	//x���W
		SetMin.y = vtxMin.y;	//y���W
		SetMin.z = vtxMin.z;	//z���W
	}
}
