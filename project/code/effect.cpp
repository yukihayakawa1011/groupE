//===============================================
//
// �G�t�F�N�g�̏��� [effect.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "effect.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
#include "texture.h"
#include "slow.h"
#include "game.h"
#include "meshfield.h"
#include "billboard.h"

//===============================================
// �������O���
//===============================================
namespace {
	const float LIFE = (30.0f); // ����

	const D3DXCOLOR COLINFO[CEffect::TYPE_MAX] = {	// ��ޕʏ����F�̐ݒ�
		{1.0f, 1.0f, 1.0f, 1.0f},
		{ 1.0f, 1.0f, 0.0f, 1.0f },
		{ 1.0f, 1.0f, 0.0f, 1.0f },
	};

	const float RADIUSINFO[CEffect::TYPE_MAX] = {	// ��ޕʔ��a�̐ݒ�
		100.0f,
		100.0f,
		100.0f,
	};
}

//===============================================
// �R���X�g���N�^
//===============================================
CEffect::CEffect()
{
	// �l�̃N���A
	m_Info.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_Info.fLife = 0;
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.fRadius = 0.0f;
	m_Info.Type = TYPE_NONE;
}

//===============================================
// �f�X�g���N�^
//===============================================
CEffect::~CEffect()
{

}

//===============================================
// ����������
//===============================================
HRESULT CEffect::Init(void)
{
	// �I�u�W�F�N�g�̏���������
	m_pObjectBilBoard = CObjectBillboard::Create(m_Info.pos, 6);
	m_pObjectBilBoard->BindTexture(CManager::GetInstance()->GetTexture()->Regist(CManager::GetInstance()->GetTexture()->GetFileName(SetTex(m_Info.Type))));
	m_pObjectBilBoard->SetAlphaText(true);
	m_pObjectBilBoard->SetZTest(true);
	m_pObjectBilBoard->SetLighting(true);
	m_pObjectBilBoard->SetFusion(CObjectBillboard::FUSION_ADD);

	m_Info.fLife = LIFE;	// �̗͂̏�����

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CEffect::Uninit(void)
{
	// �I�u�W�F�N�g�̏I������
	if (m_pObjectBilBoard != nullptr) {
		m_pObjectBilBoard->Uninit();
		m_pObjectBilBoard = nullptr;
	}

	Release();
}

//===============================================
// �X�V����
//===============================================
void CEffect::Update(void)
{
	m_Info.fLife -= CManager::GetInstance()->GetSlow()->Get();
	D3DXVECTOR3 nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float fHeight = CMeshField::GetHeight(m_Info.pos);

	if (m_Info.fLife < 0)
	{// �������Ȃ��Ȃ����ꍇ

		// �I������
		Uninit();

		return;
	}

	D3DXVECTOR3 pos = GetPosition();	// ���W

	pos += m_Info.move * CManager::GetInstance()->GetSlow()->Get();

	// ���W
	SetPosition(pos);

	switch (m_Info.Type)
	{
	case TYPE_NONE:
		m_Info.col.a -= 0.05f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.fRadius += 0.1f * CManager::GetInstance()->GetSlow()->Get();
		break;

	case TYPE_SMAKE:	// ��

		m_Info.col.a -= 0.05f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.fRadius += 0.1f * CManager::GetInstance()->GetSlow()->Get();

		break;
	case TYPE_ITEMGET:	// ��

		m_Info.col.a -= 0.03f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.fRadius += 0.1f * CManager::GetInstance()->GetSlow()->Get();
		{
			D3DXVECTOR3 rot = m_pObjectBilBoard->GetRotation();
			rot.z += D3DX_PI * 0.15f;
			m_pObjectBilBoard->SetRotation(rot);
		}

		break;

	case TYPE_LANDCLEAR:	// ��

		m_Info.col.a -= 0.05f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.fRadius += 0.1f * CManager::GetInstance()->GetSlow()->Get();

		break;

	case TYPE_LANDFAILED:	// ��

		m_Info.col.a -= 0.05f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.fRadius += 0.1f * CManager::GetInstance()->GetSlow()->Get();

		break;

	case TYPE_HIT:	// ��

		m_Info.col.a -= 0.03f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.move.x -= m_Info.move.x * 0.045f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.move.y -= m_Info.move.y * 0.025f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.move.z -= m_Info.move.z * 0.045f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.fRadius += 0.45f * CManager::GetInstance()->GetSlow()->Get();

		break;

	case TYPE_SPEAR:	// ��

		m_Info.col.a -= 0.005f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.move.y += -0.5f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.fRadius -= 0.1f * CManager::GetInstance()->GetSlow()->Get();

		if (m_Info.pos.y <= 0.0f)
		{
			m_Info.move.y = 0.0f;
			return;
		}
		else
		{
			D3DXVECTOR3 rot = m_pObjectBilBoard->GetRotation();
			rot.z += D3DX_PI * 0.2f;
			m_pObjectBilBoard->SetRotation(rot);
		}
		break;

	case TYPE_BLACKSMAKE:	// ��

		m_Info.col.a -= 0.05f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.fRadius += 0.1f * CManager::GetInstance()->GetSlow()->Get();
		break;

	case TYPE_WALK:	// ��

		m_Info.col.a -= 0.005f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.move.y += -0.1f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.fRadius -= 0.1f * CManager::GetInstance()->GetSlow()->Get();

		if (m_Info.pos.y <= 0.0f)
		{
			m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		else
		{
			D3DXVECTOR3 rot = m_pObjectBilBoard->GetRotation();
			rot.z += D3DX_PI * 0.05f;
			m_pObjectBilBoard->SetRotation(rot);
		}

		break;

	case TYPE_KUNAI:	// ��

		m_Info.col.a -= 0.05f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.fRadius += 0.4f * CManager::GetInstance()->GetSlow()->Get();
		break;

	case TYPE_BUTTON:	// ��

		m_Info.col.a -= 0.05f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.fRadius += (rand() % 10 - 5) * 1.0f * CManager::GetInstance()->GetSlow()->Get();
		break;

	case TYPE_ROTATEDOOR:	// ��

		m_Info.col.a -= 0.02f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.move.x -= m_Info.move.x * 0.045f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.move.y -= m_Info.move.y * 0.025f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.move.z -= m_Info.move.z * 0.045f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.fRadius += 0.45f * CManager::GetInstance()->GetSlow()->Get();

		{
			D3DXVECTOR3 rot = m_pObjectBilBoard->GetRotation();
			rot.z += D3DX_PI * 0.1f;
			m_pObjectBilBoard->SetRotation(rot);
		}

		break;

	case TYPE_ITEMBOX:	// ��

		m_Info.col.a -= 0.02f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.move.x -= m_Info.move.x * 0.05f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.move.y -= m_Info.move.y * 0.025f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.move.z -= m_Info.move.z * 0.05f * CManager::GetInstance()->GetSlow()->Get();

		{
			D3DXVECTOR3 rot = m_pObjectBilBoard->GetRotation();
			rot.z += D3DX_PI * 0.1f;
			m_pObjectBilBoard->SetRotation(rot);
		}

		break;

	case TYPE_ITEMBOXSTAR:	// ��

		m_Info.col.a -= 0.02f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.move.x -= m_Info.move.x * 0.025f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.move.y -= m_Info.move.y * 0.025f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.move.z -= m_Info.move.z * 0.025f * CManager::GetInstance()->GetSlow()->Get();

		{
			D3DXVECTOR3 rot = m_pObjectBilBoard->GetRotation();
			rot.z += D3DX_PI * 0.05f;
			m_pObjectBilBoard->SetRotation(rot);
		}

		break;

	case TYPE_RESULTZITABATA:	// ��

		m_Info.col.a -= 0.015f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.fRadius += 0.1f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.move.y += 0.025f * CManager::GetInstance()->GetSlow()->Get();

		break;

	case TYPE_PULLSTAR:	// ��

		m_Info.col.a -= 0.02f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.move.x -= m_Info.move.x * 0.025f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.move.y -= m_Info.move.y * 0.025f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.move.z -= m_Info.move.z * 0.025f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.fRadius -= 0.75f * CManager::GetInstance()->GetSlow()->Get();

		{
			D3DXVECTOR3 rot = m_pObjectBilBoard->GetRotation();
			rot.z += D3DX_PI * 0.005f;
			m_pObjectBilBoard->SetRotation(rot);
		}

		break;

	case TYPE_PULLNOW:	// ��

		m_Info.col.a -= 0.025f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.fRadius += 0.5f * CManager::GetInstance()->GetSlow()->Get();

		break;

	case TYPE_AIR:	// ��

		m_Info.col.a -= 0.005f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.move.x += m_Info.move.x * 0.005f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.move.y += -0.1f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.move.z += m_Info.move.z * 0.005f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.fRadius -= 0.1f * CManager::GetInstance()->GetSlow()->Get();

		if (m_Info.pos.y <= 0.0f)
		{
			m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		else
		{
			D3DXVECTOR3 rot = m_pObjectBilBoard->GetRotation();
			rot.z += D3DX_PI * 0.05f;
			m_pObjectBilBoard->SetRotation(rot);
		}

		break;

	case TYPE_CATCH:	// ��

		m_Info.col.a -= 0.005f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.move.x += m_Info.move.x * 0.005f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.move.y += -0.1f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.move.z += m_Info.move.z * 0.005f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.fRadius -= 0.1f * CManager::GetInstance()->GetSlow()->Get();

		if (m_Info.pos.y <= 0.0f)
		{
			m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		else
		{
			D3DXVECTOR3 rot = m_pObjectBilBoard->GetRotation();
			rot.z += D3DX_PI * 0.05f;
			m_pObjectBilBoard->SetRotation(rot);
		}

		break;

	case TYPE_JUMP:	// ��

		m_Info.col.a -= 0.0035f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.move.y += -0.3f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.fRadius -= 0.1f * CManager::GetInstance()->GetSlow()->Get();

		if (m_Info.pos.y <= 0.0f)
		{
			m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		else
		{
			D3DXVECTOR3 rot = m_pObjectBilBoard->GetRotation();
			rot.z += D3DX_PI * (rand() % 50 * 0.0001f + 0.065f);
			m_pObjectBilBoard->SetRotation(rot);
		}

		break;

	case TYPE_LAND:	// ��

		m_Info.col.a -= (rand() % 100) * 0.00065f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.move.y += 0.1f * CManager::GetInstance()->GetSlow()->Get();

		break;
	}

	if (m_Info.col.a < 0.0f || m_Info.fRadius < 0.0f)
	{// �l���Ђ�����Ԃ���
		Uninit();

		return;
	}

	InfoSet();
}

//===============================================
// ����
//===============================================
CEffect *CEffect::Create(D3DXVECTOR3 pos, TYPE type)
{
	CEffect *pEffect = NULL;
	CTexture *pTexture = CManager::GetInstance()->GetTexture();	// �e�N�X�`���ւ̃|�C���^

	// �G�t�F�N�g�̐���
	pEffect = new CEffect;

	if (pEffect != NULL)
	{// �����ł����ꍇ

		// ���W�ݒ�
		pEffect->SetPosition(pos);

		// ��ނ̐ݒ�
		pEffect->SetType(type);

		// ���a�ݒ�
		pEffect->RadiusSet();

		// �F�̐ݒ�
		pEffect->ColorSet();

		pEffect->InfoSet();

		// ����������
		pEffect->Init();

		// �e�N�X�`���̊��蓖��
	}
	else
	{// �����Ɏ��s�����ꍇ
		return NULL;
	}

	return pEffect;
}

//===============================================
// ����
//===============================================
CEffect *CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, float fLife, TYPE type)
{
	CEffect *pEffect = NULL;
	CTexture *pTexture = CManager::GetInstance()->GetTexture();	// �e�N�X�`���ւ̃|�C���^

	// �G�t�F�N�g�̐���
	pEffect = new CEffect();

	if (pEffect != NULL)
	{// �����ł����ꍇ

		// ���W�ݒ�
		pEffect->SetPosition(pos);

		// �G�t�F�N�g�̐ݒ�
		pEffect->SetType(type);

		// ���a�ݒ�
		pEffect->m_Info.fRadius = fRadius;

		// �ړ��ʐݒ�
		pEffect->SetMove(move);

		// �T�C�Y�̐ݒ�
		//pEffect->SetSize(pEffect->m_Info.fRadius, pEffect->m_Info.fRadius);

		// �F�̐ݒ�
		pEffect->m_Info.col = col;

		// ����������
		pEffect->Init();

		// �����ݒ�
		pEffect->m_Info.fLife = fLife;

		pEffect->InfoSet();

		// �`����@�ݒ�
		pEffect->DrawSet();
	}
	else
	{// �����Ɏ��s�����ꍇ
		return NULL;
	}

	return pEffect;
}

//===============================================
// �F�ݒ�
//===============================================
void CEffect::ColorSet(void)
{
	// ��ނ��ƂɐF�̐ݒ�
	m_Info.col = COLINFO[m_Info.Type];
	

	if (m_pObjectBilBoard == nullptr) {
		return;
	}

	m_pObjectBilBoard->SetCol(m_Info.col);
}

//===============================================
// �T�C�Y�̐ݒ�
//===============================================
void CEffect::RadiusSet(void)
{
	// ���a�̐ݒ�
	m_Info.fRadius = RADIUSINFO[m_Info.Type];

	if (m_pObjectBilBoard == nullptr) {
		return;
	}

	m_pObjectBilBoard->SetSize(m_Info.fRadius, m_Info.fRadius);
}

//===============================================
// �ړ��ʂ̐ݒ�
//===============================================
void CEffect::SetMove(D3DXVECTOR3 move)
{
	m_Info.move = move;
}

//===============================================
// ����{�ݒ�
//===============================================
void CEffect::InfoSet(void)
{
	if (m_pObjectBilBoard == nullptr) {
		return;
	}

	m_pObjectBilBoard->SetPosition(m_Info.pos);
	m_pObjectBilBoard->SetCol(m_Info.col);
	m_pObjectBilBoard->SetSize(m_Info.fRadius, m_Info.fRadius);
}

//===============================================
// �^�C�v�ʃe�N�X�`��
//===============================================
CTexture::TYPE CEffect::SetTex(TYPE type)
{
	switch (type)
	{
	case TYPE_NONE:
	{

	}
		break;

	case TYPE_SMAKE:
	{
		return CTexture::TYPE_SMOOK;
	}
	break;

	case TYPE_ITEMGET:
	{
		return CTexture::TYPE_ITEMGET_EF;
	}
	break;

	case TYPE_LANDCLEAR:
	{
		return CTexture::TYPE_SMOOK;
	}
	break;

	case TYPE_LANDFAILED:
	{
		return CTexture::TYPE_SMOOK;
	}
	break;

	case TYPE_HIT:
	{
		return CTexture::TYPE_ITEMGET_EF;
	}
	break;
		
	case TYPE_SPEAR:
	{
		return CTexture::TYPE_WOODPOW;
	}
	break;

	case TYPE_WALK:
	{
		return CTexture::TYPE_WALK;
	}
	break;

	case TYPE_KUNAI:
	{
		return CTexture::TYPE_ITEMGET_EF;
	}
	break;

	case TYPE_ROTATEDOOR:
	{
		return CTexture::TYPE_ITEMGET_EF;
	}
	break;

	case TYPE_ITEMBOX:
	{
		return CTexture::TYPE_EFFECT;
	}
	break;

	case TYPE_ITEMBOXSTAR:
	{
		return CTexture::TYPE_ITEMGET_EF;
	}
	break;

	case TYPE_RESULTZITABATA:
	{
		return CTexture::TYPE_SMOOK;
	}
	break;

	case TYPE_PULLSTAR:
	{
		return CTexture::TYPE_ITEMGET_EF;
	}
	break;

	case TYPE_PULLNOW:
	{
		return CTexture::TYPE_SMOOK;
	}
	break;

	case TYPE_AIR:
	{
		return CTexture::TYPE_AIRWOOD;
	}
	break;

	case TYPE_CATCH:
	{
		return CTexture::TYPE_EFFECT;
	}
	break;

	case TYPE_JUMP:
	{
		return CTexture::TYPE_AIRWOOD;
	}
	break;

	case TYPE_LAND:
	{
		return CTexture::TYPE_SMOOK;
	}
	break;
	}

	return CTexture::TYPE();
}

//===============================================
// �`��ݒ�
//===============================================
void CEffect::DrawSet(void)
{
	if (m_pObjectBilBoard == nullptr) {
		return;
	}

	switch (m_Info.Type)
	{
	case TYPE_NONE:
	{

	}
	break;

	case TYPE_SMAKE:
	{
		m_pObjectBilBoard->SetAlphaText(true);
		m_pObjectBilBoard->SetZTest(true);
		m_pObjectBilBoard->SetLighting(true);
		m_pObjectBilBoard->SetFusion(CObjectBillboard::FUSION_ADD);
	}
	break;

	case TYPE_ITEMGET:
	{
		m_pObjectBilBoard->SetAlphaText(true);
		m_pObjectBilBoard->SetZTest(true);
		m_pObjectBilBoard->SetLighting(true);
		m_pObjectBilBoard->SetFusion(CObjectBillboard::FUSION_ADD);
	}
	break;

	case TYPE_LANDCLEAR:
	{
		m_pObjectBilBoard->SetAlphaText(true);
		m_pObjectBilBoard->SetZTest(true);
		m_pObjectBilBoard->SetLighting(true);
		m_pObjectBilBoard->SetFusion(CObjectBillboard::FUSION_ADD);
	}
	break;

	case TYPE_LANDFAILED:
	{
		m_pObjectBilBoard->SetAlphaText(true);
		m_pObjectBilBoard->SetZTest(true);
		m_pObjectBilBoard->SetLighting(true);
		m_pObjectBilBoard->SetFusion(CObjectBillboard::FUSION_ADD);
	}
	break;

	case TYPE_HIT:
	{
		m_pObjectBilBoard->SetAlphaText(true);
		m_pObjectBilBoard->SetZTest(true);
		m_pObjectBilBoard->SetLighting(true);
		m_pObjectBilBoard->SetFusion(CObjectBillboard::FUSION_NORMAL);
	}
	break;

	case TYPE_SPEAR:
	{
		m_pObjectBilBoard->SetAlphaText(true);
		m_pObjectBilBoard->SetZTest(false);
		m_pObjectBilBoard->SetLighting(true);
		m_pObjectBilBoard->SetFusion(CObjectBillboard::FUSION_NORMAL);
	}
	break;

	case TYPE_BLACKSMAKE:
	{
		m_pObjectBilBoard->SetAlphaText(true);
		m_pObjectBilBoard->SetZTest(true);
		m_pObjectBilBoard->SetLighting(true);
		m_pObjectBilBoard->SetFusion(CObjectBillboard::FUSION_MINUS);
	}
	break;

	case TYPE_WALK:
	{
		m_pObjectBilBoard->SetAlphaText(true);
		m_pObjectBilBoard->SetZTest(false);
		m_pObjectBilBoard->SetLighting(true);
		m_pObjectBilBoard->SetFusion(CObjectBillboard::FUSION_NORMAL);
	}
	break;

	case TYPE_KUNAI:
	{
		m_pObjectBilBoard->SetAlphaText(true);
		m_pObjectBilBoard->SetZTest(false);
		m_pObjectBilBoard->SetLighting(true);
		m_pObjectBilBoard->SetFusion(CObjectBillboard::FUSION_NORMAL);
	}
	break;

	case TYPE_ROTATEDOOR:
	{
		m_pObjectBilBoard->SetAlphaText(true);
		m_pObjectBilBoard->SetZTest(false);
		m_pObjectBilBoard->SetLighting(true);
		m_pObjectBilBoard->SetFusion(CObjectBillboard::FUSION_NORMAL);
	}
	break;

	case TYPE_ITEMBOX:
	{
		m_pObjectBilBoard->SetAlphaText(true);
		m_pObjectBilBoard->SetZTest(false);
		m_pObjectBilBoard->SetLighting(true);
		m_pObjectBilBoard->SetFusion(CObjectBillboard::FUSION_ADD);
	}
	break;

	case TYPE_ITEMBOXSTAR:
	{
		m_pObjectBilBoard->SetAlphaText(true);
		m_pObjectBilBoard->SetZTest(false);
		m_pObjectBilBoard->SetLighting(true);
		m_pObjectBilBoard->SetFusion(CObjectBillboard::FUSION_NORMAL);
	}
	break;

	case TYPE_RESULTZITABATA:
	{
		m_pObjectBilBoard->SetAlphaText(true);
		m_pObjectBilBoard->SetZTest(true);
		m_pObjectBilBoard->SetLighting(true);
		m_pObjectBilBoard->SetFusion(CObjectBillboard::FUSION_ADD);
	}
	break;

	case TYPE_PULLSTAR:
	{
		m_pObjectBilBoard->SetAlphaText(true);
		m_pObjectBilBoard->SetZTest(false);
		m_pObjectBilBoard->SetLighting(true);
		m_pObjectBilBoard->SetFusion(CObjectBillboard::FUSION_ADD);
	}
	break;

	case TYPE_PULLNOW:
	{
		m_pObjectBilBoard->SetAlphaText(true);
		m_pObjectBilBoard->SetZTest(false);
		m_pObjectBilBoard->SetLighting(true);
		m_pObjectBilBoard->SetFusion(CObjectBillboard::FUSION_NORMAL);
	}
	break;

	case TYPE_AIR:
	{
		m_pObjectBilBoard->SetAlphaText(true);
		m_pObjectBilBoard->SetZTest(false);
		m_pObjectBilBoard->SetLighting(true);
		m_pObjectBilBoard->SetFusion(CObjectBillboard::FUSION_NORMAL);
	}
	break;

	case TYPE_CATCH:
	{
		m_pObjectBilBoard->SetAlphaText(true);
		m_pObjectBilBoard->SetZTest(false);
		m_pObjectBilBoard->SetLighting(true);
		m_pObjectBilBoard->SetFusion(CObjectBillboard::FUSION_ADD);
	}
	break;

	case TYPE_JUMP:
	{
		m_pObjectBilBoard->SetAlphaText(true);
		m_pObjectBilBoard->SetZTest(false);
		m_pObjectBilBoard->SetLighting(true);
		m_pObjectBilBoard->SetFusion(CObjectBillboard::FUSION_NORMAL);
		m_pObjectBilBoard->SetRotation(D3DXVECTOR3(0.0f, (rand() % 629 - 314) * 0.01f, 0.0f));
	}
	break;

	case TYPE_LAND:
	{
		m_pObjectBilBoard->SetAlphaText(true);
		m_pObjectBilBoard->SetZTest(false);
		m_pObjectBilBoard->SetLighting(true);
		m_pObjectBilBoard->SetFusion(CObjectBillboard::FUSION_ADD);
	}
	break;
	}
}