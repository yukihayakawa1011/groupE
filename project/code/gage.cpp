//==========================================================
//
// �Q�[�W [gage.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "gage.h"
#include "billboard.h"
#include "manager.h"
#include "texture.h"

// �������O���
namespace {
	const int DEF_PRI = (3);	// �D�揇��
	const char* FILENAME[CGage::TYPE_MAX] = {	// �e�N�X�`���t�@�C����
		"data\\TEXTURE\\map001.png",
		"data\\TEXTURE\\gage000.jpg"
	};
}

//==========================================================
// �R���X�g���N�^
//==========================================================
CGage::CGage()
{
	// �l�̃N���A
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++) {
		m_apObject[nCnt] = nullptr;
	}
	m_fPolyHeight = 0.0f;
	m_fPolyWidth = 0.0f;
	m_fUpHeight = 0.0f;
	m_fRate = 0.0f;
	m_pPos = nullptr;
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CGage::~CGage()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CGage::Init(void)
{
	// �I�u�W�F�N�g�̐���
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++) {
		m_apObject[nCnt] = CObjectBillboard::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), DEF_PRI + nCnt);
		m_apObject[nCnt]->SetAlphaText(false);
		m_apObject[nCnt]->SetLighting(true);
		m_apObject[nCnt]->SetZTest(false);
		m_apObject[nCnt]->SetFusion(CObjectBillboard::FUSION_NORMAL);
		m_apObject[nCnt]->BindTexture(CManager::GetInstance()->GetTexture()->Regist(FILENAME[nCnt]));
	}

	m_fRate = 1.0f;

	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CGage::Uninit(void)
{
	// �I�u�W�F�N�g�̏I������
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++) {
		if (m_apObject[nCnt] != nullptr) {
			m_apObject[nCnt]->Uninit();
			m_apObject[nCnt] = nullptr;
		}
	}

	// �J��
	Release();
}

//==========================================================
// �X�V����
//==========================================================
void CGage::Update(void)
{
	// ���W�̍X�V
	SetMixPosition();

	// �T�C�Y��ݒ�
	{
		if (m_apObject[TYPE_CONTENT] == nullptr) {
			return;
		}
		m_apObject[TYPE_CONTENT]->SetSize(m_fPolyWidth * m_fRate, m_fPolyHeight);
	}
}

//==========================================================
// ����
//==========================================================
CGage *CGage::Create(D3DXVECTOR3* pPos, const float fUpHeight, const float fPolyWidth, const float fPolyHeight)
{
	CGage *pGage = nullptr;

	pGage = new CGage;

	if (pGage != nullptr)
	{
		// ����������
		pGage->Init();

		// �e�̐ݒ�
		pGage->SetParent(pPos);

		// ���΍��W�̍�����ݒ�
		pGage->SetUpHeight(fUpHeight);

		// �|���S���T�C�Y��ݒ�
		pGage->SetPolySize(fPolyWidth, fPolyHeight);

		// ���W��ݒ�
		pGage->SetMixPosition();
	}

	return pGage;
}

//==========================================================
// �����̐ݒ�
//==========================================================
void CGage::SetRate(const float fRate)
{
	// ��������
	m_fRate = fRate;

	if (m_fRate < 0.0f) {	// �l���}�C�i�X�ɂȂ��Ă���
		m_fRate = 0.0f;
	}
	else if (m_fRate > 1.0f) {	// �l����𒴂���
		m_fRate = 1.0f;
	}
}

//==========================================================
// ���ƍ����̓K��
//==========================================================
void CGage::SetPolySize(const float fWidth, const float fHeight)
{
	// ���̐ݒ�
	{
		m_fPolyWidth = fWidth;
		if (m_fPolyWidth < 0.0f) {	// �l���}�C�i�X
			m_fPolyWidth = 0.0f;
		}
	}

	// �����̐ݒ�
	{
		m_fPolyHeight = fHeight;
		if (m_fPolyHeight < 0.0f) {	// �l���}�C�i�X
			m_fPolyHeight = 0.0f;
		}
	}

	// �I�u�W�F�N�g�ɓK��������
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++) {
		if (m_apObject[nCnt] == nullptr) {	// �g�p����Ă��Ȃ�
			continue;
		}

		// ���W�ݒ�
		m_apObject[nCnt]->SetSize(m_fPolyWidth, m_fPolyHeight);
	}
}

//==========================================================
// �ݒ荂���ƍ��������W��ݒ�
//==========================================================
void CGage::SetMixPosition(void)
{
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��̍��W
	if (m_pPos != nullptr) {	// �e�����݂��Ă���
		pos = *m_pPos;
	}
	pos.y += m_fUpHeight;	// �ݒ肳�ꂽ�������グ��

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++) {
		if (m_apObject[nCnt] == nullptr) {	// �g�p����Ă��Ȃ�
			continue;
		}

		// ���W�ݒ�
		m_apObject[nCnt]->SetPosition(D3DXVECTOR3(pos));
	}
}