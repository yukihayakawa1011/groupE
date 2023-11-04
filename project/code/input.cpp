//==========================================================
//
//���̓f�o�C�X���� [input.cpp]
//Author ����ɐ�
//
//==========================================================
#include "input.h"
#include "manager.h"
#include "debugproc.h"

#define REPEAT_TIME (15)	//���s�[�g�^�C�}�[

// �ÓI�����o�ϐ��錾
LPDIRECTINPUT8 CInput::m_pInput = NULL;	// �I�u�W�F�N�g�ւ̃|�C���^

//====================================================================================
//���N���X(���̓f�o�C�X)
//====================================================================================
// �R���X�g���N�^
//==========================================================
CInput::CInput()
{
	m_pDevice = NULL;
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CInput::~CInput()
{
	m_pDevice = NULL;
}

//==========================================================
// ����������
//==========================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{// �܂��N���g�p�J�n���Ă��Ȃ��ꍇ

		//DirectInput�I�u�W�F�N�g�̐���
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{// �������s�����ꍇ
			return E_FAIL;
		}
	}

	return S_OK;
}

//==========================================================
//�I������
//==========================================================
void CInput::Uninit(void)
{
	//�f�o�C�X�̔p��(+�A�N�Z�X���J��)
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	//�I�u�W�F�N�g�̔p��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

#if 0	// �������z�֐��Ȃ̂Œʂ�Ȃ�
//==========================================================
//�X�V����
//==========================================================
void CInput::Update(void)
{
	
}
#endif

//====================================================================================
//�h���N���X(�L�[�{�[�h)
//====================================================================================
// �R���X�g���N�^
//==========================================================
CInputKeyboard::CInputKeyboard()
{
	// �l���N���A����
	for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		m_aKeyState[nCntKey] = 0;
		m_aKeyStateTrigger[nCntKey] = 0;
		m_aKeyStateRelease[nCntKey] = 0;
		m_aKeyStateRepeat[nCntKey] = 0;
	}
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CInputKeyboard::~CInputKeyboard()
{
	
}

//==========================================================
//����������
//==========================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	//���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����擾
	m_pDevice->Acquire();

	return S_OK;
}

//==========================================================
//�I������
//==========================================================
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//==========================================================
//�X�V����
//==========================================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];	//�L�[�{�[�h�̓��͏��
	int nCntKey = 0;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];	//�L�[�{�[�h����̃g���K�[����ۑ�
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & m_aKeyState[nCntKey];	//�L�[�{�[�h����̃����[�X����ۑ�
			m_aKeyState[nCntKey] = aKeyState[nCntKey];	//�L�[�{�[�h����̃v���X����ۑ�
			m_aKeyStateRepeat[nCntKey] = m_aKeyStateTrigger[nCntKey];

			//���s�[�g�擾
			if (GetPress(nCntKey) == true)
			{//�v���X�œ��͂���Ă���Ƃ�
				m_aRepeatCnt[nCntKey]++;

				if (m_aRepeatCnt[nCntKey] >= REPEAT_TIME)
				{//���s�[�g�J�E���^�[���^�C�}�[�𒴂����Ƃ�
					m_aRepeatCnt[nCntKey] = 0;
					m_aKeyStateRepeat[nCntKey] = m_aKeyState[nCntKey];
				}
				else
				{
					m_aKeyStateRepeat[nCntKey] = m_aKeyStateRelease[nCntKey];
				}
			}

			if (GetRelease(nCntKey) == true)
			{//�����[�X���͂��ꂽ�Ƃ�
				m_aRepeatCnt[nCntKey] = 0;
			}
		}
	}
	else
	{
		m_pDevice->Acquire();	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}

}

//==========================================================
//�v���X�����擾
//==========================================================
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//==========================================================
//�g���K�[�����擾
//==========================================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//==========================================================
//�����[�X�����擾
//==========================================================
bool CInputKeyboard::GetRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}

//==========================================================
//���s�[�g�����擾
//==========================================================
bool CInputKeyboard::GetRepeat(int nKey)
{
	return (m_aKeyStateRepeat[nKey] & 0x80) ? true : false;
}

