//==========================================================
//
// �m���}��UI [quataui.h]
// Author : Ryosuke Ohara
//
//==========================================================
#ifndef _QUATAUI_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _QUATAUI_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

//#include "../task.h"
#include "task.h"	// ����Ńt�@�C���C���N���[�h�ł��܂�

//�O���錾
class CObject2D;
class CLife;

//==========================================================
// UI�̃N���X��`
//==========================================================
class CQuataUI : public CTask
{

public:	// �N�ł��A�N�Z�X�\

	// UI�̎��
	enum QUATATYPE
	{
		TYPE_START = 0,	// �Z�Z�_����
		TYPE_FRAME,		// �m���}�B��
		TYPE_MAX
	};

	enum STATE
	{
		STATE_NONE = 0, // �Ȃ���Ȃ�
		STATE_MOVE,     // �����Ă���
		STATE_SCALING,  // �g�k
		STATE_UP,       // ��ɏオ��
		STATE_CLEAR,    // ���l��������
		STATE_CHANGE,   // �e�N�X�`���؂�ւ�
		STATE_SET,      // �^�C�}�[�̉�
		STATE_MAX
	};

	struct INFO
	{
		D3DXVECTOR3 m_pos;
	    D3DXVECTOR3 m_rot;
		D3DXCOLOR m_col;
	    QUATATYPE m_type;
		STATE m_state;
		float m_fHeight;
		float m_fWidht;
		float fStateCounter;
	};

	CQuataUI(int nPriority = 6);	// �R���X�g���N�^(�I�[�o�[���[�h)
	~CQuataUI();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	HRESULT Init(float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	static CQuataUI *Create(D3DXVECTOR3 pos, QUATATYPE type, STATE state, float fWidth, float fHeight);

	// �����o�֐�(�擾)
	D3DXVECTOR3 GetPosition(void) { return m_Info.m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_Info.m_rot; }
	D3DXCOLOR GetColor(void) { return m_Info.m_col; }
	STATE GetState(void) { return m_Info.m_state; }
	float GetHeight(void) { return m_Info.m_fHeight; }
	float GetWight(void) { return m_Info.m_fWidht; }
	QUATATYPE GetType(void) { return m_Info.m_type; }

	// �����o�֐�(�ݒ�)
	void SetPosition(D3DXVECTOR3 pos) { m_Info.m_pos = pos; }
	void SetRotation(D3DXVECTOR3 rot) { m_Info.m_rot = rot; }
	void SetColor(D3DXCOLOR col) { m_Info.m_col = col; }
	void SetState(STATE state) { m_Info.m_state = state; }
	void SetHeight(float fHeight) { m_Info.m_fHeight = fHeight; }
	void SetWight(float fWight) { m_Info.m_fWidht = fWight; }
	void SetType(QUATATYPE type) { m_Info.m_type = type; }

private:	// �����������A�N�Z�X�\

	// �����o�֐�

	// �����o�ϐ�
	CObject2D *m_pObject;
	INFO m_Info;
	const static char *m_apQuataFileName[TYPE_MAX];	// �����ǂݍ��݃t�@�C����
	int m_nNumPlayer;
};

#endif