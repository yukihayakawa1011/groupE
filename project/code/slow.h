//==========================================================
//
// �X���[�̏����Ǘ� [slow.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _SLOW_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _SLOW_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

//**********************************************************
// �X���[�N���X�̒�`
//**********************************************************
class CSlow
{
public:		// �N�ł��A�N�Z�X�\

	CSlow();	// �R���X�g���N�^
	~CSlow();	// �f�X�g���N�^

	// �����o�֐�
	void Init(void);
	void Uninit(void);
	void Update(void);
	float Get(void);
	float GetOld(void);
	void SetSlow(bool bUse);
	void SetSlow(float fValue) { m_fAdd = fValue; }

private:	// �����������A�N�Z�X�\

	bool m_b;			// �J�E���g����������ۂ�
	bool m_bUse;		// �X���[���͂��ꂽ��
	int m_nBoostCnt;	// �����㏸�J�E���g
	int m_nTimeCnt;		// �^�C�}�[
	int m_nTimer;		// �J�E���g�K��l
	float m_fAdd;		// �X���[�{��
	float m_fMulOld;	// �O��̔{��
};

#endif