//====================================================================================
//�h���N���X(�}�E�X)
//====================================================================================
// �R���X�g���N�^
//==========================================================
CInputMouse::CInputMouse()
{
	m_State = {};
	m_Trigger = {};
	m_Release = {};
	m_Repeat = {};
	m_Point = {};
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CInputMouse::~CInputMouse()
{

}

//==========================================================
//�}�E�X�̏�����
//==========================================================
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	//���̓f�o�C�X�̐���
	CInput::Init(hInstance, hWnd);

	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g�̐���
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse2)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̐ݒ�
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;	//���Βl���[�h�Őݒ�

	if (FAILED(m_pDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		return E_FAIL;
	}

	//�}�E�X�ւ̃A�N�Z�X�����l��
	m_pDevice->Acquire();

	return S_OK;
}

//==========================================================
//�}�E�X�̏I��
//==========================================================
void CInputMouse::Uninit(void)
{
	//���̓f�o�C�X�̔p��
	CInput::Uninit();
}

//==========================================================
//�}�E�X�̍X�V
//==========================================================
void CInputMouse::Update(void)
{
	DIMOUSESTATE2 MouseState;	//�}�E�X�̓��͏��

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(MouseState), (LPVOID)&MouseState)))
	{
		for (int nCnt = 0; nCnt < 8; nCnt++)
		{
			m_Trigger.rgbButtons[nCnt] = (m_State.rgbButtons[nCnt] ^ MouseState.rgbButtons[nCnt]) & MouseState.rgbButtons[nCnt];	//�L�[�{�[�h����̃g���K�[����ۑ�
		}

		m_State = MouseState;	//�v���X���擾

		//�}�E�X�̌��݂̃|�C���^���擾����
		GetCursorPos(&m_Point);
	}
	else
	{
		m_pDevice->Acquire(); //�}�E�X�ւ̃A�N�Z�X�����l��
	}
}

//==========================================================
//�}�E�X�̃v���X���擾
//==========================================================
bool CInputMouse::GetPress(int nKey)
{
	return (m_State.rgbButtons[nKey] & 0x80) ? true : false;
}

//==========================================================
//�}�E�X�̃g���K�[���擾
//==========================================================
bool CInputMouse::GetTrigger(int nKey)
{
	return (m_Trigger.rgbButtons[nKey] & 0x80) ? true : false;
}

//==========================================================
//�}�E�X�̃����[�X���擾
//==========================================================
bool CInputMouse::GetRelease(int nKey)
{
	return (m_Release.rgbButtons[nKey] & 0x80) ? true : false;
}

//==========================================================
//�}�E�X�̃��s�[�g���擾
//==========================================================
bool CInputMouse::GetRepeat(int nKey)
{
	return (m_Repeat.rgbButtons[nKey] & 0x80) ? true : false;
}

//==========================================================
//�}�E�X�̃J�[�\���ړ��ʎ擾
//==========================================================
D3DXVECTOR3 CInputMouse::GetCousorMove(void)
{
	return D3DXVECTOR3((float)m_State.lX, (float)m_State.lY, (float)m_State.lZ);
}

//==========================================================
//�p�b�h�̃R���X�g���N�^
//==========================================================
CInputPad::CInputPad()
{

}

//==========================================================
//�f�X�g���N�^
//==========================================================
CInputPad::~CInputPad()
{

}

