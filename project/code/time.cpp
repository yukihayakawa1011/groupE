//===============================================
//
// �^�C���̏��� [time.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "time.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "number.h"
#include "object2D.h"
#include "slow.h"
#include "debugproc.h"

// �}�N����`
#define X_SPACE		(50)	// ���̈ړ���
#define NUM_WIDTH		(20)
#define NUM_HEIGHT	(50)

namespace {
	const D3DXVECTOR3 WARNING_SETPOS = { SCREEN_WIDTH * 1.3f, SCREEN_HEIGHT * 0.5f, 0.0f };
	const D3DXVECTOR3 WARNING_SETROT = { 0.0f, 0.0f, D3DX_PI * 0.1f };
	const D3DXVECTOR2 WARNING_SIZE = { 100.0f, 50.0f };
}

//===============================================
// �R���X�g���N�^
//===============================================
CTime::CTime()
{
	// �l���N���A
	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		m_apNumber[nCnt] = NULL;
	}

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNum = 0;
	m_fAnimTimer = 0.0f;
	m_nIdxTexture = -1;
	m_nMaxNum = 0;
	m_fDiff = 0.0f;
	m_nStartDeltaTime = 0;
	m_nPauseTimer = 0;
	m_mode = MODE_MAX;
	m_bActive = false;
	m_pWarning = nullptr;
}

//===============================================
// �f�X�g���N�^
//===============================================
CTime::~CTime()
{

}

//===============================================
// ����������
//===============================================
HRESULT CTime::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();
	m_nStartDeltaTime = timeGetTime();
	m_mode = MODE_MINUS;

	// �e�N�X�`���̓ǂݍ���
	m_nIdxTexture = pTexture->Regist(CTexture::GetFileName(CTexture::TYPE_TIMER));
	CObject2D *pObj = CObject2D::Create(6);
	pObj->SetPosition(D3DXVECTOR3(m_pos.x + X_SPACE * 1.0f + NUM_WIDTH * 1.25f, m_pos.y, 0.0f));
	pObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f));
	pObj->SetSize(NUM_WIDTH * 5.0f, NUM_HEIGHT * 0.7f);
	pObj->BindTexture(pTexture->Regist("data\\TEXTURE\\map001.png"));

	pObj = CObject2D::Create(6);
	pObj->SetPosition(D3DXVECTOR3(m_pos.x + X_SPACE * 1.0f + NUM_WIDTH * 1.4f, m_pos.y, 0.0f));
	pObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	pObj->SetSize(NUM_WIDTH * 0.4f, NUM_HEIGHT * 0.45f);
	pObj->BindTexture(pTexture->Regist("data\\TEXTURE\\number002.png"));

	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		if (m_apNumber[nCnt] == NULL)
		{// �g�p���Ă��Ȃ��ꍇ
			D3DXVECTOR3 pos = m_pos;	// �ݒ���W
			pos.x += nCnt * X_SPACE + 1.0f;	// ���ړ�
			m_apNumber[nCnt] = CNumber::Create(pos, NUM_WIDTH * 0.75f, NUM_HEIGHT * 0.5f);


			if (m_apNumber[nCnt] != NULL)
			{// �g�p���Ă���ꍇ
				m_apNumber[nCnt]->GetObject2D()->BindTexture(m_nIdxTexture);
				
			}
		}
	}

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CTime::Uninit(void)
{
	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{// �g�p���Ă��Ȃ��ꍇ
			m_apNumber[nCnt]->Uninit();

			delete m_apNumber[nCnt];

			m_apNumber[nCnt] = NULL;
		}
	}

	if (m_pWarning != nullptr)
	{
		m_pWarning->Uninit();
		m_pWarning = nullptr;
	}
}

//===============================================
// �X�V����
//===============================================
void CTime::Update(void)
{
	if(!m_bActive)
	{
		return;
	}

	m_fAnimTimer += CManager::GetInstance()->GetSlow()->Get();
	if (m_fAnimTimer >= 60)
	{// 12�t���[��������
		m_fAnimTimer = 0;	// �J�E���^�[���Z�b�g
		Add(-1);
	}
}

//===============================================
// ����
//===============================================
CTime *CTime::Create(const D3DXVECTOR3& pos)
{
	CTime *pTime = NULL;

	// �I�u�W�F�N�g2D�̐���
	pTime = new CTime;

	if (pTime != NULL)
	{// �����ł����ꍇ

		pTime->m_pos = pos;

		// ����������
		pTime->Init();
	}
	else
	{// �����Ɏ��s�����ꍇ
		return NULL;
	}


	return pTime;
}

//===============================================
// ���Z
//===============================================
void CTime::Add(int nValue)
{
	// ���
	m_nNum += nValue;

	// ���l�ݒ�
	SetValue();

	// �x�����b�Z�[�W�����m�F
	if (m_nNum != 60) {	// �c��1���ł͂Ȃ�
		return;
	}

	if (m_pWarning != nullptr) {	// ���łɌx�����\����
		return;
	}

	// �x���𐶐�
	m_pWarning = CObject2D::Create(WARNING_SETPOS, WARNING_SETROT, 6);

	if (m_pWarning != nullptr) {	// �����ł���
		m_pWarning->SetLength(WARNING_SIZE.x, WARNING_SIZE.y);
	}
}

//===============================================
// �ݒ�
//===============================================
void CTime::Set(int nValue)
{
	// ���
	m_nNum = nValue;
	m_nSetNum = nValue;

	// ���l�ݒ�
	SetValue();
}

//===============================================
// �ݒ�l
//===============================================
void CTime::SetNum(int nValue)
{
	// ���
	m_nNum = nValue;

	// ���l�ݒ�
	SetValue();
}

//===============================================
// �����Ƃ̒l�ݒ�
//===============================================
void CTime::SetValue(void)
{
	int aTexU[NUM_PLACE] = {};	// �v�Z�i�[�p

	if (m_nNum < 0)
	{// 0�ȉ��̏ꍇ
		m_nNum = 0;
	}
	else if ((m_nNum - m_nNum % 100) * 0.01f >= 60 * 100)
	{
		m_nNum = 60 * 100 - 1;
	}

	int nNum = m_nNum;
	aTexU[0] = nNum / 60 / 10;
	aTexU[1] = nNum / 60 - aTexU[0] * 10;
	aTexU[2] = nNum % 60 / 10;
	aTexU[3] = nNum % 60 - aTexU[2] * 10;

	//�X�R�A���e�z��Ɋi�[
	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{// �g�p����Ă���ꍇ
			// �l��ݒ�
			m_apNumber[nCnt]->SetIdx(aTexU[nCnt]);
		}
	}
}

//===============================================
// �F�ݒ�
//===============================================
void CTime::SetColor(D3DXCOLOR col)
{
	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{// �g�p���Ă��Ȃ��ꍇ
			m_apNumber[nCnt]->GetObject2D()->SetCol(col);
		}
	}
}