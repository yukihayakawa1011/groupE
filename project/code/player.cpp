//===============================================
//
// �v���C���[�̏��� [player.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
#include "camera.h"
#include "Xfile.h"
#include "slow.h"
#include "texture.h"
#include "meshfield.h"
#include "Xfile.h"
#include "meshorbit.h"
#include "game.h"
#include "filter.h"
#include "object2D.h"
#include "meshwall.h"
#include "objectX.h"
#include "sound.h"
#include <assert.h>
#include "billboard.h"
#include "character.h"
#include "motion.h"
#include "sound.h"
#include "waist.h"
#include "model.h"
#include "item.h"
#include "gimmick.h"
#include "gimmick_rotatedoor.h"
#include "enemy.h"
#include "goal.h"
#include "score.h"

//===============================================
// �}�N����`
//===============================================
#define MOVE	(4.0f)		// �ړ���
#define GRAVITY	(-1.0f)		//�v���C���[�d��
#define ROT_MULTI	(0.1f)	// �����␳�{��
#define WIDTH	(20.0f)		// ��
#define HEIGHT	(80.0f)	// ����
#define INER	(0.3f)		// ����
#define STEP_SPEED	(50.0f)
#define STEP_COOLTIME	(90.0f)
#define START_LIFE	(6)	// �����̗�
#define DAMAGE_INTERVAL	(10.0f)
#define DAMAGE_APPEAR	(110.0f)
#define DEATH_INTERVAL	(120.0f)
#define DASH_INTERVAL	(60.0f)
#define SPAWN_INTERVAL	(60.0f)
#define PARTICLE_TIMER	 (5.0f)
#define SHADOW_ALPHA	(0.4f)
#define JUMP	(25.0f)
#define ATK_RANGE	(50.0f)
#define CATCH_RANGE	(100.0f)
#define DROP_CNT	(4)
#define START_COIN	(10)
#define CATCH_LIMIT	(90)
#define CATCH_MOVE	(2.0f)
#define SPEED_DECAY (0.1f)  // �����Ă���A�C�e���̐��ɉ����ăX�s�[�h��������
#define HAND_PARTS	(4)	 // ��̃��f���ԍ�(��납��

// �O���錾
CPlayer *CPlayer::m_pTop = nullptr;	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
CPlayer *CPlayer::m_pCur = nullptr;	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^
int CPlayer::m_nNumCount = 0;

//===============================================
// �R���X�g���N�^
//===============================================
//CPlayer::CPlayer()
//{
//	// �l���N���A����
//	m_nCounterAnim = 0;
//	m_nPatternAnim = 0;
//}

//===============================================
// �R���X�g���N�^(�I�[�o�[���[�h)
//===============================================
CPlayer::CPlayer()
{
	// �l���N���A����
	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fRotMove = 0.0f;
	m_fRotDiff = 0.0f;
	m_fRotDest = 0.0f;
	m_pBody = nullptr;
	m_pLeg = nullptr;
	m_pWaist = nullptr;
	m_Catch.pPlayer = nullptr;
	m_Catch.pGimmick = nullptr;
	m_pScore = nullptr;
	m_Catch.SetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Catch.nMoveCnt = 0;
	m_nLife = 0;
	m_type = TYPE_NONE;
	m_nId = m_nNumCount;
	m_nNumItemCoin = 0;
	m_nNumItemBrecetet = 0;
	m_nNumItemCup = 0;
	m_nNumItemEmerald = 0;
	m_nNumItemDiamond = 0;
	m_nNumItemGold = 0;
	m_nNumItemJar = 0;
	m_nNumItemKunai = 0;
	m_nNumItemRing = 0;
	m_nNumItemScroll = 0;
	m_nNumItemShuriken = 0;
	m_nItemId = CItem::TYPE_COIN;
	m_action = ACTION_NEUTRAL;
	m_bJump = false;
	m_bGoal = false;
	m_nItemCnt = 0;
	m_pMyCamera = nullptr;

	for (int i = 0; i < MAX_ITEM; i++)
	{
		m_aSaveType[i] = 0;
	}
	
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

	m_nNumCount++;
}

//===============================================
// �f�X�g���N�^
//===============================================
CPlayer::~CPlayer()
{
	
}

//===============================================
// ����������
//===============================================
HRESULT CPlayer::Init(void)
{
	// ���̐���
	if (m_pWaist == nullptr)
	{
		m_pWaist = new CWaist;
		m_pWaist->SetParent(&m_Info.mtxWorld);
	}

	// ���̂̐ݒ�
	m_pBody = CCharacter::Create("data\\TXT\\motion_ninjabody.txt");
	m_pBody->SetParent(m_pWaist->GetMtxWorld());

	if (m_pBody->GetMotion() != nullptr)
	{
		// �������[�V�����̐ݒ�
		m_pBody->GetMotion()->InitSet(m_action);
	}

	// �����g�̐ݒ�
	m_pLeg = CCharacter::Create("data\\TXT\\motion_ninjaleg.txt");
	m_pLeg->SetParent(m_pWaist->GetMtxWorld());

	if (m_pLeg->GetMotion() != nullptr)
	{
		// �������[�V�����̐ݒ�
		m_pLeg->GetMotion()->InitSet(m_action);
	}

	// ���̍��������킹��
	if (m_pLeg != nullptr)
	{// �r���g�p����Ă���ꍇ
		CModel *pModel = m_pLeg->GetParts(0);	// ���p�[�c���擾

		if (pModel != nullptr)
		{// �p�[�c�����݂���ꍇ
			D3DXVECTOR3 pos = pModel->GetPosition();	// ���f���̑��Έʒu���擾

			// ������ݒ�
			m_pWaist->SetHeight(pos);

			// ���̃��f���̈ʒu��ύX
			pModel->SetPosition(pos);
		}
	}

	if (m_pScore == nullptr)
	{
		m_pScore = CScore::Create(D3DXVECTOR3(100.0f, 100.0f, 0.0f), 30.0f, 30.0f);
	}
	
	if (m_pScore != nullptr)
	{
		m_pScore->Init();
	}

	m_Info.state = STATE_APPEAR;
	m_action = ACTION_NEUTRAL;
	m_type = TYPE_NONE;
	m_nLife = START_LIFE;
	m_bJump = false;
	m_nItemCnt = 0;

	//m_pScore->AddScore(500 * m_nItemCnt);

	return S_OK;
}

