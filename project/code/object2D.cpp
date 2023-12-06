//===============================================
//
// �I�u�W�F�N�g(2D)�̏��� [object2D.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "object2D.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//===============================================
// �}�N����`
//===============================================
#define VTX	(4)	// ���_��
#define WIDTH	(100.0f)	// ��
#define HEIGHT	(100.0f)	// ����
#define POS_X	(300.0f)	// X���W
#define POS_Y	(300.0f)	// Y���W
#define TEX_FILENAME "data\\TEXTURE\\meteor001.png"	// �e�N�X�`����

//====================================================================================
// �I�u�W�F�N�g2D�N���X
//====================================================================================
//===============================================
// �R���X�g���N�^
//===============================================
//CObject2D::CObject2D()
//{
//	// �l���N���A����
//	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	m_fLength = 0.0f;
//	m_fAngle = 0.0f;
//	m_fWidth = 0.0f;
//	m_fHeight = 0.0f;
//}

//===============================================
// �R���X�g���N�^(�I�[�o�[���[�h)
//===============================================
CObject2D::CObject2D(const D3DXVECTOR3 pos) : CObject(3)
{
	// �K��l������
	m_pos = pos;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fLength = 0.0f;
	m_fAngle = 0.0f;
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	m_nIdxTexture = -1;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

//===============================================
// �R���X�g���N�^(�I�[�o�[���[�h)
//===============================================
CObject2D::CObject2D(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const int nPriority) : CObject(nPriority)
{
	// �K��l������
	m_pos = pos;
	m_rot = rot;
	m_fLength = 0.0f;
	m_fAngle = 0.0f;
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	m_nIdxTexture = -1;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

//===============================================
// �R���X�g���N�^(�I�[�o�[���[�h)
//===============================================
CObject2D::CObject2D(int nPriority) : CObject(nPriority)
{
	// �l���N���A����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fLength = 0.0f;
	m_fAngle = 0.0f;
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	m_nIdxTexture = -1;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

//===============================================
// �f�X�g���N�^
//===============================================
CObject2D::~CObject2D()
{

}

//===============================================
// ����������
//===============================================
HRESULT CObject2D::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���(���蓖�Ă�̂ł���Ȃ�)
	/*D3DXCreateTextureFromFile(pDevice, 
		TEX_FILENAME, 
		&m_pTexture);*/

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);
	
	if (m_pVtxBuff == NULL)
	{// �����Ɏ��s�����ꍇ
		return E_FAIL;
	}

	//�Ίp���̒������Z�o����
	m_fLength = sqrtf(WIDTH * WIDTH + HEIGHT * HEIGHT) * 0.5f;

	//�Ίp���̊p�x���Z�o����
	m_fAngle = atan2f(WIDTH, HEIGHT);

	// ���_���ݒ�
	SetVtx();

	return S_OK;
}

//===============================================
// ����������
//===============================================
HRESULT CObject2D::Init(const char *pFileName)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���(���蓖�Ă�̂ł���Ȃ�)
	/*D3DXCreateTextureFromFile(pDevice,
		pFileName,
		&m_pTexture);*/

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	if (m_pVtxBuff == NULL)
	{// �����Ɏ��s�����ꍇ
		return E_FAIL;
	}

	//�Ίp���̒������Z�o����
	m_fLength = sqrtf(m_fWidth * m_fWidth + m_fHeight * m_fHeight) * 0.5f;

	//�Ίp���̊p�x���Z�o����
	m_fAngle = atan2f(m_fWidth, m_fHeight);

	// ���_���ݒ�
	SetVtx();

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CObject2D::Uninit(void)
{
	// ���_�o�b�t�@�̔p��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �p��
	Release();
}

//===============================================
// �X�V����
//===============================================
void CObject2D::Update(void)
{
	// ���_���̍X�V
	//SetVtx();
}

//===============================================
// �`�揈��
//===============================================
void CObject2D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(
		0,
		m_pVtxBuff,
		0,
		sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->SetAddress(m_nIdxTexture));

	// �`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
		0,
		2	//���_���\���̂̃T�C�Y
	);
}

