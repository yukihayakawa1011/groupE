//==========================================================
//
// �f�o�b�O�\������ [debugproc.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "main.h"
#include "debugproc.h"
#include <string.h>
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "Xfile.h"
#include "camera.h"
#include "object_manager.h"

// �ÓI�����o�ϐ��錾
LPD3DXFONT CDebugProc::m_pFont = NULL;	// �f�o�b�O�t�H���g�ւ̃|�C���^

//**********************************************************
//�}�N����`
//**********************************************************
#define MAX_FLOATNUM	(2)		//�����_�ȉ��̕\������

//**********************************************************
//�f�o�b�OONOFF�\�����b�Z�[�W
//**********************************************************
const char *CDebugProc::m_apMode[CScene::MODE_MAX] =
{
	"�^�C�g��",
	"�`���[�g���A��",
	"�Q�[��",
	"���U���g",
	"�����L���O",
};

//==========================================================
// �R���X�g���N�^
//==========================================================
CDebugProc::CDebugProc()
{
	//�f�o�b�O�\�����̃N���A
	m_bDisp = false;
	m_pFont = NULL;
	memset(&m_aStr[0], NULL, sizeof(m_aStr));
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CDebugProc::~CDebugProc()
{
	
}

//==========================================================
//�f�o�b�O�\���̏���������
//==========================================================
void CDebugProc::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//�f�o�b�O�\���p�t�H���g�̐���
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);

//�����\���ݒ�
#if _DEBUG
	m_bDisp = true;
#else NDEBUG
	m_bDisp = false;
#endif

}

//==========================================================
//�f�o�b�O�\���̏I������
//==========================================================
void CDebugProc::Uninit(void)
{
	//�f�o�b�O�\���p�t�H���g�̔p��
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
}

//==========================================================
//�f�o�b�O�\���̍X�V����
//==========================================================
void CDebugProc::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();	// �L�[�{�[�h�̃|�C���^

	if(pInputKeyboard->GetTrigger(DIK_F1) == true)
	{//F1�L�[�������ꂽ�Ƃ�
		m_bDisp = m_bDisp ? false : true;
	}

	Print("FPS : %d\n", GetFPS());
	Print("���݂̃��[�h [ %s ] : [Enter]�őJ��\n", m_apMode[CManager::GetInstance()->GetMode()]);
	
	Print("�I�u�W�F�N�g�̑��� : %d\n", CObjectManager::GetInstance()->GetNumAll());
	Print("�D�揇�ʕ�(%d��) ��\n", NUM_PRIORITY);
	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		Print("[%d] : %d  ", nCntPri, CObjectManager::GetInstance()->GetPriNumAll(nCntPri));

		if ((nCntPri + 1) % 4 == 0)
		{
			Print("\n");
		}
	}

	Print("\n");
	Print("�e�N�X�`���̓ǂݍ��ݑ���(%d) \n", CManager::GetInstance()->GetTexture()->GetNumAll());
	Print("���f���̓ǂݍ��ݑ���    (%d) \n", CManager::GetInstance()->GetModelFile()->GetNumAll());

	{
		D3DXVECTOR3 CamPosV = CManager::GetInstance()->GetCamera()->GetPositionV();
		CManager::GetInstance()->GetDebugProc()->Print("�J���� ���_ : [%f, %f, %f]\n", CamPosV.x, CamPosV.y, CamPosV.z);
	}

	{
		D3DXVECTOR3 CamPosR = CManager::GetInstance()->GetCamera()->GetPositionR();
		CManager::GetInstance()->GetDebugProc()->Print("       �����_ : [%f, %f, %f]\n", CamPosR.x, CamPosR.y, CamPosR.z);
	}

	{
		D3DXVECTOR3 CamRot = CManager::GetInstance()->GetCamera()->GetRotation();
		CManager::GetInstance()->GetDebugProc()->Print("       ���� : [%f, %f, %f]\n", CamRot.x, CamRot.y, CamRot.z);
	}
}

//==========================================================
//�f�o�b�O�\���̕`�揈��
//==========================================================
void CDebugProc::Draw(void)
{

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	if (m_bDisp == true)
	{//�f�o�b�N���[�h���I���̎�
		//�e�L�X�g�̕`��
		m_pFont->DrawText(NULL, &m_aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	}

	//�f�o�b�O�\�����̃N���A
	memset(&m_aStr[0], NULL, sizeof(m_aStr));
}

//==========================================================
//�f�o�b�O�\���̐ݒ菈��
//==========================================================
void CDebugProc::Print(const char *fmt, ...)
{
	va_list args;
	char aString[MAX_DEBUGSTRING];		// �w�蕶���i�[�p
	char aSaveString[MAX_DEBUGSTRING];	// �ψ������g�i�[�p
	int nLength = 0;	// �ψ������̕����̒���
	int nStopLength;	// �ψ����}���ꏊ���

	// ������̑��
	strcpy(&aString[0], fmt);

	va_start(args, fmt);

	for (char *p = &aString[0]; *p != '\0'; p++)
	{
		if (*p == '%')
		{// �m�F����������ꍇ

			p++;	// �m�F�����܂Ői�߂�

			nLength = 0;	// �����̒������Z�b�g

			// �w�肳�ꂽ��ނ��Ƃɕϐ��̒l�𔲂��o��(va_arg)
			switch (*p)
			{
			case 'd':	// ����

				sprintf(&aSaveString[0], "%d", va_arg(args, int));

				break;
			case 'f':	// ����

				sprintf(&aSaveString[0], "%f", va_arg(args, double));

				// ������̒������擾
				nLength = (int)strlen(&aSaveString[0]);

				// �����_�ȉ���1�����ڂ܂Ŋm�F
				for (int nCntlength = 0; aSaveString[nCntlength] != '\0'; nCntlength++)
				{
					if (aSaveString[nCntlength] == '.')
					{// �����_���������ꍇ

						// �����_�ȉ��̌��������߂�
						int nMin = (int)strlen(&aSaveString[nCntlength + 1]);

						// �����_����̕������Ǝw�肵���l�܂ł̍��������߂�
						nMin -= MAX_FLOATNUM;

						// ������̒����������_�ȉ����ʂ܂łɕ␳
						nLength -= nMin;
					}
				}

				break;
			case 'c':	// ����

				sprintf(&aSaveString[0], "%c", va_arg(args, char));

				break;
			case 's':	// ������

				sprintf(&aSaveString[0], "%s", va_arg(args, const char*));

				break;
			}

			if (nLength == 0)
			{// �����̒������擾���Ă��Ȃ��ꍇ

				// ������̒������擾
				nLength = (int)strlen(&aSaveString[0]);
			}

			nStopLength = (int)strlen(p) + 1;

			// ���������̊m�F����(%�`)�����̕���������炷
			memmove(p + nLength - 2, p, nStopLength);

			p--;	// �|�C���^��%�܂Ŗ߂�

			// �ψ������w�肳�ꂽ�ꏊ�ɑ}��
			memcpy(p, &aSaveString[0], nLength);
		}
	}

	va_end(args);

	// �������A������
	strcat(&m_aStr[0], &aString[0]);
}


