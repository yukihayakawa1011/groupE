//==========================================================
//
// �^�X�N�Ǘ��̏��� [task_manager.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _TASK_MANAGER_H_	// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _TASK_MANAGER_H_	// ��d�C���N���[�h�h�~�p�}�N�����`

// �O���錾
class CTask;

//==========================================================
// �T���v���̃N���X��`
//==========================================================
class CTaskManager
{
private:
	CTaskManager();	// �R���X�g���N�^
	~CTaskManager();	// �f�X�g���N�^

public:
	// ���X�g�Ǘ������o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void ListIn(CTask *pTask);

	// �V���O���g��
	static CTaskManager* GetInstance(void);

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void ReleaseAll(void);
	void UpdateAll(void);
	void DeathCheck(void);

	// �����o�ϐ�
	CTask *m_pTop;	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	CTask *m_pCur;	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^
	static CTaskManager *m_pInstance;
};

#endif


