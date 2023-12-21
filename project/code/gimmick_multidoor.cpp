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
#include "sound.h"

// �������O���
namespace {
	const char* FILENAME = "data\\MODEL\\multidoor.x";	// �g�p���郂�f���t�@�C����
	const D3DXVECTOR3 SETPOS = { 150.0f, 0.0f, 0.0f };		// �����ݒ���W
	const float INERMULTI[CGimmickMultiDoor::STATE_MAX] = {0.75f, 0.15f, 0.0045f};	// �␳�{��
	const D3DXVECTOR3 OPENPOS = { 300.0f, 0.0f, 0.0f };
	const int CLOSECOUNTER = (600);
}

//==========================================================
// �R���X�g���N�^
//==========================================================
CGimmickMultiDoor::CGimmickMultiDoor()
{
	// �l�̃N���A
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++) {
		m_aObject[nCnt].pModel = nullptr;
		m_aObject[nCnt].posDest = { 0.0f, 0.0f, 0.0f };
		m_aObject[nCnt].posOld = { 0.0f, 0.0f, 0.0f };
	}

	m_state = STATE_NEUTRAL;
	m_nStateCnt = 0;
	m_nNumSwitch = 0;
	m_nNumLinkSwitch = 0;
	m_fInerMulti = 0.0f;
	m_ppButton = nullptr;
	m_nActiveSwitch = 0;
	m_nCount = 0;
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
		m_aObject[nCnt].pModel->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI * nCnt, 0.0f));
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

	if (m_ppButton != nullptr) {	// �����O�Ɏg�p����Ă���
		// �O��̐��J��Ԃ�
		for (int nCnt = 0; nCnt < m_nNumSwitch; nCnt++) {

			if (m_ppButton[nCnt] != nullptr) {	// �g�p����Ă���
				m_ppButton[nCnt] = nullptr;
			}
		}
		delete[] m_ppButton;	// �|�C���^�̊J��
		m_ppButton = nullptr;	// �g�p���Ă��Ȃ���Ԃɂ���
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
		}
	}

	if (nActive >= m_nNumLinkSwitch ||
		nActive >= m_nActiveSwitch) {	// �X�C�b�`���K��l������Ă���
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

	// �}�e���A���ݒ�
	SetButtonMaterial(nActive);
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
bool CGimmickMultiDoor::CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, D3DXVECTOR3 &SetPos, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, int nAction, CGimmick **ppGimmick, bool* bLand)
{
	bool bValue = false;
	CXFile *pFile = CManager::GetInstance()->GetModelFile();

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++) {
		if (m_aObject[nCnt].pModel != nullptr) {	// ���f�����g�p����Ă���ꍇ
			D3DXVECTOR3 vtxObjMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 vtxObjMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 ObjPos = D3DXVECTOR3(m_aObject[nCnt].pModel->GetMtx()->_41, m_aObject[nCnt].pModel->GetMtx()->_42, m_aObject[nCnt].pModel->GetMtx()->_43);
			D3DXVECTOR3 ObjRot = GetRotation();

			// �����𔽉f
			int nID = m_aObject[nCnt].pModel->GetId();
			m_aObject[nCnt].pModel->SetRotSize(vtxObjMax,
				vtxObjMin,
				pFile->GetMax(nID),
				pFile->GetMin(nID),
				m_aObject[nCnt].pModel->GetRotation().y);

			if (pos.y + vtxMax.y > ObjPos.y + vtxObjMin.y
				&& pos.y + vtxMin.y <= ObjPos.y + vtxObjMax.y)
			{//�v���C���[�ƃ��f�������������ɂ���
				if (posOld.x + vtxMin.x >= m_aObject[nCnt].posOld.x + vtxObjMax.x
					&& pos.x + vtxMin.x < ObjPos.x + vtxObjMax.x
					&& pos.z + vtxMax.z > ObjPos.z + vtxObjMin.z
					&& pos.z + vtxMin.z < ObjPos.z + vtxObjMax.z)
				{//�E���獶�ɂ߂荞��
					//�ʒu��߂�
					pos.x = ObjPos.x + vtxObjMax.x - vtxMin.x + 0.1f;
					move.x = 0.0f;
				}
				else if (posOld.x + vtxMax.x <= m_aObject[nCnt].posOld.x + vtxObjMin.x
					&& pos.x + vtxMax.x > ObjPos.x + vtxObjMin.x
					&& pos.z + vtxMax.z > ObjPos.z + vtxObjMin.z
					&& pos.z + vtxMin.z < ObjPos.z + vtxObjMax.z)
				{//������E�ɂ߂荞��
					//�ʒu��߂�
					pos.x = ObjPos.x + vtxObjMin.x - vtxMax.x - 0.1f;
					move.x = 0.0f;
				}
				else if (posOld.z + vtxMin.z >= m_aObject[nCnt].posOld.z + vtxObjMax.z
					&& pos.z + vtxMin.z < ObjPos.z + vtxObjMax.z
					&& pos.x + vtxMax.x > ObjPos.x + vtxObjMin.x
					&& pos.x + vtxMin.x < ObjPos.x + vtxObjMax.x)
				{//�������O�ɂ߂荞��
					//�ʒu��߂�
					pos.z = ObjPos.z + vtxObjMax.z - vtxMin.z + 0.1f;
					move.z = 0.0f;
				}
				else if (posOld.z + vtxMax.z <= m_aObject[nCnt].posOld.z + vtxObjMin.z
					&& pos.z + vtxMax.z > ObjPos.z + vtxObjMin.z
					&& pos.x + vtxMax.x > ObjPos.x + vtxObjMin.x
					&& pos.x + vtxMin.x < ObjPos.x + vtxObjMax.x)
				{//��O���牜�ɂ߂荞��t
				 //�ʒu��߂�
					pos.z = ObjPos.z + vtxObjMin.z - vtxMax.z - 0.1f;
					move.z = 0.0f;
				}
			}

			//Y
			if (pos.x + vtxMax.x > ObjPos.x + vtxObjMin.x
				&& pos.x + vtxMin.x < ObjPos.x + vtxObjMax.x
				&& pos.z + vtxMax.z > ObjPos.z + vtxObjMin.z
				&& pos.z + vtxMin.z < ObjPos.z + vtxObjMax.z)
			{//�͈͓��ɂ���
			 //�ォ��̔���
				if (posOld.y + vtxMin.y >= ObjPos.y + vtxObjMax.y
					&& pos.y + vtxMin.y < ObjPos.y + vtxObjMax.y)
				{//�ォ��߂荞��
				 //��ɂ̂���
					pos.y = ObjPos.y + vtxObjMax.y - vtxMin.y;
					move.y = 0.0f;
				}
			}
		}
	}

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

		m_nCount++;

		if (m_nCount == 1)
		{
			CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_OPEN00);
		}

		break;

	case STATE_CLOSE:

		m_nCount = 0;
		m_nStateCnt--;

		if (m_nStateCnt == 299)
		{
			CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_OPEN01);
		}

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
			m_aObject[nCnt].posOld = { m_aObject[nCnt].pModel->GetMtx()->_41 , m_aObject[nCnt].pModel->GetMtx()->_42, m_aObject[nCnt].pModel->GetMtx()->_43};
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
	m_nActiveSwitch = nNum;

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

