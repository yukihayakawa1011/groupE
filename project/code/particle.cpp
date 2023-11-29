//===============================================
//
// �p�[�e�B�N���̏��� [particle.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "particle.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
#include "texture.h"
#include "billboard.h"

//===============================================
// �}�N����`
//===============================================
#define LIFE	(30)		// ����

//===============================================
// �R���X�g���N�^
//===============================================
CParticle::CParticle()
{

}

//===============================================
// �f�X�g���N�^
//===============================================
CParticle::~CParticle()
{

}

//===============================================
// ����
//===============================================
void CParticle::Create(const D3DXVECTOR3& pos, CEffect::TYPE type)
{
	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	Set(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), type);
}

//===============================================
// ���_���ݒ�
//===============================================
void CParticle::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& move, CEffect::TYPE type)
{
	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	Set(pos, move, type);
}

//===============================================
// �ݒ�
//===============================================
void CParticle::Set(const D3DXVECTOR3& Defpos, const D3DXVECTOR3& Defmove, CEffect::TYPE type)
{
	D3DXVECTOR3 pos = {};
	D3DXVECTOR3 move = {};	// �ړ���
	D3DXCOLOR col = {};	// �F
	CEffect::TYPE ParType = type;
	float fRadius = 0.0f;
	float fLife = 0;
	D3DXVECTOR3 nor;
	float fCol = (float)(rand() % 3) / 10.0f + 0.3f;

	// �ړ��x�N�g�������߂�
	D3DXVec3Normalize(&nor, &Defmove);	// �x�N�g���𐳋K������

	switch (type)
	{
	case CEffect::TYPE_NONE:	// �����Ȃ�

		break;

	case CEffect::TYPE_BULLET:	// �e

			// ���W�̐ݒ�
		pos = Defpos;

		//�ړ��ʂ̐ݒ�
		move.x = sinf((float)(rand() % 629 - 314) / 100.0f) * ((float)(rand() % 100)) * 0.1f;
		move.y = cosf((float)(rand() % 629 - 314) / 100.0f) * ((float)(rand() % 100)) * 0.1f;
		move.z = cosf((float)(rand() % 629 - 314) / 100.0f) * ((float)(rand() % 100)) * 0.1f;

		//�F�̐ݒ�
		col = D3DXCOLOR(fCol, fCol + 0.1f, 1.0f, 1.0f);

		//���a�̐ݒ�
		fRadius = 3.0f;

		//�����̐ݒ�
		fLife = 10.0f;

		CEffect::Create(Defpos, move, col, fRadius, fLife, type);

		break;

	case CEffect::TYPE_EXPLOSION:	// ����

		for (int nCnt = 0; nCnt < 10; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314)  * 0.01f) * ((float)(rand() % 100)) * 0.01f;
			move.y = ((float)(rand() % 100)) * 0.001f;
			move.z = cosf((float)(rand() % 629 - 314)  * 0.01f) * ((float)(rand() % 100)) * 0.01f;

			//�F�̐ݒ�
			col = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);

			//���a�̐ݒ�
			fRadius = 20.0f;

			//�����̐ݒ�
			fLife = 80.0f;

			CEffect::Create(Defpos, move + Defmove * 0.5f, col, fRadius, fLife, type);
		}

		break;

	case CEffect::TYPE_DUST:	// ��

		for (int nCnt = 0; nCnt < 15; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314)  * 0.01f) * ((float)(rand() % 100)) * 0.04f;
			move.y = ((float)(rand() % 100)) * 0.001f;
			move.z = cosf((float)(rand() % 629 - 314)  * 0.01f) * ((float)(rand() % 100)) * 0.04f;

			//�F�̐ݒ�
			col = D3DXCOLOR(0.08f, 0.07f, 0.07f, 1.0f);

			//���a�̐ݒ�
			fRadius = 30.0f;

			//�����̐ݒ�
			fLife = 100.0f;

			CEffect::Create(Defpos, move + Defmove * 0.5f, col, fRadius, fLife, type);
		}

		break;

	case CEffect::TYPE_SHWBULLET:	// �e
	{
		for (int nCnt = 0; nCnt < 1; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			fCol = (float)(rand() % 3) * 0.05f + 0.0f;

			//�ړ��ʂ̐ݒ�
			move.x = -sinf(Defmove.y + -D3DX_PI * 0.1f + D3DX_PI * 0.2f * ((rand() % 10) * 0.1f)) * 1.5f;
			move.y = rand() % 300 * 0.01f;
			move.z = -cosf(Defmove.y + -D3DX_PI * 0.1f + D3DX_PI * 0.2f * ((rand() % 10) * 0.1f)) * 1.5f;

			//�F�̐ݒ�
			col = D3DXCOLOR(0.5f - fCol, 0.5f - fCol, 0.0f, 1.0f);

			//���a�̐ݒ�
			fRadius = 8.0f;

			//�����̐ݒ�
			fLife = 100.0f;

			
			ParType = CEffect::TYPE_SHWBULLET;

			CEffect *p = CEffect::Create(Defpos, move, col, fRadius, fLife, ParType);
			p->GetObj()->SetFusion(CObjectBillboard::FUSION_ADD);
		}
	}
		break;

	case CEffect::TYPE_SWEAT:	// ��

		fCol = (float)(rand() % 3) / 10.0f + 0.3f;

		for (int nCnt = 0; nCnt < 1; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			pos.x += (float)(rand() % 21 - 10);
			pos.z += (float)(rand() % 21 - 10);

			//�ړ��ʂ̐ݒ�
			move.x = -sinf(Defmove.y + -D3DX_PI * 0.1f + D3DX_PI * 0.2f * ((rand() % 10) * 0.1f)) * 0.5f;
			move.y = rand() % 300 * 0.01f;
			move.z = -cosf(Defmove.y + -D3DX_PI * 0.1f + D3DX_PI * 0.2f * ((rand() % 10) * 0.1f)) * 0.5f;

			//�F�̐ݒ�
			col = D3DXCOLOR(fCol + 0.0f, fCol + 0.0f, fCol + 0.0f, 1.0f);

			//���a�̐ݒ�
			fRadius = 10.0f;

			//�����̐ݒ�
			fLife = 60.0f;

			CEffect *p = CEffect::Create(pos, move, col, fRadius, fLife, type);
			p->GetObj()->SetFusion(CObjectBillboard::FUSION_ADD);
		}

		break;

	case CEffect::TYPE_HEAT:	// ���C

		fCol = (float)(rand() % 3) / 10.0f + 0.3f;

		for (int nCnt = 0; nCnt < 1; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			pos.x += (float)(rand() % 21 - 10);
			pos.z += (float)(rand() % 21 - 10);

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314) / 100.0f) * ((float)(rand() % 100)) * 0.002f;
			move.y = rand() % 100 * 0.005f;
			move.z = cosf((float)(rand() % 629 - 314) / 100.0f) * ((float)(rand() % 100)) * 0.002f;
			//�F�̐ݒ�
			col = D3DXCOLOR(fCol + 0.5f, fCol + 0.5f, fCol + 0.5f, 1.0f);

			//���a�̐ݒ�
			fRadius = 10.0f;

			//�����̐ݒ�
			fLife = 100.0f;

			CEffect::Create(pos, move, col, fRadius, fLife, type);
		}

		break;

	case CEffect::TYPE_JUMP:	// �W�����v

		for (int nCnt = 0; nCnt < 10; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314)  * 0.01f) * ((float)(rand() % 100)) * 0.04f;
			move.y = -0.01f;
			move.z = cosf((float)(rand() % 629 - 314)  * 0.01f) * ((float)(rand() % 100)) * 0.04f;

			// �ړ��x�N�g�������߂�
			D3DXVec3Normalize(&nor, &move);	// �x�N�g���𐳋K������

			pos += nor * 100.0f;
			pos.y = Defpos.y;

			//�F�̐ݒ�
			col = D3DXCOLOR(0.08f, 0.07f, 0.07f, 1.0f);

			//���a�̐ݒ�
			fRadius = 20.0f;

			//�����̐ݒ�
			fLife = 100.0f;

			CEffect::Create(pos, move + Defmove * 0.5f, col, fRadius, fLife, type);
		}

		break;

	case CEffect::TYPE_SWAP:	// �W�����v�̐�

		for (int nCnt = 0; nCnt < 20; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314)  * 0.01f) * ((float)(rand() % 100)) * 0.04f;
			move.z = cosf((float)(rand() % 629 - 314)  * 0.01f) * ((float)(rand() % 100)) * 0.04f;

			// �ړ��x�N�g�������߂�
			D3DXVec3Normalize(&nor, &move);	// �x�N�g���𐳋K������

			pos += nor * 100.0f;
			pos.y = Defpos.y;

			move = Defmove;

			//�F�̐ݒ�
			col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);

			//���a�̐ݒ�
			fRadius = 5.0f;

			//�����̐ݒ�
			fLife = 100.0f;

			CEffect *pEffect = CEffect::Create(pos, move, col, fRadius, fLife, type);

			pEffect->GetObj()->SetSize(fRadius, 50.0f);
		}

		break;

	case CEffect::TYPE_BALEXPLOSION:	// ���D����

		for (int nCnt = 0; nCnt < 30; nCnt++)
		{
			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.025f;
			move.y = ((float)(rand() % 50)) * 0.025f;
			move.z = cosf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.025f;

			//�F�̐ݒ�
			col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//���a�̐ݒ�
			fRadius = 15.0f;

			//�����̐ݒ�
			fLife = 100.0f + nCnt * 3;

			CEffect *p = CEffect::Create(Defpos + move, move, col, fRadius, fLife, CEffect::TYPE_BUBBLE);
			p->GetObj()->SetFusion(CObjectBillboard::FUSION_NORMAL);
			p->GetObj()->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\balloon.png"));
		}

		break;

	case CEffect::TYPE_SMAKE:	// ��

		for (int nCnt = 0; nCnt < 10; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.04f;
			move.y = ((float)(rand() % 50)) * 0.1f;
			move.z = cosf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.04f;

			//�F�̐ݒ�
			col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

			//���a�̐ݒ�
			fRadius = 55.0f;

			//�����̐ݒ�
			fLife = 75.0f;

			CEffect::Create(Defpos + move, move, col, fRadius, fLife, type);
		}

		break;

	case CEffect::TYPE_BUBBLE:	// ��
	{
		//�ړ��ʂ̐ݒ�
		move.x = sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.0015f;
		move.y = ((float)(rand() % 50)) * 0.025f;
		move.z = cosf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.0015f;

		//�F�̐ݒ�
		col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//���a�̐ݒ�
		fRadius = 15.0f;

		//�����̐ݒ�
		fLife = 200.0f;

		CEffect *p = CEffect::Create(Defpos + move, move, col, fRadius, fLife, type);
		p->GetObj()->SetFusion(CObjectBillboard::FUSION_NORMAL);
		p->GetObj()->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\balloon.png"));
	}
		break;

	case CEffect::TYPE_HEATHAZE:	// ��

			// ���W�̐ݒ�
		pos = Defpos;

		//�ړ��ʂ̐ݒ�
		move.x = sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.04f;
		move.y = ((float)(rand() % 50)) * 0.075f;
		move.z = cosf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.04f;

		//�F�̐ݒ�
		col = D3DXCOLOR(0.45f, 0.2f, 0.2f, 0.11f);

		//���a�̐ݒ�
		fRadius = 300.0f;

		//�����̐ݒ�
		fLife = 300.0f;

		//CEffect *pEffect = CEffect::Create(Defpos + move, move, col, fRadius, fLife, type);
		//pEffect->BindTexture(CManager::GetInstance()->GetTexture()->Regist(CTexture::GetFileName(CTexture::TYPE_HEATHAZE)));

		break;
	}
}