//===================================================
//
// �K�w�\���ɂ�郂�[�V�������� [motion.h]
// Author Ibuki Okusada
//
//===================================================
#ifndef _MOITON_H_
#define _MOITON_H_

#include "main.h"		//main.h�Œ�`���Ă�����̂��K�v�Ȃ���include

#define MAX_MOTION		(64)

// �O���錾
class CModel;

//**********************************************************
// ���[�V�����N���X�̒�`
//**********************************************************
class CMotion
{
public: // �N�ł��A�N�Z�X�\�Ȓ�`

	// �L�[
	typedef struct
	{
		float fPosX;
		float fPosY;
		float fPosZ;
		float fRotX;
		float fRotY;
		float fRotZ;
	}KEY;

private:	// �����������A�N�Z�X�\�Ȓ�`

	// �L�[���
	typedef struct
	{
		int nFrame;			// �Đ��t���[��
		KEY *aKey;			// �p�[�c�̑���
	}KEY_INFO;

	// ���[�V�������
	typedef struct
	{
		bool bLoop;			// ���[�v���邩�ǂ���
		int nNumKey;		// �L�[��
		KEY_INFO *pKeyInfo;	// �L�[�̑���
	}INFO;

	//���̃t�@�C�����
	typedef struct
	{
		CModel **ppParts;		// �p�[�c�̏��
		int nNumParts;			// �p�[�c��
	}BodyFileData;

public:		// �N�ł��A�N�Z�X�\
	CMotion();	// �R���X�g���N�^
	~CMotion();	// �f�X�g���N�^

	// �����o�֐�
	void Uninit(void);
	void Update(void);
	void Update(float fSpeedMul);
	void BlendSet(int nType);
	void Set(int nType);
	void InitSet(int nType);
	void SetModel(CModel **pModel, int nNumParts);
	void LoadMotionData(FILE *pFile);
	int GetNowKey(void) { return m_nNowKey; }
	int GetNowMotion(void) { return m_nNowMotion; }
	int GetOldMotion(void) { return m_nOldType; }
	float GetNowFrame(void) { return m_fNowFrame; }
	int GetNowNumKey(void) { return aInfo[m_nNowMotion].nNumKey; }

private:	// �����������A�N�Z�X�\

	// �����o�ϐ�
	KEY m_OldKey[64];		// �O��̃L�[���
	INFO aInfo[MAX_MOTION];	// ���[�V�������
	int m_nNumMotion;		// ���[�V������
	int m_nNowFrame;		// ���݂̃t���[����
	float m_fNowFrame;		// ���݂̃t���[����
	int m_nNowMotion;		// ���݂̃��[�V�����ԍ�
	int m_nNowKey;			// ���݂̃L�[��
	int m_nOldType;			// �O��̃��[�V�����^�C�v
	BodyFileData m_FileData;// �t�@�C�����
};

#endif
