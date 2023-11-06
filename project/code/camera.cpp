//==========================================================
//
// �J�����̏����S�� [camera.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "camera.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "game.h"
#include "meshfield.h"

//==========================================================
// �}�N����`
//==========================================================
#define CAMERA_MOVESPEED	(1.0f)			// �ړ���
#define CAMERA_LENGTHMOVE	(1.0f)			// �J���������ړ���
#define ROTATE_SPEED		(0.03f)			// �J�����̉�]���x
#define PAD_ROTATE			(0.02f)
#define CAMERA_MAXLENGTH	(5000.0f)		// �J�����ő勗��
#define CAMERA_MINLENGTH	(300.0f)		// �J�����ŏ�����
#define MOUSE_MOVESPEED		(0.2f)			// �}�E�X�ړ����x
#define MOUSE_ROTATESPEED_X	(0.004f)		// �}�E�X��]���xx��
#define MOUSE_ROTATESPEED_Z	(0.005f)		// �}�E�X��]���xz��
#define MOUSE_WHEELSPEED	(0.1f)			// �}�E�X�z�C�[����]���x
#define MAX_SLOWROT			(0.15f)
#define MESSAGERAND			(120)
#define SLOW_CAMERAROT		(0.7f)
#define TITLE_ROTATESPD		(0.0025f)			// �^�C�g����]��

//==========================================================
// �R���X�g���N�^
//==========================================================
CCamera::CCamera()
{

}

//==========================================================
// �f�X�g���N�^
//==========================================================
CCamera::~CCamera()
{

}

