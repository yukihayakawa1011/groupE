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
		TYPE_CLEAR,		// �m���}�B��
		TYPE_FIAL,			// �m���}���s
		TYPE_MAX
	};

	CQuataUI();	// �R���X�g���N�^(�I�[�o�[���[�h)
	~CQuataUI();	// �f�X�g���N�^

			// �����o�֐�
	HRESULT Init(void);
	HRESULT Init(float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	static CQuataUI *Create(D3DXVECTOR3 pos, QUATATYPE type, float fWidth, float fHeight);
	void LostCount(void);

	// �����o�֐�(�擾)
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	QUATATYPE GetType(void) { return m_type; }
	int GetLife(void) { return m_nLife; }

	// �����o�֐�(�ݒ�)
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetType(QUATATYPE type) { m_type = type; }

private:	// �����������A�N�Z�X�\

	// �����o�֐�

	// �����o�ϐ�
	CObject2D *m_pObject;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	QUATATYPE m_type;
	const static char *m_apQuataFileName[TYPE_MAX];	// �����ǂݍ��݃t�@�C����
	int m_nLife;
	int m_nNumPlayer;
};

#endif