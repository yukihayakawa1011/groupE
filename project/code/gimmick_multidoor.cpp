//==========================================================
//
// �M�~�b�N�����鑄 [gimmick_multidoor.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "gimmick_multidoor.h"
#include "model.h"
#include "manager.h"
#include "debugproc.h"
#include "player.h"
#include "Xfile.h"
#include "gimmick_button.h"
#include "input.h"
#include "manager.h"

// �������O���
namespace {
	const char* FILENAME = "data\\MODEL\\multidoor.x";	// �g�p���郂�f���t�@�C����
	const D3DXVECTOR3 SETPOS = { 100.0f, 0.0f, 0.0f };		// �����ݒ���W
	const float INERMULTI[CGimmickMultiDoor::STATE_MAX] = {0.75f, 0.15f, 0.01f};	// �␳�{��
	const D3DXVECTOR3 OPENPOS = { 300.0f, 0.0f, 0.0f };
	const int CLOSECOUNTER = (300);
}

//==========================================================
// �R���X�g���N�^
//==========================================================
CGimmickMultiDoor::CGimmickMultiDoor()
{
	// �l�̃N���A
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++) {
		m_aObject[nCnt].pModel = nullptr;
	}

	m_state = STATE_NEUTRAL;
	m_nStateCnt = 0;
	m_nNumSwitch = 0;
	m_nNumLinkSwitch = 0;
	m_fInerMulti = 0.0f;
	m_ppButton = nullptr;
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CGimmickMultiDoor::~CGimmickMultiDoor()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CGimmickMultiDoor::Init(void)
{
	// ���f���̐���
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++) {
		m_aObject[nCnt].pModel = CModel::Create(FILENAME);
		m_aObject[nCnt].pModel->SetParent(GetMtxWorld());
		m_aObject[nCnt].pModel->SetPosition({ SETPOS.x - (SETPOS.x * nCnt * 2), SETPOS.y, SETPOS.z});
	}

	StateSet();

	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CGimmickMultiDoor::Uninit(void)
{
	// ���X�g����폜
	ListOut();

	// �g�p�I�u�W�F�N�g�̍폜
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++) {
		if (m_aObject[nCnt].pModel != nullptr) {	// ���f�����g�p����Ă���ꍇ
			m_aObject[nCnt].pModel->Uninit();
			m_aObject[nCnt].pModel = nullptr;
		}
	}

	// �����[�X
	Release();
}

//==========================================================
// �X�V����
//==========================================================
void CGimmickMultiDoor::Update(void)
{
	// �}�g���b�N�X�ݒ�
	SetMtxWorld();

	// ��ԍX�V
	UpdateState();

	// �␳
	ObjIner();

	int nActive = 0;
	// �J�����Ԃ��m�F
	for (int nCnt = 0; nCnt < m_nNumSwitch; nCnt++) {
		if (m_ppButton[nCnt] != nullptr) {	// �g�p����Ă���
			if (m_ppButton[nCnt]->GetState() == CGimmickButton::STATE_PRESS) {
				nActive++;
				continue;
			}
			break;
		}
	}

	if (nActive >= m_nNumLinkSwitch) {	// �X�C�b�`���K��l������Ă���
		m_state = STATE_OPEN;
		StateSet();
	}
	else
	{
		if (m_state == STATE_OPEN) {
			m_state = STATE_CLOSE;
			StateSet();
		}
	}
}

//==========================================================
// ����
//==========================================================
CGimmickMultiDoor *CGimmickMultiDoor::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	CGimmickMultiDoor *pGimmick = nullptr;

	pGimmick = new CGimmickMultiDoor;

	if (pGimmick != nullptr)
	{
		// ����������
		pGimmick->Init();

		// �l�̐ݒ�
		pGimmick->SetPosition(pos);
		pGimmick->SetRotation(rot);
		pGimmick->CGimmick::BindType(TYPE_SPEAR);
	}

	return pGimmick;
}