//===============================================
// ����������(�I�[�o�[���[�h)
//===============================================
HRESULT CPlayer::Init(const char *pBodyName, const char *pLegName)
{
	SetMatrix();

	// ���̐���
	if (m_pWaist == nullptr)
	{
		m_pWaist = new CWaist;
		m_pWaist->SetParent(&m_Info.mtxWorld);
		m_pWaist->SetMatrix();
	}

	// ���̂̐ݒ�
	if (pBodyName != nullptr)
	{// �t�@�C���������݂��Ă���
		m_pBody = CCharacter::Create(pBodyName);
		m_pBody->SetParent(m_pWaist->GetMtxWorld());
		m_pBody->SetShadow(true);
		m_pBody->SetDraw();

		if (m_pBody->GetMotion() != nullptr)
		{
			// �������[�V�����̐ݒ�
			m_pBody->GetMotion()->InitSet(m_action);
		}
	}

	// �����g�̐ݒ�
	if (pLegName != nullptr)
	{// �t�@�C���������݂��Ă���
		m_pLeg = CCharacter::Create(pLegName);
		m_pLeg->SetParent(m_pWaist->GetMtxWorld());
		m_pLeg->SetShadow(true);
		m_pLeg->SetDraw();

		if (m_pLeg->GetMotion() != nullptr)
		{
			// �������[�V�����̐ݒ�
			m_pLeg->GetMotion()->InitSet(m_action);
		}
	}

	// ���̍��������킹��
	if (m_pLeg != nullptr)
	{// �r���g�p����Ă���ꍇ
		CModel *pModel = m_pLeg->GetParts(0);	// ���p�[�c���擾

		if (pModel != nullptr)
		{// �p�[�c�����݂���ꍇ
			D3DXVECTOR3 pos = pModel->GetPosition();	// ���f���̑��Έʒu���擾

			// ������ݒ�
			m_pWaist->SetHeight(pos);

			// ���̃��f���̈ʒu��ύX
			pModel->SetPosition(pos);
		}
	}

	/*if (m_pScore == nullptr)
	{
		m_pScore = CScore::Create(D3DXVECTOR3(50.0f + (m_nNumCount - 1) * 500.0f, 50.0f, 0.0f), 30.0f, 30.0f);
	}*/

	if (m_pScore != nullptr)
	{
		m_pScore->Init();
	}

	m_nLife = START_LIFE;
	m_type = TYPE_NONE;
	m_action = ACTION_NEUTRAL;
	m_bJump = false;
	m_nItemCnt = 0;

	//m_pScore->AddScore(500 * m_nItemCnt);

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CPlayer::Uninit(void)
{
	// ���X�g���玩�����g���폜����
	if (m_pTop == this) {// ���g���擪
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
	else if (m_pCur == this) {// ���g���Ō��
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
	else {
		if (m_pNext != nullptr)
		{
			m_pNext->m_pPrev = m_pPrev;	// ���g�̎��ɑO�̃|�C���^���o��������
		}
		if (m_pPrev != nullptr)
		{
			m_pPrev->m_pNext = m_pNext;	// ���g�̑O�Ɏ��̃|�C���^���o��������
		}
	}

	// ���̂̏I��
	if (m_pBody != nullptr) {
		m_pBody->Uninit();
		delete m_pBody;
		m_pBody = nullptr;
	}

	// �����g�̏I��
	if (m_pLeg != nullptr) {
		m_pLeg->Uninit();
		delete m_pLeg;
		m_pLeg = nullptr;
	}

	// ���̔p��
	if (m_pWaist != nullptr){
		delete m_pWaist;
		m_pWaist = nullptr;
	}

	// �X�R�A�̏I��
	if (m_pScore != nullptr) {// �g�p����Ă���ꍇ

		// �I������
		m_pScore->Uninit();

		// �J��
		delete m_pScore;

		// �g�p����Ă��Ȃ���Ԃɂ���
		m_pScore = nullptr;
	}

	// �l�������炷
	m_nNumCount--;

	// �p��
	Release();
}

//===============================================
// �X�V����
//===============================================
void CPlayer::Update(void)
{	
	// �O��̍��W���擾
	m_Info.posOld = GetPosition();

	StateSet();

	if (m_type == TYPE_ACTIVE)
	{

		if (m_Info.state != STATE_SPAWN)
		{
			// �v���C���[����
			Controller();
		}

		// �J�����Ǐ]
		if (m_pMyCamera != nullptr) {
			// �Ǐ]����
			m_pMyCamera->Update();
			m_pMyCamera->Pursue(GetPosition(), GetRotation());
		}

		// �I�����C�����M
		CManager::GetInstance()->GetScene()->SendPosition(m_Info.pos);
		CManager::GetInstance()->GetScene()->SendRotation(m_Info.rot);
		CManager::GetInstance()->GetScene()->SendLife(m_nLife);
	}
	else
	{// ����L�����ł͂Ȃ�
		D3DXVECTOR3 posDest = m_Info.posDiff - m_Info.pos;
		m_Info.pos += posDest * 0.95f;
	}

	CManager::GetInstance()->GetDebugProc()->Print("���� [%f, %f, %f] : ID [ %d]\n", GetRotation().x, GetRotation().y, GetRotation().z, m_nId);
	CManager::GetInstance()->GetDebugProc()->Print("�ʒu [%f, %f, %f]", GetPosition().x, GetPosition().y, GetPosition().z);
	CManager::GetInstance()->GetDebugProc()->Print("�̗� [ %d ] : ��� [ %d ] : �A�C�e�������� [ %d ] : �I�𒆂̃A�C�e�� [ %d ]\n", m_nLife, m_Info.state, m_nItemCnt, m_nItemId);

	// �}�g���b�N�X�ݒ�
	if (m_Info.state == STATE_CATCH) {	// �L���b�`����Ă���ꍇ!!!!
		SetCatchMatrix();
	}
	else {	// ����ȊO!!!!!!
		SetMatrix();
	}

	BodySet();

	if (m_nLife <= 0) {	// �̗͂�0
		m_Info.state = STATE_DEATH;
	}

	if (m_pLeg != nullptr)
	{// �g�p����Ă���ꍇ
		CModel *pModel = m_pLeg->GetParts(0);

		pModel->SetCurrentPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
}

//===============================================
// ����
//===============================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, const char *pBodyName, const char *pLegName)
{
	CPlayer *pPlayer = nullptr;

	// �I�u�W�F�N�g2D�̐���
	pPlayer = new CPlayer();

	if (nullptr != pPlayer)
	{// �����ł����ꍇ
		// ����������
		pPlayer->Init(pBodyName, pLegName);

		// ���W�ݒ�
		pPlayer->SetPosition(pos);

		// �����ݒ�
		pPlayer->SetRotation(rot);

		pPlayer->m_fRotDest = rot.y;

		// �ړ��ʐݒ�
		pPlayer->SetMove(move);
	}
	else
	{// �����Ɏ��s�����ꍇ
		return nullptr;
	}

	return pPlayer;
}

//===============================================
// ���쏈��
//===============================================
void CPlayer::Controller(void)
{
	D3DXVECTOR3 pos = GetPosition();	// ���W���擾
	D3DXVECTOR3 rot = GetRotation();	// �������擾
	m_fRotMove = rot.y;	//���݂̌������擾

	// ���쏈��
	if(m_action != ACTION_DAMAGE){	// �_���[�W���A�N�V���������Ă��Ȃ�
		if (m_Info.state != STATE_DEATH) {	// ���S���Ă��Ȃ�
			Move();		// �ړ�
			Rotation();	// ��]
			Jump();		// �W�����v
			Attack();	// �U��
			Catch();		// �͂�
			Throw();		// ������
			SelectItem();   // �̂Ă�A�C�e���I��
		}
	}

	MotionSet();	// ���[�V�����ݒ�

	pos = GetPosition();	// ���W���擾

	float fGravity = GRAVITY * CManager::GetInstance()->GetSlow()->Get();
	m_Info.move.y += fGravity;
	pos.y += m_Info.move.y * CManager::GetInstance()->GetSlow()->Get();

	m_Info.move.x += (0.0f - m_Info.move.x) * INER;	//x���W
	m_Info.move.z += (0.0f - m_Info.move.z) * INER;	//x���W

	pos.x += m_Info.move.x * CManager::GetInstance()->GetSlow()->Get();
	pos.z += m_Info.move.z * CManager::GetInstance()->GetSlow()->Get();

	// ����
	Adjust();

	m_Info.pos = pos;
	m_bJump = true;	// �W�����v��ԃ��Z�b�g

	// �N���Ƃ̓����蔻��
	float fHeight = CMeshField::GetHeight(m_Info.pos);
	if (m_Info.pos.y <= fHeight)
	{
		m_Info.pos.y = fHeight;
		m_bJump = false;
	}

	// �I�u�W�F�N�g�Ƃ̓����蔻��
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(50.0f, 0.0f, 50.0f);
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);
	if (CObjectX::Collision(m_Info.pos, m_Info.posOld, m_Info.move, vtxMin, vtxMax, 0.3f))
	{
		m_bJump = false;
	}

	// �A�C�e���Ƃ̓����蔻��
	CItem *pItem = CItem::Collision(m_Info.pos);

	if (pItem != nullptr) {
		m_nItemCnt++;
		if (m_pScore != nullptr)
		{
			m_pScore->AddScore(pItem->GetEachScore());
		}

		for (int i = 0; i < MAX_ITEM; i++)
		{
			if (m_aSaveType[i] == 0)
			{
				m_aSaveType[i] = pItem->GetType();

				break;
			}
		}

		AddItemCount(pItem->GetType());

		pItem->Uninit();
	}

	// �M�~�b�N�Ƃ̔���
	if (CGimmick::Collision(m_Info.pos, m_Info.posOld, m_Info.move, m_Catch.SetPos, vtxMin, vtxMax, m_action, &m_Catch.pGimmick)) {
		Damage(1);
	}

	// �S�[���Ƃ̔���
	if (!m_bGoal) {	// �܂��S�[�����Ă��Ȃ�
		if (CGoal::Collision(m_Info.pos, m_Info.posOld)) {	// �S�[�����ׂ���
			m_bGoal = true;
		}
	}

	if (m_Catch.pGimmick != nullptr && m_Info.state != STATE_DEATH) {
		m_Info.state = STATE_CATCH;
	}
}

//===============================================
// �ړ�
//===============================================
void CPlayer::Move(void)
{
	CInputKeyboard *pInputKey = CManager::GetInstance()->GetInputKeyboard();	// �L�[�{�[�h�̃|�C���^
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();

	// ���͑��u�m�F
	if (nullptr == pInputKey){
		return;
	}

	// ���͑��u�m�F
	if (nullptr == pInputPad){
		return;
	}

	//�v���C���[�̍X�V
	MoveController();
}

//===============================================
// ��]
//===============================================
void CPlayer::Rotation(void)
{
	CCamera *pCamera = m_pMyCamera;		// �J�����̃|�C���^

	if (m_pMyCamera == nullptr) {
		pCamera = CManager::GetInstance()->GetCamera();
	}

	D3DXVECTOR3 CamRot = pCamera->GetRotation();	// �J�����̊p�x
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();

	// ���͑��u�m�F
	if (nullptr == pInputPad){
		return;
	}

	if (m_nId < 0 || m_nId >= PLAYER_MAX)
	{// �R���g���[���[���I�[�o�[
		return;
	}

	if (!pInputPad->GetStickPress(m_nId, CInputPad::BUTTON_LEFT_X, 0.1f, CInputPad::STICK_PLUS) && 
		!pInputPad->GetStickPress(m_nId, CInputPad::BUTTON_LEFT_X, 0.1f, CInputPad::STICK_MINUS) &&
		!pInputPad->GetStickPress(m_nId, CInputPad::BUTTON_LEFT_Y, 0.1f, CInputPad::STICK_PLUS) &&
		!pInputPad->GetStickPress(m_nId, CInputPad::BUTTON_LEFT_Y, 0.1f, CInputPad::STICK_MINUS))
	{// �R���g���[���[���͖���
		KeyBoardRotation();
		return;
	}

	// �R���g���[���[�̓��͕����擾
	/*D3DXVECTOR2 vec;
	vec.y = pInputPad->GetStickAdd(m_nId, CInputPad::BUTTON_LEFT_X, 0.1f, CInputPad::STICK_PLUS);
	vec.x = pInputPad->GetStickAdd(m_nId, CInputPad::BUTTON_LEFT_Y, 0.1f, CInputPad::STICK_PLUS);
	D3DXVec2Normalize(&vec, &vec);
	m_fRotDest = atan2f(vec.y, vec.x);*/
}

//===============================================
// ��]
//===============================================
void CPlayer::KeyBoardRotation(void)
{
	CInputKeyboard *pInputKey = CManager::GetInstance()->GetInputKeyboard();	// �L�[�{�[�h�̃|�C���^

	if (nullptr == pInputKey){
		return;
	}

	if (pInputKey->GetPress(DIK_W))
	{
		if (pInputKey->GetPress(DIK_A))
		{
			m_fRotDest = -D3DX_PI * 0.25f;
		}
		else if (pInputKey->GetPress(DIK_D))
		{
			m_fRotDest = D3DX_PI * 0.25f;
		}
		else
		{
			m_fRotDest = D3DX_PI * 0.0f;
		}
	}
	else if (pInputKey->GetPress(DIK_S))
	{
		if (pInputKey->GetPress(DIK_A))
		{
			m_fRotDest = -D3DX_PI * 0.75f;
		}
		else if (pInputKey->GetPress(DIK_D))
		{
			m_fRotDest = D3DX_PI * 0.75f;
		}
		else
		{
			m_fRotDest = D3DX_PI * 1.0f;
		}
	}
	else if (pInputKey->GetPress(DIK_A))
	{
		m_fRotDest = -D3DX_PI * 0.5f;
	}
	else if (pInputKey->GetPress(DIK_D))
	{
		m_fRotDest = D3DX_PI * 0.5f;
	}
}

//===============================================
// ����
//===============================================
void CPlayer::MoveController(void)
{
	if (m_nId < 0 || m_nId >= PLAYER_MAX)
	{// �R���g���[���[�����[�΁[
		return;
	}

	CCamera *pCamera = m_pMyCamera;		// �J�����̃|�C���^

	if (m_pMyCamera == nullptr) {
		pCamera = CManager::GetInstance()->GetCamera();
	}

	D3DXVECTOR3 CamRot = pCamera->GetRotation();	// �J�����̊p�x
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();
	float fSpeed = MOVE;	// �ړ���

	if (m_Catch.pPlayer != nullptr) {
		fSpeed = CATCH_MOVE;
	}

	m_bMove = false;

	if (pInputPad->GetStickPress(m_nId, CInputPad::BUTTON_LEFT_X, 0.5f, CInputPad::STICK_MINUS) == true)
	{
		if (pInputPad->GetStickPress(m_nId, CInputPad::BUTTON_LEFT_Y, 0.5f, CInputPad::STICK_PLUS))
		{
			m_Info.move.x += cosf(CamRot.y + (-D3DX_PI * 0.75f)) * fSpeed - (m_nItemCnt * SPEED_DECAY);
			m_Info.move.z += sinf(CamRot.y + (-D3DX_PI * 0.75f)) * fSpeed + (m_nItemCnt * SPEED_DECAY);
			m_fRotDest = (-CamRot.y + D3DX_PI * 0.25f);
		}
		else if (pInputPad->GetStickPress(m_nId, CInputPad::BUTTON_LEFT_Y, 0.5f, CInputPad::STICK_MINUS))
		{
			m_Info.move.x += cosf(CamRot.y + (-D3DX_PI * 0.25f)) * fSpeed - (m_nItemCnt * SPEED_DECAY);
			m_Info.move.z += sinf(CamRot.y + (-D3DX_PI * 0.25f)) * fSpeed - (m_nItemCnt * SPEED_DECAY);
			m_fRotDest = (-CamRot.y + -D3DX_PI * 0.25f);
		}
		else
		{
			m_Info.move.x += cosf(CamRot.y + (-D3DX_PI * 0.5f)) * fSpeed - (m_nItemCnt * SPEED_DECAY);
			m_Info.move.z += sinf(CamRot.y + (-D3DX_PI * 0.5f)) * fSpeed;
			m_fRotDest = -CamRot.y;
		}

		// �ړ�������Ԃɂ���
		m_bMove = true;
	}
	else if (pInputPad->GetStickPress(m_nId, CInputPad::BUTTON_LEFT_X, 0.5f, CInputPad::STICK_PLUS) == true)
	{
		if (pInputPad->GetStickPress(m_nId, CInputPad::BUTTON_LEFT_Y, 0.5f, CInputPad::STICK_PLUS))
		{
			m_Info.move.x += cosf(CamRot.y + (D3DX_PI * 0.75f)) * fSpeed + (m_nItemCnt * SPEED_DECAY);
			m_Info.move.z += sinf(CamRot.y + (D3DX_PI * 0.75f)) * fSpeed + (m_nItemCnt * SPEED_DECAY);

			m_fRotDest = (-CamRot.y + D3DX_PI * 0.75f);
		}
		else if (pInputPad->GetStickPress(m_nId, CInputPad::BUTTON_LEFT_Y, 0.5f, CInputPad::STICK_MINUS))
		{
			m_Info.move.x += cosf(CamRot.y + (D3DX_PI * 0.25f)) * fSpeed + (m_nItemCnt * SPEED_DECAY);
			m_Info.move.z += sinf(CamRot.y + (D3DX_PI * 0.25f)) * fSpeed - (m_nItemCnt * SPEED_DECAY);

			m_fRotDest = (-CamRot.y + -D3DX_PI * 0.75f);
		}
		else
		{
			m_Info.move.x += cosf(CamRot.y + (D3DX_PI * 0.5f)) * fSpeed + (m_nItemCnt * SPEED_DECAY);
			m_Info.move.z += sinf(CamRot.y + (D3DX_PI * 0.5f)) * fSpeed;
			m_fRotDest = (-CamRot.y + D3DX_PI * 1.0f);
		}

		// �ړ�������Ԃɂ���
		m_bMove = true;
	}
	else if (pInputPad->GetStickPress(m_nId, CInputPad::BUTTON_LEFT_Y, 0.5f, CInputPad::STICK_PLUS))
	{
		m_Info.move.x += -cosf(CamRot.y) * fSpeed;
		m_Info.move.z += -sinf(CamRot.y) * fSpeed + (m_nItemCnt * SPEED_DECAY);
		m_fRotDest = (-CamRot.y + D3DX_PI * 0.5f);

		// �ړ�������Ԃɂ���
		m_bMove = true;

	}
	else if (pInputPad->GetStickPress(m_nId, CInputPad::BUTTON_LEFT_Y, 0.5f, CInputPad::STICK_MINUS))
	{
		m_Info.move.x += cosf(CamRot.y) * fSpeed;
		m_Info.move.z += sinf(CamRot.y) * fSpeed - (m_nItemCnt * SPEED_DECAY);
		m_fRotDest = (-CamRot.y + -D3DX_PI * 0.5f);

		// �ړ�������Ԃɂ���
		m_bMove = true;
	}
}

//===============================================
// �W�����v
//===============================================
void CPlayer::Jump(void)
{
	if (m_nId < 0 || m_nId >= PLAYER_MAX)
	{// �R���g���[���[���I�[�o�[
		return;
	}

	if (m_Catch.pPlayer != nullptr && m_Info.state != STATE_CATCH)
	{
		return;
	}

	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();

	// ����
	if (pInputPad->GetTrigger(CInputPad::BUTTON_B, m_nId))
	{
		if (m_bJump == false)
		{// �W�����v���Ă��Ȃ��ꍇ
			m_bJump = true;

			if(m_Catch.pPlayer != nullptr)
			{
				m_Info.move.y = JUMP * 0.5f;
			}
			else
			{
				m_Info.move.y = JUMP;
			}

		}
	}
}

//===============================================
// ����
//===============================================
void CPlayer::Adjust(void)
{
	while (1)
	{
		if (m_fRotDest > D3DX_PI || m_fRotDest < -D3DX_PI)
		{//-3.14�`3.14�͈̔͊O�̏ꍇ
			if (m_fRotDest > D3DX_PI)
			{
				m_fRotDest += (-D3DX_PI * 2);
			}
			else if (m_fRotDest < -D3DX_PI)
			{
				m_fRotDest += (D3DX_PI * 2);
			}
		}
		else
		{
			break;
		}
	}

	m_fRotDiff = m_fRotDest - m_fRotMove;	//�ڕW�܂ł̈ړ������̍���

	while (1)
	{
		if (m_fRotDiff > D3DX_PI || m_fRotDiff < -D3DX_PI)
		{//-3.14�`3.14�͈̔͊O�̏ꍇ
			if (m_fRotDiff > D3DX_PI)
			{
				m_fRotDiff += (-D3DX_PI * 2);
			}
			else if (m_fRotDiff < -D3DX_PI)
			{
				m_fRotDiff += (D3DX_PI * 2);
			}
		}
		else
		{
			break;
		}
	}

	m_Info.rot.y += m_fRotDiff * ROT_MULTI;

	while (1)
	{
		if (m_Info.rot.y > D3DX_PI || m_Info.rot.y < -D3DX_PI)
		{//-3.14�`3.14�͈̔͊O�̏ꍇ
			if (m_Info.rot.y > D3DX_PI)
			{
				m_Info.rot.y += (-D3DX_PI * 2);
			}
			else if (m_Info.rot.y < -D3DX_PI)
			{
				m_Info.rot.y += (D3DX_PI * 2);
			}
		}
		else
		{
			break;
		}
	}
}

//===============================================
// ��ԊǗ�
//===============================================
void CPlayer::StateSet(void)
{
	float fSlawMul = CManager::GetInstance()->GetSlow()->Get();
	switch (m_Info.state)
	{
	case STATE_APPEAR:
	{
		m_Info.fStateCounter -= fSlawMul;

		if (m_Info.fStateCounter <= 0.0f)
		{
			m_Info.fStateCounter = 0.0f;
			m_Info.state = STATE_NORMAL;
		}
	}
		break;

	case STATE_NORMAL:
	{

	}
		break;

	case STATE_DAMAGE:
	{
		m_Info.fStateCounter -= fSlawMul;

		if (m_Info.fStateCounter <= 0.0f)
		{
			m_Info.fStateCounter = DAMAGE_APPEAR;
			m_Info.state = STATE_APPEAR;
		}
	}
		break;

	case STATE_DEATH:
	{
		m_Info.fStateCounter -= fSlawMul;

		if (m_Info.fStateCounter <= 0.0f)
		{
			m_Info.fStateCounter = DAMAGE_APPEAR;
			m_Info.state = STATE_SPAWN;
			m_nLife = START_LIFE;

			if (m_pBody != nullptr) {
				m_pBody->SetDraw();
			}

			if (m_pLeg != nullptr) {
				m_pLeg->SetDraw();
			}
		}
	}
		break;

	case STATE_SPAWN:
	{
		m_Info.fStateCounter -= fSlawMul;

		if (m_Info.fStateCounter <= 0.0f)
		{
			m_Info.fStateCounter = SPAWN_INTERVAL;
			m_Info.state = STATE_APPEAR;
		}
	}
		break;

	case STATE_CATCH:
	{

	}
		break;
	}
}

//===============================================
// �_���[�W����
//===============================================
void CPlayer::Damage(int nDamage) 
{ 
	if (m_Info.state != STATE_NORMAL)
	{// �_���[�W��H���Ȃ�
		if (m_Info.state != STATE_CATCH)
		{
			return;
		}
	}

	int nOldLife = m_nLife;
	m_nLife -= nDamage;

	if (m_nLife < 0)
	{
		m_nLife = 0;
	}

	Drop(DROP_CNT * (nOldLife - m_nLife));

	if (m_nLife != nOldLife)
	{
		m_Info.fStateCounter = DAMAGE_INTERVAL;
		m_Info.state = STATE_DAMAGE;

		if (m_nLife <= 0)
		{
			m_nLife = 0;
			m_Info.state = STATE_DEATH;
			m_Info.fStateCounter = DAMAGE_APPEAR;

			if (m_pBody != nullptr){
				m_pBody->SetDraw(false);
			}

			if (m_pLeg != nullptr){
				m_pLeg->SetDraw(false);
			}

			DropAll();
		}
	}

	if (m_Catch.pPlayer != nullptr) {	// ���̃v���C���[�������Ă���
		m_Catch.pPlayer->m_Info.state = STATE_NORMAL;
		m_Catch.pPlayer->m_Catch.pPlayer = nullptr;
		m_Catch.pPlayer = nullptr;
	}
}

//===============================================
// �̗͐ݒ�
//===============================================
void CPlayer::SetLife(int nLife)
{
	m_nLife = nLife;

	if (m_nLife < 0)
	{
		m_nLife = 0;
	}
}

//===============================================
// �̗͐ݒ�
//===============================================
void CPlayer::SetType(TYPE type)
{
	m_type = type;
}

//===============================================
// ���[�V�����ݒ�
//===============================================
void CPlayer::MotionSet(void)
{
	if (nullptr == m_pBody)
	{// �I�u�W�F�N�g����
		return;
	}

	if (nullptr == m_pBody->GetMotion())
	{// ���[�V��������
		return;
	}

	if (m_Info.state == STATE_DAMAGE)
	{// �_���[�W���
		m_action = ACTION_DAMAGE;
		m_pBody->GetMotion()->Set(m_action);
		m_pLeg->GetMotion()->Set(m_action);

		if (m_pBody->GetMotion()->GetEnd())
		{// ���[�V�����I��
			m_action = ACTION_NEUTRAL;	// �ێ���ԂɕύX
		}
		else
		{
			return;
		}
	}

	if (m_Info.state == STATE_CATCH && m_Catch.pPlayer != nullptr) {
		m_pBody->GetMotion()->Set(ACTION_FLUTTERING);
		m_pLeg->GetMotion()->Set(ACTION_FLUTTERING);

		return;
	}

	if (!m_bJump && !m_bMove && 
		m_action >= ACTION_NEUTRAL && m_action <= ACTION_JUMP)
	{// �������Ă��Ȃ�
		m_action = ACTION_NEUTRAL;
		m_pBody->GetMotion()->BlendSet(m_action);
	}
	else if(m_bJump && 
		m_action >= ACTION_NEUTRAL && m_action <= ACTION_JUMP)
	{// �W�����v����
		m_action = ACTION_JUMP;
		m_pBody->GetMotion()->BlendSet(m_action);
	}
	else if (m_bMove &&
		m_action >= ACTION_NEUTRAL && m_action <= ACTION_JUMP)
	{// �ړ�����
		m_action = ACTION_WALK;
		m_pBody->GetMotion()->BlendSet(m_action);
	}
	else if (m_action == ACTION_ATK)
	{// �U������
		m_pBody->GetMotion()->Set(m_action);
		if (m_pBody->GetMotion()->GetEnd())
		{// ���[�V�����I��
			m_action = ACTION_NEUTRAL;
		}
	}
	else if (m_action == ACTION_CATCH)
	{// ������
		m_pBody->GetMotion()->BlendSet(m_action);

		if (m_pBody->GetMotion()->GetEnd())
		{// ���[�V�����I��
			if (m_Catch.pPlayer == nullptr)
			{
				//m_action = ACTION_HOLD;	// �ێ���ԂɕύX
				m_action = ACTION_NEUTRAL;
			}
		}
		else
		{
			if (m_Catch.pPlayer == nullptr){	// �v���C���[��͂�ł��Ȃ�
				CModel *pModel = m_pBody->GetParts(m_pBody->GetNumParts() - HAND_PARTS);
				D3DXVECTOR3 pos = D3DXVECTOR3(pModel->GetMtx()->_41, pModel->GetMtx()->_42, pModel->GetMtx()->_43);
				PlayerCatch(pos);
			}
		}
	}
	else if (m_action == ACTION_HOLD)
	{// �ێ����Ă���
		m_pBody->GetMotion()->BlendSet(m_action);
		if (m_pBody->GetMotion()->GetEnd())
		{// ���[�V�����I��
		
		}
	}
	else if (m_action == ACTION_THROW)
	{// ������
		m_pBody->GetMotion()->BlendSet(m_action);
		if (m_pBody->GetMotion()->GetEnd())
		{// ���[�V�����I��
			m_action = ACTION_NEUTRAL;
		}
	}
	else if (m_action == ACTION_DAMAGE)
	{// ������
		m_pBody->GetMotion()->BlendSet(m_action);
		if (m_pBody->GetMotion()->GetEnd())
		{// ���[�V�����I��
			m_action = ACTION_NEUTRAL;
		}

		return;
	}
	else
	{

	}

	if (nullptr == m_pLeg){	// �r���Ȃ�
		return;
	}

	if (nullptr == m_pLeg->GetMotion()) {	// ���[�V�������Ȃ�
		return;
	}

	if (m_bJump)
	{
		m_pLeg->GetMotion()->BlendSet(ACTION_JUMP);
	}
	else if (m_bMove)
	{
		m_pLeg->GetMotion()->BlendSet(ACTION_WALK);
	}
	else
	{
		m_pLeg->GetMotion()->BlendSet(ACTION_NEUTRAL);
	}
}

//===============================================
// �U��
//===============================================
void CPlayer::Attack(void)
{
	if (m_action < ACTION_NEUTRAL || m_action > ACTION_JUMP || m_Info.state == STATE_CATCH)
	{// �U���s�\
		if (m_action != ACTION_ATK)
		{// �U�����ł͂Ȃ�
			return;
		}
	}

	// �p�b�h����
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();

	// ����
	if (pInputPad->GetTrigger(CInputPad::BUTTON_A, m_nId))
	{
		if (m_action != ACTION_ATK)
		{// �U�����ł͂Ȃ�
			m_action = ACTION_ATK;
		}
	}

	// �U������
	if (m_pBody == nullptr){	// ���̂��Ȃ�
		return;
	}

	if (m_pBody->GetMotion() == nullptr){	// ���[�V�������Ȃ�
		return;
	}

	if (m_pBody->GetMotion()->GetNowMotion() == ACTION_ATK && 
		m_pBody->GetMotion()->GetNowKey() == m_pBody->GetMotion()->GetNowNumKey() - 2)
	{// �U�����蒆
		CModel *pModel = m_pBody->GetParts(m_pBody->GetNumParts() - HAND_PARTS);	// �p�[�c
		D3DXVECTOR3 pos = D3DXVECTOR3(pModel->GetMtx()->_41, pModel->GetMtx()->_42, pModel->GetMtx()->_43);
		DamageCollision(pos);

		// �����蔻��m�F
		AttackCheck();
	}
}

//===============================================
// ��������
//===============================================
void CPlayer::Catch(void)
{
	if (m_action < ACTION_NEUTRAL || m_action > ACTION_WALK || m_Info.state == STATE_CATCH)
	{// �ҋ@���ړ���
		if (m_action != ACTION_CATCH && (m_Catch.pPlayer == nullptr && m_Catch.pGimmick == nullptr))
		{
			return;
		}
	}

	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();

	// ����
	if (pInputPad->GetTrigger(CInputPad::BUTTON_X, m_nId))
	{
		if (m_action != ACTION_CATCH)
		{
			m_action = ACTION_CATCH;
		}
	}

	if (pInputPad->GetTrigger(CInputPad::BUTTON_Y, m_nId))
	{
		int n = 0;
	}

	// �������Ώۂ̔���
	if (m_Catch.pPlayer != nullptr && m_Info.state != STATE_CATCH) {	// ���̃v���C���[�������Ă���
		if (m_Catch.pPlayer->m_Info.state != STATE_CATCH) {	// ����̏�Ԃ��ς�����ꍇ
			m_Catch.pPlayer->m_Catch.pPlayer = nullptr;
			m_Catch.pPlayer = nullptr;
		}
		else
		{
			m_fRotDest = m_fRotMove;
			if (m_Catch.pPlayer->m_bMove) {	// ���肪�ړ�
				m_Catch.nMoveCnt++;	// �J�E���g�A�b�v
				if (m_Catch.pPlayer->m_bJump)
				{
					m_Info.pos.x += m_Catch.pPlayer->m_Info.move.x * 1.5f;	// ����̈ړ��ʂɈ���������
					m_Info.pos.z += m_Catch.pPlayer->m_Info.move.z * 1.5f;	// ����̈ړ��ʂɈ���������
				}
				else
				{
					m_Info.pos.x += m_Catch.pPlayer->m_Info.move.x * 0.75f;	// ����̈ړ��ʂɈ���������
					m_Info.pos.z += m_Catch.pPlayer->m_Info.move.z * 0.75f;	// ����̈ړ��ʂɈ���������
				}

				m_Catch.pPlayer->m_Info.pos.y += m_Catch.pPlayer->m_Info.move.y;

				if (m_Catch.pPlayer->m_Info.pos.y < m_Info.pos.y)
				{
					m_Catch.pPlayer->m_Info.pos.y = m_Info.pos.y;
					m_Catch.pPlayer->m_Info.move.y = 0.0f;
				}
			}

			if (m_Catch.nMoveCnt >= CATCH_LIMIT							// �J�E���g���E�l
				|| pInputPad->GetTrigger(CInputPad::BUTTON_X, m_nId)) {	// �L�[����
				m_Catch.pPlayer->m_Info.state = STATE_NORMAL;
				m_Catch.pPlayer->m_Catch.pPlayer = nullptr;
				m_Catch.pPlayer = nullptr;
			}
		}
	}
	else if(m_Catch.pGimmick != nullptr) {	// �M�~�b�N�������Ă���
		CGimmickRotateDoor *pDoor = m_Catch.pGimmick->GetRotateDoor();

		if (pDoor != nullptr) {	// �h�A�������Ă���

			if (pDoor->GetModel() == nullptr) {	// �h�A�̃��f�����g�p����Ă��Ȃ�
				GimmickRelease();	// �M�~�b�N�𗣂�
			}

			if (pDoor->GetModel()->GetCurrentRotation().y == 0.0f) {	// ��]���~�܂��Ă���
				GimmickRelease();	// �M�~�b�N�𗣂�
			}
		}
	}
}

//===============================================
// �������Ă���M�~�b�N���O��
//===============================================
void CPlayer::GimmickRelease(void)
{
	m_Info.state = STATE_NORMAL;
	m_Catch.pGimmick = nullptr;
}

//===============================================
// �A�C�e���̃t�@�C���ݒ�
//===============================================
const char *CPlayer::ItemFileName(int type)
{
	char m_aString[64] = "\n";

	switch (type)
	{
	case CItem::TYPE_NORMAL:
	{
		return "\0";
	}

	break;

	case CItem::TYPE_COIN:
	{
		return  "data\\MODEL\\coin.x";
	}

	break;

	case CItem::TYPE_BRECELET:
	{
		return   "data\\MODEL\\bracelet00.x";
	}

	break;

	case CItem::TYPE_CUP:
	{
		return  "data\\MODEL\\cup00.x";
	}

	break;

	case CItem::TYPE_GEM00:
	{
		return  "data\\MODEL\\gem00.x";
	}

	break;

	case CItem::TYPE_GEM01:
	{
		return  "data\\MODEL\\gem01.x";
	}

	break;

	case CItem::TYPE_GOLDBAR:
	{
		return  "data\\MODEL\\goldbar00.x";
	}

	break;

	case CItem::TYPE_JAR:
	{
		return  "data\\MODEL\\jar.x";
	}

	break;

	case CItem::TYPE_KUNAI:
	{
		return  "data\\MODEL\\kunai.x";
	}

	break;

	case CItem::TYPE_RING00:
	{
		return  "data\\MODEL\\ring00.x";
	}

	break;

	case CItem::TYPE_SCROLL:
	{
		return  "data\\MODEL\\scroll00.x";
	}

	break;

	case CItem::TYPE_SHURIKEN:
	{
		return  "data\\MODEL\\shuriken.x";
	}

	break;

	case CItem::TYPE_MAX:
	{
		return  "";
	}

	break;

	}

	return  "";
}

//===============================================
// �A�C�e���̃\�[�g
//===============================================
void CPlayer::ItemSort(void)
{
	for (int nCount = 0; nCount < MAX_ITEM - 1; nCount++)
	{
		for (int nCntRank = 1 + nCount; nCntRank < MAX_ITEM; nCntRank++)
		{
			//�傫�����������ւ�
			if (m_aSaveType[nCount] == 0)
			{//����ւ�
				m_aSaveType[nCount] = 0;
				int nTmp = m_aSaveType[nCntRank];
				m_aSaveType[nCntRank] = m_aSaveType[nCount];
				m_aSaveType[nCount] = nTmp;
			}
		}
	}
}

//===============================================
// ���ꂼ��̃A�C�e�����Z
//===============================================
void CPlayer::AddItemCount(int type)
{
	switch (type)
	{
	case CItem::TYPE_NORMAL:  // �Ȃ���Ȃ�
	{
		
	}

	break;

	case CItem::TYPE_COIN:  // �R�C��
	{
		m_nNumItemCoin++;
	}

	break;

	case CItem::TYPE_BRECELET:  // �u���X���b�g
	{
		m_nNumItemBrecetet++;
	}

	break;

	case CItem::TYPE_CUP:       // �u
	{
		m_nNumItemCup++;
	}

	break;

	case CItem::TYPE_GEM00:     // �G�������h
	{
		m_nNumItemEmerald++;
	}

	break;

	case CItem::TYPE_GEM01:     // �_�C�������h
	{
		m_nNumItemDiamond++;
	}

	break;

	case CItem::TYPE_GOLDBAR:   // ����
	{
		m_nNumItemGold++;
	}

	break;

	case CItem::TYPE_JAR:       // �r
	{
		m_nNumItemJar++;
	}

	break;

	case CItem::TYPE_KUNAI:     // �N�i�C
	{
		m_nNumItemKunai++;
	}

	break;

	case CItem::TYPE_RING00:    // �����O
	{
		m_nNumItemRing++;
	}

	break;

	case CItem::TYPE_SCROLL:    // ����
	{
		m_nNumItemScroll++;
	}

	break;

	case CItem::TYPE_SHURIKEN:  // �藠��
	{
		m_nNumItemShuriken++;
	}

	break;

	case CItem::TYPE_MAX:
	{
		
	}

	break;

	}
}

//===============================================
// ���ꂼ��̃A�C�e�����Z
//===============================================
void CPlayer::SubItemCount(int type)
{
	switch (type)
	{
	case CItem::TYPE_NORMAL:  // �Ȃ���Ȃ�
	{

	}

	break;

	case CItem::TYPE_COIN:  // �R�C��
	{
		m_nNumItemCoin--;
	}

	break;

	case CItem::TYPE_BRECELET:  // �u���X���b�g
	{
		m_nNumItemBrecetet--;
	}

	break;

	case CItem::TYPE_CUP:       // �u
	{
		m_nNumItemCup--;
	}

	break;

	case CItem::TYPE_GEM00:     // �G�������h
	{
		m_nNumItemEmerald--;
	}

	break;

	case CItem::TYPE_GEM01:     // �_�C�������h
	{
		m_nNumItemDiamond--;
	}

	break;

	case CItem::TYPE_GOLDBAR:   // ����
	{
		m_nNumItemGold--;
	}

	break;

	case CItem::TYPE_JAR:       // �r
	{
		m_nNumItemJar--;
	}

	break;

	case CItem::TYPE_KUNAI:     // �N�i�C
	{
		m_nNumItemKunai--;
	}

	break;

	case CItem::TYPE_RING00:    // �����O
	{
		m_nNumItemRing--;
	}

	break;

	case CItem::TYPE_SCROLL:    // ����
	{
		m_nNumItemScroll--;
	}

	break;

	case CItem::TYPE_SHURIKEN:  // �藠��
	{
		m_nNumItemShuriken--;
	}

	break;

	case CItem::TYPE_MAX:
	{
		
	}

	break;

	}
}

//===============================================
// �̂Ă�A�C�e���I��
//===============================================
void CPlayer::SelectItem(void)
{
	// �Q�[���p�b�h�̏����擾
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();

	if (pInputPad->GetTrigger(CInputPad::BUTTON_RIGHTBUTTON, m_nId))
	{
		m_nItemId++;
	}

	if (pInputPad->GetTrigger(CInputPad::BUTTON_LEFTBUTTON, m_nId))
	{
		m_nItemId--;
	}

	if (m_nItemId >= 12)
	{
		m_nItemId = 1;
	}
	else if(m_nItemId <= 0)
	{
		m_nItemId = 11;
	}

	if (pInputPad->GetTrigger(CInputPad::BUTTON_Y, m_nId))
	{
		if (m_nItemCnt > 0 && GetSelectItem(m_nItemId) > 0)
		{
			CItem *pItem = CItem::Create(m_Info.pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), ItemFileName(m_nItemId), m_nItemId, CItem::STATE_DROP);

			if (m_pScore != nullptr)
			{
				// �X�R�A�ւ炷��
				m_pScore->LowerScore(pItem->GetEachScore());
			}

			m_aSaveType[m_nItemId] = 0;

			if (nullptr != pItem)
			{
				D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				//�ړ��ʂ̐ݒ�
				move.x = sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.08f;
				move.y = 18.0f;
				move.z = cosf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.08f;
				pItem->SetMove(move);
			}

			m_nItemCnt--;

			SubItemCount(m_nItemId);

			ItemSort();
		}
	}
}

//===============================================
// ���ꂼ��̃A�C�e���̑����擾
//===============================================
int CPlayer::GetSelectItem(int type)
{
	switch (type)
	{
	case CItem::TYPE_NORMAL:  // �Ȃ���Ȃ�
	{

	}

	break;

	case CItem::TYPE_COIN:  // �R�C��
	{
		return m_nNumItemCoin;
	}

	break;

	case CItem::TYPE_BRECELET:  // �u���X���b�g
	{
		return m_nNumItemBrecetet;
	}

	break;

	case CItem::TYPE_CUP:       // �u
	{
		return m_nNumItemCup;
	}

	break;

	case CItem::TYPE_GEM00:     // �G�������h
	{
		return m_nNumItemEmerald;
	}

	break;

	case CItem::TYPE_GEM01:     // �_�C�������h
	{
		return m_nNumItemDiamond;
	}

	break;

	case CItem::TYPE_GOLDBAR:   // ����
	{
		return m_nNumItemGold;
	}

	break;

	case CItem::TYPE_JAR:       // �r
	{
		return m_nNumItemJar;
	}

	break;

	case CItem::TYPE_KUNAI:     // �N�i�C
	{
		return m_nNumItemKunai;
	}

	break;

	case CItem::TYPE_RING00:    // �����O
	{
		return m_nNumItemRing;
	}

	break;

	case CItem::TYPE_SCROLL:    // ����
	{
		return m_nNumItemScroll;
	}

	break;

	case CItem::TYPE_SHURIKEN:  // �藠��
	{
		return m_nNumItemShuriken;
	}

	break;

	case CItem::TYPE_MAX:
	{
		return 0;
	}

	break;

	}

	return 0;
}

//===============================================
// ���𓊂���
//===============================================
void CPlayer::Throw(void)
{
	if (m_action != ACTION_HOLD)
	{// �����Ă��Ȃ�
		return;
	}

	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();

	// ����
	if (pInputPad->GetTrigger(CInputPad::BUTTON_X, m_nId))
	{
		m_action = ACTION_THROW;
	}
}

//===============================================
// �}�g���b�N�X�ݒ�
//===============================================
void CPlayer::SetMatrix(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�ւ̃|�C���^���擾
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_Info.mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Info.rot.y, m_Info.rot.x, m_Info.rot.z);
	D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);
	D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_Info.mtxWorld);
}

