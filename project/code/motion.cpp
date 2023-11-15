//===================================================
//
// �K�w�\���ɂ�郂�[�V�������� [motion.cpp]
// Author Ibuki Okusada
//
//===================================================
#include "motion.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "texture.h"
#include "Xfile.h"
#include "model.h"
#include <string.h>
#include "slow.h"

// �}�N����`
#define DEST_MAG	(0.1f)	// �����␳�{��

//===================================================
// �R���X�g���N�^
//===================================================
CMotion::CMotion()
{
	m_nNowFrame = 0;
	m_nNumMotion = 0;
	m_nNowKey = 0;
	m_nNowMotion = 1;
	m_FileData.nNumParts = 0;
	m_FileData.ppParts = NULL;

	for (int nCnt = 0; nCnt < MAX_MOTION; nCnt++)
	{
		m_aInfo[nCnt].nNumKey = 0;
		m_aInfo[nCnt].pKeyInfo = NULL;
		m_aInfo[nCnt].bLoop = false;
	}

	m_bEnd = false;

	//OldKey = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
}

//===================================================
// �f�X�g���N�^
//===================================================
CMotion::~CMotion()
{

}

//===================================================
// �I������
//===================================================
void CMotion::Uninit(void)
{
	// ���[�V�������̔p��
	for (int nCntMotion = 0; nCntMotion < MAX_MOTION; nCntMotion++)
	{// ���[�V���������J��Ԃ�
		if (m_aInfo[nCntMotion].pKeyInfo != NULL)
		{// �L�[��񂪎g���Ă���ꍇ

			for (int nCntKey = 0; nCntKey < m_aInfo[nCntMotion].nNumKey; nCntKey++)
			{// �L�[�����J��Ԃ�

				delete[] m_aInfo[nCntMotion].pKeyInfo[nCntKey].aKey;
				m_aInfo[nCntMotion].pKeyInfo[nCntKey].aKey = NULL;
			}
			delete[] m_aInfo[nCntMotion].pKeyInfo;
			m_aInfo[nCntMotion].pKeyInfo = NULL;
		}
	}
}

