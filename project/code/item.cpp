//==========================================================
//
// �A�C�e���̏��� [item.cpp]
// Author : Yuuka Sakuma
//
//==========================================================
#include "item.h"
#include "Xfile.h"
#include "manager.h"
#include "debugproc.h"
#include "texture.h"
#include "model.h"
#include "objectX.h"
#include "meshfield.h"

// �������O���
namespace {
	const char* MODELNAME[CItem::TYPE_MAX] = {	// ���f���t�@�C����
		"data\\MODEL\\coin.x",
		"data\\MODEL\\bracelet00.x",
		"data\\MODEL\\cup00.x",
		"data\\MODEL\\gem00.x",
		"data\\MODEL\\gem01.x",
		"data\\MODEL\\goldbar00.x",
		"data\\MODEL\\jar001.x",
		"data\\MODEL\\kunai.x",
		"data\\MODEL\\ring00.x",
		"data\\MODEL\\scroll00.x",
		"data\\MODEL\\shuriken.x",
	};
}

// �}�N����`
#define COLLISION_SIZE	(75.0f)
#define BOUND_COUNT	(4)
#define GRAVITY	(-1.0f)		//�v���C���[�d��

// �ÓI�����o�ϐ�
CItem *CItem::m_pTop = nullptr;	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
CItem *CItem::m_pCur = nullptr;	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^

//==========================================================
// �R���X�g���N�^
//==========================================================
CItem::CItem()
{
	// �l�̃N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_type = TYPE_COIN;
	m_pPrev = nullptr;
	m_pNext = nullptr;
	m_nBound = 0;

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
CItem::~CItem()
{

}

//==========================================================
// ����
//==========================================================
CItem *CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int type, int nType)
{
	CItem *pObjectX = nullptr;

	// �I�u�W�F�N�gX�̐���
	pObjectX = new CItem;

	if (pObjectX != nullptr)
	{// �����ł����ꍇ
	
		// ���W
		pObjectX->SetPosition(pos);
		//pObjectX->SetOldPos(pos);

		// ����
		pObjectX->SetRotation(rot);

		//// ��ސݒ�
		//pObjectX->SetType(nType);

		// ���
		pObjectX->m_nState = nType;
		// ����������
		pObjectX->Init(type);
	}
	else
	{// �����Ɏ��s�����ꍇ
		return NULL;
	}

	return pObjectX;
}


//==========================================================
// ����������
//==========================================================
HRESULT CItem::Init(void)
{
	return S_OK;
}