//==========================================================
//�J�����̏���������
//==========================================================
HRESULT CCamera::Init(void)
{
	//�e�ϐ��̏�����
	m_posR = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_posV = D3DXVECTOR3(0.0f, 1900.0f, 1000.0f);
	m_fLength = sqrtf((m_posV.x - m_posR.x) * (m_posV.x - m_posR.x) + (m_posV.z - m_posR.z) * (m_posV.z - m_posR.z));
	m_rot = D3DXVECTOR3(0.0f, atan2f(m_posR.x - m_posV.x, m_posR.z - m_posV.z), 1.56f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot.z = MIN_CAMERA_ROTZ;
	m_mode = MODE_NORMAL;

	//���_�ݒ�
	SetV();

	return S_OK;
}

//==========================================================
//�J�����̏I������
//==========================================================
void CCamera::Uninit(void)
{

}

//==========================================================
//�J�����̍X�V����
//==========================================================
void CCamera::Update(void)
{
	
	{
		//�}�E�X�ł̎��_�ړ�
	}
	/*else
	{
		Edit();
	}*/
	//�S���_�̈ړ�
	//MoveVR();

	//�����_�̈ړ�
	//MoveR();

	//if (m_mode != MODE_SLOWSHW)
	//{
	//	if (CGame::GetPause() != NULL)
	//	{
	//		if (CGame::GetPause()->GetEnable() == false)
	//		{
	//			//���_�̈ړ�
	//			MoveV();
	//			MouseCamera();
	//		}
	//	}
	//	else
	//	{
	//		if (CManager::GetInstance()->GetMode() == CScene::MODE_TUTORIAL)
	//		{
	//			//���_�̈ړ�
	//			MoveV();
	//			MouseCamera();
	//		}
	//		//���_�̈ړ�
	//		//MoveV();
	//	}
	//}
	//else
	//{
	//	MouseCamera();
	//	SlowShw();
	//}

}

//==========================================================
//�J�����̐ݒ菈��
//==========================================================
void CCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		//�f�o�C�X�ւ̃|�C���^���擾

	//�v���W�F�N�V�����}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�̐���[ �������e ]
	/*D3DXMatrixOrthoLH(&m_mtxProjection,
		(float)SCREEN_WIDTH,
		(float)SCREEN_HEIGHT,
		0.0f,
		8000.0f);*/

	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
								D3DXToRadian(45.0f),
								(float)SCREEN_WIDTH / (float) SCREEN_HEIGHT,
								10.0f,
								40000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//�r���[�}�b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//==========================================================
//�J�����̑S�ړ�����
//==========================================================
void CCamera::MoveVR(void)
{
	CInputKeyboard *pKey = CManager::GetInstance()->GetInputKeyboard();

	//���_�����_�̓����ړ�
	if (pKey->GetPress(DIK_A) == true)
	{//A�L�[����

		//���_�̈ړ�
		if (pKey->GetPress(DIK_W) == true)
		{
			m_posV.x += cosf(m_rot.y + (-D3DX_PI * 0.75f)) * CAMERA_MOVESPEED;
			m_posV.z += sinf(m_rot.y + (-D3DX_PI * 0.75f)) * CAMERA_MOVESPEED;
		}
		else if (pKey->GetPress(DIK_S) == true)
		{
			m_posV.x += cosf(m_rot.y + (-D3DX_PI * 0.25f)) * CAMERA_MOVESPEED;
			m_posV.z += sinf(m_rot.y + (-D3DX_PI * 0.25f)) * CAMERA_MOVESPEED;
		}
		else
		{
			m_posV.x += cosf(m_rot.y + (-D3DX_PI * 0.5f)) * CAMERA_MOVESPEED;
			m_posV.z += sinf(m_rot.y + (-D3DX_PI * 0.5f)) * CAMERA_MOVESPEED;
		}
	}
	else if (pKey->GetPress(DIK_D) == true)
	{//D�L�[����

		//���_�̈ړ�
		if (pKey->GetPress(DIK_W) == true)
		{
			m_posV.x += cosf(m_rot.y + (D3DX_PI * 0.75f)) * CAMERA_MOVESPEED;
			m_posV.z += sinf(m_rot.y + (D3DX_PI * 0.75f)) * CAMERA_MOVESPEED;
		}
		else if (pKey->GetPress(DIK_S) == true)
		{
			m_posV.x += cosf(m_rot.y + (D3DX_PI * 0.25f)) * CAMERA_MOVESPEED;
			m_posV.z += sinf(m_rot.y + (D3DX_PI * 0.25f)) * CAMERA_MOVESPEED;
		}
		else
		{
			m_posV.x += cosf(m_rot.y + (D3DX_PI * 0.5f)) * CAMERA_MOVESPEED;
			m_posV.z += sinf(m_rot.y + (D3DX_PI * 0.5f)) * CAMERA_MOVESPEED;
		}

	}
	else if (pKey->GetPress(DIK_W) == true)
	{//W�L�[����

		//���_�̈ړ�
		m_posV.x += -cosf(m_rot.y) * CAMERA_MOVESPEED;
		m_posV.z += -sinf(m_rot.y) * CAMERA_MOVESPEED;
	}
	else if (pKey->GetPress(DIK_S) == true)
	{//S�L�[����
		//���_�̈ړ�
		m_posV.x += cosf(m_rot.y) * CAMERA_MOVESPEED;
		m_posV.z += sinf(m_rot.y) * CAMERA_MOVESPEED;

	}

	//�����_�ݒ�
	SetR();
}

//==========================================================
//�J�����̎��_�ړ�����
//==========================================================
void CCamera::MoveV(void)
{
	CInputKeyboard *pKey = CManager::GetInstance()->GetInputKeyboard();
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();	// �L�[�{�[�h�̃|�C���^
	float fMultiSlow = 1.0f;

	//x���̈ړ�
	if (pInputPad->GetStickPress(0, CInputPad::BUTTON_RIGHT_X, 0.0f, CInputPad::STICK_PLUS) == true)
	{//Q�L�[����
		m_rot.y += -D3DX_PI * ROTATE_SPEED * pInputPad->GetStickAdd(0, CInputPad::BUTTON_RIGHT_X, 0.0f, CInputPad::STICK_PLUS) * fMultiSlow;
		if (m_rot.y < -D3DX_PI)
		{//�p�x�����𒴂����ꍇ
			m_rot.y += D3DX_PI * 2;
		}
	}
	else if (pInputPad->GetStickPress(0, CInputPad::BUTTON_RIGHT_X, 0.0f, CInputPad::STICK_MINUS) == true)
	{//E�L�[����
		m_rot.y += -D3DX_PI * ROTATE_SPEED * pInputPad->GetStickAdd(0, CInputPad::BUTTON_RIGHT_X, 0.0f, CInputPad::STICK_MINUS) * fMultiSlow;
	}

	//x���̈ړ�
	if ((pKey->GetPress(DIK_Z) == true && pKey->GetPress(DIK_C) != true))
	{//Q�L�[����
		m_rot.y += -D3DX_PI * ROTATE_SPEED;
		if (m_rot.y < -D3DX_PI)
		{//�p�x�����𒴂����ꍇ
			m_rot.y += D3DX_PI * 2;
		}
	}
	else if ((pKey->GetPress(DIK_C) == true && pKey->GetPress(DIK_Z) != true))
	{//E�L�[����
		m_rot.y += D3DX_PI * ROTATE_SPEED;
		if (m_rot.y > D3DX_PI)
		{//�p�x�����𒴂����ꍇ
			m_rot.y += -D3DX_PI * 2;
		}
	}

	//z���̈ړ�
	if (pInputPad->GetStickPress(0, CInputPad::BUTTON_RIGHT_Y, 0.1f, CInputPad::STICK_PLUS) == true)
	{//Y�L�[����
		//�p�x�̕ύX
		m_rot.z += PAD_ROTATE * pInputPad->GetStickAdd(0, CInputPad::BUTTON_RIGHT_Y, 0.5f, CInputPad::STICK_PLUS) * fMultiSlow;
		if (m_rot.z < MIN_CAMERA_ROTZ)
		{//�p�x�����E�𒴂����ꍇ
			m_rot.z = MIN_CAMERA_ROTZ;
		}
		
	}
	else if (pInputPad->GetStickPress(0, CInputPad::BUTTON_RIGHT_Y, 0.1f, CInputPad::STICK_MINUS) == true)
	{//N�L�[����
		//�p�x�̕ύX
		m_rot.z += PAD_ROTATE * 2 * pInputPad->GetStickAdd(0, CInputPad::BUTTON_RIGHT_Y, 0.5f, CInputPad::STICK_MINUS) * fMultiSlow;

		if (m_rot.z > MAX_CAMERA_ROTZ)
		{//�p�x�����E�𒴂����ꍇ
			m_rot.z = MAX_CAMERA_ROTZ;
		}

	}

	//z���̈ړ�
	if (pKey->GetPress(DIK_Y) == true && pKey->GetPress(DIK_N) != true)
	{//Y�L�[����
	 //�p�x�̕ύX
		m_rot.z += -D3DX_PI * ROTATE_SPEED;
		if (m_rot.z < MIN_CAMERA_ROTZ)
		{//�p�x�����E�𒴂����ꍇ
			m_rot.z = MIN_CAMERA_ROTZ;
		}

	}
	else if (pKey->GetPress(DIK_N) == true && pKey->GetPress(DIK_Y) != true)
	{//N�L�[����
	 //�p�x�̕ύX
		m_rot.z += D3DX_PI * ROTATE_SPEED;

		if (m_rot.z > MAX_CAMERA_ROTZ)
		{//�p�x�����E�𒴂����ꍇ
			m_rot.z = MAX_CAMERA_ROTZ;
		}
	}

	////�����_����̋����̑���
	//if (pKey->GetPress(DIK_U) == true && pKey->GetPress(DIK_M) != true)
	//{//U�L�[����
	//	m_fLength -= CAMERA_LENGTHMOVE;

	//	if (m_fLength < CAMERA_MINLENGTH)
	//	{//�������ŏ��𒴂����ꍇ
	//		m_fLength = CAMERA_MINLENGTH;
	//	}
	//	
	//}
	//else if (pKey->GetPress(DIK_M) == true && pKey->GetPress(DIK_U) != true)
	//{//M�L�[����
	//	m_fLength += CAMERA_LENGTHMOVE;

	//	if (m_fLength > CAMERA_MAXLENGTH)
	//	{//�������ő�𒴂����ꍇ
	//		m_fLength = CAMERA_MAXLENGTH;
	//	}
	//}

	if (m_mode == MODE_SLOWGUN)
	{
		Slow();
	}

	//���_�ݒ�
	SetV();
}

//==========================================================
//�J�����̒����_�ړ�����
//==========================================================
void CCamera::MoveR(void)
{
	CInputKeyboard *pKey = CManager::GetInstance()->GetInputKeyboard();

	//x���̈ړ�
	if (pKey->GetPress(DIK_Q) == true && pKey->GetPress(DIK_E) != true)
	{//Q�L�[����

		//�p�x�̕ύX
		m_rot.y += D3DX_PI * ROTATE_SPEED;
		if (m_rot.y > D3DX_PI)
		{//�p�x�����𒴂����ꍇ
			m_rot.y += -D3DX_PI * 2;
		}
	}
	else if (pKey->GetPress(DIK_E) == true && pKey->GetPress(DIK_Q) != true)
	{//E�L�[����

		//�p�x�̕ύX
		m_rot.y += -D3DX_PI * ROTATE_SPEED;

		if (m_rot.y < -D3DX_PI)
		{//�p�x�����𒴂����ꍇ
			m_rot.y += D3DX_PI * 2;
		}
	}

	//z���̈ړ�
	if (pKey->GetPress(DIK_T) == true && pKey->GetPress(DIK_B) != true)
	{//T�L�[����

		//�p�x�̕ύX
		m_rot.z += D3DX_PI * ROTATE_SPEED;

		if (m_rot.z >  MAX_CAMERA_ROTZ)
		{//�p�x�����E�𒴂����ꍇ
			m_rot.z = MAX_CAMERA_ROTZ;
		}
	}
	else if (pKey->GetPress(DIK_B) == true && pKey->GetPress(DIK_T) != true)
	{//B�L�[����
		//�p�x�̕ύX
		m_rot.z += -D3DX_PI * ROTATE_SPEED;
		if (m_rot.z < MIN_CAMERA_ROTZ)
		{//�p�x�����E�𒴂����ꍇ
			m_rot.z = MIN_CAMERA_ROTZ;
		}
	}

	//�����_�ݒ�
	SetR();
}

//==========================================================
//�J�������_�ݒ菈��
//==========================================================
void CCamera::SetV(void)
{
	m_posV.y = m_posR.y + cosf(m_rot.z) * m_fLength;
	m_posV.x = m_posR.x + (sinf(m_rot.z) * cosf(m_rot.y)) * m_fLength;
	m_posV.z = m_posR.z + (sinf(m_rot.z) * sinf(m_rot.y)) * m_fLength;
}

//==========================================================
//�J���������_�ݒ菈��
//==========================================================
void CCamera::SetR(void)
{
	m_posR.y = m_posV.y - cosf(m_rot.z) * m_fLength;
	m_posR.x = m_posV.x - (sinf(m_rot.z) * cosf(m_rot.y)) * m_fLength;
	m_posR.z = m_posV.z - (sinf(m_rot.z) * sinf(m_rot.y)) * m_fLength;
}

//==========================================================
//�}�E�X�ł̃J�����ړ�����
//==========================================================
void CCamera::MouseCamera(void)
{
	CInputMouse *pMouse = CManager::GetInstance()->GetInputMouse();

	//if (pMouse->GetPress(CInputMouse::BUTTON_LBUTTON) == true && pMouse->GetPress(CInputMouse::BUTTON_RBUTTON) == true)
	//{//���E�����ɉ�����Ă���Ƃ�
	//	m_posV.x += cosf(m_rot.y + (-D3DX_PI * 0.5f)) * (pMouse->GetCousorMove().x * MOUSE_MOVESPEED) + -cosf(m_rot.y) * (pMouse->GetCousorMove().y * MOUSE_MOVESPEED);
	//	m_posV.z += sinf(m_rot.y + (-D3DX_PI * 0.5f)) * (pMouse->GetCousorMove().x * MOUSE_MOVESPEED) + -sinf(m_rot.y) * (pMouse->GetCousorMove().y * MOUSE_MOVESPEED);

	//	//�ړ��ʂ����Z
	//	m_posV.x += m_posV.x;
	//	m_posV.z += m_posV.z;

	//	//�ړ��ʂ�������
	//	m_posV.x = 0.0f;
	//	m_posV.z = 0.0f;

	//	//�����_�ݒ�
	//	SetR();
	//}
	//else if (pMouse->GetPress(CInputMouse::BUTTON_LBUTTON) == true)
	//{//���L�[��������Ă���Ƃ�
	//	
	//}
	//else if (pMouse->GetPress(CInputMouse::BUTTON_RBUTTON) == true)
	//{//�E�L�[��������Ă���Ƃ�
	//	m_rot.y -= pMouse->GetCousorMove().x * MOUSE_ROTATESPEED_X;
	//	m_rot.z -= pMouse->GetCousorMove().y * MOUSE_ROTATESPEED_Z;

	//	if (m_rot.y > D3DX_PI)
	//	{//�p�x�����𒴂����ꍇ
	//		m_rot.y = D3DX_PI;
	//		m_rot.y *= -1.0f;
	//	}
	//	else if (m_rot.y < -D3DX_PI)
	//	{//�p�x�����𒴂����ꍇ
	//		m_rot.y = -D3DX_PI;
	//		m_rot.y *= -1.0f;
	//	}
	//	if (m_rot.z < MIN_CAMERA_ROTZ)
	//	{//�p�x�����E�𒴂����ꍇ
	//		m_rot.z = MIN_CAMERA_ROTZ;
	//	}
	//	else if (m_rot.z > MAX_CAMERA_ROTZ)
	//	{//�p�x�����E�𒴂����ꍇ
	//		m_rot.z = MAX_CAMERA_ROTZ;
	//	}

	//	//���_�ݒ�
	//	SetR();
	//}

	m_rot.y -= pMouse->GetCousorMove().x * MOUSE_ROTATESPEED_X;
	m_rot.z -= pMouse->GetCousorMove().y * 0.003f;

	if (m_rot.y < -D3DX_PI)
	{//�p�x�����𒴂����ꍇ
		m_rot.y += D3DX_PI * 2;
	}
	else if (m_rot.y > D3DX_PI)
	{//�p�x�����𒴂����ꍇ
		m_rot.y += -D3DX_PI * 2;
	}
	if (m_rot.z < MIN_CAMERA_ROTZ)
	{//�p�x�����E�𒴂����ꍇ
		m_rot.z = MIN_CAMERA_ROTZ;
	}
	else if (m_rot.z > MAX_CAMERA_ROTZ)
	{//�p�x�����E�𒴂����ꍇ
		m_rot.z = MAX_CAMERA_ROTZ;
	}

	//�z�C�[���̎g�p�ʂŋ����̕ύX
	m_fLength += pMouse->GetCousorMove().z * MOUSE_WHEELSPEED;

	if (m_fLength > CAMERA_MAXLENGTH)
	{//�������ő�𒴂����ꍇ
		m_fLength = CAMERA_MAXLENGTH;
	}
	else if (m_fLength < CAMERA_MINLENGTH)
	{//�������ŏ��𒴂����ꍇ
		m_fLength = CAMERA_MINLENGTH;
	}

	//���_�ݒ�
	SetV();
}

//==========================================================
// �Ǐ]����
//==========================================================
void CCamera::Pursue(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	D3DXVECTOR3 posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ڕW�̒����_
	D3DXVECTOR3 posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ڕW�̎��_
	D3DXVECTOR3 RDiff = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �����_�̍���
	D3DXVECTOR3 VDiff = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ���_�̍���

	//�ړI�̒����_�̍��W���擾
	posRDest = D3DXVECTOR3(pos.x - sinf(rot.y) * 30.0f, pos.y + 50.0f, pos.z - cosf(rot.y) * 30.0f);

	//�ړI�̎��_�̍��W���l��
	posVDest = D3DXVECTOR3(
		posRDest.x + (sinf(m_rot.z) * cosf(m_rot.y)) * m_fLength,
		posRDest.y + cosf(m_rot.z) * m_fLength,
		posRDest.z + (sinf(m_rot.z) * sinf(m_rot.y)) * m_fLength);

	//�����_�̕␳
	RDiff = D3DXVECTOR3(posRDest.x - m_posR.x, posRDest.y - m_posR.y, posRDest.z - m_posR.z);
	m_posR.x += RDiff.x * 0.2f;
	m_posR.y += RDiff.y * 0.1f;
	m_posR.z += RDiff.z * 0.2f;

	//���_�̕␳
	VDiff = D3DXVECTOR3(posVDest.x - m_posV.x, posVDest.y - m_posV.y, posVDest.z - m_posV.z);
	m_posV.x += VDiff.x * 0.2f;
	m_posV.y += VDiff.y * 0.1f;
	m_posV.z += VDiff.z * 0.2f;

}

//==========================================================
// ���e�ꏊ�ݒ�
//==========================================================
void CCamera::Setting(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	m_rot.y = -rot.y + (D3DX_PI * 0.5f);

	//�ړI�̒����_�̍��W���擾
	m_posR = D3DXVECTOR3(pos.x - sinf(rot.y) * 30.0f, pos.y + 50.0f, pos.z - cosf(rot.y) * 30.0f);

	//�ړI�̎��_�̍��W���l��
	m_posV = D3DXVECTOR3(
		m_posR.x + (sinf(m_rot.z) * cosf(m_rot.y)) * m_fLength,
		m_posR.y + cosf(m_rot.z) * m_fLength,
		m_posR.z + (sinf(m_rot.z) * sinf(m_rot.y)) * m_fLength);
}

//==========================================================
// �G�f�B�b�g�p
//==========================================================
void CCamera::Edit(void)
{
	CInputMouse *pMouse = CManager::GetInstance()->GetInputMouse();
	if (pMouse->GetPress(CInputMouse::BUTTON_LBUTTON) == true && pMouse->GetPress(CInputMouse::BUTTON_RBUTTON) == true)
	{//���E�����ɉ�����Ă���Ƃ�
		m_posV.x += cosf(m_rot.y + (-D3DX_PI * 0.5f)) * (pMouse->GetCousorMove().x * MOUSE_MOVESPEED) + -cosf(m_rot.y) * (pMouse->GetCousorMove().y * MOUSE_MOVESPEED);
		m_posV.z += sinf(m_rot.y + (-D3DX_PI * 0.5f)) * (pMouse->GetCousorMove().x * MOUSE_MOVESPEED) + -sinf(m_rot.y) * (pMouse->GetCousorMove().y * MOUSE_MOVESPEED);

		//�ړ��ʂ����Z
		m_posV.x += m_posV.x;
		m_posV.z += m_posV.z;

		//�ړ��ʂ�������
		m_posV.x = 0.0f;
		m_posV.z = 0.0f;

		//�����_�ݒ�
		SetR();
	}
	else if (pMouse->GetPress(CInputMouse::BUTTON_LBUTTON) == true)
	{//���L�[��������Ă���Ƃ�
		m_rot.y -= pMouse->GetCousorMove().x * MOUSE_ROTATESPEED_X;
		m_rot.z -= pMouse->GetCousorMove().y * 0.003f;
	}
	else if (pMouse->GetPress(CInputMouse::BUTTON_RBUTTON) == true)
	{//�E�L�[��������Ă���Ƃ�
		m_rot.y -= pMouse->GetCousorMove().x * MOUSE_ROTATESPEED_X;
		m_rot.z -= pMouse->GetCousorMove().y * MOUSE_ROTATESPEED_Z;

		if (m_rot.y > D3DX_PI)
		{//�p�x�����𒴂����ꍇ
			m_rot.y = D3DX_PI;
			m_rot.y *= -1.0f;
		}
		else if (m_rot.y < -D3DX_PI)
		{//�p�x�����𒴂����ꍇ
			m_rot.y = -D3DX_PI;
			m_rot.y *= -1.0f;
		}
		if (m_rot.z < MIN_CAMERA_ROTZ)
		{//�p�x�����E�𒴂����ꍇ
			m_rot.z = MIN_CAMERA_ROTZ;
		}
		else if (m_rot.z > MAX_CAMERA_ROTZ)
		{//�p�x�����E�𒴂����ꍇ
			m_rot.z = MAX_CAMERA_ROTZ;
		}

		//���_�ݒ�
		SetR();
	}

	if (m_rot.y > D3DX_PI)
	{//�p�x�����𒴂����ꍇ
		m_rot.y = D3DX_PI;
		m_rot.y *= -1.0f;
	}
	else if (m_rot.y < -D3DX_PI)
	{//�p�x�����𒴂����ꍇ
		m_rot.y = -D3DX_PI;
		m_rot.y *= -1.0f;
	}
	if (m_rot.z < MIN_CAMERA_ROTZ)
	{//�p�x�����E�𒴂����ꍇ
		m_rot.z = MIN_CAMERA_ROTZ;
	}
	else if (m_rot.z > MAX_CAMERA_ROTZ)
	{//�p�x�����E�𒴂����ꍇ
		m_rot.z = MAX_CAMERA_ROTZ;
	}

	//�z�C�[���̎g�p�ʂŋ����̕ύX
	m_fLength += pMouse->GetCousorMove().z * MOUSE_WHEELSPEED;

	if (m_fLength > CAMERA_MAXLENGTH)
	{//�������ő�𒴂����ꍇ
		m_fLength = CAMERA_MAXLENGTH;
	}
	else if (m_fLength < CAMERA_MINLENGTH)
	{//�������ŏ��𒴂����ꍇ
		m_fLength = CAMERA_MINLENGTH;
	}

	//���_�ݒ�
	SetV();
}

//==========================================================
// ����
//==========================================================
void CCamera::SetRot(const D3DXVECTOR3 rot)
{
	float fRotDiff;
	float fRotDest;

	fRotDest = -rot.y + (D3DX_PI * 0.5f);	//�ړI�̌������擾

	fRotDiff = fRotDest - m_rot.y;

	if (fRotDiff > D3DX_PI || fRotDiff < -D3DX_PI)
	{//-3.14�`3.14�͈̔͊O�̏ꍇ
		if (fRotDiff > D3DX_PI)
		{
			fRotDiff += (-D3DX_PI * 2);
		}
		else if (fRotDiff < -D3DX_PI)
		{
			fRotDiff += (D3DX_PI * 2);
		}
	}

	m_rot.y += fRotDiff * 0.04f;

	if (m_rot.y > D3DX_PI || m_rot.y < -D3DX_PI)
	{//-3.14�`3.14�͈̔͊O�̏ꍇ
		if (m_rot.y > D3DX_PI)
		{
			m_rot.y += (-D3DX_PI * 2);
		}
		else if (m_rot.y  < -D3DX_PI)
		{
			m_rot.y += (D3DX_PI * 2);
		}
	}

	//���_�̐ݒ�
	SetV();
}

//==========================================================
// �X���[���̊p�x����
//==========================================================
void CCamera::Slow(void)
{
	float fLeftRot = m_rot.y - (m_SlowOldRot.y + D3DX_PI * MAX_SLOWROT);
	float fRightRot = m_rot.y - (m_SlowOldRot.y + -D3DX_PI * MAX_SLOWROT);

	if (fLeftRot < -D3DX_PI)
	{//�p�x�����𒴂����ꍇ
		fLeftRot += D3DX_PI * 2;
	}
	if (fLeftRot > D3DX_PI)
	{//�p�x�����𒴂����ꍇ
		fLeftRot += -D3DX_PI * 2;
	}

	if (fRightRot < -D3DX_PI)
	{//�p�x�����𒴂����ꍇ
		fRightRot += D3DX_PI * 2;
	}
	if (fRightRot > D3DX_PI)
	{//�p�x�����𒴂����ꍇ
		fRightRot += -D3DX_PI * 2;
	}

	if (fLeftRot > 0.0f)
	{
		m_rot.y = (m_SlowOldRot.y + D3DX_PI * MAX_SLOWROT);
	}

	if (fRightRot < 0.0f)
	{
		m_rot.y = (m_SlowOldRot.y + -D3DX_PI * MAX_SLOWROT);
	}
}

//==========================================================
// �X���[�V�����[���̃J��������
//==========================================================
void CCamera::SlowShw(void)
{
	CInputKeyboard *pKey = CManager::GetInstance()->GetInputKeyboard();
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();	// �L�[�{�[�h�̃|�C���^
	float fMultiSlow = SLOW_CAMERAROT;

	// ���������߂�
	float fLeftRot = m_rot.y - (m_SlowOldRot.y + D3DX_PI * 0.3f);
	float fRightRot = m_rot.y - (m_SlowOldRot.y + -D3DX_PI * 0.3f);

	if (fLeftRot < -D3DX_PI)
	{//�p�x�����𒴂����ꍇ
		fLeftRot += D3DX_PI * 2;
	}
	if (fLeftRot > D3DX_PI)
	{//�p�x�����𒴂����ꍇ
		fLeftRot += -D3DX_PI * 2;
	}

	if (fRightRot < -D3DX_PI)
	{//�p�x�����𒴂����ꍇ
		fRightRot += D3DX_PI * 2;
	}
	if (fRightRot > D3DX_PI)
	{//�p�x�����𒴂����ꍇ
		fRightRot += -D3DX_PI * 2;
	}

	//x���̈ړ�
	if (pInputPad->GetStickPress(0, CInputPad::BUTTON_RIGHT_X, 0.0f, CInputPad::STICK_PLUS) == true)
	{//Q�L�[����
		m_rot.y += -D3DX_PI * ROTATE_SPEED * pInputPad->GetStickAdd(0, CInputPad::BUTTON_RIGHT_X, 0.0f, CInputPad::STICK_PLUS) * fMultiSlow;
		if (m_rot.y < -D3DX_PI)
		{//�p�x�����𒴂����ꍇ
			m_rot.y += D3DX_PI * 2;
		}
	}
	else if (pInputPad->GetStickPress(0, CInputPad::BUTTON_RIGHT_X, 0.0f, CInputPad::STICK_MINUS) == true)
	{//E�L�[����
		m_rot.y += -D3DX_PI * ROTATE_SPEED * pInputPad->GetStickAdd(0, CInputPad::BUTTON_RIGHT_X, 0.0f, CInputPad::STICK_MINUS) * fMultiSlow;

		if (m_rot.y > D3DX_PI)
		{//�p�x�����𒴂����ꍇ
			m_rot.y += -D3DX_PI * 2;
		}
	}
	else
	{
		m_SlowOldRot = m_rot;
	}

	// �����̕ύX
	m_fLength += 30.0f;

	if (m_fLength > CAMERA_MAXLENGTH)
	{//�������ő�𒴂����ꍇ
		m_fLength = CAMERA_MAXLENGTH;
	}

	SetV();
}


//==========================================================
// ������ݒ�
//==========================================================
void CCamera::SetRotation(D3DXVECTOR3 rot)
{
	m_rot = rot;

	if (m_rot.y > D3DX_PI)
	{//�p�x�����𒴂����ꍇ
		m_rot.y = D3DX_PI;
		m_rot.y *= -1.0f;
	}
	else if (m_rot.y < -D3DX_PI)
	{//�p�x�����𒴂����ꍇ
		m_rot.y = -D3DX_PI;
		m_rot.y *= -1.0f;
	}
	//if (m_rot.z < MIN_CAMERA_ROTZ)
	//{//�p�x�����E�𒴂����ꍇ
	//	m_rot.z = MIN_CAMERA_ROTZ;
	//}
	//else if (m_rot.z > MAX_CAMERA_ROTZ)
	//{//�p�x�����E�𒴂����ꍇ
	//	m_rot.z = MAX_CAMERA_ROTZ;
	//}

	SetV();
}

//==========================================================
// �^�C�g��������]
//==========================================================
void CCamera::TitleRotateCamera(void)
{
	m_rot.y += TITLE_ROTATESPD;

	while (1)
	{
		if (m_rot.y >= -D3DX_PI && m_rot.y <= D3DX_PI)
		{
			break;
		}
		else if (m_rot.y > D3DX_PI)
		{
			m_rot.y += -D3DX_PI * 2;
		}
		else if (m_rot.y < -D3DX_PI)
		{
			m_rot.y += D3DX_PI * 2;
		}
	}

	SetV();
}

//==========================================================
// ���W�ݒ�
//==========================================================
void CCamera::SetPositionR(D3DXVECTOR3 pos)
{ 
	m_posR = pos; 
	SetV();
}


//==========================================================
// �R���X�g���N�^
//==========================================================
CMultiCamera::CMultiCamera()
{

}

//==========================================================
// �f�X�g���N�^
//==========================================================
CMultiCamera::~CMultiCamera()
{

}

//==========================================================
//�J�����̏���������
//==========================================================
HRESULT CMultiCamera::Init(void)
{
	CCamera::Init();

	//�v���C���[�Ǐ]�J�����̉�ʈʒu�ݒ�
	m_viewport.X = 0;
	m_viewport.Y = 0;
	m_viewport.Width = (DWORD)(SCREEN_WIDTH * 0.125f);
	m_viewport.Height = (DWORD)(SCREEN_HEIGHT * 0.22f);
	m_viewport.MinZ = 0.0f;
	m_viewport.MaxZ = 1.0f;

	return S_OK;
}

//==========================================================
//�J�����̏I������
//==========================================================
void CMultiCamera::Uninit(void)
{
	CCamera::Uninit();
}

//==========================================================
//�J�����̍X�V����
//==========================================================
void CMultiCamera::Update(void)
{
	CCamera::Update();
}

//==========================================================
//�J�����̐ݒ菈��
//==========================================================
void CMultiCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		//�f�o�C�X�ւ̃|�C���^���擾
	D3DXMATRIX mtxView = GetMtxView(), mtxProjection = GetMtxProjection();

	//�r���[�|�[�g�̐ݒ�
	pDevice->SetViewport(&m_viewport);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&mtxProjection,
		D3DXToRadian(45.0f),
		(float)m_viewport.Width / (float)m_viewport.Height,
		10.0f,
		40000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&mtxView,
		&GetPositionV(),
		&GetPositionR(),
		&GetVectorU());

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &mtxView);
}

//==========================================================
// �R���X�g���N�^
//==========================================================
CMapCamera::CMapCamera()
{

}

//==========================================================
// �f�X�g���N�^
//==========================================================
CMapCamera::~CMapCamera()
{

}

//==========================================================
//�J�����̏���������
//==========================================================
HRESULT CMapCamera::Init(void)
{
	CMultiCamera::Init();

	return S_OK;
}

//==========================================================
//�J�����̏I������
//==========================================================
void CMapCamera::Uninit(void)
{
	CMultiCamera::Uninit();
}

//==========================================================
//�J�����̍X�V����
//==========================================================
void CMapCamera::Update(void)
{
	
}

//==========================================================
//�J�����̐ݒ菈��
//==========================================================
void CMapCamera::SetCamera(void)
{
	CMultiCamera::SetCamera();
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		//�f�o�C�X�ւ̃|�C���^���擾

	// ���̕`��
	CMeshField *pMesh = CMeshField::GetTop();	// �擪���擾

	while (pMesh != NULL)
	{// �g�p����Ă���ԌJ��Ԃ�
		CMeshField *pMeshNext = pMesh->GetNext();	// ����ێ�

		pMesh->Draw();

		pMesh = pMeshNext;	// ���Ɉړ�
	}
}