//===================================================
// �X�V����
//===================================================
void CMotion::Update(void)
{
	if (m_FileData.ppParts == NULL)
	{// �g�p����Ă��Ȃ��ꍇ
		return;
	}

	if (m_aInfo[m_nNowMotion].nNumKey <= 0)
	{//�L�[�������݂��Ă���ꍇ
		return;
	}

	if (m_bEnd && !m_aInfo[m_nNowMotion].bLoop)
	{
		return;
	}

	int nNowMotion = m_nNowMotion;	// ���݂̃��[�V�����ԍ�
	int nNowKey = m_nNowKey;		// ���݂̃L�[
	int nNextkey = (nNowKey + 1) % m_aInfo[nNowMotion].nNumKey;	//���̃L�[
	int nFrame = m_aInfo[nNowMotion].pKeyInfo[nNowKey].nFrame;
	float fFrame = ((float)m_fNowFrame / (float)nFrame);	// �t���[���Ԃ̍���

	for (int nCntParts = 0; nCntParts < m_FileData.nNumParts; nCntParts++)
	{
		D3DXVECTOR3 setPos = m_FileData.ppParts[nCntParts]->GetPosition();	// �����ʒu
		D3DXVECTOR3 setRot = m_FileData.ppParts[nCntParts]->GetRotation();	// ��������

		//�������Z�o
		float fPosDiffX = setPos.x + m_aInfo[nNowMotion].pKeyInfo[nNextkey].aKey[nCntParts].fPosX	// X���W
			- m_OldKey[nCntParts].fPosX;
		float fPosDiffY = setPos.y + m_aInfo[nNowMotion].pKeyInfo[nNextkey].aKey[nCntParts].fPosY	// Y���W
			- m_OldKey[nCntParts].fPosY;
		float fPosDiffZ = setPos.z + m_aInfo[nNowMotion].pKeyInfo[nNextkey].aKey[nCntParts].fPosZ	// Z���W
			- m_OldKey[nCntParts].fPosZ;
		float fRotDiffX = setRot.x + m_aInfo[nNowMotion].pKeyInfo[nNextkey].aKey[nCntParts].fRotX	// X����
			- m_OldKey[nCntParts].fRotX;
		float fRotDiffY = setRot.y + m_aInfo[nNowMotion].pKeyInfo[nNextkey].aKey[nCntParts].fRotY	// Y����
			- m_OldKey[nCntParts].fRotY;
		float fRotDiffZ = setRot.z + m_aInfo[nNowMotion].pKeyInfo[nNextkey].aKey[nCntParts].fRotZ	// Z����
			- m_OldKey[nCntParts].fRotZ;

		if (fRotDiffZ < -D3DX_PI)
		{// z���W�p�x���E
			fRotDiffZ += D3DX_PI * 2;
		}
		else if (fRotDiffZ > D3DX_PI)
		{// z���W�p�x���E
			fRotDiffZ += -D3DX_PI * 2;
		}

		if (fRotDiffX < -D3DX_PI)
		{// x���W�p�x���E
			fRotDiffX += D3DX_PI * 2;
		}
		else if (fRotDiffX > D3DX_PI)
		{// x���W�p�x���E
			fRotDiffX += -D3DX_PI * 2;
		}

		if (fRotDiffY < -D3DX_PI)
		{// x���W�p�x���E
			fRotDiffY += D3DX_PI * 2;
		}
		else if (fRotDiffY > D3DX_PI)
		{// x���W�p�x���E
			fRotDiffY += -D3DX_PI * 2;
		}

		//���݂̃t���[���̍��W�����߂�
		float fPosDestX = m_OldKey[nCntParts].fPosX
			+ fPosDiffX * fFrame;
		float fPosDestY = m_OldKey[nCntParts].fPosY
			+ fPosDiffY * fFrame;
		float fPosDestZ = m_OldKey[nCntParts].fPosZ
			+ fPosDiffZ * fFrame;

		//���݂̃t���[���̌��������߂�
		float fRotDestX = m_OldKey[nCntParts].fRotX
			+ fRotDiffX * fFrame;
		float fRotDestY = m_OldKey[nCntParts].fRotY
			+ fRotDiffY * fFrame;
		float fRotDestZ = m_OldKey[nCntParts].fRotZ
			+ fRotDiffZ * fFrame;

		// �ݒ�
		m_FileData.ppParts[nCntParts]->SetCurrentPosition(D3DXVECTOR3(fPosDestX, fPosDestY, fPosDestZ));
		m_FileData.ppParts[nCntParts]->SetCurrentRotation(D3DXVECTOR3(fRotDestX, fRotDestY, fRotDestZ));
	}

	m_fNowFrame += CManager::GetInstance()->GetSlow()->Get();

	if (m_aInfo[nNowMotion].pKeyInfo[nNowKey].nFrame == 0)
	{//�t���[����0�ł͂Ȃ��ꍇ
		m_nNowKey = 0;
		m_fNowFrame = 0;
		return;
	}

	if (m_fNowFrame >= nFrame)
	{//���݂̃t���[���������B�����ꍇ
		for (int nCntParts = 0; nCntParts < m_FileData.nNumParts; nCntParts++)
		{
			// �O��̒l���擾
			m_OldKey[nCntParts].fPosX = m_FileData.ppParts[nCntParts]->GetCurrentPosition().x;
			m_OldKey[nCntParts].fPosY = m_FileData.ppParts[nCntParts]->GetCurrentPosition().y;
			m_OldKey[nCntParts].fPosZ = m_FileData.ppParts[nCntParts]->GetCurrentPosition().z;
			m_OldKey[nCntParts].fRotX = m_FileData.ppParts[nCntParts]->GetCurrentRotation().x;
			m_OldKey[nCntParts].fRotY = m_FileData.ppParts[nCntParts]->GetCurrentRotation().y;
			m_OldKey[nCntParts].fRotZ = m_FileData.ppParts[nCntParts]->GetCurrentRotation().z;
		}

		if (nNextkey >= m_aInfo[nNowMotion].nNumKey - 1)
		{// �I��
			m_bEnd = true;
		}

		m_nOldType = nNowMotion;
		m_nNowKey = nNextkey;	//���̃L�[�Ɉړ�
		m_fNowFrame = 0;
	}
}

