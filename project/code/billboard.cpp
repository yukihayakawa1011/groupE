//==========================================================
//
// �r���{�[�h�̏����S�� [billboard.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "billboard.h"
#include "input.h"
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//==========================================================
//�R���X�g���N�^
//==========================================================
CObjectBillboard::CObjectBillboard(int nPriority) : CObject(nPriority)
{
	// �l�̃N���A
	m_nIdexTexture = -1;
	m_pVtxBuff = NULL;
	m_fusion = FUSION_ADD;
	m_bLighting = true;
	m_bAlphatest = true;
	m_bZtest = true;
}

//==========================================================
//�f�X�g���N�^
//==========================================================
CObjectBillboard::~CObjectBillboard()
{

}

//==========================================================
//�r���{�[�h�̏���������
//==========================================================
HRESULT CObjectBillboard::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_���ݒ�
	SetVtx();

	return S_OK;
}

//==========================================================
//�r���{�[�h�̏I������
//==========================================================
void CObjectBillboard::Uninit(void)
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
//�r���{�[�h�̍X�V����
//==========================================================
void CObjectBillboard::Update(void)
{
	
}

//==========================================================
//�r���{�[�h�̕`�揈��
//==========================================================
void CObjectBillboard::Draw(void)
{
	if (!GetDraw())
	{
		return;
	}

	if (m_pVtxBuff == nullptr)
	{
		return;
	}

	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		//�f�o�C�X�ւ̃|�C���^���擾
	CTexture *pTexture = CManager::GetInstance()->GetTexture();	// �e�N�X�`���ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;		//�r���[�}�g���b�N�X�擾�p

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�r���[�}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

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
	pDevice->SetTexture(0, pTexture->SetAddress(m_nIdexTexture));

	if (m_bLighting) {
		//���C�e�B���O���I�t�ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	}

	if (m_bZtest) {
		//Z�e�X�g�𖳌�������
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	}

	if (m_bAlphatest) {
		//�A���t�@�e�X�g��L���ɂ���
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	}

	if (m_fusion == FUSION_ADD)
	{
		//���u�����f�B���O�����Z�����ɐݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}
	else if (m_fusion == FUSION_MINUS)
	{
		//���Z�����̐ݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	//�|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
		0,
		2	//���_���\���̂̃T�C�Y
	);

	if (m_bLighting) {
		//���C�e�B���O���I���ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}

	if (m_bZtest) {
		//Z�e�X�g��L���ɂ���
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	}

	if (m_bAlphatest) {
		//�A���t�@�e�X�g�𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 255);
	}

	if (m_fusion == FUSION_ADD)
	{
		//���u�����f�B���O�����ɖ߂�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
	else if (m_fusion == FUSION_MINUS)
	{
		//���u�����f�B���O�����ɖ߂�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}

//==========================================================
// �����𔽉f�������`�揈��
//==========================================================
void CObjectBillboard::RotFusionDraw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		//�f�o�C�X�ւ̃|�C���^���擾
	CTexture *pTexture = CManager::GetInstance()->GetTexture();	// �e�N�X�`���ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;		//�r���[�}�g���b�N�X�擾�p

	if (m_bLighting) {
		//���C�e�B���O���I�t�ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	}

	if (m_bZtest) {
		//Z�e�X�g�𖳌�������
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	}

	if (m_bAlphatest) {
		//�A���t�@�e�X�g��L���ɂ���
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	}

	if (m_fusion == FUSION_ADD)
	{
		//���u�����f�B���O�����Z�����ɐݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}
	else if (m_fusion == FUSION_MINUS)
	{
		//���Z�����̐ݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�r���[�}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

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
	pDevice->SetTexture(0, pTexture->SetAddress(m_nIdexTexture));

	//�|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
		0,
		2	//���_���\���̂̃T�C�Y
	);

	if (m_bLighting) {
		//���C�e�B���O���I���ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}

	if (m_bZtest) {
		//Z�e�X�g��L���ɂ���
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	}

	if (m_bAlphatest) {
		//�A���t�@�e�X�g�𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 255);
	}

	if (m_fusion == FUSION_ADD)
	{
		//���u�����f�B���O�����ɖ߂�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
	else if (m_fusion == FUSION_MINUS)
	{
		//���u�����f�B���O�����ɖ߂�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}

//==========================================================
//��������
//==========================================================
CObjectBillboard *CObjectBillboard::Create(D3DXVECTOR3 pos, const int nPriority)
{
	CObjectBillboard *pObjBillboard = NULL;

	// �I�u�W�F�N�g2D�̐���
	pObjBillboard = new CObjectBillboard(nPriority);

	if (pObjBillboard != NULL)
	{// �����ł����ꍇ

		// ����������
		pObjBillboard->Init();

		// ���W�ݒ�
		pObjBillboard->SetPosition(pos);

		// ��ސݒ�
		pObjBillboard->SetType(TYPE_NONE);
	}
	else
	{// �����Ɏ��s�����ꍇ
		return NULL;
	}

	return pObjBillboard;
}

//==========================================================
// ���_���ݒ�
//==========================================================
void CObjectBillboard::SetVtx(void)
{
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-5.0f, +5.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+5.0f, +5.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-5.0f, -5.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+5.0f, -5.0f, 0.0f);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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

//==========================================================
//�e�N�X�`�����W�ݒ�
//==========================================================
void CObjectBillboard::SetVtx(const int nPatternAnim, const int nTexWidth, const int nTexHeight)
{
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//���_���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(1.0f / nTexWidth * (float)nPatternAnim, (1.0f / nTexHeight * (float)(nPatternAnim / nTexWidth)));
	pVtx[1].tex = D3DXVECTOR2(1.0f / nTexWidth * (float)(nPatternAnim + 1), (1.0f / nTexHeight * (float)(nPatternAnim / nTexWidth)));
	pVtx[2].tex = D3DXVECTOR2(1.0f / nTexWidth * (float)nPatternAnim, (1.0f / nTexHeight * (float)(nPatternAnim / nTexWidth + 1)));
	pVtx[3].tex = D3DXVECTOR2(1.0f / nTexWidth * (float)(nPatternAnim + 1), (1.0f / nTexHeight * (float)(nPatternAnim / nTexWidth + 1)));

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===============================================
// ���_���ݒ�(�e�N�X�`���A�j���[�V����)
//===============================================
void CObjectBillboard::SetVtx(const float fTexU, const float fTexV)
{
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(fTexU, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.3f + fTexU, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(fTexU, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.3f + fTexU, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//==========================================================
// �F�ݒ�
//==========================================================
void CObjectBillboard::SetVtx(D3DXCOLOR col)
{
	VERTEX_3D *pVtx;
	m_col = col;

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
//�e�N�X�`���ݒ�
//==========================================================
void CObjectBillboard::BindTexture(int nIdx)
{
	m_nIdexTexture = nIdx;
}

//==========================================================
//�T�C�Y�ݒ�
//==========================================================
void CObjectBillboard::SetSize(float fWidth, float fHeight)
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
	pVtx[0].pos = D3DXVECTOR3(sinf(m_rot.z + (-D3DX_PI * 0.25f)) * m_fWidth, cosf(m_rot.z + (-D3DX_PI * 0.25f)) * m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(sinf(m_rot.z + (D3DX_PI * 0.25f)) * m_fWidth, cosf(m_rot.z + (D3DX_PI * 0.25f)) * m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(sinf(m_rot.z + (-D3DX_PI * 0.75f)) * m_fWidth, cosf(m_rot.z + (-D3DX_PI * 0.75f)) * m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(sinf(m_rot.z + (D3DX_PI * 0.75f)) * m_fWidth, cosf(m_rot.z + (D3DX_PI * 0.75f)) * m_fHeight, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//==========================================================
// �F�ݒ�
//==========================================================
void CObjectBillboard::SetCol(D3DXCOLOR col)
{
	VERTEX_3D *pVtx;
	m_col = col;

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
// �}�g���b�N�X�ݒ�
//==========================================================
void CObjectBillboard::SetMtx(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		//�f�o�C�X�ւ̃|�C���^���擾
	D3DXMATRIX mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;		//�r���[�}�g���b�N�X�擾�p

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�r���[�}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
}