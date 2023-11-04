//==========================================================
//
// �^�X�N�Ǘ��̏��� [task_manager.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "task_manager.h"
#include "task.h"

CTaskManager *CTaskManager::m_pInstance = NULL;

//==========================================================
// �R���X�g���N�^
//==========================================================
CTaskManager::CTaskManager()
{

}

//==========================================================
// �f�X�g���N�^
//==========================================================
CTaskManager::~CTaskManager()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CTaskManager::Init(void)
{
	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CTaskManager::Uninit(void)
{
	// ���X�g�̑S�p��
	ReleaseAll();
}

//==========================================================
// �X�V����
//==========================================================
void CTaskManager::Update(void)
{
	// ���X�g�̑S�X�V
	UpdateAll();
}

//===============================================
// �S�Ẵ^�X�N�̔p��
//===============================================
void CTaskManager::ReleaseAll(void)
{
	CTask *pTask = m_pTop;	// �擪���擾

	while (pTask != NULL)
	{// �g�p����Ă��Ȃ���Ԃ܂�

		CTask *pTaskNext = pTask->GetNext();	// ���̃I�u�W�F�N�g�ւ̃|�C���^���擾

		// �I������
		pTask->Uninit();

		pTask = pTaskNext;	// ���̃I�u�W�F�N�g�Ɉړ�
	}

	// ���S�t���O���`�F�b�N
	DeathCheck();
}

//===============================================
// �S�Ẵ^�X�N�̍X�V
//===============================================
void CTaskManager::UpdateAll(void)
{
	CTask *pTask = m_pTop;	// �擪���擾

	while (pTask != NULL)
	{// �g�p����Ă��Ȃ���Ԃ܂�

		CTask *pTaskNext = pTask->GetNext();	// ���̃I�u�W�F�N�g�ւ̃|�C���^���擾

		// �X�V����
		pTask->Update();

		pTask = pTaskNext;	// ���̃I�u�W�F�N�g�Ɉړ�
	}

	// ���S�t���O���`�F�b�N
	DeathCheck();
}

//===============================================
// ���S�t���O���`�F�b�N
//===============================================
void CTaskManager::DeathCheck(void)
{
	CTask *pTask = m_pTop;	// �擪���擾

	while (pTask != NULL)
	{// �g�p����Ă��Ȃ���Ԃ܂�
		CTask *pTaskNext = pTask->GetNext();	// ���̃I�u�W�F�N�g�ւ̃|�C���^���擾

		if (pTask->GetDeath() == true)
		{
			// ���X�g���玩�����g���폜����
			if (m_pTop == pTask)
			{// ���g���擪
				if (pTask->GetNext() != NULL)
				{// �������݂��Ă���
					m_pTop = pTask->GetNext();	// ����擪�ɂ���
					m_pTop->SetPrev(NULL);	// ���̑O�̃|�C���^���o���Ă��Ȃ��悤�ɂ���
				}
				else
				{// ���݂��Ă��Ȃ�
					m_pTop = NULL;	// �擪���Ȃ���Ԃɂ���
					m_pCur = NULL;	// �Ō�����Ȃ���Ԃɂ���
				}
			}
			else if (m_pCur == pTask)
			{// ���g���Ō��
				if (pTask->GetPrev() != NULL)
				{// �������݂��Ă���
					m_pCur = pTask->GetPrev();		// �O���Ō���ɂ���
					m_pCur->SetNext(NULL);			// �O�̎��̃|�C���^���o���Ă��Ȃ��悤�ɂ���
				}
				else
				{// ���݂��Ă��Ȃ�
					m_pTop = NULL;	// �擪���Ȃ���Ԃɂ���
					m_pCur = NULL;	// �Ō�����Ȃ���Ԃɂ���
				}
			}
			else
			{
				if (pTask->GetNext() != NULL)
				{
					pTask->GetNext()->SetPrev(pTask->GetPrev());	// ���g�̎��ɑO�̃|�C���^���o��������
				}
				if (pTask->GetPrev() != NULL)
				{
					pTask->GetPrev()->SetNext(pTask->GetNext());	// ���g�̑O�Ɏ��̃|�C���^���o��������
				}
			}

			delete pTask;	// �������̊J��
			pTask = NULL;
		}

		pTask = pTaskNext;	// ���̃I�u�W�F�N�g�Ɉړ�
	}
}

//===============================================
// ���X�g�ɑ}������
//===============================================
void CTaskManager::ListIn(CTask *pTask)
{
	if (m_pTop != NULL)
	{// �擪�����݂��Ă���ꍇ
		m_pCur->SetNext(pTask);	// ���ݍŌ���̃I�u�W�F�N�g�̃|�C���^�ɂȂ���
		pTask->SetPrev(m_pCur);
		m_pCur = pTask;	// �������g���Ō���ɂȂ�
	}
	else
	{// ���݂��Ȃ��ꍇ
		m_pTop = pTask;	// �������g���擪�ɂȂ�
		m_pCur = pTask;	// �������g���Ō���ɂȂ�
	}
}

//===============================================
// �C���X�^���X�̎擾
//===============================================
CTaskManager* CTaskManager::GetInstance()
{
	if (m_pInstance == NULL)
	{
		m_pInstance = new CTaskManager;
	}

	return m_pInstance;
}