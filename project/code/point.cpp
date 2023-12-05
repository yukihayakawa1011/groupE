//==========================================================
//
// �G�ړ��|�C���g [point.h]
// Author : Soma Ishihara
//
//==========================================================
#include "point.h"

// �O���錾
CPoint *CPoint::m_pTop = nullptr;	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
CPoint *CPoint::m_pCur = nullptr;	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^
int CPoint::m_nNumAll = 0;

//==========================================================
// �R���X�g���N�^
//==========================================================
CPoint::CPoint()
{
	m_pPosPoint = nullptr;
	m_nPointNum = 0;
	m_nRegistPointNum = 0;

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

	m_nNumAll++;
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CPoint::~CPoint()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CPoint::Init(void)
{
	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CPoint::Uninit(void)
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

	//�ʒu�j��
	if (m_pPosPoint != nullptr)
	{
		delete[] m_pPosPoint;
		m_pPosPoint = nullptr;
	}

	Release();
}

//==========================================================
// �X�V����
//==========================================================
void CPoint::Update(void)
{

}

//==========================================================
// ����
//==========================================================
CPoint *CPoint::Create(void)
{
	CPoint *pSample = nullptr;

	pSample = new CPoint;

	if (pSample != nullptr)
	{
		// ����������
		pSample->Init();
	}

	return pSample;
}

//==========================================================
// ���ݒ�
//==========================================================
void CPoint::SetNum(const int nNum)
{
	//���ݒ肵�Ĉʒu�̓��I�m��
	m_nPointNum = nNum;
	if (m_pPosPoint != nullptr)
	{//�Ȃ񂩐�������Ă�
		delete[] m_pPosPoint;	//����
		m_nRegistPointNum = 0;
		
	}
	m_pPosPoint = new D3DXVECTOR3[nNum];	//�m��
}

//==========================================================
// �ʒu�ݒ�
//==========================================================
void CPoint::AddPoint(const D3DXVECTOR3 pos)
{
	if (m_nRegistPointNum < m_nPointNum)
	{//�]�T������
		m_pPosPoint[m_nRegistPointNum] = pos;
		m_nRegistPointNum++;
	}
}