//===============================================
// ���_���ݒ�
//===============================================
void CObject2D::SetVtx(void)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z + (-D3DX_PI + m_fAngle)) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z + (-D3DX_PI + m_fAngle)) * m_fLength;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z + -m_fAngle) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z + -m_fAngle) * m_fLength;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===============================================
// ���_���ݒ�(�p�^�[���A�j���[�V����)
//===============================================
void CObject2D::SetVtx(const int nPatternAnim, const int nTexWidth, const int nTexHeight)
{
	VERTEX_2D *pVtx;

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
void CObject2D::SetVtx(const float fTexU, const float fTexV, const float fWidth, const float fHeight)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = m_pos.x - fWidth;
	pVtx[0].pos.y = m_pos.y - fHeight;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = m_pos.x + fWidth;
	pVtx[1].pos.y = m_pos.y - fHeight;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = m_pos.x - fWidth;
	pVtx[2].pos.y = m_pos.y + fHeight;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = m_pos.x + fWidth;
	pVtx[3].pos.y = m_pos.y + fHeight;
	pVtx[3].pos.z = 0.0f;

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(fTexU, fTexV);
	pVtx[1].tex = D3DXVECTOR2(fTexU + 1.0f, fTexV);
	pVtx[2].tex = D3DXVECTOR2(fTexU, fTexV + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(fTexU + 1.0f, fTexV + 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===============================================
// ���_���ݒ�
//===============================================
CObject2D *CObject2D::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const int nPriority)
{
	CObject2D *pObject2D = NULL;

	// �I�u�W�F�N�g2D�̐���
	pObject2D = new CObject2D(pos, rot, nPriority);

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

//===============================================
// ����
//===============================================
CObject2D *CObject2D::Create(const int nPriority)
{
	CObject2D *pObject2D = NULL;

	// �I�u�W�F�N�g2D�̐���
	pObject2D = new CObject2D(nPriority);

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

//===============================================
// ���W�ݒ�
//===============================================
void CObject2D::SetPosition(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//===============================================
// �����ݒ�
//===============================================
void CObject2D::SetRotation(const D3DXVECTOR3 rot)
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
	{// z���W�p�x���E
		m_rot.x += D3DX_PI * 2;
	}
	else if (m_rot.x > D3DX_PI)
	{// z���W�p�x���E
		m_rot.x += -D3DX_PI * 2;
	}

	if (m_rot.y < -D3DX_PI)
	{// z���W�p�x���E
		m_rot.y += D3DX_PI * 2;
	}
	else if (m_rot.y > D3DX_PI)
	{// z���W�p�x���E
		m_rot.y += -D3DX_PI * 2;
	}
}

//===============================================
// �e�N�X�`���ԍ��̊��蓖��
//===============================================
void CObject2D::BindTexture(int nIdx)
{
	m_nIdxTexture = nIdx;
}

//===============================================
// �T�C�Y�ݒ�
//===============================================
void CObject2D::SetLength(float fWidth, float fHeight)
{
	m_fWidth = fWidth * 0.5f;
	m_fHeight = fHeight * 0.5f;
	//�Ίp���̒������Z�o����
	m_fLength = sqrtf(fWidth * fWidth + fHeight * fHeight) * 0.5f;

	//�Ίp���̊p�x���Z�o����
	m_fAngle = atan2f(fWidth, fHeight);

	// ���_���ݒ�
	SetVtx();
}

//===============================================
// ���ݒ�
//===============================================
void CObject2D::SetWidth(float fWidth)
{
	m_fWidth = fWidth;
}

//===============================================
// �����ݒ�
//===============================================
void CObject2D::SetHeight(float fHeight)
{
	m_fHeight = fHeight;
}

//===============================================
// �e�N�X�`���ԍ��ݒ�
//===============================================
void CObject2D::SetIdxTex(int nIdx)
{
	m_nIdxTexture = nIdx;
}

//===============================================
// ���_���̐F�ύX
//===============================================
void CObject2D::SetCol(const D3DXCOLOR col)
{
	m_col = col;
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===============================================
// �Ίp���̒���
//===============================================
void CObject2D::SetLength(const float fLength)
{
	m_fLength = fLength;	// �������擾
}

//===============================================
// �p�x�̒���
//===============================================
void CObject2D::SetAngle(const float fAngle)
{
	m_fAngle = fAngle;	// �p�x���擾
}

//===============================================
// �T�C�Y�ݒ�
//===============================================
void CObject2D::SetSize(float fWidth, float fHeight)
{
	m_fHeight = fHeight;
	m_fWidth = fWidth;

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = m_pos.x - fWidth;
	pVtx[0].pos.y = m_pos.y - fHeight;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = m_pos.x + fWidth;
	pVtx[1].pos.y = m_pos.y - fHeight;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = m_pos.x - fWidth;
	pVtx[2].pos.y = m_pos.y + fHeight;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = m_pos.x + fWidth;
	pVtx[3].pos.y = m_pos.y + fHeight;
	pVtx[3].pos.z = 0.0f;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===============================================
// �v���C���[�p���_���ݒ�
//===============================================
void CObject2D::SetPlayerVtx(void)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = m_pos.x - m_fWidth;
	pVtx[0].pos.y = m_pos.y - m_fHeight;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = m_pos.x + m_fWidth;
	pVtx[1].pos.y = m_pos.y - m_fHeight;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = m_pos.x - m_fWidth;
	pVtx[2].pos.y = m_pos.y;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = m_pos.x + m_fWidth;
	pVtx[3].pos.y = m_pos.y;
	pVtx[3].pos.z = 0.0f;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

void CObject2D::SetTex(const float fTexU, const float fTexV, const float fWidth, const float fHeight)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(fTexU, fTexV);
	pVtx[1].tex = D3DXVECTOR2(fTexU + fWidth, fTexV);
	pVtx[2].tex = D3DXVECTOR2(fTexU, fTexV + fHeight);
	pVtx[3].tex = D3DXVECTOR2(fTexU + fWidth, fTexV + fHeight);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}