//==========================================================
// ���[�V�������ǂݍ���
//==========================================================
void CMotion::LoadMotionData(FILE *pFile)
{
	char aStr[128] = {};	//�z�u�������i�[�p
	int nCntParts = 0;
	int nCntKey = 0;
	bool bKey = false;

	while (1)
	{
		//�e�L�X�g�ǂݍ���
		int nResult = fscanf(pFile, "%s", &aStr[0]);

		if (nCntKey >= m_aInfo[m_nNumMotion].nNumKey && bKey == true)
		{//�L�[���ɗ����ꍇ
			m_nNumMotion++;	// ���[�V�������J�E���g�A�b�v
			break;
		}
		if (strcmp(&aStr[0], "LOOP") == 0)
		{//���[�v�m�F
			int nLoop = 0;
			fscanf(pFile, "%s", &aStr[0]);	//(=)�ǂݍ���
			fscanf(pFile, "%d", &nLoop);	//(=)�ǂݍ���

			if (nLoop == 0)
			{//���[�v���Ȃ��ꍇ
				m_aInfo[m_nNumMotion].bLoop = false;	//���[�v���Ȃ��悤�ɂ���
			}
			else
			{
				m_aInfo[m_nNumMotion].bLoop = true;	//���[�v����悤�ɂ���
			}
		}
		else if (strcmp(&aStr[0], "NUM_KEY") == 0)
		{//�L�[��
			fscanf(pFile, "%s", &aStr[0]);	//(=)�ǂݍ���
			fscanf(pFile, "%d", &m_aInfo[m_nNumMotion].nNumKey);	//�L�[���ǂݍ���

																					// �L�[�����̃������̊m��
			m_aInfo[m_nNumMotion].pKeyInfo = new KEY_INFO[m_aInfo[m_nNumMotion].nNumKey];

			// �p�[�c�����L�[���m��
			for (int nCnt = 0; nCnt < m_aInfo[m_nNumMotion].nNumKey; nCnt++)
			{
				memset(&m_aInfo[m_nNumMotion].pKeyInfo[nCnt], NULL, sizeof(KEY_INFO));

				m_aInfo[m_nNumMotion].pKeyInfo[nCnt].aKey = new KEY[m_FileData.nNumParts];
			}

			bKey = true;	//�L�[�����擾������Ԃɂ���
		}
		else if (strcmp(&aStr[0], "KEYSET") == 0)
		{//�p�[�c���m�F�����������ꍇ
			bool bFrame = false;
			nCntParts = 0;
			while (1)
			{
				//�ǂݍ���
				fscanf(pFile, "%s", &aStr[0]);

				if (nCntParts >= m_FileData.nNumParts)
				{//�p�[�c�����ɓ��B�����ꍇ
					break;
				}
				else if (strcmp(&aStr[0], "FRAME") == 0)
				{//�t���[����
					fscanf(pFile, "%s", &aStr[0]);	//(=)�ǂݍ���
					fscanf(pFile, "%d", &m_aInfo[m_nNumMotion].pKeyInfo[nCntKey].nFrame);	//�ǂݍ���
					bFrame = true;
				}
				else if (strcmp(&aStr[0], "KEY") == 0 && bFrame == true)
				{//�e�ԍ�
					while (1)
					{
						//�ǂݍ���
						fscanf(pFile, "%s", &aStr[0]);

						if (strcmp(&aStr[0], "END_KEY") == 0)
						{//�t���[����
							break;
						}
						else if (strcmp(&aStr[0], "POS") == 0)
						{//�t���[����
							fscanf(pFile, "%s", &aStr[0]);	//(=)�ǂݍ���
							fscanf(pFile, "%f", &m_aInfo[m_nNumMotion].pKeyInfo[nCntKey].aKey[nCntParts].fPosX);	//x���W�ǂݍ���
							fscanf(pFile, "%f", &m_aInfo[m_nNumMotion].pKeyInfo[nCntKey].aKey[nCntParts].fPosY);	//y���W�ǂݍ���
							fscanf(pFile, "%f", &m_aInfo[m_nNumMotion].pKeyInfo[nCntKey].aKey[nCntParts].fPosZ);	//z���W�ǂݍ���
						}
						else if (strcmp(&aStr[0], "ROT") == 0)
						{//�t���[����																   
							fscanf(pFile, "%s", &aStr[0]);	//(=)�ǂݍ���								
							fscanf(pFile, "%f", &m_aInfo[m_nNumMotion].pKeyInfo[nCntKey].aKey[nCntParts].fRotX);	//x���W�ǂݍ���
							fscanf(pFile, "%f", &m_aInfo[m_nNumMotion].pKeyInfo[nCntKey].aKey[nCntParts].fRotY);	//y���W�ǂݍ���
							fscanf(pFile, "%f", &m_aInfo[m_nNumMotion].pKeyInfo[nCntKey].aKey[nCntParts].fRotZ);	//z���W�ǂݍ���
						}
					}
					nCntParts++;
				}
				else if (strcmp(&aStr[0], "END_KEYSET") == 0)
				{//�p�[�c���I�������m�F�ł����ꍇ
					break;
				}
			}
			nCntKey++;	//�L�[���ړ�
		}
		if (strcmp(&aStr[0], "END_MOTIONSET") == 0)
		{//�L�����N�^�[���I�������m�F�ł����ꍇ
			m_nNumMotion++;	// ���[�V�������J�E���g�A�b�v
			break;
		}
	}
}