//===============================================
// �v���C���[���m�̍U������
//===============================================
void CPlayer::DamageCollision(D3DXVECTOR3 pos)
{
	CPlayer *pPlayer = GetTop();	// �擪���󂯎��
	CXFile *pFile = CManager::GetInstance()->GetModelFile();

	while (pPlayer != nullptr)
	{
		CPlayer *pPlayerNext = pPlayer->GetNext();	// ����ێ�

		if (pPlayer == this)
		{// �������g�����肪�ʏ��ԈȊO
			pPlayer = pPlayerNext;
			continue;
		}

		D3DXVECTOR3 ObjPos = pPlayer->GetPosition();	// ���W
		D3DXVECTOR3 HeadPos = pPlayer->m_pBody->GetParts(1)->GetPosition();
		D3DXVECTOR3 HeadMax = pFile->GetMax(pPlayer->m_pBody->GetParts(1)->GetId());
		D3DXVECTOR3 vtxMax = pFile->GetMax(pPlayer->m_pBody->GetParts(0)->GetId());
		D3DXVECTOR3 vtxMin = pFile->GetMin(pPlayer->m_pBody->GetParts(0)->GetId());

		if (pos.x + -ATK_RANGE <= ObjPos.x + vtxMax.x && pos.x + ATK_RANGE >= ObjPos.x + vtxMin.x
			&& pos.z + -ATK_RANGE <= ObjPos.z + vtxMax.z && pos.z + ATK_RANGE >= ObjPos.z + vtxMin.z)
		{// ���E�����
			if (pos.y >= ObjPos.y && pos.y <= ObjPos.y + HeadPos.y + HeadMax.y)
			{// ���������
				pPlayer->Damage(1);
			}
		}

		pPlayer = pPlayerNext;
	}
}

