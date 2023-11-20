//==========================================================
//
// �J�����}�l�[�W���[ [camera_manager.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "camera_manager.h"
#include "camera.h"

// �ÓI�����o�ϐ��錾
CCameraManager *CCameraManager::m_pInstance = nullptr;	// �C���X�^���X

//==========================================================
// �R���X�g���N�^
//==========================================================
CCameraManager::CCameraManager()
{
	// �l�̃N���A
	m_pCur = nullptr;
	m_pTop = nullptr;
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CCameraManager::~CCameraManager()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CCameraManager::Init(void)
{
	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CCameraManager::Uninit(void)
{

}

//==========================================================
// �X�V����
//==========================================================
void CCameraManager::Update(void)
{

}

//==========================================================
// �C���X�^���X���m��
//==========================================================
CCameraManager *CCameraManager::GetInstance(void)
{
	if (m_pInstance == nullptr) {	// �g���Ă��Ȃ�
		m_pInstance = new CCameraManager;
	}

	return m_pInstance;
}

//==========================================================
// �C���X�^���X�������[�X
//==========================================================
void CCameraManager::Release(void)
{
	if (m_pInstance != nullptr) {	// �C���X�^���X���m�ۂ���Ă���
		m_pInstance->Uninit();
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

//==========================================================
// ���X�g�ɑ}��
//==========================================================
void CCameraManager::ListIn(CCamera *pCamera)
{
	if (m_pTop != nullptr)
	{// �擪�����݂��Ă���ꍇ
		m_pCur->SetNext(pCamera);	// ���ݍŌ���̃I�u�W�F�N�g�̃|�C���^�ɂȂ���
		pCamera->SetPrev(m_pCur);
		m_pCur = pCamera;	// �������g���Ō���ɂȂ�
	}
	else
	{// ���݂��Ȃ��ꍇ
		m_pTop = pCamera;	// �������g���擪�ɂȂ�
		m_pCur = pCamera;	// �������g���Ō���ɂȂ�
	}
}

//==========================================================
// ���X�g����O��
//==========================================================
void CCameraManager::ListOut(CCamera *pCamera)
{
	// ���X�g���玩�����g���폜����
	if (m_pTop == pCamera)
	{// ���g���擪
		if (pCamera->GetNext() != nullptr)
		{// �������݂��Ă���
			m_pTop = pCamera->GetNext();	// ����擪�ɂ���
			m_pTop->SetPrev(nullptr);	// ���̑O�̃|�C���^���o���Ă��Ȃ��悤�ɂ���
		}
		else
		{// ���݂��Ă��Ȃ�
			m_pTop = nullptr;	// �擪���Ȃ���Ԃɂ���
			m_pCur = nullptr;	// �Ō�����Ȃ���Ԃɂ���
		}
	}
	else if (m_pCur == pCamera)
	{// ���g���Ō��
		if (pCamera->GetPrev() != nullptr)
		{// �������݂��Ă���
			m_pCur = pCamera->GetPrev();		// �O���Ō���ɂ���
			m_pCur->SetNext(nullptr);			// �O�̎��̃|�C���^���o���Ă��Ȃ��悤�ɂ���
		}
		else
		{// ���݂��Ă��Ȃ�
			m_pTop = nullptr;	// �擪���Ȃ���Ԃɂ���
			m_pCur = nullptr;	// �Ō�����Ȃ���Ԃɂ���
		}
	}
	else
	{
		if (pCamera->GetNext() != nullptr)
		{
			pCamera->GetNext()->SetPrev(pCamera->GetPrev());	// ���g�̎��ɑO�̃|�C���^���o��������
		}
		if (pCamera->GetPrev() != nullptr)
		{
			pCamera->GetPrev()->SetNext(pCamera->GetNext());	// ���g�̑O�Ɏ��̃|�C���^���o��������
		}
	}
}