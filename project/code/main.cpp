//==========================================================
//
// ���C������ [main.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "main.h"
#include "manager.h"
#include "debugproc.h"
#include <time.h>

//�}�N����`
#define CLASS_NAME	"WindowClass"		//�E�C���h�E�N���X�̖��O
#define WINDOW_NAME	"�������� I"	//�E�C���h�E�̖��O

//�v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// �O���[�o���ϐ�
int g_nCountFPS = 0;		//FPS�J�E���^

//===========================================================
//���C���֐�
//===========================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	DWORD dwCurrentTime;	//���ݎ���
	DWORD dwExecLastTime;	//�Ō�ɏ�����������
	DWORD dwFrameCount;		//�t���[���J�E���g
	DWORD dwFPSLastTime;	//�Ō��FPS���v����������

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),				//WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,						//�E�C���h�E�̃X�^�C��
		WindowProc,						//�E�C���h�E�v���V�[�W��
		0,								//0�ɂ���(�ʏ�͎g�p���Ȃ�)
		0,								//0�ɂ���(�ʏ�͎g�p���Ȃ�)
		hInstance,						//�C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),	//�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW),		//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),		//�N���C�A���g�̈�̔w�i�F
		NULL,							//���j���[�o�[
		CLASS_NAME,						//�E�C���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION)	//�t�@�C���̃A�C�R��
	};

	HWND hWnd;	//�E�C���h�E�n���h��
	MSG msg;	//���b�Z�[�W���i�[����ϐ�

				//�E�C���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	//�E�C���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�`�����w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�C���h�E�𐶐�
	hWnd = CreateWindowEx
	(
		0,								//�g���E�C���h�E�X�^�C��
		CLASS_NAME,						//�E�C���h�E�N���X�̖��O
		WINDOW_NAME,					//�E�C���h�E�̖��O
		WS_OVERLAPPEDWINDOW,			//�E�C���h�E�X�^�C��
		CW_USEDEFAULT,					//�E�C���h�E�̍���x���W
		CW_USEDEFAULT,					//�E�C���h�E�̍���y���W
		(rect.right - rect.left),		//�E�C���h�E�̕�
		(rect.bottom - rect.top),		//�E�C���h�E�̍���
		NULL,							//�e�E�C���h�E�̃n���h��
		NULL,							//���j���[�n���h���܂��͎q�E�C���h�EID
		hInstance,						//�C���X�^���X�n���h��
		NULL							//�E�C���h�E�쐬�f�[�^
	);

	// �}�l�[�W���[�̏���������
	if (FAILED(CManager::GetInstance()->Init(hInstance, hWnd, TRUE)))
	{// ���s�����ꍇ
		return -1;
	}

	//����\��ݒ�
	timeBeginPeriod(1);

	dwCurrentTime = 0;	//������
	dwExecLastTime = timeGetTime();	//���ݎ������擾(�ۑ�)
	dwFrameCount = 0;	//������
	dwFPSLastTime = timeGetTime();	//���ݎ������擾(�ۑ�)

	// �����_���̎���Đ���
	srand((unsigned)time(0));

	//�E�C���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);

	UpdateWindow(hWnd);

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windows�̏���
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DirectX�̏���

			dwCurrentTime = timeGetTime();	//���ݎ������擾
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5�b�o��
				//FPS���v��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;	//FPS�𑪒肵��������ۑ�
				dwFrameCount = 0;	//�t���[���J�E���g���N���A
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60����1�b�o��
				dwExecLastTime = dwCurrentTime;	//�����J�n�̎���[���ݎ���]��ۑ�

				if (CManager::GetInstance() != NULL)
				{// �����ł����ꍇ

					// �X�V����
					CManager::GetInstance()->Update();

					// �`�揈��
					CManager::GetInstance()->Draw();
				}

				dwFrameCount++;	//�t���[���J�E���g�����Z
			}
		}
	}

	// �I������
	if (CManager::GetInstance() != NULL)
	{// �g�p���Ă���ꍇ
		// �I������
		CManager::Release();
	}

	//�E�C���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//===========================================================
//�E�C���h�E�v���V�[�W��
//===========================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;					//�Ԃ�l���i�[

	const RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };		//�E�C���h�E�̗̈�(�`)

	switch (uMsg)
	{
	case WM_DESTROY:		//�E�B���h�E�p���̃��b�Z�[�W

		//WM_QUET���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:		//�L�[�����̃��b�Z�[�W

		switch (wParam)
		{
		case VK_ESCAPE:

			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

			if (nID == IDYES)
			{
				//�E�C���h�E��p������(WM_DESTROY���b�Z�[�W�𑗂�)
				DestroyWindow(hWnd);
			}
			break;
		}
		break;
	case WM_COMMAND:	//�R�}���h���s���b�Z�[�W
		break;
	case WM_CLOSE:		//����{�^������
		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

		if (nID == IDYES)
		{//�͂���I�������Ƃ�
			//�E�C���h�E��p������(WM_DESTROY���b�Z�[�W�𑗂�)
			DestroyWindow(hWnd);
		}
		else
		{//��������I�������Ƃ�
			return 0;	//0��Ԃ��Ȃ��ƏI�����Ă��܂�
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);	//����̏�����Ԃ�
}

//================================================
//FPS�̎擾
//================================================
int GetFPS(void)
{
	return g_nCountFPS;
}