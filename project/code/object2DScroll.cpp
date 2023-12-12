//===============================================
//
// �I�u�W�F�N�g(�}�b�v�̊���)�̏��� [object2D.cpp]
// Author : Soma Ishihara
//
//===============================================
#include "object2DScroll.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//====================================================================================
// �}�b�v�̊����N���X
//====================================================================================
//===============================================
// �R���X�g���N�^
//===============================================
CObject2DScroll::CObject2DScroll() : CObject2D(3)
{
}

//===============================================
// �R���X�g���N�^�i�I�[�o�[���[�h�j
//===============================================
CObject2DScroll::CObject2DScroll(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const int nPriority) : CObject2D(pos,rot,nPriority)
{
}

//===============================================
// �f�X�g���N�^
//===============================================
CObject2DScroll::~CObject2DScroll()
{

}

//===============================================
// ����������
//===============================================
HRESULT CObject2DScroll::Init(void)
{
	CObject2D::Init();
	return S_OK;
}

//===============================================
// �I������
//===============================================
void CObject2DScroll::Uninit(void)
{
	CObject2D::Uninit();

	// �p��
	Release();
}

//===============================================
// �X�V����
//===============================================
void CObject2DScroll::Update(void)
{
	CObject2D::Update();
}

//===============================================
// �`�揈��
//===============================================
void CObject2DScroll::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		//�f�o�C�X�ւ̃|�C���^
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	//�A���t�@�e�X�g�L���E�����ݒ�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 180);

	// �`��
	CObject2D::Draw();

	//�A���t�@�e�X�g�L���E�����ݒ�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}

//===============================================
// ���_���ݒ�
//===============================================
CObject2DScroll *CObject2DScroll::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const int nPriority)
{
	CObject2DScroll *pObject2D = NULL;

	// �I�u�W�F�N�g2D�̐���
	pObject2D = new CObject2DScroll(pos, rot, nPriority);

	if (pObject2D != NULL)
	{// �����ł����ꍇ
		// ����������

		pObject2D->Init();

		// ��ސݒ�
		pObject2D->SetType(TYPE_NONE);
	}
	else
	{// �����Ɏ��s�����ꍇ
		return NULL;
	}

	return pObject2D;
}