//==========================================================
// �{�^���g�p����ݒ�
//==========================================================
void CGimmickMultiDoor::SetActiveButton(const int nNum)
{
	m_nActiveSwitch = nNum;

	if (m_nActiveSwitch > m_nNumSwitch) {	// �K�萔���������ꍇ
		m_nActiveSwitch = m_nNumSwitch;
	}
	else if (m_nActiveSwitch < 0) {	// 0����
		m_nActiveSwitch = 0;
	}
}

//==========================================================
// �g�p�{�^�����蓖��
//==========================================================
void CGimmickMultiDoor::IdSetButton(void)
{
	CGimmick *pGimk = CGimmick::GetTop();

	// �Ō�܂ŌJ��Ԃ�
	while (pGimk != nullptr){
		CGimmick *pGimkNext = pGimk->GetNext();

		if (pGimk->GetButton() == nullptr) {	// �{�^���ł͂Ȃ�
			pGimk = pGimkNext;
			continue;
		}

		if (pGimk->GetId() != GetId()) {	// ID���s��v
			pGimk = pGimkNext;
			continue;
		}

		// ���蓖��
		BindButton(pGimk->GetButton());

		pGimk = pGimkNext;
	}
}

//==========================================================
// �O�ϓ����蔻��
//==========================================================
bool CGimmickMultiDoor::CollisionCheckCloss(D3DXVECTOR3 & pos, D3DXVECTOR3 & posOld, D3DXVECTOR3 * posCollisioned)
{
	CXFile* pFile = CManager::GetInstance()->GetModelFile();
	D3DXVECTOR3 vtxObjMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vtxObjMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bool bCollision = false;
	D3DXVECTOR3 posCulcNear = D3DXVECTOR3(FLT_MAX, 0.0f, 0.0f);

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++) 
	{
		if (m_aObject[nCnt].pModel != nullptr) 
		{// ���f�����g�p����Ă���ꍇ
			D3DXVECTOR3 ObjPos = D3DXVECTOR3(m_aObject[nCnt].pModel->GetMtx()->_41, m_aObject[nCnt].pModel->GetMtx()->_42, m_aObject[nCnt].pModel->GetMtx()->_43);

			// �����𔽉f
			int nID = m_aObject[nCnt].pModel->GetId();
			m_aObject[nCnt].pModel->SetRotSize(vtxObjMax,
				vtxObjMin,
				pFile->GetMax(nID),
				pFile->GetMin(nID),
				m_aObject[nCnt].pModel->GetRotation().y);

			D3DXVECTOR3 posPoint[4] =
			{
				D3DXVECTOR3(ObjPos.x + vtxObjMin.x,0.0f,ObjPos.z + vtxObjMin.z),
				D3DXVECTOR3(ObjPos.x + vtxObjMax.x,0.0f,ObjPos.z + vtxObjMin.z),
				D3DXVECTOR3(ObjPos.x + vtxObjMax.x,0.0f,ObjPos.z + vtxObjMax.z),
				D3DXVECTOR3(ObjPos.x + vtxObjMin.x,0.0f,ObjPos.z + vtxObjMax.z)
			};

			D3DXVECTOR3 vecMove, vecLine;
			D3DXVECTOR3 vecToPos, vecToPosOld;
			float fAreaA = 1.0f, fAreaB = 1.1f;

			for (int cnt = 0; cnt < 4; cnt++)
			{
				vecMove = pos - posOld;
				vecLine = posPoint[(cnt + 1) % 4] - posPoint[cnt];	//���E���x�N�g��
				vecToPos = pos - posPoint[cnt];
				vecToPos.y = 0.0f;
				vecToPosOld = posOld - posPoint[cnt];
				vecToPosOld.y = 0.0f;

				//�ʐϋ��߂�
				fAreaA = (vecToPos.z * vecMove.x) - (vecToPos.x * vecMove.z);
				fAreaB = (vecLine.z * vecMove.x) - (vecLine.x * vecMove.z);

				if ((vecLine.z * vecToPosOld.x) - (vecLine.x * vecToPosOld.z) >= 0.0f && (vecLine.z * vecToPos.x) - (vecLine.x * vecToPos.z) < 0.0f)
				{
					if (fAreaA / fAreaB >= 0.0f && fAreaA / fAreaB <= 1.0f)
					{//������
					 //�Փˈʒu�iXZ�̂݁BY��pos�̒l���g�p�j���~������΂�����
						if (posCollisioned != nullptr)
						{//�ق����݂����Ȃ̂ł�����
							float fRate = fAreaA / fAreaB;
							D3DXVECTOR3 posCulc = posPoint[cnt];
							posCulc.x += vecLine.x * fRate;
							posCulc.y = posOld.y;
							posCulc.z += vecLine.z * fRate;

							if (D3DXVec3Length(&(posCulc - posOld)) < D3DXVec3Length(&(posCulcNear - posOld)))
							{
								posCulcNear = posCulc;
							}
						}

						bCollision = true;
					}
				}
			}
		}
	}

	if (bCollision == true)
	{
		*posCollisioned = posCulcNear;
	}

	return bCollision;
}

