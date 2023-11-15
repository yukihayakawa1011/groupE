//==========================================================
//
// �S�[�� [goal.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "goal.h"
#include "model.h"
#include "manager.h"
#include "debugproc.h"
#include "player.h"
#include "Xfile.h"
#include "meshfield.h"

// �������O���
namespace {
	const D3DXVECTOR3 SETPOS = { 0.0f, 0.0f, 0.0f };	// �����ݒ���W
	const char *FILENAME = "data\\TEXTURE\\line000.jpg";	// �t�@�C����
	const float HEIGHT = (50.0f);
}

// �ÓI�����o�ϐ��錾
CGoal *CGoal::m_pTop = nullptr;	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
CGoal *CGoal::m_pCur = nullptr;	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^

//==========================================================
// �R���X�g���N�^
//==========================================================
CGoal::CGoal()
{
	// �l�̃N���A
	m_pos = SETPOS;
	m_rot = SETPOS;
	m_pNext = nullptr;
	m_pPrev = nullptr;

	// �������g�����X�g�ɒǉ�
	if (m_pTop != nullptr)
	{// �擪�����݂��Ă���ꍇ
		m_pCur->m_pNext = this;	// ���ݍŌ���̃I�u�W�F�N�g�̃|�C���^�ɂȂ���
		m_pPrev = m_pCur;
		m_pCur = this;	// �������g���Ō���ɂȂ�
	}
	else
	{// ���݂��Ȃ��ꍇ
		m_pTop = this;	// �������g���擪�ɂȂ�
		m_pCur = this;	// �������g���Ō���ɂȂ�
	}
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CGoal::~CGoal()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CGoal::Init(void)
{
	m_pObject = CMeshField::Create(SETPOS, SETPOS, 0.0f, 0.0f, FILENAME);
	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CGoal::Uninit(void)
{
	// ���X�g����폜
	ListOut();

	// �����[�X
	Release();
}

//==========================================================
// �X�V����
//==========================================================
void CGoal::Update(void)
{
	if (m_pObject != nullptr) {
		m_pObject->SetPosition(m_pos);
		m_pObject->SetRotation(m_rot);
	}
}

//==========================================================
// ����
//==========================================================
CGoal *CGoal::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, float fWidth)
{
	CGoal *pGoal = nullptr;

	pGoal = new CGoal;

	if (pGoal != nullptr)
	{
		// ����������
		pGoal->Init();

		// �l�̐ݒ�
		pGoal->SetPosition(pos);
		pGoal->SetRotation(rot);

		if (pGoal->m_pObject != nullptr) {	// �t�B�[���h�̐ݒ�
			pGoal->m_pObject->SetSize(fWidth, HEIGHT);
		}
	}

	return pGoal;
}

//==========================================================
// ���X�g����O��
//==========================================================
void CGoal::ListOut(void)
{
	// ���X�g���玩�����g���폜����
	if (m_pTop == this)
	{// ���g���擪
		if (m_pNext != nullptr)
		{// �������݂��Ă���
			m_pTop = m_pNext;	// ����擪�ɂ���
			m_pNext->m_pPrev = nullptr;	// ���̑O�̃|�C���^���o���Ă��Ȃ��悤�ɂ���
		}
		else
		{// ���݂��Ă��Ȃ�
			m_pTop = nullptr;	// �擪���Ȃ���Ԃɂ���
			m_pCur = nullptr;	// �Ō�����Ȃ���Ԃɂ���
		}
	}
	else if (m_pCur == this)
	{// ���g���Ō��
		if (m_pPrev != nullptr)
		{// �������݂��Ă���
			m_pCur = m_pPrev;			// �O���Ō���ɂ���
			m_pPrev->m_pNext = nullptr;	// �O�̎��̃|�C���^���o���Ă��Ȃ��悤�ɂ���
		}
		else
		{// ���݂��Ă��Ȃ�
			m_pTop = nullptr;	// �擪���Ȃ���Ԃɂ���
			m_pCur = nullptr;	// �Ō�����Ȃ���Ԃɂ���
		}
	}
	else
	{
		if (m_pNext != nullptr)
		{
			m_pNext->m_pPrev = m_pPrev;	// ���g�̎��ɑO�̃|�C���^���o��������
		}
		if (m_pPrev != nullptr)
		{
			m_pPrev->m_pNext = m_pNext;	// ���g�̑O�Ɏ��̃|�C���^���o��������
		}
	}
}

//==========================================================
// �����蔻��
//==========================================================
bool CGoal::Collision(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld)
{
	CGoal *pGl = m_pTop;	// �擪

	while (pGl != nullptr) {
		CGoal *pGlNext = pGl->m_pNext;
		if (pGl->CollisionCheck(pos, posOld)) {	// �ׂ���
			return true;
		}

		pGl = pGlNext;
	}

	return false;
}

//==========================================================
// ����m�F
//==========================================================
bool CGoal::CollisionCheck(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld) 
{
	if (m_pObject == nullptr) {	// �I�u�W�F�N�g���Ȃ�
		return false;
	}

	if ((m_rot.y == SETPOS.y) || (m_rot.y == D3DX_PI) || (m_rot.y == -D3DX_PI)) {	// �����l�Ɠ�������
		if ((pos.x >= m_pos.x + (-m_pObject->GetWidth() * m_pObject->GetNumWidth())) &&
			(pos.x >= m_pos.x + (-m_pObject->GetWidth() * m_pObject->GetNumWidth()))) {	// �͈͓�

			if ((posOld.z >= m_pos.z && pos.z <= m_pos.z) ||
				(pos.z >= m_pos.z && posOld.z <= m_pos.z)) {	// �ׂ���
				return true;
			}
		}
	}
	else   // 90�x��]
	{
		if ((pos.z >= m_pos.z + (-m_pObject->GetWidth() * m_pObject->GetNumWidth())) &&
			(pos.z >= m_pos.z + (-m_pObject->GetWidth() * m_pObject->GetNumWidth()))) {	// �͈͓�

			if ((posOld.x >= m_pos.x && pos.x <= m_pos.x) ||
				(pos.x >= m_pos.x && posOld.x <= m_pos.x)) {	// �ׂ���
				return true;
			}
		}
	}

	return false;
}