//===============================================
// �A�C�e���𗎂Ƃ�
//===============================================
void CPlayer::Drop(int nDropCnt)
{
	int nOldCnt = m_nItemCnt;

	m_nItemCnt -= nDropCnt;

	if (m_nItemCnt < 0) {	// ��������0���������
		m_nItemCnt = 0;
	}

	int nDiff = nOldCnt - m_nItemCnt;	// ������

	// ���Ƃ���������
	for (int nCnt = 0; nCnt < nDiff; nCnt++)
	{
		char aString[258] = "\n";

		strcpy(aString, ItemFileName(m_aSaveType[nCnt]));

		CItem *pItem = CItem::Create(m_Info.pos, D3DXVECTOR3(0.0f, 0.0f ,0.0f), aString, m_aSaveType[nCnt], CItem::STATE_DROP);

		if (m_pScore != nullptr)
		{
			// �X�R�A�ւ炷��
			m_pScore->LowerScore(pItem->GetEachScore());
		}

		m_aSaveType[nCnt] = 0;

		if (nullptr != pItem)
		{
			D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.08f;
			move.y = 18.0f;
			move.z = cosf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.08f;
			pItem->SetMove(move);
		}
	}

	ItemSort();
}

//===============================================
// �A�C�e���S�����Ƃ�
//===============================================
void CPlayer::DropAll(void)
{
	// ���Ƃ���������
	for (int nCnt = 0; nCnt < m_nItemCnt; nCnt++)
	{
		char aString[258] = "\n";

		strcpy(aString, ItemFileName(m_aSaveType[nCnt]));

		CItem *pItem = CItem::Create(m_Info.pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), aString, m_aSaveType[nCnt], CItem::STATE_DROP);

		if (m_pScore != nullptr)
		{
			// �X�R�A�ւ炷��
			m_pScore->LowerScore(pItem->GetEachScore());
		}

		m_aSaveType[nCnt] = 0;

		if (nullptr != pItem)
		{
			D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.08f;
			move.y = 18.0f;
			move.z = cosf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.08f;
			pItem->SetMove(move);
		}
	}

	// �������Ă���A�C�e���̑������[���ɂ���
	m_nItemCnt = 0;
}

