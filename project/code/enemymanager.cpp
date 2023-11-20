//==========================================================
//
// �G�}�l�[�W�� [enemymanager.cpp]
// Author : Soma Ishihara
//
//==========================================================
#include "enemymanager.h"
#include "enemy.h"

// �}�N����`
#define TEMP_SPAWN_POS	D3DXVECTOR3(-1500.0f,10.0f,300.0f)	//���̃X�|�[���ʒu
#define SPAWN_PULSE		(600)	//�X�|�[���Ԋu
#define MAX_SPAWN_ENEMY	(1)	//�G�������

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
			CEnemy::Create(TEMP_SPAWN_POS, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, NULL);
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