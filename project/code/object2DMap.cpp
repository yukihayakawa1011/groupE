//==========================================================
//
// �}�b�v�I�u�W�F�N�g [object2DMap.cpp]
// Author : Soma Ishihara
//
//==========================================================
#include "object2DMap.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

// �}�N����`

//==========================================================
// �R���X�g���N�^
//==========================================================
CObject2DMap::CObject2DMap(int nPriOrity) : CObject2D(nPriOrity)
{

}

//==========================================================
// �f�X�g���N�^
//==========================================================
CObject2DMap::~CObject2DMap()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CObject2DMap::Init(void)
{
	CObject2D::Init();
	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CObject2DMap::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================================
// �`�揈��
//==========================================================
void CObject2DMap::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		//�f�o�C�X�ւ̃|�C���^
	CTexture *pTexture = CManager::GetInstance()->GetTexture();
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtx();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(
		0,
		pVtxBuff,
		0,
		sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �}�b�v�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTextureMap);

	// �`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
		0,
		2	//���_���\���̂̃T�C�Y
	);

	// �܂����낭�낷���e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTextureUnex);

	// �`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
		0,
		2	//���_���\���̂̃T�C�Y
	);
}

//==========================================================
// ����
//==========================================================
CObject2DMap *CObject2DMap::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight)
{
	CObject2DMap *pMap = nullptr;

	pMap = new CObject2DMap;

	if (pMap != nullptr)
	{
		// ����������
		pMap->Init();
		pMap->SetPosition(pos);
		pMap->SetRotation(rot);
		pMap->SetSize(fWidth, fHeight);
	}

	return pMap;
}

//==========================================================
// �e�N�X�`���ݒ�
//==========================================================
void CObject2DMap::SetTexture(LPDIRECT3DTEXTURE9 pTexMap, LPDIRECT3DTEXTURE9 pTexUnex)
{
	m_pTextureMap = pTexMap;
	m_pTextureUnex = pTexUnex;
}