//===============================================
// �v���C���[��͂�
//===============================================
void CPlayer::PlayerCatch(D3DXVECTOR3 pos)
{
	CPlayer *pPlayer = GetTop();	// �擪���󂯎��
	CXFile *pFile = CManager::GetInstance()->GetModelFile();

	while (pPlayer != nullptr)
	{
		CPlayer *pPlayerNext = pPlayer->GetNext();	// ����ێ�

		if (pPlayer == this)
		{// �������g�����肪�ʏ��ԈȊO
			pPlayer = pPlayerNext;
			continue;
		}

		D3DXVECTOR3 ObjPos = pPlayer->GetPosition();	// ���W
		D3DXVECTOR3 HeadPos = pPlayer->m_pBody->GetParts(1)->GetPosition();
		D3DXVECTOR3 HeadMax = pFile->GetMax(pPlayer->m_pBody->GetParts(1)->GetId());
		D3DXVECTOR3 vtxMax = pFile->GetMax(pPlayer->m_pBody->GetParts(0)->GetId());
		D3DXVECTOR3 vtxMin = pFile->GetMin(pPlayer->m_pBody->GetParts(0)->GetId());

		if (pos.x + -CATCH_RANGE <= ObjPos.x + vtxMax.x && pos.x + CATCH_RANGE >= ObjPos.x + vtxMin.x
			&& pos.z + -CATCH_RANGE <= ObjPos.z + vtxMax.z && pos.z + CATCH_RANGE >= ObjPos.z + vtxMin.z)
		{// ���E�����
			if (pos.y >= ObjPos.y && pos.y <= ObjPos.y + HeadPos.y + HeadMax.y)
			{// ���������
				if (pPlayer->m_Info.state == STATE_NORMAL)
				{// �ʏ��Ԃ̏ꍇ
					pPlayer->m_Info.state = STATE_CATCH;	// �����͂܂�Ă����Ԃ�
					pPlayer->m_Catch.pPlayer = this;		// ����Ɏ������w��
					m_Catch.pPlayer = pPlayer;				// �����̃|�C���^�ɑ�����w��
					m_Catch.nMoveCnt = 0;
				}
			}
		}

		pPlayer = pPlayerNext;
	}
}