//==========================================================
//����������
//==========================================================
HRESULT CInputPad::Init(HINSTANCE hInstance, HWND hWnd)
{
	//Xinput�̃X�e�[�g��ݒ�
	XInputEnable(true);
	int nCnt;

	for (nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
	{
		//�������[���N���A
		memset(&m_State[nCnt], 0, sizeof(XINPUT_STATE));
		memset(&m_Trigger[nCnt], 0, sizeof(XINPUT_STATE));
	}

	return S_OK;
}

//==========================================================
//�I������
//==========================================================
void CInputPad::Uninit(void)
{
	//Xinput�X�e�[�g��ݒ�
	XInputEnable(false);
}

//==========================================================
// �X�V����
//==========================================================
void CInputPad::Update(void)
{
	XINPUT_STATE aGamepadState[PLAYER_MAX];	//�Q�[���p�b�h�̓��͏��
	static int nRepeatJoyKeyCnt[PLAYER_MAX] = {};
	int nCntPad = 0;

	for (nCntPad = 0; nCntPad < PLAYER_MAX; nCntPad++)
	{
		//���̓f�o�C�X����f�[�^���擾
		if (XInputGetState(nCntPad, &aGamepadState[nCntPad]) == ERROR_SUCCESS)
		{
			m_Trigger[nCntPad].Gamepad.wButtons =
				~m_State[nCntPad].Gamepad.wButtons
				& aGamepadState[nCntPad].Gamepad.wButtons;	//�g���K�[(�{�^��)

			m_Release[nCntPad].Gamepad.wButtons =
				(m_State[nCntPad].Gamepad.wButtons
					^ aGamepadState[nCntPad].Gamepad.wButtons)
				& m_State[nCntPad].Gamepad.wButtons;	//�����[�X(�{�^��)

			m_State[nCntPad] = aGamepadState[nCntPad];	//�v���X

			//���s�[�g�擾

		}
	}
}

//==========================================================
// �v���X����
//==========================================================
bool CInputPad::GetPress(int nKey, int nPlayer)
{
	return (m_State[nPlayer].Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}

//==========================================================
// �g���K�[����
//==========================================================
bool CInputPad::GetTrigger(int nKey, int nPlayer)
{
	return (m_Trigger[nPlayer].Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}

//==========================================================
// �����[�X����
//==========================================================
bool CInputPad::GetRelease(int nKey, int nPlayer)
{
	return (m_Release[nPlayer].Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}

//==========================================================
// ���s�[�g����
//==========================================================
bool CInputPad::GetRepeat(int nKey, int nPlayer)
{
	return (m_Repeat[nPlayer].Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}

//==========================================================
// �X�e�B�b�N�擾
//==========================================================
bool CInputPad::GetStickPress(int nPlayer, int nKey, float DeadZone, Stick PlusStick)
{
	float fAnswer = 0.0f;

	switch (nKey)
	{
	case BUTTON_LEFT_X:
		fAnswer = (float)m_State[nPlayer].Gamepad.sThumbLX / SHRT_MAX;
		break;
	case BUTTON_LEFT_Y:
		fAnswer = (float)m_State[nPlayer].Gamepad.sThumbLY / SHRT_MAX;
		break;
	case BUTTON_RIGHT_X:
		fAnswer = (float)m_State[nPlayer].Gamepad.sThumbRX / SHRT_MAX;
		break;
	case BUTTON_RIGHT_Y:
		fAnswer = (float)m_State[nPlayer].Gamepad.sThumbRY / SHRT_MAX;
		break;
	default:
		break;
	}

	if ((fAnswer < 0.0f && PlusStick == STICK_MINUS && fAnswer < -DeadZone) || (fAnswer > 0.0f && PlusStick == STICK_PLUS && fAnswer > DeadZone))
	{
		return true;
	}


	return false;
}

//==========================================================
// �X�e�B�b�N�̒l�擾
//==========================================================
float CInputPad::GetStickAdd(int nPlayer, int nKey, float DeadZone, Stick PlusStick)
{
	float fAnswer = 0.0f;

	switch (nKey)
	{
	case BUTTON_LEFT_X:
		fAnswer = (float)m_State[nPlayer].Gamepad.sThumbLX / SHRT_MAX;
		break;
	case BUTTON_LEFT_Y:
		fAnswer = (float)m_State[nPlayer].Gamepad.sThumbLY / SHRT_MAX;
		break;
	case BUTTON_RIGHT_X:
		fAnswer = (float)m_State[nPlayer].Gamepad.sThumbRX / SHRT_MAX;
		break;
	case BUTTON_RIGHT_Y:
		fAnswer = (float)m_State[nPlayer].Gamepad.sThumbRY / SHRT_MAX;
		break;
	default:
		break;
	}

	return fAnswer;
}

//==========================================================
// �E�g���K�[�擾
//==========================================================
BYTE CInputPad::GetRightTriggerPress(int nPlayer)
{
	return (m_State[nPlayer].Gamepad.bRightTrigger);
}