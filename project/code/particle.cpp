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
	}
}