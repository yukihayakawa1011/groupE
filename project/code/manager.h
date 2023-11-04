//===============================================
//
// �}�l�[�W���[�̏��� [manager.h]
// Author : Ibuki Okusada
//
//===============================================
#ifndef _MANAGER_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _MANAGER_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"

// �O���錾
class CRenderer;
class CInputKeyboard;
class CInputMouse;
class CInputPad;
class CDebugProc;
class CSound;
class CCamera;
class CLight;
class CTexture;
class CXFile;
class CFileLoad;
class CSlow;
class CFade;
class CMultiCamera;
class CMapCamera;
class CTime;
class CPlayer;
class CFileLoad;
class CEditor;
class CEnemyRoute;
class CCarManager;
class CEnemyManager;

//===============================================
// �V�[���N���X�̒�`
//===============================================
class CScene
{
public:

	// ���[�h�񋓌^
	enum MODE
	{
		MODE_TITLE = 0,	// �^�C�g�����
		MODE_TUTORIAL,	// �`���[�g���A�����
		MODE_GAME,		// �Q�[�����
		MODE_RESULT,	// ���U���g���
		MODE_RANKING,	// �����L���O���
		MODE_MAX
	};

	CScene();
	~CScene();

	// �����o�֐�
	static CScene *Create(MODE mode);
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	virtual CMapCamera *GetMapCamera(void) { return NULL; }
	virtual CPlayer *GetPlayer(void) { return NULL; }
	virtual CFileLoad *GetFileLoad(void) { return NULL; }
	virtual CEditor *GetEditor(void) { return NULL; }
	virtual void SendPosition(D3DXVECTOR3 pos) {  }
	virtual void SendRotation(D3DXVECTOR3 rot) {  }
	virtual void SendDamage(int nDamage) {  }
	virtual void SendLife(int nLife) {  }
	void SetMode(MODE mode) { m_mode = mode; }
	MODE GetMode(void) { return m_mode; }

private:
	MODE m_mode;	// ���[�h
};

//===============================================
// �}�l�[�W���[�N���X�̒�`
//===============================================
class CManager
{
public:	// �N�ł��A�N�Z�X�\

	CManager();	// �R���X�g���N�^
	~CManager();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	CRenderer *GetRenderer(void);
	CInputKeyboard *GetInputKeyboard(void);
	CInputMouse *GetInputMouse(void);
	CInputPad *GetInputPad(void);
	CDebugProc *GetDebugProc(void);
	CSound *GetSound(void);
	CMultiCamera *GetCamera(void);
	CLight *GetLight(void);
	CTexture *GetTexture(void);
	CXFile *GetModelFile(void);
	CSlow *GetSlow(void);
	CFade *GetFade(void);
	void SetMode(CScene::MODE mode);
	CScene::MODE GetMode(void) { return m_pScene->GetMode(); }
	CScene *GetScene(void) { return m_pScene; }
	static CManager *GetInstance(void);
	static void Release(void);

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void DataReset(void);

	// �ÓI�����o�ϐ�
	CRenderer *m_pRenderer;	// �����_���[�̃|�C���^
	CInputKeyboard *m_pInputKeyboard;	// �L�[�{�[�h�̃|�C���^
	CInputMouse *m_pInputMouse;	// �}�E�X�̃|�C���^
	CInputPad *m_pInputPad;	// �p�b�h�̃|�C���^
	CDebugProc *m_pDebugProc;	// �f�o�b�O�\���̃|�C���^
	CMultiCamera *m_pCamera;		// �J�����̃|�C���^
	CLight *m_pLight;		// ���C�g�̃|�C���^
	CTexture *m_pTexture;	// �e�N�X�`���̃|�C���^
	CXFile *m_pModelFile;	// X�t�@�C���̃|�C���^
	CSound *m_pSound;		// �T�E���h�̃|�C���^
	CSlow *m_pSlow;			// �X���[�̃|�C���^
	CScene *m_pScene;		// �V�[���̃|�C���^
	CFade *m_pFade;			// �t�F�[�h�̃|�C���^
	static CManager *m_pManager;	// �}�l�[�W���[�̃|�C���^
};


#endif