//===============================================
// �v���C���[�̃}�g���b�N�X
//===============================================
void CPlayer::SetCatchMatrix(void)
{
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_Info.mtxWorld);

	if (m_Catch.pPlayer != nullptr) {	// �v���C���[
		D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, m_Info.pos.y - m_Catch.pPlayer->m_Info.mtxWorld._42, -50.0f);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxTrans);

		// �p�[�c�̃}�g���b�N�X�Ɛe�̃}�g���b�N�X���������킹��
		D3DXMatrixMultiply(&m_Info.mtxWorld,
			&m_Info.mtxWorld, &m_Catch.pPlayer->m_Info.mtxWorld);

		m_Info.pos = D3DXVECTOR3(m_Info.mtxWorld._41, m_Info.mtxWorld._42, m_Info.mtxWorld._43);

		return;
	}
	else if (m_Catch.pGimmick != nullptr) { // �M�~�b�N

		D3DXVECTOR3 pos = m_Catch.SetPos;
		D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		CGimmickRotateDoor *pDoor = m_Catch.pGimmick->GetRotateDoor();
		
		if (pDoor != nullptr) {

			if (pDoor->GetModel() != nullptr) {

				// �ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
				D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxTrans);

				// �����𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
				D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxRot);

				// �p�[�c�̃}�g���b�N�X�Ɛe�̃}�g���b�N�X���������킹��
				D3DXMatrixMultiply(&m_Info.mtxWorld,
					&m_Info.mtxWorld, pDoor->GetModel()->GetMtx());

				m_Info.pos = D3DXVECTOR3(m_Info.mtxWorld._41, m_Info.mtxWorld._42, m_Info.mtxWorld._43);
			}
		}

		return;
	}

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Info.rot.y, m_Info.rot.x, m_Info.rot.z);
	D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);
	D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxTrans);
}

