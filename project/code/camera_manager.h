//==========================================================
//
// �J�����}�l�[�W���[ [camera_manager.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _CAMERAMANAGER_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _CAMERAMANAGER_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

// �O���錾
class CCamera;

//==========================================================
// �T���v���̃N���X��`
//==========================================================
class CCameraManager
{
private:

	CCameraManager();		// �R���X�g���N�^
	~CCameraManager();	// �f�X�g���N�^

public:	// �N�ł��A�N�Z�X�\

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CCameraManager *GetInstance(void);
	static void Release(void);
	CCamera *GetTop(void) { return m_pTop; }
	CCamera *GetCur(void) { return m_pCur; }
	void ListIn(CCamera *pCamera);
	void ListOut(CCamera *pCamera);

private:	// �����������A�N�Z�X�\

	// �����o�֐�

	// �����o�ϐ�
	CCamera *m_pTop;	// �擪
	CCamera *m_pCur;	// �Ō��
	static CCameraManager *m_pInstance;	// �C���X�^���X
};

#endif