//==========================================================
// ���͐��ɉ����ĐF�̕ύX
//==========================================================
void CGimmickMultiDoor::SetButtonMaterial(int nPressCnt)
{
	if (m_ppButton == nullptr) {
		return;
	}

	D3DMATERIAL9 mat = {};	// �}�e���A���i�[
	D3DXCOLOR col = D3DXCOLOR(0.1f, 0.1f, 1.0f, 1.0f);
	
	// ������Ă��Ȃ��{�^���̎c��̐��ɍ��킹�ĐF��ς���
	switch (m_nActiveSwitch - nPressCnt) {
	case 1:
		col = D3DXCOLOR(0.35f, 0.3f, 0.05f, 1.0f);
		break;

	case 2:
		col = D3DXCOLOR(0.3f, 0.05f, 0.4f, 1.0f);
		break;

	case 3:
		col = D3DXCOLOR(0.1f, 0.1f, 0.5f, 1.0f);
		break;

	default:
		col = D3DXCOLOR(0.3f, 1.0f, 0.3f, 1.0f);
		break;
	}

	// �F������
	mat.Ambient = col;
	mat.Diffuse = col;
	mat.Emissive = col;

	for (int nCnt = 0; nCnt < m_nNumSwitch; nCnt++) {
		if (m_ppButton[nCnt] == nullptr) {	// �g�p����Ă��Ȃ�
			continue;
		}
		// �}�e���A���ύX
		m_ppButton[nCnt]->SetPressMaterial(mat);
	}
}