//===============================================
// �U�����̓����蔻��m�F
//===============================================
void CPlayer::AttackCheck(void)
{
	if (m_pBody == nullptr) {	// �̂��Ȃ�
		return;
	}

	CModel *pModel = m_pBody->GetParts(m_pBody->GetNumParts() - HAND_PARTS);	// ����擾����

	if (pModel == nullptr) {	// ���f�����Ȃ�
		return;
	}

	D3DXVECTOR3 AtkPos = D3DXVECTOR3(pModel->GetMtx()->_41, pModel->GetMtx()->_42, pModel->GetMtx()->_43);	// �U�����W
	CEnemy *pEnem = CEnemy::GetTop()->GetTop();	// �G�̐擪���擾
	
	// �G�����m�F
	while (pEnem != nullptr) {
		CEnemy *pEnemNext = pEnem->GetNext();
		pEnem->HitCheck(AtkPos, ATK_RANGE);	// �G��Ă��邩�`�F�b�N
		pEnem = pEnemNext;
	}
}

//===============================================
// �g�p�K�w�\���̐ݒ�
//===============================================
void CPlayer::BodySet(void)
{
	// �����g�X�V
	if (m_pLeg != nullptr)
	{// �g�p����Ă���ꍇ
		m_pLeg->Update();

		// ���̐ݒ�
		if (m_pWaist != nullptr)
		{
			CModel *pModel = m_pLeg->GetParts(0);

			// ���̍������U
			m_pWaist->SetPosition(m_pWaist->GetSetPosition() + pModel->GetCurrentPosition());
			m_pWaist->SetMatrix();
		}
	}

	// ���̍X�V
	if (m_pBody != nullptr)
	{// �g�p����Ă���ꍇ
		m_pBody->Update();
	}
}