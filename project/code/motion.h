//===================================================
//
// �K�w�\���ɂ�郂�[�V�������� [motion.h]
// Author Ibuki Okusada
//
//===================================================
#ifndef _MOITON_H_
#define _MOITON_H_

#include "main.h"		// main.h�Œ�`���Ă�����̂��K�v�Ȃ���include

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
	struct KEY
	{
		float fPosX;
		float fPosY;
		float fPosZ;
		float fRotX;
		float fRotY;
		float fRotZ;
	};

private:	// �����������A�N�Z�X�\�Ȓ�`

	// �L�[���
	struct KEY_INFO
	{
		int nFrame;			// �Đ��t���[��
		KEY *aKey;			// �p�[�c�̑���
	};

	// ���[�V�������
	struct INFO
	{
		bool bLoop;			// ���[�v���邩�ǂ���
		int nNumKey;			// �L�[��
		KEY_INFO *pKeyInfo;	// �L�[�̑���
	};

	//���̃t�@�C�����
	struct BodyFileData
	{
		CModel **ppParts;		// �p�[�c�̏��
		int nNumParts;			// �p�[�c��
	};

public:		// �N�ł��A�N�Z�X�\
	CMotion();	// �R���X�g���N�^
	~CMotion();	// �f�X�g���N�^

	// �����o�֐�
	void Uninit(void);
	void Update(void);
	void BlendSet(int nType);
	void Set(int nType);
	void InitSet(int nType);
	void SetModel(CModel **pModel, int nNumParts);
	void LoadMotionData(FILE *pFile);
	int GetNowKey(void) { return m_nNowKey; }
	int GetNowMotion(void) { return m_nNowMotion; }
	int GetOldMotion(void) { return m_nOldType; }
	float GetNowFrame(void) { return m_fNowFrame; }
	int GetNowNumKey(void) { return m_aInfo[m_nNowMotion].nNumKey; }
	bool GetEnd(void) { return m_bEnd; }

private:	// �����������A�N�Z�X�\

	// �����o�ϐ�
	KEY m_OldKey[64];		// �O��̃L�[���
	INFO m_aInfo[MAX_MOTION];	// ���[�V�������
	int m_nNumMotion;		// ���[�V������
	int m_nNowFrame;		// ���݂̃t���[����
	float m_fNowFrame;	// ���݂̃t���[����
	int m_nNowMotion;		// ���݂̃��[�V�����ԍ�
	bool m_bEnd;			// �I���������ǂ���
	int m_nNowKey;		// ���݂̃L�[��
	int m_nOldType;		// �O��̃��[�V�����^�C�v
	BodyFileData m_FileData;// �t�@�C�����
};

#endif
