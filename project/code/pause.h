//==========================================================
//
// �|�[�Y�̏��� [pause.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "object2D.h"

//**********************************************************
// �|�[�Y�N���X�̒�`
//**********************************************************
class CPause
{
private:	// �����������A�N�Z�X�\�Ȓ�`

	// ��ԗ񋓌^
	enum MENU
	{
		MENU_CONTINUE = 0,	// �Q�[���ɖ߂�
		MENU_RETRY,			// �Q�[������蒼��
		MENU_QUIT,			// �^�C�g����ʂɖ߂�
		MENU_MAX
	};

	// ��ޗ񋓌^
	enum TYPE
	{
		TYPE_CONTINUE = 0,	// �Q�[���ɖ߂�
		TYPE_RETRY,			// �Q�[������蒼��
		TYPE_QUIT,			// �^�C�g����ʂɖ߂�
		TYPE_BG,				// �w�i
		TYPE_MAX
	};

	// �|���S���\����
	struct SPolygon
	{
		CObject2D *pObject2D;	// 2D�I�u�W�F�N�g�ւ̃|�C���^
		D3DXCOLOR col;		// �F
	};

public:		// �N�ł��A�N�Z�X�\

	CPause();	// �R���X�g���N�^
	~CPause();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	bool Update(void);
	void Draw(void);
	static CPause *Create(void);
	bool GetSelect(void) { return m_bSelect; }
	void SetDraw(const bool bValue);

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void ColorSet(void);

	// �����o�ϐ�
	static const char* m_apTexPass[TYPE_MAX];	// �t�@�C���p�X��
	MENU m_SelectMenu;				// �I������
	CObject2D *m_pBg;					// �w�i�p
	SPolygon m_aMenu[MENU_MAX];		// ���j���[�p
	bool m_bSelect;					// �I���������ǂ���
	float m_fMoveCol_a;				// �����x�̕ω���
	int m_nStartDeltaTime;	// �v���J�n�^�C�}�[
	int m_nPauseTimer;	// �|�[�Y�^�C�}�[��
};

#endif