//==========================================================
// ���[�V�����ԍ��ݒ�
//==========================================================
void CMotion::BlendSet(int nType)
{
	if (nType >= 0 && nType < m_nNumMotion)
	{// ���[�V�����͈͓�
		if (m_nNowMotion != nType)
		{// ���݂̃��[�V�����ƈႤ�ꍇ
			m_nOldType = m_nNowMotion;
			m_nNowMotion = nType;	// ��ނ�ݒ�
			m_nNowKey = m_aInfo[m_nNowMotion].nNumKey - 1;
			m_fNowFrame = 0;
			m_bEnd = false;

			for (int nCntParts = 0; nCntParts < m_FileData.nNumParts; nCntParts++)
			{
				// �O��̒l���擾
				m_OldKey[nCntParts].fPosX = m_FileData.ppParts[nCntParts]->GetCurrentPosition().x;
				m_OldKey[nCntParts].fPosY = m_FileData.ppParts[nCntParts]->GetCurrentPosition().y;
				m_OldKey[nCntParts].fPosZ = m_FileData.ppParts[nCntParts]->GetCurrentPosition().z;
				m_OldKey[nCntParts].fRotX = m_FileData.ppParts[nCntParts]->GetCurrentRotation().x;
				m_OldKey[nCntParts].fRotY = m_FileData.ppParts[nCntParts]->GetCurrentRotation().y;
				m_OldKey[nCntParts].fRotZ = m_FileData.ppParts[nCntParts]->GetCurrentRotation().z;
			}
		}
	}
}

//==========================================================
// �p�[�c���擾
//==========================================================
void CMotion::SetModel(CModel **pModel, int nNumParts)
{
	m_FileData.ppParts = pModel;
	m_FileData.nNumParts = nNumParts;
}

