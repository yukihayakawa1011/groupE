//==========================================================
//
// �G�}�l�[�W�� [enemymanager.cpp]
// Author : Soma Ishihara
//
//==========================================================
#include "enemymanager.h"
#include "enemy.h"
#include "point.h"

// �}�N����`
#define TEMP_SPAWN_POS	D3DXVECTOR3(0.0f,0.0f,0.0f)	//���̃X�|�[���ʒu
#define SPAWN_PULSE		(600)	//�X�|�[���Ԋu
#define MAX_SPAWN_ENEMY	(6)	//�G�������

//==========================================================
// �R���X�g���N�^
//==========================================================
CEnemyManager::CEnemyManager()
{
	// �l�̃N���A
	m_nCounterSpawn = 0;
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CEnemyManager::~CEnemyManager()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CEnemyManager::Init(void)
{
	m_nCounterSpawn = SPAWN_PULSE;
	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CEnemyManager::Uninit(void)
{
	Release();
}

//==========================================================
// �X�V����
//==========================================================
void CEnemyManager::Update(void)
{
	m_nCounterSpawn++;

	if (m_nCounterSpawn >= SPAWN_PULSE)
	{
		m_nCounterSpawn = 0;	//�J�E���^�[���Z�b�g

		if (CEnemy::GetNum() < MAX_SPAWN_ENEMY)
		{
			int nRand = rand() % CPoint::GetNumAll();
			CPoint* pPoint = CPoint::GetTop();
			for (int cnt = 0; cnt < nRand; cnt++)
			{
				pPoint = pPoint->GetNext();
			}
			CEnemy::Create(pPoint->GetPoint(0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, NULL, nRand);
		}
	}
}

//==========================================================
// ����
//==========================================================
CEnemyManager *CEnemyManager::Create(void)
{
	CEnemyManager *pEnemyManager = nullptr;

	pEnemyManager = new CEnemyManager;

	if (pEnemyManager != nullptr)
	{
		// ����������
		pEnemyManager->Init();
	}

	return pEnemyManager;
}