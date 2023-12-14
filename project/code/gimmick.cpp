//==========================================================
//
// �M�~�b�N��� [gimmick.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "gimmick.h"
#include "manager.h"
#include "renderer.h"

// �ÓI�����o�ϐ��錾
CGimmick *CGimmick::m_pTop = nullptr;	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
CGimmick *CGimmick::m_pCur = nullptr;	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^

//==========================================================
// �R���X�g���N�^
//==========================================================
CGimmick::CGimmick()
{
	// �l�̃N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_type = TYPE_NONE;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

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
CGimmick::~CGimmick()
{
	// ���X�g����O��
	ListOut();
}

//==========================================================
// �}�g���b�N�X�̐ݒ�
//==========================================================
void CGimmick::SetMtxWorld(void)
{
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxParent;			// �e�̃}�g���b�N�X���

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
}

//==========================================================
// �����蔻��
//==========================================================
bool CGimmick::Collision(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, D3DXVECTOR3 &SetPos, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, int nAction, CGimmick **ppGimmick, bool* bLand)
{
	CGimmick *pObj = m_pTop;	// �擪�擾
	bool bValue = false;	// ���n�������ۂ�

	while (pObj != nullptr)
	{
		CGimmick *pObjNext = pObj->m_pNext;
		if (pObj->CollisionCheck(pos, posOld, move, SetPos, vtxMin, vtxMax, nAction, ppGimmick, bLand))
		{
			bValue = true;
		}

		pObj = pObjNext;
	}

	return bValue;
}

//==========================================================
// �O�ϓ����蔻��
//==========================================================
bool CGimmick::CollisionCloss(D3DXVECTOR3 & pos, D3DXVECTOR3 & posOld, D3DXVECTOR3 * posCollisioned)
{
	CGimmick *pObj = m_pTop;	// �擪�擾
	D3DXVECTOR3 posNear = D3DXVECTOR3(FLT_MAX, 0.0f, 0.0f);
	bool bValue = false;	// �����񂵂���

	while (pObj != nullptr)
	{
		CGimmick *pObjNext = pObj->m_pNext;
		D3DXVECTOR3 posObjColl = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		if (pObj->CollisionCheckCloss(pos, posOld, &posObjColl))
		{
			float fLength = D3DXVec3Length(&(posOld - posObjColl));

			if (D3DXVec3Length(&(posOld - posNear)) > fLength)
			{
				posNear = posObjColl;
			}

			bValue = true;
		}

		pObj = pObjNext;
	}

	if (posCollisioned != nullptr)
	{
		*posCollisioned = posNear;
	}

	return bValue;
}

//==========================================================
// ���X�g����O��
//==========================================================
void CGimmick::ListOut(void)
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
// �X�C�b�`���I�t�ɂ���
//==========================================================
void CGimmick::SwitchOff(void)
{
	CGimmick *pObj = m_pTop;	// �擪�擾

	while (pObj != nullptr)
	{
		CGimmick *pObjNext = pObj->m_pNext;
		pObj->Switch(false);
		pObj = pObjNext;
	}
}

//==========================================================
// �X�C�b�`���I���ɂ���
//==========================================================
void CGimmick::SwitchOn(void)
{
	CGimmick *pObj = m_pTop;	// �擪�擾

	while (pObj != nullptr)
	{
		CGimmick *pObjNext = pObj->m_pNext;
		pObj->Switch(true);
		pObj = pObjNext;
	}
}

//=========================================================
// �{�^�����I�t�ɂ���
//==========================================================
void CGimmick::Buttonoff(void)
{
	CGimmick *pObj = m_pTop;	// �擪�擾

	while (pObj != nullptr)
	{
		CGimmick *pObjNext = pObj->m_pNext;

		if (pObj->GetButton() != nullptr) {
			pObj->Switch(false);
		}
		pObj = pObjNext;
	}
}