//==========================================================
// �����ݒ�
//==========================================================
void CMotion::InitSet(int nType)
{
	if (nType >= 0 && nType < m_nNumMotion)
	{// ���[�V�����͈͓�
		m_nNowMotion = nType;	// ��ނ�ݒ�
		m_nNowKey = 0;
		m_fNowFrame = 0;
		m_bEnd = false;

		for (int nCntParts = 0; nCntParts < m_FileData.nNumParts; nCntParts++)
		{
			// �O��̒l���擾
			m_OldKey[nCntParts].fPosX = m_FileData.ppParts[nCntParts]->GetPosition().x + m_aInfo[m_nNowMotion].pKeyInfo[m_nNowKey].aKey[nCntParts].fPosX;
			m_OldKey[nCntParts].fPosY = m_FileData.ppParts[nCntParts]->GetPosition().y + m_aInfo[m_nNowMotion].pKeyInfo[m_nNowKey].aKey[nCntParts].fPosY;
			m_OldKey[nCntParts].fPosZ = m_FileData.ppParts[nCntParts]->GetPosition().z + m_aInfo[m_nNowMotion].pKeyInfo[m_nNowKey].aKey[nCntParts].fPosZ;
			m_OldKey[nCntParts].fRotX = m_FileData.ppParts[nCntParts]->GetRotation().x + m_aInfo[m_nNowMotion].pKeyInfo[m_nNowKey].aKey[nCntParts].fRotX;
			m_OldKey[nCntParts].fRotY = m_FileData.ppParts[nCntParts]->GetRotation().y + m_aInfo[m_nNowMotion].pKeyInfo[m_nNowKey].aKey[nCntParts].fRotY;
			m_OldKey[nCntParts].fRotZ = m_FileData.ppParts[nCntParts]->GetRotation().z + m_aInfo[m_nNowMotion].pKeyInfo[m_nNowKey].aKey[nCntParts].fRotZ;
		}
	}
}

//==========================================================
// �����ݒ�
//==========================================================
void CMotion::Set(int nType)
{
	if (nType >= 0 && nType < m_nNumMotion)
	{// ���[�V�����͈͓�
		if (m_nNowMotion != nType)
		{// ���݂̃��[�V�����ƈႤ�ꍇ
			m_nNowMotion = nType;	// ��ނ�ݒ�
			m_nNowKey = 0;
			m_fNowFrame = 0;
			m_bEnd = false;

			for (int nCntParts = 0; nCntParts < m_FileData.nNumParts; nCntParts++)
			{
				// �O��̒l���擾
				m_OldKey[nCntParts].fPosX = m_FileData.ppParts[nCntParts]->GetPosition().x + m_aInfo[m_nNowMotion].pKeyInfo[m_nNowKey].aKey[nCntParts].fPosX;
				m_OldKey[nCntParts].fPosY = m_FileData.ppParts[nCntParts]->GetPosition().y + m_aInfo[m_nNowMotion].pKeyInfo[m_nNowKey].aKey[nCntParts].fPosY;
				m_OldKey[nCntParts].fPosZ = m_FileData.ppParts[nCntParts]->GetPosition().z + m_aInfo[m_nNowMotion].pKeyInfo[m_nNowKey].aKey[nCntParts].fPosZ;
				m_OldKey[nCntParts].fRotX = m_FileData.ppParts[nCntParts]->GetRotation().x + m_aInfo[m_nNowMotion].pKeyInfo[m_nNowKey].aKey[nCntParts].fRotX;
				m_OldKey[nCntParts].fRotY = m_FileData.ppParts[nCntParts]->GetRotation().y + m_aInfo[m_nNowMotion].pKeyInfo[m_nNowKey].aKey[nCntParts].fRotY;
				m_OldKey[nCntParts].fRotZ = m_FileData.ppParts[nCntParts]->GetRotation().z + m_aInfo[m_nNowMotion].pKeyInfo[m_nNowKey].aKey[nCntParts].fRotZ;

				// �ݒ�
				m_FileData.ppParts[nCntParts]->SetCurrentPosition(D3DXVECTOR3(m_OldKey[nCntParts].fPosX, m_OldKey[nCntParts].fPosY, m_OldKey[nCntParts].fPosZ));
				m_FileData.ppParts[nCntParts]->SetCurrentRotation(D3DXVECTOR3(m_OldKey[nCntParts].fRotX, m_OldKey[nCntParts].fRotY, m_OldKey[nCntParts].fRotZ));
			}
		}
	}
}
