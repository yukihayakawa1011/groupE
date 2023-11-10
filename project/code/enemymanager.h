//==========================================================
//
// �G�}�l�[�W�� [enemymanager.h]
// Author : Soma Ishihara
//
//==========================================================
#ifndef _ENEMY_MANAGER_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _ENEMY_MANAGER_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "task.h"

//==========================================================
// �T���v���̃N���X��`
//==========================================================
class CEnemyManager : public CTask
{

public:	// �N�ł��A�N�Z�X�\

	CEnemyManager();	// �R���X�g���N�^(�I�[�o�[���[�h)
	~CEnemyManager();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CEnemyManager *Create(void);

	// �����o�֐�(�擾)

	// �����o�֐�(�ݒ�)

private:	// �����������A�N�Z�X�\

	// �����o�֐�

	// �����o�ϐ�
	int m_nCounterSpawn;	//�X�|�[���J�E���^�[
};

#endif