//==========================================================
// ��ԊǗ�
//==========================================================
void CGimmickMultiDoor::StateSet(void)
{
	// ��Ԃ��Ƃɐݒ�
	switch (m_state) 
	{
	case STATE_NEUTRAL:

		for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++) {
			if (m_aObject[nCnt].pModel != nullptr) {	// ���f�����g�p����Ă���ꍇ
				m_aObject[nCnt].posDest = m_aObject[nCnt].pModel->GetPosition();	// ������Ԃ�ڕW��
			}
		}

		break;

	case STATE_OPEN:

		for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++) {
			if (m_aObject[nCnt].pModel != nullptr) {	// ���f�����g�p����Ă���ꍇ
				m_aObject[nCnt].posDest = { OPENPOS.x - (OPENPOS.x * nCnt * 2), OPENPOS.y, OPENPOS.z };	// �J������Ԃ�ڕW��
			}
		}

		break;

	case STATE_CLOSE:
		
		for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++) {
			if (m_aObject[nCnt].pModel != nullptr) {	// ���f�����g�p����Ă���ꍇ
				m_aObject[nCnt].posDest = m_aObject[nCnt].pModel->GetPosition();	// ������Ԃ�ڕW��
			}
		}

		m_nStateCnt = CLOSECOUNTER;

		break;
	}

	// �␳�{����ݒ�
	m_fInerMulti = INERMULTI[m_state];
}

//==========================================================
// ����m�F
//==========================================================
bool CGimmickMultiDoor::CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, D3DXVECTOR3 &SetPos, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, int nAction, CGimmick **ppGimmick)
{
	D3DXVECTOR3 ObjPos = GetPosition();
	D3DXVECTOR3 ObjRot = GetRotation();
	bool bValue = false;

	return bValue;
}

//==========================================================
// ��Ԃ��Ƃ̍X�V
//==========================================================
void CGimmickMultiDoor::UpdateState(void)
{
	// ��Ԃ��Ƃɐݒ�
	switch (m_state) 
	{
	case STATE_NEUTRAL:

		break;

	case STATE_OPEN:

		break;

	case STATE_CLOSE:

		m_nStateCnt--;

		if (m_nStateCnt < 0) {
			m_state = STATE_NEUTRAL;	// �ҋ@��ԂɕύX
			StateSet();
		}

		break;
	}
}

//==========================================================
// �I�u�W�F�N�g�̕␳�{��
//==========================================================
void CGimmickMultiDoor::ObjIner(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++) {
		if (m_aObject[nCnt].pModel != nullptr) {	// ���f�����g�p����Ă���ꍇ
			D3DXVECTOR3 pos = m_aObject[nCnt].pModel->GetCurrentPosition();
			D3DXVECTOR3 posDiff = m_aObject[nCnt].posDest - pos;
			pos += posDiff * m_fInerMulti;
			m_aObject[nCnt].pModel->SetCurrentPosition(pos);
		}
	}
}

//==========================================================
// �{�^���������N������
//==========================================================
void CGimmickMultiDoor::BindButton(CGimmickButton *pButton)
{
	if(m_ppButton == nullptr){	// �g�p��{�^������������Ă��Ȃ�
		return;
	}

	m_nNumLinkSwitch = 0;

	for (int nCnt = 0; nCnt < m_nNumSwitch; nCnt++) {
		if (m_ppButton[nCnt] != nullptr) {	// �g�p����Ă���
			m_nNumLinkSwitch++;
			continue;
		}

		m_ppButton[nCnt] = pButton;
		m_nNumLinkSwitch++;
		break;
	}
}

//==========================================================
// �{�^���g�p����ݒ�
//==========================================================
void CGimmickMultiDoor::SetNumButton(const int nNum)
{
	CGimmickButton **ppButtonOld = m_ppButton;
	int nNumOld = m_nNumSwitch;

	if (m_ppButton != nullptr) {	// ���Ɏg�p����Ă���
		m_ppButton = nullptr;
	}

	// �|�C���^�𐶐�
	m_ppButton = new CGimmickButton*[nNum];
	m_nNumSwitch = nNum;

	for (int nCnt = 0; nCnt < m_nNumSwitch; nCnt++) {
		m_ppButton[nCnt] = nullptr;
	}

	if (ppButtonOld != nullptr) {	// �����O�Ɏg�p����Ă���
		// �O��̐��J��Ԃ�
		for (int nCnt = 0; nCnt < nNumOld; nCnt++){
			
			if (ppButtonOld[nCnt] != nullptr) {	// �g�p����Ă���
				BindButton(ppButtonOld[nCnt]);	// �g�p����Ă����{�^�����Đݒ�
			}
		}
		delete[] ppButtonOld;	// �|�C���^�̊J��
		ppButtonOld = nullptr;	// �g�p���Ă��Ȃ���Ԃɂ���
	}
}