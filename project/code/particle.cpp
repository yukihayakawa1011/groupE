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

	case CEffect::TYPE_SMAKE:	// ��

		for (int nCnt = 0; nCnt < 30; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.09f;
			move.y = ((float)(rand() % 50)) * 0.15f;
			move.z = cosf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.09f;

			//�F�̐ݒ�
			col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

			//���a�̐ݒ�
			fRadius = 100.0f;

			//�����̐ݒ�
			fLife = 500.0f;

			CEffect::Create(Defpos + move, move, col, fRadius, fLife, type);
		}

		break;

	case CEffect::TYPE_ITEMGET:	// ��
	{
		for (int nCnt = 0; nCnt < 30; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.05f;
			move.y = ((float)(rand() % 50)) * 0.2f;
			move.z = cosf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.05f;

			//�F�̐ݒ�
			col = D3DXCOLOR(1.0f, rand() % 10 * 0.1f + 0.0f, 0.0f, 1.0f);

			//���a�̐ݒ�
			fRadius = 10.0f;

			//�����̐ݒ�
			fLife = 500.0f;

			CEffect::Create(Defpos + move, move, col, fRadius, fLife, type);
		}
	}

	case CEffect::TYPE_LANDCLEAR:	// ��
	{
		for (int nCnt = 0; nCnt < 10; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.05f;
			move.y = ((float)(rand() % 50)) * 0.2f;
			move.z = cosf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.05f;

			//�F�̐ݒ�
			col = D3DXCOLOR(0.3f, 0.3f, 0.1f, 1.0f);

			//���a�̐ݒ�
			fRadius = 10.0f;

			//�����̐ݒ�
			fLife = 500.0f;

			CEffect::Create(Defpos + move, move, col, fRadius, fLife, type);
		}
	}

	case CEffect::TYPE_LANDFAILED:	// ��
	{
		for (int nCnt = 0; nCnt < 60; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.1f;
			move.y = 0.0f;
			move.z = cosf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.1f;

			//�F�̐ݒ�
			col = D3DXCOLOR(0.025f, 0.02f, 0.015f, 1.0f);

			//���a�̐ݒ�
			fRadius = 30.0f;

			//�����̐ݒ�
			fLife = 500.0f;

			CEffect::Create(Defpos + move, move, col, fRadius, fLife, type);
		}
	}
	break;

	case CEffect::TYPE_HIT:	// �q�b�g
	{
		for (int nCnt = 0; nCnt < 20; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.15f;
			move.y = sinf((float)(rand() % 629 - 314) * 0.01f) * 4.0f;
			move.z = cosf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.15f;

			//�F�̐ݒ�
			col = D3DXCOLOR(rand() % 5 * 0.1f + 0.6f, 1.0f, 0.3f, 1.0f);

			//���a�̐ݒ�
			fRadius = 7.0f;

			//�����̐ݒ�
			fLife = 500.0f;

			CEffect::Create(Defpos + move, move, col, fRadius, fLife, type);
		}
	}
	break;

	case CEffect::TYPE_SPEAR:	// �q�b�g
	{
		for (int nCnt = 0; nCnt < 30; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.075f;
			move.y = rand() % 100 * 0.01f * 20.0f;
			move.z = cosf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.075f;

			//�F�̐ݒ�
			col = D3DXCOLOR(rand() % 2 * 0.1f + 0.9f, 1.0f, 1.0f, 1.0f);

			//���a�̐ݒ�
			fRadius = 17.0f;

			//�����̐ݒ�
			fLife = 250.0f + rand() % 50;

			CEffect::Create(Defpos + move, move, col, fRadius, fLife, type);
		}
	}
	break;

	case CEffect::TYPE_BLACKSMAKE:	// ��
	{
		for (int nCnt = 0; nCnt < 30; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.09f;
			move.y = ((float)(rand() % 50)) * 0.15f;
			move.z = cosf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.09f;

			//�F�̐ݒ�
			col = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);

			//���a�̐ݒ�
			fRadius = 100.0f;

			//�����̐ݒ�
			fLife = 30.0f;

			CEffect::Create(Defpos + move, move, col, fRadius, fLife, type);
		}
	}
		break;

	case CEffect::TYPE_WALK:	// ��
	{
		for (int nCnt = 0; nCnt < 3; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.015f;
			move.y = rand() % 100 * 0.01f * 5.0f;
			move.z = cosf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.015f;

			//�F�̐ݒ�
			col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);

			//���a�̐ݒ�
			fRadius = 17.0f;

			//�����̐ݒ�
			fLife = 250.0f + rand() % 50;

			CEffect::Create(Defpos + move, move, col, fRadius, fLife, type);
		}
	}
		break;

	case CEffect::TYPE_KUNAI:	// ��
	{
		for (int nCnt = 0; nCnt < 1; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.01f;
			move.y = ((float)(rand() % 50)) * 0.01f;
			move.z = cosf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.01f;

			//�F�̐ݒ�
			col = D3DXCOLOR(0.1f, 0.1f, 0.8f, 1.0f);

			//���a�̐ݒ�
			fRadius = 7.0f;

			//�����̐ݒ�
			fLife = 30.0f;

			CEffect::Create(Defpos + move, move, col, fRadius, fLife, type);
		}
	}
	break;

	case CEffect::TYPE_BUTTON:	// ��
	{
		for (int nCnt = 0; nCnt < 1; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.03f;
			move.y = ((float)(rand() % 50)) * 0.01f;
			move.z = cosf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.03f;

			//�F�̐ݒ�
			col = D3DXCOLOR(0.1f, 0.6f, 0.6f, 0.3f);

			//���a�̐ݒ�
			fRadius = 70.0f;

			//�����̐ݒ�
			fLife = 30.0f + rand() % 10;

			CEffect::Create(Defpos + move, move, col, fRadius, fLife, type);
		}
	}
	break;

	case CEffect::TYPE_ROTATEDOOR:	// ��
	{
		for (int nCnt = 0; nCnt < 20; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.15f;
			move.y = sinf((float)(rand() % 629 - 314) * 0.01f) * 4.0f;
			move.z = cosf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.15f;

			float frand = rand() % 5 * 0.1f;

			//�F�̐ݒ�
			col = D3DXCOLOR(frand + 0.6f, frand + 0.6f, 1.0f, 1.0f);

			//���a�̐ݒ�
			fRadius = 15.0f;

			//�����̐ݒ�
			fLife = 500.0f;

			CEffect::Create(Defpos + move, move, col, fRadius, fLife, type);
		}
	}
	break;

	case CEffect::TYPE_ITEMBOX:	// ��
	{
		for (int nCnt = 0; nCnt < 15; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.05f;
			move.y = ((float)(rand() % 50)) * 0.2f;
			move.z = cosf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.05f;

			float frand = rand() % 2 * 0.1f;

			//�F�̐ݒ�
			col = D3DXCOLOR(frand + 0.9f, frand + 0.9f, 1.0f, 1.0f);

			//���a�̐ݒ�
			fRadius = 6.0f;

			//�����̐ݒ�
			fLife = 500.0f;

			CEffect::Create(Defpos + move, move, col, fRadius, fLife, type);
		}
	}
	break;

	case CEffect::TYPE_ITEMBOXSTAR:	// ��
	{
		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.01f;
			move.y = ((float)(rand() % 3)) * 2.0f;
			move.z = cosf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.01f;

			float frand = rand() % 6 * 0.1f;

			//�F�̐ݒ�
			col = D3DXCOLOR(1.0f, frand, frand * 0.5f, 1.0f);

			//���a�̐ݒ�
			fRadius = 18.0f;

			//�����̐ݒ�
			fLife = 500.0f;

			CEffect::Create(Defpos + move, move, col, fRadius, fLife, type);
		}
	}
	break;

	case CEffect::TYPE_RESULTZITABATA:	// ��
	{
		for (int nCnt = 0; nCnt < 20; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.03f;
			move.y = ((float)(rand() % 2)) * 0.5f;
			move.z = cosf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.03f;

			//�F�̐ݒ�
			col = D3DXCOLOR(0.05f, 0.04f, 0.03f, 1.0f);

			//���a�̐ݒ�
			fRadius = 30.0f;

			//�����̐ݒ�
			fLife = 120.0f;

			CEffect::Create(Defpos + move, move, col, fRadius, fLife, type);
		}
	}
	break;

	case CEffect::TYPE_PULLSTAR:	// ��
	{
		for (int nCnt = 0; nCnt < 1; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.01f;
			move.y = ((float)(rand() % 3 + 1)) * 3.0f;
			move.z = cosf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.01f;

			float frand = rand() % 8 * 0.1f;

			//�F�̐ݒ�
			col = D3DXCOLOR(1.0f, frand + 0.3f, frand, 1.0f);

			//���a�̐ݒ�
			fRadius = 30.0f;

			//�����̐ݒ�
			fLife = 500.0f;

			CEffect::Create(Defpos + move, move, col, fRadius, fLife, type);
		}
	}
	break;

	case CEffect::TYPE_PULLNOW:	// ��
	{
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.01f;
			move.y = ((float)(rand() % 3 + 1)) * 0.1f;
			move.z = cosf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.01f;

			float frand = rand() % 2 * 0.1f;

			//�F�̐ݒ�
			col = D3DXCOLOR(frand + 0.9f, frand + 0.9f, frand + 0.9f, 1.0f);

			//���a�̐ݒ�
			fRadius = 30.0f;

			//�����̐ݒ�
			fLife = 500.0f;

			CEffect::Create(Defpos + move, move, col, fRadius, fLife, type);
		}
	}
	break;

	case CEffect::TYPE_AIR:	// ��
	{
		for (int nCnt = 0; nCnt < 1; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.1f;
			move.y = ((float)(rand() % 3 + 1)) * 2.0f;
			move.z = cosf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.1f;

			float frand = rand() % 2 * 0.1f;

			//�F�̐ݒ�
			col = D3DXCOLOR(frand + 0.9f, frand + 0.9f, frand + 0.9f, 1.0f);

			//���a�̐ݒ�
			fRadius = 15.0f;

			//�����̐ݒ�
			fLife = 500.0f;

			CEffect::Create(Defpos + move, move, col, fRadius, fLife, type);
		}
	}
	break;

	case CEffect::TYPE_CATCH:	// ��
	{
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.03f;
			move.y = ((float)(rand() % 3 + 1)) * 0.95f;
			move.z = cosf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.03f;

			float frand = rand() % 2 * 0.1f;

			//�F�̐ݒ�
			col = D3DXCOLOR(frand + 0.7f, frand + 0.7f, 1.0f, 1.0f);

			//���a�̐ݒ�
			fRadius = 8.0f;

			//�����̐ݒ�
			fLife = 500.0f;

			CEffect::Create(Defpos + move, move, col, fRadius, fLife, type);
		}
	}
	break;

	case CEffect::TYPE_JUMP:	// ��
	{
		for (int nCnt = 0; nCnt < 15; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.055f;
			move.y = rand() % 100 * 0.01f * 11.0f;
			move.z = cosf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.055f;

			//�F�̐ݒ�
			col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);

			//���a�̐ݒ�
			fRadius = 8.0f + rand() % 10;

			//�����̐ݒ�
			fLife = 250.0f + rand() % 50;

			CEffect::Create(Defpos + move, move, col, fRadius, fLife, type);
		}
	}
	break;
	}
}