//==========================================================
// ����������
//==========================================================
HRESULT CItem::Init(int type)
{
	m_pObject = CModel::Create(MODELNAME[type]);
	m_pObject->SetRotation(m_rot);
	m_type = type;

	//�����蔻�萶��
	CXFile* pFile = CManager::GetInstance()->GetModelFile();
	D3DXVECTOR3 vtxObjMin = pFile->GetMin(m_pObject->GetId());
	m_pos.y = m_pos.y - vtxObjMin.y;

	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CItem::Uninit(void)
{
	// ���X�g���玩�����g���폜����
	if (m_pTop == this)
	{// ���g���擪
		if (m_pNext != NULL)
		{// �������݂��Ă���
			m_pTop = m_pNext;	// ����擪�ɂ���
			m_pNext->m_pPrev = NULL;	// ���̑O�̃|�C���^���o���Ă��Ȃ��悤�ɂ���
		}
		else
		{// ���݂��Ă��Ȃ�
			m_pTop = NULL;	// �擪���Ȃ���Ԃɂ���
			m_pCur = NULL;	// �Ō�����Ȃ���Ԃɂ���
		}
	}
	else if (m_pCur == this)
	{// ���g���Ō��
		if (m_pPrev != NULL)
		{// �������݂��Ă���
			m_pCur = m_pPrev;			// �O���Ō���ɂ���
			m_pPrev->m_pNext = NULL;	// �O�̎��̃|�C���^���o���Ă��Ȃ��悤�ɂ���
		}
		else
		{// ���݂��Ă��Ȃ�
			m_pTop = NULL;	// �擪���Ȃ���Ԃɂ���
			m_pCur = NULL;	// �Ō�����Ȃ���Ԃɂ���
		}
	}
	else
	{
		if (m_pNext != NULL)
		{
			m_pNext->m_pPrev = m_pPrev;	// ���g�̎��ɑO�̃|�C���^���o��������
		}
		if (m_pPrev != NULL)
		{
			m_pPrev->m_pNext = m_pNext;	// ���g�̑O�Ɏ��̃|�C���^���o��������
		}
	}

	if (nullptr != m_pObject) {
		m_pObject->Uninit();
		m_pObject = NULL;
	}

	Release();
}

//==========================================================
// �X�V����
//==========================================================
void CItem::Update(void)
{
	if (m_pObject == nullptr)
	{
		return;
	}

	switch (m_nState)
	{
	case STATE_NORMAL:
	{
		D3DXVECTOR3 pos = m_pos;
		m_posOld = m_pos;
		m_pos = m_pObject->GetPosition();
		m_rot = m_pObject->GetRotation();

		//�p�x�����߂�
		m_fCurve += (D3DX_PI * 0.02f);

		//�ʒu��������
		m_pos.y = m_posOld.y + sinf(m_fCurve) * 1.5f;

		if (m_pObject->GetMtxParent() == nullptr) {
			m_rot.y += sinf(D3DX_PI * 0.02f);
		}
		else {

			if ((m_rot.x >= D3DX_PI * 0.1f && m_rot.x <= D3DX_PI * 0.6f) || (m_rot.x <= -D3DX_PI * 0.4f && m_rot.x >= -D3DX_PI * 0.9f)) {
				m_rot.x += sinf(D3DX_PI * 0.005f);
			}
			else
			{
				m_rot.x += sinf(D3DX_PI * 0.04f);
			}
		}

		m_pos = pos;
	}
		break;

	case STATE_DROP:
	{
		m_posOld = m_pos;

		//�ʒu��������
		m_move.y += GRAVITY;
		m_pos += m_move;
		m_rot.y += sinf(D3DX_PI * (0.02f + (BOUND_COUNT - m_nBound) * 0.01f));

		CXFile* pFile = CManager::GetInstance()->GetModelFile();
		D3DXVECTOR3 vtxObjMin = pFile->GetMin(m_pObject->GetId());

		if (m_pos.y + vtxObjMin.y <= 0.0f)
		{
			m_pos.y = 0.0f - vtxObjMin.y;
			m_move *= 0.4f;
			m_move.y *= -1.0f;
			m_nBound++;

			if (m_nBound >= BOUND_COUNT)
			{
				m_move.y = 0.0f;
				m_nState = STATE_NORMAL;
				m_nBound = 0;
			}
		}
	}
		break;

	case STATE_CRASH:
	{
		m_posOld = m_pos;

		//�ʒu��������
		m_move.x += GRAVITY;
		m_pos += m_move;

		if (m_pos.x <= -900.0f)
		{
			m_pos.x = -900.0f;
			m_move *= 0.8f;
			m_move.x *= -1.0f;
			m_nState = STATE_NORMAL;

			Uninit();
		}
	}

	break;

	case STATE_DOWN:
		m_posOld = m_pos;

		//�ʒu��������
		m_move.y += GRAVITY;
		m_pos += m_move;

		if (m_pos.y <= -700.0f)
		{
			m_pos.y = -700.0f;
			m_move *= 0.8f;
			m_move.y *= -1.0f;
			m_nState = STATE_NORMAL;

			Uninit();
		}
	}
	


	while (1)
	{
		if (m_rot.y > D3DX_PI || m_rot.y < -D3DX_PI)
		{//-3.14�`3.14�͈̔͊O�̏ꍇ
			if (m_rot.y > D3DX_PI)
			{
				m_rot.y += (-D3DX_PI * 2);
			}
			else if (m_rot.y < -D3DX_PI)
			{
				m_rot.y += (D3DX_PI * 2);
			}
		}
		else
		{
			break;
		}
	}

	// �g�p�I�u�W�F�N�g�X�V
	if (nullptr != m_pObject) {
		D3DXVECTOR3 ObjPos = m_pos;
		ObjPos.y += 10.0f;
		m_pObject->SetPosition(ObjPos);
		m_pObject->SetRotation(m_rot);
	}

	// �����蔻��
	if (CManager::GetInstance()->GetMode() != CScene::MODE_RANKING && CManager::GetInstance()->GetMode() != CScene::MODE_TITLE)
	{
		//�����蔻�萶��
		CXFile* pFile = CManager::GetInstance()->GetModelFile();
		int nID = m_pObject->GetId();
		D3DXVECTOR3 vtxObjMax = pFile->GetMax(nID);
		D3DXVECTOR3 vtxObjMin = pFile->GetMin(nID);

		//�I�u�W�F�N�g
		CObjectX::Collision(m_pos, m_posOld, m_move, vtxObjMin, vtxObjMax);
	}
}

////==========================================================
//// �`�揈��
////==========================================================
//void CItem::Draw(void)
//{
//	m_pObject->
//}
//

//==========================================================
// �����蔻��
//==========================================================
CItem *CItem::Collision(D3DXVECTOR3 &pos)
{
	CItem *pObj = m_pTop;	// �擪�擾

	while (pObj != NULL)
	{
		CItem* pObjNext = pObj->m_pNext;
		if (pObj->CollisionCheck(pos))
		{
			if (pObj->m_pObject != nullptr)
			{
				pObj->m_pObject->SetDraw(false);
				return pObj;
			}
		}

		pObj = pObjNext;
	}

	return nullptr;
}

//==========================================================
// ���ꂼ��̃X�R�A�ݒ�
//==========================================================
int CItem::GetEachScore(void)
{
	switch (m_type)
	{
	case TYPE_COIN:
	{
		return 500;
	}

	break;

	case TYPE_BRECELET:
	{
		return 1500;
	}

	break;

	case TYPE_CUP:
	{
		return 1000;
	}

	break;

	case TYPE_GEM00:
	{
		return 2000;
	}

	break;

	case TYPE_GEM01:
	{
		return 2000;
	}

	break;

	case TYPE_GOLDBAR:
	{
		return 3000;
	}

	break;

	case TYPE_JAR:
	{
		return 700;
	}

	break;

	case TYPE_KUNAI:
	{
		return 1300;
	}

	break;

	case TYPE_RING00:
	{
		return 5000;
	}

	break;

	case TYPE_SCROLL:
	{
		return 2500;
	}

	break;

	case TYPE_SHURIKEN:
	{
		return 1000;
	}

	break;

	case TYPE_MAX:
	{

	}

	break;

	}
	return 0;
}

//==========================================================
// �ʔ���`�F�b�N
//==========================================================
bool CItem::CollisionCheck(D3DXVECTOR3 &pos)
{
	D3DXVECTOR3 ObjPos = GetPosition();

	if (m_pObject == nullptr){	// �I�u�W�F�N�g���Ȃ�
		return false;
	}

	if (!m_pObject->GetDraw()){	// �`�悵�Ȃ�
		return false;
	}

	if (m_nState == STATE_DROP)
	{
		return false;
	}

	// �������擾
	float fLength = sqrtf((pos.x - ObjPos.x) * (pos.x - ObjPos.x)
		+ (pos.z - ObjPos.z) * (pos.z - ObjPos.z));

	float fSize = COLLISION_SIZE;

	if (fLength > fSize)
	{// �G��Ă��Ȃ�
		return false;
	}

	if (pos.y >= ObjPos.y - fSize && pos.y <= ObjPos.y + fSize)
	{// �������ꏏ
		return true;
	}
	return false;
}