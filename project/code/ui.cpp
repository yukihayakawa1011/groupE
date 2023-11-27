//==========================================================
//
// �T���v���^�X�N [sample_task.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "ui.h"
#include "object2D.h"
#include "manager.h"
#include "texture.h"
#include "life.h"

// �}�N����`
#define TEXTURE_MONEY	("data\\TEXTURE\\money0.png")	//�����̒P�ʂ̃e�N�X�`��
#define MONEY_POSY	(38.0f)		//�P�ʂ̏ꏊ

// �t�@�C����
const char *CUI::m_apFrameFileName[FRAME_MAX] =
{
	"data\\TEXTURE\\frame0.png",
	"data\\TEXTURE\\frame1.png",
	"data\\TEXTURE\\frame2.png",
	"data\\TEXTURE\\frame3.png",
};

// �t�@�C����
const char *CUI::m_apIconFileName[ICON_MAX] =
{
	"data\\TEXTURE\\player_icon0.png",
	"data\\TEXTURE\\player_icon1.png",
	"data\\TEXTURE\\player_icon2.png",
	"data\\TEXTURE\\player_icon3.png",
};

//==========================================================
// �R���X�g���N�^
//==========================================================
CUI::CUI()
{
	// �l�̃N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);;
	m_type = TYPE_NORMAL;
	m_nLife = 0;

}

//==========================================================
// �f�X�g���N�^
//==========================================================
CUI::~CUI()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CUI::Init(void)
{
	for (int nCnt = 0; nCnt < NUM_OBJ; nCnt++)
	{
		m_pObject[nCnt] = CObject2D::Create();
	}

	m_pObject[0]->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\frame0.png"));
	m_pObject[0]->SetPosition(m_pos);
	m_pObject[0]->SetRotation(m_rot);
	m_pObject[0]->SetLength(300.0f, 125.0f);

	m_pObject[1]->BindTexture(CManager::GetInstance()->GetTexture()->Regist(TEXTURE_MONEY));
	m_pObject[1]->SetPosition(D3DXVECTOR3(m_pos.x + 50.0f, m_pos.y + 38.0f, m_pos.z));
	m_pObject[1]->SetRotation(m_rot);
	m_pObject[1]->SetLength(50.0f, 25.0f);

	m_pObject[2]->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\player_icon0.png"));
	m_pObject[2]->SetPosition(D3DXVECTOR3(m_pos.x - 110.0f, m_pos.y - 20.0f, m_pos.z));
	m_pObject[2]->SetRotation(m_rot);
	m_pObject[2]->SetLength(70.0f, 70.0f);

	return S_OK;
}

//==========================================================
// ����������
//==========================================================
HRESULT CUI::Init(int nFrame, int nIcon)
{
	for (int nCnt = 0; nCnt < NUM_OBJ; nCnt++)
	{
		m_pObject[nCnt] = CObject2D::Create(7);
	}

	//�t���[��
	m_pObject[0]->BindTexture(CManager::GetInstance()->GetTexture()->Regist(m_apFrameFileName[nFrame]));
	m_pObject[0]->SetPosition(m_pos);
	m_pObject[0]->SetLength(350.0f, 125.0f);

	//�����̒P��
	m_pObject[1]->BindTexture(CManager::GetInstance()->GetTexture()->Regist(TEXTURE_MONEY));
	m_pObject[1]->SetLength(50.0f, 25.0f);

	//��
	m_pObject[2]->BindTexture(CManager::GetInstance()->GetTexture()->Regist(m_apIconFileName[nIcon]));
	m_pObject[2]->SetLength(70.0f, 70.0f);

	//�^�C�v���Ƃ̈ʒu�ݒ�
	if (nFrame == 0)
	{
		m_pObject[1]->SetPosition(D3DXVECTOR3(m_pos.x + 125.0f, m_pos.y - MONEY_POSY, m_pos.z));	//�P��
		m_pObject[2]->SetPosition(D3DXVECTOR3(m_pos.x - 135.0f, m_pos.y + 15.0f, m_pos.z));	//��
		CLife *pLife = CLife::Create(D3DXVECTOR3(m_pos.x - 50.0f, m_pos.y + 20.0f, m_pos.z), m_rot);
		pLife->SetLife(m_nLife);

	}
	else if (nFrame == 1)
	{
		m_pObject[1]->SetPosition(D3DXVECTOR3(m_pos.x + 130.0f, m_pos.y - MONEY_POSY, m_pos.z)); //�P��
		m_pObject[2]->SetPosition(D3DXVECTOR3(m_pos.x + 130.0f, m_pos.y + 20.0f, m_pos.z));	//��
		CLife *pLife = CLife::Create(D3DXVECTOR3(m_pos.x - 70.0f, m_pos.y + 20.0f, m_pos.z), m_rot);
		pLife->SetLife(m_nLife);
	}
	else if (nFrame == 2)
	{
		m_pObject[1]->SetPosition(D3DXVECTOR3(m_pos.x + 125.0f, m_pos.y + MONEY_POSY, m_pos.z)); //�P��
		m_pObject[2]->SetPosition(D3DXVECTOR3(m_pos.x - 130.0f, m_pos.y - 20.0f, m_pos.z));	//��
		CLife *pLife = CLife::Create(D3DXVECTOR3(m_pos.x - 50.0f, m_pos.y - 20.0f, m_pos.z), m_rot);
		pLife->SetLife(m_nLife);
	}
	else if (nFrame == 3)
	{	
		m_pObject[1]->SetPosition(D3DXVECTOR3(m_pos.x + 130.0f, m_pos.y + MONEY_POSY, m_pos.z)); //�P��
		m_pObject[2]->SetPosition(D3DXVECTOR3(m_pos.x + 130.0f, m_pos.y - 20.0f, m_pos.z));	//��
		CLife *pLife = CLife::Create(D3DXVECTOR3(m_pos.x - 70.0f, m_pos.y - 20.0f , m_pos.z), m_rot);
		pLife->SetLife(m_nLife);
	}

	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CUI::Uninit(void)
{
	Release();

	for (int nCnt = 0; nCnt < NUM_OBJ; nCnt++)
	{
		if (nullptr != m_pObject[nCnt]) {
			m_pObject[nCnt]->Uninit();
			m_pObject[nCnt] = NULL;
		}
	}
}

//==========================================================
// �X�V����
//==========================================================
void CUI::Update(void)
{
	//�T�C�Y�̐ݒ�
	for (int nCnt = 0; nCnt < NUM_OBJ; nCnt++)
	{
		m_pObject[nCnt]->SetVtx();
	}
}

//==========================================================
// ����
//==========================================================
CUI *CUI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nFrame, int nIcon, TYPE type)
{
	CUI *pUI = nullptr;

	pUI = new CUI;

	if (pUI != nullptr)
	{
		pUI->SetPosition(pos);
		pUI->SetRotation(rot);
		pUI->SetType(type);
		// ����������
		pUI->Init(nFrame, nIcon);
	}	

	return pUI;
}